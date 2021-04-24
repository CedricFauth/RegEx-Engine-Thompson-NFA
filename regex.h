#ifndef REGEX_CUSTOM_H
#define REGEX_CUSTOM_H

typedef struct state state_t;
typedef struct fragment fragment_t;
typedef union out_list out_list_t;

enum OP {
	OP_MATCH = -1,
	OP_SPLIT = -2,
	OP_CONCAT = -3
};

union out_list {
	state_t *s;
	out_list_t *next;
};

struct state {
	int_fast8_t sym;
	state_t *out;
	state_t *out1;
	unsigned listid;
};

struct fragment {
	state_t *s;
	out_list_t *out;
};

void parse(char *r);

void debug();

#endif
