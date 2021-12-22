**1.使用 SJF 和 FIFO 调度程序运行长度为 200 的 3 个作业时,计算响应时间和周转时间。**
$$
T 响应时间= T 首次运行−T 到达时间
$$
$$
T 周转时间= T 完成时间−T 到达时间
$$

|  Job ID  | SJF 响应时间 | SJF 周转时间 | FIFO 响应时间 | FIFO 周转时间 |
| :------: | ------------ | ------------ | ------------- | ------------- |
|  Job 0   | 0            | 200          | 0             | 200           |
|  Job 1   | 200          | 400          | 200           | 400           |
|  Job 2   | 400          | 600          | 400           | 600           |
| 平均时间 | 200          | 400          | 200           | 400           |



**2.现在做同样的事情,但有不同长度的作业,即 100、200 和 300。**

|  Job ID  | SJF 响应时间 | SJF 周转时间 | FIFO 响应时间 | FIFO 周转时间 |
| :------: | ------------ | ------------ | ------------- | ------------- |
|  Job 0   | 0            | 100          | 0             | 100           |
|  Job 1   | 200          | 300          | 100           | 300           |
|  Job 2   | 300          | 600          | 300           | 600           |
| 平均时间 | 133.33       | 333.33       | 133.33        | 333.33        |



**3.现在做同样的事情,但采用 RR 调度程序,时间片为 1。**
```shell
./scheduler.py -p RR -l 200,200,200 -q 1 -c
```

|  Job ID  | RR 响应时间 | RR 周转时间 |
| :------: | ----------- | ----------- |
|  Job 0   | 0           | 598         |
|  Job 1   | 1           | 599         |
|  Job 2   | 2           | 600         |
| 平均时间 | 1           | 599         |


```shell
./scheduler.py -p RR -l 100,200,300 -q 1 -c
```

|  Job ID  | RR 响应时间 | RR 周转时间 |
| :------: | ----------- | ----------- |
|  Job 0   | 0           | 298         |
|  Job 1   | 1           | 499         |
|  Job 2   | 2           | 600         |
| 平均时间 | 1           | 465.67      |



**4.对于什么类型的工作负载,SJF 提供与 FIFO 相同的周转时间?**

运行长度相同的工作负载



**5.对于什么类型的工作负载和量子长度, SJF 与 RR 提供相同的响应时间?**

量子长度应该是指时间片，如果每个任务需要的时长相同，且等于时间片时长的，则SJF和RR的响应时间相同



**6.随着工作长度的增加,SJF 的响应时间会怎样?你能使用模拟程序来展示趋势吗?**

相当于是按运行时间从小到大排队了，前面排的越多，越后面的响应时间自然就越长

运行如下代码我们来观察SJF的响应时间：

```shell
./scheduler.py -p SJF -j 1,2,3,4,5,6,7,8,9 -c -s 1
```

**运行结果**：

```
ARG policy SJF
ARG jlist 1,2,3,4,5,6,7,8,9

Here is the job list, with the run time of each job: 
  Job 0 ( length = 1.0 )
  Job 1 ( length = 2.0 )
  Job 2 ( length = 3.0 )
  Job 3 ( length = 4.0 )
  Job 4 ( length = 5.0 )
  Job 5 ( length = 6.0 )
  Job 6 ( length = 7.0 )
  Job 7 ( length = 8.0 )
  Job 8 ( length = 9.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 1.00 secs ( DONE at 1.00 )
  [ time   1 ] Run job 1 for 2.00 secs ( DONE at 3.00 )
  [ time   3 ] Run job 2 for 3.00 secs ( DONE at 6.00 )
  [ time   6 ] Run job 3 for 4.00 secs ( DONE at 10.00 )
  [ time  10 ] Run job 4 for 5.00 secs ( DONE at 15.00 )
  [ time  15 ] Run job 5 for 6.00 secs ( DONE at 21.00 )
  [ time  21 ] Run job 6 for 7.00 secs ( DONE at 28.00 )
  [ time  28 ] Run job 7 for 8.00 secs ( DONE at 36.00 )
  [ time  36 ] Run job 8 for 9.00 secs ( DONE at 45.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 1.00  Wait 0.00
  Job   1 -- Response: 1.00  Turnaround 3.00  Wait 1.00
  Job   2 -- Response: 3.00  Turnaround 6.00  Wait 3.00
  Job   3 -- Response: 6.00  Turnaround 10.00  Wait 6.00
  Job   4 -- Response: 10.00  Turnaround 15.00  Wait 10.00
  Job   5 -- Response: 15.00  Turnaround 21.00  Wait 15.00
  Job   6 -- Response: 21.00  Turnaround 28.00  Wait 21.00
  Job   7 -- Response: 28.00  Turnaround 36.00  Wait 28.00
  Job   8 -- Response: 36.00  Turnaround 45.00  Wait 36.00
```

从运行结果的 Final statistics 中我们能明显感知SJF的响应时间会快速增长，且运行时间越长的任务排在越后面，响应时间越久



**7.随着量子长度的增加,RR 的响应时间会怎样?你能写出一个方程,计算给定 N 个**
**工作时,最坏情况的响应时间吗?**

量子长度是指时间片长度，吐槽一下这译者到底懂不懂OS

最坏的响应时间  =  (N - 1)  * 时间片长度
