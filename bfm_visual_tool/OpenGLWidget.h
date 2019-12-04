#pragma once
/*********************************************************************

Author: Bemfoo
Date: 2019-10-26
Description: A Qt5 widget implemented by built-in OpenGL to show Basel
face model.

**********************************************************************/

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <GL/glu.h>
#include <qevent.h>
#include <dlib/matrix.h>

class QMouseEvent;
class QKeyEvent;

/*
 * Class: OpenGLWidget
 * --------------------------------------------------------------------
 * The widget is used to show generated face.
 */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLWidget(QWidget *parent = Q_NULLPTR);

public:
	void initializeGL()			Q_DECL_OVERRIDE;
	void paintGL()				Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;


	/*
	 * Function: mouseMoveEvent
	 * ------------------------------------------------------------
	 * When mouse move, rotate model in the direction judged by the
	 * relative position between current X and oldX.
	 */

	void mouseMoveEvent(QMouseEvent *event);


	/*
	 * Function: mousePressEvent
	 * -------------------------------------------------------------
	 * When mouse clicks, mark current X pos as oldX.
	 */

	void mousePressEvent(QMouseEvent *event);

public:
	double oldX;		/* last position of mouse, used for rotation */
	double theta = 0.0;		/* rotation degree */
	double scale = 1.0;		/* zooming scale */

	dlib::matrix<double> shape;
	dlib::matrix<double> tex;
	dlib::matrix<double> tl;
};
