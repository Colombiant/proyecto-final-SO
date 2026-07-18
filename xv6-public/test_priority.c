// Prueba de planificacion por prioridad en xv6.
// Crea tres procesos hijos concurrentes y les asigna prioridades distintas (1 Alta, 5 Media, 9 Baja).
// Los hijos hacen sleep(20) inicialmente para darle tiempo al proceso padre de configurar sus prioridades
// y luego ejecutan un bucle que consume CPU. Deben terminar estrictamente en orden de prioridad.

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1, pid2, pid3;

  printf(1, "Iniciando test de planificador por prioridad...\n");

  // Crear Hijo 1 y asignarle prioridad 9 (Baja)
  pid1 = fork();
  if(pid1 == 0){
    sleep(20); // Espera a que el padre defina todas las prioridades
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

  // Crear Hijo 2 y asignarle prioridad 5 (Media)
  pid2 = fork();
  if(pid2 == 0){
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

  // Crear Hijo 3 y asignarle prioridad 1 (Alta)
  pid3 = fork();
  if(pid3 == 0){
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

  // Esperar a que terminen los 3 procesos hijos
  wait();
  wait();
  wait();
  printf(1, "Test de planificador finalizado.\n");
  exit();
}
