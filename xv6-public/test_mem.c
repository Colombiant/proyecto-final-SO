#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int mem_inicial, mem_despues_alloc, mem_final;
  char *ptr;

  printf(1, "Iniciando test de memoria libre...\n");

  // Get initial free memory
  mem_inicial = freemem();
  printf(1, "Memoria libre inicial: %d bytes\n", mem_inicial);

  // Allocate 40960 bytes (10 pages)
  printf(1, "Asignando 40960 bytes (10 paginas)...\n");
  ptr = sbrk(40960);
  if(ptr == (char*)-1){
    printf(1, "Error en sbrk\n");
    exit();
  }

  // Get free memory after allocation
  mem_despues_alloc = freemem();
  printf(1, "Memoria libre despues de sbrk: %d bytes\n", mem_despues_alloc);
  printf(1, "Diferencia: %d bytes (Esperado: 40960)\n", mem_inicial - mem_despues_alloc);

  // Deallocate (shrink heap)
  printf(1, "Liberando memoria...\n");
  if(sbrk(-40960) == (char*)-1){
    printf(1, "Error en sbrk de liberacion\n");
    exit();
  }

  // Get final free memory
  mem_final = freemem();
  printf(1, "Memoria libre final: %d bytes\n", mem_final);

  if(mem_final == mem_inicial){
    printf(1, "Test de memoria exitoso!\n");
  } else {
    printf(1, "Test de memoria fallo! La memoria no se recupero por completo.\n");
  }

  exit();
}
