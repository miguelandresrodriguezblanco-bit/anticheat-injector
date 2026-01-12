#include "memory-hook.h"
#include <android/log.h>
#include <fstream>
#include <sstream>
#include <cstring>

#define LOG_TAG "MemoryHook"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Offsets del volcado com.estar.bap[X64].cs
constexpr uint64_t OFFSET_GAMEMATCH_SINGLETON = 0x8;
constexpr uint64_t OFFSET_GAMEMATCH_PLAYERLIST = 0x48;
constexpr uint64_t OFFSET_GAMEMATCH_BALL = 0x28;
constexpr uint64_t OFFSET_PLAYER_SPEEDVALUE = 0x2f0;
constexpr uint64_t OFFSET_PLAYER_CUR_PHYSICAL = 0x38c;
constexpr uint64_t OFFSET_FOOTBALL_POSITION = 0xec;
constexpr uint64_t OFFSET_FOOTBALL_VELOCITY = 0xe0;

MemoryHook::MemoryHook() 
    : game_base_address(0), il2cpp_base_address(0), initialized(false) {
}

MemoryHook::~MemoryHook() {
    cleanup();
}

bool MemoryHook::initialize() {
    LOGI("Inicializando MemoryHook...");
    
    // Encontrar las direcciones base
    game_base_address = findGameBase();
    il2cpp_base_address = findIL2CppBase();
    
    if (game_base_address == 0 || il2cpp_base_address == 0) {
        LOGE("No se pudieron encontrar las direcciones base");
        return false;
    }
    
    LOGI("Game Base: 0x%lx", game_base_address);
    LOGI("IL2CPP Base: 0x%lx", il2cpp_base_address);
    
    initialized = true;
    return true;
}

uint64_t MemoryHook::findGameBase() {
    // Buscar el módulo del juego en /proc/self/maps
    std::ifstream maps("/proc/self/maps");
    std::string line;
    
    while (std::getline(maps, line)) {
        // Buscar libil2cpp.so o libmain.so
        if (line.find("libil2cpp.so") != std::string::npos || 
            line.find("libmain.so") != std::string::npos) {
            
            std::istringstream iss(line);
            std::string addr_range;
            iss >> addr_range;
            
            // Extraer la dirección inicial
            size_t dash_pos = addr_range.find('-');
            if (dash_pos != std::string::npos) {
                std::string start_addr = addr_range.substr(0, dash_pos);
                return std::stoull(start_addr, nullptr, 16);
            }
        }
    }
    
    LOGE("No se encontró la librería del juego");
    return 0;
}

uint64_t MemoryHook::findIL2CppBase() {
    std::ifstream maps("/proc/self/maps");
    std::string line;
    
    while (std::getline(maps, line)) {
        if (line.find("libil2cpp.so") != std::string::npos) {
            std::istringstream iss(line);
            std::string addr_range;
            iss >> addr_range;
            
            size_t dash_pos = addr_range.find('-');
            if (dash_pos != std::string::npos) {
                std::string start_addr = addr_range.substr(0, dash_pos);
                return std::stoull(start_addr, nullptr, 16);
            }
        }
    }
    
    return 0;
}

uint64_t MemoryHook::getGameMatchSingleton() {
    if (!initialized) return 0;
    
    // La dirección del Singleton está en il2cpp_base + offset
    uint64_t singleton_ptr_addr = il2cpp_base_address + OFFSET_GAMEMATCH_SINGLETON;
    uint64_t singleton = readMemory<uint64_t>(singleton_ptr_addr);
    
    LOGI("GameMatch Singleton: 0x%lx", singleton);
    return singleton;
}

uint64_t MemoryHook::getPlayerList() {
    uint64_t game_match = getGameMatchSingleton();
    if (game_match == 0) return 0;
    
    uint64_t player_list_ptr = game_match + OFFSET_GAMEMATCH_PLAYERLIST;
    uint64_t player_list = readMemory<uint64_t>(player_list_ptr);
    
    LOGI("Player List: 0x%lx", player_list);
    return player_list;
}

