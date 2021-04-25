#ifndef REGEX_CUSTOM_H
#define REGEX_CUSTOM_H

typedef struct fragment fragment_t;
typedef fragment_t regex_t;
typedef struct state state_t;
typedef union out_list out_list_t;

regex_t *create_regex(char *r);
void delete_regex(regex_t *r);

void debug();

#endif
