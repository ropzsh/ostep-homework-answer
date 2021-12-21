习题源代码及README：https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-intro

**1.用以下标志运行程序: ./process-run.py -l 5:100,5:100 。CPU 利用率(CPU 使用时间**
**的百分比)应该是多少?为什么你知道这一点?利用 -c 标记查看你的答案是否正确。**

**运行结果：**

```html
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Process 1
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)

```

**加入参数 -c ：**

```html
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          1
  5        RUN:cpu         READY             1          
  6           DONE       RUN:cpu             1          
  7           DONE       RUN:cpu             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          
```

**答案：**

CPU 利用率为 100%，因为没有执行I/O指令，进程就不会阻塞，两个进程只在运行态和就绪态之间切换，CPU始终处于在繁忙状态



**2.现在用这些标志运行: ./process-run.py -l 4:100,1:0 。这些标志指定了一个包含 4 条指**
**令的进程(都要使用 CPU),并且只是简单地发出 I/O 并等待它完成。完成这两个进程需要**
**多长时间?利用-c 检查你的答案是否正确。**

**运行结果：**

```html
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu

Process 1
  io
  io_done

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

**加入参数 -c：**

```html
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          
  5           DONE        RUN:io             1          
  6           DONE       WAITING                           1
  7           DONE       WAITING                           1
  8           DONE       WAITING                           1
  9           DONE       WAITING                           1
 10           DONE       WAITING                           1
 11*          DONE   RUN:io_done             1          
```

**答案：**

需要11个时钟周期（Time）



**3.现在交换进程的顺序: ./process-run.py -l 1:0,4:100 。现在发生了什么?交换顺序是否**
**重要?为什么?同样,用-c 看看你的答案是否正确。**

**运行结果：**

```Produce a trace of what would happen when you run these processes: 
Process 0 
  io 
  io_done 
 
Process 1 
  cpu 
  cpu 
  cpu 
  cpu 
 
Important behaviors: 
  System will switch when the current process is FINISHED or ISSUES AN IO 
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

**加入参数-c：**

```
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        WAITING       RUN:cpu             1             1
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7*   RUN:io_done          DONE             1          

```

**答案：**

两个进程总的完成时间缩短至7个时钟周期，交换顺序很重要，因为当进程0进入阻塞态，CPU便可切换到进程1运行，当进程1完成，如果进程0就绪，就可以切换到进程0再次运行，提高了CPU利用率。



**4.现在探索另一些标志。一个重要的标志是-S,它决定了当进程发出 I/O 时系统如何**
**反应。将标志设置为 SWITCH_ON_END,在进程进行 I/O 操作时,系统将不会切换到另一**
**个进程,而是等待进程完成。当你运行以下两个进程时,会发生什么情况?一个执行 I/O,**
**另一个执行 CPU 工作。(-l 1:0,4:100 -c -S SWITCH_ON_END)**

**运行结果：**

```
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        WAITING         READY                           1
  3        WAITING         READY                           1
  4        WAITING         READY                           1
  5        WAITING         READY                           1
  6        WAITING         READY                           1
  7*   RUN:io_done         READY             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          
 11           DONE       RUN:cpu             1          
```

**答案：**运行进程0时，CPU不会切换到处于就绪态的进程1，而是会一直阻塞到进程0的I/O结束才切换到进程1。



**5.现在,运行相同的进程,但切换行为设置,在等待 I/O 时切换到另一个进程(-l 1:0,4:100**
**-c -S SWITCH_ON_IO)。现在会发生什么?利用-c 来确认你的答案是否正确。**

**运行结果：**

```
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        WAITING       RUN:cpu             1             1
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7*   RUN:io_done          DONE             1          

```

**答案：**

进程0阻塞时，CPU会切换到进程1运行



**6.另一个重要的行为是 I/O 完成时要做什么。利用-I IO_RUN_LATER,当 I/O 完成时,**
**发出它的进程不一定马上运行。相反,当时运行的进程一直运行。当你运行这个进程组合**
**时会发生什么?(./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_**
**LATER -c -p)系统资源是否被有效利用?**

**运行结果：**

