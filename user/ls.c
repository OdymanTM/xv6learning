#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;
  
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  
  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  
  int fd;  //

  struct dirent de;
      // struct dirent {
      //   ushort inum;  //identifier of an entry in a directory file or dir
      //   char name[DIRSIZ];  //it's name 
      // };



  struct stat st; //storage for a dir's or a file's detailed info
      //   struct stat {
        //   short type;  // Type of file
        //   int dev;     // File system's disk device
        //   uint ino;    // Inode number
        //   short nlink; // Number of links to file
        //   uint size;   // Size of file in bytes
        // };

  
  if((fd = open(path, 0)) < 0){  // check of the path is accessible 
    printf(2, "ls: cannot open %s\n", path);
    return;  
  }
  
  if(fstat(fd, &st) < 0){  //attemp to run fstat -> gather info about the given entry (file or dir)
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  
  switch(st.type){  //different cases for the case of a file or a directory entry
  case T_FILE:  //file case
    //fmtname returns the file name as shown in the path 
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);  
    //print file related data gathered by fstat above 
    break;
  
  case T_DIR:  //directory case
    //check if our buffer can fith 
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){  //DIRSIZ is defined as the max length of a file name (a dir is pactically a file)
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path); //load the path provided to our buffer 
    p = buf+strlen(buf); //set the p pointer of the buffer to point at the null terminator 
    *p++ = '/';  //change the value of the null terminator to '/' 
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit();
}
