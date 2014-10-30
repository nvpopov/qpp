#include<geom/geom.hpp>
#include<io/geomio.hpp>
#include<io/qpparser.hpp>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <initializer_list>
#endif

#include <geom/shape.hpp>
#include <mathf/intlst.hpp>
//#include <dsyevj3.h>

const int N = 5;
//const double sc = .02;
#define DIM 3

typedef lace::vector3d<double> v3d;
typedef lace::vector2d<double> v2d;
typedef lace::vector3d<int> i3d;
typedef lace::matrix3d<double> m3d;
using qpp::pi;

/*
int diagon(const m3d &A, m3d &Q, v3d &lmb)
{
  double AA[3][3], QQ[3][3], ll[3];
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      AA[i][j] = A(i,j);
  
  dsyevj3(AA, QQ, ll);

  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      Q(i,j) = QQ[i][j];
  
  for (int i=0; i<3; i++)
    lmb(i) = ll[i];

}
*/

double Sig(const v3d &a1, const v3d &a2, const v3d &b1, const v3d &b2, m3d & R)
{
  double la1 = norm(a1), la2 = norm(a2), lb1 = norm(b1), lb2 = norm(b2);
  double alpha = std::acos(scal(a1,a2)/(la1*la2)),
    beta = std::acos(scal(b1,b2)/(lb1*lb2));

  v3d n1 = a1/la1, n2 = b1/lb1, n = n1%n2;
  n /= norm(n);
  double cost = scal(n1,n2);

  m3d R1,R2,R3;

  R1 = lace::RotMtrx(n, -std::acos(cost));

  v3d aa1 = R1*a1, aa2 = R1*a2;

  n = b1/lb1;
  n1 = aa2 - n*scal(aa2,n);
  n1 /= norm(n1);

  n2 = b2 - n*scal(b2,n);
  n2 /= norm(n2);

  R2 = lace::outer(n,n) + lace::outer(n2,n1) + lace::outer(n%n2,n%n1);

  aa1 = R2*aa1;
  aa2 = R2*aa2;

  n = b1%b2;
  n /= norm(n);

  double tant = std::sin(alpha-beta)/(std::cos(alpha-beta)+(la1*lb1)/(la2*lb2));

  R3 = lace::RotMtrx(n, std::atan(tant));
  R = R3*R2*R1;

  double Sigma = la1*la1 + la2*la2 + lb1*lb1 + lb2*lb2 -
    2*std::sqrt(la1*la1*lb1*lb1 + la2*la2*lb2*lb2 + 2*la1*lb1*la2*lb2*std::cos(alpha-beta));

  double Sigma1 = norm2(b1-R*a1) + norm2(b2 - R*a2);

  return Sigma;
}

// ---------------------------------------------------------------------

std::vector<lace::matrix3d<int> > O,Oh;

void build_O()
{
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      if (j!=i)
	for (int k=0; k<3; k++)
	  if (k!=i && k!=j)
	    for (int sx=1; sx>=-1; sx-=2)
	      for (int sy=1; sy>=-1; sy-=2)
		for (int sz=1; sz>=-1; sz-=2)
		  {
		    lace::matrix3d<int> M=0;
		    M(0,i)=sx;
		    M(1,j)=sy;
		    M(2,k)=sz;
		    Oh.push_back(M);
		    if (det(M)==1)
		      O.push_back(M);
		  }
}

// --------------------------------------------------------------------

void match_latt1(const qpp::periodic_cell<3> & cell1, const qpp::periodic_cell<3> & cell2)
{
  for (int n=1; n<N; n++)
    for (int n1 = 0; n1<=n; n1++)
      for (int n2 = -n; n2<=n; n2++)
	if (n1*n1+n2*n2<=n*n)
	  for (int n3 = -n; n3<=n; n3++)
	    if ( n1*n1+n2*n2+n3*n3<=n*n &&  n1*n1+n2*n2+n3*n3>(n-1)*(n-1))
	      for (int m=1; m<=n; m++)
		for (int m1 = -m; m1<=m; m1++)
		  for (int m2 = -m; m2<=m; m2++)
		    if (m1*m1+m2*m2<=m*m)
		      for (int m3 = -m; m3<=m; m3++)
			if ( m1*m1+m2*m2+m3*m3<=m*m &&  m1*m1+m2*m2+m3*m3>(m-1)*(m-1))
			  {
			    double S;
			    int ii;
			    i3d nn(n1,n2,n3),mm(m1,m2,m3);
			    if (! (nn%mm==i3d(0,0,0)))
			      {
				for (int i=0; i<O.size(); i++)
				  {
				    v3d a1,a2,b1,b2;
				    i3d ni = O[i]*nn;
				    i3d mi = O[i]*mm;

				    a1 = nn(0)*cell1(0) + nn(1)*cell1(1) + nn(2)*cell1(2);
				    a2 = mm(0)*cell1(0) + mm(1)*cell1(1) + mm(2)*cell1(2);
				    b1 = ni(0)*cell2(0) + ni(1)*cell2(1) + ni(2)*cell2(2);
				    b2 = mi(0)*cell2(0) + mi(1)*cell2(1) + mi(2)*cell2(2);
				    lace::matrix3d<double> R,OO;
				    for (int j=0; j<3; j++)
				      for (int k=0; k<3; k++)
					OO(j,k) = O[i](j,k);
				    
				    b1 = OO*b1;
				    b2 = OO*b2;
				    
				    double S1 =  Sig(a1,a2,b1,b2,R)/lace::norm2(a1%a2);
				    if ( S1<S || i==0)
				      {
					S = S1;
					ii = i;
				      }
				  }
				std::cout << nn << mm << O[ii]*nn << O[ii]*mm << " " 
					  << S << " symop=" << ii << "\n";
			      }
			  }
}