```
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1          
  8          READY          DONE       RUN:cpu         READY             1          
  9          READY          DONE       RUN:cpu         READY             1          
 10          READY          DONE       RUN:cpu         READY             1          
 11          READY          DONE       RUN:cpu         READY             1          
 12          READY          DONE          DONE       RUN:cpu             1          
 13          READY          DONE          DONE       RUN:cpu             1          
 14          READY          DONE          DONE       RUN:cpu             1          
 15          READY          DONE          DONE       RUN:cpu             1          
 16          READY          DONE          DONE       RUN:cpu             1          
 17    RUN:io_done          DONE          DONE          DONE             1          
 18         RUN:io          DONE          DONE          DONE             1          
 19        WAITING          DONE          DONE          DONE                           1
 20        WAITING          DONE          DONE          DONE                           1
 21        WAITING          DONE          DONE          DONE                           1
 22        WAITING          DONE          DONE          DONE                           1
 23        WAITING          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1          
 25         RUN:io          DONE          DONE          DONE             1          
 26        WAITING          DONE          DONE          DONE                           1
 27        WAITING          DONE          DONE          DONE                           1
 28        WAITING          DONE          DONE          DONE                           1
 29        WAITING          DONE          DONE          DONE                           1
 30        WAITING          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)
```

**答案：**

系统资源没有被有效利用，Time19-23、26-30时，CPU处于空闲状态



**7.现在运行相同的进程,但使用-I IO_RUN_IMMEDIATE 设置,该设置立即运行发出**
**I/O 的进程。这种行为有何不同?为什么运行一个刚刚完成 I/O 的进程会是一个好主意?**

**运行结果：**

```
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1          
  8         RUN:io          DONE         READY         READY             1          
  9        WAITING          DONE       RUN:cpu         READY             1             1
 10        WAITING          DONE       RUN:cpu         READY             1             1
 11        WAITING          DONE       RUN:cpu         READY             1             1
 12        WAITING          DONE       RUN:cpu         READY             1             1
 13        WAITING          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1          
 15         RUN:io          DONE          DONE         READY             1          
 16        WAITING          DONE          DONE       RUN:cpu             1             1
 17        WAITING          DONE          DONE       RUN:cpu             1             1
 18        WAITING          DONE          DONE       RUN:cpu             1             1
 19        WAITING          DONE          DONE       RUN:cpu             1             1
 20        WAITING          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)
```

**答案：**

CPU利用率到达100%，立即运行一个刚刚完成 I/O 的进程，当这个进程想再次调用I/O请求时，该进程可以让出CPU给其他进程。



**8.现在运行一些随机生成的进程,例如 -s 1 -l 3:50,3:50, -s 2 -l 3:50,3:50, -s 3 -l 3:50,3:50。**
**看看你是否能预测追踪记录会如何变化?当你使用-I IO_RUN_IMMEDIATE 与-I IO_RUN_**
**LATER 时会发生什么?当你使用-S SWITCH_ON_IO 与-S SWITCH_ON_END 时会发生什么?**

**运行结果：**

```
>$ ./process-run.py -s 1 -l 3:50,3:50 -c
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7        WAITING          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        WAITING          DONE                           1
 11        WAITING          DONE                           1
 12        WAITING          DONE                           1
 13        WAITING          DONE                           1
 14        WAITING          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)
```

```
>$ ./process-run.py -s 1 -l 3:50,3:50  -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7        WAITING          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        WAITING          DONE                           1
 11        WAITING          DONE                           1
 12        WAITING          DONE                           1
 13        WAITING          DONE                           1
 14        WAITING          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)
```

```
>$ ./process-run.py -s 1 -l 3:50,3:50  -I IO_RUN_IMMEDIATE -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        WAITING         READY                           1
  4        WAITING         READY                           1
  5        WAITING         READY                           1
  6        WAITING         READY                           1
  7        WAITING         READY                           1
  8*   RUN:io_done         READY             1          
  9         RUN:io         READY             1          
 10        WAITING         READY                           1
 11        WAITING         READY                           1
 12        WAITING         READY                           1
 13        WAITING         READY                           1
 14        WAITING         READY                           1
 15*   RUN:io_done         READY             1          
 16           DONE       RUN:cpu             1          
 17           DONE       RUN:cpu             1          
 18           DONE       RUN:cpu             1          

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)
```

这题可以根据自己的需要自行组合或设计参数