#include <stdio.h>
#include "node.h"
#include "treeprint.h"

#define MAX_DEPTH 4096

struct TreePrintContext {
  int stack_depth;
  int index[MAX_DEPTH];
  int nsibs[MAX_DEPTH];
};

static void pushctx(struct TreePrintContext *ctx, int nsibs) {
  int level = ctx->stack_depth;
  ctx->index[level] = 0;
  ctx->nsibs[level] = nsibs;
  ctx->stack_depth++;
}

static void popctx(struct TreePrintContext *ctx) {
  ctx->stack_depth--;
}

static void print_node(struct Node *n, struct TreePrintContext *ctx, const char *(*node_tag_to_str_fn)(int)) {
  int depth = ctx->stack_depth;
  for (int i = 1; i < depth; i++) {
    if (i == depth-1) {
      printf("+--");
    } else {
      int level_index = ctx->index[i];
      int level_nsibs = ctx->nsibs[i];
      if (level_index < level_nsibs) {
        printf("|  ");
      } else {
        printf("   ");
      }
    }
  }

  int tag = node_get_tag(n);
  const char *str = node_get_str(n);

  printf("%s", node_tag_to_str_fn(tag));
  if (str) {
    printf("[%s]", str);
  }
  printf("\n");
  ctx->index[depth-1]++;

  int nkids = node_get_num_kids(n);
  pushctx(ctx, nkids);
  for (int i = 0; i < nkids; i++) {
    print_node(node_get_kid(n, i), ctx, node_tag_to_str_fn);
  }
  popctx(ctx);
}

void treeprint(struct Node *root, const char *(*node_tag_to_str_fn)(int)) {
  struct TreePrintContext ctx;
  ctx.stack_depth = 0;
  pushctx(&ctx, 1);
  print_node(root, &ctx, node_tag_to_str_fn);
}
