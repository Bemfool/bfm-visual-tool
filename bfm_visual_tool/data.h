#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "vec3.h"
#include "constant.h"
#ifdef USE_QT
#include <qdebug.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
#endif 
#ifdef USE_HDF5
#include "H5Cpp.h"
#include "hdf5.h"
using namespace H5;
#endif

using namespace std;

class QDebug;

#ifdef USE_HDF5
#define load_hdf5_model(model_type, dataset_path, data_type) { \
			DataSet model_type##_data = file.openDataSet(dataset_path); \
			model_type##_data.read(model_type##_raw, data_type); \
			model_type##_data.close(); \
			raw2vector(model_type, model_type##_raw); \
		} 
#endif

#ifdef USE_QT
#define load_vec3_model(model_type, data_type) { \
	in.open(model_type##_path_bin, std::ios::binary); \
	if (!in) {	\
		res += FAIL;	\
	} else {	\
		for (auto it = model_type.begin(); it != model_type.end(); it++)	\
			if(data_type == FLOAT_DATA) { \
				float tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->x = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->y = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->z = (double)tmp; \
			} else if(data_type == DOUBLE_DATA) { \
				double tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->x = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->y = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->z = (double)tmp; \
			} \
		in.close();	\
	} \
}

#define load_seq_model(model_type, data_type) { \
	in.open(model_type##_path_bin, std::ios::binary); \
	if (!in) {	\
		res += FAIL;	\
	} else {	\
		for (auto it = model_type.begin(); it != model_type.end(); it++)	\
			if(data_type == FLOAT_DATA) { \
				float tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				*it = (double)tmp; \
			} else { \
				double tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				*it = tmp; \
			} \
		in.close();	\
	} \
}

#define load_text_model(model_type) { \
	in.open(model_type##_path_text); \
	if (!in) {	\
		res += FAIL;	\
	} else {	\
		for (auto it = model_type.begin(); it != model_type.end(); it++)	\
			in >> (*it);	\
		in.close();	\
	} \
}


#define load_pc_model(model_type, data_type) { \
	if(data_type == TEXT_DATA) \
		in.open(model_type##_path_text);	\
	else \
		in.open(model_type##_path_bin, std::ios::binary); \
	if (!in) {	\
		res += FAIL;	\
	} else {	\
		int flag = 0;	\
		for(int i=0; i<N_VERTICE; i++) {	\
			for(int j=0; j<N_PC; j++) {	\
				if(flag == 0)	\
					if(data_type == TEXT_DATA) \
						in >> model_type[j][i].x;	\
					else { \
						float tmp; \
						in.read((char *)&tmp, sizeof(tmp)); \
						model_type[j][i].x = tmp; \
					} \
				else if(flag == 1)	\
					if(data_type == TEXT_DATA) \
						in >> model_type[j][i].y;	\
					else { \
						float tmp; \
						in.read((char *)&tmp, sizeof(tmp)); \
						model_type[j][i].y = tmp; \
					} \
				else  \
					if(data_type == TEXT_DATA) \
						in >> model_type[j][i].z;	\
					else { \
						float tmp; \
						in.read((char *)&tmp, sizeof(tmp)); \
						model_type[j][i].z = tmp; \
					} \
			}	\
			flag = (flag + 1) % 3;	\
			if(flag != 0)	\
				i--;	\
		}	\
		in.close();	\
	}	\
}
#else
#define load_vec3_model(model_type, data_type) { \
	cout << "	" << #model_type << " - ";	\
	in.open(model_type##_path_bin, std::ios::binary); \
	if (!in) {	\
		cout << "fail" << endl;	\
		res += FAIL;	\
	} else {	\
		for (auto it = model_type.begin(); it != model_type.end(); it++)	\
			if(data_type == FLOAT_DATA) { \
				float tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->x = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->y = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->z = (double)tmp; \
			} else if(data_type == DOUBLE_DATA) { \
				double tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->x = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->y = (double)tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				it->z = (double)tmp; \
			} \
		in.close();	\
		cout << "success" << endl;	\
	} \
}

#define load_seq_model(model_type, data_type) { \
	cout << "	" << #model_type << " - ";	\
	in.open(model_type##_path_bin, std::ios::binary); \
	if (!in) {	\
		cout << "fail" << endl;	\
		res += FAIL;	\
	} else {	\
		for (auto it = model_type.begin(); it != model_type.end(); it++)	\
			if(data_type == FLOAT_DATA) { \
				float tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				*it = (double)tmp; \
			} else { \
				double tmp; \
				in.read((char *)&tmp, sizeof(tmp)); \
				*it = tmp; \
			} \
		in.close();	\
		cout << "success" << endl;	\
	} \
}

#define load_text_model(model_type) { \
	cout << "	" << #model_type << " - ";	\
	in.open(model_type##_path_text); \
	if (!in) {	\
		cout << "fail" << endl;	\
		res += FAIL;	\
	} else {	\
		for (auto it = model_type.begin(); it != model_type.end(); it++)	\
			in >> (*it);	\
		in.close();	\
		cout << "success" << endl;	\
	} \
}


#define load_pc_model(model_type, data_type) { \
	cout << "	" << #model_type << " - ";	\
	if(data_type == TEXT_DATA) \
		in.open(model_type##_path_text);	\
	else \
		in.open(model_type##_path_bin, std::ios::binary); \
	if (!in) {	\
		cout << "fail" << endl;	\
		res += FAIL;	\
	} else {	\
		int flag = 0;	\
		for(int i=0; i<N_VERTICE; i++) {	\
			for(int j=0; j<N_PC; j++) {	\
				if(flag == 0)	\
					if(data_type == TEXT_DATA) \
						in >> model_type[j][i].x;	\
					else { \
						float tmp; \
						in.read((char *)&tmp, sizeof(tmp)); \
						model_type[j][i].x = tmp; \
					} \
				else if(flag == 1)	\
					if(data_type == TEXT_DATA) \
						in >> model_type[j][i].y;	\
					else { \
						float tmp; \
						in.read((char *)&tmp, sizeof(tmp)); \
						model_type[j][i].y = tmp; \
					} \
				else  \
					if(data_type == TEXT_DATA) \
						in >> model_type[j][i].z;	\
					else { \
						float tmp; \
						in.read((char *)&tmp, sizeof(tmp)); \
						model_type[j][i].z = tmp; \
					} \
			}	\
			flag = (flag + 1) % 3;	\
			if(flag != 0)	\
				i--;	\
		}	\
		in.close();	\
		cout << "success" << endl;	\
	}	\
}
#endif

void raw2vector(std::vector<double> &vec, float *raw);
void raw2vector(std::vector<vec3> &vec, float *raw);
void raw2vector(std::vector<vec3> &vec, unsigned int *raw);
void raw2vector(std::vector<std::vector<vec3>> &vec, float *raw);
int load(d_type type);
void data_check();