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
    char ** parameters = malloc(sizeof(char*)*(argc));
    for(int i=0;i<argc-1;i++){
        parameters[i]=argv[i+1];
    }
    parameters[argc-1]=NULL;
    pid_t pid;
    int status;
    clock_t start_time = clock();
    pid=fork();
    if(pid<0){
        fprintf(stderr, "Fork failed\n");
        return EXIT_FAILURE;
    }else if (pid==0){
        execvp(program_name,parameters);
        fprintf(stderr, "Exec Failed\n");
    }
    else{
        wait(&status);
        if(WIFEXITED(status)){
            fprintf(stderr, "Child Exited with status %d\n", WEXITSTATUS(status));
        }else{
            fprintf(stderr, "Child did not exit successfully\n");
        }
        clock_t end_time= clock();
        float time_taken = (float)(end_time-start_time)/CLOCKS_PER_SEC;
        fprintf(stdout,"Time Taken to run %s : %f\n", program_name, time_taken);
        return 0 ;
    }
}