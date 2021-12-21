/*
    @author recovxy
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int agrc, char* argv[])
{ 
    int fd  = open("2-file.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    if (fd == -1)  {    
        fprintf(stderr, "open file failed\n");
        _exit(0);
    }

    int pid = fork();
    if (pid < 0){
        fprintf(stderr, "fork failed\n");
        _exit(0);
    }else if (pid == 0) {
        char *buf = "I am child\n";
        int numWrite = write(fd, buf, strlen(buf));
        if (numWrite == -1) {
            fprintf(stderr, "child process write file failed\n");
            _exit(0);
        }else {
            printf("child process write file successed\n");
        }
    }else {
        char *buf = "I am parent\n";
        int numWrite = write(fd, buf, strlen(buf));
        if (numWrite == -1) {
            fprintf(stderr, "parent process write file failed\n");
            _exit(0);
        }else {
            printf("parent process write file successed\n");
        }
    }

    return 0;
}