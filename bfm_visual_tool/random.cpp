#include "random.h"

std::vector<double> randn(int n, double scale) {
	std::vector<double> res;
	std::default_random_engine e;
	e.seed(time(NULL));
	std::normal_distribution<double> dis(0, scale);
	for (int i = 0; i < n; i++)
		res.push_back(dis(e));
	return res;
}
