#ifndef custom_math_h
#define custom_math_h

#include <algorithm>
using std::sort;

#include <limits>
using std::numeric_limits;

#include <vector>
using std::vector;

#include <set>
using std::set;

#include <map>
using std::map;


#include <iostream>
using std::cout;
using std::endl;

#include <cmath>
#include <cstdlib>





#include <boost/multiprecision/cpp_bin_float.hpp>

using namespace boost::multiprecision;

//

typedef cpp_bin_float_double MyBig;
typedef cpp_bin_float_20 MySmall;


namespace custom_math
{
	class vector_3;

	 MyBig pi = 4.0 * atan(1.0);
	 MyBig pi_half = pi / 2.0;
	 MyBig pi_2 = pi * 2.0;
	 MyBig epsilon = 1e-6;


 MyBig d( MyBig &a, MyBig &b);
 MyBig d_3(const vector_3 &a, const vector_3 &b);
	 MyBig d_3_sq(const vector_3 &a, const vector_3 &b);
};

class custom_math::vector_3
{
public:
	 MyBig x = 0, y = 0, z = 0;

	 custom_math::vector_3(const MyBig src_x, const MyBig src_y, const MyBig src_z)
	 {
		 x = src_x;
		 y = src_y;
		 z = src_z;
	 }

	 custom_math::vector_3(const double src_x, const double src_y, const double src_z)
	 {
		 x = src_x;
		 y = src_y;
		 z = src_z;
	 }

	 custom_math::vector_3(void)
	 {
		 x = 0;
		 y = 0;
		 z = 0;
	 }

	bool operator==(const vector_3 &rhs);
	bool operator!=(const vector_3 &rhs);
	void zero(void);
	void rotate_x(  MyBig radians);
	void rotate_y(  MyBig radians);
    void rotate_z(  MyBig radians);
    vector_3 operator+( vector_3 &rhs);
	vector_3 operator-( vector_3 &rhs);
	vector_3 operator*( vector_3 &rhs);
	vector_3 operator*(  MyBig rhs);
	vector_3 operator/(  MyBig rhs);
	vector_3 operator=( vector_3 &rhs);
	vector_3 operator+=( vector_3 rhs);
	vector_3 operator+=(MyBig rhs);
	vector_3 operator*=( vector_3 &rhs);
	vector_3 operator*=(  MyBig rhs);
	vector_3 operator-(void);
	 MyBig length(void) const;
	vector_3 &normalize(void);
	 MyBig dot(const vector_3 &rhs) const;
	 MyBig self_dot(void) const;
	vector_3 cross(const vector_3 &rhs) const;
};

#endif