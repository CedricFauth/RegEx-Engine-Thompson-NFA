#ifndef REGEX_CUSTOM_H
#define REGEX_CUSTOM_H

#define DEBUG_REGEX
//#undef DEBUG_REGEX

#ifdef DEBUG_REGEX
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...) {}
#endif//DEBUG_REGEX

typedef struct fragment fragment_t;
typedef struct regex_t regex_t;
typedef struct state state_t;
typedef union out_list out_list_t;

regex_t *create_regex(char *r);

void delete_regex(regex_t *r);

void debug(regex_t *r);

#endif
