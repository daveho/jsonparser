#ifndef NODE_H
#define NODE_H

// Node datatype and functions

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Source information structure.
struct SourceInfo {
  const char *filename;
  int line, col;
};

struct Node;

// Create Node with specified tag.
struct Node *node_alloc(int tag);

// Create a node with a string value by copying a specified string.
struct Node *node_alloc_str_copy(int tag, const char *str_to_copy);

// Create a node with a string value by adopting specific string,
// which will be freed when the Node is destroyed.
struct Node *node_alloc_str_adopt(int tag, char *str_to_adopt);

// Create a node with a given integer value.
struct Node *node_alloc_ival(int tag, long ival);

// Convenience functions to create a Node with specified tag value
// and pointers to children.
struct Node *node_build0(int tag);
struct Node *node_build1(int tag, struct Node *child1);
struct Node *node_build2(int tag, struct Node *child1, struct Node *child2);
struct Node *node_build3(int tag, struct Node *child1, struct Node *child2, struct Node *child3);
struct Node *node_build4(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4);
struct Node *node_build5(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5);
struct Node *node_build6(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5, struct Node *child6);
struct Node *node_build7(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5, struct Node *child6,
                         struct Node *child7);
struct Node *node_build8(int tag,
                         struct Node *child1, struct Node *child2, struct Node *child3,
                         struct Node *child4, struct Node *child5, struct Node *child6,
                         struct Node *child7, struct Node *child8);

// Create a Node with specified tag and arbitrary pointers to children.
// The sequence of child pointers should be terminated with a null pointer.
struct Node *node_buildn(int tag, ...);

// Destroy a Node.
void node_destroy(struct Node *n);

// Recursively destroy a tree of Nodes.
void node_destroy_recursive(struct Node *n);

// Get a Node's tag.
int node_get_tag(struct Node *n);

// Get the number of children of a Node.
int node_get_num_kids(struct Node *n);

// Append a child Node.
void node_add_kid(struct Node *n, struct Node *kid);

// Get a child Node (index 0 is the first child.)
struct Node *node_get_kid(struct Node *n, int index);
int node_first_kid_has_tag(struct Node *n, int tag);

// Set the SourceInfo for a Node.
void node_set_source_info(struct Node *n, struct SourceInfo source_info);

// Get the SoureeInfo for a Node.
struct SourceInfo node_get_source_info(struct Node *n);

// Get the string value of a Node.
const char *node_get_str(struct Node *n);

// Get integer value of a Node.
long node_get_ival(struct Node *n);

// Set integer value of a Node.
void node_set_ival(struct Node *n, long ival);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // NODE_H
