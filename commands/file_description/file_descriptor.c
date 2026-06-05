#include <fcntl.h>
#include <stdio.h>  
#include <stdlib.h>

#include <sys/stat.h>
void getFileInfo(int * fd){

}
int main(int argc, char * argv[]){
    int val;
    if(argc!=2){
        fprintf(stderr, "Usage : %s <descriptor>\n",argv[0]);
        return 1;
    }
    if ((val=fcntl(atoi(argv[1]),F_GETFL,0))<0){
        fprintf(stderr, "fcntl error for file descriptor : %s\n",argv[1]);
    }
    switch(val & O_ACCMODE){

        case O_RDONLY:
        printf("Read Only");
        break;

        case O_WRONLY:
        printf("Write Only");
        break;

        case O_RDWR:
        printf("Read + Write");
        break;

        default:
        fprintf(stderr, "Unknown Access Mode");
    }
    if(val&O_APPEND){
        printf(", append\n");
    }
    if (val&O_NONBLOCK){
        printf(", nonblocking");
    }
    #if defined(O_SYNC)
        if(val& O_SYNC){
            printf(", synchronous writes");
        }
    #endif
    #if !defined(_POSIC_C_SOURCE) && defined(O_FSYNC)
        if (val&O_FSYNC){
            printf(", synchronous writes");
        }
    #endif
    putchar('\n');
    return 0;
}


