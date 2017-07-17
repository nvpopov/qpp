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
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart1bra0ket0fd.h>
#include <HRRPart1bra0ket0fp.h>
#include <HRRPart1bra0ket0gp.h>
#include <_aB_G__0__F__1___TwoPRep_P__0__D__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_G__0__F__1___TwoPRep_P__0__D__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,1656)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_G__0__F__1___TwoPRep_P__0__D__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*450+4356)*1+lsi)*1]), &(inteval->stack[((hsi*225+1281)*1+lsi)*1]), &(inteval->stack[((hsi*150+1506)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+4806)*1+lsi)*1]), &(inteval->stack[((hsi*315+966)*1+lsi)*1]), &(inteval->stack[((hsi*225+1281)*1+lsi)*1]),15);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*900+5481)*1+lsi)*1]), &(inteval->stack[((hsi*675+4806)*1+lsi)*1]), &(inteval->stack[((hsi*450+4356)*1+lsi)*1]),15);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*630+4356)*1+lsi)*1]), &(inteval->stack[((hsi*315+441)*1+lsi)*1]), &(inteval->stack[((hsi*210+756)*1+lsi)*1]),21);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*945+6381)*1+lsi)*1]), &(inteval->stack[((hsi*441+0)*1+lsi)*1]), &(inteval->stack[((hsi*315+441)*1+lsi)*1]),21);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*1260+0)*1+lsi)*1]), &(inteval->stack[((hsi*945+6381)*1+lsi)*1]), &(inteval->stack[((hsi*630+4356)*1+lsi)*1]),21);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*2700+1656)*1+lsi)*1]), &(inteval->stack[((hsi*1260+0)*1+lsi)*1]), &(inteval->stack[((hsi*900+5481)*1+lsi)*1]),60);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*2700+1656)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
