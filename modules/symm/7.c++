#include <iostream>
#include <symm/shenflis.hpp>
#include <lace/lace3d.hpp>
#include <cmath>

class permutation
{
  int *p;
  int N;

public:
  
  permutation(){ N=0;}

  permutation(int _N)
  {
    N = _N;
    p = new int [N];
  }

  permutation(const permutation & P)
  {
    N = P.N;
    p = new int [N];
    for (int i=0; i<size(); i++)
      p[i] = P.p[i];
  }

  inline int & operator()(int i)
  {
    return p[i];
  }

  inline int size() const
  {
    return N;
  }

  inline permutation operator*(permutation & Q)
  {
    assert(size() == Q.size());
    permutation R(size());

    for (int i=0; i<size(); i++)
      R(i)=p[Q(i)];
    return R;
  }

  static permutation unity(int N)
  {
    permutation R(N);
    for (int i=0; i<N; i++)
      R(i)=i;
    return R;
  }

  ~permutation()
  {
    if (N>0)
      delete p;
  }

  bool operator==(permutation P) const
  {
    if (N==P.N)
      {
	bool eq=true;
	for (int i=0; i<N; i++)
	  if (p[i]!=P.p[i])
	    {
	      eq=false;
	      break;
	    }
	return eq;
      }
    else return false;
  }

};

template<typename _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os, permutation P)
{
  std::basic_ostringstream<_CharT, _Traits> __s;
  __s.flags(__os.flags());
  __s.imbue(__os.getloc());
  __s.precision(__os.precision());
  __s << "[";
  for (int i=0; i<P.size(); i++)
    __s << P(i);
  __s << "]";
  return __os << __s.str();
}


void preamble()
{
  std::cout << "\\documentclass[12pt]{report} \n \n\\usepackage{longtable} \n\\usepackage{mathtext}   \n\\usepackage{amssymb} \n\\usepackage[T2A]{fontenc}  \n\\usepackage{indentfirst} \n\\usepackage{amsbsy} \n\\usepackage{epsf} \n \n\\setlength\\belowcaptionskip{10pt} \n\\renewcommand{\\baselinestretch}{1.5} \n\\begin{document} \n \n\\newcommand{\\rr}{\\boldsymbol{r}} \n\\newcommand{\\kk}{\\boldsymbol{k}} \n\\newcommand{\\RR}{\\boldsymbol{R}} \n\\newcommand{\\fsp}{\\mbox{ }} \n\\renewcommand{\\le}{\\leqslant} \n\\renewcommand{\\ge}{\\geqslant} \n\\newcommand{\\ds}{\\displaystyle} \n\\newcommand{\\eps}{\\varepsilon} \n\\newcommand{\\fmbr}{\\begin{array}{c}} \n\\newcommand{\\fm}{\\end{array}} \n\\newcommand{\\ra}{{\\rightarrow}} \n\\newcommand{\\eq}{\\begin{equation}} \n\\newcommand{\\eeq}{\\end{equation}} \n\\newcommand{\\arsh}{\\mathop{\\rm arsh}\\nolimits} \n \n";
}

//typedef lace::dcomplex VALTYPE;
typedef double VALTYPE;

void print_multab(qpp::symmetry_group<permutation,float> &G)
{
  
  std::cout << "\\center{The group multiplication table:}\n\n";
  std::cout << "\\begin{tabular}{c | ";
  for (int i=0; i<G.size(); i++)
    std::cout << "c "; 
  std::cout <<  "} \n";
  
  for (int j=0; j<G.size(); j++)
    std::cout << "& " << "$" << G.notion(j) << "$";
  std::cout << "\\\\ \n \\hline \n ";

  for (int i=0; i<G.size(); i++)
    {
      std::cout << "$" << G.notion(i) << "$";
      for (int j=0; j<G.size(); j++)
	std::cout << "& " << "$" << G.notion(G.multab(i,j)) << "$";
      std::cout << "\\\\\n";
    }
  std::cout << "\\end{tabular}\n\n";

  std::cout << "\\\\\nClasses of conjugated elements:\n\\\\\n";
  for (int i=0; i<G.n_class(); i++)
    {
      std::cout << "\\{";
      for (int j = 0; j<G.dim_class(i); j++)
	std::cout << " $" << G.notion(G.g_class(i,j)) << "$";
      std::cout << "\\}";
      if (i<G.n_class()-1) 
	std::cout << ",";
      else
	std::cout << "\n\n";
    }
}


void print_class(qpp::symmetry_group<permutation,float> &G, int cl)
{
  std::cout << "$\\{";
  for (int j = 0; j<G.dim_class(cl); j++)
    std::cout << G.notion(G.g_class(cl,j));
  std::cout << "\\}$";
}


void print_chi(qpp::symmetry_group<permutation,float> &G)
{
  std::cout << "Character table:\n\n\n";
  std::cout.precision(7);

  std::cout << "\\begin{tabular}{c | ";
  for (int i=0; i<G.n_class(); i++)
    std::cout << "c "; 
  std::cout <<  "} \n";
  
  for (int j=0; j<G.n_class(); j++)
    {
      std::cout << "& " << j;

      //      print_class(G,j);
    }
  std::cout << "\\\\ \n \\hline \n ";

  for (int i=0; i<G.n_irrep(); i++)
    {
      for (int j=0; j<G.n_class(); j++)
	std::cout << "& " << G.chi(i,j);
      std::cout << "\\\\\n";
    }
  std::cout << "\\end{tabular}\n\n";
}


void permute(qpp::symmetry_group<permutation,float> &G, permutation &P, int i)
{
  if (i==P.size() && !(P==permutation::unity(P.size())))
    {
      std::stringstream s;
      s << P;
      G.add(P,s.str());
    }
  else
    for ( P(i) = 0; P(i) < P.size(); P(i)++)
      {
	bool duplic = false;
	for (int j=0; j<i; j++)
	  if (P(i)==P(j))
	  {
	    duplic=true;
	    break;
	  }
	if (!duplic)
	  permute(G,P,i+1);
      }
}


void print_end()
{
  std::cout << "\\end{document} \n";
}

int main()
{

  //  permutation P(3),Q(3);
  //P(0)=2; P(1)=1; P(2)=0;
  //Q(0)=1; Q(1)=0; Q(2)=2;

  //std::cout << P << "*" << Q << "=" << P*Q << "\n";

  int N = 3;

  qpp::symmetry_group<permutation,float> G(permutation::unity(N));

  permutation P(N);
  permute(G,P,0);

  //for (int i=0; i<G.size(); i++)
    //  std::cout << G(i) << " " << G.notion(i) << "\n";
  //G.build_multab();

  G.build_all();

  preamble();
  print_multab(G);
  print_chi(G);
  //  check_regrep(G);
  print_end();
  
}
