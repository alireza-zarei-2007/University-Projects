/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 01 - Task A
 * Description: Write a program that accepts a positive integer from the user, calculates its reverse (reversing the digits), and prints the final reversed number.
 */

#include <stdio.h> 
int reverse(int n){ 
  int i=0; 
  while (n>0){ 
    i *= 10; 
    i += (n%10); 
    n /= 10; 
  } 
  return i; 
} 
int main(){ 
  int n; 
  scanf ("%d", &n); 
  printf ("%d", reverse(n)); 
  return 0; 
}


/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 01 - Task B
 * Description: Write a C function that receives a positive integer `n` as an input argument and
                checks whether it is a prime number. The function returns `1` if `n` is prime, and `0` otherwise.
 */

#include <stdio.h>
int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = n / 2; i > 1; i--) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", isPrime(n));
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 01 - Task C
 * Description: Given an integer array of length n and an integer k, write a C function checkMult(int arr[], int n, int k) that 
                returns 1 if there exist two elements in the array whose product equals k, otherwise returns 0.
 */

#include <stdio.h>
int checkMult(int Array[], int n, int k) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (Array[i] * Array[j] == k) {
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    int arr[20];
    int k = 0, n = 0;
    printf("Enter The numbers: ");
    scanf("%d %d", &k, &n);
    printf("Enter the values of Array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("return is: %d", checkMult(arr, n, k));
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 01 - Task D
 * Description: Given a 10x10 integer array representing grayscale pixel values (0-255), 
                write a C function that takes the 2D array and coordinates (i, j) and 
                returns the sum of the pixel at (i, j) and all its adjacent neighbors (up, down, left, right).
 */

#include <stdio.h>
#define NUM 10
int calculateBrightness(int image[10][10], int i, int j) {
    int sum = 0;
    for (int s = i - 2; s < i + 1; s++) {
        if ((s < 0) || (s > NUM - 1)) {
            continue;
        }
        for (int p = j - 2; p < j + 1; p++) {
            if ((p < 0) || (p > NUM - 1)) {
                continue;
            }
            sum += image[s][p];
        }
    }
    return sum;
}

int main(void) {
    int Arr[NUM][NUM];
    int num1, num2;
    printf("Enter 10x10 pixel values:\n");
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            scanf("%d", &Arr[i][j]);
        }
    }
    printf("Enter the pixel coordinates (i j): ");
    scanf("%d %d", &num1, &num2);
    printf("The result is: %d\n", calculateBrightness(Arr, num1, num2));
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 01 - Task E
 * Description: Given an integer array of length n, write a C function void shiftRight(int arr[], int n, int k) that 
                rotates the array to the right by k positions (k < n). Elements that fall off the right side should wrap around to the left side. 
                You may use a temporary array.
                Example: arr = [2,1,4,3,5], k = 3 → arr = [4,3,5,2,1]
 */

#include <stdio.h>
void shiftRight(int arr[], int n, int k) {
    int arr2[n];
    for (int i = 0; i < n; i++) {
        arr2[(i + k) % n] = arr[i];
    }
    for (int j = 0; j < n; j++) {
        printf("%d,", arr2[j]);
    }
}
int main(void) {
    int arr[50];
    int n = 0, k = 0;
    printf("Enter the n & k: ");
    scanf("%d %d", &n, &k);
    printf("Enter The Array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    shiftRight(arr, n, k);
    return 0;
}
