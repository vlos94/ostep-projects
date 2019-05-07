#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include <assert.h>
/*
int main () {
  char** tokens_1 = parse_tokens ("A B C D E", " ");
  char* test_1[6] = {"A", "B", "C", "D", "E", NULL};
  size_t i;
  for (i = 0; i < 5; ++i)
    assert (strcmp (tokens_1[i], test_1[i]) == 0);
  assert (tokens_1[i] == test_1[i]);
  free_tokens (tokens_1);
  exit (EXIT_SUCCESS);
}
  
*/  
/*Count tokens in s that are delimted by the 
  chars in delim*/
size_t count_tokens (char* s, char* delim) {
  char* t = strdup (s);
  char* cpy = t;
  size_t count = 0;
  char* w;
  while ((w = strsep (&t, delim)))
    if (w[0] != '\0')
      ++count;
  free (cpy);
  return count;
}

/*Save the tokens into a null terminated array*/
char** parse_tokens (char* s, char* delim) {
  size_t count = count_tokens (s, delim);
  char** tokens = malloc (sizeof (char*) * (1 + count));
  char* t = strdup (s);
  char* cpy = t;
  char* w;
  size_t offset = 0;
  while ((w = strsep (&t, delim)))
    if (w[0] != '\0')
      tokens[offset++] = strdup (w);
  tokens[offset] = NULL;
  free(cpy);
  return tokens;
}

/*Free array of tokens
  First the strings
  Then the array of string*/
void free_tokens (char** tokens) {
  if (!tokens)
    return;
  size_t offset = 0;
  while (tokens[offset])
    free (tokens[offset++]);
  free (tokens);
}




