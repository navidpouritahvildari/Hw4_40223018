/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void allocatematrix(int*** matrix, int rows, int cols) {
    *matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = (int*)malloc(cols * sizeof(int));
    }
}

void toeplitzmatrix(int** matrix, int n, int* ptr) {
    int j;
    int k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
           k=j-i;
           if(k<0)
           {
               k=n-k-1;
           }
           matrix[i][j]=ptr[k];
        }
    }
}

void printmatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int checkmatrix(int** matrix, int i, int j) {
    int row,col;
   printf("please enter row and col");
   scanf("%d  %d",&row,&col);
   return matrix[row-1][col-1];
}

void freematrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows, cols;
    int row,col;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    int** matrix;
    allocatematrix(&matrix, rows, cols);

    int* ptr = (int*)malloc((rows + cols - 1) * sizeof(int));
    printf("Enter the elements of the first row: ");
    for (int i = 0; i < cols; i++) {
        scanf("%d", &ptr[i]);
    }
    printf("Enter the elements of the first column: ");
    for (int i = cols; i < rows + cols - 1; i++) {
        scanf("%d", &ptr[i]);
    }

    toeplitzmatrix(matrix, rows, ptr);

    printf("Toeplitz matrix:\n");
    printmatrix(matrix, rows, cols);

    int result = checkmatrix(matrix, row, col);
    printf("Result of checkmatrix: %d\n", result);

    freematrix(matrix, rows);
    free(ptr);

    return 0;
}
