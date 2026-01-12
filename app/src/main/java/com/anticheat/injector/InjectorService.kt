package com.anticheat.injector

import android.app.Service
import android.content.Intent
import android.os.IBinder
import android.util.Log

class InjectorService : Service() {

    companion object {
        private const val TAG = "InjectorService"
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        Log.d(TAG, "Servicio de inyección iniciado")
        
        // Inicializar offsets
        MemoryOffsets.initialize()
        
        // Cargar la librería nativa
        try {
            System.loadLibrary("anticheat-injector")
            Log.d(TAG, "Librería nativa cargada exitosamente")
            
            // Iniciar el hooking
            startHooking()
        } catch (e: Exception) {
            Log.e(TAG, "Error al cargar la librería nativa", e)
        }

        return START_STICKY
    }

    private fun startHooking() {
        Log.d(TAG, "Iniciando hooking de funciones...")
        
        // Llamar a la función nativa para iniciar el hooking
        nativeStartHooking()
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d(TAG, "Servicio destruido")
        nativeStopHooking()
    }

    override fun onBind(intent: Intent?): IBinder? = null

    // Funciones nativas
    private external fun nativeStartHooking()
    private external fun nativeStopHooking()
}
