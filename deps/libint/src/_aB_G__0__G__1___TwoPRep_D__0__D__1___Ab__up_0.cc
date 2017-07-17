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
#include <HRRPart0bra0ket0gd.h>
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart0bra0ket0hp.h>
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hp.h>
#include <_aB_G__0__G__1___TwoPRep_D__0__D__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_G__0__G__1___TwoPRep_D__0__D__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,4096)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_G__0__G__1___TwoPRep_D__0__D__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*945+12196)*1+lsi)*1]), &(inteval->stack[((hsi*441+2380)*1+lsi)*1]), &(inteval->stack[((hsi*315+2821)*1+lsi)*1]),21);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1323+13141)*1+lsi)*1]), &(inteval->stack[((hsi*588+1792)*1+lsi)*1]), &(inteval->stack[((hsi*441+2380)*1+lsi)*1]),21);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1890+14464)*1+lsi)*1]), &(inteval->stack[((hsi*1323+13141)*1+lsi)*1]), &(inteval->stack[((hsi*945+12196)*1+lsi)*1]),21);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+12196)*1+lsi)*1]), &(inteval->stack[((hsi*315+3556)*1+lsi)*1]), &(inteval->stack[((hsi*225+3871)*1+lsi)*1]),15);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*945+12871)*1+lsi)*1]), &(inteval->stack[((hsi*420+3136)*1+lsi)*1]), &(inteval->stack[((hsi*315+3556)*1+lsi)*1]),15);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1350+1792)*1+lsi)*1]), &(inteval->stack[((hsi*945+12871)*1+lsi)*1]), &(inteval->stack[((hsi*675+12196)*1+lsi)*1]),15);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*4050+16354)*1+lsi)*1]), &(inteval->stack[((hsi*1890+14464)*1+lsi)*1]), &(inteval->stack[((hsi*1350+1792)*1+lsi)*1]),90);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+1792)*1+lsi)*1]), &(inteval->stack[((hsi*588+784)*1+lsi)*1]), &(inteval->stack[((hsi*420+1372)*1+lsi)*1]),28);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1764+12196)*1+lsi)*1]), &(inteval->stack[((hsi*784+0)*1+lsi)*1]), &(inteval->stack[((hsi*588+784)*1+lsi)*1]),28);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*2520+20404)*1+lsi)*1]), &(inteval->stack[((hsi*1764+12196)*1+lsi)*1]), &(inteval->stack[((hsi*1260+1792)*1+lsi)*1]),28);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*5670+22924)*1+lsi)*1]), &(inteval->stack[((hsi*2520+20404)*1+lsi)*1]), &(inteval->stack[((hsi*1890+14464)*1+lsi)*1]),90);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*8100+4096)*1+lsi)*1]), &(inteval->stack[((hsi*5670+22924)*1+lsi)*1]), &(inteval->stack[((hsi*4050+16354)*1+lsi)*1]),90);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*8100+4096)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
