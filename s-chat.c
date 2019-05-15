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
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/select.h> /* For select() */
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
	/* copy of stdin for keyboard (keybin) */
	int keybin = dup(STDIN_FILENO);
	if(-1 == keybin) {
		fprintf(stderr, "dup() encountered an error\n");
		errno_check();
	}
	uint8_t buf[256];
	int numbytes;
	fd_set readfds;
	/* Select return */
	int selret;
	struct timeval timeout;
	/* Initialize the readfds bit array. */
	FD_ZERO(&readfds);
	/* Put keybin into the set of readfds. */
	FD_SET(keybin, &readfds);
	/* Timeout of 3ms before select no longer blocks. */
	timeout.tv_sec = 0;
	timeout.tv_usec = 3000;
	while(1) {
		selret = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
		if(-1 == selret) {
			fprintf(stderr, "select() encountered an error\n");
			errno_check();
		}
		/* Select did not time out, there is input available in the readfds. */
		else if(selret > 0) {
			/*
			 * TODO: Check and see if this is getting here. I don't get any printf's
			 * when I run the program.
			 */
			numbytes = read(keybin, buf, sizeof(buf));
			printf("%s", buf);
			if(-1 == numbytes) {
				fprintf(stderr, "read() encountered an error\n");
				errno_check();
			}
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

