#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "parse.h"
#include "path.h"
#include "cmd.h"

static int free_and_return (char**, int);

/*Function will return:
  0 for OK
  -1 for ERROR
  1 for EXIT */
int run_cmd (char* cmd, char* file_name, node** curr_path) {
  char** tokens = parse_tokens (cmd, "\t\n ");
  if (tokens[0] == NULL)
    return free_and_return (tokens, 0);
  node* path = *curr_path;
  if (strcmp (tokens[0], "exit") == 0) {
    if ((tokens[1] != NULL) || file_name )
      return free_and_return (tokens, -1);
    else 
      return free_and_return (tokens, 1);
  }
  else if (strcmp (tokens[0], "cd") == 0) {
    if ((tokens[1] == NULL) || (tokens[2] != NULL) || file_name)
      return free_and_return (tokens, -1);
    else {
      if (chdir (tokens[1]) == 0)
	return free_and_return (tokens, 0);
      else
	return free_and_return (tokens, -1);
    }
  }
  else if (strcmp (tokens[0], "path") == 0) {
    if (file_name)
      return free_and_return (tokens, -1);
    free_nodes (path);
    path = NULL;
    size_t offset = 0;
    while (tokens[++offset])
      path = prepend (path, tokens[offset]);
    *curr_path = path;
    return free_and_return (tokens, 0);
  }
  else {
    char* full_path = find_path (path, tokens[0]);
    if (full_path == NULL)
      return free_and_return (tokens, -1);
    pid_t pid = fork();
    if (pid == 0) {
      int fd;
      if (file_name) {
	fd = open (file_name, O_TRUNC | O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
	dup2 (fd, STDOUT_FILENO);
	stdout = fdopen (STDOUT_FILENO, "w");
	dup2 (fd, STDERR_FILENO);
        stdout = fdopen (STDERR_FILENO, "w");
      }
      execv (full_path, tokens);
    }
    else
      free (full_path);
    return free_and_return (tokens, 0);
  }
}

				    

static int free_and_return (char** tokens, int ret) {
  free_tokens (tokens);
  return ret;
}
  
  
