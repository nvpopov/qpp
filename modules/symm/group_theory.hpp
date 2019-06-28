#ifndef QPP_GROUP_THEORY_H
#define QPP_GROUP_THEORY_H

#include <vector>
#include <algorithm>
#include <complex>
#include <data/types.hpp>
#include <data/data.hpp>
#include <Eigen/Dense>

namespace qpp {

  template<class TRANSFORM, class ARRAY = std::vector<TRANSFORM> >
  class group_analyzer {

      // All group elements are stored here
      const ARRAY & G;

      // Orders
      int* ordr{nullptr};

      // The elements of the classes
      // cltab[i][j] is the j-th element of i-th class
      std::vector<std::vector<int> > cltab;
      std::vector<int> classof;

      // where in mtab is the record for i-th times j-th element
      /*
      inline int mtidx(int i, int j) const
      {
        return i*G.size()+j;
      }
    */

    public:

      // Multiplication table
      //  int * mtab;
      static_table<int> multab;

      // --------------------------------------------
      // Finds element g of the group and returns its index
      int index(const TRANSFORM & g) const {
        int i;
        bool result=false;

        for (i=0; i<G.size(); i++)
          if ( G[i] == g) {
              result = true;
              break;
            }

        return result? i : -1;
      }

      // Construction of the group multiplication table
      void build_multab() {
        //        if (mtab!=NULL) delete mtab;
        //mtab = new int[G.size()*G.size()];

        multab.resize(G.size(),G.size());

        for (int i = 0; i<G.size(); i++)
          for (int j = 0; j<G.size(); j++)
            multab(i,j) = index(G[i]*G[j]);
      }

      // Find orders of all elements
      void build_orders() {

        //        if (ordr != nullptr) delete [] ordr;
        delete [] ordr;
        ordr = new int [G.size()];

        for (int g = 0; g < G.size(); g++) {
            int n = 0, h = g;
            while (h != 0) {
                n++;
                h = multab(h,g);
              }
            ordr[g] = n + 1;
          }

      }

      // Find the classes
      void build_classes() {

        std::vector<bool> already(G.size());
        for (int i=0; i<G.size(); i++) already[i] = false;

        int Ncl = 0;
        do {
            int i=0;
            while (i<G.size() && already[i]) i++;
            if (i==G.size()) break;
            cltab.resize(Ncl+1);

            for (int j=0; j<G.size(); j++){
                int k = multab(multab(j,i),invert(j));
                if (!already[k]) {
                    cltab[Ncl].push_back(k);
                    already[k] = true;
                  }
              }

            Ncl++;
          } while (true);

        classof.resize(G.size());

        for (int i=0; i<G.size(); i++) {
            bool found = false;
            int jcl;
            for (jcl=0; jcl<cltab.size(); jcl++) {

                for (int k=0; k<cltab[jcl].size(); k++)
                  if (cltab[jcl][k]==i) {
                      found = true; break;
                    }

                if (found){
                    classof[i]=jcl;
                    break;
                  }
              }
          }

        //std::cout << "Nclasses= " << cltab.size() << "\n";
      }

      // multiplication table
      /*
      inline int multab(int i, int j) const {
        return mtab[mtidx(i,j)];
      }
    */

      // order of the element
      inline int order(int i) const {
        return ordr[i];
      }

      // inverse of i-th element
      int invert(int i) const {
        int j=0;
        while (multab(i,j)!=0) j++;
        return j;
      }

      // number of classes
      inline int n_classes() const {
        return cltab.size();
      }

      // nember of elements in i-th class
      inline int class_size(int i) const {
        return cltab[i].size();
      }

      // j-th element of i-th class
      inline int class_element(int i, int j) const {
        return cltab[i][j];
      }

      // class of i-th element
      inline int class_of(int i) const {
        return classof[i];
      }

      // --------------------------------------------------------

