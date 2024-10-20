#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){ //εάν ο χρήστης δεν δώσει 2ο argument δλδ κάποιο path να δημιουργηθεί, 
                //τότε exit and print usage comment
                //(μετράει σαν 1ο argument το όνομα της συνάρτησης)
    printf(2, "Usage: mkdir files...\n");
    exit();
  }

  for(i = 1; i < argc; i++){ //εάν ο χρήστης δώσει πάνω από ένα argument (path δλδ) 
                             //εκτέλεσε την mkdir system call για κάθε ένα από τα paths
    if(mkdir(argv[i]) < 0){
      printf(2, "mkdir: %s failed to create\n", argv[i]); //εάν η mkdir αποτύχει 
      break;  //σταμάτα την δημιουργία των paths μετά την πρώτη αποτυχία
    }
  }

  exit();
}