#include <iostream>
#include <geom/lace3d.hpp>
#include <symm/autosymm.hpp>

using namespace qpp;

int main(){
  rotrans<double> R1 = rotrans<double>({1,0,0},RotMtrx({0,1,1},2*pi/4));
  //rotrans<double> R1 = rotrans<double>({1,1,-1},Sigma<double>({1,1,-1}));
  auto S1 = invariant_subspace(rotrans4d(R1));

  std::cout << "dim(S1)= " << S1.dim << " point(S1)= " << S1.point << std::endl 
	    << " axis(S1)= " << S1.axis << std::endl  << S1.X << std::endl 
	    << "orths= " << std::endl << S1.orths << std::endl;

  
  rotrans<double> R2 = rotrans<double>({1,1,1},Sigma<double>({1,1,1}));
  auto S2 = invariant_subspace(rotrans4d(R2));

  std::cout << "dim(S2)= " << S2.dim << " point(S2)= " << S2.point << std::endl 
	    << " axis(S2)= " << S2.axis << std::endl  << S2.X << std::endl 
	    << "orths= " << std::endl << S2.orths << std::endl;


  auto S3 = S1 & S2;
  
  std::cout << "dim(S3)= " << S3.dim << " point(S3)= " << S3.point << std::endl 
	    << " axis(S3)= " << S3.axis << std::endl  << S3.X << std::endl 
	    << "orths= " << std::endl << S3.orths << std::endl;

 
}

