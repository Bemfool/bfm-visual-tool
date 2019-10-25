#include "bfm.h"

bool init_bfm(d_type type) {
	for (int i = 0; i < N_PC; i++) {
		shape_pc[i].resize(N_VERTICE);
		tex_pc[i].resize(N_VERTICE);
	}
	if (load(type) == FAIL) {
		cout << "failed to load all data, and errors are listed above." << endl;
		cout << "continue or not? [Y/n] ";
		char option;
		while (true) {
			cin >> option;
			if (option == 'Y' || option == 'y')
				break;
			else if (option == 'N' || option == 'n') {
				system("pause");
				return false;
			}
			else
				cout << "please input 'Y'/'y' or 'N'/'n'." << endl;
		}
	}
	else {
		cout << "load data - success" << endl;
	}
	return true;
}


void generate_random_face(std::vector<vec3> &shape, std::vector<vec3> &tex, double scale) {
	cout << "generate random face" << endl;
	cout << "	generate random sequence - ";
	vector<double> alpha = randn(N_PC, scale);
	vector<double> beta = randn(N_PC, scale);
	cout << "success" << endl;

	cout << "	pca - ";
	shape = coef2object(alpha, shape_mu, shape_pc, shape_ev);
	tex = coef2object(beta, tex_mu, tex_pc, tex_ev);
	cout << "success" << endl;
}


void save_ply(string filename, const std::vector<vec3> &shape, const std::vector<vec3> &tex) {
	cout << "	write into .ply file - ";
	ply_write("random_face.ply", shape, tex, tl);
	cout << "success" << endl;
}


vector<vec3> coef2object(vector<double> &coef, vector<vec3> &mu, vector<vector<vec3>> &pc, vector<double> &ev) {
	vector<double> temp = dot(coef, ev);
	return mu + pc * temp;
}

void ply_write(string fn, vector<vec3> shape, vector<vec3> tex, vector<vec3> tl) {
	ofstream out;
	out.open(fn, std::ios::binary);
	if (!out) {
		std::cout << "Creation of " << fn << " failed." << std::endl;
		return;
	}
	out << "ply\n";
	out << "format binary_little_endian 1.0\n";
	out << "comment Made from the 3D Morphable Face Model of the Univeristy of Basel, Switzerland.\n";
	out << "element vertex " << N_VERTICE << "\n";
	out << "property float x\n";
	out << "property float y\n";
	out << "property float z\n";
	out << "property uchar red\n";
	out << "property uchar green\n";
	out << "property uchar blue\n";
	out << "element face " << N_FACE << "\n";
	out << "property list uchar int vertex_indices\n";
	out << "end_header\n";

	for (int i = 0; i < N_VERTICE; i++) {
		float x = float(shape[i].x);
		float y = float(shape[i].y);
		float z = float(shape[i].z);
		unsigned char r = tex[i].x;
		unsigned char g = tex[i].y;
		unsigned char b = tex[i].z;
		out.write((char *)&x, sizeof(x));
		out.write((char *)&y, sizeof(y));
		out.write((char *)&z, sizeof(z));
		out.write((char *)&r, sizeof(r));
		out.write((char *)&g, sizeof(g));
		out.write((char *)&b, sizeof(b));
	}

	unsigned char N_VER_PER_FACE = 3;
	for (int i = 0; i < N_FACE; i++) {
		out.write((char *)&N_VER_PER_FACE, sizeof(N_VER_PER_FACE));
		tl[i] = tl[i] - 1;
		int x = tl[i].x;
		int y = tl[i].y;
		int z = tl[i].z;
		out.write((char *)&y, sizeof(y));
		out.write((char *)&x, sizeof(x));
		out.write((char *)&z, sizeof(z));
	}
	out.close();
}

