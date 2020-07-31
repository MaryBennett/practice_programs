# Make file for Floyd Algorithm

# Copyright (C) 2020 Embecosm Limited <www.embecosm.com>
# Contributor: Mary Bennett <mary.bennett@embecosm.com>
# SPDX-License-Identifier: GPL-3.0-or-later

CC = gcc
CFLAGS = -g
export CFLAGS

.PHONY: all clean
all: floyd

clean:
	$(RM) floyd
	$(RM) *.o *.i

floyd: floyd.c
	$(CC) $(CFLAGS) -o $@ $^