// -----------------------------------------------------------

v2d strten(const v3d & a1, const v3d & a2, const v3d & b1, const v3d & b2)
{
  double aa1=norm(a1), aa2 = norm(a2), bb1 = norm(b1), bb2 = norm(b2);

  double eta1 = bb1/aa1, eta2 = bb2/aa2;
  double cosa = scal(a1,a2)/(aa1*aa2), cosb = scal(b1,b2)/(bb1*bb2);
  double sina = std::sqrt(1-cosa*cosa), sinb = std::sqrt(1-cosb*cosb);

  double M = eta1*eta1 + eta2*eta2 - 2*eta1*eta2*cosa*cosb;


  double D = M*M - 4*eta1*eta1*eta2*eta2*sinb*sinb*sina*sina;
  D = std::sqrt(D);

  return v2d(std::sqrt(M/2+D/2),std::sqrt(M/2-D/2))/sina;
}

// -----------------------------------------------

bool mutually_simple(int n1, int n2, int n3)
{
  int m = n1;
  if (m>n2)
    m = n2;
  if (m>n3)
    m = n3;

  bool found = false;
  for (int d = 2; d<=m; d++)
    if ( n1%d==0 && n2%d==0 && n3%d==0 )
      {
	found = true;
	break;
      }
  return !found;
}

// ---------------------------------------------------------------

int denom(int n, int m)
{
  if (n<0)
    n = -n;
  if (m<0)
    m = -m;

  if (n>m)
    {
      int n1=m;
      m=n;
      n=n1;
    }
  if (n==0)
    return m;
  for (int i=n; i>1; i--)
    if ( (n/i)*i==n && (m/i)*i==m )
      {
	return i;
      }
  return 1;
}

// ---------------------------------------------------------------

#ifdef __GXX_EXPERIMENTAL_CXX0X__

int denom(std::initializer_list<int> n)
{
  int d = *n.begin();
  for (std::initializer_list<int>::iterator i=n.begin()+1; i!=n.end(); i++)
    {
      d = denom(d,*i);
      if (d==1)
	return 1;
    }
  return d;
}

#else

int denom(int n1, int n2, int n3)
{
  int d = denom(n1,n2);
  if (d>1)
    d = denom(d,n3);
  return d;
}

#endif

// --------------------------------------------------------------

int commult(int n, int m)
{
  return n*m/denom(n,m);
}

// --------------------------------------------------------------

void reduce(i3d & i)
{
  //  int d = denom({i(0),i(1),i(2)});
  int d = denom(i(0),i(1));
  d = denom(d,i(2));
  i /= d;
}

// --------------------------------------------------------------
#ifdef __GXX_EXPERIMENTAL_CXX0X__
int commult(std::initializer_list<int> n)
{
  int m = *n.begin();
  for (std::initializer_list<int>::iterator i=n.begin()+1; i!=n.end(); i++)
    {
      m = commult(m,*i);
    }
  return m;
}
#endif
// --------------------------------------------------------------

