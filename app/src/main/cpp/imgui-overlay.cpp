#include <android/log.h>

#define LOG_TAG "ImGuiOverlay"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**
 * Archivo stub para la interfaz ImGui
 * En una implementación completa, aquí iría el código para renderizar
 * un overlay ImGui dentro del juego
 */

void initImGuiOverlay() {
    LOGI("ImGui Overlay inicializado");
    // TODO: Implementar inicialización de ImGui
}

void renderImGuiOverlay() {
    // TODO: Implementar renderización del overlay
}

void destroyImGuiOverlay() {
    LOGI("ImGui Overlay destruido");
}
