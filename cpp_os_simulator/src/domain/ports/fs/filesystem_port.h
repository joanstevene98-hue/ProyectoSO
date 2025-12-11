#ifndef DOMAIN_PORTS_FS_FILESYSTEM_PORT_H
#define DOMAIN_PORTS_FS_FILESYSTEM_PORT_H

#include <optional>
#include <string>

namespace domain::ports::fs {

/**
 * @typedef OpenResult
 * @brief Resultado de operación open: file descriptor (handle) o nullopt si falla
 */
using OpenResult = std::optional<int>;

/**
 * @class FilesystemPort
 * @brief Interfaz (puerto) que define el contrato de un sistema de archivos
 * 
 * Operaciones CRUD básicas:
 * - CREATE: Crear nuevo archivo
 * - OPEN: Obtener handle para operaciones
 * - CLOSE: Liberar handle
 * - REMOVE: Eliminar archivo
 * - LIST (ls): Ver archivos disponibles
 * 
 * Patrón: Este puerto permite cambiar entre diferentes implementaciones
 * (en memoria, disco, red) sin cambiar el código que lo usa.
 * 
 * Ejemplo de uso:
 * @code
 * FilesystemPort& fs = /* alguna implementación */;
 * if (fs.create("myfile.txt")) {
 *     if (auto h = fs.open("myfile.txt")) {
 *         // hacer algo
 *         fs.close(*h);
 *     }
 * }
 * @endcode
 */
class FilesystemPort {
public:
    virtual ~FilesystemPort() = default;
    
    /**
     * @brief Crea un nuevo archivo vacío
     * @param name Nombre del archivo
     * @return true si se creó, false si ya existe
     * 
     * Precondición: Archivo no debe existir
     * Tiempo: O(log n) en implementación con map
     */
    virtual bool create(const std::string &name) = 0;
    
    /**
     * @brief Abre un archivo y retorna un handle (file descriptor)
     * @param name Nombre del archivo a abrir
     * @return Handle (int) si exitoso, nullopt si no existe
     * 
     * Precondición: Archivo debe existir
     * Postcondición: Archivo marcado como open=true
     * Tiempo: O(log n)
     */
    virtual OpenResult open(const std::string &name) = 0;
    
    /**
     * @brief Cierra un archivo por su handle
     * @param handle File descriptor retornado por open()
     * @return true si cierre exitoso, false si handle inválido
     * 
     * Postcondición: Archivo marcado como open=false
     * Tiempo: O(1)
     */
    virtual bool close(int handle) = 0;
    
    /**
     * @brief Elimina un archivo del sistema
     * @param name Nombre del archivo
     * @return true si se eliminó, false si no existe o está abierto
     * 
     * Precondición: Archivo no debe estar abierto
     * Tiempo: O(n)
     */
    virtual bool remove(const std::string &name) = 0;
    
    /**
     * @brief Lista todos los archivos y su estado
     * 
     * Imprime información de cada archivo:
     * - Nombre
     * - Tamaño
     * - Estado (open/closed)
     * 
     * Tiempo: O(n) donde n = número de archivos
     */
    virtual void ls() = 0;
};

} // namespace domain::ports::fs

#endif // DOMAIN_PORTS_FS_FILESYSTEM_PORT_H
