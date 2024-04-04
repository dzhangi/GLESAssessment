package com.pk.opengles_native_lib

class NativeLib {

    /**
     * A native method that is implemented by the 'opengles_native_lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'opengles_native_lib' library on application startup.
        init {
            System.loadLibrary("opengles_native_lib")
        }
    }
}