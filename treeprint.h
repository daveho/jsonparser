#ifndef TREEPRINT_H
#define TREEPRINT_H

#ifdef __cplusplus
extern "C" {
#endif

struct Node;

void treeprint(struct Node *root, const char *(*node_tag_to_str_fn)(int));

#ifdef __cplusplus
}
#endif

#endif // TREEPRINT_H
