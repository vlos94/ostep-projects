#include <stdlib.h>
#include "parse.h"
#include "redir.h"
#include "cmd.h"
#include "path.h"
#include "errors.h"
/*Run jobs, ie a line entered to the shell
  A job is a line of cmds separated by &'s
  job ---> cmd_1 & ... & cmd_n 
  
  A return value of 0 will mean to
  keep looping for input
  A return value of 1 will mean exit*/


int run_job (char* input_line, node** path) {
  char** job_tokens = parse_tokens (input_line, "&");
  int status;
  size_t offset = 0;
  
  while (job_tokens[offset]) {
    if (!valid_redirs (job_tokens[offset])) {
      error_msg ();
      ++offset;
      continue;
    }
    char* cmd = get_cmd (job_tokens[offset]);
    char* file_name = get_file_name (job_tokens[offset]);
    status = run_cmd (cmd, file_name, path);
    if (status == 1) {
      free (cmd);
      free (file_name);
      free_tokens (job_tokens);
      return 1;
    }
    if (status == -1)
      error_msg();
    ++offset;
    free (cmd);
    free (file_name);
  }
  free_tokens (job_tokens);
  return 0;
}
  
    

