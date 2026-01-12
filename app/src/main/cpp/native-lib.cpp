#include <jni.h>
#include <android/log.h>
#include <cstring>
#include <unistd.h>
#include "memory-hook.h"

#define LOG_TAG "AntiCheatInjector"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Variables globales para el hooking
static MemoryHook* g_hook = nullptr;
static bool g_hooking_active = false;

extern "C" {

JNIEXPORT void JNICALL
Java_com_anticheat_injector_InjectorService_nativeStartHooking(JNIEnv *env, jobject thiz) {
    LOGI("Iniciando hooking nativo...");
    
    if (g_hooking_active) {
        LOGI("Hooking ya está activo");
        return;
    }

    try {
        g_hook = new MemoryHook();
        
        // Inicializar el hook
        if (g_hook->initialize()) {
            LOGI("MemoryHook inicializado correctamente");
            
            // Aplicar los hacks disponibles
            g_hook->applySpeedHack(50.0f);
            g_hook->applyInfiniteStamina();
            g_hook->applyBallMagnet();
            
            g_hooking_active = true;
            LOGI("Todos los hacks aplicados exitosamente");
        } else {
            LOGE("Error al inicializar MemoryHook");
            delete g_hook;
            g_hook = nullptr;
        }
    } catch (const std::exception& e) {
        LOGE("Excepción al iniciar hooking: %s", e.what());
    }
}

JNIEXPORT void JNICALL
Java_com_anticheat_injector_InjectorService_nativeStopHooking(JNIEnv *env, jobject thiz) {
    LOGI("Deteniendo hooking nativo...");
    
    if (g_hook != nullptr) {
        g_hook->cleanup();
        delete g_hook;
        g_hook = nullptr;
        g_hooking_active = false;
        LOGI("Hooking detenido");
    }
}

} // extern "C"
