#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 7
#define INITIAL_CAP 128

typedef struct {
    int *ids;
    int *counts;
    int size;
    int cap;
} SparseVec;

typedef struct {
    char *text;
    SparseVec sem;
    double sem_norm;
    double structure[DIM];
} Sentence;

typedef struct {
    char *key;
    int value;
} HashEntry;

typedef struct {
    double scores[DIM];
    int word_count;
    double total_len;
    double total_len_sq;
    double vowel_ratio_sum;
} StructureStats;

typedef struct {
    SparseVec *vec;
    int insert_new;
} SemanticBuildCtx;

static Sentence *sentences = NULL;
static int line_num = 0;
static int sentence_cap = 0;

static char **dict = NULL;
static int dict_num = 0;
static int dict_cap = 0;
static HashEntry *dict_hash = NULL;
static int dict_hash_size = 0;
static int dict_hash_count = 0;

static char **stop_words = NULL;
static int stop_num = 0;
static int stop_cap = 0;

static double *similarity = NULL;

static void *xmalloc(size_t size);
static void *xcalloc(size_t count, size_t size);
static void *xrealloc(void *ptr, size_t size);
static char *xstrdup_range(const char *s, size_t len);
static char *read_line_dynamic(FILE *fp);
static int open_file(FILE **fp, const char *name, const char *mode);

static int ispunct_real(unsigned char c);
static void load_stop_list(void);
static int is_stop_word(const char *word);
static int cmp_string_ptr(const void *a, const void *b);

static unsigned long hash_string(const char *s);
static void dict_hash_init(void);
static void dict_hash_free(void);
static void dict_hash_rebuild(int new_size);
static int dict_lookup(const char *word);
static int dict_get_id(const char *word, int insert_new);

static void sparse_init(SparseVec *v);
static void sparse_free(SparseVec *v);
static void sparse_add(SparseVec *v, int id);
static double sparse_norm(const SparseVec *v);

static void for_each_word(const char *text, void (*callback)(const char *, void *), void *ctx);
static void process_document(void);
static void build_document_vectors(void);
static void compute_structure_vector(const char *text, double out[DIM]);
static void min_max_array(double data[DIM]);
static double cosine_array(const double a[DIM], const double b[DIM]);
static double semantic_similarity(const SparseVec *doc_vec, double doc_norm,
                                  const double *query_counts, double query_norm);
static SparseVec build_semantic_vector(const char *text, int insert_new);
static void structure_word_callback(const char *word, void *ctx);
static void semantic_word_callback(const char *word, void *ctx);
static int *retrieve_top_k(int k);
static int cmp_desc(const void *a, const void *b);
static void print_results(int k, const int *result);
static void cleanup(void);

int main(void)
{
    process_document();
    load_stop_list();
    dict_hash_init();
    build_document_vectors();

    char *query = read_line_dynamic(stdin);
    if (query == NULL)
        query = xstrdup_range("", 0);

    double alpha = 0.0;
    int k = 0;
    scanf("%lf", &alpha);
    scanf("%d", &k);
    if (k < 0)
        k = 0;
    if (k > line_num)
        k = line_num;

    SparseVec query_vec = build_semantic_vector(query, 0);
    double query_norm = sparse_norm(&query_vec);
    double *query_counts = (double *)xcalloc((size_t)dict_num, sizeof(double));
    for (int i = 0; i < query_vec.size; ++i)
        query_counts[query_vec.ids[i]] = (double)query_vec.counts[i];

    double query_structure[DIM];
    compute_structure_vector(query, query_structure);

    similarity = (double *)xcalloc((size_t)line_num, sizeof(double));
    for (int i = 0; i < line_num; ++i) {
        double sem = semantic_similarity(&sentences[i].sem, sentences[i].sem_norm,
                                         query_counts, query_norm);
        double str = cosine_array(query_structure, sentences[i].structure);
        similarity[i] = alpha * sem + (1.0 - alpha) * str;
    }

    int *result = retrieve_top_k(k);
    print_results(k, result);

    free(result);
    free(query_counts);
    sparse_free(&query_vec);
    free(query);
    cleanup();
    return 0;
}

