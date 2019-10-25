#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glLoadIdentity();
	gluLookAt(0, 0, 300000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}
void OpenGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 400000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 300000.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void OpenGLWidget::paintGL()
{
	double scale = 1.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!shape.empty()) {
		int count = 0;
		for (auto t = tl.begin(); t != tl.end(); t++) {
			glBegin(GL_TRIANGLES);
			vec3 tmp = *t - 1;
			glColor3f(tex[tmp.x].x / 255.0, tex[tmp.x].y / 255.0, tex[tmp.x].z / 255.0);
			glVertex3f(shape[tmp.x].x * scale, shape[tmp.x].y * scale, shape[tmp.x].z * scale);
			glColor3f(tex[tmp.y].x / 255.0, tex[tmp.y].y / 255.0, tex[tmp.y].z / 255.0);
			glVertex3f(shape[tmp.y].x * scale, shape[tmp.y].y * scale, shape[tmp.y].z * scale);
			glColor3f(tex[tmp.z].x / 255.0, tex[tmp.z].y / 255.0, tex[tmp.z].z / 255.0);
			glVertex3f(shape[tmp.z].x * scale, shape[tmp.z].y * scale, shape[tmp.z].z * scale);
			count++;
			qDebug("%d %lf %lf %lf\n", count, tex[tmp.z].x, tex[tmp.z].y, tex[tmp.z].z);
			qDebug("%d %lf %lf %lf\n", count, shape[tmp.z].x, shape[tmp.z].y, shape[tmp.z].z);
			glEnd();
		}
	}
	else {
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-50000, 0, 0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(50000, 0, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 50000, 0);
		glEnd();
	}
}
