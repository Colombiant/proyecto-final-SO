// Prueba del algoritmo limitador de cuota de memoria (setmemlimit).
// 1. Establece un limite bajo de 100 KB para el proceso actual.
// 2. Intenta reservar 150 KB via sbrk(). Verifica que el kernel deniegue la operacion (retorne -1).
// 3. Eleva el limite de cuota a 300 KB.
// 4. Intenta reservar 150 KB de nuevo. Verifica que en esta ocasion si sea exitoso.
// 5. Restablece el limite a 0 (sin limite de memoria).

#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid = getpid();
  char *ptr;

  printf(1, "Iniciando test de algoritmo de cuotas de memoria...\n");

  // 1. Establecer cuota inicial baja (100 KB = 102400 bytes, unas 25 paginas)
  printf(1, "Estableciendo limite de memoria de 102400 bytes (25 paginas)...\n");
  if(setmemlimit(pid, 102400) < 0){
    printf(1, "Error estableciendo limite de memoria\n");
    exit();
  }

  // 2. Intentar solicitar 150 KB. Debe fallar porque supera los 100 KB limits.
  printf(1, "Intentando reservar 153600 bytes (38 paginas) via sbrk...\n");
  ptr = sbrk(153600);
  if(ptr == (char*)-1){
    printf(1, "-> ERROR ESPERADO: sbrk fallo correctamente al sobrepasar el limite!\n");
  } else {
    printf(1, "-> ERROR: sbrk no debio haber reservado memoria!\n");
    sbrk(-153600); // Limpiar en caso de fallo
    exit();
  }

  // 3. Subir la cuota de memoria a 300 KB (= 307200 bytes)
  printf(1, "Estableciendo limite de memoria mas alto: 307200 bytes...\n");
  if(setmemlimit(pid, 307200) < 0){
    printf(1, "Error estableciendo limite de memoria alto\n");
    exit();
  }

  // 4. Volver a intentar solicitar los 150 KB. Ahora debe funcionar.
  printf(1, "Intentando reservar 153600 bytes de nuevo...\n");
  ptr = sbrk(153600);
  if(ptr == (char*)-1){
    printf(1, "-> ERROR: sbrk fallo a pesar de que habia suficiente limite!\n");
  } else {
    printf(1, "-> EXITO: sbrk reservo memoria de forma exitosa bajo la nueva cuota!\n");
    sbrk(-153600); // Limpiar memoria solicitada
  }

  // 5. Restablecer el limite a 0 (desactivado)
  printf(1, "Quitando el limite de memoria (setmemlimit a 0)...\n");
  setmemlimit(pid, 0);

  printf(1, "Test de algoritmo de cuotas finalizado con exito.\n");
  exit();
}
