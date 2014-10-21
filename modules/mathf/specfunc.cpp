#include <mathf/specfunc.hpp>
#include <cmath>

namespace qpp{

double logfact(int n)
// returns ln(n!)
{
	double f = 0e0;
	for (int k = 1; k<=n; k++)
		f += std::log(1e0*k);
	return f;
}

double atanxy(double x, double y)
{
	// returns the polar angle for the (x,y) direction
	const double eps=1e-8;
	double phi;

	if ( std::abs(x) <= eps )
	{
		phi = pi/2;
		if ( y < 0 )
			phi += pi;
	}
	else
	{
		phi = std::atan(y/x);
		if ( x  < 0 )
			phi += pi;
	}
	return phi;
}

void Pl_legendre(double x, int l, std::vector<double> &Pl)
{
	Pl.at(0) = 1e0;

	double pl_prev = 1e0, pl = x;
	double pl_next;

	for (int k = 1; k<=l; k++)
	{
		Pl.at(k) = pl;

		pl_next = pl*x*(2*k + 1)/(k + 1) - pl_prev*k/(k+1);
		pl_prev = pl;
		pl = pl_next;
	}

}

void Pn_Jacobi(double x, double alpha, int n, std::vector<double> &Pn)
{
	double p, p_1, p_2;

	Pn.at(0) = p_2 = 1e0;

	if (n>=1)
		Pn.at(1) =  p_1 = (alpha + 1e0)*(1e0 - 2*x);

	for (int k = 2; k <= n; k++)
	{
		p = (alpha + k -.5e0)*(1e0 - 2*x)*p_1 - .5e0*(alpha + k - 1e0)*p_2;
		p *= 2*(alpha+k)/((2*alpha+k)*k);

		Pn.at(k) = p;

		p_2 = p_1;
		p_1 = p;
	}
}

void Pn_laguerre(double x, double alpha, int n, std::vector<double> &Pn)
{
	double p, p_1, p_2;

	Pn.at(0) = p_2 = 1e0;

	if (n>=1)
		Pn.at(1) =  p_1 = alpha + 1e0 - x;

	for (int k = 2; k <= n; k++)
	{
		p = -( (x-alpha-2*k+1)*p_1 + (alpha+k-1)*p_2 )/k;

		Pn.at(k) = p;

		p_2 = p_1;
		p_1 = p;
	}
}

double efrc(double x)
{
	double z = (x>0) ? x : -x;
	double t = 1e0/(1 + .5e0*z);

	double erfcc = t*std::exp( -z*z - 1.26551223 +
							   t*(1.00002368 +
								   t*(.37409196
									   +t*(.09678418
											+t*(-.18628806+
												t*(.27886807 +
												   t*(-1.13520398+
													  t*( 1.48851587
														  +t*( -.82215223 + t*.17087277)))))))));

	if (x<0)
		return 2e0 - erfcc;
	else
		return erfcc;
}

double erf(double x)
{
	return 1e0 - erfc(x);
}

void Fn_boys(double x, int n, std::vector<double> &Fn)
{
	double sx = std::sqrt(x);
	double ex = std::exp(-x);

	Fn.at(0) = erf(sx)/sx;
	double hspi = std::sqrt(pi)/2;
	for (int k=0; k<n; k++)
		Fn.at(k+1) = ( (2*k+1)*Fn.at(k) - ex/hspi )/(2*x);
}

double I0_bessel(double x, double predexp)
{
	const double
			p1 = 1.0e0,
			p2 = 3.5156229e0,
			p3 = 3.0899424e0,
			p4 = 1.2067492e0,
			p5 = 0.2659732e0,
			p6 = 0.360768e-1,
			p7 = 0.45813e-2,
			q1 = 0.39894228e0,
			q2 = 0.1328592e-1,
			q3 = 0.225319e-2,
			q4 = -0.157565e-2,
			q5 = 0.916281e-2,
			q6 = -0.2057706e-1,
			q7 = 0.2635537e-1,
			q8 = -0.1647633e-1,
			q9 = 0.392377e-2;

	double absx = std::abs(x);
	if ( absx < 3.75e0 )
	{
		double xx = x/3.75e0;
		xx *= xx;

		return ( p1 + xx*(p2 + xx*(p3 + xx*(p4 + xx*(p5 + xx*(p6 + xx*p7))))) )*std::exp(predexp);
	}
	else
	{
		double xx = 3.75/absx;
		return (std::exp(predexp+absx)/std::sqrt(absx))*(q1 + xx*(q2 + xx*(q3 + xx*(q4 +
																					xx*(q5 + xx*(q6 + xx*(q7 + xx*(q8 + xx*q9))))))));
	}
}

void In_bessel(int n, double x, std::vector<double> &In, double predexp)
{
	double I0 = I0_bessel(x, predexp);
	double tx = 2e0/x;

	double big = 1e10, small = 1e-10;
	double bi = 1e0, bip=0e0, bim;

	double accrcy = 40e0;
	int nstart = 2*( ( n + (int)std::sqrt(accrcy*n) )/2 );

	for ( int j = nstart; j>0; j-- )
	{
		bim = bip + j * tx * bi;
		bip = bi;
		bi = bim;

		if (j<=n+1) In.at(j-1) = bi;

		if ( bi > big )
		{
			bi  *= small;
			bip *= small;

			for (int i=j-1; i<=n; i++) In.at(i) *= small;
		}
	}

	for (int i=0; i<=n; i++) In.at(i) *= I0/bi;
}

void Qml_legendre(int l, int m, double x, std::vector<double> &Qml)

{
	int n = l - m;
	double Cmm = 1e0;
	double sin2 = 1e0 - x*x;
	for (int i=1; i<=m; i++)
		Cmm *= sin2*(1 - .5e0/i);
	Cmm = std::sqrt(Cmm);

	if ( int(m/2)*2 != m ) Cmm = -Cmm;

	Qml.at(0)=Cmm;

	if ( n>0 ) Qml.at(1) = std::sqrt(2*m+1)*x*Qml.at(0);

	for (int i=2; i<=n; i++ )
	{
		int ll = m+i;
		Qml.at(i) = (2*ll-1)*x*Qml.at(i-1) - std::sqrt( (ll-1)*(ll-1e0) - m*m )*Qml.at(i-2);
		Qml.at(i) /= std::sqrt(ll*ll - m*m);
	}
}

double Ylm_spherical(int l, int m, double theta)
{
	std::vector<double> Q(l-m+1);
	int sgn = 1;
	if (m<0 && 2*int(m/2)!=m ) sgn = -1;
	if (m<0) m = -m;
	Qml_legendre(l,m,std::cos(theta),Q);
	return  sgn*std::sqrt((2*l+1)/(4*pi))*Q.at(l-m);
}

double djmk_wigner(int J, int M, int K, double beta)
{
	// fixme - inefficient implementation
	// It's better to use recurrence relations
	/*  */  int sgn = 1;
	double pi=std::atan(1.)*4;

	if ((beta<=pi/2))//||(beta>=pi))
	{
		beta=pi-beta;
		if((J+M)%2==1){sgn*=(-1);};
		K = -K;
	};
	if (M+K<0)
	{
		int tmp = M;
		M = -K;
		K = -tmp;
	};
	if (K>M)
	{
		sgn *= ((K-M)%2 == 1)? -1 : 1;
		int tmp = K;
		K = M;
		M = tmp;
	};

	/// Calculating prefactor

	/*  */  int f1 = 1;
	if ( (J-K)%2 == 1 ) {f1 = -1;};

	/*  */  double f2 = 0e0;
	///-
	for(int i = J-M+1;i<=J+M; i++)
	{
		f2 += std::log( (double)i );
	};
	f2 *= 0.5e0;

	/*  */  double f3=0e0;
	for(int i = J-abs(K)+1; i<=J+abs(K); i++)
	{
		f3 += std::log( (double)i );
	};

	f3 *= 0.5e0;

	if(K<0) f3 = -f3;

	/*  */  double fmk=0e0;
	for(int i = 1; i<=M+K; i++)
	{
		fmk += std::log( (double)i );
	};

	double beta2=beta/2;
	double Sin = std::sin(beta2);
	double Sin2J = std::pow(Sin, 2*J );
	double CTan = std::cos(beta2)/Sin;
	double CTan2 = CTan*CTan;
	double CTanMK = std::pow(CTan, M+K );

	double Prefac = sgn*Sin2J*CTanMK*f1*std::exp(f2+f3-fmk);

	double sum = 1e0, g = 1e0;


	for(int i = 0; i < J-M; i++)
	{

		g *= -CTan2*(J-M-i)*(J-K-i)/((i+1)*(M+K+i+1));


		sum += g;
	};


	return Prefac*sum;

}


};

