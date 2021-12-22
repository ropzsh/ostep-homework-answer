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
            (float)((time_end.tv_sec - time_start.tv_sec )* 10e+6 + ( time_end.tv_usec - time_start.tv_usec )) / N);

    return 0;
}