void miller2pair(const i3d & nml, i3d & a, i3d & b)
{
  int perm[3];
  for (int i=0; i<3; i++)
    perm[i] = i;
  int j;

  i3d nml1 = nml, a1, b1;

  bool zero=false;
  for (j=0; j<3; j++)
    if (nml(j)==0)
      {
	zero = true;
	break;
      }
  if (zero)
    {
      int p=perm[0];
      perm[0] = perm[j];
      perm[j] = p;

      nml1(0) = nml(perm[0]);
      nml1(1) = nml(perm[1]);
      nml1(2) = nml(perm[2]);

      zero=false;
      for (j=1; j<3; j++)
	if (nml1(j)==0)
	  {
	    zero = true;
	    break;
	  }
      if (zero)
	{
	  p=perm[1];
	  perm[1] = perm[j];
	  perm[j] = p;

	  nml1(0) = nml(perm[0]);
	  nml1(1) = nml(perm[1]);
	  nml1(2) = nml(perm[2]);
	}
    }

  if ( nml1(0)==0 && nml1(1) == 0)
    {
      a1 = i3d(1,0,0);
      b1 = i3d(0,1,0);
    }
  else if (nml1(0) == 0)
    {
      a1 = i3d(1,0,0);

      b1 = i3d(0,nml1(2),-nml1(1));
    }
  else
    {
      int m = nml1(0)*nml1(1)*nml1(2);
      a1 = i3d(m/nml1(0), 0,         -m/nml1(2));
      b1 = i3d(0,         m/nml1(1), -m/nml1(2));
    }

  reduce(a1);
  reduce(b1);
  
  for (int i=0; i<3; i++)
    {
      a(perm[i]) = a1(i);
      b(perm[i]) = b1(i);
    }

  /*
  std::cout << nml << nml1 << " a= " << a << " b= " << b << " " 
	    << perm[0] << " " << perm[1] << " " << perm[2] << "\n";
  std::cout << scal(a,nml) << " " << scal(b,nml) << "\n";
  */

}

// ---------------------------------------------------------------

void match_latt(const qpp::periodic_cell<3> & cell1, const qpp::periodic_cell<3> & cell2)
{
  for (int n=1; n<N; n++)
    for (int n1 = 0; n1<=n; n1++)
      for (int n2 = n1==0 ? 0 : -n; n2<=n; n2++)
	if (n1*n1+n2*n2<=n*n)
	  for (int n3 = (n1==0 && n2==0)? 1 : -n; n3<=n; n3++)
	    if ( n1*n1+n2*n2+n3*n3<=n*n &&  n1*n1+n2*n2+n3*n3>(n-1)*(n-1)
		 && denom(n1,n2,n3)==1 )
	      {
		i3d ia1,ia2,ib1,ib2;
		miller2pair(i3d(n1,n2,n3),ia1,ib1);

		double S;
		v3d a1,a2,b1,b2;

		a1 = ia1(0)*cell1(0) + ia1(1)*cell1(1) + ia1(2)*cell1(2);
		b1 = ib1(0)*cell1(0) + ib1(1)*cell1(1) + ib1(2)*cell1(2);

		//std::cout << n1 << " " << n2 << " " << n3 << "\n";
		for (int op = 0; op<O.size(); op++)
		  {
		    i3d iia2 = O[op]*ia1;
		    i3d iib2 = O[op]*ib1;
		    a2 = iia2(0)*cell2(0) + iia2(1)*cell2(1) + iia2(2)*cell2(2);
		    b2 = iib2(0)*cell2(0) + iib2(1)*cell2(1) + iib2(2)*cell2(2);

		    v2d sig = strten(a1,b1,a2,b2) - v2d(1e0,1e0);
		    double S1 = std::sqrt(sig(0)*sig(0)+sig(1)*sig(1));

		    /*
		    std::cout << a1 << b1 << a2 << b2 << "\n";
		    std::cout << ia1 << "x" << ib1 
			      << "->" << iia2 << "x" << iib2 << " op = " << op 
			      << " sig= " << sig <<  " S= " << S1 << "\n";
		    */
		    
		    if (op==0 || S1<S)
		      {
			S = S1;
			ia2 = iia2;
			ib2 = iib2;
		      }		    
		  }
		std::cout << "[" << n1 << "," << n2 << "," << n3 << "]: " << ia1 << "x" << ib1 
			  << "->" << ia2 << "x" << ib2 << " S= " << S << "\n";
	      }
}

// -----------------------------------------------------------

int main(int argc, char **argv)
{ 

  std::string fname="";
  
  if (argc>1)
    fname = argv[1];
  
  std::istream *f;
  if (fname == "")
    f = &std::cin;
  else
    f = new std::ifstream(fname.c_str());
  
  std::vector<qpp::qpp_object*> decls;
  qpp::qpp_read(*f,decls);
  
  //  qpp::geometry<DIM> * uc=NULL;
  qpp::periodic_cell<DIM> *cell1=NULL, *cell2=NULL;
  
  for (int i=0; i<decls.size(); i++)
    if (decls[i]->gettype() & qpp::qtype_vectors)
      {
	if (cell1 == NULL)
	  cell1 = (qpp::periodic_cell<DIM>*)decls[i];
	else
	  cell2 = (qpp::periodic_cell<DIM>*)decls[i];
      }

  if (cell1==NULL || cell2==NULL)
    {
      std::cerr << "At least of two cels is not defined\n";
      exit(1);
    }

  build_O(); 
  match_latt(*cell1,*cell2);

  // for (int i=0; i<Oh.size(); i++)
  //   std::cout << i << "\n"<< Oh[i] << "\n";
  
  // qpp::init_rand(); 

}
