template <class FREAL>
class qpp_shell<QBAS, FREAL> { //: public qpp_object{

  int _nprim, _nl;
  int * _l;
  FREAL * _alpha, * _coeff;
  STRING_EX * _lbl;

  qpp_angtype _angtype;
  const static FREAL eps;

  void init_props(){
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    py_label.bind(this);
    py_l.bind(this);
    py_alpha.bind(this);
    py_coeff.bind(this);
#endif
  }

public:

  qpp_shell(int __nprim, int __nl, qpp_angtype __angtype = qang_spherical){
    _nprim = __nprim;
    _nl = __nl;
    _l = new int[_nl];
    _alpha = new FREAL[_nprim];
    _coeff = new FREAL[_nprim*_nl];
    _lbl = new STRING_EX[_nl];
    _angtype = __angtype;
    init_props();
  }

  qpp_shell(const qpp_shell<QBAS,FREAL> & sh){
    //qpp_object(sh.name(),sh.owner())
    _nprim = sh._nprim;
    _nl = sh._nl;
    _l = new int[_nl];
    _alpha = new FREAL[_nprim];
    _coeff = new FREAL[_nprim*_nl];
    _lbl = new STRING_EX[_nl];
    for (int i=0; i<_nl; i++){
        _l[i] = sh._l[i];
        _lbl[i] = sh._lbl[i];
      }
    for (int i=0; i<_nprim; i++)
      _alpha[i] = sh._alpha[i];
    for (int i=0; i<_nprim*_nl; i++)
      _coeff[i] = sh._coeff[i];
    _angtype = sh._angtype;
    init_props();

  }

  ~qpp_shell(){
    delete _l;
    delete _alpha;
    delete _coeff;
  }

  inline int nprim() const
  { return _nprim; }

  inline int nshells() const
  { return _nl; }

  inline STRING_EX & label(int i)
  { return _lbl[i]; }

  inline STRING_EX label(int i) const
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
  { return _coeff[i+j*_nprim]; }

  inline FREAL coeff(int i, int j) const
  { return _coeff[i+j*_nprim]; }

  qpp_angtype & angtype()
  { return _angtype; }

  qpp_angtype angtype() const
  { return _angtype; }

