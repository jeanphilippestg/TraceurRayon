//--------------------------------------------------------------------------------------------------
// Ce code source est du domaine publique.
// Auteur : Stephane Duguay, 2007-2008. s@binarez.com
//--------------------------------------------------------------------------------------------------

#pragma once
#include <cmath>

//----------------------------------------------------------------------------------------------
// Types
//----------------------------------------------------------------------------------------------
template <typename T> class Vector3;
typedef Vector3< float >				Vector3f;
typedef Vector3< double >				Vector3d;
typedef Vector3< int >					Vector3i;
typedef Vector3< unsigned int >			Vector3u;

//----------------------------------------------------------------------------------------------
// Class
//----------------------------------------------------------------------------------------------
template <typename T>
class Vector3
{
public:
	static const unsigned int cNumberOfElements = 3;
	T x, y, z;

public:
	Vector3(void) : x(0), y(0), z(0) { }
	Vector3(const T & _x, const T & _y, const T & _z) : x(_x), y(_y), z(_z) {}
	Vector3(const Vector3 & other) : x(other.x), y(other.y), z(other.z) {}

public:
	const Vector3 &		operator =		(const Vector3 & other) { x = other.x; y = other.y; z = other.z; return *this; }
	const Vector3 &		operator +=		(const Vector3 & other) { x += other.x; y += other.y; z += other.z; return *this; }
	const Vector3 &		operator -=		(const Vector3 & other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	const Vector3 &		operator *=		(const T & _v) { x *= _v; y *= _v; z *= _v; return *this; }
	const Vector3 &		operator /=		(const T & _v) { x /= _v; y /= _v; z /= _v; return *this; }
	inline const T &    operator [ ]	(int _i) const;
	inline T &          operator [ ]	(int _i);
	const Vector3 &		operator +		(void) const { return *this; }
	const Vector3		operator -		(void) const { return Vector3(-x, -y, -z); }
	bool                operator ==     (const Vector3 & other) const { return ((x == other.x) && (y == other.y) && (z == other.z)); }
	bool                operator !=     (const Vector3 & other) const { return ((x != other.x) || (y != other.y) || (z != other.z)); }
public:
	T                   produitScalaire(const Vector3 & other) const { return x*other.x + y*other.y + z*other.z; }
	Vector3				produitVectoriel(const Vector3 & other) const
							{
								return Vector3(	(y * other.z - z * other.y),
												-(x * other.z - z * other.x),
												(x * other.y - y * other.x));
							}
	auto				magnitude( void ) const { return sqrt(x*x + y*y + z*z); }

	void				normalize() { auto m = magnitude(); if (m > 0) (*this) /= m; }
	Vector3				normalized() const { Vector3 copy{ *this }; copy.normalize(); return copy; }

	void                get(T & _x, T & _y, T & _z) const { _x = x; _y = y; _z = z; }
	void                set(const T & _x, const T & _y, const T & _z) { x = _x; y = _y; z = _z; }

public:
	static Vector3 I;
	static Vector3 J;
	static Vector3 K;
	static Vector3 Zero;

};

template <class T>
Vector3<T> Vector3<T>::I = Vector3<T>(1, 0, 0);

template <class T>
Vector3<T> Vector3<T>::J = Vector3<T>(0, 1, 0);

template <class T>
Vector3<T> Vector3<T>::K = Vector3<T>(0, 0, 1);

template <class T>
Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);

template <class T>
inline const T &
Vector3<T>::operator [ ](int _i) const
{
	return ((T*)(this))[_i];
}

template <class T>
inline T &
Vector3<T>::operator [ ](int _i)
{
	return ((T*)(this))[_i];
}

template <typename T>
Vector3<T>
operator+(const Vector3<T> & _lhs, const Vector3<T> & _rhs)
{
	Vector3<T> ret = _lhs;
	return (ret += _rhs);
}

template <typename T>
Vector3<T>
operator-(const Vector3<T> & _lhs, const Vector3<T> & _rhs)
{
	Vector3<T> ret = _lhs;
	return (ret -= _rhs);
}

template <typename T>
Vector3<T>
operator*(const Vector3<T> & _lhs, const T _v)
{
	Vector3<T> ret = _lhs;
	return (ret *= _v);
}
