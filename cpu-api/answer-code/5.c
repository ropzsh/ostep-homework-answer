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
        int ret = wait(NULL);
        printf("hello, I am child (ret:%d) (pid:%d)\n", ret, (int) getpid());
    } else {
        int ret = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", pid, ret, (int) getpid());
    }

    return 0;
}   