  inline bool operator==(const qpp_shell<QBAS,FREAL> & sh) const{
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

  bool same_alpha(const qpp_shell<QBAS,FREAL> & sh) const{
    if (_nprim != sh._nprim)
      return false;
    for (int i=0; i<_nprim; i++)
      if ( std::abs(_alpha[i] - sh._alpha[i]) > eps )
        return false;

    return true;
  }

  void merge(const qpp_shell<QBAS,FREAL> & sh){
    int * new_l = new int[nshells()+sh.nshells()];
    for (int i=0; i<nshells(); i++)
      new_l[i] = _l[i];
    for (int i=0; i<sh.nshells(); i++)
      new_l[i+nshells()] = sh._l[i];

    FREAL * new_coeff = new FREAL[nprim()*(nshells()+sh.nshells())];
    for (int p=0; p<nprim(); p++){
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

  virtual void write_g98(std::basic_ostream<CHAR_EX,TRAITS> &os,
                         int offset=0) const{
    for (int i=0; i<nshells(); i++){
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
        for (int p=0; p<nprim(); p++){
            for (int f=0; f<offset; f++) os << " ";
            os << fmt::format("{:15.6f} {:15.6f}\n", alpha(p), coeff(p,i));
          }
      }
  }

  /*
    virtual STRING_EX category() const
    {
      return "shell";
    }

    virtual qppobject_type gettype() const
    {
      return qtype_shell | qtype_basis_gauss | qtype_data<FREAL>::type;
    }

    virtual int n_nested() const
    {
      return _parm->n_nested();
    }

    virtual int n_param() const
    {
      return _parm->n_nested();
    }

    virtual void set_n_param(int n)
    {
      // fixme - generate exception
    }

    virtual qpp_object* nested(int i) const
    {
      return _parm->nested(i);
    }
*/
  virtual void write(OSTREAM &os, int offset=0) const{
    for (int k=0; k<offset; k++) os << " ";
    os << "shell(bastype=gaussian, angtype=";
    if (_angtype == qang_spherical)
      os << "spherical";
    else if (_angtype == qang_cartesian)
      os << "cartesian";
    for (int i=0; i<nshells(); i++){
        os << ", ";
        if (label(i) != "")
          os << label(i) << "=";
        os << l(i);
      }
    os << "){\n";

    for (int i=0; i<nprim(); i++){
        for (int k=0; k<offset+2; k++) os << " ";
        os << fmt::format("{:15.8f} ",alpha(i));
        for (int j=0; j<nshells(); j++)
          os << fmt::format("{:10.6f} ", coeff(i,j));
        os << "\n";
      }
    for (int k=0; k<offset; k++) os << " ";
    os << "}\n";
  }

  /*
    virtual qpp_object * copy() const
    {
      return new qpp_shell<QBAS,FREAL>(*this);
      }*/

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  typedef qpp_shell<QBAS,FREAL> SELF;

  inline void py_set_label(int i, const STRING_EX & l)
  { _lbl[i]=l; }

  inline STRING_EX py_get_label(int i)
  { return _lbl[i]; }

  inline int py_get_l(int i)
  { return _l[i]; }

  inline void py_set_l(int i, const int & l)
  { _l[i] = l; }

  inline FREAL py_get_alpha(int i)
  { return _alpha[i]; }

  inline void py_set_alpha(int i, const FREAL & a)
  { _alpha[i]=a; }

  inline FREAL py_get_coeff(int i, int j)
  { return _coeff[i+j*_nprim]; }

  inline void py_set_coeff(int i, int j, const FREAL & c)
  { _coeff[i+j*_nprim] = c; }

  inline FREAL py_get_coeff1(int i)
  { TypeError("Contraction coefficient needs 2 indicies"); }

  inline void py_set_coeff1(int i, const FREAL & c)
  { TypeError("Contraction coefficient needs 2 indicies"); }

  py_indexed_property< SELF, STRING_EX, int,
                      &SELF::py_get_label, &SELF::py_set_label> py_label;

  py_indexed_property< SELF, int, int,
                      &SELF::py_get_l, &SELF::py_set_l> py_l;

  py_indexed_property< SELF, FREAL, int,
                      &SELF::py_get_alpha, &SELF::py_set_alpha> py_alpha;

  py_2indexed_property<SELF, FREAL, FREAL, int,
                      &SELF::py_get_coeff1, &SELF::py_set_coeff1,
                      &SELF::py_get_coeff, &SELF::py_set_coeff > py_coeff;

  static void py_props(py::module m, const char * pyname){

    std::string sPropNameLabel =
         fmt::format("{0}_{1}",pyname,"idx_prop_label");
    py_indexed_property< SELF, STRING_EX, int,
        &SELF::py_get_label, &SELF::py_set_label>::py_export(
          m, sPropNameLabel.c_str());

    std::string sPropNameL =
         fmt::format("{0}_{1}",pyname,"idx_prop_l");
    py_indexed_property< SELF, int, int,
        &SELF::py_get_l, &SELF::py_set_l>::py_export(m, sPropNameL.c_str());

    std::string sPropNameAlpha =
         fmt::format("{0}_{1}",pyname,"idx_prop_alpha");
    py_indexed_property< SELF, FREAL, int,
        &SELF::py_get_alpha, &SELF::py_set_alpha>::py_export(
          m, sPropNameAlpha.c_str());

    std::string sPropNameCoeff =
         fmt::format("{0}_{1}",pyname,"idx_prop_coeff");
    py_2indexed_property<SELF, FREAL, FREAL, int,
        &SELF::py_get_coeff1, &SELF::py_set_coeff1,
        &SELF::py_get_coeff, &SELF::py_set_coeff >::py_2export(
          m, sPropNameCoeff.c_str());
  }

#endif

};

template <class FREAL>
const FREAL qpp_shell<QBAS,FREAL>::eps = 1e-8;
