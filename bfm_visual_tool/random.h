#pragma once
#include <random>
#include <time.h>
#include <dlib/matrix.h>

/* Function: randn
* Usage:
*		std::vector<double> seq = randn(n);
*		std::vector<double> seq = randn(n, scale);
* Parameters:
*		n - The number of random element to be generated.
* -------------------------------------------------------------
* Generate a sequence of random numbers into a vector sequence.
* Its distribution is normal distribution whose sigma = 0 ,and
* miu = 1.
*/

dlib::matrix<double> randn(int n, double scale);