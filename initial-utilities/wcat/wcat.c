#include <stdio.h>
#include <stdlib.h>

void cat (FILE* fp);

int main (int argc, char* argv[argc + 1]) {
  
  for (size_t i = 1; i < argc; ++i) {
    FILE* fp = fopen (argv[i], "r");
    if (!fp) {
      fprintf (stdout, "wcat: cannot open file\n");
      exit (EXIT_FAILURE);
    }
    
    cat (fp);
    fclose (fp);
  }  
  exit (EXIT_SUCCESS);
}

void cat (FILE* fp) {
  
  char* buf = NULL;
  size_t len = 0;
  
  while (getline (&buf, &len, fp) != -1) {
    fprintf (stdout, "%s", buf);
    free (buf);
    buf = NULL;
  }
}
