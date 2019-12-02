#pragma once
#include <string>

#define USE_QT true

#ifdef USE_QT == true
#include <QDebug>
#define OUT qDebug()
#else
#define OUT std::cout
#endif

#define FAIL	 -1
#define SUCCESS 0

/* camera type */
typedef int camera_type;
enum {
	PARALLEL = 0,
	PINHOLE = 1,
};

typedef int op_type;
enum {
	COARSE = 0,
	REAL = 1,
};