#include "bfm.h"

bfm::bfm(const std::string &filename) {
	init(filename);
}


void bfm::init(const std::string &filename) {
	if (!read_parm_from_file(filename))
		return;
	init_parm();
	load_data();
}


void bfm::data_check() {
	bfm_out << "check data\n";
	bfm_out << "	(1) shape mu: \n";
	bfm_out << "		Yours:   " << shape_mu(0, 0) << "\n";
	bfm_out << "		Correct: -57239 42966 80410\n\n";
	bfm_out << "	(2) shape ev: \n";
	bfm_out << "		Yours:   " << shape_ev(0, 0) << " " << shape_ev(1, 0) << "\n";
	bfm_out << "		Correct: 884340 555880\n\n";
	bfm_out << "	(3) shape pc: \n";
	bfm_out << "		Yours:   " << shape_pc(0, 0) << "\n";
	bfm_out << "		Correct: -0.0024\n\n";
	bfm_out << "	(4) texture mu: \n";
	bfm_out << "		Yours:   " << tex_mu(0, 0) << endl;
	bfm_out << "		Correct: 182.8750 135.0400 107.1400\n" << endl;
	bfm_out << "	(5) texture ev: \n";
	bfm_out << "		Yours:   " << tex_ev(0) << " " << tex_ev(1) << "\n";
	bfm_out << "		Correct: 4103.2 2024.1\n\n";
	bfm_out << "	(6) texture pc: \n";
	bfm_out << "		Yours:   " << tex_pc(0, 0) << "\n";
	bfm_out << "		Correct: -0.0028\n\n";
	bfm_out << "	(7) expression mu: \n";
	bfm_out << "		Yours:   " << expr_mu(0, 0) << endl;
	bfm_out << "		Correct: 182.8750 135.0400 107.1400\n" << endl;
	bfm_out << "	(8) expression ev: \n";
	bfm_out << "		Yours:   " << expr_ev(0) << " " << expr_ev(1) << "\n";
	bfm_out << "		Correct: 4103.2 2024.1\n\n";
	bfm_out << "	(9) expression pc: \n";
	bfm_out << "		Yours:   " << expr_pc(0, 0) << "\n";
	bfm_out << "		Correct: -0.0028\n\n";
	bfm_out << "	(10) triangle list: \n";
	bfm_out << "		Yours:   " << tl(0) << " " << tl(1) << "\n";
	bfm_out << "		Correct: -0.0028\n\n";
}


bool bfm::read_parm_from_file(const std::string &filename) {
	ifstream in(filename, std::ios::in);
	if (!in) {
		bfm_out << "[ERROR] Can't open " << filename.c_str() << ".\n";
		return false;
	}
	in >> bfm_h5_path;
	in >> n_vertice >> n_face >> n_id_pc >> n_expr_pc;
	in >> n_landmark >> landmark_idx_path;
	in >> intrinsic_parm[0] >> intrinsic_parm[1] >> intrinsic_parm[2] >> intrinsic_parm[3];
	in >> shape_mu_h5_path >> shape_ev_h5_path >> shape_pc_h5_path;
	in >> tex_mu_h5_path >> tex_ev_h5_path >> tex_pc_h5_path;
	in >> expr_mu_h5_path >> expr_ev_h5_path >> expr_pc_h5_path;
	in >> tl_h5_path;

	in.close();
	return true;
}


void bfm::init_parm() {
	shape_coef.set_size(n_id_pc, 1);
	shape_mu.set_size(n_vertice * 3, 1);
	shape_ev.set_size(n_id_pc, 1);
	shape_pc.set_size(n_vertice * 3, n_id_pc);

	tex_coef.set_size(n_id_pc, 1);
	tex_mu.set_size(n_vertice * 3, 1);
	tex_ev.set_size(n_id_pc, 1);
	tex_pc.set_size(n_vertice * 3, n_id_pc);

	expr_coef.set_size(n_expr_pc, 1);
	expr_mu.set_size(n_vertice * 3, 1);
	expr_ev.set_size(n_expr_pc, 1);
	expr_pc.set_size(n_vertice * 3, n_expr_pc);

	tl.set_size(n_face * 3, 1);

	current_shape.set_size(n_vertice * 3, 1);
	current_tex.set_size(n_vertice * 3, 1);
	current_expr.set_size(n_vertice * 3, 1);
	current_blendshape.set_size(n_vertice * 3, 1);

	landmark_idx.resize(n_landmark);
}


