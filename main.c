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

	regex_t *reg = create_regex(argv[2]);

	debug(reg);

	delete_regex(reg);

	exit(EXIT_SUCCESS);
}

