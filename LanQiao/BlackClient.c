#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL
#define HASH_SIZE 400009

typedef long long ll;

typedef struct Node {
    ll key;
    int cnt;
    struct Node *next;
} Node;

Node *hash_table[HASH_SIZE];

unsigned int hash_func(ll x) {
    if (x < 0) x = -x;
    return (unsigned int)(x % HASH_SIZE);
}

void insert_hash(ll x) {
    unsigned int h = hash_func(x);
    Node *p = hash_table[h];
    while (p) {
        if (p->key == x) {
            p->cnt++;
            return;
        }
        p = p->next;
    }
    p = (Node *)malloc(sizeof(Node));
    p->key = x;
    p->cnt = 1;
    p->next = hash_table[h];
    hash_table[h] = p;
}

int find_count(ll x) {
    unsigned int h = hash_func(x);
    Node *p = hash_table[h];
    while (p) {
        if (p->key == x) return p->cnt;
        p = p->next;
    }
    return 0;
}

ll qpow(ll a, ll b) {
    ll r = 1;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int main() {
    int L, i;
    scanf("%d", &L);

    int S = L - 2;
    ll *a = (ll *)malloc(sizeof(ll) * L);

    for (i = 0; i < L; i++) {
        scanf("%lld", &a[i]);
        insert_hash(a[i]);
    }

    ll *fact = (ll *)malloc(sizeof(ll) * (S + 1));
    ll *invfact = (ll *)malloc(sizeof(ll) * (S + 1));

    fact[0] = 1;
    for (i = 1; i <= S; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    invfact[S] = qpow(fact[S], MOD - 2);
    for (i = S; i >= 1; i--) {
        invfact[i - 1] = invfact[i] * i % MOD;
    }

    ll base = fact[S];
    for (i = 0; i < HASH_SIZE; i++) {
        Node *p = hash_table[i];
        while (p) {
            base = base * invfact[p->cnt] % MOD;
            p = p->next;
        }
    }

    ll ans = 0;
    ll d;
    for (d = 1; d * d <= S; d++) {
        if (S % d != 0) continue;

        ll n = d;
        ll m = S / d;

        int cnt_n = find_count(n);
        int cnt_m = find_count(m);

        if (n == m) {
            if (cnt_n >= 2) {
                ll ways = base * cnt_n % MOD * (cnt_n - 1) % MOD;
                ans = (ans + ways) % MOD;
            }
        } else {
            if (cnt_n > 0 && cnt_m > 0) {
                ll ways = base * cnt_n % MOD * cnt_m % MOD;
                ans = (ans + ways) % MOD;
                ans = (ans + ways) % MOD;
            }
        }
    }

    printf("%lld\n", ans % MOD);

    free(a);
    free(fact);
    free(invfact);

    return 0;
}