/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_string(const char* input, char delimiter, int* substring_count) {
    int input_length = strlen(input);
    int i, j, count = 0;
    char** substrings = NULL;
    for (i = 0; i < input_length; i++) {
        if (input[i] == delimiter) {
            count++;
        }
    }
    count++; 
    substrings = (char**)malloc(count * sizeof(char*));
    if (substrings == NULL) {
        *substring_count = 0;
        return NULL;
    }
    j = 0;
    for (i = 0; i < count; i++) {
        int substring_length = 0;
        while (input[j] != delimiter && input[j] != '\0') {
            substring_length++;
            j++;
        }
        substrings[i] = (char*)malloc((substring_length + 1) * sizeof(char));
        if (substrings[i] == NULL) {
            for (i = 0; i < count; i++) {
                free(substrings[i]);
            }
            free(substrings);
            *substring_count = 0;
            return NULL;
        }
        strncpy(substrings[i], input + j - substring_length, substring_length);
        substrings[i][substring_length] = '\0';
        j++;
    }

    *substring_count = count;
    return substrings;
}

void free_substrings(char** substrings, int count) {
    for (int i = 0; i < count; i++) {
        free(substrings[i]);
    }
    free(substrings);
}

int main() {
    char input[100];
    char delimiter;
    int substring_count;
    char** substrings;

    printf("Enter the input string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 

    printf("Enter the delimiter character: ");
    scanf(" %c", &delimiter);

    substrings = split_string(input, delimiter, &substring_count);

    printf("Output array:\n");
    for (int i = 0; i < substring_count; i++) {
        printf("%s\n", substrings[i]);
    }

    free_substrings(substrings, substring_count);

    return 0;
}

