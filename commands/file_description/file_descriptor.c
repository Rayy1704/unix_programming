#include <fcntl.h>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>

#include <sys/stat.h>
void getFileInfo(char * fd){
    struct stat st;
    if(fstat(atoi(fd),&st)<0){
        fprintf(stderr, "fstat error for file descriptor : %s\n",fd);
        exit(1);
    }
    printf("Best I/O Block Size : %d\n",st.st_blksize);
    printf("File Size : %lld\n",st.st_size);
    printf("File Last Modified: %s", ctime(&(st.st_mtime)));

}
void getFileAccessMode(char * fd){
    int val;
    if ((val=fcntl(atoi(fd),F_GETFL,0))<0){
        fprintf(stderr, "fcntl error for file descriptor : %s\n",fd);
        exit(1);
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
}

void getFileType(char * fd){
    struct stat st;
    if(fstat(atoi(fd),&st)<0){
        fprintf(stderr, "fstat error for file descriptor : %s\n",fd);
        exit(1);
    }
    mode_t mode = st.st_mode;
    if(S_ISREG(mode)){
        printf("Regular File\n");
    }else if(S_ISDIR(mode)){
        printf("Directory File\n");
    }else if(S_ISCHR(mode)){
        printf("Character Special File\n");
    }else if(S_ISBLK(mode)){
        printf("Block Special File\n");
    }else if(S_ISFIFO(mode)){
        printf("PIPE/FIFO File\n");
    }else if(S_ISLNK(mode)){
        printf("Symbolic Link File\n");
    }else if(S_ISSOCK(mode)){
        printf("Socket File\n");
    }else if(S_TYPEISMQ(&st)){
        printf("Message Queue\n");
    }else if(S_TYPEISSEM(&st)){
        printf("Semaphore\n");
    }else if(S_TYPEISSHM(&st)){
        printf("Shared Memory Object\n");
    }
    else{
        fprintf(stderr, "Unknown File Type\n");
    }
}










int main(int argc, char * argv[]){

    if(argc!=2){ // handle parameters
        fprintf(stderr, "Usage : %s <descriptor>\n",argv[0]);
        return 1;
    }

    getFileAccessMode(argv[1]);    
    getFileInfo(argv[1]);
    getFileType(argv[1]);
    return 0;
}


