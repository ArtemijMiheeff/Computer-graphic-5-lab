#include "GraphicObject.h"
GraphicObject::GraphicObject()
{
	position = vec3(0, 0, 0);
	angle = 0;
	color = vec3(0, 0, 0);
}
void GraphicObject::setPosition(vec3 position)
{
	this->position = position;

}
vec3 GraphicObject::getPosition()
{
	return position;
}
void GraphicObject::setAngle(float grad)
{
	this->angle = grad;
}
float GraphicObject::getAngle()
{
	return angle;
}
void GraphicObject::setСolor(vec3 color)
{
	this->color = color;
}
vec3 GraphicObject::getColor()
{
	return color;
}
// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
	float angRad = radians(angle);
	modelMatrix[0] = cos(angRad);
	modelMatrix[5] = 1;
	modelMatrix[2] = -sin(angRad);
	modelMatrix[8] = sin(angRad);
	modelMatrix[10] = cos(angRad) ;

	modelMatrix[12] = position.x;
	modelMatrix[13] = position.y;
	modelMatrix[14] = position.z;
}

// Установка используемого материала
void GraphicObject::setMaterial(std::shared_ptr<PhongMaterial> materiall)
{
	this->material = materiall;
}

// вывести объект
void GraphicObject::draw()
{
	glColor3f(color.r, color.g, color.b);


	material->apply();
	

	glPushMatrix();
	recalculateModelMatrix();
	glMultMatrixf(modelMatrix);
	glutSolidTeapot(1.0);
	glPopMatrix();

}