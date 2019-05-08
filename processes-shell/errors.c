#include "errors.h"
#include "stdio.h"

void error_msg (void) {
  char* msg = "An error has occurred\n";
  fprintf (stderr, "%s",  msg);
}