uint64_t MemoryHook::getBallAddress() {
    uint64_t game_match = getGameMatchSingleton();
    if (game_match == 0) return 0;
    
    uint64_t ball_ptr = game_match + OFFSET_GAMEMATCH_BALL;
    uint64_t ball = readMemory<uint64_t>(ball_ptr);
    
    LOGI("Ball Address: 0x%lx", ball);
    return ball;
}

void MemoryHook::applySpeedHack(float speed) {
    LOGI("Aplicando Speed Hack (velocidad: %.2f)...", speed);
    
    uint64_t player_list = getPlayerList();
    if (player_list == 0) {
        LOGE("No se pudo obtener la lista de jugadores");
        return;
    }
    
    // Iterar sobre los jugadores (asumiendo 22 jugadores en 11v11)
    for (int i = 0; i < 22; i++) {
        // En Unity, los arrays tienen un encabezado de 0x20
        uint64_t player_ptr_addr = player_list + 0x20 + (i * 0x8);
        uint64_t player = readMemory<uint64_t>(player_ptr_addr);
        
        if (player != 0) {
            uint64_t speed_addr = player + OFFSET_PLAYER_SPEEDVALUE;
            writeMemory<float>(speed_addr, speed);
            LOGI("Speed Hack aplicado al jugador %d", i);
        }
    }
}

void MemoryHook::applyInfiniteStamina() {
    LOGI("Aplicando Infinite Stamina...");
    
    uint64_t player_list = getPlayerList();
    if (player_list == 0) {
        LOGE("No se pudo obtener la lista de jugadores");
        return;
    }
    
    // Aplicar estamina infinita a todos los jugadores
    for (int i = 0; i < 22; i++) {
        uint64_t player_ptr_addr = player_list + 0x20 + (i * 0x8);
        uint64_t player = readMemory<uint64_t>(player_ptr_addr);
        
        if (player != 0) {
            uint64_t stamina_addr = player + OFFSET_PLAYER_CUR_PHYSICAL;
            writeMemory<float>(stamina_addr, 100.0f);
        }
    }
    
    LOGI("Infinite Stamina aplicado a todos los jugadores");
}

void MemoryHook::applyBallMagnet() {
    LOGI("Aplicando Ball Magnet...");
    
    uint64_t ball = getBallAddress();
    if (ball == 0) {
        LOGE("No se pudo obtener la dirección del balón");
        return;
    }
    
    uint64_t player_list = getPlayerList();
    if (player_list == 0) {
        LOGE("No se pudo obtener la lista de jugadores");
        return;
    }
    
    // Obtener la posición del primer jugador (jugador local)
    uint64_t player_ptr_addr = player_list + 0x20;
    uint64_t local_player = readMemory<uint64_t>(player_ptr_addr);
    
    if (local_player != 0) {
        // Leer la posición del jugador
        uint64_t player_pos_addr = local_player + 0x1e8; // offset de position
        
        // Copiar la posición del jugador al balón
        uint64_t ball_pos_addr = ball + OFFSET_FOOTBALL_POSITION;
        
        // Leer 12 bytes (3 floats para X, Y, Z)
        float pos_data[3];
        std::memcpy(pos_data, reinterpret_cast<void*>(player_pos_addr), sizeof(pos_data));
        
        // Escribir en la posición del balón
        std::memcpy(reinterpret_cast<void*>(ball_pos_addr), pos_data, sizeof(pos_data));
        
        LOGI("Ball Magnet aplicado");
    }
}

void MemoryHook::applyPerfectAccuracy() {
    LOGI("Aplicando Perfect Accuracy...");
    
    uint64_t player_list = getPlayerList();
    if (player_list == 0) {
        LOGE("No se pudo obtener la lista de jugadores");
        return;
    }
    
    // Aplicar precisión perfecta a todos los jugadores
    for (int i = 0; i < 22; i++) {
        uint64_t player_ptr_addr = player_list + 0x20 + (i * 0x8);
        uint64_t player = readMemory<uint64_t>(player_ptr_addr);
        
        if (player != 0) {
            // Offset de precisión basado en el volcado
            uint64_t accuracy_addr = player + 0x2c; // Offset aproximado
            writeMemory<float>(accuracy_addr, 100.0f);
        }
    }
    
    LOGI("Perfect Accuracy aplicado");
}

void MemoryHook::cleanup() {
    LOGI("Limpiando MemoryHook...");
    initialized = false;
}
