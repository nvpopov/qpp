#ifndef _QPP_SYMM_H
#define _QPP_SYMM_H

#include<vector>
#include<iterator>
#include<string>
#include<lace/lace.hpp>

//#include <iostream>

namespace qpp{

  const double invar_tol = 1e-6;

  // Ugly debug
  template <class VALTYPE,lace::vector_type VT >
  void prnvtr(lace::vector<VALTYPE,VT> &A)
  {
    for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%14.8f ") % A(i);
    std::cout << "\n";
  }
  template <class VALTYPE,lace::matrix_type MT >
  void prnmtr(lace::matrix<VALTYPE,MT> &A)
  {
    for(int i=0; i<A.size(0); i++)
      {
	for(int j=0; j<A.size(1); j++)
	  std::cout << boost::format("%10.5f ") % A(i,j);
	std::cout << "\n";
      }
  }

  template <class TRANSFORM, class VALTYPE>
  class symmetry_group{
    /* Implements the finite symmetry groups with arbitrary type of elements
       elements are of type TRANSFORM
       and this type must posess:
       1)  multiplication A*B
       2a) unity element TRANSFORM(1) or
       2b) you provide unity element manually
       3)  comparison A==B (implemented with some tolerance)
    */

    typedef std::vector<TRANSFORM> storage;

    //    typedef double VALTYPE;

    // All group elements are stored here
    storage G;

    // The names of group elements are stored here
    std::vector<std::string> S;

    // Multiplication table
    int * mtab;

    // The elements of the classes
    // cltab[i][j] is the j-th element of i-th class
    std::vector<std::vector<int> > cltab;
    std::vector<int> classof;

  public:
    // Character table
    lace::matrix<VALTYPE,lace::rectang> chi;

  private:
    // Dimensions of irreps
    std::vector<int> chardim;
    // Number of irreps can be less than number of classes 
    // if we restrict ourselves by real representation matricies
    int nirrep;
    
  public:
    // --------------------------------------------
    // Finds element g of the group and returns its index
    int index(TRANSFORM g)
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
  private:

    inline int mtidx(int i, int j)
    {
      return i*G.size()+j;
    }

  public:
    // ---------------------------------------------
    // Construction of the group multiplication table
    void build_multab()
    {
      mtab = new int[G.size()*G.size()];
      for (int i = 0; i<G.size(); i++)
	for (int j = 0; j<G.size(); j++)
	  mtab[mtidx(i,j)] = index(G[i]*G[j]);
    }

    // -----------------------------------------------------
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

