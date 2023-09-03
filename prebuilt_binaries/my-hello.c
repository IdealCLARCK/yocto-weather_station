#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN  64
#endif

int main(void)
{
        char hostname[MAXHOSTNAMELEN];

        gethostname(hostname, MAXHOSTNAMELEN);
        hostname[MAXHOSTNAMELEN - 1] = '\0';

        fprintf(stdout, "Hello from %s\n", hostname);

        return EXIT_SUCCESS;
}
