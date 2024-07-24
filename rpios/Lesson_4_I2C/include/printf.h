#pragma once

#include <stdarg.h>

int printf(char *fmt, ...);

void init_printf(void *, void (*putf)(void *, char));
