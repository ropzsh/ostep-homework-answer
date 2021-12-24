**1.只用两个工作和两个队列运行几个随机生成的问题。针对每个工作计算 MLFQ 的执**
**行记录。限制每项作业的长度并关闭 I/O,让你的生活更轻松。**

**执行代码**：

```shell
>$ ./mlfq.py -s 6 -j 2 -n 2 -m 9 -M 0
```

**运行结果**：

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime   7 - ioFreq   0
  Job  1: startTime   0 - runTime   4 - ioFreq   0

Compute the execution trace for the given workloads.
If you would like, also compute the response and turnaround
times for each of the jobs.

Use the -c flag to get the exact results when you are finished.

```

 **执行记录**：

```
[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 6 (of 7) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 5 (of 7) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 4 (of 7) ]
[ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 3 (of 7) ]
[ time 4 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 2 (of 7) ]
[ time 5 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 1 (of 7) ]
[ time 6 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 0 (of 7) ]
[ time 7 ] FINISHED JOB 0
[ time 7 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
[ time 8 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 2 (of 4) ]
[ time 9 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 1 (of 4) ]
[ time 10 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 0 (of 4) ]
[ time 11 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround   7
  Job  1: startTime   0 - response   7 - turnaround  11

  Avg  1: startTime n/a - response 3.50 - turnaround 9.00

```



**2.如何运行调度程序来重现本章中的每个实例?**

```sh
>$ ./mlfq.py -n 3 -l 0,100,0:50,10,0:0,50,10 -i 10 -c
```



**3.将如何配置调度程序参数,像轮转调度程序那样工作?**

只设置一个优先级，并且把I/O也关了

```sh
>$ ./mlfq.py -s 6 -n 1 -M 0 -c
```



**4.设计两个工作的负载和调度程序参数,以便一个工作利用较早的规则 4a 和 4b(用**
**-S 标志打开)来“愚弄”调度程序,在特定的时间间隔内获得 99%的 CPU。**

模拟程序默认每个队列的时间片都是10，在时间片用完之前进行I/O就能保持优先级，即 `I/O频率 < 时间片长度`

```sh
>$ ./mlfq.py -n 3 -l 0,50,9:0,50,0 -i 1 -S -c
```



**5.给定一个系统,其最高队列中的时间片长度为 10ms,你需要如何频繁地将工作推回**
**到最高优先级级别(带有-B 标志),以保证一个长时间运行(并可能饥饿)的工作得到至少**
**5%的 CPU?**

假设这5%就是一个时间片的时间，那么任务在200ms（20个时间片）内只“拿到”了一个时间片就是最少，那么 BOOST <= 190就行了，因为你至少得给任务一个时间片才是5%，是吧

**6.调度中有一个问题,即刚完成 I/O 的作业添加在队列的哪一端。-I 标志改变了这个**
**调度模拟器的这方面行为。尝试一些工作负载,看看你是否能看到这个标志的效果。**

```sh
>$ ./mlfq.py -n 1 -l 0,30,5:0,30,0:0,30,0 -i 3 -c
```

```
Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] JOB BEGINS by JOB 2
[ time 0 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 30) ]
[ time 1 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 30) ]
[ time 2 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 30) ]
[ time 3 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 30) ]
[ time 4 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 30) ]
[ time 5 ] IO_START by JOB 0
IO DONE
[ time 5 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 30) ]
[ time 6 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 30) ]
[ time 7 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 30) ]
[ time 8 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 30) ]
[ time 9 ] IO_DONE by JOB 0
[ time 9 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 30) ]
[ time 10 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 30) ]
[ time 11 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 30) ]
[ time 12 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 30) ]
[ time 13 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 30) ]
[ time 14 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 30) ]
[ time 15 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 30) ]
[ time 16 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 30) ]
[ time 17 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 30) ]
[ time 18 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 30) ]
[ time 19 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 30) ]
[ time 20 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 30) ]
[ time 21 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 30) ]
[ time 22 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 30) ]
[ time 23 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 30) ]
[ time 24 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 30) ]
[ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 30) ]
[ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 30) ]
[ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 30) ]
[ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 30) ]
[ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 30) ]
[ time 30 ] IO_START by JOB 0
IO DONE
[ time 30 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 30) ]
[ time 31 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 30) ]
[ time 32 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 30) ]
[ time 33 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 30) ]
[ time 34 ] IO_DONE by JOB 0
[ time 34 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 30) ]
[ time 35 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 30) ]
[ time 36 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 30) ]
[ time 37 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 30) ]
[ time 38 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 30) ]
[ time 39 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 30) ]
[ time 40 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 30) ]
[ time 41 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 30) ]
[ time 42 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 30) ]
[ time 43 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 30) ]
[ time 44 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 30) ]
[ time 45 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 30) ]
[ time 46 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 30) ]
[ time 47 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 30) ]
[ time 48 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 30) ]
[ time 49 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 30) ]
[ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 30) ]
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 30) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 30) ]
[ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 30) ]
[ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 30) ]
[ time 55 ] IO_START by JOB 0
IO DONE
[ time 55 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 30) ]
[ time 56 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 30) ]
[ time 57 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 30) ]
[ time 58 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 30) ]
[ time 59 ] IO_DONE by JOB 0
[ time 59 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 30) ]
[ time 60 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 30) ]
[ time 61 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 30) ]
[ time 62 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 30) ]
[ time 63 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 30) ]
[ time 64 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 30) ]
[ time 65 ] FINISHED JOB 1
[ time 65 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 30) ]
[ time 66 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 30) ]
[ time 67 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 30) ]
[ time 68 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 30) ]
[ time 69 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 30) ]
[ time 70 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 30) ]
[ time 71 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 30) ]
[ time 72 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 30) ]
[ time 73 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 30) ]
[ time 74 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 30) ]
[ time 75 ] FINISHED JOB 2
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 30) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 30) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 30) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 30) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 30) ]
[ time 80 ] IO_START by JOB 0
IO DONE
[ time 80 ] IDLE
[ time 81 ] IDLE
[ time 82 ] IDLE
[ time 83 ] IDLE
[ time 84 ] IO_DONE by JOB 0
[ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 9 (of 30) ]
[ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 8 (of 30) ]
[ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 7 (of 30) ]
[ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 6 (of 30) ]
[ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 5 (of 30) ]
[ time 89 ] IO_START by JOB 0
IO DONE
[ time 89 ] IDLE
[ time 90 ] IDLE
[ time 91 ] IDLE
[ time 92 ] IDLE
[ time 93 ] IO_DONE by JOB 0
[ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 30) ]
[ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 30) ]
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 30) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 30) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 30) ]
[ time 98 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  98
  Job  1: startTime   0 - response   5 - turnaround  65
  Job  2: startTime   0 - response  15 - turnaround  75

  Avg  2: startTime n/a - response 6.67 - turnaround 79.33

```



仅设置一个优先级，给第一个任务设置每5ms I/0一次，一次I/O持续3ms

从运行结果可以看到，Job 0 完成了I/O不会立刻接着执行这个任务，而是执行Job 2，所以不是放在首端，但又不像是放在尾端，而Job 0 放在了 Job 1之前，所以应该是在按最初的顺序`循环排队`着运行



