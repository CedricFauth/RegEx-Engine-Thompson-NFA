#include <stdio.h>
#include <stdlib.h>
#include "regex.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s TEXT REGEX\
		\n\tTEXT  - the text to match against\
		\n\tREGEX - the regex\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	parse(argv[2]);
	debug();

	exit(EXIT_SUCCESS);
}

