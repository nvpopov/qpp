  template <class FREAL>
  class qpp_shell<QBAS, FREAL> : public qpp_object{

    int _nprim, _nl;
    int * _l;
    FREAL * _alpha, * _coeff;
    STRING * _lbl;

    qpp_angtype _angtype;

    const static FREAL eps;

  public:

    qpp_shell(int __nprim, int __nl, qpp_angtype __angtype = qang_spherical, 
	      qpp_object * __owner = NULL, int __line=-1, const STRING & __file = "") :
      qpp_object("",__owner)
    {
      _nprim = __nprim;
      _nl = __nl;
      _l = new int[_nl];
      _alpha = new FREAL[_nprim];
      _coeff = new FREAL[_nprim*_nl];
      _lbl = new STRING[_nl];
      _angtype = __angtype;
      setline(__line);
      setfile(__file);
    }

    qpp_shell(const qpp_shell<QBAS,FREAL> & sh) :
      qpp_object(sh.name(),sh.owner())
    {
      _nprim = sh._nprim;
      _nl = sh._nl;
      _l = new int[_nl];
      _alpha = new FREAL[_nprim];
      _coeff = new FREAL[_nprim*_nl];
      _lbl = new STRING[_nl];
      for (int i=0; i<_nl; i++)
	{
	  _l[i] = sh._l[i];
	  _lbl[i] = sh._lbl[i];
	}
      for (int i=0; i<_nprim; i++)
	_alpha[i] = sh._alpha[i];
      for (int i=0; i<_nprim*_nl; i++)
	_coeff[i] = sh._coeff[i];
      _angtype = sh._angtype;

      setline(sh.line());
      setfile(sh.file());
    }

    ~qpp_shell()
    {
      delete _l;
      delete _alpha;
      delete _coeff;
    }

    inline int nprim() const
    { return _nprim; }

    inline int nshells() const
    { return _nl; }

    inline STRING & label(int i)
    { return _lbl[i]; }

    inline STRING label(int i) const
    { return _lbl[i]; }

    inline int & l(int i)
    { return _l[i]; }

    inline int l(int i) const
    { return _l[i]; }

    inline FREAL & alpha(int i)
    { return _alpha[i]; }

    inline FREAL alpha(int i) const
    { return _alpha[i]; }

    inline FREAL & coeff(int i, int j)
    { return _coeff[i*_nprim+j]; }

    inline FREAL coeff(int i, int j) const
    { return _coeff[i*_nprim+j]; }

    qpp_angtype & angtype()
    { return _angtype; }

    qpp_angtype angtype() const
    { return _angtype; }

    inline bool operator==(const qpp_shell<QBAS,FREAL> & sh) const
    {
      if (_nl != sh._nl || _nprim != sh._nprim)
	return false;
      for (int i=0; i<_nl; i++)
	if (_l[i] != sh._l[i])
	  return false;
      for (int i=0; i<_nprim; i++)
	if ( std::abs(_alpha[i] - sh._alpha[i]) > eps )
	  return false;
      for (int i=0; i<_nprim*_nl; i++)
	if ( std::abs(_coeff[i] - sh._coeff[i]) > eps )
	  return false;

      return true;
    }

    bool same_alpha(const qpp_shell<QBAS,FREAL> & sh) const
    {
      if (_nprim != sh._nprim)
	return false;
      for (int i=0; i<_nprim; i++)
	if ( std::abs(_alpha[i] - sh._alpha[i]) > eps )
	  return false;

      return true;
    }

    void merge(const qpp_shell<QBAS,FREAL> & sh)
    {
      int * new_l = new int[nshells()+sh.nshells()];
      for (int i=0; i<nshells(); i++)
	new_l[i] = _l[i];
      for (int i=0; i<sh.nshells(); i++)
	new_l[i+nshells()] = sh._l[i];

      FREAL * new_coeff = new FREAL[nprim()*(nshells()+sh.nshells())];
      for (int p=0; p<nprim(); p++)
	{
	  for (int i=0; i<nshells(); i++)
	    new_coeff[i*nprim()+p] = _coeff[i*nprim()+p];
	  for (int i=0; i<sh.nshells(); i++)
	    new_coeff[(i+nshells())*nprim()+p] = sh._coeff[i*nprim()+p];
	}
      
      delete _coeff;
      delete _l;
      _coeff = new_coeff;
      _l = new_l;

      _nl = nshells() + sh.nshells();
    }

    virtual void write_g98(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int i=0; i<nshells(); i++)
	{
	  for (int f=0; f<offset; f++) os << " ";
	  if (l(i)==0)
	    os << "S";
	  else if (l(i)==1)
	    os << "P";
	  else if (l(i)==2)
	    os << "D";
	  else if (l(i)==3)
	    os << "F";
	  else if (l(i)==4)
	    os << "G";	  
	  os << "  " << nprim() << "  1.00\n";
	  for (int p=0; p<nprim(); p++)
	    {
	      for (int f=0; f<offset; f++) os << " ";
	      os << boost::format("%15.6f %15.6f\n") % alpha(p) % coeff(i,p);
	    }
	}      
    }

    virtual STRING category() const
    {
      return "shell";
    }

    virtual qppobject_type gettype() const
    {
      return qtype_shell | qtype_basis_gauss | qtype_data<FREAL>::type; 
    }

    virtual int n_nested() const
    {
      return 0;
    }

    virtual qpp_object* nested(int i) const
    {
      return NULL;
    }

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "shell(bastype=gaussian, angtype=";
      if (_angtype == qang_spherical)
	os << "spherical";
      else if (_angtype == qang_cartesian)
	os << "cartesian";
      for (int i=0; i<nshells(); i++)
	{
	  os << ", ";
	  if (label(i) != "")
	    os << label(i) << "=";
	  os << l(i);
	}
      os << "){\n";

      for (int i=0; i<nprim(); i++)
	{
	  for (int k=0; k<offset+2; k++) os << " "; 
	  os << boost::format("%15.8e ") % alpha(i);
	  for (int j=0; j<nshells(); j++)
	    os << boost::format("%10.6f ") % coeff(j,i);
	  os << "\n";
	}
      for (int k=0; k<offset; k++) os << " ";
      os << "}\n";
    }
    
    virtual qpp_object * copy() const
    {
      return new qpp_shell<QBAS,FREAL>(*this);
    }

  };

  template <class FREAL>
  const FREAL qpp_shell<QBAS,FREAL>::eps = 1e-7;
