/* test-update-server.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#include <stdio.h>                  /* standard in/out procedures */
#include <stdlib.h>                 /* defines system calls */
#include <string.h>                 /* necessary for memset */
#include <netdb.h>
#include <termios.h>
#include <sys/socket.h>             /* used for all socket calls */
#include <netinet/in.h>             /* used for sockaddr_in6 */
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#ifndef __MACH__
#include <termio.h>
#include <linux/serial.h>
typedef void (*sighandler_t)(int);
sighandler_t sigset(int sig, sighandler_t disp);
#endif

#define MSGLEN      (4 + 4 + 8)

#ifndef UART_DEV
#define UART_DEV "/dev/ttyS0"
#endif
#ifndef B115200
#define B115200 115200
#endif
#ifndef TIMEOUT
#define TIMEOUT 60
#endif

void alarm_handler(int signo)
{
    printf("0\n");
    exit(0);
}


int main(int argc, char** argv)
{
    struct termios tty;
    int res, serialfd;
    int star = 0;
    int i = 3;
    uint32_t ver = 0;
    sigset(SIGALRM, alarm_handler);


    if ((argc > 3) || (argc < 2)) {
        printf("Usage: %s UART_TTY [trigger command]\n", argv[0]);
        exit(1);
    }

    serialfd = open(argv[1], O_RDWR | O_NOCTTY);
    if (serialfd < 0) {
        fprintf(stderr, "Cannot open serial port %s: %s\n", argv[1], strerror(errno));
	exit(2);
    }
    tcgetattr(serialfd, &tty);
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
    tcsetattr(serialfd, TCSANOW, &tty);
    cfmakeraw(&tty);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CRTSCTS;
    if (tcsetattr(serialfd, TCSANOW, &tty) != 0)
	    return -1;

    alarm(TIMEOUT);

    if (argc > 2) {
        fprintf(stderr, "Executing \"%s\"\n", argv[2]);
        system(argv[2]);
    }

    while (i >= 0) {
        char c;
        res = read(serialfd, &c, 1);
	if (res <= 0) {
            usleep(10000);
            continue;
        }
        fprintf(stderr, "rx: %x\n", c);
	if (!star) {
            if (c == '*') {
                star = 1;
                i = 3;
            } else {
                star = 0;
            }
        } else {
            ver += (((uint32_t)c) << (i-- * 8));
        }
    }
    printf("%d\n", ver);

    fprintf(stderr, "ver: %d\n", ver);

    close(serialfd);
    return 0;
}
