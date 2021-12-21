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
        printf("hello, I am child (ret:%d) (pid:%d)\n", (int) getpid());
    } else {
        int ret = waitpid(pid, NULL, 0); 
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", pid, ret, (int) getpid());
    }

    return 0;
}    