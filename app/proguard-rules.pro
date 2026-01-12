# ProGuard rules for Anti-Cheat Injector

# Keep native methods
-keepclasseswithmembernames class * {
    native <methods>;
}

# Keep all classes in our package
-keep class com.anticheat.injector.** { *; }

# Keep JNI methods
-keepclasseswithmembernames class com.anticheat.injector.InjectorService {
    native <methods>;
}
