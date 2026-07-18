#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1, pid2, pid3;

  printf(1, "Iniciando test de planificador por prioridad...\n");

  pid1 = fork();
  if(pid1 == 0){
    // Child 1 (Low priority)
    sleep(20); // Sleep to let parent set all priorities
    volatile int i;
    volatile int k = 0;
    for(i = 0; i < 80000000; i++){
      k += i;
    }
    printf(1, "Hijo 1 (Prioridad 9 - Baja) Terminado!\n");
    exit();
  } else if (pid1 > 0) {
    setpriority(pid1, 9);
  }

  pid2 = fork();
  if(pid2 == 0){
    // Child 2 (Medium priority)
    sleep(20);
    volatile int i;
    volatile int k = 0;
    for(i = 0; i < 80000000; i++){
      k += i;
    }
    printf(1, "Hijo 2 (Prioridad 5 - Media) Terminado!\n");
    exit();
  } else if (pid2 > 0) {
    setpriority(pid2, 5);
  }

  pid3 = fork();
  if(pid3 == 0){
    // Child 3 (High priority)
    sleep(20);
    volatile int i;
    volatile int k = 0;
    for(i = 0; i < 80000000; i++){
      k += i;
    }
    printf(1, "Hijo 3 (Prioridad 1 - Alta) Terminado!\n");
    exit();
  } else if (pid3 > 0) {
    setpriority(pid3, 1);
  }

  wait();
  wait();
  wait();
  printf(1, "Test de planificador finalizado.\n");
  exit();
}
