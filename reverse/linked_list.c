#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char* data;
  size_t bytes;
  struct node* link;
};

typedef struct node node;

node* make_node (void) {
  node* n = malloc (sizeof (node));
  n->data = NULL;
  n->bytes = 0;
  n->link = NULL;
  return n;
}

node* prepend_data (node* head, char* data, size_t bytes) {
  node* new_head = make_node();
  char* buf = malloc (sizeof (char) * (1 + bytes));
  memset (buf+bytes, '\0', 1);
  memcpy (buf, data, bytes);
  new_head->data = buf;
  new_head->bytes = bytes;
  new_head->link = head;
  return new_head;
}

node* process_file (FILE* src) {
  node* n = NULL;
  char* buf = NULL;
  size_t len = 0;
  size_t read;
  while ((read = getline (&buf, &len, src)) != -1) {
    n = prepend_data (n, buf, read);
    free (buf);
    buf = NULL;
  }
  return n;
}

void write_nodes (FILE*dst, node* n) {
  while (n) {
    fprintf (dst, "%s", n->data);
    n = n->link;
  }
}

void free_nodes (node* n) {
  node* tmp;
  while (n) {
    tmp = n->link;
    free (n->data);
    free (n);
    n = tmp;
  }
}
/*
int main (int argc, char* argv[argc + 1]) {
  
  FILE* fp = fopen (argv[1], "r");
  
  node* n = process_file (fp);
  
  write_nodes (stdout, n);
  
  free_nodes (n);
  
  exit (EXIT_FAILURE);
}
*/
