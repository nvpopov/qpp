
namespace lace{

  class complex{

    REAL _re,_im;

  public:

    inline REAL re(){return _re;}
    
    inline REAL im(){return _im;}

    complex( REAL __re = REAL(), REAL __im = REAL()) : _re(__re), _im(__im) {}
    
//     complex( altcomplex1  z );

//     complex( altcomplex2  z );

    inline bool operator==(complex z){return (_re == z._re) && (_im == z._im); }

    inline bool operator!=(complex z){return (_re != z._re) || (_im != z._im); }

    inline complex& operator+=(complex z)
    {
      _re += z._re;
      _im += z._im;
      return *this;
    }

    inline complex& operator-=(complex z)
    {
      _re -= z._re;
      _im -= z._im;
      return *this;
    }

    inline complex& operator*=(complex z)
    {
      REAL tmp = _re * z._re - _im * z._im;
      _im = _im * z._re + _re * z._im;
      _re = tmp;
      return *this;
    }

    inline complex& operator/=(REAL a)
    {
      _re /= a;
      _im /= a;
      return *this;
    }

  };

  inline REAL norm2(complex a)
  {
    return a.re()*a.re() + a.im()*a.im();
  }

  inline REAL abs(complex a)
  {
    return std::sqrt(norm2(a));
  }

  inline complex conj(complex a)
  {
    return complex( a.re(), -a.im() );
  }

  inline complex polar( REAL rho, REAL phi )
  {
    return complex( rho*std::cos(phi), rho*std::sin(phi) );
  }

  inline complex operator+(complex a, complex b)
  {
    return complex( a.re() + b.re(), a.im() + b.im() );
  }

  inline complex operator-(complex a, complex b)
  {
    return complex( a.re() - b.re(), a.im() - b.im() );
  }

  inline complex operator-(complex a)
  {
    return complex( - a.re(), - a.im() );
  }

  inline complex operator*(complex a, complex b)
  {
    return complex( a.re()*b.re() - a.im()*b.im() , 
		    a.im()*b.re() + a.re()*b.im() );
  }
  
  inline complex operator*(REAL a, complex b)
  {
    return complex( a*b.re(), a*b.im() );
  }
  
  inline complex operator/(complex a, REAL b)
  {
    return complex( a.re()/b, a.im()/b );
  }

  inline complex operator/(complex a, complex b)
  {
    REAL denom = norm2(b);
    return complex( (a.re()*b.re() + a.im()*b.im())/denom , 
		    (a.im()*b.re() - a.re()*b.im())/denom );
  }

  inline REAL arg(complex a)
  {
    return atan2(a.im(),a.re());
  }

  inline complex exp(complex a)
  {
    return polar( std::exp(a.re()), a.im() );
  }

  inline complex log(complex a)
  {
    return complex( std::log(abs(a)), arg(a) );
  }

  inline complex sqrt(complex a)
  {
    return polar( std::sqrt( abs(a) ), arg(a)/REAL(2) );
  }

  inline REAL real(complex a)
  {
    return a.re();
  }

  template<typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, complex z)
  {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    if ( z.im() >= REAL() )
      __s << z.re() << "+i*" << z.im() ;
    else
      __s << z.re() << "-i*" << (-z.im()) ;
    return __os << __s.str();
  }

};


