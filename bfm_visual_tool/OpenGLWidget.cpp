#include "OpenGLWidget.h"
#include "MainWindow.h"

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
	MainWindow *p = (MainWindow*)(parentWidget()->parentWidget());
	shape = p->getModel().get_current_blendshape();
	tex = p->getModel().get_current_tex();
	tl = p->getModel().get_tl();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (shape.nr()!=0) {
		/* human face model */
		double sint = sin(theta), cost = cos(theta);
		for (int i = 0; i < tl.size()/3; i++) {
			glBegin(GL_TRIANGLES);
			double xIdx = tl(i * 3) - 1;
			double yIdx = tl(i * 3 + 1) - 1;
			double zIdx = tl(i * 3 + 2) - 1;
			glColor3f(tex(xIdx * 3) / 255.0, tex(xIdx * 3 + 1) / 255.0, tex(xIdx * 3 + 2) / 255.0);
			glVertex3f(shape(xIdx * 3) * scale * cost - shape(xIdx * 3 + 2) * scale * sint, shape(xIdx * 3 + 1) * scale, shape(xIdx * 3) * scale * sint + shape(xIdx * 3 + 2) * scale * cost);
			glColor3f(tex(yIdx * 3) / 255.0, tex(yIdx * 3 + 1) / 255.0, tex(yIdx * 3 + 2) / 255.0);
			glVertex3f(shape(yIdx * 3) * scale * cost - shape(yIdx * 3 + 2) * scale * sint, shape(yIdx * 3 + 1) * scale, shape(yIdx * 3) * scale * sint + shape(yIdx * 3 + 2) * scale * cost);
			glColor3f(tex(zIdx * 3) / 255.0, tex(zIdx * 3 + 1) / 255.0, tex(zIdx * 3 + 2) / 255.0);
			glVertex3f(shape(zIdx * 3) * scale * cost - shape(zIdx * 3 + 2) * scale * sint, shape(zIdx * 3 + 1) * scale, shape(zIdx * 3) * scale * sint + shape(zIdx * 3 + 2) * scale * cost);
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