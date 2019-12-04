#pragma once
#include <dlib/matrix.h>
#include <dlib/geometry.h>

/* Definition of 3d coordinate, because dlib only support dlib::point, which is 2d */
typedef dlib::vector<double, 3> point3f;
typedef dlib::vector<int, 3> point3d;
template<typename T> using point3x = dlib::vector<T, 3>;
typedef dlib::point point2d;