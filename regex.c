#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "regex.h"

enum OP {
	// + = * = ? > AND > |
	// merge if last > current

	OP_MATCH= 	-1,		// matches
	OP_ZORM= 	-5,		// 	*	zero or more	
	OP_OORM= 	-5,		// 	+	one or more
	OP_ZORO= 	-5,		// 	?	zero or one
	OP_CONCAT=	-10,	// 	ab 	concatination
	OP_OR=	 	-15,	// 	| 	or
	OP_OPEN_P= 	-50,	// 	(
	OP_CLOSE_P=	-50		//	)
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

static fragment_t *out_ptr, out_stack[1000];
static int_fast8_t *op_ptr, op_stack[1000];

static bool no_concat;

#define PUSH_OUT(x) *out_ptr++ = x
#define POP_OUT() *--out_ptr
#define PUSH_OP(x) *op_ptr++ = x
#define POP_OP() *--op_ptr
#define PEEK_OP() *(op_ptr-1)

bool validate(char *r){
	char *tmp = r;
	if (*r != '/') return false; 	// regex starts with '/'
	if (*++r == '/') return false; 	// regex is not "//"
	++r;
	while (*r && (*r != '/' || *(r-1) == '\\')) ++r; // go to next '/'; ignore '\/'
	if (!*r) return false;			// pos not '\0' but '/'
	if (*(r+1)) return false;		// next pos is end '\0'
	printf("found regex of len: %ld\n", r-tmp-1);
	return true;
}

state_t *new_state(int_fast8_t sym, state_t *o, state_t *o1) {
	state_t *s = malloc(sizeof(*s));
	s->sym = sym;
	s->out = o;
	s->out1 = o1;
	s->listid = 0;
	return s;
}

fragment_t new_frag(state_t *s, out_list_t *o) {
	fragment_t f = {s, o};
	return f;
}

out_list_t *new_list(state_t **s) {
	out_list_t *l;
	l = (out_list_t *)s;
	l->next = NULL;
	return l;
}

out_list_t *append(out_list_t *l1, out_list_t *l2) {
	out_list_t *new = l1;
	while (l1->next) l1 = l1->next;
	l1->next = l2;
	return new;
}

void patch(out_list_t *l, state_t *out) {
	out_list_t *next;
	for (; l; l=next) {
		next = l->next;
		l->s = out;
		printf("patching out %p to %p\n", (void*)&l->s, (void*)out);
		printf("now patched to %p\n", (void*)l->s);
	}
}

void add_char(char c) {
	if (no_concat || out_ptr == out_stack) {
		printf("\nno_concat add_char\n");
	} else PUSH_OP(OP_CONCAT);
	//
	state_t *s = new_state(c, NULL, NULL);
	PUSH_OUT(new_frag(s, new_list(&s->out)));
}

/*

/ab(c+d*|ef)/

*/

void print_frag(fragment_t *f) {
	printf("print_frag: s: %p; outlist", (void*)f->s);
	out_list_t *next, *curr = f->out;
	for (;curr;curr=next){
		next = curr->next;
		printf("->%p", (void*)curr);
	}
	
}

void merge() {
	for (int i = 0; i < 10; ++i) printf("%d ", op_stack[i]);
	int8_t last_op = POP_OP();
	state_t *s;
	fragment_t f1, f2;
	switch (last_op) {
	case OP_MATCH:
		f1 = POP_OUT();
		s = new_state(OP_MATCH, NULL, NULL);
		printf("final state: %p\n", (void*)s);
		patch(f1.out, s);
		PUSH_OUT(new_frag(f1.s, NULL));
	case OP_CONCAT:
		printf("OP_CONCAT\n");
		f2 = POP_OUT();
		f1 = POP_OUT();
		patch(f1.out, f2.s);
		PUSH_OUT(new_frag(f1.s, f2.out));
		break;
	case OP_OR:
		printf("OP_OR\n");
		f2 = POP_OUT();
		f1 = POP_OUT();

		printf("\nf1: ");
		print_frag(&f1);
		printf("\nf2: ");
		print_frag(&f2);

		s = new_state(OP_OR, f1.s, f2.s);
		PUSH_OUT(new_frag(s, append(f1.out, f2.out)));
		break;
	default:
		fprintf(stderr, "error: merge op not found: %d\n", last_op);
		break;
	}
}

void check_precedence(int8_t operator) {
	while (op_ptr != op_stack && PEEK_OP() > operator) {
		printf("merge: %d\n", PEEK_OP());
		merge();
	}
}

void parse(char *r) {
	if (!*r++) return; // *r != '\0' and r = r+1
	
	no_concat = false;
	out_ptr = out_stack;
	op_ptr = op_stack;

	char c;
	while ((c = *r++)) {
		switch (c) {
		case '/':
			while (op_ptr != op_stack) merge();
			if (out_ptr-out_stack != 1) {
				fprintf(stderr, "error: more than one fragment at end\n");
				return;
			}
			PUSH_OP(OP_MATCH);
			merge();
			return;
		case '(':
			// TODO
			no_concat = true;
			break;
		case ')':
			// TODO
			PUSH_OP(OP_CONCAT);
			break;
		case '|':
			check_precedence(OP_OR);
			PUSH_OP(OP_OR);
			no_concat = true;
		case '+':
		case '*':
		case '?':
			break;
		default: // is alpha or num
			if (!isalnum(c)) {
				fprintf(stderr, "warning: ignoring unknown symbol: '%c'\n", c);
				break;
			};
			add_char(c);
			no_concat = false;
			break;
		}
	}
}

regex_t *create_regex(char *r) {

	if (!validate(r)) {
		fprintf(stderr, "error: regex not valid.\n");
		return NULL;
	}
	parse(r);

	regex_t *reg = malloc(sizeof(*reg));
	reg->s = out_stack->s;
	reg->out = out_stack->out;

	debug(reg);

	return reg;
}

void free_states(state_t *s) {
	// TODO
}

void delete_regex(regex_t *r) {
	if (!r) return;
	free_states(r->s);
	free(r);
}

// debugging section

void follow(state_t *s) {
	if (!s) return;
	printf("\t%p -> (%d; out: %p; out1: %p)\n", 
		(void*)s, s->sym, (void *)s->out, (void *)s->out1);
	printf("\t\taddr out: %p; addr out1: %p\n", 
		(void*)&s->out, (void*)&s->out1);
	follow(s->out);
	follow(s->out1);
}

void debug(regex_t *f) {
	printf("\nout_stack: %ld\n", out_ptr-out_stack);
	printf("op_stack: %ld\n", op_ptr-op_stack);

	printf("fragment: s: %p; outlist\n", (void*)f->s);
	out_list_t *next, *curr = f->out;
	for (;curr;curr=next){
		next = curr->next;
		printf("->%p\n", (void*)curr);
	}
	printf("done \n");
	follow(f->s);
}

/*

/ab|12/

op_s  :
out_s : ab|12

/ab(1|2)?c/

op_s  :
out_s :a->b->(1|2)?->c


ab(1|21+)?/

op_s  :
out_s :a->b->1|(21+)?

Klammer: auf: kein . danach; zu: alles löschen bis Klammer + push(.)
Buchstabe: 	wenn letzter push operator war: nur hinzufügen
			sonst push(.) und hinzufügen
Operator: | -> davor .*? ausführen
			sonst push(.)

		andere: + = * = ? > AND > |

Bei | (bin op) kein auto . danach

ab|cd|ef

op_s  :
out_s :ab|(cd|ef)

a|b+c

op_s  :
out_s :a|((b+)c)

*/
