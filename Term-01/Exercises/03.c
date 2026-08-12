/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 03 - Task A
 * Description: Write a function filterNumericData that takes two filenames as arguments. It opens the first text file, extracts only numeric characters ('0'–'9'), 
                and writes them to the second file. All other characters (letters, spaces, symbols) are excluded.
                Requirements:
                Return 0 if both files open successfully and the operation completes without errors.       
                Return 1 if an error occurs while opening either file.
 */


#include <stdio.h>
#include <string.h>
int filterNumericData(char *inputFileName, char *outputFileName)
{
    FILE *input = fopen(inputFileName, "r");
    char NumberOfFile[100];
    int i = 0;
    if (input == NULL) {
        return 1;
    }
    while (!feof(input)) {
        char Input_char = getc(input);
        if ((Input_char >= 48) && (Input_char <= 57)) {
            NumberOfFile[i] = Input_char;
            i++;
        }
    }
    fclose(input);
    FILE *output = fopen(outputFileName, "wb");
    if (output == NULL) {
        return 1;
    }
    fwrite(NumberOfFile, sizeof(char), i, output);
    fclose(output);
    return 0;
}
int main()
{
    char inputFileName[50] = {"input.txt"};
    char outputFileName[50] = {"output.txt"};
    printf("%d", filterNumericData(inputFileName, outputFileName));
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 03 - Task B
 * Description: We have a file named students.txt that contains the names of students in a class. Each student's first and 
                last name (maximum 100 characters total) is written on a separate line.
                Complete the function below so that:
                It reads each line containing a student's first and last name from the file and prints it on the screen.
                It takes the student's attendance status (as an integer 0 or 1 from input, where 0 means absent and 1 means present) from the user.
                Finally, the function must write each student's first and last name along with their attendance status to a file named attendance_report.txt,
                as shown in the example below.
                Note: Some lines in students.txt may be empty and should be ignored during processing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void CheckAttendency(char *Name, char *outputFileName, int checkAttendency)
{
    FILE *output = fopen(outputFileName, "a");
    if (output == NULL) {
        printf("file Doesnt exist!!");
    }
    fprintf(output, "%s", Name);
    if (checkAttendency == 1) {
        fprintf(output, "%s", ": Present\n");
    } else if (checkAttendency == 0) {
        fprintf(output, "%s", ": Absent\n");
    }
    fclose(output);
}
int main()
{
    char inputFileName[50] = {"students.txt"};
    char outputFileName[50] = {"report_attendance.txt"};
    FILE *input = fopen(inputFileName, "rb");
    if (input == NULL) {
        printf("Erorr reading the file");
        return 0;
    }
    while (!feof(input)) {
        char Name[100] = "";
        int i = 0, checkAttendency = 0;
        char character = 0;
        while (1) {
            character = getc(input);
            if ((character == '\n') || (character == EOF)) {
                break;
            }
            Name[i] = character;
            i++;
        }
        if (character != EOF) {
            Name[i - 1] = 0;
        }
        if (Name[0] == 0) {
            continue;
        }
        printf("%s --> ", Name);
        scanf("%d", &checkAttendency);
        CheckAttendency(Name, outputFileName, checkAttendency);
    }
    fclose(input);
    return 0;
}

/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 03 - Task C
 * Description: The Selection Sort algorithm is one of the simple algorithms for sorting an array of numbers. 
                The algorithm works as follows: it traverses the array starting from the first element and finds the index of the smallest element 
                among indices 0 to n-1, then swaps the content of this element with the first element of the array using the found index. 
                For the second pass, it traverses from the second element and finds the index of the smallest element among indices 1 to n-1, 
                then swaps this element with the second element of the array. This process continues until the end of the array, 
                resulting in the entire array being sorted.
                Write the function in C language that takes an array arr and its size n and implements the above algorithm on it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void selectionSort(int *arr, int n)
{
    int temp = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = *(arr + i), index_min = i;
        for (int j = i + 1; j < n; j++) {
            if (*(arr + j) < min) {
                index_min = j;
                min = *(arr + j);
            }
        }
        temp = *(arr + i);
        *(arr + i) = min;
        *(arr + index_min) = temp;
    }
    for (int k = 0; k < n; k++) {
        printf("%d ", *(arr + k));
    }
}
int main()
{
    int lengthOfArray = 0;
    printf("Enter the size of array: ");
    scanf("%d", &lengthOfArray);
    int *arr = (int *)malloc(lengthOfArray * sizeof(int));
    printf("Enter the values of array (with space): \n");
    for (int i = 0; i < lengthOfArray; i++) {
        scanf("%d", (arr + i));
    }
    selectionSort(arr, lengthOfArray);
    free(arr);
    return 0;
}
