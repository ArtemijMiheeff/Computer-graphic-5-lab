#include <windows.h>
#include "camera.h"
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "GraphicObject.h"
#include "Light.h"
#include "PhongMaterial.h"
#include <vector>
Camera camera(vec3(0, 15, 17.5));
// используем пространство имен стандартной библиотеки
using namespace glm;
using namespace std;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

vector<vec3> color{ vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(0.5, 0.0, 1.0) };
//std::vector<vec3> color1 { 1.0, 0.0, 1.0 };

float r = 1;
float g = 0.5;
float b = 0.5;


// список графических объектов
vector <GraphicObject> graphicObjects;

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
Light light(vec3(10, 0, 10));

// используемые материалы
std::vector<std::shared_ptr<PhongMaterial>> materials;

void display(void)
{
	
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	camera.apply();
	/*material.setDiffuse(vec4(0.0, 0.0, 1.0, 1.0));
	material.setAmbient(vec4(0.0, 0.0, 0.4, 1.0));
	material.setSpecular(vec4(1.0, 1.0, 1.0, 0.0));
	material.setEmission(vec4(0.0, 0.0, 0.0, 1.0));
	material.setShininess(0.0);*/
	

	light.setAmbient(vec4(0.5, 0.5, 0.5, 1));
	light.setDiffuse(vec4(0.5, 0.5, 0.5, 1));
	light.setSpecular(vec4(0.5, 0.5, 0.5, 1));
	light.setPosition(vec3(0, 0, 0));
	light.apply();
	//gluLookAt(10, 15, 17.5, 0, 0, 0, 0, 1, 0);
	// выводим все графические объекты
	for (auto& go : graphicObjects) {
		go.draw();
		
	}
	// смена переднего и заднего буферов
	glutSwapBuffers();
};
int count_color = 0;
// функция вызывается каждые 20 мс
int counter = 1;
int counter1 = 0;
void simulation()
{

	if (GetAsyncKeyState(VK_LEFT))
	{
		camera.rotateLeftRight(-0.1);
	};
	if (GetAsyncKeyState(VK_RIGHT))
	{
		camera.rotateLeftRight(0.1);
	};
	if (GetAsyncKeyState(VK_UP))
	{
		camera.rotateUpDown(0.1);
	};
	if (GetAsyncKeyState(VK_DOWN))
	{
		camera.rotateUpDown(-0.1);
	};
	if (GetAsyncKeyState(VK_SPACE))
	{
		camera.zoomInOut(0.1);
	};
	if (GetAsyncKeyState(VK_SHIFT))
	{
		camera.zoomInOut(-0.1);
	};


	counter1++;
	if (counter1 == 50) {
		switch (counter)
		{
		case 1:
			r = color[0][0];
			g = color[0][1];
			b = color[0][2];
			counter++;
			counter1 = 0;
			break;
		case 2:
			r = color[1][0];
			g = color[1][1];
			b = color[1][2];
			counter++;
			counter1 = 0;
			break;
		case 3:
			r = color[2][0];
			g = color[2][1];
			b = color[2][2];
			counter = 1;
			counter1 = 0;
			break;
		}
	}
	//counter1 = 0;
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	//glutTimerFunc(20, simulation, 0);
};



// Функция обработки нажатия клавиш

void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	// для провекри класса камеры вызываем методы передвижения
	switch (static_cast<char>(key)) {
	case 'w':
		camera.rotateUpDown(5.0);
		break;
	case 's':
		camera.rotateUpDown(-5.0);
		break;
	case 'a':
		camera.rotateLeftRight(5.0);
		break;
	case 'd':
		camera.rotateLeftRight(-5.0);
		break;
	case '+':
		camera.zoomInOut(0.2);
		break;
	case '-':
		camera.zoomInOut(-0.2);
		break;
	}
};


void main(int argc, char** argv)
{
	//setlocale(LC_ALL, "ru");

	//ofstream MyFile("11.txt");
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_01");

	// ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
	// инициализация графических объектов

	std::shared_ptr<PhongMaterial> material1 = make_shared<PhongMaterial>();
	materials.push_back(material1);
	std::shared_ptr<PhongMaterial> material2 = make_shared<PhongMaterial>();
	materials.push_back(material2);
	std::shared_ptr<PhongMaterial> material3 = make_shared<PhongMaterial>();
	materials.push_back(material3);
	std::shared_ptr<PhongMaterial> material4 = make_shared<PhongMaterial>();
	materials.push_back(material4);
	materials[0]->load("1.txt");
	materials[1]->load("2.txt");
	materials[2]->load("3.txt");
	materials[3]->load("4.txt");


	GraphicObject tempGraphicObject;
	// 1 -----------------------------------------
	tempGraphicObject.setPosition(vec3(5, 0, 0));
	tempGraphicObject.setAngle(180);
	tempGraphicObject.setСolor(vec3(1, 0, 0));
	tempGraphicObject.setMaterial(materials[0]);
	graphicObjects.push_back(tempGraphicObject);
	// 2 -----------------------------------------
	tempGraphicObject.setPosition(vec3(-5, 0, 0));
	tempGraphicObject.setAngle(0);
	tempGraphicObject.setСolor(vec3(0, 1, 0));
	tempGraphicObject.setMaterial(materials[1]);
	graphicObjects.push_back(tempGraphicObject);
	// 3 -----------------------------------------
	tempGraphicObject.setPosition(vec3(0, 0, 5));
	tempGraphicObject.setAngle(90);
	tempGraphicObject.setСolor(vec3(0, 0, 1));
	tempGraphicObject.setMaterial(materials[2]);
	graphicObjects.push_back(tempGraphicObject);
	// 4 -----------------------------------------
	tempGraphicObject.setPosition(vec3(0, 0, -5));
	tempGraphicObject.setAngle(-90);
	tempGraphicObject.setСolor(vec3(0, 1, 1));
	tempGraphicObject.setMaterial(materials[3]);
	graphicObjects.push_back(tempGraphicObject);

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана через 20 мс
	glutIdleFunc(simulation);

	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(keyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
};