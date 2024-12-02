#!/bin/bash

cat /proc/sys/kernel/random/entropy_avail

i=0
while [ "$i" -le 1000 ]; do
    cat "$i" 2>/dev/null
    i=$((i + 1))
done

while [ "$i" -le 1000 ]; do
    xxcatx "$i" 2>/dev/null
    i=$((i + 1))
done

while [ "$i" -le 1000 ]; do
    catx "$i" 2>/dev/null
    i=$((i + 1))
done

while [ "$i" -le 1000 ]; do
    echo  $(date) 1>/dev/null
    i=$((i + 1))
done
cat /proc/sys/kernel/random/entropy_avail