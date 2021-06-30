//
// Created by Ruslan Tikhonov on 21/06/2021.
//


#pragma once

#include <vector>
#include <glad/glad.h>
#include "VertexBuffer.h"

struct VertexAttribute
{
    unsigned int count;
    unsigned int type;
    unsigned int offset;
    bool normalized;

    VertexAttribute(unsigned int count, unsigned int type, unsigned int offset, bool normalized = false);

    unsigned int sizeofType() const;
};

class VertexArray
{
public:
    unsigned int ID;

    VertexArray();

    void addBuffer(VertexBuffer &buffer, const VertexAttribute* attributes, unsigned int attributeCount);

    void use();

    virtual ~VertexArray();
};

