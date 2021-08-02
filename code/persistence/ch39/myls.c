#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define STRINGSIZE 1024
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void print_file(struct stat s){
    printf("%ld     ", (long) s.st_ino);
    printf("%4lo    ", (unsigned long)s.st_mode);
    printf("%3lo    ", (long) s.st_nlink);
    printf("%3ld    %3ld    ", (long)s.st_uid, (long)s.st_gid);
    printf("%4lld   ", (long long)s.st_size);
    char timeString[STRINGSIZE] = "";
    strftime(timeString, STRINGSIZE, "%b %d %H:%M", localtime(&s.st_mtime));
    printf("%s  ", timeString);
}
int main(int argc, char** argv){
    struct stat s;
    int opt;
    char* pathname = ".";
    bool list = false;
    DIR *dp;
    opterr = 0;

    while((opt = getopt(argc, argv, "l:"))!=-1){
        switch(opt) {
            case 'l':
                pathname = optarg;
                list = true;
                break;
            case '?':
                if(optopt == 'l')
                    list = true;
                break;
            default:
                break;
        }
    }

    if(!list && argc > 1)
        pathname = argv[1];
    
    if(stat(pathname, &s) == -1)
        handle_error("stat");
    
    if(S_ISDIR(s.st_mode)){
        if((dp = opendir(pathname)) == NULL)
            handle_error("opendir");
        struct dirent *d;//One entry
        while((d = readdir(dp)) != NULL) {//traverse every entry
            if(list) {
                char filePath[STRINGSIZE] = "";
                strncpy(filePath, pathname, strlen(pathname));
                strncat(filePath, "/", 1);
                strncat(filePath, d->d_name, strlen(d->d_name));
                if(stat(filePath, &s) == -1)//Now previou s is now useless.  
                    handle_error("stat");
                print_file(s);
            }
            printf("%s\n", d->d_name);
        } 
        closedir(dp);
    } else {//In case we provide a regular file
        if(list)
            print_file(s);
        printf("%s\n", pathname);
    }

    exit(EXIT_SUCCESS);
}