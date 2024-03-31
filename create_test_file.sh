#!/bin/bash

file_size=$((4*1024*1024+1))
dd if=/dev/zero of=fileA bs=1 count=$file_size
printf '\x01' | dd of=fileA bs=1 seek=0 count=1 conv=notrunc
printf '\x01' | dd of=fileA bs=1 seek=10000 count=1 conv=notrunc
printf '\x01' | dd of=fileA bs=1 seek=$((file_size-1)) count=1 conv=notrunc