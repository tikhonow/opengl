//
// Created by Ruslan Tikhonov on 15/06/2021.
//


#pragma once

#include <glad/glad.h>

#include <assert.h>

#define glCall(x) GLClearError(); \
    x; assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
