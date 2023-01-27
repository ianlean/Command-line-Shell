//***************************************************************************//**
////  @file (MyShell.c)
////  @author       Juhua Hu
//
//*******************************************************************************/

/**
DONOT change the existing function definitions. You can add functions, if necessary.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXSTR 255

/**
  @brief Fork a child to execute the command using execvp. The parent should wait for the child to terminate
  @param args Null terminated list of arguments (including program).
  @return returns 1, to continue execution and 0 to terminate the MyShell prompt.
 */

int execute(char **args) {
    if (args[0][0] == '\0') {return 1;}
    if (!strcmp(args[0], "exit" )) {return 0;}
    int rc = fork();
    if (rc == 0) {
        if(execvp(args[0], args) == -1) {
            printf("error executing command: No such file or directory\n");
            exit(-1);
        }
    } else if (rc < 0){
        printf("fork failed\n");
    } else {
        wait(NULL);
    }
    return 1;
}

void free_arr(char arr[], int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = '\0';
    }
}

void free_dyn_arr(char** array) {
    for (int i=0; i<strlen(array); i++) {
        if(array[i] != NULL) {
            free(array[i]);
        }
    }
    free(array);
}


/**
  @brief gets the input from the prompt and splits it into tokens. Prepares the arguments for execvp
  @return returns char** args to be used by execvp
 */
char** parse(void) {
    char **our_array = malloc(sizeof(char*) * MAXSTR);
    char s[MAXSTR];
    fgets(s,sizeof(s),stdin);
    char temp[MAXSTR];
    int j = 0;
    int i = 0;
    int temp_index = 0;
    int length = 0;
    while (1) {
        if (s[i] == ' ' || s[i] == '\n') {
            temp[length] = '\0';
            our_array[j] = malloc(length * sizeof(char));
            strcpy(*(our_array+j),temp);
            free_arr(temp, length);
            if (s[i] == '\n') break;
            temp_index = 0;
            j++;
        } else {
            temp[temp_index] = s[i];
            temp_index++;
            length++;
        }
        i++;
    }
    return our_array;
}


/**
   @brief Main function should run infinitely until terminated manually using CTRL+C or typing in the exit command
   It should call the parse() and execute() functions
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv) {
    int exit = 1;
    while(exit) {
        printf("MyShell> ");
        char** parsed_command = parse();
        exit = execute(parsed_command);
    }
    return EXIT_SUCCESS;
}