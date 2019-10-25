#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	initUI();
	initSignalSlots();
	setWindowTitle("Tools for Basel Face Model");
}

void MainWindow::initUI()
{
	genRndFaceBtn = ui.centralWidget->findChild<QPushButton *>("genRndFaceBtn");
	savePlyBtn = ui.centralWidget->findChild<QPushButton *>("savePlyBtn");
	rndRangeSlider = ui.centralWidget->findChild<QSlider *>("rndRangeSlider");
	rndRangeLabel = ui.centralWidget->findChild<QLabel *>("rndRangeLabel");
	openGLWidget = ui.centralWidget->findChild<OpenGLWidget *>("openGLWidget");
}

void MainWindow::initSignalSlots()
{
	QObject::connect(genRndFaceBtn, SIGNAL(clicked()), this, SLOT(generateRandomFace()));
	QObject::connect(savePlyBtn, SIGNAL(clicked()), this, SLOT(savePly()));
}

void MainWindow::generateRandomFace()
{
	openGLWidget->setUpdatesEnabled(true);
	std::vector<vec3> shape, tex;
	generate_random_face(shape, tex, rndRangeSlider->value() / 10.0);
	openGLWidget->shape = shape;
	openGLWidget->tex = tex;
	openGLWidget->tl = tl;
	openGLWidget->update();

	QDialog *dialog = new QDialog;
	dialog->setModal(true);
	dialog->resize(300, 100);
	QLabel *label = new QLabel(dialog);
	label->setText("Loading...");
	dialog->exec();
}

void MainWindow::savePly()
{
	ply_write("rnd_face.ply", openGLWidget->shape, openGLWidget->tex, openGLWidget->tl);
	QDialog *dialog = new QDialog;
	dialog->setModal(true);
	dialog->resize(300, 100);
	QLabel *label = new QLabel(dialog);
	label->setText("save - success");
	dialog->exec();
}