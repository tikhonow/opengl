//
// Created by tikhonow on 7/6/21.
//

#ifndef CRY_ELEMENTBUFFEROBJECT_H
#define CRY_ELEMENTBUFFEROBJECT_H


class ElementBufferObject {
public:
    unsigned int stride;

    ElementBufferObject(void* data, unsigned int size);

    void use();

    virtual ~ElementBufferObject();

private:
    unsigned int ID_EBO;

};


#endif //CRY_ELEMENTBUFFEROBJECT_H
