#ifndef DOMAIN_ENTITIES_FS_FCB_H
#define DOMAIN_ENTITIES_FS_FCB_H

#include <string>

namespace domain::entities::fs {

/**
 * @struct FCB
 * @brief File Control Block - Metadata de un archivo en el sistema
 * 
 * Almacena información sobre cada archivo:
 * - Identificación (nombre)
 * - Tamaño y ubicación
 * - Estado (abierto/cerrado)
 * 
 * Similar a los inodes en sistemas Unix o FAT entries
 * 
 * @note En un SO real, incluiría permisos, timestamps, propietario, etc.
 */
struct FCB {
    std::string name;        ///< Nombre del archivo (ej: "data.txt")
    int size;                ///< Tamaño en bytes (simulado)
    int start_block;         ///< Bloque inicial (para discos simulados)
    bool open;               ///< true si archivo está abierto por algún proceso

    /**
     * @brief Constructor de FCB
     * @param n Nombre del archivo (default: "")
     * @param s Tamaño en bytes (default: 0)
     * @param start Bloque inicial (default: -1 = no asignado)
     */
    FCB(std::string n="", int s=0, int start=-1) 
        : name(std::move(n)), size(s), start_block(start), open(false) {}
};

} // namespace domain::entities::fs

#endif // DOMAIN_ENTITIES_FS_FCB_H
