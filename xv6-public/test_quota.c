#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid = getpid();
  char *ptr;

  printf(1, "Iniciando test de algoritmo de cuotas de memoria...\n");

  // 1. Set a small memory limit (100 KB = 102400 bytes)
  printf(1, "Estableciendo limite de memoria de 102400 bytes (25 paginas)...\n");
  if(setmemlimit(pid, 102400) < 0){
    printf(1, "Error estableciendo limite de memoria\n");
    exit();
  }

  // 2. Try to allocate 150 KB (38 pages). This should exceed the quota!
  printf(1, "Intentando reservar 153600 bytes (38 paginas) via sbrk...\n");
  ptr = sbrk(153600);
  if(ptr == (char*)-1){
    printf(1, "-> ERROR ESPERADO: sbrk fallo correctamente al sobrepasar el limite!\n");
  } else {
    printf(1, "-> ERROR: sbrk no debio haber reservado memoria!\n");
    sbrk(-153600); // Clean up
    exit();
  }

  // 3. Set a larger memory limit (300 KB = 307200 bytes)
  printf(1, "Estableciendo limite de memoria mas alto: 307200 bytes...\n");
  if(setmemlimit(pid, 307200) < 0){
    printf(1, "Error estableciendo limite de memoria alto\n");
    exit();
  }

  // 4. Try to allocate 150 KB again. This should now succeed!
  printf(1, "Intentando reservar 153600 bytes de nuevo...\n");
  ptr = sbrk(153600);
  if(ptr == (char*)-1){
    printf(1, "-> ERROR: sbrk fallo a pesar de que habia suficiente limite!\n");
  } else {
    printf(1, "-> EXITO: sbrk reservo memoria de forma exitosa bajo la nueva cuota!\n");
    // Clean up
    sbrk(-153600);
  }

  // 5. Reset limit to 0 (no limit)
  printf(1, "Quitando el limite de memoria (setmemlimit a 0)...\n");
  setmemlimit(pid, 0);

  printf(1, "Test de algoritmo de cuotas finalizado con exito.\n");
  exit();
}
