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