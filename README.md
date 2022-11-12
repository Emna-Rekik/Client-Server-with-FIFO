### Client-Server-with-FIFO

This program performs the following functions as a client/server communication system :
- The server waits for clients questions in a named pipe called "fifo1."
- The client prepares his query by going through the following two steps:
  1. Select a random number between 1 and NMAX.
  2. Write his request
- The clients send their query along with their PID so that the server can wake them up later with the signal SIGUSR1 since the client will keep waiting until the response is ready.
- The server prepares its response by giving n randomly generated numbers, then places the results in a named pipe called "fifo2" (n is the random number already generated by the client). 
- The server then sends the response with its PID and wakes up the client.
- The client reads the response and alert the server by the same signal.

#### Example of the output :

![Image1](https://user-images.githubusercontent.com/89909599/201468249-b40e41c1-65b5-4e28-863a-cf5df42e3b0f.png)


#### Compilation command :

```
$ make
```
