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
#include <HRRPart0bra0ket0fp.h>
#include <HRRPart1bra0ket0fd.h>
#include <HRRPart1bra0ket0fp.h>
#include <HRRPart1bra0ket0gp.h>
#include <_aB_F__0__F__1___TwoPRep_P__0__D__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_F__0__F__1___TwoPRep_P__0__D__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,1150)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_F__0__F__1___TwoPRep_P__0__D__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*300+2950)*1+lsi)*1]), &(inteval->stack[((hsi*150+900)*1+lsi)*1]), &(inteval->stack[((hsi*100+1050)*1+lsi)*1]),10);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*450+3250)*1+lsi)*1]), &(inteval->stack[((hsi*210+690)*1+lsi)*1]), &(inteval->stack[((hsi*150+900)*1+lsi)*1]),10);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*600+3700)*1+lsi)*1]), &(inteval->stack[((hsi*450+3250)*1+lsi)*1]), &(inteval->stack[((hsi*300+2950)*1+lsi)*1]),10);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*450+2950)*1+lsi)*1]), &(inteval->stack[((hsi*225+315)*1+lsi)*1]), &(inteval->stack[((hsi*150+540)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+4300)*1+lsi)*1]), &(inteval->stack[((hsi*315+0)*1+lsi)*1]), &(inteval->stack[((hsi*225+315)*1+lsi)*1]),15);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*900+0)*1+lsi)*1]), &(inteval->stack[((hsi*675+4300)*1+lsi)*1]), &(inteval->stack[((hsi*450+2950)*1+lsi)*1]),15);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*1800+1150)*1+lsi)*1]), &(inteval->stack[((hsi*900+0)*1+lsi)*1]), &(inteval->stack[((hsi*600+3700)*1+lsi)*1]),60);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*1800+1150)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
