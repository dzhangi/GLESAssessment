//
// Created by xtrml on 4/4/2024.
//

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "native-opengles.h"

const Vertex QUAD[4] = {
        {{-0.5f, -0.5f}, {0x00, 0xCC, 0x00}},
        {{0.5f,  -0.5f}, {0x00, 0x00, 0xCC}},
        {{-0.5f, 0.5f},  {0xCC, 0x00, 0x00}},
        {{0.5f,  0.5f},  {0xBB, 0xCC, 0xAA}},
};

bool checkGlError(const char *funcName) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        ALOGE("GL error after %s(): 0x%08x\n", funcName, err);
        return true;
    }
    return false;
}

GLuint createShader(GLenum shaderType, const char *src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        checkGlError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                ALOGE("Could not compile %s shader:\n%s\n",
                      shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint createProgram(const char *vtxSrc, const char *fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader) goto exit;

    fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader) goto exit;

    program = glCreateProgram();
    if (!program) {
        checkGlError("glCreateProgram");
        goto exit;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        ALOGE("Could not link program");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                ALOGE("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

    exit:
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}

static void printGlString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    ALOGV("GL %s: %s\n", name, v);
}


Renderer::Renderer() {}

void Renderer::resize(int w, int h) {
    mapOffsetBuf();
    unmapOffsetBuf();

    glViewport(0, 0, w, h);
}

void Renderer::step(float rotationAngle) {
    timespec now;
    auto nowNs = now.tv_sec * 1000000000ull + now.tv_nsec;

    if (mLastFrameNs > 0) {
        float *transforms = mapTransformBuf();

        for (unsigned int i = 0; i < mNumInstances; i++) {
            float s = sinf(mAngle);
            float c = cosf(mAngle);
            transforms[4 * i + 0] = c * mScale[0];
            transforms[4 * i + 1] = s * mScale[1];
            transforms[4 * i + 2] = -s * mScale[0];
            transforms[4 * i + 3] = c * mScale[1];
        }

        unmapTransformBuf();
    }

    mLastFrameNs = nowNs;
}

void Renderer::render() {
    step();

    glClearColor(0.1f, 0.2f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    checkGlError("Renderer::render");
}

void Renderer::shiftAngle(float angle) {
    mAngle = angle;
}
