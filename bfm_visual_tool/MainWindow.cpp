#include "MainWindow.h"

const double SHAPE_SCALE = 0.1;
const double TEX_SCALE = 120;
const double EXPR_SCALE = 0.3;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	statusBar()->showMessage("loading...", 3000);
	model.init("inputs.txt");
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
	setExprPcBtn = ui.centralWidget->findChild<QPushButton *>("setExprPcBtn");

	rndRangeSlider = ui.centralWidget->findChild<QSlider *>("rndRangeSlider");
	shapeSlider = ui.centralWidget->findChild<QSlider *>("shapeSlider");
	texSlider = ui.centralWidget->findChild<QSlider *>("texSlider");
	exprSlider = ui.centralWidget->findChild<QSlider *>("exprSlider");

	shapeComboBox = ui.centralWidget->findChild<QComboBox *>("shapeComboBox");
	texComboBox = ui.centralWidget->findChild<QComboBox *>("texComboBox");
	exprComboBox = ui.centralWidget->findChild<QComboBox *>("exprComboBox");
	for (int i = 1; i <= model.get_n_id_pc(); i++) {
		shapeComboBox->addItem(QString::number(i));
		texComboBox->addItem(QString::number(i));
	}
	for (int i = 1; i <= model.get_n_expr_pc(); i++)
		exprComboBox->addItem(QString::number(i));

	saveFilename = ui.centralWidget->findChild<QTextEdit *>("saveFilename");
	openGLWidget = ui.centralWidget->findChild<OpenGLWidget *>("openGLWidget");
	qDebug() << "[viewer] ui init done.\n";
}

void MainWindow::initSignalSlots()
{
	QObject::connect(genRndFaceBtn, SIGNAL(clicked()), this, SLOT(generateRandomFace()));
	QObject::connect(setShapePcBtn, SIGNAL(clicked()), this, SLOT(setShapePc()));
	QObject::connect(setTexPcBtn, SIGNAL(clicked()), this, SLOT(setTexPc()));
	QObject::connect(setExprPcBtn, SIGNAL(clicked()), this, SLOT(setExprPc()));

	QObject::connect(shapeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(synShapeSlider()));
	QObject::connect(texComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(synTexSlider()));
	QObject::connect(exprComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(synExprSlider()));

	QObject::connect(savePlyBtn, SIGNAL(clicked()), this, SLOT(savePly()));
}

void MainWindow::generateRandomFace()
{
	statusBar()->showMessage("generating...", 3000);
	double sliderVal = (double)rndRangeSlider->value();
	model.generate_random_face(sliderVal / SHAPE_SCALE, sliderVal / TEX_SCALE, sliderVal / EXPR_SCALE);
	openGLWidget->theta = 0.0;
	openGLWidget->scale = 1.0;
	openGLWidget->update();
	synShapeSlider();
	synTexSlider();
	synExprSlider();
}

void MainWindow::synShapeSlider()
{
	int pc = shapeComboBox->currentIndex();
	shapeSlider->setValue(int(model.get_mutable_shape_coef()(pc) * SHAPE_SCALE));
}


void MainWindow::synTexSlider()
{
	int pc = texComboBox->currentIndex();
	texSlider->setValue(int(model.get_mutable_tex_coef()(pc) * TEX_SCALE));
}

void MainWindow::synExprSlider()
{
	int pc = exprComboBox->currentIndex();
	exprSlider->setValue(int(model.get_mutable_expr_coef()(pc) * EXPR_SCALE));
}


void MainWindow::setShapePc()
{
	int pc = shapeComboBox->currentIndex();
	double pcValue = shapeSlider->value() / SHAPE_SCALE;
	model.get_mutable_shape_coef()(pc) = pcValue;
	model.generate_face();
	openGLWidget->update();
}

void MainWindow::setTexPc()
{
	int pc = texComboBox->currentIndex();
	double pcValue = texSlider->value() / TEX_SCALE;
	model.get_mutable_tex_coef()(pc) = pcValue;
	model.generate_face();
	openGLWidget->update();
}

void MainWindow::setExprPc()
{
	int pc = exprComboBox->currentIndex();
	double pcValue = exprSlider->value() / EXPR_SCALE;
	model.get_mutable_expr_coef()(pc) = pcValue;
	model.generate_face();
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

	model.ply_write(filename);
	QDialog *dialog = new QDialog;
	dialog->setModal(true);
	dialog->resize(300, 100);
	QLabel *label = new QLabel(dialog);
	label->setText("save - success");
	dialog->exec();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
	case Qt::Key_A:
		openGLWidget->theta += 0.1;
		break;
	case Qt::Key_D:
		openGLWidget->theta -= 0.1;
		break;
	case Qt::Key_W:
		openGLWidget->scale += 0.1;
		break;
	case Qt::Key_S:
		openGLWidget->scale -= 0.1;
		break;
	default:
		break;
	}
	openGLWidget->update();
}


void MainWindow::wheelEvent(QWheelEvent *event) {
	openGLWidget->scale += event->delta() / 1200.0;
	if (openGLWidget->scale <= 0.0)
		openGLWidget->scale = 0.01;
	openGLWidget->update();
}