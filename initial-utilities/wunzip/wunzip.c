#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int* count;
  char* c;
  char padding[3];
} my_struct_t;

void decode (my_struct_t*);
void wunzip (FILE*);

int main (int argc, char* argv[argc + 1]) {
  
  if (argc == 1) {
    fprintf (stdout, "wunzip: file1 [file2 ...]\n");
    exit (EXIT_FAILURE);
  }
  
  for (size_t i = 1; i < argc; ++i) {
    FILE* fp = fopen (argv[i], "r");
    wunzip (fp);
    fclose (fp);
  }
  exit (EXIT_SUCCESS);
}

void decode (my_struct_t* data) {
  if (!(*data->count))
    return;
  char* buf = malloc (sizeof (char) * (*data->count));
  memset (buf, *data->c, (size_t)(*data->count));
  fwrite (buf, sizeof (char), (size_t)(*data->count), stdout);
  free (buf);
}

void wunzip (FILE* fp) {
  size_t read;
  my_struct_t* data = malloc (sizeof (my_struct_t));
  memset (data->padding, 0, 3);
  void* buf = malloc (1000);
  while ((read = fread (buf, 1, 1000, fp)) != 0) {
    size_t offset = 0;
    while (offset < read) {
      data->count = (int*)(buf+offset);
      data->c = (char*)(buf+offset+4);
      decode (data);
      offset += 5;
    }
  }
  free (data);
  free (buf);
}
    

  