      // Construct abelian subgroup with g-th element
      std::vector<int> abelian_sub(int g) {
        std::vector<int> sub = {0};
        int h = g;
        while (h!=0){
            sub.push_back(h);
            h = multab(g,h);
          }
        return sub;
      }

      std::vector<int> mul_subs(const std::vector<int> & G1, const std::vector<int> &G2) {

        std::vector<int> res;
        res.resize(G1.size()*G2.size());
        int i=0;

        for (int g1 : G1)
          for (int g2 : G2)
            res[i++] = multab(g1,g2);

        std::sort(res.begin(), res.end());
        res.erase( std::unique( res.begin(), res.end() ), res.end() );
        return res;

      }

      std::vector<int> find_generators(const std::vector<int> & H) {
        int N = G.size();
        if (H.size() == N)
          return std::vector<int>();

        std::vector<int> H1(H), F;
        std::sort(H1.begin(),H1.end());
        int i1=0;
        for (int i=0; i<N; i++){
            while (H1[i1]<i && i1 < H1.size()-1) i1++;
            if ( N % (H.size()*order(i))==0 &&  i!=H1[i1] )
              F.push_back(i);
          }
        std::sort(F.begin(),F.end(),
                  [this] (const int & a, const int & b) -> bool {
            return order(a) > order(b) ? true : order(a)==order(b) && a<b;
          } );

        /*
      std::cout << "F sorted:\n";
      for (int i : F)
        std::cout << " " << i << "(" << order(i) << ")";
      std::cout << "\n";
      */

        for (int g : F){
            //std::cout << "trying " << g << "\n";

            H1.clear();
            H1 = mul_subs(H, abelian_sub(g) );
            if (H1.size() == H.size()*order(g)){
                std::vector<int> gg = find_generators(H1);
                bool success = !(gg.size()==1 && gg[0]==-1);
                if (success)
                  {
                    gg.insert(gg.begin(),g);
                    return gg;
                  }
              }
          }
        return std::vector<int>({-1});
      }

      //-------------------------------------------------------------------------------------

      // Constructors
      group_analyzer(const ARRAY & _G) : G(_G) {
        //mtab = NULL;
        //ordr = NULL;

        //std::cout << "alive1\n";
        build_multab();

        //std::cout << "alive2\n";
        build_orders();

        //std::cout << "alive3\n";
        build_classes();

        //std::cout << "alive4\n";
      }

      ~group_analyzer() {
        //      if (ordr != nullptr) delete [] ordr;
        delete [] ordr;
      }

  };

  // -------------------------------------------------------------------------------

  template <class TRANSFORM, class ARRAY = std::vector<TRANSFORM> >
  void generator_form(genform_group<TRANSFORM> & R, ARRAY & G) {
    group_analyzer<TRANSFORM,ARRAY> A(G);
    std::vector<int> ee = {0}, gg = A.find_generators(ee);
    int DIM = gg.size();

    //genform_group<TRANSFORM> R(DIM);
    R.set_dim(DIM);
    for (int d = 0; d<DIM; d++)
      R.generators[d] = G[gg[d]];

    R.auto_orders();

    //return R;
  }

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

      group_characters(const ARRAY & _G,
                       const group_analyzer<TRANSFORM,ARRAY> & _A) :
        G(_G), A(_A){
        //std::cout << "before characters\n";
        build_chi();
      }

      // Regular representation matrix for i-th element
      matrix regrep(int i) {
        matrix R = matrix::Zero(G.size(),G.size());

        for (int j=0; j<G.size(); j++)
          R(j,A.multab(j,i)) = VALTYPE(1);
        return R;
      }

