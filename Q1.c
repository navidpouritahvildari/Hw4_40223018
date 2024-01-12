/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_and_manipulate(char* str1, char* str2) {
    int new_length = strlen(str1) + strlen(str2) + 2;
    char* new_str = (char*)malloc(new_length * sizeof(char));
     strcpy(new_str, str1);
    strcat(new_str, "_");
    strcat(new_str, str2);
    return new_str;
}

int main() {
    char str1[100];
    char str2[100];

    printf("Enter the first name: ");
    scanf("%s", str1);

    printf("Enter the last name: ");
    scanf("%s", str2);

    char* new_str = concatenate_and_manipulate(str1, str2);
    printf("New string: %s\n", new_str);
    free(new_str);

    return 0;
}