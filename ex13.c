#include <stdio.h>
#include <string.h>
#include <assert.h>

int main (int argc, char * argv[])
{
  char * c;

  if (argc != 2) {
    printf("usage: %s token\n", argv[0]);
    return 1;
  }
  
  assert(strlen(argv[1]) > 0);     /* arg[1] is nonempty string */
  c = argv[1];                     /* preserve argv[1] */
  do {
    switch (*c) {
    case 'a':
    case 'A':
      printf("> %c\n", *c);
      break;
    case 'e':
    case 'E':
      printf("> %c\n", *c);
      break;
    case 'i':
    case 'I':
      printf("> %c\n", *c);
      break;
    case 'o':
    case 'O':
      printf("> %c\n", *c);
      break;
    case 'u':
    case 'U':
      printf("> %c\n", *c);
      break;
    default:
      ;
    }
  } while (*++c);

  return 0;
}
