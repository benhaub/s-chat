################################################################################
#Authour	:Ben Haubrich						       																			 #
#File			:makefile						       																					 #
#Synopsis	:makefile for s-chat.c					       															 #
################################################################################

CC=gcc
CFLAGS=-Wall -Wextra -std=c99
ifdef DEBUG
	CFLAGS+=-g3 -gdwarf-2 -O0
endif
VPATH=./include

s-chat: s-chat.o s-chat_err.o liblist.a
	${CC} ${CFLAGS} -o s-chat s-chat.o s-chat_err.o -lpthread -L. -llist

s-chat.o:	s-chat.c s-chat.h
	${CC} ${CFLAGS} -c -I./include s-chat.c

s-chat_err.o: s-chat_err.c s-chat_err.h
	${CC} ${CFLAGS} -c -I./include s-chat_err.c

clean:
	rm -rf s-chat s-chat.o s-chat_err.o
