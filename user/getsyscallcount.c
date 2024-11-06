#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int num;

  if(argc < 2){ //εάν ο χρήστης δεν δώσει 2ο argument δλδ κάποιο path να δημιουργηθεί, 
                //τότε exit and print usage comment
                //(μετράει σαν 1ο argument το όνομα της συνάρτησης)
    printf(2, "Usage: get how many times a system call has run ...\n");
    exit();
  }

    int argument ;
  
    for(int i = 1; i < argc; i++){ 
      argument = atoi(argv[i]);
        if( num = getcount(argument) < 0 && argument != 0){
            printf(1, "Getting count failed...\n"); 
            break; 
        }
        printf(2, "The given system call has run %d times!\n", num);
  }
  exit();
}