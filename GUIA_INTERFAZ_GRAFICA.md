# 🖥️ INTERFAZ GRÁFICA DEL SIMULADOR DE MINI-KERNEL

## 📋 Descripción

Interfaz web interactiva completa que permite probar y visualizar todos los componentes del simulador de mini-kernel:

✅ **Gestión de Procesos (CPU Scheduling)**
✅ **Gestión de Memoria (First-Fit Algorithm)**
✅ **Gestión de Archivos (Sistema de Archivos)**
✅ **Gestión de E/S (Device Queues)**
✅ **Escenarios Integrados**

---

## 🚀 Cómo Usar

### 1. Abrir la Interfaz

**Opción 1: Doble clic en el archivo**
```
c:\Users\joans\Downloads\Proyecto So\INTERFAZ_SIMULADOR.html
```

**Opción 2: Desde navegador (Ctrl+O)**
- Abre tu navegador favorito (Chrome, Firefox, Edge, Safari)
- Presiona `Ctrl+O` (o Cmd+O en Mac)
- Navega a `INTERFAZ_SIMULADOR.html`

**Opción 3: Desde línea de comandos**
```bash
# Windows
start INTERFAZ_SIMULADOR.html

# Linux/Mac
open INTERFAZ_SIMULADOR.html
```

---

## 🎮 Guía de Uso por Componente

### ⚙️ Panel 1: Gestión de Procesos (CPU Scheduling)

#### Crear Procesos
1. Ingresa **Nombre del Proceso** (ej: P1, P2)
2. Ingresa **Tiempo de Ráfaga** (burst time en ms)
3. Selecciona **Planificador**:
   - **FIFO**: Procesos en orden de llegada (sin preemption)
   - **Round Robin**: Con quantum = 3 ms (con preemption)
4. Haz clic en **➕ Crear Proceso**

#### Ejecutar Procesos
1. Haz clic en **▶️ Ejecutar Cola**
2. Observa en tiempo real:
   - **Ready Queue**: Procesos esperando CPU
   - **Running**: Proceso actual en CPU
   - **Terminated**: Procesos finalizados

#### Estadísticas Mostradas
- **Total Procesos**: Cantidad creada
- **Context Switches**: Cambios de contexto
- **Turnaround Avg**: Tiempo promedio de finalización

**Ejemplo**:
```
1. Crear P1 (10ms)
2. Crear P2 (8ms)
3. Crear P3 (12ms)
4. Ejecutar con Round Robin
5. Ver cómo se intercalan los procesos
```

---

### 💾 Panel 2: Gestión de Memoria (First-Fit)

#### Asignar Memoria
1. Ingresa **Tamaño de Asignación** (1-32 bytes)
2. Ingresa **PID** a asignar (identificador de proceso)
3. Haz clic en **➕ Asignar Memoria**

#### Funciones Especiales
- **👁️ Visualizar Memoria**: Muestra dump actual
- **🔓 Liberar por PID**: Libera toda la memoria de un proceso
- **🔄 Compactar**: Desfragmenta la memoria

#### Indicadores
- **Bytes Usados**: Memoria en uso
- **Bytes Libres**: Memoria disponible
- **Fragmentación**: % de fragmentación

#### Visualización
```
Heap: [1111222..333.........]
      └─ PID 1 ┘ PID 2 ┘ LIBRE

Donde:
  1 = Asignado a PID 1
  2 = Asignado a PID 2
  . = Libre
```

**Experimento Educativo**:
1. Asignar 10 bytes a PID 1
2. Asignar 8 bytes a PID 2
3. Asignar 6 bytes a PID 3
4. Liberar PID 1 (genera fragmentación)
5. Intentar asignar 12 bytes (First-Fit falla)
6. Compactar
7. Intentar nuevamente (ahora funciona)

---

### 📁 Panel 3: Sistema de Archivos & E/S

#### TAB: Archivos

**Crear Archivo**:
1. Ingresa **Nombre del Archivo** (ej: datos.txt)
2. Ingresa **Tamaño en bloques** (1-100)
3. Haz clic en **📝 Crear Archivo**

**Eliminar Archivo**:
1. Ingresa el nombre del archivo
2. Haz clic en **🗑️ Eliminar**
   - ⚠️ No puedes eliminar archivos abiertos

**Listar Archivos**:
- Haz clic en **📋 Listar Archivos**
- Ver en la consola todos los archivos del sistema

**Estadísticas del Disco**:
- **Total Archivos**: Cantidad de archivos
- **Bloques Usados**: Espacio ocupado
- **Bloques Libres**: Espacio disponible (total: 100)

#### TAB: E/S (Input/Output)

**Solicitar E/S**:
1. Selecciona **Dispositivo** (Disco, Red, Impresora)
2. Selecciona **Operación** (Lectura o Escritura)
3. Ingresa **PID del Proceso** 
4. Ingresa **Datos (bytes)** a transferir
5. Haz clic en **📤 Enviar Solicitud**

**Procesar E/S**:
- Haz clic en **⏱️ Procesar (Poll)** para completar una solicitud
- Cada poll simula latencia realista (50-150ms)

**Estadísticas de E/S**:
- **E/S Pendientes**: Solicitudes en cola
- **E/S Completadas**: Operaciones terminadas
- **Tiempo Promedio**: Latencia promedio

