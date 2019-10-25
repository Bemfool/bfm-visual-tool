#pragma once
#include <iostream>
#include <vector>
#include "vec3.h"
#include "data.h"
#include "random.h"
#include "constant.h"

extern std::vector<vec3> shape_mu;
extern std::vector<double> shape_ev;
extern std::vector<std::vector<vec3>> shape_pc;
extern std::vector<vec3> tex_mu;
extern std::vector<double> tex_ev;
extern std::vector<std::vector<vec3>> tex_pc;
extern std::vector<vec3> tl;

/* For Users */
bool init_bfm(d_type type = BINARY_DATA);
void generate_random_face(std::vector<vec3> &shape, std::vector<vec3> &tex, double scale = 1.0);
void save_ply(string filename, const std::vector<vec3> &shape, const std::vector<vec3> &tex);

/* For Programmers */
std::vector<vec3> coef2object(std::vector<double> &coef, 
	std::vector<vec3> &mu, std::vector<std::vector<vec3>> &pc, std::vector<double> &ev);
void ply_write(std::string fn, std::vector<vec3> shape, std::vector<vec3> tex, std::vector<vec3> tl);