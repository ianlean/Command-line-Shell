//
// Created by Ian McLean on 1/24/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    char * myarg;
    printf("hello world \n");
    printf("number of args=%d \n",argc);
    char ** ourarray = malloc(sizeof(char *) * argc);
    int j=argc-1;
    for (int i=0;i<argc;i++) {
        char* s = malloc(sizeof(char) * strlen(argv[i]));
        s = strcpy(s,argv[i]);
        ourarray[j] = s;
        j--;
    }
    for (int i=0;i<argc;i++) {
        printf("ourarray arg %d=%s\n",i,ourarray[i]);
    }

    *(ourarray[0]+1)='b';
    for (int i=0;i<argc;i++)
        printf("ourarray[%d]=%s –- argv[%d]=%s\n",i,ourarray[i],i,argv[i]);

    return 0;
}
