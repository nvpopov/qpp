#include <mathf/gaussian.hpp>

double cartesian_gaussian_prim(lace::vector3d<double> pos,
	const double k, const double m, const double n, const double v)
{
		return pow(pos(0),k)*pow(pos(1),n)*pow(pos(0),v)*
		exp(-v*(pos(0)*pos(0)+pos(1)*pos(1)+pos(2)*pos(2)));
}
