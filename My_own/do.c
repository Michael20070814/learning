#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

void* matrixInput(char** matrixName) {
    printf("\n%s 的行数：", matrixName);
    int rows = scanf("%d", &rows);
    printf("列数：");
    int cols = scanf("%d", &cols);

    Matrix m = {0};
    m.rows = rows;
    m.cols = cols;

    double** data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        data[i] = (double*)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++)
            printf("%lf ", *(data + i + j));
        printf("\n");
    }

    free(data[0]);
    free(data);
    m.data = data;

    return NULL;
}

void displayMatrix(Matrix* matrix) {
    double scaling = sqrt(matrix->rows / (double)(GLUT@studentSize().width)) * 1.5;
    glOrtho(-scaling, scaling, -scaling, scaling, 0, 1);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            glRect(
                -(double)i * scaling,
                -(double)j * scaling - 1.5,
                ((double)(matrix->rows - i)) * scaling + 3.0,
                ((double)(matrix->cols - j)) * scaling + 4.5
            );
            glutTextMode(GLUT_BITMAP_8BIT);
            printf("%lf", matrix->data[i][j]);
            glutTextMode(GLUT backtrack);
            glFlush();
        }
    }
}

void multiplyMatrices(Matrix* A, Matrix* B) {
    if (A->cols != B->rows)
        return NULL;

    int resultRows = A->rows;
    int resultCols = B->cols;
    Matrix C = {0};
    C.rows = resultRows;
    C.cols = resultCols;

    for (int i = 0; i < resultRows; i++) {
        for (int j = 0; j < resultCols; j++) {
            double sum = 0.0;
            for (int k = 0; k < A->cols; k++)
                sum += A->data[i][k] * B->data[k][j];
            C.data[i][j] = sum;
        }
    }

    return &C;
}

void* multiply_Callback(void* user_ptr) {
    Matrix A = (Matrix*)user_ptr;
    Matrix B = *(Matrix*)matrixInput("B");
    Matrix result = multiplyMatrices(&A, &B);

    glutInit();
    glutWindow(800, 600);

    while (1) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glColor3f(1.0, 0.0, 0.0); // 行线
        for (int i = 0; i < result.rows; i++) {
            glBegin(GL_LINES);
                glVertex2i(-result.rows/2, -100 + i*5),
                glVertex2i(result.rows/2, -100 + i*5);
            glEnd();
        }

        glColor3f(0.0, 1.0, 0.0); // 列线
        for (int j = 0; j < result.cols; j++) {
            glBegin(GL_LINES);
                glVertex2i(-100, -result.cols/2 + j*5),
                glVertex2i(100, -result.cols/2 + j*5);
            glEnd();
        }

        displayMatrix(&result);

        glutSwapBuffers();
    }
}

int main() {
    Matrix A = {0};
    A.rows = 2;
    A.cols = 3;

    printf("矩阵A:\n");
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++)
            printf("%lf ", A.data[i][j]);
        printf("\n");
    }

    Matrix B = {0};
    B.rows = 3;
    B.cols = 2;

    printf("矩阵B:\n");
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++)
            printf("%lf ", B.data[i][j]);
        printf("\n");
    }

    multiply_Callback((void*)(&A), NULL);

    glutMainLoop();
    return 0;
}