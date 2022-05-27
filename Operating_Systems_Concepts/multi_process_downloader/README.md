# Goals:

1. To gain hands-on experience with fork(), exec(), and wait() system calls.
2. To master the basics of multi-process application development.
3. To appreciate the performance and fault-tolerance benefits of multi-process applications.
4. To implement a multi-process downloader application.

In this homework I used C++ language.

From the Linux terminal:
Part I
To compile the shell.cpp use the command: g++ shell.cpp -o shell
and then run the file using the command: ./shell

Part II
To compile the serial.cpp usethe command: g++ serial.cpp -o serial
and then run the file using the command: ./serial

To compile the parallel.cpp use the command: g++ parallel.cpp -o parallel
and then run the file using the command: ./parallel

Extra Credit
I implemented the extra credit and to compile the multi-search.cpp use the command:
g++ multi-search.cpp -o multi-search and then run the file using the command:
./multi-search <FILE NAME> <KEY> <NUMBER OF PROCESSES>, where <FILE NAME> is the
name of the file containing the string, <KEY> is the string to search for
<NUMBER OF PROCESSES> is the number of child processes.

The Execution Times
Serial downloader:
  real    2m32.617s
  user    0m1.938s
  sys     0m30.162s

Parallel downloader:
  real    1m40.675s
  user    0m2.005s
  sys     0m22.934s

The answers to the questions on the assignment1.pdf:
1. The difference between real, user, and sys times:
Real is wall clock time - time from start to finish of the call. This is all
elapsed time including time slices used by other processes and time the process
spends blocked (for example if it is waiting for I/O to complete).

User is the amount of CPU time spent in user-mode code (outside the kernel)
within the process. This is only actual CPU time used in executing the process.
Other processes and time the process spends blocked do not count towards this figure.

Sys is the amount of CPU time spent in the kernel within the process.
This means executing CPU time spent in system calls within the kernel, as
opposed to library code, which is still running in user-space. Like 'user',
this is only CPU time used by the process.

2. Is user time or sys time longer?
The outputs of both downloaders showed that sys time was longer. This also
makes sense to me because there is a heavy disk I/O activity (downloading large
files) going on within both downloaders. And more CPU time is being spent in the
kernel. Therefore, this makes the sys time longer.

3. When downloading the files above, which downloader finishes faster?
The parallel downloader finished faster in my program. I believe it could be
because when we download in parallel, we can access multiple resources at the
same time, hence increases the utilization of the available resources better.
If the communication capacity is  good enough, not bottleneck, we would
get better results with parallel downloaders compared to serial downloaders.

4. Repeat the experiment for 10 files (any reasonably large-sized files, e.g.,
100 MB, will do). Is the downloader in the previous question still faster? If
not so, why do you think that is?
I repeated this experiment for 15 files and found out that the parallel downloaders
was still faster. However, I would expect that when I download more large files
at the same time as we have resources for, then it might start slowing down since
more processes compete for limited resources where the overhead becomes an issue.

My submission is as expected. For the bonus question I used an online source:
"https://www.techiedelight.com/split-vector-into-subvectors-cpp/" for the next
and copy functions used in splitting the vector into n sections.
