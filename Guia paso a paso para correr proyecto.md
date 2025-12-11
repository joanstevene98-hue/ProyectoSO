# Guía paso a paso para correr el proyecto

Esta guía explica cómo compilar el proyecto C++ (CMake) en Windows y cómo ejecutar los binarios y tests.

---

## Requisitos previos

1. Tener `cmake` en `PATH` (versión >= 3.15).
2. Un compilador C++ instalado:
   - MSVC / Visual Studio (recomendado en Windows) **o**
   - MinGW / MSYS2 (alternativa)
3. Opcional: `ctest` (se instala con CMake) y `git` para control de versiones.

# Guía completa: compilar y ejecutar el proyecto + tests


- Ejecutar todos los tests con `ctest` y ejecutar tests individualmente.

Resumen rápido (comandos clave)
- Generar (configurar):
```powershell
cmake -S cpp_os_simulator -B cpp_os_simulator/build
```
- Compilar (Release):
```powershell
cmake --build cpp_os_simulator/build --config Release
```
- Ejecutar todos los tests:
```powershell
cd cpp_os_simulator\build
ctest -C Release --output-on-failure
```

Requisitos
- `cmake` en `PATH`.
- Compilador: Visual Studio (MSVC) recomendado o MinGW/MSYS2.
- `git` si quieres clonar/actualizar desde remoto.

1) Preparar la terminal
- Si usas MSVC: abre "x64 Native Tools Command Prompt for VS".
- Si usas MinGW/MSYS2: abre la terminal MinGW apropiada.

2) Generar la configuración de build
```powershell
cmake -S cpp_os_simulator -B cpp_os_simulator/build
```
- Notas:
   - En Windows con Visual Studio, CMake detecta automáticamente MSVC.
   - Si quieres usar MinGW explícitamente:
      ```powershell
      cmake -S cpp_os_simulator -B cpp_os_simulator/build -G "MinGW Makefiles"
      ```

3) Compilar
```powershell
cmake --build cpp_os_simulator/build --config Release
```
- Para compiladores de una sola configuración (Ninja), puedes usar `-DCMAKE_BUILD_TYPE=Release` al generar.

4) Dónde quedan los ejecutables
- MSVC (multi-config): `cpp_os_simulator/build/Release/<nombre>.exe` o `.../Debug/`.
- MinGW (single-config): `cpp_os_simulator/build/<nombre>.exe`.
- Ejecutables relevantes (definidos en `CMakeLists.txt`):
   - `os_simulator_kernel`
   - `os_simulator_scheduler`
   - `os_simulator_memory`
   - `os_simulator_files`

5) Ejecutar un binario (ejemplo: demo de memoria)
```powershell
# MSVC (Release)
.\cpp_os_simulator\build\Release\os_simulator_memory.exe

# MinGW
.\cpp_os_simulator\build\os_simulator_memory.exe
```

6) Ejecutar tests con CTest (todos)
- Desde la carpeta `cpp_os_simulator/build`:
```powershell
cd cpp_os_simulator\build
ctest -C Release --output-on-failure
```
- Para salida más detallada (verbose):
```powershell
ctest -C Release -V
```

7) Ejecutar tests individuales
- Los tests registrados en CMake son (nombres):
   - `PCB_Tests`
   - `Memory_Tests`
   - `Filesystem_Tests`
   - `Scheduler_Tests`
   - `Integration_Tests`

- Ejecutar por nombre (regex):
```powershell
# Ejecuta solo los tests cuyo nombre coincide con "PCB_Tests"
ctest -R PCB_Tests -C Release --output-on-failure
```

- Ejecutar directamente el ejecutable de test (útil para ver prints y asserts):
```powershell
# MSVC (Release)
.\cpp_os_simulator\build\Release\test_memory.exe

# MinGW
.\cpp_os_simulator\build\test_memory.exe
```
   - Si ejecutas el binario directamente verás los `std::cout` impresos y, en caso de `assert` fallido, el proceso terminará con código distinto de 0.

8) Qué esperar (salida y resultados)
- Tests del repositorio imprimen mensajes como `[TEST PASS] ...` y terminan con `return 0` si todo pasó.
- Si un `assert` falla, el ejecutable normalmente aborta y devuelve un código de salida distinto de 0; `ctest` marcará ese test como fallido.
- `ctest --output-on-failure` mostrará la salida del test que falló.

9) Ejecutar tests de integración (pueden imprimir más y tardar más):
```powershell
ctest -R Integration_Tests -C Release --output-on-failure
```

10) Comandos útiles adicionales
- Ejecutar todos los tests con tempo (verbose):
```powershell
ctest -C Release -V --output-on-failure
```
- Ejecutar el objetivo `test` con CMake (equivalente a `ctest`):
```powershell
cmake --build cpp_os_simulator/build --config Release --target test
```
- Limpiar el build (recomendado si cambias generador):
```powershell
rd /s /q cpp_os_simulator\build
```
   (o borra la carpeta con el explorador)

11) Depuración de fallos en tests
- Si un test falla por `assert`, haz lo siguiente:
   1. Ejecuta el ejecutable del test directamente para ver mensajes previos.
   2. Si necesitas trazar, compila en `Debug`:
       ```powershell
       cmake -S cpp_os_simulator -B cpp_os_simulator/build-debug -DCMAKE_BUILD_TYPE=Debug
       cmake --build cpp_os_simulator/build-debug --config Debug
       ```
   3. Ejecuta el test en un depurador (Visual Studio o `gdb` en MinGW) para ver la línea exacta del fallo.

12) Problemas comunes y soluciones rápidas
- `cmake` no encontrado: instala CMake y reinicia la terminal.
- `cl.exe` no reconocido: abre "x64 Native Tools Command Prompt" o instala Visual Studio Build Tools.
- Errores por includes: comprueba que `target_include_directories` en `CMakeLists.txt` apunta a `include/` (ya está configurado).
- `ctest` no encuentra tests: confirma que los ejecutables de test existen en la carpeta `build`.

13) Lista de ejecutables de tests (rutas esperadas)
- `test_pcb` -> `cpp_os_simulator/build[/Release]/test_pcb.exe`
- `test_memory` -> `cpp_os_simulator/build[/Release]/test_memory.exe`
- `test_filesystem` -> `cpp_os_simulator/build[/Release]/test_filesystem.exe`
- `test_schedulers` -> `cpp_os_simulator/build[/Release]/test_schedulers.exe`
- `test_integration` -> `cpp_os_simulator/build[/Release]/test_integration.exe`

14) ¿Quieres que haga commit y push?
- Puedo añadir este archivo al repo, hacer `git commit` y `git push` al remoto `origin/main`. Dime si lo hace ahora.

Fin de la guía extendida.
