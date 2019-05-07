#include "redir.h"
#include <string.h>
#include "parse.h"

static size_t count_redirs (char* s) {
  size_t count = 0;
  for (size_t i = 0; i < strlen (s); ++i)
    if (s[i] == '>')
      ++count;
  return count;
}

bool valid_redirs (char* s) {
  size_t count = count_redirs (s);
  if (count > 1)
    return false;
  else if (count == 0)
    return true;
  
  if (count_tokens (s, ">") != 2)
    return false;
  char** file_tokens = parse_tokens (s, ">");
  if (count_tokens (file_tokens[1], "\t \n") != 1) {
    free_tokens (file_tokens);
    return false;
  }
  free_tokens (file_tokens);
  return 1;
}

char* get_file_name (char* s) {
  if (count_redirs (s) == 0)
    return NULL;
  char** file_tokens = parse_tokens (s, ">");
  char** token = parse_tokens (file_tokens[1], "\t\n ");
  char* file_name = strdup (token[0]);
  free_tokens (token);
  free_tokens (file_tokens);
  return file_name;
}

char* get_cmd (char* s) {
  char** file_tokens = parse_tokens (s, ">");
  char* cmd = strdup (file_tokens[0]);
  free_tokens (file_tokens);
  return cmd;
}






  
