#pragma once
#include "Vector3.h"

template<typename T>
class Quaternion
{
public:
	T w;
	Vector3<T> v;
	Quaternion<T>(T w = 1, Vector3<T> v = Vector3<T>(0)) : w{ w }, v{ v } {}
	Quaternion<T>(T w = 1, T x = 0, T y = 0, T z = 0) : w{ w }, v{ x, y, z } {}
	Quaternion<T>(const Quaternion<T>& q) : w{ q.w }, v{ q.v } {}
	~Quaternion<T>() {}

	/*
	* create a new quaternion from the angle and the axis
	* the correct way to use this quaternion to get the rotated vector3
	* use qvq*
	* where  q: this quaternion
	*	     v: the vector to be rotated
	*	    q*: complex conjugate of q */
	static Quaternion<T> const from_rotation(T theta, Vector3<T> axis) {
		axis.normalize();
		return Quaternion(cos(theta/2), axis * sin(theta/2));
	}

	Quaternion<T>& const operator=(Quaternion<T>&& q) {
		if (this == &q)
			return *this;
		this->x = &q.x;
		this->v = &q.v;
		return *this;
	}

	Quaternion<T> const operator+(const T scala) {
		return Quaternion(this->w + scala, this->x, this->y, this->z);
	}

	Quaternion<T>& operator+=(const T scala) {
		this->w += scala;
		return *this;
	}

	Quaternion<T> const operator+(const Quaternion<T>& q) {
		return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z);
	}

	Quaternion<T>& operator+=(const Quaternion<T>& q) {
		this->v += q.v;
		this->z += q.z;
		return *this;
	}

	Quaternion<T> const operator*(const T scala) {
		return Quaternion(this->w * scala, this->x * scala, this->y * scala, this->z * scala);
	}

	Quaternion<T>& operator*=(const T scala) {
		this->w *= scala;
		this->v *= scala;
		return *this;
	}

	Quaternion<T> const operator*(const Quaternion<T>& q) {
		Quaternion<T> _new(0);
		_new.v = Vector3<T>::cross(this->v, q.v);
		_new.v += this->w * q.v + q.w * this->v;
		_new.w = this->w * q.w - Vector3<T>::dot(this->v, q.v);
		return _new;
	}

	Quaternion<T>& operator*=(const Quaternion<T>& q) {
		Quaternion<T> _new(0);

		_new.v = Vector3<T>::cross(this->v, q.v);
		_new.v += this->w * q.v + q.w * this->v;
		_new.w = this->w * q.w - Vector3<T>::dot(this->v, q.v);

		this->v = _new.v;
		this->w = _new.w;
		return *this;
	}

	Quaternion<T> const operator/(const T scala) {
		return Quaternion(this->w / scala, this->x / scala, this->y / scala, this->z / scala);
	}

	Quaternion<T>& operator /=(const T scala) {
		this->w /= scala;
		this->v /= scala;
		return *this;
	}

	Quaternion<T> const complex_conjugate() {
		return Quaternion(this->w, -this->x, -this->y, -this->z);
	}

	Quaternion<T>& normalize() {
		*this /= this->norm();
		return *this;
	}

	T const norm() {
		return sqrt(Quaternion::sq_norm(*this));
	}

	Quaternion<T> const inverse() {
		Quaternion inv = this->complex_conjugate();
		inv /= Vector3<T>::sq_norm(*this);
		return inv;
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q);

private:
	T sq_norm(const Quaternion<T>& q) {
		return Vector3<T>::sq_norm(q.v) + q.w * q.w;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q) {
	os << q.w << (q.v.x >= 0 ? "+" : "") << q.v.x << (q.v.y >= 0 ? "i+" : "i") << q.v.y << (q.v.z >= 0 ? "j+" : "j") << q.v.z << "k";
	return os;
}