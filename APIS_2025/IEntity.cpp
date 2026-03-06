#include "IEntity.h"

glm::vec4 IEntity::GetPosicion() const
{
	return this->posicion;
}

glm::vec4 IEntity::GetRotacion() const
{
	return this->rotacion;
}

glm::vec4 IEntity::GetEscala() const
{
	return this->escalado;
}

glm::mat4 IEntity::GetMatrizModelo() const
{
	return this->matrizModelo;
}

void IEntity::setPosicion(const glm::vec4& pos)
{
	this->posicion = pos;
}

void IEntity::setRotacion(const glm::vec4& rot)
{
	this->rotacion = rot;
}

void IEntity::setEscala(const glm::vec4& esc)
{
	this->escalado = esc;
}

glm::mat4 IEntity::computeModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posicion.x, posicion.y, posicion.z));//aplicar posicion

	model = glm::rotate(model, glm::radians(rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));//aplicar rotacion en X
	model = glm::rotate(model, glm::radians(rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));//aplicar rotacion en Y
	model = glm::rotate(model, glm::radians(rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));//aplicar rotacion en Z


	model = glm::scale(model, glm::vec3(escalado.x, escalado.y, escalado.z));//aplicar escala

	this->matrizModelo = model;
	return this->matrizModelo;
}





