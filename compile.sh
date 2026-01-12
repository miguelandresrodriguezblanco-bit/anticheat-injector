#!/bin/bash

echo "🔨 Iniciando compilación del APK..."
echo "=================================="

# Descargar e instalar Android SDK si es necesario
if [ ! -d "$ANDROID_HOME" ]; then
    echo "📦 Instalando Android SDK..."
    apt-get update -qq
    apt-get install -y -qq android-sdk android-sdk-build-tools android-sdk-platform-tools
    export ANDROID_HOME=/usr/lib/android-sdk
fi

# Compilar
echo "🏗️  Compilando APK..."
chmod +x gradlew
./gradlew assembleDebug

# Verificar resultado
if [ -f "app/build/outputs/apk/debug/app-debug.apk" ]; then
    echo ""
    echo "✅ ¡APK COMPILADO EXITOSAMENTE!"
    echo "📦 Ubicación: app/build/outputs/apk/debug/app-debug.apk"
    echo ""
    echo "Puedes descargar el archivo desde la carpeta de archivos de Replit"
    ls -lh app/build/outputs/apk/debug/app-debug.apk
else
    echo "❌ Error: El APK no se compiló correctamente"
    exit 1
fi
