//
// Created by pk on 4/4/2024.
//

#ifndef GLESASSESSMENT_NATIVE_OPENGLES_H
#define GLESASSESSMENT_NATIVE_OPENGLES_H

#include <android/log.h>
#include <math.h>
#include <GLES3/gl32.h>

#define DEBUG 1

#define LOG_TAG "GLES3JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) \
  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif


#define MAX_INSTANCES 1

struct Vertex {
    GLfloat pos[2];
    GLubyte rgba[4];
};

extern const Vertex QUAD[4];

extern bool checkGlError(const char *funcName);

extern GLuint createShader(GLenum shaderType, const char *src);

extern GLuint createProgram(const char *vtxSrc, const char *fragSrc);

class Renderer {
public:
    void resize(int w, int h);

    void render();

    void shiftAngle(float angle);

protected:
    Renderer();

    virtual float *mapOffsetBuf() = 0;

    virtual void unmapOffsetBuf() = 0;

    virtual float *mapTransformBuf() = 0;

    virtual void unmapTransformBuf() = 0;

    virtual void draw() = 0;

private:
    void step(float rotationAngle = 0);

    int mNumInstances = 1;
    float mScale[2] = {1, 1};
    uint64_t mLastFrameNs;
    float mAngle = 0;
};

extern Renderer *createES3Renderer();

#endif //GLESASSESSMENT_NATIVE_OPENGLES_H
