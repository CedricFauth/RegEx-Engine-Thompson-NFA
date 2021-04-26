#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "regex.h"

enum OP {
	// + = * = ? > AND > |
	// merge if last > current

	OP_MATCH =	-1,		// matches
	OP_ZORM =	-3,		// 	*	zero or more	
	OP_OORM =	-4,		// 	+	one or more
	OP_ZORO =	-5,		// 	?	zero or one
	OP_CONCAT =	-10,	// 	ab 	concatination
	OP_OR =		-15,	// 	| 	or
	OP_OPEN_P =	-50,	// 	(
	OP_CLOSE_P=	-51		//	)
};

int_fast8_t precedence(int_fast8_t op) {
	if (op == -1) return 10;			// match
	else if (op >= OP_ZORO) return 5;	// * + ?
	else if (op == OP_CONCAT) return 4;	// concat
	else if (op == OP_OR) return 3;		// |
	else return 1;						// ()
}

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

struct regex_t {
	fragment_t f;
	unsigned n;
	state_t *states[];
};

static fragment_t *out_ptr, out_stack[1000];
static int_fast8_t *op_ptr, op_stack[1000];
static state_t **state_ptr, *state_stack[1000];

static bool no_concat;

#define PUSH_OUT(x) *out_ptr++ = x
#define POP_OUT() *--out_ptr
#define PUSH_OP(x) *op_ptr++ = x
#define POP_OP() *--op_ptr
#define PEEK_OP() *(op_ptr-1)

#define PUSH_STATE(x) *state_ptr++ = x
#define POP_STATE() *--state_ptr

bool isregcrtl(char c) {
	if (c=='+'||c=='*'||c=='?'||c=='|') return true;
	return false;
}

bool validate(char *r){
	char c, lastc = 0, *tmp = r;
	int open_close = 0;
	if (*r != '/') return false; 	// regex starts with '/'
	if (*++r == '/') return false; 	// regex is not "//"
	// go to next '/'; ignore '\/'
	while (*r && (*r != '/' || lastc == '\\')) {
		c = *r;
		debugf("%c\n",c);
		if (isregcrtl(c) && (!lastc||isregcrtl(lastc))){
			debugf("%c %d\n", c, lastc);
			if (!(c=='|' && lastc!='|')) return false;
		}
		if (isregcrtl(c) && lastc == '(') return false;
		if (c=='(') ++open_close;
		else if (c == ')') --open_close;
		if (open_close < 0) return false;
		lastc = c;
		++r;
	}
	if (!*r) return false;			// pos not '\0' but '/'
	if (*(r+1)) return false;		// next pos is end '\0'
	debugf("found regex of len: %ld\n", r-tmp-1);
	return true;
}

state_t *new_state(int_fast8_t sym, state_t *o, state_t *o1) {
	state_t *s = malloc(sizeof(*s));
	s->sym = sym;
	s->out = o;
	s->out1 = o1;
	s->listid = 0;
	PUSH_STATE(s);	// push state address on local stack
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
		debugf("patching out %p to %p\n", (void*)&l->s, (void*)out);
		debugf("now patched to %p\n", (void*)l->s);
	}
}

void print_frag(fragment_t *f) {
	debugf("print_frag: s: %p; outlist", (void*)f->s);
	out_list_t *next, *curr = f->out;
	for (;curr;curr=next){
		next = curr->next;
		debugf("->%p", (void*)curr);
	}
	
}

void merge() {
	for (int i = 0; i < 10; ++i) debugf("%d ", op_stack[i]);
	int_fast8_t last_op = POP_OP();
	state_t *s;
	fragment_t f1, f2;
	switch (last_op) {
	case OP_MATCH:
		f1 = POP_OUT();
		s = new_state(OP_MATCH, NULL, NULL);
		debugf("final state: %p\n", (void*)s);
		patch(f1.out, s);
		PUSH_OUT(new_frag(f1.s, NULL));
		break;
	case OP_CONCAT:
		debugf("OP_CONCAT\n");
		f2 = POP_OUT();
		f1 = POP_OUT();
		patch(f1.out, f2.s);
		PUSH_OUT(new_frag(f1.s, f2.out));
		break;
	case OP_OR:
		debugf("OP_OR\n");
		f2 = POP_OUT();
		f1 = POP_OUT();
		s = new_state(OP_OR, f1.s, f2.s);
		PUSH_OUT(new_frag(s, append(f1.out, f2.out)));
		break;
	case OP_OORM:
		debugf("OP_OORM +\n");
		f1 = POP_OUT();
		s = new_state(OP_OORM, f1.s, NULL);
		patch(f1.out, s);
		PUSH_OUT(new_frag(f1.s, new_list(&s->out1)));
		break;
	case OP_ZORM:
		debugf("OP_ZORM *\n");
		f1 = POP_OUT();
		s = new_state(OP_ZORM, f1.s, NULL);
		patch(f1.out, s);
		PUSH_OUT(new_frag(s, new_list(&s->out1)));
		break;
	case OP_ZORO:
		debugf("OP_ZORO ?\n");
		f1 = POP_OUT();
		s = new_state(OP_ZORO, f1.s, NULL);
		PUSH_OUT(new_frag(s, append(f1.out, new_list(&s->out1))));
		break;
	default:
		fprintf(stderr, "error: merge op not found: %d\n", last_op);
		break;
	}
}

