# Anti-Cheat Injector para Football Dream

Una herramienta de prueba de seguridad diseñada para desarrolladores antitrampas. Permite inyectar código nativo en el juego Football Dream para probar vulnerabilidades de memoria y validar sistemas de protección.

## ⚠️ Advertencia Legal

Esta herramienta está diseñada **exclusivamente para propósitos educativos y de pruebas de seguridad en entornos controlados**. El uso no autorizado de esta herramienta contra servidores o juegos de terceros puede violar leyes de protección de software y términos de servicio.

## Características

- **Inyección de Código Nativo**: Integración con libil2cpp.so para acceso directo a memoria del juego
- **Speed Hack**: Aumenta la velocidad del jugador
- **Infinite Stamina**: Estamina infinita para todos los jugadores
- **Ball Magnet**: El balón sigue al jugador
- **Perfect Accuracy**: Precisión de tiro al 100%
- **Interfaz ImGui**: Overlay en tiempo real dentro del juego (en desarrollo)

## Requisitos

- Android 5.0+ (API 21)
- Dispositivo rooteado o emulador con capacidades de debugging
- NDK de Android
- Gradle 8.1.0+

## Compilación

### Opción 1: GitHub Actions (Recomendado)

1. Haz fork de este repositorio
2. Ve a **Actions** en tu repositorio
3. El workflow de compilación se ejecutará automáticamente
4. Descarga el APK compilado desde los artefactos

### Opción 2: Compilación Local

```bash
# Clonar el repositorio
git clone https://github.com/tu-usuario/anticheat-injector.git
cd anticheat-injector

# Compilar con Gradle
./gradlew assembleDebug

# El APK se generará en:
# app/build/outputs/apk/debug/app-debug.apk
```

## Instalación

```bash
# Instalar en el dispositivo
adb install app/build/outputs/apk/debug/app-debug.apk

# O usando el APK directamente
adb push app/build/outputs/apk/debug/app-debug.apk /data/local/tmp/
adb shell pm install /data/local/tmp/app-debug.apk
```

## Uso

1. **Enraizar el dispositivo** (si no lo está ya)
2. **Instalar el APK**
3. **Abrir la aplicación**
4. **Hacer clic en "Iniciar Inyector"**
5. **Abrir Football Dream**
6. El overlay ImGui aparecerá en la pantalla del juego

## Estructura de Offsets

Los offsets están basados en el volcado `com.estar.bap[X64].cs`:

| Clase | Campo | Offset | Tipo |
|-------|-------|--------|------|
| GameMatch | Singleton | 0x8 | Pointer |
| GameMatch | playerList | 0x48 | Array |
| GameMatch | ball | 0x28 | Pointer |
| Player | speedValue | 0x2f0 | Float |
| Player | curPhysical | 0x38c | Float |
| Football | position | 0xec | Vector3 |
| Football | velocity | 0xe0 | Vector3 |

## Arquitectura

```
anticheat-injector/
├── app/
│   ├── src/main/
│   │   ├── java/com/anticheat/injector/
│   │   │   ├── MainActivity.kt          # Interfaz principal
│   │   │   ├── InjectorService.kt       # Servicio de inyección
│   │   │   └── MemoryOffsets.kt         # Definición de offsets
│   │   ├── cpp/
│   │   │   ├── native-lib.cpp           # Interfaz JNI
│   │   │   ├── memory-hook.cpp          # Lógica de hooking
│   │   │   ├── memory-hook.h            # Header del hooking
│   │   │   ├── imgui-overlay.cpp        # Overlay ImGui
│   │   │   └── CMakeLists.txt           # Configuración CMake
│   │   └── res/
│   │       ├── layout/activity_main.xml
│   │       ├── values/
│   │       └── drawable/
│   └── build.gradle.kts
├── .github/workflows/build.yml          # GitHub Actions
└── README.md
```

## Hacks Disponibles

### Speed Hack
Aumenta la velocidad de movimiento del jugador a un valor personalizable.

```cpp
applySpeedHack(50.0f); // Velocidad 50x
```

### Infinite Stamina
Mantiene la estamina del jugador al máximo constantemente.

```cpp
applyInfiniteStamina();
```

### Ball Magnet
El balón sigue la posición del jugador local.

```cpp
applyBallMagnet();
```

### Perfect Accuracy
Establece la precisión de tiro al 100%.

```cpp
applyPerfectAccuracy();
```

## Detección de Antitrampas

Para validar tu sistema antitrampas, puedes detectar:

1. **Valores fuera de rango**: Velocidades > 30 m/s
2. **Estamina congelada**: Sin cambios durante acciones
3. **Distancia balón-jugador = 0**: Indicador de Ball Magnet
4. **Precisión imposible**: Tiros con 100% de precisión consistente

## Desarrollo Futuro

- [ ] Interfaz ImGui completa
- [ ] Sistema de scripts dinámicos
- [ ] Soporte para múltiples versiones del juego
- [ ] Logging de eventos en tiempo real
- [ ] Exportación de datos de pruebas

## Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Haz fork del proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## Licencia

Este proyecto está bajo licencia MIT. Ver `LICENSE` para más detalles.

## Soporte

Para reportar bugs o solicitar features, abre un issue en GitHub.

## Autores

- **Manus AI** - Desarrollo inicial

## Agradecimientos

- Volcado de clases proporcionado por il2cpp-dumper
- Comunidad de seguridad en videojuegos
