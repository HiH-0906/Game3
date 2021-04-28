#include <cassert>
#include <numeric>
#include "..\Vector2.h"


template <class T>
Vector2Temple<T>::Vector2Temple()
{
	x = 0;
	y = 0;
}

template <class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <class T>
Vector2Temple<T>::~Vector2Temple()
{
}
template <class T>
Vector2Temple<T>&Vector2Temple<T>::operator=(const Vector2Temple<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}
template <class T>
T& Vector2Temple<T>::operator[](int num)
{
	if (num == 0)
	{
		return x;
	}
	else if (num == 1)
	{
		return y;
	}
	else
	{
		// ëzíËÇµÇƒÇ¢Ç»Ç¢ìYÇ¶éöÇ™óàÇΩèÍçáÇ∆ÇËÇ†Ç¶Ç∏xÇÇ©Ç¶Ç∑
		assert(!"ëzíËÇµÇƒÇ¢Ç»Ç¢ìYÇ¶éöÅFVector2Temple");
		return x;
	}
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple<T>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(const Vector2Temple& vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(const Vector2Temple& vec)
{
	if (vec.x == 0 || vec.y == 0)
	{
		assert(!"0èúéZ å^ÇÃç≈ëÂílÇï‘ÇµÇ‹Ç∑ÅFVector2Temple");
		x = std::numeric_limits<T>::max();
		y = std::numeric_limits<T>::max();
		return *this;
	}
	x /= vec.x;
	y /= vec.y;
	return *this;
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	return *this;
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	return Vector2Temple(-this->x, -this->y);
}


template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const T u)
{
	this->x += u;
	this->y += u;
	return *this;
}
template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const T u)
{
	this->x -= u;
	this->y -= u;
	return *this;
}
template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(const T k)
{
	x *= k;
	y *= k;
	return *this;
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(const T k)
{
	if (k == 0)
	{
		assert(!"0èúéZ å^ÇÃç≈ëÂílÇï‘ÇµÇ‹Ç∑ÅFVector2Temple");
		x = std::numeric_limits<T>::max();
		y = std::numeric_limits<T>::max();
		return *this;
	}
	x /= k;
	y /= k;
	return *this;
}

template<class T>
Vector2Temple<int> Vector2Temple<T>::operator%=(const Vector2Temple& vec)
{
	Vector2Temple<int> intthis = static_cast<Vector2Temple<int>>(*this);
	Vector2Temple<int> intvec = static_cast<Vector2Temple<int>>(vec);
	return Vector2Temple<int>(intthis.x % intvec.x, intthis.y % intvec.y);
}

template <class T>
bool Vector2Temple<T>::operator==(const Vector2Temple<T>& vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}
template <class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple<T>& vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}
template <class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple<T>& vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}
template <class T>
bool Vector2Temple<T>::operator<(const Vector2Temple<T>& vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}
template <class T>
bool Vector2Temple<T>::operator>=(const Vector2Temple<T>& vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}
template <class T>
bool Vector2Temple<T>::operator>(const Vector2Temple<T>& vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}
template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& vec, T u)
{
	return Vector2Temple<T>(vec.x + u, vec.y + u);
}
template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& vec, T u)
{
	return Vector2Temple<T>(vec.x - u, vec.y - u);
}
template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& vec, T u)
{
	return Vector2Temple<T>(vec.x * u, vec.y * u);
}
template <class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& vec, T u)
{
	if (vec.x == 0 || vec.y == 0)
	{
		assert(!"0èúéZ å^ÇÃç≈ëÂílÇï‘ÇµÇ‹Ç∑ÅFVector2Temple");
		vec.x = std::numeric_limits<T>::max();
		vec.y = std::numeric_limits<T>::max();
		return vec;
	}
	return Vector2Temple<T>(vec.x / u, vec.y / u);
}
template <class T>
Vector2Temple<T> operator*(T u, const Vector2Temple<T>& vec)
{
	return Vector2Temple<T>(u * vec.x, u * vec.y);
}
template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& veca, const Vector2Temple<T>& vecb)
{
	return Vector2Temple<T>(veca.x + vecb.x, veca.y + vecb.y);
}
template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& veca, const Vector2Temple<T>& vecb)
{
	return Vector2Temple<T>(veca.x - vecb.x, veca.y - vecb.y);
}
template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& veca, const Vector2Temple<T>& vecb)
{
	return Vector2Temple<T>(veca.x * vecb.x, veca.y * vecb.y);
}
template <class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& veca, const Vector2Temple<T>& vecb)
{
	if (vecb.x == 0 || vecb.y == 0)
	{
		assert(!"0èúéZ å^ÇÃç≈ëÂílÇï‘ÇµÇ‹Ç∑ÅFVector2Temple");
		return  Vector2Temple<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
	}
	return Vector2Temple<T>(veca.x / vecb.x, veca.y / vecb.y);
}
template <class T>
Vector2Temple<int> operator%(const Vector2Temple<T>& vec, const int u)
{
	Vector2Temple<int> intvec = static_cast<Vector2Temple<int>>(vec);
	return Vector2Temple<int>(intvec.x % u, intvec.y % u);
}
template <class T>
Vector2Temple<int> operator%(const Vector2Temple<T>& veca, const Vector2Temple<T>& vecb)
{
	Vector2Temple<int> intveca = static_cast<Vector2Temple<int>>(veca);
	Vector2Temple<int> intvecb = static_cast<Vector2Temple<int>>(vecb);
	return Vector2Temple<int>(intveca.x % intvecb.x, intveca.y % intvecb.y);
}
