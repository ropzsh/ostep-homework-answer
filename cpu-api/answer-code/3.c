/*
    @author recovxy
*/
#include <stdio.h>
#include <unistd.h>

int main(int agrc, char* argv[]) {
    int pid = vfork(); //vfork创建的子进程与父进程共享数据段,而且由vfork()创建的子进程将先于父进程运行

    if (pid < 0){
        fprintf(stderr, "fork failed\n");
        _exit(0);
    } else if (pid == 0) {
        printf("hello");
    } else {
        //sleep(1);    // or let the parent process sleep first
        printf ("goodbye");
    }


    return 0;
}