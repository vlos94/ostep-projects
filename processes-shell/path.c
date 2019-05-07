#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "path.h"

char* make_full_path(char* path, char* file_name) {
  size_t length_p = strlen (path);
  size_t length_f = strlen (file_name);
  char* full_path = malloc (sizeof (char) * (2 + length_f + length_p));
  memcpy (full_path, path, length_p);
  full_path[length_p] = '/';
  memcpy (full_path+length_p+1, file_name, length_f);
  full_path[1+length_f+length_p] = '\0';
  return full_path;
}

char* find_path (node* path, char* file_name) {
  node* tmp = path;
  while (tmp) {
    char* full_path = make_full_path (tmp->data, file_name);
    if (access (full_path, X_OK) == 0)
      return full_path;
    else {
      free (full_path);
      tmp = tmp->link;
    }
  }
  return NULL;
}



