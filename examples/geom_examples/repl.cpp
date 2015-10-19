#include <instr/geomanip.hpp>
#include <io/geomio.hpp>

typedef lace::vector3d<double> v3d;

int main()
{

  qpp::periodic_cell<3,double> vec(lace::vector3d<double>(2.76,2.76,0.00),
				   lace::vector3d<double>(2.76,0.00,2.76),
				   lace::vector3d<double>(0.00,2.76,2.76),
				   "caf2");


  qpp::xtr_geometry<3,double> uc(1,0,0,"caf2");
  
  uc.add("Ca",0,0,0);
  uc.add("F", 1.38,  1.38,  1.38);
  uc.add("F", 1.38,  1.38, -1.38);
  uc.add("F", 1.38, -1.38,  1.38);
  uc.add("F", 1.38, -1.38, -1.38);
  uc.add("F",-1.38,  1.38,  1.38);
  uc.add("F",-1.38,  1.38, -1.38);
  uc.add("F",-1.38, -1.38,  1.38);
  uc.add("F",-1.38, -1.38, -1.38);

  uc.field_name(0) = "charge";
  uc.xtr_real(0,0) = 2e0;
  for (int i=1; i<uc.nat(); i++)
    uc.xtr_real(0,i) = -0.25e0;

  uc.setsymm(vec);

  uc.write(std::cout);
  vec.write(std::cout);

  qpp::geometry<2,double> uc2;
  uc2.add("C",0,0,0);
  uc2.add("C",-.7, 1.212435565298, 0);

  qpp::periodic_cell<2,double> vec2(lace::vector3d<double>(0,2.424871130596,0),
				    lace::vector3d<double>(2.1,1.212435565298,0 ));
  

  qpp::shape_sphere<double> sph1(25.0,lace::vector3d<double>(0e0,0e0,0e0),"nano1");
  qpp::shape_sphere<double> sph2(15.0,lace::vector3d<double>(0e0,0e0,0e0),"nano2");
  qpp::shape_box<double> b1(25,25,25);
  qpp::shape_box<double> b2(25,25,25);
  b2.move(lace::vector3d<double>(-25,-25,0));
  qpp::shape_box<double> b3(25,25,25);
  b3.move(lace::vector3d<double>(0,-25,-25));
  qpp::shape_box<double> b4(25,25,25);
  b4.move(lace::vector3d<double>(-25,0,-25));
  //  qpp::shape_sphere<double> sph2(.0,lace::vector3d<double>(25e0,0e0,0e0),"nano1");
  //  qpp::shape_box<double> box(v3d(-10,10,10),v3d(10,10,-10),v3d(10,-10,10), v3d(0,0,5),"box1");
  //  qpp::shape_intersect<double> sph(sph1,sph2,"nano");
  qpp::shape_subtract<double> s(sph1, 
				*new qpp::shape_union<double>(
						 *new qpp::shape_union<double>(b1,b2),
						 *new qpp::shape_union<double>(b3,b4)));

  s.rotate(lace::RotMtrx(lace::vector3d<double>(1,2,3), 1.));

  s.write(std::cout);
  
  qpp::xtr_geometry<0,double> * nano = (qpp::xtr_geometry<0,double> *)
    qpp::replicate<0,3,double,
		   qpp::periodic_cell<0,double>,
		   qpp::periodic_cell<3,double> >(uc,vec,s, 
						  qpp::qmode_join + qpp::qmode_atomwise, 0.1);

  qpp::replace(*nano, sph2, "Ca", "Sr");
  
  /*
  qpp::geometry<0,double> *nano2 = 
    qpp::replicate<0,2,double,
		   qpp::periodic_cell<0,double>,
		   qpp::periodic_cell<2,double> >(uc2,vec2,s,qpp::qmode_atomwise+qpp::qmode_merge,0.1);
  */
  qpp::OFSTREAM x("nano.xyz");
  qpp::OFSTREAM y("nano.qpp");
  //nano->write(std::cout);
  qpp::write_xyz(x,*nano);
  nano->write(y);
}
