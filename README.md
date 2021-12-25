## 完成情况

### Introduction

Chapter | What To Do
--------|-----------
[Introduction](http://www.cs.wisc.edu/~remzi/OSTEP/intro.pdf) &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; | No homework (yet)

### Virtualization  direct-execution

Chapter | What To Do| Answer 
--------|-----------|-----------
[Abstraction: Processes](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf) | :heavy_check_mark:Run [process-run.py](cpu-intro) | [answer.md](cpu-intro/answer.md) 
[Process API](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf) | :heavy_check_mark:Run [fork.py](cpu-api) and write some code](cpu-intro)](cpu-intro)](cpu-intro) | [answer.md](cpu-api/answer.md) 
[Direct Execution](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-mechanisms.pdf) | :heavy_check_mark:Write some code | [answer.md](direct-execution/answer.md) 
[Scheduling Basics](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-sched.pdf) | :heavy_check_mark:Run [scheduler.py](cpu-sched) |[answer.md](cpu-sched/answer.md)
[MLFQ Scheduling](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-sched-mlfq.pdf)	| :heavy_check_mark:Run [mlfq.py](cpu-sched-mlfq) |[answer.md](cpu-sched/answer.md)
[Lottery Scheduling](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-sched-lottery.pdf) | :heavy_check_mark:Run [lottery.py](cpu-sched-lottery) |[answer.md](cpu-sched-lottery/answer.md)
[Multiprocessor Scheduling](http://www.cs.wisc.edu/~remzi/OSTEP/cpu-sched-multi.pdf) | :x:Run [multi.py](cpu-sched-multi) |
[Abstraction: Address Spaces](http://www.cs.wisc.edu/~remzi/OSTEP/vm-intro.pdf) | :x:Write some code |
[VM API](http://www.cs.wisc.edu/~remzi/OSTEP/vm-api.pdf) | :x:Write some code |
[Relocation](http://www.cs.wisc.edu/~remzi/OSTEP/vm-mechanism.pdf) | :x:Run [relocation.py](vm-mechanism) |
[Segmentation](http://www.cs.wisc.edu/~remzi/OSTEP/vm-segmentation.pdf) | :x:Run [segmentation.py](vm-segmentation) |
[Free Space](http://www.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf) | :x:Run [malloc.py](vm-freespace) |
[Paging](http://www.cs.wisc.edu/~remzi/OSTEP/vm-paging.pdf) | :x:Run [paging-linear-translate.py](vm-paging) |
[TLBs](http://www.cs.wisc.edu/~remzi/OSTEP/vm-tlbs.pdf) | :x:Write some code |
[Multi-level Paging](http://www.cs.wisc.edu/~remzi/OSTEP/vm-smalltables.pdf) | :x:Run [paging-multilevel-translate.py](vm-smalltables) |
[Paging Mechanism](http://www.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys.pdf) | :x:Run [mem.c](vm-beyondphys) |
[Paging Policy](http://www.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys-policy.pdf) | :x:Run [paging-policy.py](vm-beyondphys-policy) |
[Complete VM](http://www.cs.wisc.edu/~remzi/OSTEP/vm-complete.pdf) | No homework (yet)|

### Concurrency

Chapter | What To Do| Answer 
--------|-----------|-----------
[Threads Intro](http://www.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf) | :x:Run [x86.py](threads-intro) |
[Thread API](http://www.cs.wisc.edu/~remzi/OSTEP/threads-api.pdf)	| :x:Run [some C code](threads-api) |
[Locks](http://www.cs.wisc.edu/~remzi/OSTEP/threads-locks.pdf)	| :x:Run [x86.py](threads-locks) |
[Lock Usage](http://www.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf) | :x:Write some code |
[Condition Variables](http://www.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf) | :x:Run [some C code](threads-cv) |
[Semaphores](http://www.cs.wisc.edu/~remzi/OSTEP/threads-sema.pdf) | :x:Read and write [some code](threads-sema) |
[Concurrency Bugs](http://www.cs.wisc.edu/~remzi/OSTEP/threads-bugs.pdf) | :x:Run [some C code](threads-bugs) |
[Event-based Concurrency](http://www.cs.wisc.edu/~remzi/OSTEP/threads-events.pdf) | :x:Write some code |

### Persistence

Chapter | What To Do| Answer 
--------|-----------|-----------
[I/O Devices](http://www.cs.wisc.edu/~remzi/OSTEP/file-devices.pdf) | No homework (yet)| 
[Hard Disk Drives](http://www.cs.wisc.edu/~remzi/OSTEP/file-disks.pdf) | :x:Run [disk.py](file-disks) |  
[RAID](http://www.cs.wisc.edu/~remzi/OSTEP/file-raid.pdf) | :x:Run [raid.py](file-raid) |  
[FS Intro](http://www.cs.wisc.edu/~remzi/OSTEP/file-intro.pdf) | :x:Write some code |  
[FS Implementation](http://www.cs.wisc.edu/~remzi/OSTEP/file-implementation.pdf) | :x:Run [vsfs.py](file-implementation) |  
[Fast File System](http://www.cs.wisc.edu/~remzi/OSTEP/file-ffs.pdf) | :x:Run [ffs.py](file-ffs) |  
[Crash Consistency and Journaling](http://www.cs.wisc.edu/~remzi/OSTEP/file-journaling.pdf) | :x:Run [fsck.py](file-journaling) |  
[Log-Structured File Systems](http://www.cs.wisc.edu/~remzi/OSTEP/file-lfs.pdf) | :x:Run [lfs.py](file-lfs) |  
[Solid-State Disk Drives](http://www.cs.wisc.edu/~remzi/OSTEP/file-ssd.pdf) | :x:Run [ssd.py](file-ssd) |  
[Data Integrity](http://www.cs.wisc.edu/~remzi/OSTEP/file-integrity.pdf) | :x:Run [checksum.py](file-integrity) and Write some code |  
[Distributed Intro](http://www.cs.wisc.edu/~remzi/OSTEP/dist-intro.pdf) | :x:Write some code |  
[NFS](http://www.cs.wisc.edu/~remzi/OSTEP/dist-nfs.pdf) | :x:Write some analysis code |  
[AFS](http://www.cs.wisc.edu/~remzi/OSTEP/dist-afs.pdf) | :x:Run [afs.py](dist-afs) |  

## 测试环境

**OS:** Manjaro 21.2.0 Qonos

**Kernel:** x86_64 Linux 5.13.19-2-MANJARO

**gcc** 版本 11.1.0 (GCC)

**Python** 3.8.12
