#pragma once
template <class T> class Vector3Template
{
public:
	Vector3Template();
	Vector3Template(T x, T y,T z);
	~Vector3Template();
	T x;
	T y;
	T z;
	
	//ë„ì¸ââéZéq
	Vector3Template& operator = (const Vector3Template& vec);
	
	// ìYÇ¶éöââéZéq
	T& operator [] (int num);
	
	// íPçÄââéZéq
	Vector3Template& operator += (const Vector3Template& vec);
	Vector3Template& operator -= (const Vector3Template& vec);
	Vector3Template& operator *= (const Vector3Template& vec);
	Vector3Template& operator /= (const Vector3Template& vec);

	Vector3Template operator + ()const;
	Vector3Template operator - ()const;

	Vector3Template& operator += (const T u);
	Vector3Template& operator -= (const T u);
	Vector3Template& operator *= (const T k);
	Vector3Template& operator /= (const T k);

	Vector3Template<int> operator %= (const Vector3Template& vec);

	// ÉLÉÉÉXÉgââéZéq
	explicit operator Vector3Template<int>()
	{
		return Vector3Template<int>(static_cast<int>(x), static_cast<int>(y));
	};

	explicit operator Vector3Template<float>()
	{
		return Vector3Template<float>(static_cast<float>(x), static_cast<float>(y));
	};

	explicit operator Vector3Template<double>()
	{
		return Vector3Template<double>(static_cast<double>(x), static_cast<double>(y));
	};

	// î‰ärââéZéq
	bool operator == (const Vector3Template& vec) const;
	bool operator != (const Vector3Template& vec) const;
	bool operator <= (const Vector3Template& vec) const;
	bool operator < (const Vector3Template& vec) const;
	bool operator >= (const Vector3Template& vec) const;
	bool operator > (const Vector3Template& vec) const;

	T Magnitude()const;
	void Nomalize();
	Vector3Template Nomalized()const;

};
template <class T>
Vector3Template<T> operator + (const Vector3Template<T>& vec, T u);
template <class T>
Vector3Template<T> operator - (const Vector3Template<T>& vec, T u);
template <class T>
Vector3Template<T> operator * (const Vector3Template<T>& vec, T u);
template <class T>
Vector3Template<T> operator / (Vector3Template<T>& vec, T u);
template <class T>
Vector3Template<T> operator * (T u, const Vector3Template<T>& vec);
template <class T>
Vector3Template<T> operator + (const Vector3Template<T>& veca, const Vector3Template<T>& vecb);
template <class T>
Vector3Template<T> operator - (const Vector3Template<T>& veca, const Vector3Template<T>& vecb);
template <class T>
Vector3Template<T> operator * (const Vector3Template<T>& veca, const Vector3Template<T>& vecb);
template <class T>
Vector3Template<T> operator / (const Vector3Template<T>& veca, const Vector3Template<T>& vecb);

template <class T>
Vector3Template<int> operator % (const Vector3Template<T>& vec, const int u);
template <class T>
Vector3Template<int> operator % (const Vector3Template<T>& veca, const Vector3Template<T>& vecb);

template <class T>
T Dot(const Vector3Template<T>& veca, const Vector3Template<T>& vecb);

template <class T>
Vector3Template<T> Cross(const Vector3Template<T>& veca, const Vector3Template<T>& vecb);

using Vector3Int = Vector3Template<int>;
using Vector3Dbl = Vector3Template<double>;
using Vector3 = Vector3Template<float>;


#include "details/Vector3.h"