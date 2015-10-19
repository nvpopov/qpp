#include <data/globals.hpp>
#include <data/meta.hpp>

int main()
{
  for (int i=0; i<qpp::global::metas.size(); i++)
    {
      std::cout << "Meta #" << i << " " << qpp::global::keywords[i] << "\n";
      //      qpp::global::metas[i]->write(std::cout);
    }
}

