/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

#define max_num_users 1000 
#define max_length    100  

void read_backup_file(char** stored_data, int num_users, char backup_file_name[]) {
    FILE *filepointer = fopen(backup_file_name, "r");

    if (filepointer == NULL) {
        printf("Unable to open the backup file!\n");
        return;
    }

    num_users = 0;

    char character;
    int length = 0;

    while ((character = fgetc(filepointer)) != EOF) {
        if (character == '\n') {
            num_users++;
            length = 0;
        }
        else {
            stored_data[num_users][length++] = character;
        }
    }    

    fclose(filepointer);
    printf("\nNumber of users restored from backup file: %d\n\n", num_users);
}

void show_users(char** stored_data, int num_users) {
    printf("\nList of all users:\n");
    for (int i = 0; i < num_users; i++) {
        bool flag = 1;

        for (int j = 0; j < max_length; j++) {
            char character = stored_data[i][j];

            if (character == ' ') {
                break;
            }
            else if (character == '_') {
                character = ' ';
                flag = 1;
            }
            else {
                if (flag) {
                    if (character >= 'a') {
                        character += 'A' - 'a';
                    }
                    flag = 0;
                }
                else {
                    if (character < 'a') {
                        character += 'a' - 'A';
                    }
                }
            }

            printf("%c", character);
        }
        printf("\n");
    }
    printf("\n");
}

void new_user(char** stored_data, int num_users, char *new_user_info) {
    int username_length;
    for (int i = 0; i < max_length; i++) {
        if (new_user_info[i] == ' ') {
            username_length = i - 1;
            break;
        }
    }

    for (int i = 0; i < num_users; i++) {
        if (strncmp(stored_data[i], new_user_info, username_length) == 0) {
            printf("Username already exists!\n");
            return;
        }
    }

    strcpy(stored_data[num_users], new_user_info);
    num_users++;
    printf("New User Added!\n");
}

void delete_user(char** stored_data, int num_users, char *username) {
    int username_length;
    for (int i = 0; i < max_length; i++) {
        if (username[i] == '\0') {
            username_length = i - 1;
            break;
        }
    }

    for (int i = 0; i < num_users; i++) {
        if (strncmp(stored_data[i], username, username_length) == 0) {
            for (int j = i; j < num_users - 1; j++) {
                stored_data[j] = stored_data[j + 1];
            }
            
            num_users--;

            printf("User Deleted!\n");
            return;
        }
    }

    printf("Username does'nt exists!\n");
}

void end_program(char** stored_data, int num_users) {
    FILE *filepointer = fopen("new_datasets_file.txt", "w");

    if (filepointer == NULL) {
        printf("Unable to open a new file!\n");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(filepointer, "%s\n", stored_data[i]);
    }

    fclose(filepointer);
    printf("Datasets stored in a new file!\n");
}

void email_cnt(char** stored_data, int num_users) {
    char all_platforms[50][10];
    int counter[50] = {0};
    int num_platforms = 0;

    int i, j, k;
    for (i = 0; i < num_users; i++) {
        char platform[10];
    
        for (j = 0; j < max_length; j++) {
            if (stored_data[i][j] == '@') {
                for (k = 0; k < 10; k++) {
                    if (stored_data[i][j + k] == '.') {
                        strncpy(platform, stored_data[i] + j + 1, k - 1);
                        platform[k - 1] = '\0';
                        break;
                    }
                }
                break;
            }
        }

        bool exists = 0;
        for (j = 0; j < num_platforms; j++) {
            if (strcmp(all_platforms[j], platform) == 0) {
                exists = 1;
                counter[j]++;
                break;
            }
        }

        if (exists == 0) {
            strcpy(all_platforms[num_platforms], platform);
            counter[num_platforms] = 1;
            num_platforms++;
        }
    }

    for (i = num_users; i > 0; i--) {
        for (j = 0; j < num_platforms; j++) {
            if (counter[j] == i) {
                printf("%s %d\n", all_platforms[j], i);
            }
        }
    }
    printf("\n");
}

void wait_for_commands(char** stored_data, int num_users) {
    char command[110];
    while(1) {
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin);
        
        if (strlen(command) > 0 && command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            end_program(stored_data, num_users);
            return;
        }
        else if (strcmp(command, "showusers") == 0) {
            show_users(stored_data, num_users);
        }
        else if (strncmp(command, "newuser", 7) == 0) {
            new_user(stored_data, num_users, command + 8);
        }
        else if (strncmp(command, "deluser", 7) == 0) {
            delete_user(stored_data, num_users, command + 8);
        }
        else if (strcmp(command, "emailcnt") == 0) {
            email_cnt(stored_data, num_users);
        }
        else {
            printf("This is not a valid command!\n");
            printf("List of valid commands:  showusers  newuser  deluser  emailcnt  exit\n\n");            
        }
    }
}

int main() {
    char** stored_data = (char**)malloc(max_num_users * sizeof(char*));
    for (int i = 0; i < max_num_users; i++) {
        stored_data[i] = (char*)malloc(max_length * sizeof(char));
    }
    
    char backup_file_name[100] = "HW4_Datasets.txt";
  

    int num_users = 0;
    read_backup_file(stored_data, num_users, backup_file_name);
    
    wait_for_commands(stored_data, num_users);

    return 0;
}