bool bfm::load_data() {
	float *shape_mu_raw = new float[n_vertice * 3];
	float *shape_ev_raw = new float[n_id_pc];
	float *shape_pc_raw = new float[n_vertice * 3 * n_id_pc];
	float *tex_mu_raw = new float[n_vertice * 3];
	float *tex_ev_raw = new float[n_id_pc];
	float *tex_pc_raw = new float[n_vertice * 3 * n_id_pc];
	float *expr_mu_raw = new float[n_vertice * 3];
	float *expr_ev_raw = new float[n_expr_pc];
	float *expr_pc_raw = new float[n_vertice * 3 * n_expr_pc];
	unsigned int *tl_raw = new unsigned int[n_face * 3];

	H5File file(bfm_h5_path, H5F_ACC_RDONLY);
	load_hdf5_model(shape_mu, shape_mu_h5_path, PredType::NATIVE_FLOAT);
	load_hdf5_model(shape_ev, shape_ev_h5_path, PredType::NATIVE_FLOAT);
	load_hdf5_model(shape_pc, shape_pc_h5_path, PredType::NATIVE_FLOAT);

	load_hdf5_model(tex_mu, tex_mu_h5_path, PredType::NATIVE_FLOAT);
	load_hdf5_model(tex_ev, tex_ev_h5_path, PredType::NATIVE_FLOAT);
	load_hdf5_model(tex_pc, tex_pc_h5_path, PredType::NATIVE_FLOAT);

	load_hdf5_model(expr_mu, expr_mu_h5_path, PredType::NATIVE_FLOAT);
	load_hdf5_model(expr_ev, expr_ev_h5_path, PredType::NATIVE_FLOAT);
	load_hdf5_model(expr_pc, expr_pc_h5_path, PredType::NATIVE_FLOAT);

	load_hdf5_model(tl, tl_h5_path, PredType::NATIVE_UINT32);
	file.close();

	shape_mu = shape_mu * 1000.0;

	ifstream in(landmark_idx_path, std::ios::in);
	if (!in) {
		bfm_out << "[ERROR] Can't open " << landmark_idx_path.c_str() << ".\n";
		return false;
	}
	for (int i = 0; i < n_landmark; i++) {
		int tmp_idx;
		in >> tmp_idx;
		landmark_idx[i] = tmp_idx - 1;
	}
	bfm_out << "[bfm] load data - success.\n";
	return true;
}


void bfm::generate_random_face(double scale) {
	shape_coef = randn(n_id_pc, scale);
	tex_coef = randn(n_id_pc, scale);
	expr_coef = randn(n_expr_pc, scale);
	generate_face();
}


void bfm::generate_random_face(double shape_scale, double tex_scale, double expr_scale) {
	shape_coef = randn(n_id_pc, shape_scale);
	tex_coef = randn(n_id_pc, tex_scale);
	expr_coef = randn(n_expr_pc, expr_scale);
	generate_face();
}


void bfm::generate_face() {
	current_shape = coef2object(shape_coef, shape_mu, shape_pc, shape_ev);
	current_tex = coef2object(tex_coef, tex_mu, tex_pc, tex_ev);
	current_expr = coef2object(expr_coef, expr_mu, expr_pc, expr_ev);
	current_blendshape = current_shape + current_expr;
}


dlib::matrix<double> bfm::coef2object(dlib::matrix<double> &coef, dlib::matrix<double> &mu,
	dlib::matrix<double> &pc, dlib::matrix<double> &ev) {
	return mu + pc * pointwise_multiply(coef, ev);
}


void bfm::ply_write(string fn, bool pick_landmark) {
	ofstream out;
	/* Note: In Linux Cpp, we should use std::ios::bfm_out as flag, which is not necessary in Windows */
	out.open(fn, std::ios::out | std::ios::binary);
	if (!out) {
		bfm_out << "Creation of " << fn.c_str() << " failed.\n";
		return;
	}
	out << "ply\n";
	out << "format binary_little_endian 1.0\n";
	out << "comment Made from the 3D Morphable Face Model of the Univeristy of Basel, Switzerland.\n";
	out << "element vertex " << n_vertice << "\n";
	out << "property float x\n";
	out << "property float y\n";
	out << "property float z\n";
	out << "property uchar red\n";
	out << "property uchar green\n";
	out << "property uchar blue\n";
	out << "element face " << n_face << "\n";
	out << "property list uchar int vertex_indices\n";
	out << "end_header\n";

	int cnt = 0;
	for (int i = 0; i < 68; i++)
		std::cout << " " << landmark_idx[i] << std::endl;

	for (int i = 0; i < n_vertice; i++) {
		float x = float(current_blendshape(i * 3));
		float y = float(current_blendshape(i * 3 + 1));
		float z = float(current_blendshape(i * 3 + 2));
		unsigned char r, g, b;
		if (find(landmark_idx.begin(), landmark_idx.end(), i) != landmark_idx.end()) {
			r = 255;
			g = 0;
			b = 0;
			cnt++;
		}
		else {
			r = current_tex(i * 3);
			g = current_tex(i * 3 + 1);
			b = current_tex(i * 3 + 2);
		}
		out.write((char *)&x, sizeof(x));
		out.write((char *)&y, sizeof(y));
		out.write((char *)&z, sizeof(z));
		out.write((char *)&r, sizeof(r));
		out.write((char *)&g, sizeof(g));
		out.write((char *)&b, sizeof(b));
	}
	if (pick_landmark && cnt != n_landmark) {
		bfm_out << "[ERROR] Pick too less landmarks.\n";
		bfm_out << "Number of picked points is " << cnt << ".\n";
	}

	unsigned char N_VER_PER_FACE = 3;
	for (int i = 0; i < n_face; i++) {
		out.write((char *)&N_VER_PER_FACE, sizeof(N_VER_PER_FACE));
		int x = tl(i * 3) - 1;
		int y = tl(i * 3 + 1) - 1;
		int z = tl(i * 3 + 2) - 1;
		out.write((char *)&y, sizeof(y));
		out.write((char *)&x, sizeof(x));
		out.write((char *)&z, sizeof(z));
	}
	out.close();
}