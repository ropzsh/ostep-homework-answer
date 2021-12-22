**1.编写一个调用 fork()的程序。在调用之前,让主进程访问一个变量(例如 x)并将其值设置为某个值(例如 100)。子进程中的变量有什么值?当子进程和父进程都改变 x 的值时,变量会发生什么?**

**代码**：

```C
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

```

**运行结果**：

```
parent: change before x= 100
parent: change later x= 888
chlid: change before x= 100
child: change later x= 999
```

子进程相当于复制了一份父进程，它拥有自己的地址空间（即拥有自己的私有内存）、寄存器、程序计数器等，两个进程中的变量修改互不影响



**2.编写一个打开文件的程序(使用 open 系统调用),然后调用 fork 创建一个新进程。子进程和父进程都可以访问 open()返回的文件描述符吗?当它们并发(即同时)写入文件时,会发生什么?**

**代码：**

```C
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
```

**运行结果**：

```
parent process write file successed
child process write file successed
```

子进程和父进程都可以访问 open()返回的文件描述符，并发写入时他们之间存在竞态，但最后都能写入成功



**3.使用 fork()编写另一个程序。子进程应打印“hello”,父进程应打印“goodbye”你应该尝试确保子进程始终先打印。你能否不在父进程调用 wait()而做到这一点呢?**

**代码**：

```C
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
```

**运行结果**：

```
hellogoodbye
```



**4.编写一个调用 fork() 的程序, 然后调用某种形式的 exec()来运行程序"/bin/ls"看看是否可以尝试 exec 的所有变体,包括 execl()、 execle()、 execlp()、 execv()、 execvp()和 execve(),为什么同样的基本调用会有这么多变种？**

**代码**：

```C
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
```

| 位数  | 含义                                                   |
| ----- | ------------------------------------------------------ |
| 前4位 | 统一为 exec 开头                                       |
| 第5位 | l: 参数传递为逐个列举方式  v: 参数传递为字符串数组方式 |
| 第6位 | e: 可传递新进程环境变量  p: 可执行文件查找方式为文件名 |



**5.现在编写一个程序，在父进程中使用 wait(),等待子进程完成。wait()返回什么？如果你在子进程中使用 wait()会发生什么？**

**代码**：

```C
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
```

**运行结果**：

```
hello, I am child (ret:-1) (pid:23340)
hello, I am parent of 23340 (wc:23340) (pid:23334)
```

wait()调用成功返回子进程号，失败返回-1
子进程调用wait()失败，返回-1



**6.对前一个程序稍作修改，这次使用 waitpid()而不是 wait().什么时候 waitpid()会有用？**

**代码**：

```C
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
```

**运行结果**：

```
hello, I am child (ret:23979) (pid:0hello, I am child (ret:23979) (pid:0)
hello, I am parent of 23979 (wc:23979) (pid:23973)
```

waitpid提供更多功能



**7.编写一个创建子进程的程序，然后在子进程中关闭标准输出（STDOUT_FILENO).如果子进程在关闭描述符后调用 printf 打印输出，会发生什么？**

**代码**：

```C
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
```

**运行结果**：

```
I'm parent process. I print after the subprocess ends
```

子进程关闭标准输出后，printf无法打印输出在控制台，而父进程不受影响，可以正常打印



**8.编写一个程序，创建两个子进程，并使用 pipe()系统调用，将一个子进程的标准输出连接到另一个子进程的标准输入。**

**代码**：

```C
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
```

**运行结果**：

```
I am pid1, I say "hello world" to pid2.
I am pid2, pid1 say: Hello world!
I am parent, all child processes have finished running
```
