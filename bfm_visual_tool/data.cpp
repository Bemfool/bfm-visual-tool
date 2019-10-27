#include "data.h"

std::vector<double> alpha;
std::vector<double> beta;

std::vector<vec3> shape_mu(N_VERTICE);
std::vector<double> shape_ev(N_PC);
std::vector<std::vector<vec3>> shape_pc(N_PC);
std::vector<vec3> tex_mu(N_VERTICE);
std::vector<double> tex_ev(N_PC);
std::vector<std::vector<vec3>> tex_pc(N_PC);
std::vector<vec3> tl(N_FACE_HDF5);

std::vector<vec3> shape;
std::vector<vec3> tex;

int load(d_type type) {
#ifndef USE_QT
	std::cout << "data list: " << std::endl;
#endif
	ifstream in;
	int res = 0;
	if (type == BINARY_DATA) {
		load_vec3_model(shape_mu, FLOAT_DATA);
		load_seq_model(shape_ev, FLOAT_DATA);
		load_pc_model(shape_pc, FLOAT_DATA);
		load_vec3_model(tex_mu, FLOAT_DATA);
		load_seq_model(tex_ev, FLOAT_DATA);
		load_pc_model(tex_pc, FLOAT_DATA);
		load_vec3_model(tl, DOUBLE_DATA);
	} else if(type == TEXT_DATA){
		load_text_model(shape_mu);
		load_text_model(shape_ev);
		load_pc_model(shape_pc, TEXT_DATA);
		load_text_model(tex_mu);
		load_text_model(tex_ev);
		load_pc_model(tex_pc, TEXT_DATA);
		load_text_model(tl);
	}
	else if (type == HDF5_DATA) {
#ifdef USE_HDF5
		float *shape_mu_raw = new float[N_VERTICE * 3];
		float *shape_ev_raw = new float[N_PC];
		float *shape_pc_raw = new float[N_VERTICE * 3 * N_PC];
		float *tex_mu_raw = new float[N_VERTICE * 3];
		float *tex_ev_raw = new float[N_PC];
		float *tex_pc_raw = new float[N_VERTICE * N_PC * 3];
		unsigned int *tl_raw = new unsigned int[N_FACE_HDF5 * 3];

		H5File file(bfm_h5_path, H5F_ACC_RDONLY);
		load_hdf5_model(shape_mu, "/shape/model/mean", PredType::NATIVE_FLOAT);

		//for (int i = 0; i < N_VERTICE; i++)
		//	qDebug() << i << ": " << shape_mu_raw[i * 3] << endl;

		load_hdf5_model(shape_ev, "/shape/model/pcaVariance", PredType::NATIVE_FLOAT);
		load_hdf5_model(shape_pc, "/shape/model/pcaBasis", PredType::NATIVE_FLOAT);

		//for (int i = 0; i < 10; i++)
		//	qDebug() << shape_pc_raw[i] << " ";
		qDebug() << "??" << endl;
		qDebug() << shape_pc[0][0].x << endl;
		qDebug() << shape_pc[1][0].x << endl;

		load_hdf5_model(tex_mu, "/color/model/mean", PredType::NATIVE_FLOAT);
		load_hdf5_model(tex_ev, "/color/model/pcaVariance", PredType::NATIVE_FLOAT);
		load_hdf5_model(tex_pc, "/color/model/pcaBasis", PredType::NATIVE_FLOAT);
		load_hdf5_model(tl, "/color/representer/cells", PredType::NATIVE_UINT32);
		
		//DataSet tl_data = file.openDataSet("/color/representer/cells");
		//tl_data.read(tl_raw, PredType::NATIVE_UINT32); 
		//tl_data.close(); 
		//raw2vector(tl, tl_raw); 


		//for (int i = 0; i < N_FACE_HDF5; i++)
		//	qDebug() << i << ": " << tl_raw[i * 3] << " " << tl_raw[i * 3 + 1] << " " << tl_raw[i * 3 + 2] << endl;

		//for (int i = 0; i < N_FACE_HDF5; i++)
		//	qDebug() << i << ": " << tl[i].x << " " << tl[i].y << " " << tl[i].z << endl;

		file.close();

		for (int i = 0; i < N_VERTICE; i++) {
			shape_mu[i] = shape_mu[i] * 1000.0;
			tex_mu[i] = tex_mu[i] * 255.0;
			 //qDebug() << i << ": " << shape_mu[i].x << endl;
			 //qDebug() << i << ": " << tex_mu[i].x << " " << tex_mu[i].y << " " << tex_mu[i].z << endl;
		}
#endif
	}
	return (res < 0) ? FAIL : SUCCESS;
}

void raw2vector(std::vector<double> &vec, float *raw) {
	for (int i = 0; i < N_PC; i++)
		vec[i] = raw[i];
}

void raw2vector(std::vector<vec3> &vec, float *raw) {
	for (int i = 0; i < N_VERTICE; i++) {
		vec[i].x = raw[i * 3];
		vec[i].y = raw[i * 3 + 1];
		vec[i].z = raw[i * 3 + 2];
	}
}

void raw2vector(std::vector<vec3> &vec, unsigned int *raw) {
	for (int i = 0; i < N_FACE_HDF5; i++) {
		vec[i].x = raw[i];
		vec[i].y = raw[i + N_FACE_HDF5];
		vec[i].z = raw[i + N_FACE_HDF5 * 2];
	}
}

void raw2vector(std::vector<std::vector<vec3>> &vec, float *raw) {
	for (int i = 0; i < N_VERTICE; i++) {
		for (int j = 0; j < N_PC; j++) {
				vec[j][i].x = raw[j + (i * 3) * N_PC];
				vec[j][i].y = raw[j + (i * 3 + 1) * N_PC];
				vec[j][i].z = raw[j + (i * 3 + 2) * N_PC];
		}
	}
}


void data_check() {
#ifdef USE_QT
	QDialog *dialog = new QDialog;
	dialog->setModal(true);
	dialog->resize(400, 100);
	QLabel *label = new QLabel(dialog);
	label->setText("[WARING]\n Data check available only when cmd mode.");
	label->adjustSize();
	dialog->show();
#else
	cout << "check data" << endl;
	cout << "(1) shape mu: " << endl;
	cout << "Yours:   " << shape_mu[0] << endl;
	cout << "Correct: -57239 42966 80410" << endl;
	cout << endl;
	cout << "(2) shape ev: " << endl;
	cout << "Yours:   " << shape_ev[0] << " " << shape_ev[1] << endl;
	cout << "Correct: 884340 555880" << endl;
	cout << endl;
	cout << "(3) shape pc: " << endl;
	cout << "Yours:   " << shape_pc[0][0].x << endl;
	cout << "Correct: -0.0024" << endl;
	cout << endl;
	cout << "(1) texture mu: " << endl;
	cout << "Yours:   " << tex_mu[0] << endl;
	cout << "Correct: 182.8750 135.0400 107.1400" << endl;
	cout << endl;
	cout << "(2) texture ev: " << endl;
	cout << "Yours:   " << tex_ev[0] << " " << tex_ev[1] << endl;
	cout << "Correct: 4103.2 2024.1" << endl;
	cout << endl;
	cout << "(3) texture pc: " << endl;
	cout << "Yours:   " << tex_pc[0][0].x << endl;
	cout << "Correct: -0.0028" << endl;
	cout << endl;
#endif

}
