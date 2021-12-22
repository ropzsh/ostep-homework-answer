 

# 作业描述

​		在这个作业中,你将测量系统调用和上下文切换的成本。测量系统调用的成本相对容
易。例如,你可以重复调用一个简单的系统调用(例如,执行 0 字节读取)并记下所花的
时间。将时间除以迭代次数,就可以估计系统调用的成本。

​		你必须考虑的一件事是时钟的精确性和准确性。你可以使用的典型时钟是 gettimeofday()。
详细信息请阅读手册页。你会看到,gettimeofday()返回自 1970 年以来的微秒时间。然而,
这并不意味着时钟精确到微秒。测量 gettimeofday()的连续调用,以了解时钟的精确度。这
会告诉你为了获得一个好的测量结果,需要让空系统调用测试的迭代运行多少次。如果
gettimeofday()对你来说不够精确,可以考虑利用 x86 机器提供的 rdtsc 指令。

​		测量上下文切换的成本有点棘手。lmbench 基准测试的实现方法,是在单个 CPU 上运
行两个进程并在它们之间设置两个 UNIX 管道。管道只是 UNIX 系统中的进程可以相互通
信的许多方式之一。第一个进程向第一个管道写入数据,然后等待第二个数据的读取。由
于看到第一个进程等待从第二个管道读取的内容,OS 将第一个进程置于阻塞状态,并切换
到另一个进程,该进程从第一个管道读取数据,然后写入第二个管理。当第二个进程再次
尝试从第一个管道读取时,它会阻塞,从而继续进行通信的往返循环。通过反复测量这种
通信的成本,lmbench 可以很好地估计上下文切换的成本。你可以尝试使用管道或其他通信
机制(例如 UNIX 套接字),重新创建类似的东西。

​		在具有多个 CPU 的系统中,测量上下文切换成本有一点困难。在这样的系统上,你需
要确保你的上下文切换进程处于同一个处理器上。幸运的是,大多数操作系统都会提供系
统调用,让一个进程绑定到特定的处理器。例如,在 Linux 上,sched_setaffinity()调用就是
你要查找的内容。通过确保两个进程位于同一个处理器上,你就能确保在测量操作系统停
止一个进程并在同一个 CPU 上恢复另一个进程的成本。



**代码**：

```C
// test-syscall-cost.c
/*
    @author recovxy
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define N 100000 // N表示系统调用的次数

int main() {

    struct timeval time_start;
    struct timeval time_end;
    gettimeofday(&time_start, NULL);

    for(int i=0; i < N; i++){
        read(0, NULL, 0); //执行 0 字节读取
    }

    gettimeofday(&time_end, NULL);


    printf("一次系统调用的执行时间：%f微秒", 
            (float) ((time_end.tv_sec - time_start.tv_sec )* 10e+6 + ( time_end.tv_usec - time_start.tv_usec )) / N);

    return 0;
}
```

**运行结果**：

```
一次系统调用的执行时间：0.433880微秒
```



```C
// test-context-switching-cost.c
/*
    @author recovxy
*/
#define _GNU_SOURCE //sched_setaffinity
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>  
#include <sys/types.h>  

#define N 10000 // N表示读写数据的次数

int main() {
    int fd1[2]={0, 0}; //管道1
    int fd2[2]={0, 0}; //管道2
    int fd3[2]={0, 0}; //传递时间，time_start, time_end
    int pid;
    char s = 's'; //用来在进程间传递
    struct timeval time_start, time_end;
    struct sched_param param = {sched_get_priority_min(SCHED_FIFO)};

    cpu_set_t set;
    CPU_SET(0, &set);     // 将cpu 0 添加到集合

    if ( pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fd3) < 0) { // 这里如果改成按位与“|”，竟然会影响上下文切换时间，值得思考
        perror("pipe");
        exit(1);
    }
    
    if ((pid = fork()) < 0) {
        printf("fork error");
        exit(1);
    }else if(pid == 0) {
        if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) { //进程调度指定为先来先服务
            printf("程序运行需要root权限(sched_setscheduler系统调用)\n");
            perror("sched_setscheduler");
            exit(EXIT_FAILURE);
        }

        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) { // 线程绑定核心
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        gettimeofday(&time_start, NULL);
        
        for (int i = 0; i < N; i++) { 
            write(fd1[1], &s, 1);
            read(fd2[0], NULL, 1);   //直接丢弃数据
        }
        write(fd3[1], &time_start, sizeof(time_start));
        exit(0); 
    }else {
         if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) {
            printf("程序运行需要root权限(sched_setscheduler系统调用)\n");
            perror("sched_setscheduler");
            exit(EXIT_FAILURE);
        }

        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < N; i++) {    
            read(fd1[0], NULL, 1);   //直接丢弃数据 
            write(fd2[1], &s, 1);  
        }
        gettimeofday(&time_end, NULL);
        read(fd3[0], &time_start, sizeof(time_start));
        printf("一次上下文切换的花费时间：%f微秒", 
            (float)( ( time_end.tv_sec - time_start.tv_sec )* 10e+6 + ( time_end.tv_usec - time_start.tv_usec ) ) / N);
    }
    
    return 0;
}
```

**运行结果**：

```
一次上下文切换的花费时间：1.779200微秒
```

