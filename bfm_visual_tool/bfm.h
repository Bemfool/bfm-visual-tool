#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "data.h"
#include "random.h"
#include "vec.h"

class bfm {
public:
	bfm(const std::string &filename);
	void data_check();
	void generate_random_face(double scale);
	void generate_random_face(double shape_scale, double tex_scale, double expr_scale);
	void generate_face();
	void ply_write(string fn);
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

	std::vector<double> landmark_idx;
};