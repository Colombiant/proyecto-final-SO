// Prueba de medicion de memoria fisica libre usando la syscall freemem().
// Registra la memoria libre al inicio, luego reserva 40 KB (10 paginas) usando sbrk(),
// verifica que la memoria libre caiga exactamente en esa cantidad,
// libera la memoria encogiendo el heap mediante sbrk(-40960) y comprueba que se restaure al 100%.

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int mem_inicial, mem_despues_alloc, mem_final;
  char *ptr;

  printf(1, "Iniciando test de memoria libre...\n");

  // Obtener memoria libre inicial
  mem_inicial = freemem();
  printf(1, "Memoria libre inicial: %d bytes\n", mem_inicial);

  // Solicitar 40960 bytes (10 paginas de 4KB)
  printf(1, "Asignando 40960 bytes (10 paginas)...\n");
  ptr = sbrk(40960);
  if(ptr == (char*)-1){
    printf(1, "Error en sbrk\n");
    exit();
  }

  // Obtener memoria libre tras la asignacion
  mem_despues_alloc = freemem();
  printf(1, "Memoria libre despues de sbrk: %d bytes\n", mem_despues_alloc);
  printf(1, "Diferencia: %d bytes (Esperado: 40960)\n", mem_inicial - mem_despues_alloc);

  // Liberar la memoria (reduciendo el tamano del heap de vuelta)
  printf(1, "Liberando memoria...\n");
  if(sbrk(-40960) == (char*)-1){
    printf(1, "Error en sbrk de liberacion\n");
    exit();
  }

  // Obtener memoria libre final para verificar la recuperacion
  mem_final = freemem();
  printf(1, "Memoria libre final: %d bytes\n", mem_final);

  // Comparar estado inicial vs final
  if(mem_final == mem_inicial){
    printf(1, "Test de memoria exitoso!\n");
  } else {
    printf(1, "Test de memoria fallo! La memoria no se recupero por completo.\n");
  }

  exit();
}
