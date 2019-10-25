#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include <qdebug.h>
#include "bfm.h"

class vec3;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLWidget(QWidget *parent = nullptr);

public:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	bool needUpdate = true;
};
