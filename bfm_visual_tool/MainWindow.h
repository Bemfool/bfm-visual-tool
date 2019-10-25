#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qslider.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include "bfm.h"
#include "MyDialog.h"
#include "OpenGLWidget.h"

class QSlider;
class QPushButton;
class QLabel;
class QOpenGLWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private slots: 
	void generateRandomFace();
	void savePly();

private:
	Ui::MainWindowClass ui;
	OpenGLWidget *openGLWidget;
	QPushButton *genRndFaceBtn;
	QPushButton *savePlyBtn;
	QSlider		*rndRangeSlider;
	QLabel		*rndRangeLabel;
	void initUI();
	void initSignalSlots();
};
