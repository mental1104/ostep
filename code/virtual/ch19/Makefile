CC := gcc
OSFLAG := -D $(shell uname -s)

tlb.out: tlb.c
	$(CC) -O0 -o $@ $< -Wall -Wextra -pthread $(OSFLAG)