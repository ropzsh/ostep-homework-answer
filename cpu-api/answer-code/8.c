/*
    @author recovxy
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fd[2] = {0, 0};
	if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
	
	int pid1 = fork();
	if (pid1 < 0)
	{
		fprintf(stderr, "fork filed pid1\n");
	}
	else if (pid1 == 0)
	{
		close(fd[0]); //  pid1写数据到管道，关闭读端
		char *msg = "Hello world!\n";
		write(fd[1], msg, strlen(msg)); // 向管道写
		close(fd[1]); // 关闭写端
		printf("I am pid1, I say \"hello world\" to pid2.\n");
		return 0; // pid1运行完直接退出，否则pid1进程会运行 int pid2 = fork()
	}

	int pid2 = fork();
	if (pid2 < 0)
	{
		fprintf(stderr, "fork filed pid2\n");
	}
    else if (pid2 == 0)
	{
		waitpid(pid1, NULL, 0); // pid2等待pid1进程完成写操作
		close(fd[1]); // 关闭写端
		char buf[1024];
		int len = read(fd[0], buf, 1024); // 从管道中读数据
		if (len > 0)
		{
			buf[len] = '\0';
			printf("I am pid2, pid1 say: %s", buf);
		}
		return 0;
	}

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("I am parent, all child processes have finished running\n");
	return 0;
}
