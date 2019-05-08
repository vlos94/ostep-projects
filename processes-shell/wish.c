#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "errors.h"
#include "job.h"
#include "linked_list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char* argv[argc + 1]) {
  if (argc > 2) {
    error_msg();
    exit (EXIT_FAILURE);
  }
  else if (argc == 2) {
    int fd = open (argv[1], O_RDONLY);
    if (fd == -1) {
      error_msg();
      exit (EXIT_FAILURE);
    }
    dup2 (fd, STDIN_FILENO);
    stdin = fdopen (STDIN_FILENO, "r");
  }

  char* buf = NULL;
  size_t len = 0;
  node* path = prepend (NULL, "/bin");
  
  if (argc == 1)
    fprintf (stdout, "wish> ");
  while (getline (&buf, &len, stdin) != -1) {
    int status = run_job (buf, &path);
    while (!((waitpid (-1, NULL, 0) == -1) && (errno == ECHILD)))
      ;
    if (status == 1)
      break;
    if (argc == 1)
      fprintf (stdout, "wish> ");
    free (buf);
    buf = NULL;
  }

  free_nodes (path);
  free (buf);
  exit (EXIT_SUCCESS);
}


