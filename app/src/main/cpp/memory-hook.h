#ifndef MEMORY_HOOK_H
#define MEMORY_HOOK_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * Estructura para representar un offset de memoria
 */
struct MemoryOffset {
    std::string name;
    uint64_t offset;
    std::string type; // "float", "int", "bool", "vec3"
    std::string description;
};

/**
 * Clase principal para el hooking de memoria
 */
class MemoryHook {
public:
    MemoryHook();
    ~MemoryHook();

    /**
     * Inicializa el hook y encuentra la dirección base del juego
     */
    bool initialize();

    /**
     * Aplica el hack de velocidad
     */
    void applySpeedHack(float speed);

    /**
     * Aplica estamina infinita
     */
    void applyInfiniteStamina();

    /**
     * Aplica el hack del balón magnético
     */
    void applyBallMagnet();

    /**
     * Aplica precisión perfecta
     */
    void applyPerfectAccuracy();

    /**
     * Lee un valor de memoria
     */
    template<typename T>
    T readMemory(uint64_t address) {
        T value = 0;
        if (address == 0) return value;
        
        try {
            std::memcpy(&value, reinterpret_cast<void*>(address), sizeof(T));
        } catch (...) {
            // Error al leer memoria
        }
        return value;
    }

    /**
     * Escribe un valor en memoria
     */
    template<typename T>
    bool writeMemory(uint64_t address, const T& value) {
        if (address == 0) return false;
        
        try {
            std::memcpy(reinterpret_cast<void*>(address), &value, sizeof(T));
            return true;
        } catch (...) {
            return false;
        }
    }

    /**
     * Limpia los recursos
     */
    void cleanup();

private:
    uint64_t game_base_address;
    uint64_t il2cpp_base_address;
    bool initialized;

    /**
     * Encuentra la dirección base de la librería del juego
     */
    uint64_t findGameBase();

    /**
     * Encuentra la dirección base de il2cpp
     */
    uint64_t findIL2CppBase();

    /**
     * Obtiene la dirección de GameMatch Singleton
     */
    uint64_t getGameMatchSingleton();

    /**
     * Obtiene la lista de jugadores
     */
    uint64_t getPlayerList();

    /**
     * Obtiene la dirección del balón
     */
    uint64_t getBallAddress();
};

#endif // MEMORY_HOOK_H
