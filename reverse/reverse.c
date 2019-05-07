#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "linked_list.h"

bool same_inode (FILE* fp_1, FILE* fp_2);

int main (int argc, char* argv[argc + 1]) {
  FILE* src;
  FILE* dst;

  if (argc == 1) {
    src = stdin;
    dst = stdout;
  }
  
  else if (argc == 2) {
    src = fopen (argv[1], "r");
    if (src == NULL) {
      fprintf (stderr, "reverse: cannot open file '%s'\n", argv[1]);
      exit (EXIT_FAILURE);
    }
    dst = stdout;
  }
  
  else if (argc == 3) {
    if (strcmp (argv[1], argv[2]) == 0) {
      fprintf (stderr, "reverse: input and output file must differ\n");
      exit (EXIT_FAILURE);
    }
    src = fopen (argv[1], "r");
    dst = fopen (argv[2], "w");
    if (src == NULL) {
      if (dst)
	fclose (dst);
      fprintf (stderr, "reverse: cannot open file '%s'\n", argv[1]);
      exit (EXIT_FAILURE);
    }
    if (same_inode (src, dst)) {
      fprintf (stderr, "reverse: input and output file must differ\n");
      exit (EXIT_FAILURE);
    }
  }
  
  else {
    fprintf (stderr, "usage: reverse <input> <output>\n");
    exit (EXIT_FAILURE);
  }

  node* reversed_lines = process_file (src);
  write_nodes (dst, reversed_lines);
  free_nodes (reversed_lines);
  
  fclose (src);
  fclose (dst);  
  exit (EXIT_SUCCESS);

}

bool same_inode (FILE* fp_1, FILE* fp_2) {
  int fd_1 = fileno(fp_1);
  int fd_2 = fileno (fp_2);

  struct stat* buf_1 = malloc (sizeof (struct stat));
  struct stat* buf_2 = malloc (sizeof (struct stat));

  fstat (fd_1, buf_1);
  fstat (fd_2, buf_2);

  bool val = buf_1->st_ino == buf_2->st_ino;

  free (buf_1);
  free (buf_2);

  return val;
}



















  
