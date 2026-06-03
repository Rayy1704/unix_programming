#include <fcntl.h>
#include <stdio.h>  
#include <stdlib.h>

int main(int argc, char * argv[]){
    int val;
    if(argc!=2){
        fprintf(stderr, "Usage : %s <descriptor>\n",argv[0]);
        return 0;
    }
    if ((val=fcntl(atoi(argv[1]),F_GETFL,0))<0){
        fprintf(stderr, "fcntl error for file descriptor : %s\n",argv[1]);
    }
    switch(val & O_ACCMODE){

        case O_RDONLY:
        printf("Read Only\n");
        break;

        case O_WRONLY:
        printf("Write Only\n");
        break;

        case O_RDWR:
        printf("Read + Write");
        break;

        default:
        fprintf(stderr, "Unknown Access Mode");
    }
}


