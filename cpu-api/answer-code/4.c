/*
    @author recovxy
*/
#include <stdio.h>
#include <unistd.h>

int main(int agrc, char* argv[], char *envp[]) {
    char *cmd = "/bin/ls";
    char *arg[] = {"ls", "-a", NULL};

    int pid = fork();


    if (pid < 0){
        fprintf(stderr, "fork failed\n");
        _exit(0);
    } else if (pid == 0) {
        execl(cmd, "ls", NULL);
        execle(cmd, "ls", NULL, envp);
        execlp(cmd, "ls", NULL);
        execv(cmd, arg);
        execvp(cmd, arg);
        execve(cmd, arg, envp);
    } else {}

    return 0;
}