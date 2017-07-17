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
#include <HRRPart1bra0ket0fd.h>
#include <HRRPart1bra0ket0ff.h>
#include <HRRPart1bra0ket0fp.h>
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hp.h>
#include <_aB_P__0__F__1___TwoPRep_S__0__F__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_P__0__F__1___TwoPRep_S__0__F__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,222)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_P__0__F__1___TwoPRep_S__0__F__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*135+522)*1+lsi)*1]), &(inteval->stack[((hsi*63+84)*1+lsi)*1]), &(inteval->stack[((hsi*45+147)*1+lsi)*1]),3);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*90+657)*1+lsi)*1]), &(inteval->stack[((hsi*45+147)*1+lsi)*1]), &(inteval->stack[((hsi*30+192)*1+lsi)*1]),3);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*180+747)*1+lsi)*1]), &(inteval->stack[((hsi*135+522)*1+lsi)*1]), &(inteval->stack[((hsi*90+657)*1+lsi)*1]),3);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*189+927)*1+lsi)*1]), &(inteval->stack[((hsi*84+0)*1+lsi)*1]), &(inteval->stack[((hsi*63+84)*1+lsi)*1]),3);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*270+1116)*1+lsi)*1]), &(inteval->stack[((hsi*189+927)*1+lsi)*1]), &(inteval->stack[((hsi*135+522)*1+lsi)*1]),3);
HRRPart1bra0ket0ff(inteval, &(inteval->stack[((hsi*300+222)*1+lsi)*1]), &(inteval->stack[((hsi*270+1116)*1+lsi)*1]), &(inteval->stack[((hsi*180+747)*1+lsi)*1]),3);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*300+222)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
