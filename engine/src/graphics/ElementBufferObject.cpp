//
// Created by tikhonow on 7/6/21.
//

#include "ElementBufferObject.h"
ElementBufferObject::ElementBufferObject(void *data, unsigned int size) {
    glCall(glGenBuffers(1, &ID_EBO));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
void ElementBufferObject::use() {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_EBO,GL_STATIC_DRAW)));
}
ElementBufferObject::~ElementBufferObject() {
    glCall(glDeleteBuffers(1, &ID_EBO
