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
#include <HRRPart0bra0ket0dd.h>
#include <HRRPart0bra0ket0dp.h>
#include <HRRPart0bra0ket0fp.h>
#include <HRRPart1bra0ket0gp.h>
#include <_aB_D__0__G__1___TwoPRep_D__0__P__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_D__0__G__1___TwoPRep_D__0__P__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,1116)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_D__0__G__1___TwoPRep_D__0__P__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart0bra0ket0dp(inteval, &(inteval->stack[((hsi*270+2736)*1+lsi)*1]), &(inteval->stack[((hsi*150+876)*1+lsi)*1]), &(inteval->stack[((hsi*90+1026)*1+lsi)*1]),15);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*450+3006)*1+lsi)*1]), &(inteval->stack[((hsi*225+651)*1+lsi)*1]), &(inteval->stack[((hsi*150+876)*1+lsi)*1]),15);
HRRPart0bra0ket0dd(inteval, &(inteval->stack[((hsi*540+3456)*1+lsi)*1]), &(inteval->stack[((hsi*450+3006)*1+lsi)*1]), &(inteval->stack[((hsi*270+2736)*1+lsi)*1]),15);
HRRPart0bra0ket0dp(inteval, &(inteval->stack[((hsi*378+2736)*1+lsi)*1]), &(inteval->stack[((hsi*210+315)*1+lsi)*1]), &(inteval->stack[((hsi*126+525)*1+lsi)*1]),21);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*630+3996)*1+lsi)*1]), &(inteval->stack[((hsi*315+0)*1+lsi)*1]), &(inteval->stack[((hsi*210+315)*1+lsi)*1]),21);
HRRPart0bra0ket0dd(inteval, &(inteval->stack[((hsi*756+0)*1+lsi)*1]), &(inteval->stack[((hsi*630+3996)*1+lsi)*1]), &(inteval->stack[((hsi*378+2736)*1+lsi)*1]),21);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1620+1116)*1+lsi)*1]), &(inteval->stack[((hsi*756+0)*1+lsi)*1]), &(inteval->stack[((hsi*540+3456)*1+lsi)*1]),36);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*1620+1116)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
