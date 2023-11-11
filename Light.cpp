#include "Light.h"
Light::Light()
{
	position = vec4(0, 0, 0, 1);
}
Light::Light(vec3 position)
{
	this->position = vec4(position.x, position.y, position.z, 1);
}
Light::Light(float x, float y, float z)
{
	position = vec4(x, y, z, 1);
}
void Light::setPosition(vec3 position)
{
	this->position = vec4(position.x, position.y, position.z, 1);
}
void Light::setAmbient(vec4 color)
{
	ambient = color;
}
void Light::setDiffuse(vec4 color)
{
	diffuse = color;
}
void Light::setSpecular(vec4 color)
{
	specular = color;
}
void Light::apply(GLenum LightNumber)
{
	glEnable(GL_LIGHTING);
	glEnable(LightNumber);
	GLfloat lightAmbient[] = { ambient.x, ambient.y, ambient.z, 1.0 };
	glLightfv(LightNumber, GL_AMBIENT, lightAmbient);
	GLfloat lightDiffuse[] = { diffuse.x, diffuse.y, diffuse.z, 1.0 };
	glLightfv(LightNumber, GL_DIFFUSE, lightDiffuse);
	GLfloat lightSpecular[] = { specular.x, specular.y, specular.z, 1.0 };
	glLightfv(LightNumber, GL_SPECULAR, lightSpecular);
	GLfloat lightPosition[] = { position.x, position.y, position.z, 1.0 };
	glLightfv(LightNumber, GL_POSITION, lightPosition);

}