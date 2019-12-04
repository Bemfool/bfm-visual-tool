#pragma once
/*********************************************************************

Author: Bemfoo
Date: 2019-10-26
Description: The main widget window of Basel face model visual tool.

**********************************************************************/

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qslider.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qstatusbar.h>
#include <qdialog.h>
#include "OpenGLWidget.h"
#include <dlib/matrix.h>
#include "bfm.h"

class QSlider;
class QPushButton;
class QLabel;
class QComboBox;
class QOpenGLWidget;
class QKeyEvent;
class QWheelEvent;
class QDialog;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	bfm &getModel() { return model; }
	void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);

private slots: 
	void generateRandomFace();
	void synShapeSlider();
	void synTexSlider();
	void synExprSlider();
	void setShapePc();
	void setTexPc();
	void setExprPc();
	void savePly();

private:
	Ui::MainWindowClass ui;
	
	bfm model;

	OpenGLWidget *openGLWidget;
	QPushButton *genRndFaceBtn;
	QPushButton *savePlyBtn;
	QPushButton *setShapePcBtn;
	QPushButton *setTexPcBtn;
	QPushButton *setExprPcBtn;
	
	QSlider *shapeSlider;
	QSlider *texSlider;
	QSlider *exprSlider;
	QSlider	*rndRangeSlider;

	QComboBox *shapeComboBox;
	QComboBox *texComboBox;
	QComboBox *exprComboBox;

	QTextEdit *saveFilename;

	void initUI();
	void initSignalSlots();
};
