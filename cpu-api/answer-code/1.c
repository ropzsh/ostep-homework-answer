/*
    @author recovxy
*/
#include <stdio.h>
#include <unistd.h>

int main(int agrc, char* argv[])
{   
    int x = 100;
    int pid =  fork();
    if (pid < 0) {  // fork failed, exit
        fprintf(stderr, "fork failed\n");
        _exit(1);
    }else if(pid == 0) {
        printf("chlid: change before x= %d\n", x);
        x = 999; //change x 
        printf("child: change later x= %d\n", x);
    }else {
        printf("parent: change before x= %d\n", x);
        x = 888; //change x 
        printf("parent: change later x= %d\n", x);
    }
    return 0;
}

