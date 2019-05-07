struct node {
  char* data;
  size_t bytes;
  struct node* link;
};

typedef struct node node;

node* make_node (void);

node* prepend_data (node*,  char*, size_t);

node* process_file (FILE*);

void write_nodes (FILE*, node*);

void free_nodes (node*);




