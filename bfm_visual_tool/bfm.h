#pragma once
#include "data.h"
#include "random.h"

class bfm {
public:
	bfm() {}
	bfm(const std::string &filename);
	void init(const std::string &filename);
	void data_check();
	void generate_random_face(double scale = 0.0);
	void generate_random_face(double shape_scale, double tex_scale, double expr_scale);
	void generate_average_face() { generate_random_face(0.0); }
	void generate_face();
	void ply_write(string fn = "rnd_face.ply", bool pick_landmarks = false);
	int get_n_id_pc() { return n_id_pc; }
	int get_n_expr_pc() { return n_expr_pc; }
	int get_n_face() { return n_face; }
	int get_n_vertice() { return n_vertice; }
	dlib::matrix<double> &get_mutable_shape_coef() { return shape_coef; }
	dlib::matrix<double> &get_mutable_tex_coef() { return tex_coef; }
	dlib::matrix<double> &get_mutable_expr_coef() { return expr_coef; }
	const dlib::matrix<double> &get_current_shape() { return current_shape; }
	const dlib::matrix<double> &get_current_tex() { return current_tex; }
	const dlib::matrix<double> &get_current_expr() { return current_expr; }
	const dlib::matrix<double> &get_current_blendshape() { return current_blendshape; }
	const dlib::matrix<double> &get_tl() { return tl; }
private:
	bool read_parm_from_file(const std::string &filename);
	void init_parm();
	bool load_data();
	dlib::matrix<double> coef2object(dlib::matrix<double> &coef, dlib::matrix<double> &mu,
		dlib::matrix<double> &pc, dlib::matrix<double> &ev);

	std::string bfm_h5_path;
	std::string landmark_idx_path;

	std::string shape_mu_h5_path;
	std::string shape_ev_h5_path;
	std::string shape_pc_h5_path;

	std::string tex_mu_h5_path;
	std::string tex_ev_h5_path;
	std::string tex_pc_h5_path;

	std::string expr_mu_h5_path;
	std::string expr_ev_h5_path;
	std::string expr_pc_h5_path;

	std::string tl_h5_path;

	int n_vertice;
	int n_face;
	int n_id_pc;
	int n_expr_pc;
	int n_landmark;

	double external_parm[6] = { 0.f };	/* yaw roll pitch tx ty tz */
	double intrinsic_parm[4] = { 0.f };	/* fx fy cx cy */

	dlib::matrix<double> shape_coef;
	dlib::matrix<double> shape_mu;
	dlib::matrix<double> shape_ev;
	dlib::matrix<double> shape_pc;

	dlib::matrix<double> tex_coef;
	dlib::matrix<double> tex_mu;
	dlib::matrix<double> tex_ev;
	dlib::matrix<double> tex_pc;

	dlib::matrix<double> expr_coef;
	dlib::matrix<double> expr_mu;
	dlib::matrix<double> expr_ev;
	dlib::matrix<double> expr_pc;

	dlib::matrix<double> tl;	/* triangle list */

	dlib::matrix<double> current_shape;
	dlib::matrix<double> current_tex;
	dlib::matrix<double> current_expr;
	dlib::matrix<double> current_blendshape;

	std::vector<int> landmark_idx;
};