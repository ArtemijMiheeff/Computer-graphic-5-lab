#include "camera.h"

// установка позиции камеры
void Camera::setPosition(vec3 position)
{
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов 
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}
Camera::Camera()
{
	position = vec3(0, 0, 0);
	r = 1.0f;
	angleX = 0.0f;
	angleY = 0.0f;
}
Camera::Camera(vec3 position)
{
	setPosition(position);
}
Camera::Camera(float x, float y, float z)
{
	setPosition(vec3(x,y,z));
}
vec3 Camera::getPosition()
{
	return position;
}
void Camera::rotateLeftRight(float degree)
{
	angleX += degree;
	recalculatePosition();
}
void Camera::rotateUpDown(float degree)
{
	angleY += degree;
	std::cout << angleY << std::endl;
	if (angleY >= 80)
	{
		angleY = 80;
		std::cout << "test rotate";
	}
	if (angleY < 5)
	{
		angleY = 5;
		std::cout << "test rotate";
	}
	recalculatePosition();
}
void Camera::zoomInOut(float degree)
{
	r += degree;

	if (r > 52)
	{
		r = 52;
	}

	if (r < 23)
	{
		r = 23;
	}
	recalculatePosition();
}
void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}
void Camera::recalculatePosition()
{

	float angle_x = radians(angleX);
	float angle_y = radians(angleY);

	position.x = r * sin(angle_y) * cos(angle_x);
	position.y = r * cos(angle_y);
	position.z = r * sin(angle_y) * sin(angle_x);
}