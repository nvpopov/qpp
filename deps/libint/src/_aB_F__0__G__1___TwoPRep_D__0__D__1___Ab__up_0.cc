/*
 *  Copyright (C) 2004-2017 Edward F. Valeev
 *
 *  This file is part of Libint.
 *
 *  Libint is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libint is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Libint.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <libint2.h>
#include <HRRPart0bra0ket0fd.h>
#include <HRRPart0bra0ket0fp.h>
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hp.h>
#include <_aB_F__0__G__1___TwoPRep_D__0__D__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_F__0__G__1___TwoPRep_D__0__D__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,2944)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_F__0__G__1___TwoPRep_D__0__D__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*630+8344)*1+lsi)*1]), &(inteval->stack[((hsi*315+1729)*1+lsi)*1]), &(inteval->stack[((hsi*210+2044)*1+lsi)*1]),21);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*945+8974)*1+lsi)*1]), &(inteval->stack[((hsi*441+1288)*1+lsi)*1]), &(inteval->stack[((hsi*315+1729)*1+lsi)*1]),21);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*1260+9919)*1+lsi)*1]), &(inteval->stack[((hsi*945+8974)*1+lsi)*1]), &(inteval->stack[((hsi*630+8344)*1+lsi)*1]),21);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*450+8344)*1+lsi)*1]), &(inteval->stack[((hsi*225+2569)*1+lsi)*1]), &(inteval->stack[((hsi*150+2794)*1+lsi)*1]),15);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*675+8794)*1+lsi)*1]), &(inteval->stack[((hsi*315+2254)*1+lsi)*1]), &(inteval->stack[((hsi*225+2569)*1+lsi)*1]),15);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*900+1288)*1+lsi)*1]), &(inteval->stack[((hsi*675+8794)*1+lsi)*1]), &(inteval->stack[((hsi*450+8344)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*2700+11179)*1+lsi)*1]), &(inteval->stack[((hsi*1260+9919)*1+lsi)*1]), &(inteval->stack[((hsi*900+1288)*1+lsi)*1]),60);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*840+1288)*1+lsi)*1]), &(inteval->stack[((hsi*420+588)*1+lsi)*1]), &(inteval->stack[((hsi*280+1008)*1+lsi)*1]),28);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+8344)*1+lsi)*1]), &(inteval->stack[((hsi*588+0)*1+lsi)*1]), &(inteval->stack[((hsi*420+588)*1+lsi)*1]),28);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*1680+13879)*1+lsi)*1]), &(inteval->stack[((hsi*1260+8344)*1+lsi)*1]), &(inteval->stack[((hsi*840+1288)*1+lsi)*1]),28);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*3780+15559)*1+lsi)*1]), &(inteval->stack[((hsi*1680+13879)*1+lsi)*1]), &(inteval->stack[((hsi*1260+9919)*1+lsi)*1]),60);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*5400+2944)*1+lsi)*1]), &(inteval->stack[((hsi*3780+15559)*1+lsi)*1]), &(inteval->stack[((hsi*2700+11179)*1+lsi)*1]),60);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*5400+2944)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
