#pragma once
#include <string>

#define USE_QT true

#ifdef USE_QT
	#include <QDebug>
	#define bfm_out qDebug()
#else
	#define bfm_out std::cout
#endif

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