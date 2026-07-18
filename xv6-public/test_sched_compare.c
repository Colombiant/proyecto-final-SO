#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1, pid2, pid3;

  printf(1, "Iniciando test de comparacion de planificacion...\n");

  pid1 = fork();
  if(pid1 == 0){
    volatile int i;
    for(i = 0; i < 50000000; i++) {
      if(i % 10000000 == 0) {
        printf(1, "Hijo 1 (Bajo RR) trabajando...\n");
      }
    }
    printf(1, "Hijo 1 Terminado!\n");
    exit();
  }

  pid2 = fork();
  if(pid2 == 0){
    volatile int i;
    for(i = 0; i < 50000000; i++) {
      if(i % 10000000 == 0) {
        printf(1, "Hijo 2 (Bajo RR) trabajando...\n");
      }
    }
    printf(1, "Hijo 2 Terminado!\n");
    exit();
  }

  pid3 = fork();
  if(pid3 == 0){
    volatile int i;
    for(i = 0; i < 50000000; i++) {
      if(i % 10000000 == 0) {
        printf(1, "Hijo 3 (Bajo RR) trabajando...\n");
      }
    }
    printf(1, "Hijo 3 Terminado!\n");
    exit();
  }

  wait();
  wait();
  wait();
  printf(1, "Test finalizado.\n");
  exit();
}
