package com.anticheat.injector

import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private lateinit var statusText: TextView
    private lateinit var startButton: Button
    private lateinit var stopButton: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        statusText = findViewById(R.id.status_text)
        startButton = findViewById(R.id.start_button)
        stopButton = findViewById(R.id.stop_button)

        startButton.setOnClickListener {
            startInjectorService()
        }

        stopButton.setOnClickListener {
            stopInjectorService()
        }

        updateStatus()
    }

    private fun startInjectorService() {
        val intent = Intent(this, InjectorService::class.java)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(intent)
        } else {
            startService(intent)
        }
        statusText.text = "Inyector iniciado..."
    }

    private fun stopInjectorService() {
        stopService(Intent(this, InjectorService::class.java))
        statusText.text = "Inyector detenido"
    }

    private fun updateStatus() {
        statusText.text = "Estado: Listo\nOffsetsLoaded: ${MemoryOffsets.isInitialized()}"
    }
}
