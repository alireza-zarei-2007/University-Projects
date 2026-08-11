/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 02 - Task A
 * Description: Write a C function that receives the dimension N of a square matrix and the matrix itself (using pointers only, no array subscripting [] allowed). 
                The function must calculate and return the sum of elements in the upper triangle (including the main diagonal and elements above it).
 */

#include <stdio.h>
#include <stdlib.h>
int sumUpperTriangle(int N, int **matrix) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j >= i) {
                sum += *(*(matrix + i) + j);
            }
        }
    }
    return sum;
}
int main(void) {
    int N = 0;
    printf("Enter the number: ");
    scanf("%d", &N);
    int **matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        *(matrix + i) = (int*)malloc(N * sizeof(int));
    }
    printf("Enter the matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", (*(matrix + i) + j));
        }
    }
    printf("The result is: %d\n", sumUpperTriangle(N, matrix));
    for (int i = 0; i < N; i++) {
        free(*(matrix + i));
    }
    free(matrix);
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 02 - Task B
 * Description: Write a C function that receives the dimension N of a square matrix and the matrix itself 
                (using pointers only, no array subscripting [] allowed). The function must check whether the matrix is an identity matrix 
                (all elements on the main diagonal are 1 and all other elements are 0). Return 1 if true, otherwise return 0.
 */

#include <stdio.h>
#include <stdlib.h>
int isIdentityMatrix(int N, int **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                if (*(*(matrix + i) + j) != 1) {
                    return 0;
                }
            } else {
                if (*(*(matrix + i) + j) != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main(void) {
    int N = 0;
    printf("Enter the number: ");
    scanf("%d", &N);
    int **matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        *(matrix + i) = (int*)malloc(N * sizeof(int));
    }
    printf("Enter the matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", (*(matrix + i) + j));
        }
    }
    printf("The result is: %d\n", isIdentityMatrix(N, matrix));
    for (int i = 0; i < N; i++) {
        free(*(matrix + i));
    }
    free(matrix);
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 02 - Task C
 * Description: Write a function named deleteElement that receives three parameters as pointers to perform the following operations on an input array:
                Search: Find the element with value *target in the array starting at address addr.
                Delete and Shift: If found, remove the first occurrence. All subsequent elements must be shifted one position to the left.
                Update Size: If deletion is successful, decrement the value of *size (which represents the number of elements in the array) by one.
 */

#include <stdio.h>
#include <stdlib.h>
void deleteElement(int *addr, int *target, int *size) {
    for (int i = 0; i < *size; i++) {
        if (*(addr + i) == *target) {
            for (int j = i; j < *size; j++) {
                if (j == *size - 1) {
                    addr = (int*)realloc(addr, (*size - 1) * sizeof(int));
                    *size = *size - 1;
                    break;
                }
                *(addr + j) = *(addr + (j + 1));
            }
            break;
        }
    }
}

int main(void) {
    int size = 0, target = 0;
    printf("Enter the size of array: ");
    scanf("%d", &size);
    int *addr = (int*)malloc(size * sizeof(int));
    printf("Enter the array: \n");
    for (int i = 0; i < size; i++) {
        scanf("%d", (addr + i));
    }
    printf("Enter the target: ");
    scanf("%d", &target);
    deleteElement(addr, &target, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", *(addr + i));
    }
    free(addr);
    return 0;
}
