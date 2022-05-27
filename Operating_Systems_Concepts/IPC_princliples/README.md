# Objectives:

1. To demonstrate IPC principles in action.
2. To develop greater appreciation of shared memory, message passing, and signal IPC mechanisms.
3. To implement a multiprocess application.
4. To use message passing, shared memory, and signals IPC mechanisms in order to implement
cooperation between between processes.
5. To develop a practical application where the sender process transfers files to the receiver
process.

In this homework I used C++ language.

From the Linux terminal:

Open two terminals, then compile using make on one of the terminals. And then
first run the receiver file using the command: ./recv. While the recv is running,
run the sender file file using the command: ./sender keyfile.txt.


Extra Credit
I tried to implement the extra credit in recvSig.cpp and senderSig.cpp and to
compile the recvSig.cpp and senderSig.cpp use the commands:
g++ recvSig.cpp -o r and g++ senderSig.cpp -o s respectively. And then
first run the receiver file using the command: ./r. While the receiver is running,
run the sender file file using the command: ./s keyfile.txt.

My implementation on the bonus question compiles and the sender gets the
receiver's pid, but the receiver does not get sender's pid successfully. Because
of that, it cannot read the fileName, byte size and the data from the sender
correctly.

Another thing to note is that the sender exits when it is done, but the receiver
keeps running even after hitting Ctrl+C. It deallocates its resources on the
ipcs after hitting Ctrl+C, but does not exit, keeps running. In order to kill
the process, find the pidof r on the command line, kill the process with
kill -9 <process id>.