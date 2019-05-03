#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void grep (FILE*,  char*);

int main (int argc, char* argv[argc+1]) {
  
  if (argc == 1) {
    fprintf (stdout, "wgrep: searchterm [file ...]\n");
    exit (EXIT_FAILURE);
  }
  
  char* search_term = argv[1];
   
  /* No input files means read from the stdin */
  if (argc == 2) {
    grep (stdin, search_term);
    exit (EXIT_SUCCESS);
  }
  
  for (size_t k = 2; k < argc; ++k) {
    FILE* fp = fopen (argv[k], "r");
    if (fp == NULL) {
      fprintf (stdout,  "wgrep: cannot open file\n");
      exit (EXIT_FAILURE);
    }
    grep (fp, search_term);
    fclose (fp);
  }
  
  exit (EXIT_SUCCESS);
}
  
/*Go over file line by line. Print to stdout those 
  lines that contain the search term*/
void grep (FILE* fp, char* search_term) {
  char* buf = NULL;
  size_t len = 0;
  ssize_t read;

   
  while ((read = getline (&buf, &len, fp)) > 0) {
    if (strstr (buf, search_term))
      fprintf (stdout, "%s", buf);
    free (buf);
    buf = NULL;
  }
}






      
      
