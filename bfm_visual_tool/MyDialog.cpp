#include "MyDialog.h"

MyDialog::MyDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("hint");

}

MyDialog::~MyDialog()
{
}


void MyDialog::initSignalSlots()
{
	QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

