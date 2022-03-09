#!/bin/bash
make
valgrind ./server &
sleep 0.5
./client $(pidof valgrind) "`cat texts/10ksymb.txt`"
kill $(pidof valgrind)
