#include "data.h"

std::vector<double> alpha;
std::vector<double> beta;

std::vector<vec3> shape_mu(N_VERTICE);
std::vector<double> shape_ev(N_PC);
std::vector<std::vector<vec3>> shape_pc(N_PC);
std::vector<vec3> tex_mu(N_VERTICE);
std::vector<double> tex_ev(N_PC);
std::vector<std::vector<vec3>> tex_pc(N_PC);
std::vector<vec3> tl(N_FACE);

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
#ifdef USE_QT
	//dialog->close();
#endif 
	return (res < 0) ? FAIL : SUCCESS;
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
