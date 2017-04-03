#ifndef _QPP_GROUP_THEORY_H
#define _QPP_GROUP_THEORY_H

#include <vector>
#include <complex>
#include <data/types.hpp>
#include <Eigen/Dense>

namespace qpp{

  template<class TRANSFORM, class ARRAY = std::vector<TRANSFORM> >
  class group_analyzer{
    
    // All group elements are stored here
    const ARRAY & G;

    // Multiplication table
    int * mtab;

    // The elements of the classes
    // cltab[i][j] is the j-th element of i-th class
    std::vector<std::vector<int> > cltab;
    std::vector<int> classof;
    
    // --------------------------------------------
    // Finds element g of the group and returns its index
    int index(const TRANSFORM & g) const
    {
      int i;
      bool result=false;
      for (i=0; i<G.size(); i++)
	if ( G[i] == g )
	  {
	    result = true;
	    break;
	  }
      return result? i : -1;
    }

    // where in mtab is the record for i-th times j-th element
    inline int mtidx(int i, int j) const
    {
      return i*G.size()+j;
    }

    // Construction of the group multiplication table
    void build_multab()
    {
      mtab = new int[G.size()*G.size()];
      for (int i = 0; i<G.size(); i++)
	for (int j = 0; j<G.size(); j++)
	  mtab[mtidx(i,j)] = index(G[i]*G[j]);
    }

    // Find the classes
    void build_classes()
    {
      std::vector<bool> already(G.size());
      for (int i=0; i<G.size(); i++)
	already[i] = false;
      int Ncl = 0;
      do
	{
	  int i=0;
	  while ( i<G.size() && already[i] ) i++;
	  if (i==G.size()) break;
	  cltab.resize(Ncl+1);
	  
	  for (int j=0; j<G.size(); j++)
	    {
	      int k = multab(multab(j,i),invert(j));
	      if (!already[k])
		{
		  cltab[Ncl].push_back(k);
		  already[k] = true; 
		}
	    }

	  Ncl++;
	} while (true);

      classof.resize(G.size());
      for (int i=0; i<G.size(); i++)
	{
	  bool found = false;
	  int jcl;
	  for (jcl=0; jcl<cltab.size(); jcl++)
	    {
	      for (int k=0; k<cltab[jcl].size(); k++)
		if (cltab[jcl][k]==i)
		  {
		    found = true; break;
		  }
	      if (found) 
		{
		  classof[i]=jcl;
		  break;
		}
	    }
	}

      //std::cout << "Nclasses= " << cltab.size() << "\n";
    }

  public:

    // multiplication table
    inline int multab(int i, int j) const
    {
      return mtab[mtidx(i,j)];
    }

    // inverse of i-th element
    int invert(int i) const
    {
      int j=0;
      while (multab(i,j)!=0) j++;
      return j; 
    }
    
    // number of classes
    inline int n_classes() const
    {
      return cltab.size();
    }

    // nember of elements in i-th class
    inline int class_size(int i) const
    {
      return cltab[i].size();
    }

    // j-th element of i-th class
    inline int class_element(int i, int j) const
    {
      return cltab[i][j];
    }
    
    // class of i-th element
    inline int class_of(int i) const
    {
      return classof[i];
    }

    // Constructors
    group_analyzer(const ARRAY & _G) : G(_G)
    {
      build_multab();
      
      std::cout << "Multiplication table:\n";
      
      for (int i=0; i<G.size(); i++)
	{
	  std::cout << boost::format("%3i |") % i;
	  for (int j=0; j<G.size(); j++)
	    std::cout << boost::format("%3i ") % multab(i,j);
	  std::cout << std::endl;
	}

      build_classes();
    }

  };

  // -------------------------------------------------------------------------------
  
  template <class VALTYPE, class TRANSFORM, class ARRAY = std::vector<TRANSFORM> >
  class group_characters{
    
    // All group elements are stored here
    const ARRAY & G;

    // The group is already partitioned into classes
    const group_analyzer<TRANSFORM,ARRAY> & A;

    typedef Eigen::Matrix<VALTYPE, Eigen::Dynamic, Eigen::Dynamic> matrix;
    typedef Eigen::Matrix<VALTYPE, Eigen::Dynamic, 1> vector;

  public:

    double chi_tol = 1e-6;

    // Character table
    matrix chi;
    int nirrep;
    
    group_characters(const ARRAY & _G, const group_analyzer<TRANSFORM,ARRAY> & _A) :
      G(_G), A(_A)
    {
      build_chi();
    }

    // Regular representation matrix for i-th element
    matrix regrep(int i)
    {
      matrix R = matrix::Zero(G.size(),G.size());
      
      for (int j=0; j<G.size(); j++)
	R(j,A.multab(j,i)) = VALTYPE(1);
      return R;
    }
    
