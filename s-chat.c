/******************************************************************************#
*Authour	:	Ben Haubrich																											 *
*File			: s-chat.c																													 *
*Synopsis	:	A simple chat facility that enables someone at one terminal to	   *
*						communicate with another user at a terminal using the UDP transport*
*						protocol and the pthreads library.																 *
*******************************************************************************/
/* Standard Headers */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/select.h> /* For select() */
#include <fcntl.h> /* For open() */
/* Local Headers */
#include <s-chat.h>
#include <s-chat_err.h>

void delay() {
	int i;
	for(i = 0; i < 1E6; i++);
}

/*
 * Waits for input from the keyboard
 */
void *keyin(void *args) {
	fcntl(STDIN_FILENO, F_SETFL, (O_RDONLY | O_NONBLOCK));
	uint8_t buf[256];
	int numbytes;
	while(1) {
		numbytes = read(STDIN_FILENO, buf, sizeof(buf));
		if(-1 == numbytes) {
			/* read is going to error a lot, and mostly it will be EAGAIN. */
			/* That just means that read could not perform a read without */
			/* blocking. We're not really interested in this error as it is */
			/* expected. */
			if(EAGAIN == errno) {
				/* Clear the buffer of data so it doesn't read() twice. */
				memset(buf, 0, 256);
				continue;
			}
			else {
				fprintf(stderr, "read() encountered an error\n");
				errno_check();
				memset(buf, 0, 256);
			}
		}
		else {
			printf("%s", buf);
		}
	}
}

/*
 * Wait for udp datagrams
 */
void *receive_udp(void *args) {
	while(1) {
	}
}

/*
 * Send a upd datagram
 */
void *send_udp(void *args) {
	while(1) {
	}
}

/*
 * Puts characters on the local screen
 */
void *put_c(void *args) {
	while(1) {
	}
}

int main(int argc, char *argv[]) {

	if(argc < 4) {
		fprintf(stderr, "Not enough arguments\n%s\n", USAGE);
		exit(EXIT_FAILURE);

	}
	else if(argc > 4) {
		fprintf(stderr, "Too many arguments\n%s\n", USAGE);
		exit(EXIT_FAILURE);
	}

	unsigned int localPort;
	char *remoteName;
	unsigned int remotePort;
	pthread_t threads[NUM_CHAT_TASKS];
	void *tasks[NUM_CHAT_TASKS] = {keyin, receive_udp, send_udp, put_c};

	localPort = atoi(argv[0]);
	remoteName = argv[1];
	remotePort = atoi(argv[2]);

	int retval;
	int i;
	for(i = 0; i < NUM_CHAT_TASKS; i++) {
		retval = pthread_create(	threads + i,
															NULL, /* Default attributes */
															tasks[i],
															NULL); /* No arguments passed */
		switch(retval) {
			case EAGAIN:	fprintf(stderr, "Insufficient resources to create another "
												"thread\n"); break;
			case EINVAL:	fprintf(stderr, "invalid settings in attr\n");	break;

			case EPERM:		fprintf(stderr, "No permission to set the scheduling "
												"policy and parameters specified in attr\n"); break;
			case 0:				break; /* No errors */
			default:			fprintf(stderr, "Unepected error\n");	break;
		}
		assert(retval == 0);
	}
	/* Stop the parent thread here, and let the children run */
	for(i = 0; i < NUM_CHAT_TASKS; i++) {
		retval = pthread_join(threads[i], NULL);
		switch(retval) {
			case EDEADLK:	fprintf(stderr, "A deadlock was detected\n");
										break;
			case EINVAL:	fprintf(stderr, "The thread is not joinable\n");
										break;
			case ESRCH:		fprintf(stderr, "No thread with this threads ID could be "
																		" found\n"); break;
			case 0:				break; /* No errors */
			default:			fprintf(stderr, "Unexpected error\n");
		}
		assert(retval == 0);
	}
	return EXIT_SUCCESS;
}