---

## 🔗 Panel 4: Escenarios Integrados

Demostraciones que muestran cómo interactúan todos los subsistemas:

### Escenario 1: CPU + Memoria
- Crea 3 procesos con diferentes tiempos de ráfaga
- Asigna memoria a cada proceso
- Ejecuta scheduling
- **Demuestra**: Cómo la asignación de memoria afecta el scheduling

**Resultado Esperado**:
```
✅ P1 creado (15ms)
✅ P2 creado (10ms)
✅ P3 creado (20ms)
✅ Asignados 10 bytes a PID 1
✅ Asignados 8 bytes a PID 2
▶️ Ejecutando Round Robin...
✅ P1 terminado (Turnaround: Xms)
✅ P2 terminado (Turnaround: Yms)
✅ P3 terminado (Turnaround: Zms)
```

### Escenario 2: I/O Concurrente
- Crea 2 archivos en disco
- Genera solicitudes de lectura/escritura
- Procesa operaciones de E/S
- **Demuestra**: Cómo la E/S bloquea procesos

**Resultado Esperado**:
```
📄 datos1.txt - 10 bloques - CERRADO
📄 datos2.txt - 15 bloques - CERRADO
📤 E/S solicitada: READ en disk (256 bytes)
📤 E/S solicitada: WRITE en disk (256 bytes)
✅ E/S completada: READ (Latencia: 87ms)
✅ E/S completada: WRITE (Latencia: 92ms)
```

### Escenario 3: Integración Completa
- Ejecuta Escenario 1 + Escenario 2 simultáneamente
- Muestra cómo todos los subsistemas interactúan
- **Demuestra**: Un mini-kernel funcional

---

## 📟 Consola de Ejecución

Muestra en tiempo real:
- ✅ Operaciones exitosas
- ❌ Errores y validaciones
- ⚠️ Advertencias
- 📊 Estadísticas
- ⏱️ Timestamps

**Comandos útiles**:
- Ver historial completo: Scroll en la consola
- Limpiar consola: 🗑️ Limpiar Consola (botón)

---

## 🎓 Experimentos Educativos Recomendados

### Experimento 1: Comparar FIFO vs Round Robin
```
1. Crear 3 procesos: P1(20ms), P2(15ms), P3(10ms)
2. Ejecutar con FIFO
3. Anotar Turnaround times
4. Resetear
5. Ejecutar con Round Robin
6. Comparar resultados
→ Observar cómo RR es más justo pero tiene más context switches
```

### Experimento 2: Fragmentación de Memoria
```
1. Asignar 8 bytes a PID 1
2. Asignar 8 bytes a PID 2
3. Asignar 8 bytes a PID 3
4. Asignar 8 bytes a PID 4
5. Liberar PID 1
6. Liberar PID 3
7. Intentar asignar 16 bytes
→ Ver cómo First-Fit no encuentra espacio (fragmentación)
→ Compactar y reintentar (ahora funciona)
```

### Experimento 3: I/O Blocking
```
1. Crear archivo "importante.txt" (20 bloques)
2. Solicitar lectura desde PID 1
3. Solicitar lectura desde PID 2
4. Solicitar escritura desde PID 1
5. Procesar las E/S una por una
→ Ver cómo la latencia de E/S afecta el sistema
```

### Experimento 4: Integración Completa
```
1. Ejecutar Escenario 3
2. Observar toda la consola
3. Ver cómo cada subsistema afecta a los otros
→ Entender un mini-kernel en acción
```

---

## 🌐 Características Técnicas

### Tecnología
- **Frontend**: HTML5 + CSS3 + JavaScript (ES6)
- **Sin dependencias externas**: Funciona offline
- **Responsive**: Se adapta a diferentes tamaños de pantalla
- **Cross-browser**: Compatible con Chrome, Firefox, Edge, Safari

### Performance
- Simulaciones en tiempo real
- Consola eficiente (máximo 50 líneas)
- Visualización actualizada instantáneamente
- Sin lag o retrasos

### Algoritmos Implementados
✅ First-Fit Memory Management
✅ Round Robin Scheduling
✅ FIFO Device Queues
✅ FCB File System

---

## 📋 Checklist de Prueba

- [ ] Crear múltiples procesos
- [ ] Ejecutar con FIFO
- [ ] Ejecutar con Round Robin
- [ ] Asignar y liberar memoria
- [ ] Ver fragmentación
- [ ] Compactar memoria
- [ ] Crear archivos
- [ ] Eliminar archivos
- [ ] Solicitar E/S
- [ ] Procesar E/S
- [ ] Ejecutar Escenario 1
- [ ] Ejecutar Escenario 2
- [ ] Ejecutar Escenario 3
- [ ] Resetear simulación

---

## 🎯 Conclusión

Esta interfaz gráfica permite:

✅ **Visualizar** el comportamiento de cada componente
✅ **Experimentar** variando parámetros
✅ **Aprender** conceptos de sistemas operativos
✅ **Demostrar** la integración de subsistemas
✅ **Validar** que el simulador funciona correctamente

Es una herramienta educativa poderosa para estudiantes, docentes e investigadores interesados en sistemas operativos.

---

**Última actualización**: Diciembre 2025
**Versión**: 1.0
**Estado**: ✅ Funcional y Completo
