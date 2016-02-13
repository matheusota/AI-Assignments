#!/bin/sh

gcc -g -o main main.c functions.c unifier.c resolution.c -lm
