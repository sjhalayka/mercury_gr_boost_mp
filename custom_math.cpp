
#include "custom_math.h"




//
//custom_math::vector_3( MyBig src_x, MyBig src_y, MyBig src_z)
//{
//	x = src_x;
//	y = src_y;
//	z = src_z;
//}
//
//custom_math::vector_3(double src_x, double src_y, double src_z)
//{
//	x = src_x;
//	y = src_y;
//	z = src_z;
//}

bool custom_math::vector_3::operator==(const vector_3 &rhs)
{
	if(x == rhs.x && y == rhs.y && z == rhs.z)
		return true;

	return false;
}

bool custom_math::vector_3::operator!=(const vector_3 &rhs)
{
	if(x == rhs.x && y == rhs.y && z == rhs.z)
		return false;

	return true;
}

void custom_math::vector_3::zero(void)
{
	x = y = z = 0;
}

void custom_math::vector_3::rotate_x( MyBig radians)
{
	 MyBig t_y = y;

	y = t_y*cos(radians) + z*sin(radians);
	z = t_y*-sin(radians) + z*cos(radians);
}

void custom_math::vector_3::rotate_y( MyBig radians)
{
	 MyBig t_x = x;

	x = t_x*cos(radians) + z*-sin(radians);
	z = t_x*sin(radians) + z*cos(radians);
}

void custom_math::vector_3::rotate_z( MyBig radians)
{
    MyBig t_x = x;
    
    x = t_x*cos(radians) + y*-sin(radians);
    y = t_x*sin(radians) + y*cos(radians);
}

custom_math::vector_3 custom_math::vector_3::operator+( vector_3 &rhs)
{
	vector_3 v;
	v.x = x + rhs.x;
	v.y = y + rhs.y;
	v.z = z + rhs.z;


	return v;
}

custom_math::vector_3 custom_math::vector_3::operator-( vector_3 &rhs)
{
	vector_3 v;
	v.x = this->x - rhs.x;
	v.y = this->y - rhs.y;
	v.z = this->z - rhs.z;

	return v;

	//return vector_3(x - rhs.x, y - rhs.y, z - rhs.z);
}

custom_math::vector_3 custom_math::vector_3::operator*( vector_3 &rhs)
{
	vector_3 v;
	v.x = x * rhs.x;
	v.y = y * rhs.y;
	v.z = z * rhs.z;

	return v;

	//return vector_3(x*rhs.x, y*rhs.y, z*rhs.z);
}

custom_math::vector_3 custom_math::vector_3::operator*( MyBig rhs)
{
	vector_3 v;
	v.x = x * rhs;
	v.y = y * rhs;
	v.z = z * rhs;

	return v;

	//return vector_3(x*rhs, y*rhs, z*rhs);
}

custom_math::vector_3 custom_math::vector_3::operator/( MyBig rhs)
{
	vector_3 v;
	v.x = x / rhs;
	v.y = y / rhs;
	v.z = z / rhs;

	return v;

	//return vector_3(x/rhs, y/rhs, z/rhs);
}

custom_math::vector_3 custom_math::vector_3::operator=( vector_3 &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return *this;

	//x = rhs.x;
	//y = rhs.y;
	//z = rhs.z;
	//return *this;
}

custom_math::vector_3 custom_math::vector_3::operator+=( vector_3 rhs)
{
	//vector_3 v;
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

	return *this;

	//x += rhs.x; y += rhs.y; z += rhs.z;
	//return *this;
}

custom_math::vector_3 custom_math::vector_3::operator+=(MyBig rhs)
{
	//vector_3 v;
	this->x += rhs;
	this->y += rhs;
	this->z += rhs;

	return *this;

	//x += rhs.x; y += rhs.y; z += rhs.z;
	//return *this;
}


custom_math::vector_3 custom_math::vector_3::operator*=( vector_3 &rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z;
	return *this;
}

custom_math::vector_3 custom_math::vector_3::operator*=( MyBig rhs)
{
	x *= rhs; y *= rhs; z *= rhs;
	return *this;
}

custom_math::vector_3 custom_math::vector_3::operator-(void)
{
	vector_3 temp;
	temp.x = -x;
	temp.y = -y;
	temp.z = -z;

	return temp;
}
 MyBig custom_math::vector_3::length(void) const
{
	return sqrt(self_dot());
}

custom_math::vector_3 &custom_math::vector_3::normalize(void)
{
	 MyBig len = length();

	 MyBig one = 1;

	if(len != one)
	{
		x = x / len;
		y = y / len;
		z = z / len;
	}

	return *this;
}
 MyBig custom_math::vector_3::dot(const vector_3 &rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

 MyBig custom_math::vector_3::self_dot(void) const
{
	return x*x + y*y + z*z;
}

custom_math::vector_3 custom_math::vector_3::cross(const vector_3 &rhs) const
{
	vector_3 cross;
	cross.x = y*rhs.z - rhs.y*z;
	cross.y = z*rhs.x - rhs.z*x;
	cross.z = x*rhs.y - rhs.x*y;

	return cross;
}



 MyBig custom_math::d(  MyBig &a,   MyBig &b)
{
	return abs(a - b);
}
 MyBig custom_math::d_3(const vector_3 &a, const vector_3 &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
 MyBig custom_math::d_3_sq(const vector_3 &a, const vector_3 &b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z);
}
