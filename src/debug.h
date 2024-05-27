#ifndef CORD_DEBUG_H
#define CORD_DEBUG_H
#include "token.h"

#ifdef DEBUG_BUILD
#define DEBUG 1
#endif

extern const char* debug_token_type_strings[NUM_TOKEN_TYPES];

#endif // !CORD_DEBUG_H
#define CORD_DEBUG_H