#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "util.h"

void *xmalloc(size_t n) {
  void *buf = malloc(n);
  if (!buf) {
    err_fatal("Allocation of %lu bytes failed", (unsigned long) n);
  }
  return buf;
}

char *xstrdup(const char *s) {
  size_t slen = strlen(s);
  char *buf = xmalloc(slen + 1);
  memcpy(buf, s, slen);
  buf[slen] = '\0';
  return buf;
}

void err_fatal(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  exit(1);
}

void verr_fatal(const char *fmt, va_list args) {
  vfprintf(stderr, fmt, args);
  exit(1);
}
