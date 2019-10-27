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
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 600000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 300000.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!shape.empty()) {
		/* human face model */
#ifdef DEBUG
		int count = 0;
#endif
		double sint = sin(theta), cost = cos(theta);
		for (auto t = tl.begin(); t != tl.end(); t++) {
			glBegin(GL_TRIANGLES);
			vec3 tmp = *t;
			glColor3f(tex[tmp.x].x / 255.0, tex[tmp.x].y / 255.0, tex[tmp.x].z / 255.0);
			glVertex3f(shape[tmp.x].x * scale * cost - shape[tmp.x].z * scale * sint, shape[tmp.x].y * scale, shape[tmp.x].x * scale * sint + shape[tmp.x].z * scale * cost);
			glColor3f(tex[tmp.y].x / 255.0, tex[tmp.y].y / 255.0, tex[tmp.y].z / 255.0);
			glVertex3f(shape[tmp.y].x * scale * cost - shape[tmp.y].z * scale * sint, shape[tmp.y].y * scale, shape[tmp.y].x * scale * sint + shape[tmp.y].z * scale * cost);
			glColor3f(tex[tmp.z].x / 255.0, tex[tmp.z].y / 255.0, tex[tmp.z].z / 255.0);
			glVertex3f(shape[tmp.z].x * scale * cost - shape[tmp.z].z * scale * sint, shape[tmp.z].y * scale, shape[tmp.z].x * scale * sint + shape[tmp.z].z * scale * cost);
#ifdef DEBUG
			 count++;
			 qDebug("%d %lf %lf %lf\n", count, tex[tmp.z].x, tex[tmp.z].y, tex[tmp.z].z);
			 qDebug("%d %lf %lf %lf\n", count, shape[tmp.z].x, shape[tmp.z].y, shape[tmp.z].z);
#endif
			glEnd();
		}
	}
	else {
		/* initial scene - triangle */
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-50000 * cos(theta) * scale, 0, 0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(50000 * cos(theta) * scale, 0, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 50000 * scale, 0);
		glEnd();
	}
}


void OpenGLWidget::mousePressEvent(QMouseEvent *event) 
{
	if (event->button() == Qt::LeftButton)
		oldX = event->x();	/* record the current X pos */
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) 
{
	if (event->buttons() & Qt::LeftButton) {
		double clockwise;
		if (event->x() < oldX) 
			clockwise = -1.0;
		else if (event->x() > oldX)
			clockwise = 1.0;
		else
			clockwise = 0;
		oldX = event->x();
		theta += clockwise * 0.1;
		update();
	}
}