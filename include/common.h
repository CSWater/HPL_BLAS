#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STR(...) #__VA_ARGS__
#define PRINT_DEFINE(x) printf("%s = %s\n", #x, STR(x))
