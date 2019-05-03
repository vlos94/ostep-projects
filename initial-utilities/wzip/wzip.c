#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void wzip (FILE*, char*, int*);
void encode (char*, int*);

int main (int argc, char* argv[argc + 1]) {
  
  if (argc == 1) {
    fprintf (stdout, "wzip: file1 [file2 ...]\n");
    exit (EXIT_FAILURE);
  }
  int* count = malloc (sizeof (int));
  char* c = malloc (sizeof (char));
  
  for (size_t i = 1; i < argc; ++i) {
    
    FILE* fp = fopen (argv [i], "r");
    wzip (fp, c, count);
    fclose (fp);
  }
  /*Last values are never written since
    the write is delayed until
    a mismatch is encountered.
    So write them after
    the for loop*/
  encode (c, count);
  free (c);
  free (count);
}


/*write encoded data to the stdout*/
void encode (char* c, int* count) {
  if (*count == 0)
    return;
  fwrite (count, sizeof (int), 1, stdout);
  fwrite (c, sizeof (char), 1, stdout);
}

/*Compress one file, writing to compressed file to stdout*/
void wzip (FILE* fp, char* last_char, int* last_count) {
  
  int curr_count = *last_count;
  char curr_char = *last_char;
  
  char* buf = NULL;
  size_t len = 0;
  
  while (getline (&buf, &len, fp) != -1) {
    size_t iterations = strlen (buf);
    for (size_t i = 0; i < iterations; ++i) {
      if (buf[i] == curr_char)
	++curr_count;
      else {
	encode (&curr_char, &curr_count);
	curr_char = buf[i];
	curr_count = 1;
      }
    }
    free (buf);
    buf = NULL;
  }
  *last_count = curr_count;
  *last_char = curr_char;
}








