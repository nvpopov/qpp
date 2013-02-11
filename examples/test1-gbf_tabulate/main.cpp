#include <iostream>
#include <mathf/gaussian.hpp>
#include <lace/lace3d.hpp>

int main(){
	for (int i=1; i<500; i++)
	{
		lace::vector3d<double> vec(i/100.0,0.0001,0.0001);
		double gbf_s = cartesian_gaussian_prim(vec,0.2,0.3,0.4,0.7);
		std::cout<<vec(0)<<" "<<gbf_s<<std::endl;
	}
}
