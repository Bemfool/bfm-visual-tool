#pragma once
#include <string>

#define USE_QT

static std::string bfm_path = "D:\\database\\bfm\\2009\\PublicMM1\\";

/* Text Format Data (deprecated) */
static std::string shape_mu_path_text = bfm_path + "shapeMU.dat";
static std::string shape_ev_path_text = bfm_path + "shapeEV.dat";
static std::string shape_pc_path_text = bfm_path + "shapePC.dat";
static std::string tex_mu_path_text = bfm_path + "texMU.dat";
static std::string tex_ev_path_text = bfm_path + "texEV.dat";
static std::string tex_pc_path_text = bfm_path + "texPC.dat";
static std::string tl_path_text = bfm_path + "tl.dat";

/* Binary Format Data */
static std::string shape_mu_path_bin = bfm_path + "shapeMU.bin";
static std::string shape_ev_path_bin = bfm_path + "shapeEV.bin";
static std::string shape_pc_path_bin = bfm_path + "shapePC.bin";
static std::string tex_mu_path_bin = bfm_path + "texMU.bin";
static std::string tex_ev_path_bin = bfm_path + "texEV.bin";
static std::string tex_pc_path_bin = bfm_path + "texPC.bin";
static std::string tl_path_bin = bfm_path + "tl.bin";

#define N_VERTICE 53490
#define N_FACE 106466
#define N_PC 199

#define FAIL -1
#define SUCCESS 0

typedef int d_type;
#define BINARY_DATA	0
#define TEXT_DATA	1
#define FLOAT_DATA  2
#define DOUBLE_DATA 3
#define VEC3_DATA   4

inline void set_bfm_path(std::string new_path) { bfm_path = new_path; }