#ifndef QPP_GMSIO_H
#define QPP_GMSIO_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <ios>
#include <algorithm>
#include <basis/basis.hpp>
#include <geom/xgeom.hpp>
#include <data/molecule.hpp>
#include <io/strfun.hpp>
#include <consts.hpp>

namespace qpp{

  template<qpp_bastype BT, class FREAL>
  void read_gms_basis(std::basic_istream<CHAR,
                      TRAITS> & inp,
                      atomic_basis<BT,FREAL> & bas){
    bas.shells.clear();
    STRING s1, s2;
    std::getline(inp,s1);
    //std::cerr << s1 << "\n";

    if (strnf(s1)==0){
        //empty basis!
        bas.basis_name = "";
        return;
      }
    std::getline(inp,s2);
    //std::cerr << s2 << "\n";

    if (strnf(s2)==0){
        // basis name in s1
        bas.basis_name = s1;
        return;
      }
    int nsh = 0;
    while (strnf(s1)==2){
        std::vector<STRING> fields = split(s1);
        fields[0] = tolower(fields[0]);
        int l1,l2,ng;
        if (fields[0]=="s")
          l1 = l2 = 0;
        else if (fields[0]=="p")
          l1 = l2 = 1;
        else if (fields[0]=="d")
          l1 = l2 = 2;
        else if (fields[0]=="f")
          l1 = l2 = 3;
        else if (fields[0]=="l")
          {
            l1 = 0; l2 = 1;
          }
        else break;
        s2t<int>(fields[1],ng);

        //std::cerr << "ng= " << ng << " l= " << l1 << " " << l2 << "\n";

        bas.shells.emplace_back(ng,l2-l1+1,qang_cartesian);
        for (int i=0; i<=l2-l1; i++)
          bas.shells[nsh].l(i) = l1+i;

        for (int i=0; i<ng; i++){
            split(s2,fields);
            FREAL r;
            s2t<FREAL>(fields[1],r);
            bas.shells[nsh].alpha(i) = r;
            for (int j=0; j<=l2-l1; j++)
              {
                s2t<FREAL>(fields[2+j],r);
                bas.shells[nsh].coeff(i,j) = r;
              }
            std::getline(inp,s2);
            //std::cerr << s2 << "\n";

          }
        if (strnf(s2)==0)
          break;
        else{
            s1=s2;
            std::getline(inp,s2);
            //std::cerr << s2 << "\n";
          }
        nsh++;
      }
  }

  template<qpp_bastype BT, class FREAL>
  void write_gms_basis(std::basic_ostream<CHAR,TRAITS>  & out,
                       const atomic_basis<BT,FREAL> & bas){
    if (bas.shells.size()==0 && bas.basis_name!=""){
        out << bas.basis_name << std::endl;
        return;
      }
    for (const auto & sh : bas.shells){
        STRING lbl="";
        if (sh.nshells()==1){
            if (sh.l(0)==0)
              lbl = "S";
            else if (sh.l(0)==1)
              lbl = "P";
            else if (sh.l(0)==2)
              lbl = "D";
            else if (sh.l(0)==3)
              lbl = "F";
            else
              ValueError("Only S,P,D,F, and SP shells can "
                         "be written in GAMESS format");
          }
        else if (sh.nshells()==2 && sh.l(0)==0 && sh.l(1)==1 )
          lbl = "L";
        else
          ValueError("Only S,P,D,F, and SP shells can "
                     "be written in GAMESS format");
        out << lbl << "    " << sh.nprim() << std::endl;
        for (int i=0; i<sh.nprim(); i++){
            out << fmt::format("{:3d}  {:16.8f}  ",i,sh.alpha(i));
            for (int j=0; j<sh.nshells(); j++)
              out << fmt::format("  {:16.8f}",sh.coeff(i,j));
            out << std::endl;
          }
      }
  }


  template<class FREAL>
  void read_gms_ecp(std::basic_istream<CHAR,TRAITS>  & inp,
                    STRING & name, atomic_ecp<FREAL> & ecp){
    STRING s;
    std::getline(inp,s);

    std::vector<STRING> sf = split(s);

    if (sf.size()==1){
        name = sf[0];
        ecp = atomic_ecp<FREAL>();
        return;
      }
    else if (sf.size()==2 && icompare(sf[0],"none") && icompare(sf[1],"none")){
        name = "none";
        ecp = atomic_ecp<FREAL>();
        return;
      }

    name = sf[0];
    if (!icompare(sf[1],"GEN"))
      SyntaxError("When reading GAMESS ECP: GEN expected");

    int nelec,L;
    if ( !s2t<int>(sf[2],nelec) || ! s2t<int>(sf[3],L) )
      SyntaxError("When reading GAMESS ECP: integer expected");

    ecp = atomic_ecp<FREAL>(L);
    ecp.nelec = nelec;

    for (int l=0; l<=L; l++){
        std::getline(inp,s);
        sf = split(s);
        int nprim;
        if ( !s2t<int>(sf[0],nprim) )
          SyntaxError("When reading GAMESS ECP: integer expected");
        ecp.setnprim(l,nprim);
        for (int i=0; i<nprim; i++){
            std::getline(inp,s);
            sf = split(s);
            s2t<FREAL>(sf[0], ecp.coeff(l,i) );
            s2t<int>(  sf[1], ecp.n(l,i) );
            s2t<FREAL>(sf[2], ecp.alpha(l,i) );
          }
      }
  }

