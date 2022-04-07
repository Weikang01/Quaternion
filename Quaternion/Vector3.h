#pragma once
#include <iostream>
#include <cmath>

template<typename T>
class Vector3
{
public:
	T x;
	T y;
	T z;

	Vector3<T>(const T x = 0, const T y = 0, const T z = 0) : x(x), y(y), z(z) {}
	Vector3<T>(const Vector3<T>& v) : x{ v.x }, y{ v.y }, z{ v.z } {}

	Vector3<T>& const operator=(Vector3<T>&& v) {
		if (this == &v)
			return *this;
		this->x = &v.x;
		this->y = &v.y;
		this->z = &v.z;
		return *this;
	}

	Vector3<T> operator+(const Vector3<T>& v) const {
		return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vector3<T>& operator+=(const Vector3<T>& v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}

	Vector3<T> operator*(const T scala) const {
		return Vector3<T>(this->x * scala, this->y * scala, this->z * scala);
	}

	Vector3<T>& operator*=(const T scala) {
		this->x *= scala;
		this->y *= scala;
		this->z *= scala;
		return *this;
	}

	Vector3<T> operator*(const Vector3<T>& v) const {
		return Vector3<T>(this->x * v.x, this->y * v.y, this->z * v.z);
	}

	Vector3<T>& operator*=(const Vector3<T>& v) {
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		return *this;
	}

	Vector3<T> operator/(const T scala) const {
		return Vector3<T>(this->x / scala, this->y / scala, this->z / scala);
	}

	Vector3<T>& operator/=(const T scala) {
		this->x /= scala;
		this->y /= scala;
		this->z /= scala;
		return *this;
	}

	T norm() const {
		return sqrt(sq_norm(*this));
	}

	Vector3<T>& normalize() {
		*this /= this->norm();
		return *this;
	}

	static T const dot(const Vector3<T>& q, const Vector3<T>& p) {
		return q.x * p.x + q.y * p.y + q.z * p.z;
	}

	static Vector3<T> const cross(const Vector3<T>& q, const Vector3<T>& p) {
		return Vector3<T>(p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x);
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v);

	static T const sq_norm(const Vector3<T>& v) {
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}

	Vector3<T> rotate_along(const T theta, const Vector3<T> axis) const {
		const T cos_theta = cos(theta);
		const T sin_theta = sin(theta);
		return (*this) * cos_theta + axis * (1 - cos_theta) * (Vector3<T>::dot(axis, *this)) + Vector3<T>::cross(axis, *this) * sin_theta;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
	os << "< " << v.x << ", " << v.y << ", " << v.z << " >";
	return os;
}