#include <errno.h>
#include <stdio.h>
/*
 * Functions that set the value of errno can be checked with this function.
 * errno is a global variable defined in errno.h
 *
 * returns 1 if an error was set, 0 if one was not set
 */  
int errno_check() {
	switch (errno) {
		case EACCES:				fprintf(stderr, "EACCES\n");
												return 1;
		case ELOOP:					fprintf(stderr, "ELOOP\n");
												return 1;
		case ENAMETOOLONG:	fprintf(stderr, "ENAMETOOLONG\n");	
												return 1;
		case ENOENT:				fprintf(stderr, "ENOENT\n");
												return 1;
		case ENOTDIR:				fprintf(stderr, "ENOTENT\n");
												return 1;
		case EFAULT:				fprintf(stderr, "EFAULT\n");
												return 1;
		case EINVAL:				fprintf(stderr, "EINVAL\n");
												return 1;
		case EMFILE:				fprintf(stderr, "EMFILE\n");
												return 1;
		case EBUSY:					fprintf(stderr, "EBUSY\n");
												return 1;
		case ENFILE:				fprintf(stderr, "ENFILE\n");
												return 1;
		case EAGAIN:				fprintf(stderr, "EAGAIN\n");
												return 1;
		case EBADF:					fprintf(stderr, "EBADF\n");
												return 1;
		case EBADMSG:				fprintf(stderr, "EBADMSG\n");
												return 1;
		case EINTR:					fprintf(stderr, "EINTR\n");
												return 1;
		case EIO:						fprintf(stderr, "EIO\n");
												return 1;
		case EISDIR:				fprintf(stderr, "EISDIR\n");
												return 1;
		case EOVERFLOW:			fprintf(stderr, "EOVERFLOW\n");
												return 1;
		case ECONNRESET:		fprintf(stderr, "ECONNRESET\n");
												return 1;
		case ETIMEDOUT:			fprintf(stderr, "ETIMEDOUT\n");
												return 1;
		case ENOBUFS:				fprintf(stderr, "ENOBUFS\n");
												return 1;
		case ENXIO:					fprintf(stderr, "ENXIO\n");
												return 1;
		case ESPIPE:				fprintf(stderr, "ESPIPE\n");
												return 1;
		case ENOMEM:				fprintf(stderr, "ENOMEM\n");
												return 1;
		case ENOSYS:				fprintf(stderr, "ENOSYS\n");
												return 1;
		case ENOEXEC:				fprintf(stderr, "ENOEXEC\n");
												return 1;
		case EPERM:					fprintf(stderr, "EPERM\n");
												return 1;
		case ETXTBSY:				fprintf(stderr, "ETXTBSY\n");
												return 1;
		case ECHILD:				fprintf(stderr, "ECHILD\n");
												return 1;
		case ESRCH:					fprintf(stderr, "ESRCH\n");
												return 1;
		case EDEADLK:				fprintf(stderr, "EDEADLK\n");
												return 1;
	}
	return 0;
}
