#ifndef QPP_SHOENFLIS_H
#define QPP_SHOENFLIS_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <symm/groups.hpp>
#include <symm/group_theory.hpp>
#include <symm/gen_cell.hpp>
#include <cmath>

namespace qpp{

  template<class REAL>
  class shnfl {
    public:

      static array_group<matrix3<REAL> > Cs() {
        array_group<matrix3<REAL> > G("Cs");
        G.add(Sigma<REAL>({0,1,0}));
        return G;
      }

      static array_group<matrix3<REAL> > Ci() {
        array_group<matrix3<REAL> > G("Ci");
        G.add(-1*matrix3<REAL>::Identity());
        return G;
      }

      static array_group<matrix3<REAL> > Cn(int n) {
        array_group<matrix3<REAL> > G("C"+std::to_string(n));
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/n));
        return G;
      }

      static array_group<matrix3<REAL> > Cnv(int n) {
        array_group<matrix3<REAL> > G("C"+std::to_string(n)+"v");
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/n));
        G.generate(Sigma<REAL>({1,0,0}));
        return G;
      }

      static array_group<matrix3<REAL> > Cnh(int n) {
        array_group<matrix3<REAL> > G("C"+std::to_string(n)+"h");
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/n));
        G.generate(Sigma<REAL>({0,0,1}));
        return G;
      }

      static array_group<matrix3<REAL> > S2n(int n) {
        array_group<matrix3<REAL> > G("S"+std::to_string(2*n));
        G.generate(RotMtrx<REAL>({0,0,1},REAL(pi)/n)*Sigma<REAL>({0,0,1}));
        return G;
      }

      static array_group<matrix3<REAL> > Dn(int n) {
        array_group<matrix3<REAL> > G("D"+std::to_string(n));
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/n));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)));
        return G;
      }

      static array_group<matrix3<REAL> > Dnh(int n) {
        array_group<matrix3<REAL> > G("D"+std::to_string(n)+"h");
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/n));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)));
        G.generate(Sigma<REAL>({0,0,1}));
        return G;
      }

      static array_group<matrix3<REAL> > Dnd(int n) {
        array_group<matrix3<REAL> > G("D"+std::to_string(n)+"d");
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/n));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)));
        G.generate(Sigma<REAL>({std::sin(REAL(pi)/(2*n)),std::cos(REAL(pi)/(2*n)),0}));
        return G;
      }

      static array_group<matrix3<REAL> > T() {
        array_group<matrix3<REAL> > G("T");
        G.generate(RotMtrx<REAL>({1,1,1},2*REAL(pi)/3));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)));
        return G;
      }

      static array_group<matrix3<REAL> > Td() {
        array_group<matrix3<REAL> > G("Td");
        G.generate(RotMtrx<REAL>({1,1,1},2*REAL(pi)/3));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)));
        G.generate(Sigma<REAL>({1,1,0}));
        return G;
      }

      static array_group<matrix3<REAL> > Th() {
        array_group<matrix3<REAL> > G("Th");
        G.generate(RotMtrx<REAL>({1,1,1},REAL(pi)/3)*Sigma<REAL>({1,1,1}));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)));
        return G;
      }

      static array_group<matrix3<REAL> > O() {
        array_group<matrix3<REAL> > G("O");
        G.generate(RotMtrx<REAL>({1,1,1},2*REAL(pi)/3));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)/2));
        return G;
      }

      static array_group<matrix3<REAL> > Oh() {
        array_group<matrix3<REAL> > G("Oh");
        G.generate(RotMtrx<REAL>({1,1,1},2*REAL(pi)/3));
        G.generate(RotMtrx<REAL>({1,0,0},REAL(pi)/2));
        G.generate(-1*matrix3<REAL>::Identity());
        return G;
      }

      static array_group<matrix3<REAL> > I() {
        array_group<matrix3<REAL> > G("I");
        G.generate(RotMtrx<REAL>({0,0,1},2*REAL(pi)/5));
        REAL alp = acos(-std::cos(3*REAL(pi)/5)/(1+std::cos(3*REAL(pi)/5)));
        G.generate(RotMtrx<REAL>({std::sin(alp),0, std::cos(alp)},2*REAL(pi)/5));
        return G;
      }

      static array_group<matrix3<REAL> > Ih() {
        array_group<matrix3<REAL> > G = I();
        G.name = "Ih";
        G.generate(-1*matrix3<REAL>::Identity());
        return G;
      }

      static array_group<matrix3<REAL> > group(const STRING_EX & _name) {

        STRING_EX name  = tolower(_name), error = "Nonexisting point group "+_name;
        int n;
        size_t sz;

        try {
          n = std::stoi(name.substr(1),&sz);
          //std::cout << "shmogla " << n << " " <<  _name << "\n";
        }
        catch (const std::invalid_argument & e) {
          //std::cout << "ne shmogla " << _name << "\n";
          sz = 0; n=0;
        }

        CHAR_EX first = name[0], last;
        STRING_EX spec = name.substr(sz+1);
        if (spec.length() == 0)
          last = ' ';
        else if (spec.length() == 1)
          last = spec[0];
        else
          throw std::invalid_argument(error.c_str());

        //std::cout << "F= " << first << " L= " << last << "\n";

        if (first == 'c') {
            if (last == ' ' && n>0 ) return Cn(n);
            else if (last == 'v' && n>0 ) return Cnv(n);
            else if (last == 'h' && n>0 ) return Cnh(n);
            else if (last == 's' && n==0 ) return Cs();
            else if (last == 'i' && n==0 ) return Ci();
            else throw std::invalid_argument(error.c_str());
          }
        else if (first == 's') {
            if (last != ' ') throw std::invalid_argument(error.c_str());
            if ( n % 2 == 0 ) return S2n(n/2);
            else return Cnh(n);
          }
        else if (first == 'd') {
            if (n==0) throw std::invalid_argument(error.c_str());
            if (last == ' ') return Dn(n);
            else if (last == 'h') return Dnh(n);
            else if (last == 'd') return Dnd(n);
            else throw std::invalid_argument(error.c_str());
          }
        else if (first == 't') {
            if (n>0) throw std::invalid_argument(error.c_str());
            if (last == ' ') return T();
            else if (last == 'd') return Td();
            else if (last == 'h') return Th();
            else throw std::invalid_argument(error.c_str());
          }
        else if (first == 'o') {
            if (n>0) throw std::invalid_argument(error.c_str());
            if (last == ' ') return O();
            else if (last == 'h') return Oh();
            else throw std::invalid_argument(error.c_str());
          }
        else if (first == 'i') {
            if (n>0) throw std::invalid_argument(error.c_str());
            if (last == ' ') return I();
            else if (last == 'h') return Ih();
            else throw std::invalid_argument(error.c_str());
          }

        throw std::invalid_argument(error.c_str());

      }

      static std::vector<STRING_EX> groups_by_order(int n) {

        if (n==1) return {"C1"};
        else if (n==2) return {"Ci", "Cs", "C2", "C2h", "C2v", "D2", "D2h"};
        else if (n==3) return {"T", "C3", "C3v", "D3"};
        else if (n==4) return {"O", "Td", "C4", "C4h", "C4v", "D4", "D2d", "D4h", "S4"};
        else if (n==5) return {"I", "C5", "C5v", "D5"};
        else if (n==6) return {"Oh", "Th", "C6", "C3h", "C6h", "C6v", "D6", "D3d", "D3h", "D6h", "S6"};
        else if (n==7) return {"C7", "C7v", "D7"};
        else if (n==8) return {"C8", "C8h", "C8v", "D8", "D4d", "D8h", "S8"};
        else if (n==9) return {"C9", "C9v", "D9"};
        else if (n==10) return {"Ih", "C10", "C5h", "C10h", "C10v", "D10", "D5d", "D5h", "D10h", "S10"};
        else {
            STRING_EX nn = std::to_string(n), n2 = std::to_string(n/2);

            if (n%2==1) return {"C"+nn, "C"+nn+"v", "D"+nn};
            else if (n%4==2) return {"C"+nn, "C"+n2+"h", "C"+nn+"h", "C"+nn+"v", "D"+nn,
                    "D"+n2+"d", "D"+n2+"h", "D"+nn+"h", "S"+nn};
            else return {"C"+nn, "C"+nn+"h", "C"+nn+"v", "D"+nn, "D"+n2+"d", "D"+nn+"h", "S"+nn};
          }
      }

      // fingerprints
      struct fingerprint {
          std::vector<REAL> trace, det;
          std::vector<int> count;

          int size() const {return trace.size();}

          void add(REAL tr, REAL dt, REAL eps = matrix3<REAL>::tol_equiv) {
            int i=0;
            bool found = false;

            for (i=0; i<trace.size(); i++){
                if (std::abs(trace[i]-tr)<eps && std::abs(det[i]-dt)<eps)
                  {
                    found = true;
                    break;
                  }
                if (trace[i]+eps < tr || (std::abs(trace[i]-tr)<eps &&  det[i]+eps < dt))
                  break;
              }
            if (found)
              count[i]++;
            else
              {
                trace.insert(trace.begin()+i,tr);
                det.insert(det.begin()+i,dt);
                count.insert(count.begin()+i,1);
              }
          }

          bool compare(const fingerprint & f, REAL eps = matrix3<REAL>::tol_equiv) const {

            if (size() != f.size()) return false;

            bool res = true;

            for (int i=0; i<trace.size(); i++)
              if (!( std::abs(trace[i]-f.trace[i])<eps &&
                     std::abs(det[i]-f.det[i])<eps &&
                     count[i]==f.count[i])
                  ) {
                  res = false;
                  break;
                }

            return res;

          }

          bool operator==(const fingerprint & f) const {
            return compare(f);
          }

          fingerprint(){}

          fingerprint(const array_group<matrix3<REAL> > & G, REAL eps = matrix3<REAL>::tol_equiv) {
            for (int i=0; i<G.size(); i++) {
                auto M = G[i];
                add( M(0,0) + M(1,1) + M(2,2), M.determinant(), eps);
              }
          }


#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

          static void py_export(py::module &m, const char * pyname){
            py::class_<shnfl<REAL>::fingerprint>(m, pyname)
                .def(py::init<>())
                .def(py::init<const array_group<matrix3<REAL> > &, REAL>(),
                     py::arg("G"),
                     py::arg("eps") = matrix3<REAL>::tol_equiv)
                .def("add",     & shnfl<REAL>::fingerprint::add,
                     py::arg("tr"), py::arg("dt"),
                     py::arg("eps") = matrix3<REAL>::tol_equiv )
                .def("compare", & shnfl<REAL>::fingerprint::compare,
                     py::arg("f"),
                     py::arg("eps") = matrix3<REAL>::tol_equiv )
                .def("__len__", & shnfl<REAL>::fingerprint::size)
                .def_readwrite("trace", & shnfl<REAL>::fingerprint::trace)
                .def_readwrite("det",   & shnfl<REAL>::fingerprint::det)
                .def_readwrite("count", & shnfl<REAL>::fingerprint::count)
                ;
          }
#endif

      };


  };


};

#endif
