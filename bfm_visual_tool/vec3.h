#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "constant.h"

class vec3 {
public:
	vec3() : x(0), y(0), z(0) {}
	double x;
	double y;
	double z;
};

inline std::istream& operator>>(std::istream& in, vec3& v) {
	in >> v.x >> v.y >> v.z;
	return in;
}

inline std::ostream& operator<<(std::ostream& out, vec3 v) {
	out << v.x << " " << v.y << " " << v.z << std::endl;
	return out;
}

inline vec3 operator*(vec3 &v, double times) {
	vec3 res;
	res.x = v.x * times;
	res.y = v.y * times;
	res.z = v.z * times;
	return res;
}

inline vec3 operator+(const vec3 &lhs, const vec3 &rhs) {
	vec3 ret;
	ret.x = rhs.x + lhs.x;
	ret.y = rhs.y + lhs.y;
	ret.z = rhs.z + lhs.z;
	return ret;
}

inline std::vector<vec3> operator+(const std::vector<vec3> &lhs, const std::vector<vec3> &rhs) {
	std::vector<vec3> res;
	for (int i = 0; i < lhs.size(); i++) 
		res.push_back(lhs.at(i) + rhs.at(i));
	return res;
}

inline std::vector<double> dot(std::vector<double> a, std::vector<double> b) {
	if (a.size() != b.size()) {
		std::cout << "[ERROR] dot size is not compartible." << std::endl;
		std::cout << a.size() << " : " << b.size() << std::endl;
		return a;
	}
	std::vector<double> res;
	for (int i = 0; i<a.size(); i++)
		res.push_back(a.at(i) * b.at(i));
	return res;
}

inline std::vector<vec3> operator*(std::vector<std::vector<vec3>> &a, std::vector<double> &b) {
	std::vector<vec3> res;
	for (int i = 0; i < N_VERTICE; i++) {
		vec3 temp;
		for (int j = 0; j < N_PC; j++)
			temp = temp + a[j][i] * b[j];
		res.push_back(temp);
	}
	return res;
}

inline vec3 operator-(const vec3 &v, const int n) {
	vec3 res;
	res.x = v.x - n;
	res.y = v.y - n;
	res.z = v.z - n;
	return res;
}