    // ------------------------------------------------------------
    // Decompose the subspace of the regular representation defined by its
    // basis vectors n(i) into invariant subspaces
    void subspace_decompose_gen(lace::matrix<VALTYPE,lace::rectang> &n,
				std::vector<int> &dims)
    {
      // n(i,j) is j-th component of i-th basis vector of the subspace
      // dims array contains the dimensions of invariant subspaces

      // Step 1. Project regular representation on the subspace

      int N = n.size(0);
      int M = n.size(1);
      assert(N==G.size() && "only regular representaion subspaces!");

      std::vector<lace::matrix<VALTYPE,lace::rectang>*> T(N);
      for (int i = 0; i<N; i++)
	{
	  T[i] = new lace::matrix<VALTYPE,lace::rectang>(M);
	  *T[i] = n.H()*regrep(i)*n;
	}

      // Step 2. Form the matrix commuting the projected representation
      lace::matrix<VALTYPE, lace::rectang> A(M),B(M);
      const int MXRND = 1000000000;
      for (int i=1; i<N; i++)
	for (int j=0; j<=i; j++)
	  A(i,j) = A(j,i) = VALTYPE(1e0*(rand()%MXRND)/MXRND);

      B = A;
      for (int i=1; i<N; i++)
	B = B + (*T[i])*A*(*T[invert(i)]);      

      // Step 3. Diagonalize it
      lace::matrix<VALTYPE, lace::hermitian> S(M);
      for (int i=0; i<M; i++)
	for (int j=i; j<M; j++)
	  S(i,j) = B(i,j);
      
      lace::vector<VALTYPE> eig(M);
      lace::matrix<VALTYPE,lace::rectang> vecs(M);
  
      lace::diagon(S,eig,vecs);

      // Step 4. Count invariant subspaces
      // fixme! - check the constant, move its definition
      dims.clear();
      int d = 1;
      for (int i=1; i<M; i++)
	if ( lace::abs(eig(i)-eig(i-1))<invar_tol )
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
    // ------------------------------------------------------------
    // Version 2 - noniterative
    // 
    // Decompose the subspace of the regular representation defined by its
    // basis vectors n(i) into invariant subspaces
    // n(i,j) = delta_ij in the beginning
    void subspace_decompose(lace::matrix<VALTYPE,lace::rectang> &n,
			    std::vector<int> &dims)
    {
      // n(i,j) is j-th component of i-th basis vector of the subspace
      // dims array contains the dimensions of invariant subspaces


      int N = size();
      assert(N==n.size(0) && N==n.size(1) && "only regular representaion subspaces!");


      // Step 1. Form the matrix commuting the regular representation
      lace::matrix<VALTYPE, lace::rectang> A(N);
      const int MXRND = 1000000000;
      for (int i=0; i<N; i++)
	for (int j=0; j<=i; j++)
	  if (lace::numeric_type<VALTYPE>::is_complex())
	    {
	      A(i,j) =  VALTYPE(1e0*(rand()%MXRND)/MXRND) + 
		lace::numeric_type<VALTYPE>::I()*VALTYPE(1e0*(rand()%MXRND)/MXRND);
	      A(j,i) = lace::conj(A(i,j));
	    }
	  else
	    A(i,j) = A(j,i) = VALTYPE(1e0*(rand()%MXRND)/MXRND);

      lace::matrix<VALTYPE, lace::hermitian> S(N);

      for (int i=0; i<N; i++)
	for (int j=0; j<=i; j++)
	  {
	    VALTYPE ele = VALTYPE(0);

	    for (int g=0; g<N; g++)
	      ele += A(multab(i,g),multab(j,g));

	    S(i,j) = ele;
	  }


      // Step 3. Diagonalize it
      
      lace::vector<typename lace::eigvals_valtype<VALTYPE,lace::hermitian>::type> eig(N);
      lace::matrix<VALTYPE,lace::rectang> vecs(N);
  
      lace::diagon(S,eig,vecs);

      std::cout << "Eigval\n";
      eig = eig/eig(N-1);
      prnvtr(eig);

      std::cout << "Eigvec\n";
      prnmtr(vecs);

      // Step 4. Count invariant subspaces
      // fixme! - check the constant, move its definition
      dims.clear();
      int d = 1;
      for (int i=1; i<N; i++)
	if ( lace::abs(eig(i)-eig(i-1))<invar_tol )
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

    // ----------------------------------------------------------
    // Scalar product of two characters
    VALTYPE chi_scal(lace::vector<VALTYPE> ch, int irrep)
    {
      VALTYPE s = VALTYPE(0);
      for (int cl = 0; cl < n_class(); cl++)
	s += lace::conj(ch(cl))*chi(irrep,cl)*dim_class(cl);
      return s;
    }

    // This generic function decomposes arbitrary vector space
    // 
    //template<class VECTOR>
    //int irrep_decompose(int irrep, VECTOR )

    // Build character table by decomposing the regular representation
    // into invariant subspaces
    // fixme - find more efficient algorithm (MeatAxe?)
    // fixme - should this algorithm be recursive?
    void build_chi()
    {
      int N = G.size();
      chi.resize(n_class());

      lace::matrix<VALTYPE> n(N);
      n = VALTYPE(0);
      for (int i=0; i<N; i++) 
	n(i,i) = VALTYPE(1);
      std::vector<int> dims;
      const double chi_tol = 1e-6;

      subspace_decompose(n,dims);

      std::cout << "subspaces found with dims:\n";
      for (int i=0; i<dims.size(); i++)
      std::cout << dims[i] << " ";
      std::cout << "\n";

      // Find character
      int i0=0, i1;
      int nfound = 0;
      for (int rep = 0; rep < dims.size(); rep++)
	{
	  i1 = i0 + dims[rep] - 1;
	  
	  lace::vector<VALTYPE> new_chi(n_class());
	  for (int cl = 0; cl < n_class(); cl++)
	    {
	      int g = cltab[cl][0];
	      lace::matrix<VALTYPE,lace::rectang> R(dims[rep]);
	      R = n(lace::sub::full,lace::sub(i0,i1)).H()*regrep(g)*n(lace::sub::full,lace::sub(i0,i1));
	      new_chi(cl) = R.trace();
	    }

	  //std::cout << "New character \n";
	  //for (int cl = 0; cl < n_irrep(); cl++) std::cout << new_chi(cl) << " ";
	  //std::cout << "\n";

	  bool already = false;
	  for (int irrep=0; irrep < nfound; irrep++)
	    if ( lace::abs(chi_scal(new_chi,irrep)) > chi_tol )
	      {
		already = true;
		break;
	      }

	  if (!already)
	    {
	      for (int cl = 0; cl < n_class(); cl++)
		chi(nfound,cl) = new_chi(cl);
	      nfound++;
	    }

	  i0 = i1 + 1;
	}

      nirrep = nfound;

      for (int i=0; i<chi.size(0); i++)
	for (int j=0; j<chi.size(0); j++)
	  if (lace::abs(chi(i,j))<=invar_tol)
	    chi(i,j) = VALTYPE(0);
    }
    
  public:

    inline void add(TRANSFORM g, std::string nm = "")
    {
      G.push_back(g);
      S.push_back(nm);
    }

    inline void adduniq(TRANSFORM g, std::string nm = "") 
    {
      if (index(g)==-1) add(g,nm);
    }

    symmetry_group() : chi(){
      // Creates a group with just a unity element
      add(TRANSFORM(1),"E");
      mtab = NULL;
    }

    symmetry_group(TRANSFORM unity) : chi(){
      add(unity,"E");
      mtab = NULL;
    }

    symmetry_group(symmetry_group<TRANSFORM,VALTYPE> & GR) : 
      chi(lace::matrix_shape(lace::rectang,0,0))
    {
      G = GR.G;
      S = GR.S; 
    }

    ~symmetry_group()
    {
      if (mtab != NULL) delete mtab;
    }

    symmetry_group<TRANSFORM,VALTYPE>& operator=(symmetry_group<TRANSFORM,VALTYPE> & GR)
    {
      G = GR.G;
      S = GR.S;
    }

    void generator(TRANSFORM g)
    {
      if ( index(g) == -1 )
	{
	  add(g);
	  int i = 0;
	  while (i<G.size())
	    {
	      TRANSFORM h = g*G[i];
	      if ( index(h) == -1 ) add(h);
	      i++;
	    }
	}
    }

    inline TRANSFORM & operator()(int i)
    {
      return G[i];
    }

    inline std::string notion(int i) 
    {
      return S[i];
    }

    inline int multab(int i, int j)
    {
      return mtab[mtidx(i,j)];
    }

    inline int size(){return G.size();}

    virtual void build_all()
    {
      //      std::cout << "buildall start\n";
      build_multab();
      //      std::cout << "after build_multab\n";
      build_classes();
      build_chi();
    }

    int invert(int i)
    {
      int j=0;
      while (multab(i,j)!=0) j++;
      return j; 
    }

    inline int n_irrep()
    {
      return nirrep;
    }

    inline int n_class()
    {
      return cltab.size();
    }

    inline int dim_class(int i)
    {
      return cltab[i].size();
    }

    inline int dim_irrep(int i)
    {
      return int(lace::real(chi(i,0))+.5);
    }

    // j-th element of i-th class
    inline int g_class(int i, int j)
    {
      return cltab[i][j];
    }

    // class of i-th element
    inline int class_of(int i)
    {
      return classof[i];
    }

    // Regular representation matrix for i-th element
    lace::matrix<VALTYPE,lace::rectang> & regrep(int i)
    {
      lace::matrix<VALTYPE,lace::rectang> *R = new lace::matrix<VALTYPE,lace::rectang>(size());
      *R = VALTYPE(0);

      for (int j=0; j<size(); j++)
	(*R)(j,multab(j,i)) = VALTYPE(1);
      return *R;
    }

    
  };

};

#endif
