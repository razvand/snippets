/*
 * does a new socket (created from the accept call) have the same
 * port as the listening socket?
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_PORT	55555
#define LISTEN_BACKLOG	5

static inline void print_sock (struct sockaddr_in *addr, char *msg)
{
	printf ("%s: %s:%d\n", msg, inet_ntoa (addr->sin_addr),
			ntohs (addr->sin_port));
}

int main (void)
{
	int lsock, csock;	/* listening and connection socket */
	struct sockaddr_in caddr;
	struct sockaddr_in laddr = {
		.sin_family = AF_INET,
		.sin_port = htons (LISTEN_PORT),
		.sin_addr = {
			.s_addr = htonl (INADDR_ANY),
		},
	};
	socklen_t len;

	lsock = socket (PF_INET, SOCK_STREAM, 0);
	if (lsock < 0) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	len = sizeof (laddr);
	if (bind (lsock, (struct sockaddr *) &laddr, len) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}

	if (listen (lsock, LISTEN_BACKLOG) < 0) {
		perror ("listen");
		exit (EXIT_FAILURE);
	}

	csock = accept (lsock, NULL, NULL);
	if (csock < 0) {
		perror ("accept");
		exit (EXIT_FAILURE);
	}

	len = sizeof (caddr);
	if (getsockname (csock, (struct sockaddr *) &caddr, &len) < 0) {
		perror ("getsockname");
		exit (EXIT_FAILURE);
	}

	print_sock (&laddr, "Listening socket");
	print_sock (&caddr, "Connection socket");

	return 0;
}
