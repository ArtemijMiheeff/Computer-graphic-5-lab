#include "PhongMaterial.h"



PhongMaterial::PhongMaterial()
{
	ambient = vec4(0.0, 0.4, 0.0, 1.0);
	emission = vec4(0.0, 0.0, 0.0, 1.0);
	diffuse = vec4(0, 1, 0, 1);
	specular = vec4(1.0, 1.0, 1.0, 1.0);
	shininess = 32.0;
}
void PhongMaterial::setEmission(vec4 color)
{
	emission = color;
}
void PhongMaterial::setAmbient(vec4 color)
{
	ambient = color;
}
void PhongMaterial::setDiffuse(vec4 color)
{
	diffuse = color;
}
void PhongMaterial::setSpecular(vec4 color)
{
	specular = color;
}
void PhongMaterial::setShininess(float p)
{
	shininess = p;
}
void PhongMaterial::load(std::string filename) {
	ifstream File;
	string line;
	string key;
	string new_key;
	float r, g, b, a;
	File.open(filename);
	if (!File.is_open()) {
		cout << "Error material fail\n";
	}
	else {
		cout << "File open\n";
	}
	while (!File.eof()) {
		getline(File, line);
		std::istringstream iss(line);
		iss >> key >> r >> g >> b >> a;
		new_key = key.substr(0, key.length() - 1);
		cout << new_key<<" " << r << " " << g<<" " << b <<" " << a<<" " << endl;
		if (new_key=="diffuse")
		{
			setDiffuse(vec4(r, g, b, a));
		}
		else if (new_key == "ambient")
		{
			setAmbient(vec4(r, g, b, a));
		}
		else if (new_key == "specular")
		{
			setSpecular(vec4(r, g, b, a));
		}
		else if (new_key == "emission")
		{
			setEmission(vec4(r, g, b, a));
		}
		else
		{
			setShininess(r);
		}
	}
	File.close();
}

void PhongMaterial::apply()
{
	//GL_FRONT, GL_BACK или GL_FRONT_AND_BACK. 
	GLfloat MaterialAmbient[] = { ambient.x, ambient.y, ambient.z, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
	GLfloat MaterialDiffuse[] = { diffuse.x, diffuse.y, diffuse.z, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
	GLfloat MaterialSpecular[] = { specular.x, specular.y, specular.z, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
	GLfloat MaterialEmission[] = { emission.x, emission.y, emission.z, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, MaterialEmission);
	const GLfloat* shin = &shininess;
	glMaterialfv(GL_FRONT, GL_SHININESS, shin);
}