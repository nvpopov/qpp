#ifndef _QPP_IO_H
#define _QPP_IO_H

#include <io/qppdata.hpp>

namespace qpp{

  template< class VALTYPE=double, class ATLABEL = std::string, class charT = char, 
	    class traits = std::char_traits<charT> >
  class qpp_data_reader{

    qpp_data_reader(std::string fname)
    {}

    qpp_data_reader(std::basic_istream<charT,traits> & is)
    {}

    virtual qpp_data_array<charT,traits> * get_data(qppdata_type t) =0;

    template <int DIM>
    virtual void get_geometry(geometry<DIM,VALTYPE,ATLABEL,charT,traits> &geom) =0;

    /* ------------ example -------------------
       qpp_gulpinp_reader inp("c60.gin");
       qpp_qpp_data_array * p = inp.get_data(qppdata_geometry | qppdata_vectors);
       int i=0;

       if (p[1].gettype & qppdata_geometry)
         i=1;

       geometry<3,double> G = p[i];

       i=0;
       if (p[1].gettype & qppdata_vectors)
         i=1;

       periodic_cell<3,double> cl = p[i];
    */
  };

  // ------------------------------------------------------------

  template< class VALTYPE=double, class ATLABEL = std::string, class charT = char, 
	    class traits = std::char_traits<charT> >
  class qpp_data_writer{

    qpp_data_writer(std::string fname)
    {}

    qpp_data_writer(std::basic_ostream<charT,traits> & os)
    {}

    virtual void put_data(const qpp_data_array<charT,traits> & q) =0;

    virtual void put_data(const qpp_object<charT,traits> & q) =0;

    /* ------------------- example ---------------------

       gaussian_molecule<0,double> mol;

       ............................

       qpp_gamessinp_writer inp("CH4.inp");
       inp.put_data(mol);

     */
  };

};

#endif
