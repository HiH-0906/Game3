#include <cassert>
#include <cmath>
#include <limits>
#include "..\Vector3.h"


template <class T>
Vector3Template<T>::Vector3Template()
{
	x = 0;
	y = 0;
	z = 0;
}

template <class T>
Vector3Template<T>::Vector3Template(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template <class T>
Vector3Template<T>::~Vector3Template()
{
}
template <class T>
Vector3Template<T>& Vector3Template<T>::operator=(const Vector3Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}
template <class T>
T& Vector3Template<T>::operator[](int num)
{
	if (num == 0)
	{
		return x;
	}
	else if (num == 1)
	{
		return y;
	}
	else if (num == 2)
	{
		return z;
	}
	else
	{
		// ‘z’è‚µ‚Ä‚¢‚È‚¢“Y‚¦š‚ª—ˆ‚½ê‡‚Æ‚è‚ ‚¦‚¸x‚ğ‚©‚¦‚·
		assert(!"‘z’è‚µ‚Ä‚¢‚È‚¢“Y‚¦šFVector2Temple");
		return x;
	}
}

template <class T>
Vector3Template<T>& Vector3Template<T>::operator+=(const Vector3Template<T>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

template <class T>
Vector3Template<T>& Vector3Template<T>::operator-=(const Vector3Template<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator*=(const Vector3Template& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

template<class T>
Vector3Template<T>& Vector3Template<T>::operator/=(const Vector3Template& vec)
{
	if (vec.x == 0)
	{
		assert(!"0œZ Œ^‚ÌÅ‘å’l‚ğ•Ô‚µ‚Ü‚·FVector3Temple");
		x = std::numeric_limits<T>::max();
	}
	else
	{
		x /= vec.x;
	}
	if (vec.y == 0)
	{
		assert(!"0œZ Œ^‚ÌÅ‘å’l‚ğ•Ô‚µ‚Ü‚·FVector3Temple");
		y = std::numeric_limits<T>::max();
	}
	else
	{
		y /= vec.y;
	}
	if (vec.z == 0)
	{
		assert(!"0œZ Œ^‚ÌÅ‘å’l‚ğ•Ô‚µ‚Ü‚·FVector3Temple");
		z = std::numeric_limits<T>::max();
	}
	else
	{
		z /= vec.z;
	}
	return *this;
}

template <class T>
Vector3Template<T> Vector3Template<T>::operator+() const
{
	return *this;
}

template <class T>
Vector3Template<T> Vector3Template<T>::operator-() const
{
	return Vector3Template(-this->x, -this->y, -this->z);
}


template <class T>
Vector3Template<T>& Vector3Template<T>::operator+=(const T u)
{
	this->x += u;
	this->y += u;
	this->z += u;
	return *this;
}
template<class T>
Vector3Template<T>& Vector3Template<T>::operator-=(const T u)
{
	this->x -= u;
	this->y -= u;
	this->z -= u;
	return *this;
}
template <class T>
Vector3Template<T>& Vector3Template<T>::operator*=(const T k)
{
	x *= k;
	y *= k;
	z *= k;
	return *this;
}

template <class T>
Vector3Template<T>& Vector3Template<T>::operator/=(const T k)
{
	if (k == 0)
	{
		assert(!"0œZ Œ^‚ÌÅ‘å’l‚ğ•Ô‚µ‚Ü‚·FVector3Temple");
		x = std::numeric_limits<T>::max();
		y = std::numeric_limits<T>::max();
		z = std::numeric_limits<T>::max();
		return *this;
	}
	x /= k;
	y /= k;
	z /= k;
	return *this;
}

template<class T>
Vector3Template<int> Vector3Template<T>::operator%=(const Vector3Template& vec)
{
	Vector3Template<int> intthis = static_cast<Vector3Template<int>>(*this);
	Vector3Template<int> intvec = static_cast<Vector3Template<int>>(vec);
	return Vector3Template<int>(intthis.x % intvec.x, intthis.y % intvec.y, intthis.z % intvec.z);
}

template <class T>
bool Vector3Template<T>::operator==(const Vector3Template<T>& vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y) && (this->z == vec.z));
}
template <class T>
bool Vector3Template<T>::operator!=(const Vector3Template<T>& vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y) && (this->z == vec.z));
}
template <class T>
bool Vector3Template<T>::operator<=(const Vector3Template<T>& vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y) && (this->z <= vec.z));
}
template <class T>
bool Vector3Template<T>::operator<(const Vector3Template<T>& vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y) && (this->z < vec.z));
}
template <class T>
bool Vector3Template<T>::operator>=(const Vector3Template<T>& vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y) && (this->z >= vec.z));
}
template <class T>
bool Vector3Template<T>::operator>(const Vector3Template<T>& vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y) && (this->z > vec.z));
}
template<class T>
inline T Vector3Template<T>::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}
template<class T>
inline void Vector3Template<T>::Nomalize()
{
	auto len = Magnitude();
	if (len == 0) return;

	x /= len;
	y /= len;
	z /= len;
}
template<class T>
inline Vector3Template<T> Vector3Template<T>::Nomalized() const
{
	auto len = Magnitude();

	if (len == 0)
	{
		return { 0,0,0 };
	}

	Vector3Template<T> vec = { x / len,y / len ,z / len };
	return vec;
}
template <class T>
Vector3Template<T> operator+(const Vector3Template<T>& vec, T u)
{
	return Vector3Template<T>(vec.x + u, vec.y + u, vec.z + u);
}
template <class T>
Vector3Template<T> operator-(const Vector3Template<T>& vec, T u)
{
	return Vector3Template<T>(vec.x - u, vec.y - u, vec.z - u);
}
template <class T>
Vector3Template<T> operator*(const Vector3Template<T>& vec, T u)
{
	return Vector3Template<T>(vec.x * u, vec.y * u, vec.z * u);
}
template <class T>
Vector3Template<T> operator/(Vector3Template<T>& vec, T u)
{
	if (u == 0)
	{
		assert(!"0œZ Œ^‚ÌÅ‘å’l‚ğ•Ô‚µ‚Ü‚·FVector3Temple");
		vec.x = std::numeric_limits<T>::max();
		vec.y = std::numeric_limits<T>::max();
		vec.z = std::numeric_limits<T>::max();
		return vec;
	}
	return Vector3Template<T>(vec.x / u, vec.y / u, vec.z / u);
}
template <class T>
Vector3Template<T> operator*(T u, const Vector3Template<T>& vec)
{
	return Vector3Template<T>(u * vec.x, u * vec.y, u * vec.z);
}
template <class T>
Vector3Template<T> operator+(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	return Vector3Template<T>(veca.x + vecb.x, veca.y + vecb.y, veca.z + vecb.z);
}
template <class T>
Vector3Template<T> operator-(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	return Vector3Template<T>(veca.x - vecb.x, veca.y - vecb.y, veca.z - vecb.z);
}
template <class T>
Vector3Template<T> operator*(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	return Vector3Template<T>(veca.x * vecb.x, veca.y * vecb.y, veca.z * vecb.z);
}
template <class T>
Vector3Template<T> operator/(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	if (vecb.x == 0 || vecb.y == 0 || vecb.z == 0)
	{
		assert(!"0œZ Œ^‚ÌÅ‘å’l‚ğ•Ô‚µ‚Ü‚·FVector3Temple");
		return  Vector3Template<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
	}
	return Vector3Template<T>(veca.x / vecb.x, veca.y / vecb.y, veca.y / vecb.z);
}
template <class T>
Vector3Template<int> operator%(const Vector3Template<T>& vec, const int u)
{
	Vector3Template<int> intvec = static_cast<Vector3Template<int>>(vec);
	return Vector3Template<int>(intvec.x % u, intvec.y % u, intvec.z % u);
}
template <class T>
Vector3Template<int> operator%(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	Vector3Template<int> intveca = static_cast<Vector3Template<int>>(veca);
	Vector3Template<int> intvecb = static_cast<Vector3Template<int>>(vecb);
	return Vector3Template<int>(intveca.x % intvecb.x, intveca.y % intvecb.y, intveca.z % intvecb.z);
}

template<class T>
inline T Dot(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	return veca.x * vecb.x + veca.y * vecb.y + veca.z * vecb.z;
}

template<class T>
inline Vector3Template<T> Cross(const Vector3Template<T>& veca, const Vector3Template<T>& vecb)
{
	return Vector3Template<T>(
		veca.y * vecb.z - veca.z * vecb.y,
		veca.z * vecb.x - veca.x * vecb.z,
		veca.x * vecb.y - veca.y * vecb.x
		);
}
