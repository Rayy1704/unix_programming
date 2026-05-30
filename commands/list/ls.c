#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#define MAXLINE 4096
const char *red = "\033[0;31m";
const char *bold_green = "\033[1;32m";
const char *bold_red   = "\033[1;31m";
const char *highlight_green = "\033[42m";
const char * reset = "\033[0m";
void printEnt(struct dirent *dirp, struct stat st, int recursive){
    if(S_ISDIR(st.st_mode)){
        if(opendir(dirp->d_name) == NULL){
            printf("%s%s%s  ",highlight_green,dirp->d_name,reset);
        }else{
            printf("%s%s%s  ",bold_green,dirp->d_name,reset);
        }
        
    }else{
        printf("%s%s%s  ",bold_red,dirp->d_name,reset);
    }
    if(recursive == 1){
        printf("\n");
    }
}

void list( char* current_dir,int level,int recursive){
    DIR *dp;
    struct dirent *dirp;
    struct stat st;
    if((dp=opendir(current_dir))==NULL){
        fprintf(stderr,"Cannot open directory: %s\n",current_dir);
        return;
    }
    while((dirp=readdir(dp))!=NULL){
        char path[MAXLINE];
        snprintf(path,MAXLINE,"%s/%s",current_dir,dirp->d_name);
        if(lstat(path, &st) == 0 && strcmp(dirp->d_name,".") && strcmp(dirp->d_name,"..")){
            for(int i=0;i<level;i++){
                printf((i==level-1)?"|--":"|  ");
            }
            printEnt(dirp,st,recursive);
            if(S_ISDIR(st.st_mode) && recursive == 1){
                list(path,level+1,recursive);
            }
        }
    }
    closedir(dp);
}
int main(int argc, char* argv[]){
    if(argc==1){
        list(".",0,0);
    }else if(argc==2){
        list(argv[1],0,0);
    }else if (argc==3 && strcmp(argv[2],"-R")==0){
        list(argv[1],0,1);
    }else {
        printf("Usage: %s [directory] [-R]\n",argv[0]);
        return 1;
    }
    printf("\n");
    return 0;
}
