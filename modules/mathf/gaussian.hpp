#ifndef MATHF_GAUSSIAN_H
#define MATHF_GAUSSIAN_H

#include <lace/lace3d.hpp>
#include <math.h>

double cartesian_gaussian_prim(lace::vector3d<double> pos, 
	const double k, const double m, const double n, const double v);

#endif
