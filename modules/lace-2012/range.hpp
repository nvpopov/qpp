#ifndef _LACE_RANGE_H
#define _LACE_RANGE_H

#include<lace-2012/expressions.hpp>

namespace _lace_expressions{

  struct sub{
    int i1,i2,inc;

    sub(){}

    sub(int _i1, int _i2, int _inc = 1)
    {
      assert( _inc > 0 && " Increment <= 0 is not allowed in subranges ");
      i1 = _i1; i2 = _i2; inc = _inc;
    }

    inline int idx(int i)
    {
      return i1 + i*inc;
    }

    inline int begin(){return i1;}

    inline int end(){return i2;}

    inline int size()
    {
      return i2>=i1 ? (i2-i1)/inc+1 : 0;
    }

    inline bool operator==(sub &I)
    {
      return i1==I.i1 && i2==I.i2 && inc==I.inc;
    }

    inline void reduce(int b1, int b2)
    {
      if (i1==-1) i1 = b1;
      if (i2==-1) i2 = b2 - 1;

      if (i2 >= b2) i2 = b2 - 1;
      if (i1 < b1 )
	i1 += inc*( (b1 - i1)/inc + 1 );
    }

    static sub full;

    //------
    void debug()
    {
      std::cout << " " << i1 << ":" << i2 << "%" << inc << " ";
    }

  };

  inline sub operator|(sub I, int i2)
  {
    return sub(I.i1, i2, I.inc);
  }

  inline sub operator|(int i1, sub I)
  {
    return sub(i1, I.i2, I.inc);
  }

  inline sub sub_of_sub( sub I1, sub I2)
  // returns the subrange for expression like
  // 
  //  X(I1)(I2)
  {
    int i1 = I1.idx(I2.i1);
    int inc = I1.inc * I2.inc;
    int i2 = I1.idx(I2.i2);
    if (i2 > I1.i2)
      i2 = I1.i2;
    return sub(i1,i2,inc);
  }

  class subrange_expression : public abstract_expression{
  
    sub I;    

  public:
    typedef expression_literal<char,subrange_expression> literal;
    
    subrange_expression() : I(-1,-1,1){}

    subrange_expression(sub _I) : I(_I){}

    subrange_expression(int _i1, int _i2, int _inc = 1) : I(_i1,_i2,_inc){}
    
    virtual int gettype(){return _range + _actual;}

    virtual int basetype(){return _range;}
    
    virtual bool equiv(tree_node *tree)
    {
      bool res = tree == NULL ? false : tree -> gettype() == gettype() && tree -> nnext() ==nnext();

      if (res)
	res = I == ((subrange_expression*)tree) -> I;
      return res;
    }

    sub rng(){return I;}
    
    //debug--------
    virtual void print_tree(int shift = 0){ print_me(shift);}
    
    virtual void print_me(int shift = 0)
    {
      if (shift==0)
	std::cout << " " << I.i1 << ":" << I.i2 << "%" << I.inc << " ";
      else
	{
	  indent(shift);
	  std::cout << " subrange " << I.i1 << ":" << I.i2 << "%" << I.inc << " UID = " <<  getUID() 
		    << " nref = " << nref << " nbound = " <<   nbound << "\n";
	}
    }

    virtual void free(){delete (subrange_expression*)this;}
    
    ~subrange_expression(){}
    
    virtual bool match(abstract_expression *xpr)
    {
      if (equiv(xpr))
	{
	  ((subrange_expression*)this) -> bind(xpr);
	  return true;
	}
      else 
	{
	  return false;
	}
    }
        
    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & _actual) == 0 )
	return new subrange_expression(I);
      else
	return this;
    }  

    //    virtual void calculate_expr(XPR* &target, VALTYPE scale = VALTYPE(1e0) )

  };
  
};

#endif