void check_precedence(int_fast8_t op) {
	while (op_ptr != op_stack 
		&& precedence(PEEK_OP()) > precedence(op)) 
	{
		debugf("merge: %d\n", PEEK_OP());
		merge();
	}
}

void parse(char *r) {
	if (!*r++) return; // *r != '\0' and r = r+1

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
			if (!no_concat) // no binary op before
				PUSH_OP(OP_CONCAT);
			PUSH_OP(OP_OPEN_P);
			no_concat = true;
			break;
		case ')':
			check_precedence(OP_CLOSE_P);
			if (PEEK_OP() == OP_OPEN_P) POP_OP();
			else {
				fprintf(stderr, "No '(' for ')' detected\n");
				return;
			}
			no_concat = false;
			break;
		case '|':
			check_precedence(OP_OR);
			PUSH_OP(OP_OR);
			no_concat = true;
			break;
		case '+':
			check_precedence(OP_OORM);
			PUSH_OP(OP_OORM);
			no_concat = false;
			break;
		case '*':
			check_precedence(OP_ZORM);
			PUSH_OP(OP_ZORM);
			no_concat = false;
			break;
		case '?':
			check_precedence(OP_ZORO);
			PUSH_OP(OP_ZORO);
			no_concat = false;
			break;
		default: // is alpha or num
			if (!isalnum(c)) {
				fprintf(stderr, "warning: ignoring unknown symbol: '%c'\n", c);
				break;
			}
			if (no_concat || out_ptr == out_stack) {
				debugf("\nno_concat add_char\n");
			} else {
				check_precedence(OP_CONCAT);
				PUSH_OP(OP_CONCAT);
			}
			state_t *s = new_state(c, NULL, NULL);
			PUSH_OUT(new_frag(s, new_list(&s->out)));
			no_concat = false;
			break;
		}
	}
}

regex_t *create_regex(char *r) {

	no_concat = true; // beginning: no concatination required
	out_ptr = out_stack;
	op_ptr = op_stack;
	state_ptr = state_stack;

	if (!validate(r)) { // validating input regex string
		fprintf(stderr, "error: regex not valid.\n");
		return NULL;
	}

	parse(r);	// generating NFA from string

	if (out_ptr-out_stack != 1) { // 
		fprintf(stderr, "error: more than one fragment at end\n");
		return NULL;
	}

	ssize_t num_states = state_ptr-state_stack;
	regex_t *reg = malloc(sizeof(*reg) + num_states*sizeof(reg->states[0]));
	debugf("size of states %zu*%lu\n", num_states, sizeof(reg->states[0]));

	reg->f = POP_OUT();
	reg->n = num_states;
	for (int i = 0; i < num_states; i++) 
		reg->states[i] = POP_STATE();

	return reg;
}

void delete_regex(regex_t *r) {
	if (!r) return;
	for (int i = 0; i < r->n; i++) {
		debugf("free\n");
		free(r->states[i]);
	}
	free(r);
}

// debugging section

void follow(state_t *s) {
	if (!s) return;
	printf("\t%p -> (%d; out: %p; out1: %p)\n", 
		(void*)s, s->sym, (void *)s->out, (void *)s->out1);
	printf("\t\taddr out: %p; addr out1: %p\n", 
		(void*)&s->out, (void*)&s->out1);
	
	if(s->sym != OP_ZORM 		// otherwise endless recursion
		&& s-> sym != OP_OORM) follow(s->out); 
	follow(s->out1);
}

void debug(regex_t *r) {
	printf("\nout_stack: %ld\n", out_ptr-out_stack);
	printf("op_stack: %ld\n", op_ptr-op_stack);

	printf("fragment: s: %p; outlist\n", (void*)r->f.s);
	out_list_t *next, *curr = r->f.out;
	for (;curr;curr=next){
		next = curr->next;
		printf("->%p\n", (void*)curr);
	}
	printf("done \n");
	follow(r->f.s);
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
