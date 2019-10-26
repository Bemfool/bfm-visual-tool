#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include <qdebug.h>
#include "bfm.h"
#include "qevent.h"

class vec3;
class QMouseEvent;
class QKeyEvent;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLWidget(QWidget *parent = nullptr);

public:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

public:
	double oldX = -1.0;
	double theta = 0.0;
	double scale = 1.0;
};
