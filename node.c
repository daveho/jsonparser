#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "util.h"
#include "node.h"

#define DEFAULT_INITIAL_CAPACITY 2

#define DEBUG_PRINT(args...)
//#define DEBUG_PRINT(args...) printf(args)

struct Node {
  // the tag is the node type (for parse trees, the grammar symbol)
  int tag;
  // dynamic array of pointers to child nodes
  struct Node **kids;
  // how many children there are
  int num_kids;
  // total capacity of kids array
  int capacity;

  // payload data
  char *str;
  long ival;

  // information about source file and location
  struct SourceInfo source_info;
};

struct Node *node_alloc(int tag) {
  struct Node *n = malloc(sizeof(struct Node));
  n->kids = xmalloc(sizeof(struct Node *) * DEFAULT_INITIAL_CAPACITY);
  n->num_kids = 0;
  n->capacity = DEFAULT_INITIAL_CAPACITY;
  n->str = NULL;
  n->ival = 0L;
  n->tag = tag;
  // Node starts out with unknown source info
  n->source_info.filename = "<unknown file>";
  n->source_info.line = -1;
  n->source_info.col = -1;
  return n;
}

struct Node *node_alloc_str_copy(int tag, const char *str_to_copy) {
  return node_alloc_str_adopt(tag, xstrdup(str_to_copy));
}

struct Node *node_alloc_str_adopt(int tag, char *str_to_adopt) {
  DEBUG_PRINT("Token: %d:%s\n", tag, str_to_adopt);
  struct Node *n = node_alloc(tag);
  n->str = str_to_adopt;
  return n;
}

struct Node *node_alloc_ival(int tag, long ival) {
  struct Node *n = node_alloc(tag);
  n->ival = ival;
  return n;
}

struct Node *node_build0(int tag) {
  DEBUG_PRINT("Node0: %d\n", tag);
  return node_buildn(tag, NULL);
}

struct Node *node_build1(int tag, struct Node *child1) {
  DEBUG_PRINT("Node1: %d\n", tag);
  return node_buildn(tag, child1, NULL);
}

struct Node *node_build2(int tag, struct Node *child1, struct Node *child2) {
  DEBUG_PRINT("Node2: %d\n", tag);
  return node_buildn(tag, child1, child2, NULL);
}

struct Node *node_build3(int tag, struct Node *child1, struct Node *child2, struct Node *child3) {
  DEBUG_PRINT("Node3: %d\n", tag);
  return node_buildn(tag, child1, child2, child3, NULL);
}

struct Node *node_build4(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4) {
  DEBUG_PRINT("Node4: %d\n", tag);
  return node_buildn(tag, child1, child2, child3, child4, NULL);
}

struct Node *node_build5(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5) {
  DEBUG_PRINT("Node5: %d\n", tag);
  return node_buildn(tag, child1, child2, child3, child4, child5, NULL);
}

struct Node *node_build6(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5, struct Node *child6) {
  DEBUG_PRINT("Node6: %d\n", tag);
  return node_buildn(tag, child1, child2, child3, child4, child5, child6, NULL);
}

struct Node *node_build7(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5, struct Node *child6,
                         struct Node *child7) {
  DEBUG_PRINT("Node7: %d\n", tag);
  return node_buildn(tag, child1, child2, child3, child4, child5, child6, child7, NULL);
}

struct Node *node_build8(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5, struct Node *child6,
                         struct Node *child7, struct Node *child8) {
  DEBUG_PRINT("Node8: %d\n", tag);
  return node_buildn(tag, child1, child2, child3, child4, child5, child6, child7, child8, NULL);
}

struct Node *node_buildn(int tag, ...) {
  va_list args;
  va_start(args, tag);
  struct Node *n = node_alloc(tag);
  int done = 0;
  while (!done) {
    struct Node *child = (struct Node *) va_arg(args, struct Node *);
    if (child) {
      node_add_kid(n, child);
    } else {
      done = 1;
    }
  }
  va_end(args);
  return n;
}

void node_destroy(struct Node *n) {
  free(n->kids);
  free(n->str);
  free(n);
}

void node_destroy_recursive(struct Node *n) {
  for (int i = 0; i < n->num_kids; i++) {
    if (n->kids[i]) {
      node_destroy_recursive(n->kids[i]);
    }
  }
  node_destroy(n);
}

int node_get_tag(struct Node *n) {
  return n->tag;
}

int node_get_num_kids(struct Node *n) {
  return n->num_kids;
}

void node_add_kid(struct Node *n, struct Node *kid) {
  if (n->num_kids >= n->capacity) {
    // grow kids array
    int grow_cap = n->capacity * 2;
    struct Node **a = malloc(sizeof(struct Node *) * grow_cap);
    for (int i = 0; i < n->num_kids; i++) {
      a[i] = n->kids[i];
    }
    free(n->kids);
    n->kids = a;
    n->capacity = grow_cap;
  }
  assert(n->capacity > n->num_kids);
  n->kids[n->num_kids++] = kid;
}

struct Node *node_get_kid(struct Node *n, int index) {
  assert(index >= 0);
  assert(index < n->num_kids);
  return n->kids[index];
}

int node_first_kid_has_tag(struct Node *n, int tag) {
  return n->num_kids > 0 && n->kids[0]->tag == tag;
}

void node_set_source_info(struct Node *n, struct SourceInfo source_info) {
  n->source_info = source_info;
}

struct SourceInfo node_get_source_info(struct Node *n) {
  return n->source_info;
}

const char *node_get_str(struct Node *n) {
  return n->str;
}

long node_get_ival(struct Node *n) {
  return n->ival;
}

void node_set_ival(struct Node *n, long ival) {
  n->ival = ival;
}
