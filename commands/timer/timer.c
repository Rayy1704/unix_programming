#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    if (argc<2){
        fprintf(stderr, "Usage: %s <program_name> [parameters]\n", argv[0]);
        return EXIT_FAILURE;
    }
    char * program_name = argv[1];
    char ** parameters = malloc(sizeof(char*)*(argc-1));
    for(int i=0;i<argc-1;i++){
        parameters[i]=argv[i+1];
    }
}