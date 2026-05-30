#include <stdio.h>//has fprintf
#include <dirent.h> //has dirent
#include <sys/stat.h>// has stat
#include <stdlib.h>// has exit
#include <string.h> //has strcmp
char * found_path;
void find(char * dir, char * file){
    DIR *dp;
    struct dirent * dirp;
    struct stat st;
    if((dp=opendir(dir))==NULL){
        fprintf(stderr, "Cannot open directory: %s\n",dir);
        exit(1);
    }
    while((dirp=readdir(dp))!=NULL){
        if(strcmp(dirp->d_name, ".")&& strcmp(dirp->d_name, "..")){
            char path[4096];
            snprintf(path,4096,"%s/%s",dir,dirp->d_name);
            if(strcmp(dirp->d_name,file)==0){
                found_path = malloc(sizeof(path));
                strcpy(found_path,path);
                return;
            }else if(lstat(path,&st)==0&& S_ISDIR(st.st_mode)){
                find(path,file);
            }
        }
    }
    closedir(dp);
}
