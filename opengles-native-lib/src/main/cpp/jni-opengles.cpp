#include <jni.h>
#include <string>
#include "native-opengles.h"

static Renderer *g_renderer = NULL;

extern "C" {

JNIEXPORT void JNICALL
Java_com_pk_opengles_1native_1lib_NativeLib_initGL(JNIEnv *env, jobject obj) {
    if (g_renderer) {
        delete g_renderer;
        g_renderer = NULL;
    }

    const char *versionStr = (const char *) glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")) {
        g_renderer = createES3Renderer();
    } else {
        ALOGE("Unsupported OpenGL ES version");
    }
}

JNIEXPORT void JNICALL
Java_com_pk_opengles_1native_1lib_NativeLib_resizeViewPort(JNIEnv *env, jobject obj, jint width,
                                                       jint height) {
    if (g_renderer) {
        g_renderer->resize(width, height);
    }
}

JNIEXPORT void JNICALL
Java_com_pk_opengles_1native_1lib_NativeLib_drawFrame(JNIEnv *env, jobject obj) {
    if (g_renderer) {
        g_renderer->render();
    }
}

JNIEXPORT void JNICALL
Java_com_pk_opengles_1native_1lib_NativeLib_shiftAngle(JNIEnv *env, jobject obj, jfloat angle) {
    g_renderer->shiftAngle(angle);
}

}