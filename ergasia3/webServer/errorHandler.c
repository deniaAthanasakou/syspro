#include <stdio.h>
#include <stdlib.h> /* exit */

#include "errorHandler.h"

void perror_exit(char *message) {
	perror(message);
	exit(EXIT_FAILURE);
}
