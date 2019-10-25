#pragma once

#include <QDialog>
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_MyDialog.h"

class QLabel;
class QPushButton;

class MyDialog : public QDialog
{
	Q_OBJECT

public:
	MyDialog(QWidget *parent = Q_NULLPTR);
	~MyDialog();

private:
	Ui::MyDialog ui;
	QLabel *lable;
	QPushButton *btn;
	void initUI();
	void initSignalSlots();
};
