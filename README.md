# minitalk

Learning Unix IPC by misusing signals!
---

### Usage
---

clone the repo:

```
git clone --recursive https://github.com/3lswear/minitalk
```

build:

```
cd minitalk && make
```
launch server:

```
./server
```

launch client with a pid ????

### Description
---
The program consists of a client and a server. The former takes a file and sends it to server using user-defined signals `SIGUSR1`, `SIGUSR2`.
Upon completion the server simply prints out received text.

The communication goes on something like this:
```
┌───────────┐    one bit of data  ┌───────────┐
│           ├─────────────────────►           │
│           │                     │           │
│           │  SIGUSR1/SIGUSR2    │           │
│  client   │                     │  server   │
│           │                     │           │
│           ◄─────────────────────┤           │
│           │      confirmation   │           │
│           │                     │           │
└───────────┘                     └───────────┘
```
The hard part was to make data transfer fast and resistant to latency variations.
