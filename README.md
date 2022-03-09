# minitalk

Learning Unix IPC by misusing signals!
---

### Usage
---

clone the repo:

```bash
git clone --recursive https://github.com/3lswear/minitalk
```

build:

```bash
cd minitalk && make
```
launch server:

```
./server
```

launch client with server's pid and string to send as arguments:

```bash
./client 1337 a_string_to_send
```
or, to make things easier:

```bash
./client $(pidof server) "$(< text.txt)"
```

### Description
---
The program consists of a client and a server. The former takes a file and sends it to server using user-defined signals `SIGUSR1`, `SIGUSR2`.
Upon completion the server simply prints out received text.

The communication goes on something like this:
```
┌───────────┐                    ┌───────────┐
│           │   one bit of data  │           │
│           ├────────────────────►           │
│           │                    │           │
│  client   │  SIGUSR1/SIGUSR2   │  server   │
│           │                    │           │
│           │                    │           │
│           ◄────────────────────┤           │
│           │    confirmation    │           │
└───────────┘                    └───────────┘
```
The hard part was to make data transfer fast and resistant to latency variations.