    // ----------------------------------------------------------
    // Scalar product of character chi with irrep character
    VALTYPE chi_scal(const vector &ch, int irrep)
    {
      VALTYPE s(0);
      for (int cl = 0; cl < A.n_classes(); cl++)
	s += std::conj(ch(cl))*chi(irrep,cl)*VALTYPE(A.class_size(cl));
      return s;
    }

    // ------------------------------------------------------------
    // Version 2 - noniterative
    // 
    // Decompose the subspace of the regular representation defined by its
    // basis vectors n(i) into invariant subspaces
    // n(i,j) = delta_ij in the beginning
    void subspace_decompose(matrix &n, std::vector<int> &dims)
    {
      // n(i,j) is j-th component of i-th basis vector of the subspace
      // dims array contains the dimensions of invariant subspaces
      
      int N = G.size();
      if (N!=n.rows() || N!=n.cols())
	throw  std::range_error("group_characters::subspace_decompose : only regular representaion subspaces!");

      // Step 1. Form the matrix commuting the regular representation
      matrix R = matrix::Random(N,N);
      R = R + R.adjoint().eval();

      matrix S(N,N);

      for (int i=0; i<N; i++)
	for (int j=0; j<=i; j++)
	  {
	    VALTYPE ele = VALTYPE(0);

	    for (int g=0; g<N; g++)
	      ele += R(A.multab(i,g),A.multab(j,g));

	    S(i,j) = ele;
	  }


      // Step 3. Diagonalize it
      Eigen::SelfAdjointEigenSolver<matrix> es;

      es.compute(S,Eigen::ComputeEigenvectors);

      auto  eig = es.eigenvalues();
      auto  vecs = es.eigenvectors();

      std::cout << "Eigval\n";      
      eig /= eig(N-1);
      std::cout <<  eig << std::endl;

      std::cout << "Eigvec\n";
      std::cout <<  vecs << std::endl;

      // Step 4. Count invariant subspaces
      // fixme! - check the constant, move its definition
      dims.clear();
      int d = 1;
      for (int i=1; i<N; i++)		  
	if ( std::abs(eig(i)-eig(i-1))<chi_tol )
	  d++;
	else
	  {
	    dims.push_back(d);
	    d=1;
	  }
      
      dims.push_back(d);

      // Step 5. Transform basis vectors n so that they are
      // basis vector for invariant subspaces just found
      
      n = n*vecs;      
    }

    // Build character table by decomposing the regular representation
    // into invariant subspaces
    // fixme - find more efficient algorithm (MeatAxe?)
    // fixme - should this algorithm be recursive?
    void build_chi()
    {
      int N = G.size();
      //chi.resize(A.n_classes());
      
      matrix n = matrix::Identity(N,N);
      
      std::vector<int> dims;

      subspace_decompose(n,dims);

      std::cout << "subspaces found with dims:\n";
      for (int i=0; i<dims.size(); i++)
	std::cout << dims[i] << " ";
      std::cout << "\n";

      // Find character
      int i0=0, i1;
      int nfound = 0;

      chi.resize(1,A.n_classes());

      for (int rep = 0; rep < dims.size(); rep++)
	{
	  i1 = i0 + dims[rep] - 1;
	  
	  vector new_chi(A.n_classes());
	  for (int cl = 0; cl < A.n_classes(); cl++)
	    {
	      int g = A.class_element(cl,0);
	      matrix R(dims[rep],dims[rep]);
	      R = n.block(0,i0,n.rows(),i1-i0+1).adjoint()*regrep(g)*n.block(0,i0,n.rows(),i1-i0+1);
	      new_chi(cl) = R.trace();
	    }
	  
	  //std::cout << "New character \n";
	  //for (int cl = 0; cl < n_irrep(); cl++) std::cout << new_chi(cl) << " ";
	  //std::cout << "\n";

	  bool already = false;
	  for (int irrep=0; irrep < nfound; irrep++)
	    if ( std::abs(chi_scal(new_chi,irrep)) > chi_tol )
	      {
		already = true;
		break;
	      }

	  if (!already)
	    {
	      chi.conservativeResize(nfound+1, A.n_classes() );
	      for (int cl = 0; cl < A.n_classes(); cl++)
		chi(nfound,cl) = new_chi(cl);
	      nfound++;
	    }
	  
	  i0 = i1 + 1;
	}
      
      nirrep = nfound;

      for (int i=0; i<chi.rows(); i++)
	for (int j=0; j<chi.rows(); j++)
	  if (std::abs(chi(i,j))<=chi_tol)
	    chi(i,j) = VALTYPE(0);
    }


  };
  
};

#endif
