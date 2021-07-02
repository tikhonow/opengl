//
// Created by Ruslan Tikhonov on 21/06/2021.
//


#pragma once


class VertexBuffer
{
public:
    unsigned int stride;

    VertexBuffer(void* data, unsigned int size, unsigned int stride);

    void use();

    virtual ~VertexBuffer();

private:
    unsigned int ID;
};

