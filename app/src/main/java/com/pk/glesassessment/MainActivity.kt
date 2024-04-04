package com.pk.glesassessment

import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.pk.glesassessment.databinding.ActivityMainBinding
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.rotationSlider.addOnChangeListener { _, value, _ ->
            Log.d(SLIDER_TAG, "Value: $value")
        }

        binding.glSurfaceView.apply {
            setEGLContextClientVersion(3)
            setRenderer(object : GLSurfaceView.Renderer {
                override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
                    Log.d(GL_TAG, "onSurfaceCreated")
                }

                override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
                    Log.d(GL_TAG, "onSurfaceChanged")
                }

                override fun onDrawFrame(gl: GL10?) {
                    Log.d(GL_TAG, "onDrawFrame")
                }
            })
        }
    }

    companion object {
        const val SLIDER_TAG = "SLIDER_LISTENER"
        const val GL_TAG = "GL_RENDERER"

        init {
            System.loadLibrary("glesassessment")
        }
    }
}