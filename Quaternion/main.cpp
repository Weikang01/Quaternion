#include "Quaternion.h"
using quaternion = Quaternion<double>;
using vec3 = Vector3<double>;
int main() {
	quaternion p(1, 2, 3, 4);
	vec3 v(1, 2, 3);
	vec3 u(2, 3, 4);
	u.normalize();
	std::cout << v.rotate_along(3.1415, u) << std::endl;
	quaternion q = quaternion::from_rotation(3.1415, u);
	std::cout << q << std::endl;

	return 0;
}