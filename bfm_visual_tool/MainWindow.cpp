#include "MainWindow.h"

double SLIDER_STEP = 0.01;
double SLIDER_SCALE = 1.0 / SLIDER_STEP;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	statusBar()->showMessage("loading...", 3000);
	init_bfm();
	initUI();
	initSignalSlots();
	setWindowTitle("Tools for Basel Face Model");
	statusBar()->showMessage("ready");
}

void MainWindow::initUI()
{
	genRndFaceBtn = ui.centralWidget->findChild<QPushButton *>("genRndFaceBtn");
	savePlyBtn = ui.centralWidget->findChild<QPushButton *>("savePlyBtn");
	setShapePcBtn = ui.centralWidget->findChild<QPushButton *>("setShapePcBtn");
	setTexPcBtn = ui.centralWidget->findChild<QPushButton *>("setTexPcBtn");

	rndRangeSlider = ui.centralWidget->findChild<QSlider *>("rndRangeSlider");
	shapeSlider = ui.centralWidget->findChild<QSlider *>("shapeSlider");
	texSlider = ui.centralWidget->findChild<QSlider *>("texSlider");

	shapeComboBox = ui.centralWidget->findChild<QComboBox *>("shapeComboBox");
	texComboBox = ui.centralWidget->findChild<QComboBox *>("texComboBox");
	for (int i = 1; i <= 199; i++) {
		shapeComboBox->addItem(QString::number(i));
		texComboBox->addItem(QString::number(i));
	}

	saveFilename = ui.centralWidget->findChild<QTextEdit *>("saveFilename");
	openGLWidget = ui.centralWidget->findChild<OpenGLWidget *>("openGLWidget");
}

void MainWindow::initSignalSlots()
{
	QObject::connect(genRndFaceBtn, SIGNAL(clicked()), this, SLOT(generateRandomFace()));
	QObject::connect(setShapePcBtn, SIGNAL(clicked()), this, SLOT(setShapePc()));
	QObject::connect(setTexPcBtn, SIGNAL(clicked()), this, SLOT(setTexPc()));

	QObject::connect(shapeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(synShapeSlider()));
	QObject::connect(texComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(synTexSlider()));

	QObject::connect(savePlyBtn, SIGNAL(clicked()), this, SLOT(savePly()));
}

void MainWindow::generateRandomFace()
{
	statusBar()->showMessage("generating...", 3000);
	generate_random_face(rndRangeSlider->value() / SLIDER_SCALE);
	openGLWidget->update();
	synShapeSlider();
	synTexSlider();
}

void MainWindow::synShapeSlider()
{
	int pc = shapeComboBox->currentIndex();
	shapeSlider->setValue(int(alpha[pc] * SLIDER_SCALE));
}


void MainWindow::synTexSlider()
{
	int pc = texComboBox->currentIndex();
	texSlider->setValue(int(beta[pc] * SLIDER_SCALE));
}


void MainWindow::setShapePc()
{
	if (shape.empty()) {
		QDialog *dialog = new QDialog;
		dialog->setModal(true);
		dialog->resize(300, 100);
		QLabel *label = new QLabel(dialog);
		label->setText("Generate a face first.");
		dialog->exec();
		
		return;
	}

	int pc = shapeComboBox->currentIndex();
	double pcValue = shapeSlider->value() / SLIDER_SCALE;
	alpha[pc] = pcValue;
	generate_face();
	openGLWidget->update();
}

void MainWindow::setTexPc()
{
	if (tex.empty()) {
		QDialog *dialog = new QDialog;
		dialog->setModal(true);
		dialog->resize(300, 100);
		QLabel *label = new QLabel(dialog);
		label->setText("Generate a face first.");
		dialog->exec();
		return;
	}

	int pc = texComboBox->currentIndex();
	double pcValue = texSlider->value() / SLIDER_SCALE;
	beta[pc] = pcValue;
	generate_face();
	openGLWidget->update();
}

void MainWindow::savePly()
{
	std::string filename = saveFilename->toPlainText().toStdString();

	/* Make sure filename is like *.ply format (default filename = rnd_face.ply) */
	int fSize = filename.size();
	if (fSize == 0)
		filename = "rnd_face.ply";
	else if (fSize <= 4 || filename.substr(fSize - 4) != ".ply")
		filename = filename + ".ply";

	ply_write(filename);
	QDialog *dialog = new QDialog;
	dialog->setModal(true);
	dialog->resize(300, 100);
	QLabel *label = new QLabel(dialog);
	label->setText("save - success");
	dialog->exec();
}