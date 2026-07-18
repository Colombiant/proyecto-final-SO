# Planificador por Prioridad y Algoritmo de Cuotas de Memoria en xv6

Este repositorio contiene el proyecto final de Sistemas Operativos. Consiste en la implementación de características avanzadas de planificación de CPU y control de memoria física sobre el núcleo académico **xv6 (arquitectura x86)**.

El proyecto está diseñado para ejecutarse libre de dependencias locales a través de **Docker** y **QEMU**, garantizando portabilidad entre Linux, macOS y Windows.

---

## Estructura del Proyecto

*   `xv6-public/`: Código fuente modificado de xv6 (incluye el planificador por prioridad, llamadas de memoria `freemem()` y `setmemlimit()`, y programas de prueba).
*   `xv6-original/`: Código fuente original e intacto de xv6, utilizado para realizar comparaciones de comportamiento (ej. Round Robin).
*   `Dockerfile`: Definición del contenedor Docker con GCC-multilib (32-bits) y QEMU-nox preinstalados.
*   `INFORME.pdf`: Informe final del proyecto.
---

## Requisitos de Ejecución

Solo necesitas tener instalado:
*   [Docker Desktop](https://www.docker.com/products/docker-desktop/) (activo en tu máquina).

---

## Instrucciones de Uso (Paso a Paso)

### 1. Construir la Imagen del Entorno (Solo una vez)
Abre una terminal en el directorio raíz de este proyecto y construye el contenedor de compilación y ejecución:
```bash
docker build -t xv6-env .
```

### 2. Ejecutar la Versión Modificada (xv6-public)
Compila y arranca la consola de la versión modificada con QEMU-nox:
```bash
docker run -it --rm -v "${PWD}/xv6-public:/usr/src/xv6" xv6-env sh -c "make clean && make fs.img && make qemu-nox"
```

### 3. Ejecutar la Versión Original (xv6-original)
Para evaluar comparativas, puedes iniciar la base de xv6 stock sin modificaciones:
```bash
docker run -it --rm -v "${PWD}/xv6-original:/usr/src/xv6" xv6-env sh -c "make clean && make fs.img && make qemu-nox"
```

*(Nota: Para salir del emulador QEMU en cualquier momento, presiona combinadamente `Ctrl + A` y luego pulsa la tecla `X`).*

---

## Pruebas Unitarias Incluidas

Una vez que el indicador del shell de xv6 esté activo (`$`), puedes correr los siguientes programas de verificación:

### 1. Prueba de Prioridades (`test_priority`)
Ejecuta tres procesos hijos concurrentes con prioridades asignadas dinámicamente (`1` Alta, `5` Media, `9` Baja).
*   **Comando**: `test_priority`
*   **Resultado esperado**: Los procesos finalizan secuencialmente en orden estricto de prioridad (primero el hijo prioritario 1, luego 5 y al final 9) sin alternancia de CPU.

### 2. Prueba de Consumo de RAM (`test_mem`)
Realiza la llamada de sistema `freemem()` para auditar la memoria física disponible en bytes antes, durante y después de la asignación y liberación de memoria.
*   **Comando**: `test_mem`
*   **Resultado esperado**: Al solicitar bytes con `sbrk()`, se observa una deducción exacta de la RAM libre, la cual es restaurada al $100\%$ tras liberar el bloque.

### 3. Prueba Comparativa de Planificadores (`test_sched_compare`)
Corre un bucle computacional concurrente idéntico entre 3 hijos con la prioridad predeterminada por defecto ($10$).
*   **Comando**: `test_sched_compare`
*   **Resultado esperado**: Muestra un comportamiento intercalado equitativo (Round Robin). Al correr este comando en ambas versiones del sistema operativo (`xv6-original` y `xv6-public`), se valida que nuestro planificador conserva justicia distributiva cuando no se alteran las prioridades de forma explícita.

### 4. Prueba del Algoritmo de Cuotas (`test_quota`)
Fija una cuota artificial de memoria máxima por proceso usando `setmemlimit()` para ensayar el comportamiento del algoritmo limitador.
*   **Comando**: `test_quota`
*   **Resultado esperado**: Al rebasar la cuota de 100 KB asignada, `sbrk()` es anulada devolviendo `-1`. Tras elevar la cuota de seguridad a 300 KB, el growth se concreta sin problemas.

---

## Autores y Créditos

*   **Estudiante**: William David Hernández Solarte
*   **Código**: 2228934
*   **Universidad**: Universidad del Valle - Plan de Ingeniería de Sistemas
*   **Asignatura**: Sistemas Operativos (2026)
*   **Profesor**: Jeferson Amado Peña

---

## 📚 Referencias y Código Base

Este proyecto es una bifurcación con propósitos educativos de la base x86 de:
*   **Código Base de xv6**: Desarrollado originalmente por el [MIT PDOS Group](https://github.com/mit-pdos/xv6-public).
*   **Recurso de Apoyo**: Estructuras basadas en el repositorio docente [learn-xv6](https://github.com/nbicocchi/learn-xv6) de Nicola Bicocchi.