static void *xmalloc(size_t size)
{
    void *ptr = malloc(size == 0 ? 1 : size);
    if (ptr == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

static void *xcalloc(size_t count, size_t size)
{
    void *ptr = calloc(count == 0 ? 1 : count, size == 0 ? 1 : size);
    if (ptr == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

static void *xrealloc(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size == 0 ? 1 : size);
    if (new_ptr == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

static char *xstrdup_range(const char *s, size_t len)
{
    char *copy = (char *)xmalloc(len + 1);
    if (len > 0)
        memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

static char *read_line_dynamic(FILE *fp)
{
    size_t cap = 128;
    size_t len = 0;
    char *line = (char *)xmalloc(cap);
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            break;
        if (len + 1 >= cap) {
            cap *= 2;
            line = (char *)xrealloc(line, cap);
        }
        line[len++] = (char)ch;
    }

    if (ch == EOF && len == 0) {
        free(line);
        return NULL;
    }

    if (len > 0 && line[len - 1] == '\r')
        len--;
    line[len] = '\0';
    return line;
}

static int open_file(FILE **fp, const char *name, const char *mode)
{
    char path[512];
    *fp = fopen(name, mode);
    if (*fp != NULL)
        return 1;

    snprintf(path, sizeof(path), "BigWork/%s", name);
    *fp = fopen(path, mode);
    if (*fp != NULL)
        return 1;

    snprintf(path, sizeof(path), "output/%s", name);
    *fp = fopen(path, mode);
    if (*fp != NULL)
        return 1;

    snprintf(path, sizeof(path), "BigWork/output/%s", name);
    *fp = fopen(path, mode);
    return *fp != NULL;
}

static int ispunct_real(unsigned char c)
{
    return ispunct(c) && c != '\'';
}

static void load_stop_list(void)
{
    FILE *fp = NULL;
    if (!open_file(&fp, "stopList.txt", "r"))
        return;

    char *line;
    while ((line = read_line_dynamic(fp)) != NULL) {
        size_t len = strlen(line);
        while (len > 0 && isspace((unsigned char)line[len - 1]))
            line[--len] = '\0';
        size_t start = 0;
        while (line[start] && isspace((unsigned char)line[start]))
            start++;

        if (line[start] != '\0') {
            for (size_t i = start; line[i] != '\0'; ++i)
                line[i] = (char)tolower((unsigned char)line[i]);

            if (stop_num == stop_cap) {
                stop_cap = stop_cap == 0 ? INITIAL_CAP : stop_cap * 2;
                stop_words = (char **)xrealloc(stop_words, (size_t)stop_cap * sizeof(char *));
            }
            stop_words[stop_num++] = xstrdup_range(line + start, strlen(line + start));
        }
        free(line);
    }

    fclose(fp);
    qsort(stop_words, (size_t)stop_num, sizeof(char *), cmp_string_ptr);
}

static int cmp_string_ptr(const void *a, const void *b)
{
    const char *sa = *(const char * const *)a;
    const char *sb = *(const char * const *)b;
    return strcmp(sa, sb);
}

static int is_stop_word(const char *word)
{
    int low = 0;
    int high = stop_num - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(word, stop_words[mid]);
        if (cmp == 0)
            return 1;
        if (cmp < 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}

static unsigned long hash_string(const char *s)
{
    unsigned long h = 2166136261u;
    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 16777619u;
    }
    return h;
}

static void dict_hash_init(void)
{
    dict_hash_size = 4096;
    dict_hash_count = 0;
    dict_hash = (HashEntry *)xcalloc((size_t)dict_hash_size, sizeof(HashEntry));
}

static void dict_hash_free(void)
{
    free(dict_hash);
    dict_hash = NULL;
    dict_hash_size = 0;
    dict_hash_count = 0;
}

static void dict_hash_rebuild(int new_size)
{
    HashEntry *old_hash = dict_hash;
    int old_size = dict_hash_size;

    dict_hash = (HashEntry *)xcalloc((size_t)new_size, sizeof(HashEntry));
    dict_hash_size = new_size;
    dict_hash_count = 0;

    for (int i = 0; i < old_size; ++i) {
        if (old_hash[i].key != NULL) {
            unsigned long h = hash_string(old_hash[i].key);
            int pos = (int)(h & (unsigned long)(dict_hash_size - 1));
            while (dict_hash[pos].key != NULL)
                pos = (pos + 1) & (dict_hash_size - 1);
            dict_hash[pos] = old_hash[i];
            dict_hash_count++;
        }
    }

    free(old_hash);
}

static int dict_lookup(const char *word)
{
    if (dict_hash == NULL || dict_hash_size == 0)
        return -1;

    unsigned long h = hash_string(word);
    int pos = (int)(h & (unsigned long)(dict_hash_size - 1));
    while (dict_hash[pos].key != NULL) {
        if (strcmp(dict_hash[pos].key, word) == 0)
            return dict_hash[pos].value;
        pos = (pos + 1) & (dict_hash_size - 1);
    }
    return -1;
}

static int dict_get_id(const char *word, int insert_new)
{
    int id = dict_lookup(word);
    if (id >= 0 || !insert_new)
        return id;

    if ((dict_hash_count + 1) * 10 >= dict_hash_size * 7)
        dict_hash_rebuild(dict_hash_size * 2);

    if (dict_num == dict_cap) {
        dict_cap = dict_cap == 0 ? INITIAL_CAP : dict_cap * 2;
        dict = (char **)xrealloc(dict, (size_t)dict_cap * sizeof(char *));
    }

    char *copy = xstrdup_range(word, strlen(word));
    id = dict_num;
    dict[dict_num++] = copy;

    unsigned long h = hash_string(copy);
    int pos = (int)(h & (unsigned long)(dict_hash_size - 1));
    while (dict_hash[pos].key != NULL)
        pos = (pos + 1) & (dict_hash_size - 1);
    dict_hash[pos].key = copy;
    dict_hash[pos].value = id;
    dict_hash_count++;

    return id;
}

static void sparse_init(SparseVec *v)
{
    v->ids = NULL;
    v->counts = NULL;
    v->size = 0;
    v->cap = 0;
}

static void sparse_free(SparseVec *v)
{
    free(v->ids);
    free(v->counts);
    v->ids = NULL;
    v->counts = NULL;
    v->size = 0;
    v->cap = 0;
}

static void sparse_add(SparseVec *v, int id)
{
    for (int i = 0; i < v->size; ++i) {
        if (v->ids[i] == id) {
            v->counts[i]++;
            return;
        }
    }

    if (v->size == v->cap) {
        v->cap = v->cap == 0 ? 8 : v->cap * 2;
        v->ids = (int *)xrealloc(v->ids, (size_t)v->cap * sizeof(int));
        v->counts = (int *)xrealloc(v->counts, (size_t)v->cap * sizeof(int));
    }
    v->ids[v->size] = id;
    v->counts[v->size] = 1;
    v->size++;
}

static double sparse_norm(const SparseVec *v)
{
    double sum = 0.0;
    for (int i = 0; i < v->size; ++i)
        sum += (double)v->counts[i] * v->counts[i];
    return sqrt(sum);
}

static void for_each_word(const char *text, void (*callback)(const char *, void *), void *ctx)
{
    size_t cap = 32;
    size_t len = 0;
    char *word = (char *)xmalloc(cap);

    for (const char *p = text;; ++p) {
        unsigned char c = (unsigned char)*p;
        int delim = (c == '\0') || isspace(c) || ispunct_real(c);

        if (delim) {
            if (len > 0) {
                word[len] = '\0';
                if (!is_stop_word(word))
                    callback(word, ctx);
                len = 0;
            }
            if (c == '\0')
                break;
        } else {
            if (len + 1 >= cap) {
                cap *= 2;
                word = (char *)xrealloc(word, cap);
            }
            word[len++] = (char)tolower(c);
        }
    }

    free(word);
}

static void process_document(void)
{
    FILE *fp = NULL;
    if (!open_file(&fp, "document.txt", "rb")) {
        perror("Error opening document.txt");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fsize < 0) {
        fclose(fp);
        fprintf(stderr, "Failed to get document size\n");
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *)xmalloc((size_t)fsize + 1);
    size_t bytes_read = fread(buffer, 1, (size_t)fsize, fp);
    buffer[bytes_read] = '\0';
    fclose(fp);

    const char *start = buffer;
    while (*start) {
        while (*start && isspace((unsigned char)*start))
            start++;
        if (*start == '\0')
            break;

        const char *p = start;
        while (*p && *p != '.' && *p != '?' && *p != '!' && *p != '\n')
            p++;

        size_t len = (*p && *p != '\n') ? (size_t)(p - start + 1) : (size_t)(p - start);
        while (len > 0 && isspace((unsigned char)start[len - 1]))
            len--;

        if (len > 0) {
            if (line_num == sentence_cap) {
                sentence_cap = sentence_cap == 0 ? INITIAL_CAP : sentence_cap * 2;
                sentences = (Sentence *)xrealloc(sentences, (size_t)sentence_cap * sizeof(Sentence));
            }
            sentences[line_num].text = xstrdup_range(start, len);
            sparse_init(&sentences[line_num].sem);
            sentences[line_num].sem_norm = 0.0;
            for (int i = 0; i < DIM; ++i)
                sentences[line_num].structure[i] = 0.0;
            line_num++;
        }

        if (*p == '\0')
            break;
        start = p + 1;
    }

    free(buffer);
}

static void structure_word_callback(const char *word, void *ctx)
{
    StructureStats *stats = (StructureStats *)ctx;
    int len = (int)strlen(word);
    int vowels = 0;

    for (int i = 0; i < len; ++i) {
        char c = word[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            vowels++;
    }

    stats->word_count++;
    stats->total_len += len;
    stats->total_len_sq += (double)len * len;
    if (len > 0)
        stats->vowel_ratio_sum += (double)vowels / len;
}

static void compute_structure_vector(const char *text, double out[DIM])
{
    int valid_count = 0;
    int punct_count = 0;
    int upper_count = 0;
    int digit_count = 0;

    for (const char *p = text; *p != '\0'; ++p) {
        unsigned char c = (unsigned char)*p;
        if (isspace(c))
            continue;
        valid_count++;
        if (ispunct(c))
            punct_count++;
        if (isupper(c))
            upper_count++;
        if (isdigit(c))
            digit_count++;
    }

    StructureStats stats;
    memset(&stats, 0, sizeof(stats));
    for_each_word(text, structure_word_callback, &stats);

    if (stats.word_count > 0) {
        double mean = stats.total_len / stats.word_count;
        out[0] = mean;
        out[1] = stats.total_len_sq / stats.word_count - mean * mean;
        if (out[1] < 0 && out[1] > -1e-9)
            out[1] = 0.0;
        out[2] = stats.word_count;
        out[3] = stats.vowel_ratio_sum / stats.word_count;
    } else {
        out[0] = out[1] = out[2] = out[3] = 0.0;
    }

    if (valid_count > 0) {
        out[4] = (double)punct_count / valid_count;
        out[5] = (double)upper_count / valid_count;
        out[6] = (double)digit_count / valid_count;
    } else {
        out[4] = out[5] = out[6] = 0.0;
    }

    min_max_array(out);
}

static void min_max_array(double data[DIM])
{
    double min_val = data[0];
    double max_val = data[0];
    for (int i = 1; i < DIM; ++i) {
        if (data[i] < min_val)
            min_val = data[i];
        if (data[i] > max_val)
            max_val = data[i];
    }

    double range = max_val - min_val;
    if (range <= 1e-12) {
        for (int i = 0; i < DIM; ++i)
            data[i] = 0.0;
        return;
    }

    for (int i = 0; i < DIM; ++i)
        data[i] = (data[i] - min_val) / range;
}

static double cosine_array(const double a[DIM], const double b[DIM])
{
    double dot = 0.0;
    double norm_a = 0.0;
    double norm_b = 0.0;

    for (int i = 0; i < DIM; ++i) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }

    if (norm_a <= 1e-12 || norm_b <= 1e-12)
        return 0.0;
    return dot / (sqrt(norm_a) * sqrt(norm_b));
}

static void semantic_word_callback(const char *word, void *ctx)
{
    SemanticBuildCtx *build = (SemanticBuildCtx *)ctx;
    int id = dict_get_id(word, build->insert_new);
    if (id >= 0)
        sparse_add(build->vec, id);
}

static SparseVec build_semantic_vector(const char *text, int insert_new)
{
    SparseVec vec;
    sparse_init(&vec);

    SemanticBuildCtx ctx;
    ctx.vec = &vec;
    ctx.insert_new = insert_new;
    for_each_word(text, semantic_word_callback, &ctx);

    return vec;
}

static void build_document_vectors(void)
{
    for (int i = 0; i < line_num; ++i) {
        sentences[i].sem = build_semantic_vector(sentences[i].text, 1);
        sentences[i].sem_norm = sparse_norm(&sentences[i].sem);
        compute_structure_vector(sentences[i].text, sentences[i].structure);
    }
}

static double semantic_similarity(const SparseVec *doc_vec, double doc_norm,
                                  const double *query_counts, double query_norm)
{
    if (doc_norm <= 1e-12 || query_norm <= 1e-12)
        return 0.0;

    double dot = 0.0;
    for (int i = 0; i < doc_vec->size; ++i)
        dot += (double)doc_vec->counts[i] * query_counts[doc_vec->ids[i]];

    return dot / (doc_norm * query_norm);
}

static int cmp_desc(const void *a, const void *b)
{
    int idx1 = *(const int *)a;
    int idx2 = *(const int *)b;
    double v1 = similarity[idx1];
    double v2 = similarity[idx2];

    if (v1 > v2)
        return -1;
    if (v1 < v2)
        return 1;
    return idx1 - idx2;
}

static int *retrieve_top_k(int k)
{
    if (k <= 0 || line_num <= 0)
        return NULL;

    int *indices = (int *)xmalloc((size_t)line_num * sizeof(int));
    for (int i = 0; i < line_num; ++i)
        indices[i] = i;

    qsort(indices, (size_t)line_num, sizeof(int), cmp_desc);

    int *result = (int *)xmalloc((size_t)k * sizeof(int));
    for (int i = 0; i < k; ++i)
        result[i] = indices[i];

    free(indices);
    return result;
}

static void print_results(int k, const int *result)
{
    if (k <= 0 || result == NULL)
        return;

    for (int i = 0; i < k; ++i)
        printf("%s\n", sentences[result[i]].text);
}

static void cleanup(void)
{
    for (int i = 0; i < line_num; ++i) {
        free(sentences[i].text);
        sparse_free(&sentences[i].sem);
    }
    free(sentences);

    for (int i = 0; i < dict_num; ++i)
        free(dict[i]);
    free(dict);
    dict_hash_free();

    for (int i = 0; i < stop_num; ++i)
        free(stop_words[i]);
    free(stop_words);

    free(similarity);
}
