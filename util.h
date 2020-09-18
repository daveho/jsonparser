#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* utility routines */

#ifdef __GNUC__
# define GCC_ATTR(x) x
#else
# define GCC_ATTR(x)
#endif

/* Memory allocation (fatal error if allocation fails) */

void *xmalloc(size_t n);
char *xstrdup(const char *s);

/* Error handling */

void err_fatal(const char *fmt, ...) GCC_ATTR(__attribute__((format(printf, 1, 2))));
void verr_fatal(const char *fmt, va_list args);

#define NOT_IMPLEMENTED(what) \
err_fatal("%s:%d: Not implemented: %s\n", __FILE__, __LINE__, what)

#ifdef __cplusplus
}
#endif

#endif // UTIL_H
