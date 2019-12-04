#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "vec.h"
#include "constant.h"
#include "H5Cpp.h"

using namespace H5;
using namespace std;

/* Macro Function: load_hdf5_model
* Usage: load_hdf5_model(model_type, dataset_path, data_type);
* Parameters:
* 		model_type:   data name, e.g. shape_mu;
* 		dataset_path: dataset path in .h5 file, e.g. "/shape/model/mean"
* 		data_type:    data type in dataset, e.g. PredType::NATIVE_FLOAT
* ***********************************************************************
* Load data from .h5 format file into corresponding data struction.
*/

#define load_hdf5_model(model_type, dataset_path, data_type) { \
			DataSet model_type##_data = file.openDataSet(dataset_path); \
			model_type##_data.read(model_type##_raw, data_type); \
			model_type##_data.close(); \
			raw2matrix(model_type, model_type##_raw); \
			delete[] model_type##_raw; \
		} 


template<typename T>
void raw2matrix(dlib::matrix<double> &m, T *raw) {
	bfm_out << "check: " << m.nr() << " " << m.nc() << "\n";
	for (int i = 0; i < m.nr(); i++)
		for (int j = 0; j < m.nc(); j++)
			m(i, j) = raw[i * m.nc() + j];
}
