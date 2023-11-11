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
// ���������� ������������ ���� ����������� ����������
using namespace glm;
using namespace std;

// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

vector<vec3> color{ vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(0.5, 0.0, 1.0) };
//std::vector<vec3> color1 { 1.0, 0.0, 1.0 };

float r = 1;
float g = 0.5;
float b = 0.5;


// ������ ����������� ��������
vector <GraphicObject> graphicObjects;

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
Light light(vec3(10, 0, 10));

// ������������ ���������
std::vector<std::shared_ptr<PhongMaterial>> materials;

void display(void)
{
	
	// �������� ����� ����� � ����� �������
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ������������� ������
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
	// ������� ��� ����������� �������
	for (auto& go : graphicObjects) {
		go.draw();
		
	}
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};
int count_color = 0;
// ������� ���������� ������ 20 ��
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
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	//glutTimerFunc(20, simulation, 0);
};



// ������� ��������� ������� ������

void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	// ��� �������� ������ ������ �������� ������ ������������
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
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("Laba_01");

	// ������������� ������, ����������� ��� ������ ���������:
	// ������������� ����������� ��������

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
	tempGraphicObject.set�olor(vec3(1, 0, 0));
	tempGraphicObject.setMaterial(materials[0]);
	graphicObjects.push_back(tempGraphicObject);
	// 2 -----------------------------------------
	tempGraphicObject.setPosition(vec3(-5, 0, 0));
	tempGraphicObject.setAngle(0);
	tempGraphicObject.set�olor(vec3(0, 1, 0));
	tempGraphicObject.setMaterial(materials[1]);
	graphicObjects.push_back(tempGraphicObject);
	// 3 -----------------------------------------
	tempGraphicObject.setPosition(vec3(0, 0, 5));
	tempGraphicObject.setAngle(90);
	tempGraphicObject.set�olor(vec3(0, 0, 1));
	tempGraphicObject.setMaterial(materials[2]);
	graphicObjects.push_back(tempGraphicObject);
	// 4 -----------------------------------------
	tempGraphicObject.setPosition(vec3(0, 0, -5));
	tempGraphicObject.setAngle(-90);
	tempGraphicObject.set�olor(vec3(0, 1, 1));
	tempGraphicObject.setMaterial(materials[3]);
	graphicObjects.push_back(tempGraphicObject);

	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// ������������� �������, ������� ����� ������� ����� 20 ��
	glutIdleFunc(simulation);

	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(keyboardFunc);

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
};