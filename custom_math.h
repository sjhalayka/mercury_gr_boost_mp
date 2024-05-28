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

using cpp_bin_float_20_ = number<backends::cpp_bin_float<20, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_21_ = number<backends::cpp_bin_float<21, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_22_ = number<backends::cpp_bin_float<22, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_23_ = number<backends::cpp_bin_float<23, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_24_ = number<backends::cpp_bin_float<24, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_25_ = number<backends::cpp_bin_float<25, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_26_ = number<backends::cpp_bin_float<26, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_27_ = number<backends::cpp_bin_float<27, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_28_ = number<backends::cpp_bin_float<28, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_29_ = number<backends::cpp_bin_float<29, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_30_ = number<backends::cpp_bin_float<30, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;





using cpp_bin_float_35_ = number<backends::cpp_bin_float<35, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_40_ = number<backends::cpp_bin_float<40, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_45_ = number<backends::cpp_bin_float<45, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_50_ = number<backends::cpp_bin_float<50, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;
using cpp_bin_float_55_ = number<backends::cpp_bin_float<55, backends::digit_base_2, void, std::int16_t, -126, 127>, et_off >;

using cpp_bin_float_100_ = number<backends::cpp_bin_float<100, backends::digit_base_2, void, std::int16_t, -1022, 1023>, et_off >;


typedef cpp_bin_float_100_ MyBig;
typedef cpp_bin_float_24_ MySmall;


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