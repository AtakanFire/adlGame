#ifndef vector_h__
#define vector_h__
#include "common.h"

class adlVec2
{
public:
	inline adlVec2();
	inline adlVec2(float x, float y);
	inline adlVec2(float value);

	inline static adlVec2 zero();

	/*----Operator overloads----*/
	inline adlVec2 operator+(const adlVec2& vector) const;
	inline adlVec2 operator-(const adlVec2& vector) const;

	inline adlVec2 operator+(float value) const;
	inline adlVec2 operator-(float value) const;
	inline adlVec2 operator*(float value) const;
	inline adlVec2 operator/(float value) const;

	inline bool operator==(const adlVec2& vector) const;
	inline bool operator!=(const adlVec2& vector) const;
	/*--------------------------*/

	float x;
	float y;
};

inline adlVec2::adlVec2()
	: x(0), y(0)
{
}

inline adlVec2::adlVec2(float x, float y)
	: x(x), y(y)
{
}

inline adlVec2::adlVec2(float value)
	: x(value), y(value)
{
}

inline adlVec2 adlVec2::zero()
{
	return adlVec2(0.0f);
}

inline adlVec2 adlVec2::operator+(const adlVec2& vector) const
{
	return adlVec2(x + vector.x, y + vector.y);
}

inline adlVec2 adlVec2::operator-(const adlVec2& vector) const
{
	return adlVec2(x - vector.x, y - vector.y);
}

inline adlVec2 adlVec2::operator+(float value) const
{
	return adlVec2(x + value, y + value);
}

inline adlVec2 adlVec2::operator-(float value) const
{
	return adlVec2(x - value, y - value);
}

inline adlVec2 adlVec2::operator*(float value) const
{
	return adlVec2(x * value, y * value);
}

inline adlVec2 adlVec2::operator/(float value) const
{
	return adlVec2(x / value, y / value);
}

inline bool adlVec2::operator==(const adlVec2& vector) const
{
	return (x == vector.x) && (y == vector.y);
}

inline bool adlVec2::operator!=(const adlVec2& vector) const
{
	return (x != vector.x) && (y != vector.y);
}

class adlVec2_i32
{
public:
	inline adlVec2_i32();
	inline adlVec2_i32(int32 x, int32 y);
	inline adlVec2_i32(int32 value);

	inline static adlVec2_i32 zero();

	/*----Operator overloads----*/
	inline adlVec2_i32 operator+(const adlVec2_i32& vector) const;
	inline adlVec2_i32 operator-(const adlVec2_i32& vector) const;

	inline adlVec2_i32 operator+(int32 value) const;
	inline adlVec2_i32 operator-(int32 value) const;
	inline adlVec2_i32 operator*(int32 value) const;
	inline adlVec2_i32 operator/(int32 value) const;

	inline bool operator==(const adlVec2_i32& vector) const;
	inline bool operator!=(const adlVec2_i32& vector) const;
	/*--------------------------*/

	int32 x;
	int32 y;
};

inline adlVec2_i32::adlVec2_i32()
	: x(0), y(0)
{
}

inline adlVec2_i32::adlVec2_i32(int32 x, int32 y)
	: x(x), y(y)
{
}

inline adlVec2_i32::adlVec2_i32(int32 value)
	: x(value), y(value)
{
}

inline adlVec2_i32 adlVec2_i32::zero()
{
	return adlVec2_i32(0);
}

inline adlVec2_i32 adlVec2_i32::operator+(const adlVec2_i32& vector) const
{
	return adlVec2_i32(x + vector.x, y + vector.y);
}

inline adlVec2_i32 adlVec2_i32::operator-(const adlVec2_i32& vector) const
{
	return adlVec2_i32(x - vector.x, y - vector.y);
}

inline adlVec2_i32 adlVec2_i32::operator+(int32 value) const
{
	return adlVec2_i32(x + value, y + value);
}

inline adlVec2_i32 adlVec2_i32::operator-(int32 value) const
{
	return adlVec2_i32(x - value, y - value);
}

inline adlVec2_i32 adlVec2_i32::operator*(int32 value) const
{
	return adlVec2_i32(x * value, y * value);
}

inline adlVec2_i32 adlVec2_i32::operator/(int32 value) const
{
	return adlVec2_i32(x / value, y / + value);
}

inline bool adlVec2_i32::operator==(const adlVec2_i32& vector) const
{
	return (x == vector.x) && (y == vector.y);
}

inline bool adlVec2_i32::operator!=(const adlVec2_i32& vector) const
{
	return (x != vector.x) && (y != vector.y);
}

class adlVec3
{
public:
	inline adlVec3();
	inline adlVec3(float x, float y, float z);
	inline adlVec3(adlVec2 xy, float z);
	inline adlVec3(float value);

	inline static adlVec3 zero();

	/*----Operator overloads----*/
	inline adlVec3 operator+(const adlVec3& vector) const;
	inline adlVec3 operator-(const adlVec3& vector) const;

	inline adlVec3 operator+(float value) const;
	inline adlVec3 operator-(float value) const;
	inline adlVec3 operator*(float value) const;
	inline adlVec3 operator/(float value) const;

	inline bool operator==(const adlVec3& vector) const;
	inline bool operator!=(const adlVec3& vector) const;
	/*--------------------------*/

	float x;
	float y;
	float z;
};

inline adlVec3::adlVec3()
	: x(0), y(0), z(0)
{
}

inline adlVec3::adlVec3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

inline adlVec3::adlVec3(adlVec2 xy, float z)
	: x(xy.x), y(xy.y), z(z)
{
}

inline adlVec3::adlVec3(float value)
	: x(value), y(value), z(value)
{
}

inline adlVec3 adlVec3::zero()
{
	return adlVec3(0.0f);
}


inline adlVec3 adlVec3::operator+(const adlVec3& vector) const
{
	return adlVec3(x + vector.x, y + vector.y, z + vector.z);
}

inline adlVec3 adlVec3::operator-(const adlVec3& vector) const
{
	return adlVec3(x - vector.x, y - vector.y, z - vector.z);
}

inline adlVec3 adlVec3::operator+(float value) const
{
	return adlVec3(x + value, y + value, z + value);
}

inline adlVec3 adlVec3::operator-(float value) const
{
	return adlVec3(x - value, y - value, z - value);
}

inline adlVec3 adlVec3::operator*(float value) const
{
	return adlVec3(x * value, y * value, z * value);
}

inline adlVec3 adlVec3::operator/(float value) const
{
	return adlVec3(x / value, y / value, z / value);
}

inline bool adlVec3::operator==(const adlVec3& vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z);
}

inline bool adlVec3::operator!=(const adlVec3& vector) const
{
	return (x != vector.x) && (y != vector.y) && (z != vector.z);
}

#endif // vector_h__