/*
    @author recovxy
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int agrc, char* argv[]) {
    int pid = fork();

    if (pid < 0){
        fprintf(stderr, "fork failed\n");
        _exit(0);
    } else if (pid == 0) {
        close(STDOUT_FILENO);
        printf("I'm child process. I closed the STDOUT_FILENO");
    } else {
        int res = wait(NULL);
        printf("I'm parent process. I print after the subprocess ends");
    }

    return 0;
}    