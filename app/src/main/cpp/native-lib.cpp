#include <jni.h>
#include <string>

extern "C" {

JNIEXPORT void JNICALL
Java_com_pk_glesassessment_MainActivity_initGL(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_com_pk_glesassessment_MainActivity_resizeViewPort(JNIEnv *env, jobject obj, jint width, jint height);

JNIEXPORT void JNICALL
Java_com_pk_glesassessment_MainActivity_drawFrame(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_com_pk_glesassessment_MainActivity_shiftAngle(JNIEnv *env, jobject obj, jfloat angle);

}