      // ----------------------------------------------------------
      // Scalar product of character chi with irrep character
      VALTYPE chi_scal(const vector &ch, int irrep) {
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
      void subspace_decompose(matrix &n, std::vector<int> &dims) {
        // n(i,j) is j-th component of i-th basis vector of the subspace
        // dims array contains the dimensions of invariant subspaces

        int N = G.size();
        if (N!=n.rows() || N!=n.cols())
          throw std::range_error("group_characters::subspace_decompose : "
                                 "only regular representaion subspaces!");

        // Step 1. Form the matrix commuting the regular representation
        //std::cout << "step1\n";

        matrix R = matrix::Random(N,N);
        R = R + R.adjoint().eval();

        matrix S(N,N);

        for (int i=0; i<N; i++)
          for (int j=0; j<=i; j++){
              VALTYPE ele = VALTYPE(0);

              for (int g=0; g<N; g++)
                ele += R(A.multab(i,g), A.multab(j,g));

              S(i,j) = ele;
            }


        // Step 3. Diagonalize it
        //std::cout << "step3\n";
        Eigen::SelfAdjointEigenSolver<matrix> es;

        es.compute(S,Eigen::ComputeEigenvectors);

        auto  eig = es.eigenvalues();
        auto  vecs = es.eigenvectors();

        //      std::cout << "Eigval\n";
        eig /= eig(N-1);
        //std::cout <<  eig << std::endl;

        //std::cout << "Eigvec\n";
        //std::cout <<  vecs << std::endl;

        // Step 4. Count invariant subspaces
        // fixme! - check the constant, move its definition
        //std::cout << "step4\n";
        dims.clear();
        int d = 1;
        for (int i=1; i<N; i++)
          if ( std::abs(eig(i)-eig(i-1))<chi_tol )
            d++;
          else{
              dims.push_back(d);
              d=1;
            }

        dims.push_back(d);

        // Step 5. Transform basis vectors n so that they are
        // basis vector for invariant subspaces just found

        //std::cout << "step5\n";
        n = n*vecs;
      }

      // Build character table by decomposing the regular representation
      // into invariant subspaces
      // fixme - find more efficient algorithm (MeatAxe?)
      // fixme - should this algorithm be recursive?
      void build_chi() {
        int N = G.size();
        //chi.resize(A.n_classes());

        matrix n = matrix::Identity(N, N);

        std::vector<int> dims;

        subspace_decompose(n, dims);

        //std::cout << "subspaces found with dims:\n";
        //for (int i=0; i<dims.size(); i++)
        //std::cout << dims[i] << " ";
        //std::cout << "\n";

        // Find character
        int i0=0, i1;
        int nfound = 0;

        chi.resize(1, A.n_classes());

        for (int rep = 0; rep < dims.size(); rep++){
            i1 = i0 + dims[rep] - 1;

            vector new_chi(A.n_classes());
            for (int cl = 0; cl < A.n_classes(); cl++){
                int g = A.class_element(cl,0);
                matrix R(dims[rep], dims[rep]);
                R = n.block(
                      0, i0, n.rows(), i1-i0+1).adjoint()*regrep(g)*n.block(
                      0,i0,n.rows(), i1-i0+1);
                new_chi(cl) = R.trace();
              }

            //std::cout << "New character \n";
            //for (int cl = 0; cl < n_irrep(); cl++) std::cout << new_chi(cl) << " ";
            //std::cout << "\n";

            bool already = false;
            for (int irrep=0; irrep < nfound; irrep++)
              if ( std::abs(chi_scal(new_chi, irrep)) > chi_tol ){
                  already = true;
                  break;
                }

            if (!already){
                chi.conservativeResize(nfound+1, A.n_classes() );
                for (int cl = 0; cl < A.n_classes(); cl++)
                  chi(nfound, cl) = new_chi(cl);
                nfound++;
              }

            i0 = i1 + 1;
          }

        nirrep = nfound;

        for (int i = 0; i < chi.rows(); i++)
          for (int j = 0; j < chi.rows(); j++)
            if (std::abs(chi(i, j))<=chi_tol)
              chi(i, j) = VALTYPE(0);
      }

  };

} //namespace qpp

#endif
