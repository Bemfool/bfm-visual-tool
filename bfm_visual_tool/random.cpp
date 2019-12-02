#include "random.h"

dlib::matrix<double> randn(int n, double scale) {
	dlib::matrix<double> res(n, 1);
	std::default_random_engine e;
	e.seed(time(NULL));
	std::normal_distribution<double> dis(0, scale);
	for (int i = 0; i < n; i++)
		res(i) = dis(e);
	return res;
}
