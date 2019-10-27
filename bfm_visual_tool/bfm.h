#pragma once
#include <iostream>
#include <vector>
#include "vec3.h"
#include "data.h"
#include "random.h"
#include "constant.h"
#ifdef USE_QT
#include <qdebug.h>
#endif

extern std::vector<double> alpha;
extern std::vector<double> beta;

extern std::vector<vec3> shape_mu;
extern std::vector<double> shape_ev;
extern std::vector<std::vector<vec3>> shape_pc;
extern std::vector<vec3> tex_mu;
extern std::vector<double> tex_ev;
extern std::vector<std::vector<vec3>> tex_pc;
extern std::vector<vec3> tl;

extern std::vector<vec3> shape;
extern std::vector<vec3> tex;

/* For Users */
bool init_bfm(d_type type = HDF5_DATA);
void generate_random_face(double scale = 1.0);
void generate_face();
void save_ply(string filename);

/* For Programmers */
std::vector<vec3> coef2object(std::vector<double> &coef, 
	std::vector<vec3> &mu, std::vector<std::vector<vec3>> &pc, std::vector<double> &ev);
void ply_write(std::string fn);