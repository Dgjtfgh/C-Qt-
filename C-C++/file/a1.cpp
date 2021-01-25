#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>   
#include <string.h>

int main(int argc,char *argv[])
{
    printf("%d\n", argc);
    DIR * dp;
    struct dirent *filename;
    char path[1024];

    if (argc == 2)
    {
        strcpy(path, argv[1]);
    } else {
        strcpy(path, "/home");
    }
    int len = strlen(path);
    dp = opendir(path);
    if (!dp)
    {
        fprintf(stderr,"open directory error\n");
        return 0;
    }
    while (filename = readdir(dp))
    {
        struct stat buf;
        if((strcmp(filename->d_name,".")==0)||(strcmp(filename->d_name,"..")==0)) continue;
        sprintf(path+len, "/%s", filename->d_name);
        printf("filename:%-10s\td_info:%ld\t d_reclen:%us\n",
        filename->d_name,filename->d_ino,filename->d_reclen);
    }
    closedir(dp);
    return 0;
}