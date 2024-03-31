#!/bin/bash

make

bash create_test_file.sh

./myprogram fileA fileB

gzip -k fileA
gzip -k fileB

gzip -cd fileB.gz | ./myprogram fileC

./myprogram -b 100 fileA fileD

echo "File sizes:"
stat -c "%n: %s bytes, %b blocks" fileA fileA.gz fileB fileB.gz fileC fileD