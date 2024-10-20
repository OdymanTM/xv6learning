#include "types.h"
#include "stat.h"
#include "user.h"



void stat_file(char *path) {
  struct stat st;
  //stat system call
  if (stat(path, &st) < 0) {  //εάν αποτύχει η stat return με error
    printf(2, "stat: cannot stat %s\n", path);
    return;
  }

  printf(1, "File: %s\n", path);
  printf(1, "Type: ");
  switch (st.type) {
    case T_FILE:
      printf(1, "regular file\n");
      break;
    case T_DIR:
      printf(1, "directory\n");
      break;
    default:
      printf(1, "unknown\n");
  }

  printf(1, "Inode: %d\n", st.ino);
  printf(1, "Size: %d bytes\n", st.size);
  printf(1, "Number of Links: %d\n", st.nlink);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(2, "Usage: stat <file>...\n"); //stat explanation
    exit();
  }

  for (int i = 1; i < argc; i++) {
    if(i>1){printf(2, "------\n");} //εκτύπωσε divider
    stat_file(argv[i]);
  }

  exit();
}