#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <math.h>

inline void glPerspective( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
#ifdef __APPLE__
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
#else
    gluPerspective(fovY, aspect, zNear, zFar);
#endif
}

inline void glBindVAO(GLuint id)
{
#ifdef __APPLE__
    glBindVertexArrayAPPLE(id);
#else
    glBindVertexArray(id);
#endif
}

inline void glGenVAO(GLsizei n, GLuint *ids)
{
#ifdef __APPLE__
    glGenVertexArraysAPPLE(n, ids);
#else
    glGenVertexArrays(n, ids);
#endif
}

#endif