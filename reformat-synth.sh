#!/bin/bash


awk 'NR <= 131070 {val=strtonum($4); printf "0x%x\n", val}' addr.gen > parseaddr.gen
python3 test.py

md5sum parseaddr.gen test.out