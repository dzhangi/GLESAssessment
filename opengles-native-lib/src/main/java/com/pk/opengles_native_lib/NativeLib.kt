package com.pk.opengles_native_lib

class NativeLib {

    external fun initGL()

    external fun resizeViewPort(width: Int, height: Int)

    external fun drawFrame()

    external fun shiftAngle(angle: Float)

    companion object {
        // Used to load the 'opengles_native_lib' library on application startup.
        init {
            System.loadLibrary("opengles_native_lib")
        }
    }
}