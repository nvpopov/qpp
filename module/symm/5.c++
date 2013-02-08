#include <iostream>
#include <symm/shenflis.hpp>
#include <lace/lace3d.hpp>
#include <cmath>

typedef lace::vector3d<double> vec3d;
typedef lace::matrix3d<double> mat3d;

void print_multab(qpp::shoenflis<double>::point_group &G)
{
  std::cout << "\\documentclass[12pt]{report} \n \n\\usepackage{longtable} \n\\usepackage{mathtext}   \n\\usepackage{amssymb} \n\\usepackage[T2A]{fontenc}  \n\\usepackage{indentfirst} \n\\usepackage{amsbsy} \n\\usepackage{epsf} \n \n\\setlength\\belowcaptionskip{10pt} \n\\renewcommand{\\baselinestretch}{1.5} \n\\begin{document} \n \n\\newcommand{\\rr}{\\boldsymbol{r}} \n\\newcommand{\\kk}{\\boldsymbol{k}} \n\\newcommand{\\RR}{\\boldsymbol{R}} \n\\newcommand{\\fsp}{\\mbox{ }} \n\\renewcommand{\\le}{\\leqslant} \n\\renewcommand{\\ge}{\\geqslant} \n\\newcommand{\\ds}{\\displaystyle} \n\\newcommand{\\eps}{\\varepsilon} \n\\newcommand{\\fmbr}{\\begin{array}{c}} \n\\newcommand{\\fm}{\\end{array}} \n\\newcommand{\\ra}{{\\rightarrow}} \n\\newcommand{\\eq}{\\begin{equation}} \n\\newcommand{\\eeq}{\\end{equation}} \n\\newcommand{\\arsh}{\\mathop{\\rm arsh}\\nolimits} \n \n";
  
  for (int i=0; i<G.n_irrep(); i++)
    {
      std::cout << "CLASS N " << i;
      for (int j = 0; j<G.n_class(i); j++)
	std::cout << " $" << G.notion(G.g_class(i,j)) << "$";
      std::cout << "\n\n";
    }
  std::cout << "\\end{document} \n";

}

int main()
{
  qpp::shoenflis<double>::point_group G = qpp::shoenflis<double>::T();
  G.build_all();

  //  for (int i=0; i<G.size(); i++)
  // for (int j=0; j<G.size(); j++)
  //   std::cout << i << " " << j << " " << G.multab(i,j) << "\n";

  print_multab(G);
}
