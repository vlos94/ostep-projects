#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node {
  char* data;
  struct node* link;
} node;

node* prepend (node*, char*);
void free_nodes (node*);
#endif
