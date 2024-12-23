#!/bin/bash

cp kuri.c test.c
make clean
make
cd ../hard
make clean
make
make program
