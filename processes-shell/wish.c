#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "redir.h"
#include "parse.h"
#include "cmd.h"
#include "linked_list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
void error_msg (void);

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
  char* cmd = NULL;
  char* file_name = NULL;
  char** job_tokens = NULL;
  
  if (argc == 1)
    fprintf (stdout, "wish> ");
  while (getline (&buf, &len, stdin) != -1) {
    job_tokens = parse_tokens (buf, "&");
    size_t offset = 0;
    int status;
    while (job_tokens[offset]) {
      if (!valid_redirs (job_tokens[offset])) {
	error_msg();
	if (argc == 1)
	  fprintf (stdout, "wish> ");
	++offset;
	continue;
      }
      cmd = get_cmd (job_tokens[offset]);
      file_name = get_file_name (job_tokens[offset]);
      status = run_cmd (cmd, file_name, &path);
      if (status == -1)
	error_msg();
      else if (status == 1)
	break; 
    free (file_name);
    file_name = NULL;
    free (cmd);
    cmd = NULL;
    ++offset;
    }
    while (!((waitpid (-1, NULL, 0) == -1) && (errno == ECHILD)))
      ;
    if (status == 1)
      break;
    if (argc == 1)
      fprintf (stdout, "wish> ");
    free (buf);
    buf = NULL;
    free_tokens (job_tokens);
    job_tokens = NULL;
  }
  free_tokens (job_tokens);
  free_nodes (path);
  free (cmd);
  free (file_name);
  free (buf);
  exit (EXIT_SUCCESS);
}

void error_msg (void) {
  char* msg = "An error has occurred\n";
  fprintf (stderr, "%s",  msg);
}
