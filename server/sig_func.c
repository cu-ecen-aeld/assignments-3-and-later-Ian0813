/*
 * =====================================================================================
 *
 *       Filename:  sig_func.c
 *
 *    Description:  signal handler
 *
 *        Version:  1.0
 *        Created:  2023年04月16日 22時50分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ian 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdarg.h>
#include "aesdsocket.h" 

void signal_handler(int signum) {

    USER_LOGGING("%s", "Caught signal, exiting");
    //USER_LOGGING("%s:%d", "hello", 30);
#if 0
    exit(EXIT_SUCCESS);
#else
    return;
#endif
}

int signal_setup(int amount, ...) {

    int rc, signum;
	va_list ap;
    struct sigaction sig_info; 

	sig_info.sa_handler = signal_handler;

    va_start(ap, amount);
	while (amount > 0) {
        signum = va_arg(ap, int);
        rc = sigaction(signum, &sig_info, NULL); 
		if (rc == -1) {
            break;  
		}
		amount--;
	}
	va_end(ap);

    return rc;
}
