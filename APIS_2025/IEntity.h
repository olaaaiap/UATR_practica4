#pragma once
#include "vertex_t.h"


class IEntity
{
protected:
    glm::vec4 posicion; //Posicion
    glm::vec4 rotacion; //Rotacion
    glm::vec4 escalado; //Rotacion
    glm::mat4 matrizModelo; //Matriz modelo
public:


    glm::vec4 GetPosicion() const;
    glm::vec4 GetRotacion() const;
    glm::vec4 GetEscala() const;
    glm::mat4 GetMatrizModelo() const;


    void setPosicion(const glm::vec4& pos);
    void setRotacion(const glm::vec4& rot);
    void setEscala(const glm::vec4& esc);

    glm::mat4 computeModelMatrix();

    virtual void step(double deltaTime) = 0; //Las clases que implementes Entity tendrán que dar una implementación de este método.


};

