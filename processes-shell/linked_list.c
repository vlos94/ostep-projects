#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

/*Add a new node to the front of a linked list*/
node* prepend (node* nodes, char* data) {
  node* new_node = malloc (sizeof (node));
  new_node->data = strdup (data);
  new_node->link = nodes;
  return new_node;
}

/*Free the linked list
  Assumes that the data in nodes is 
  heap-allocated*/
void free_nodes (node* nodes) {
  while (nodes) {
    node* tmp = nodes->link;
    free (nodes->data);
    free (nodes);
    nodes = tmp;
  }
}