  template<class FREAL>
  void write_gms_ecp(std::basic_ostream<CHAR,TRAITS>  & out,
                     const STRING & name,
                     const atomic_ecp<FREAL> & ecp){
    if (icompare(name,"none"))
      out << "none none" << std::endl;
    else if ( ecp.empty() )
      out << name << std::endl;
    else{
        out << name << " GEN " << ecp.nelec << " " << ecp.L() << std::endl;
        for (int l=0; l<ecp.L(); l++)
          {
            out << fmt::format("{:3d}",ecp.nprim(l)) << std::endl;
            for (int i=0; i<ecp.nprim(l); i++)
              out <<
                     fmt::format("{:15.8f} {:3d} {:15.8f}",
                                 ecp.coeff(l, i), ecp.n(l, i), ecp.alpha(l, i))
                  << std::endl;
          }
      }
  }


  template<class REAL, class CELL = periodic_cell<REAL> >
  void write_gms_data(std::basic_ostream<CHAR,TRAITS>  & out,
                      geometry<REAL, CELL> & geom,
                      std::vector<atomic_basis<qbas_gauss,REAL> > & bas){
    if (!geom.is_xgeometry())
      TypeError("Must be xgeometry with charges to be "
                "printed as GAMESS data section");

    xgeometry<REAL, CELL> *xgeom = (xgeometry<REAL, CELL>*)(&geom);

    out << " $DATA" << std::endl << geom.name << std::endl;

    // fixme! correct point group description should be here
    out << "C1" << std::endl;

    for (int i=0; i<geom.nat(); i++)
      if (!geom.shadow(i)){
          vector3<REAL> r = xgeom->pos(i);
          out << fmt::format("{:8s}  {:12.6f} {:14.8f} {:14.8f} {:14.8f}",
                             xgeom->atom(i),xgeom->charge(i),r(0),r(1),r(2));
          out << std::endl;
          for (int j=0; j<bas.size(); j++)
            if (bas[j].atom == xgeom->atom(i)){
                qpp::write_gms_basis(out,bas[j]);
              }
          out << std::endl;
        }

    out << " $END" << std::endl;
  }

  template<class REAL, class CELL = periodic_cell<REAL>, class FREAL = REAL >
  void write_gms_data(std::basic_ostream<CHAR,TRAITS>  & out,
                      qmmm_molecule<REAL,CELL,qbas_gauss,FREAL> & mol){
    for (int i : mol.fixedatoms)
      mol.geom->shadow(i,true);
    qpp::write_gms_data(out, *mol.geom, mol.basis);
    for (int i : mol.fixedatoms)
      mol.geom->shadow(i,false);
  }

  // ------------------------------------------------

  template<class REAL, class CELL = periodic_cell<REAL> >
  void write_gms_charges(std::basic_ostream<CHAR,TRAITS>  & out,
                         xgeometry<REAL, CELL> & geom){
    out << " $EFRAG" << std::endl
        << " position=fixed coord=cart" << std::endl
        << " FRAGNAME=cla" << std::endl
        << " cla1    0.00  0.00  0.00" << std::endl
        << " cla2    1.00  0.00  0.00" << std::endl
        << " cla3    0.00  1.00  0.00" << std::endl
        << " $END" << std::endl
        << " $cla" << std::endl
        << " Point charges" << std::endl
        << " COORDINATES" << std::endl
        << " cla1    0.00    0.00  0.00  1.00  0.00" << std::endl
        << " cla2    1.8897  0.00  0.00  1.00  0.00" << std::endl
        << " cla3    0.00   1.8897 0.00  1.00  0.00" << std::endl;

    for (int i=0; i<geom.nat(); i++)
      if (!geom.shadow(i)){
          vector3<REAL> r = ang_to_bohr*geom.coord(i);
          out <<
                 fmt::format("{:5d} {:16.8f} {:16.8f} {16.8f}",
                             i,r.x(),r.y(),r.z())<< std::endl;
        }
    out << " stop" << std::endl << " monopoles" << std::endl;
    for (int i=0; i<geom.nat(); i++)
      if (!geom.shadow(i))
        out << fmt::format("{:5d} {:16.8f}",i,geom.charge(i)) << std::endl;
    out << " stop" << std::endl << " $END" << std::endl;
  }

  template<class REAL, class CELL = periodic_cell<REAL>, class FREAL = REAL >
  void write_gms_charges(std::basic_ostream<CHAR,TRAITS>  & out,
                         qmmm_molecule<REAL,CELL,qbas_gauss,FREAL> & mol){
    for (int i : mol.fixedatoms)
      mol.geom->shadow(i,true);
    write_gms_data(out, *mol.geom, mol.basis);
    for (int i : mol.fixedatoms)
      mol.geom->shadow(i,false);
  }



}

#endif
