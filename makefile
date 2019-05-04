################################################################################
#Authour	:Ben Haubrich						       																			 #
#File			:makefile						       																					 #
#Synopsis	:makefile for s-chat.c					       															 #
################################################################################

CC=gcc
CFLAGS=-Wall -Wextra -std=c89 -g
VPATH=./include

s-chat: s-chat.o
	${CC} ${CFLAGS} -o s-chat s-chat.o -lpthread

s-chat.o:	s-chat.c s-chat.h
	${CC} ${CFLAGS} -c -I./include s-chat.c

clean:
	rm -rf s-chat s-chat.o
