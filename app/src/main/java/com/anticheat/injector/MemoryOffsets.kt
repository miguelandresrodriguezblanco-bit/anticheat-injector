package com.anticheat.injector

/**
 * Offsets de memoria extraídos del volcado com.estar.bap[X64].cs
 * Estos valores representan las direcciones relativas dentro de las clases de Unity IL2CPP
 */
object MemoryOffsets {

    // GameMatch - Punto de entrada principal
    const val GAMEMATCH_SINGLETON = 0x8L
    const val GAMEMATCH_PLAYERLIST = 0x48L
    const val GAMEMATCH_BALL = 0x28L
    const val GAMEMATCH_TEAMA = 0x38L
    const val GAMEMATCH_TEAMB = 0x40L

    // Player - Estructura del jugador
    const val PLAYER_ID = 0x2cL
    const val PLAYER_INDEX = 0x30L
    const val PLAYER_NAME = 0x40L
    const val PLAYER_TEAM = 0x48L
    const val PLAYER_PROPERTY = 0x1b8L
    const val PLAYER_SPEEDVALUE = 0x2f0L
    const val PLAYER_POSITION = 0x1e8L
    const val PLAYER_ROTATION = 0x1f4L

    // PlayerProperty - Propiedades del jugador
    const val PLAYERPROPERTY_MANAGER = 0x10L
    const val PLAYERPROPERTY_SPEED = 0x20L
    const val PLAYERPROPERTY_STAMINA = 0x24L
    const val PLAYERPROPERTY_STRENGTH = 0x28L
    const val PLAYERPROPERTY_ACCURACY = 0x2cL

    // Football (Balón)
    const val FOOTBALL_POSITION = 0xecL
    const val FOOTBALL_VELOCITY = 0xe0L
    const val FOOTBALL_RADIUS = 0x10L
    const val FOOTBALL_LASTKICKPLAYER = 0x18L

    // PlayerProperty - Física del jugador
    const val PLAYER_UPPER_PHYSICAL = 0x388L
    const val PLAYER_CUR_PHYSICAL = 0x38cL
    const val PLAYER_CAN_SPEEDUP = 0x390L

    // Métodos importantes (Offsets de funciones)
    const val METHOD_SETPROPERTYVALUE = 0xed6504L
    const val METHOD_GETPROPERTYVALUE = 0xed6278L

    private var initialized = false

    fun initialize() {
        initialized = true
    }

    fun isInitialized(): Boolean = initialized

    /**
     * Estructura de datos para un offset de hack
     */
    data class HackOffset(
        val name: String,
        val offset: Long,
        val type: String, // "float", "int", "long", "bool"
        val description: String,
        val value: Any? = null
    )

    /**
     * Hacks disponibles basados en el volcado
     */
    fun getAvailableHacks(): List<HackOffset> = listOf(
        HackOffset(
            name = "Speed Hack",
            offset = PLAYER_SPEEDVALUE,
            type = "float",
            description = "Aumenta la velocidad del jugador",
            value = 50.0f
        ),
        HackOffset(
            name = "Infinite Stamina",
            offset = PLAYER_CUR_PHYSICAL,
            type = "float",
            description = "Mantiene la estamina al máximo",
            value = 100.0f
        ),
        HackOffset(
            name = "Ball Magnet",
            offset = FOOTBALL_POSITION,
            type = "vec3",
            description = "El balón sigue al jugador",
            value = null
        ),
        HackOffset(
            name = "Perfect Accuracy",
            offset = PLAYERPROPERTY_ACCURACY,
            type = "float",
            description = "Precisión de tiro al 100%",
            value = 100.0f
        ),
        HackOffset(
            name = "Infinite Speed",
            offset = PLAYER_CAN_SPEEDUP,
            type = "bool",
            description = "Permite acelerar infinitamente",
            value = true
        )
    )
}
