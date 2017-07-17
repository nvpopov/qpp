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
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gf.h>
#include <HRRPart1bra0ket0gg.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hf.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0id.h>
#include <HRRPart1bra0ket0ip.h>
#include <HRRPart1bra0ket0kp.h>
#include <_aB_S__0__G__1___TwoPRep_S__0__G__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_S__0__G__1___TwoPRep_S__0__G__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,145)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_S__0__G__1___TwoPRep_S__0__G__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*63+370)*1+lsi)*1]), &(inteval->stack[((hsi*28+81)*1+lsi)*1]), &(inteval->stack[((hsi*21+109)*1+lsi)*1]),1);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*84+433)*1+lsi)*1]), &(inteval->stack[((hsi*36+45)*1+lsi)*1]), &(inteval->stack[((hsi*28+81)*1+lsi)*1]),1);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*126+517)*1+lsi)*1]), &(inteval->stack[((hsi*84+433)*1+lsi)*1]), &(inteval->stack[((hsi*63+370)*1+lsi)*1]),1);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*45+643)*1+lsi)*1]), &(inteval->stack[((hsi*21+109)*1+lsi)*1]), &(inteval->stack[((hsi*15+130)*1+lsi)*1]),1);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*90+688)*1+lsi)*1]), &(inteval->stack[((hsi*63+370)*1+lsi)*1]), &(inteval->stack[((hsi*45+643)*1+lsi)*1]),1);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*150+778)*1+lsi)*1]), &(inteval->stack[((hsi*126+517)*1+lsi)*1]), &(inteval->stack[((hsi*90+688)*1+lsi)*1]),1);
HRRPart1bra0ket0kp(inteval, &(inteval->stack[((hsi*108+643)*1+lsi)*1]), &(inteval->stack[((hsi*45+0)*1+lsi)*1]), &(inteval->stack[((hsi*36+45)*1+lsi)*1]),1);
HRRPart1bra0ket0id(inteval, &(inteval->stack[((hsi*168+928)*1+lsi)*1]), &(inteval->stack[((hsi*108+643)*1+lsi)*1]), &(inteval->stack[((hsi*84+433)*1+lsi)*1]),1);
HRRPart1bra0ket0hf(inteval, &(inteval->stack[((hsi*210+1096)*1+lsi)*1]), &(inteval->stack[((hsi*168+928)*1+lsi)*1]), &(inteval->stack[((hsi*126+517)*1+lsi)*1]),1);
HRRPart1bra0ket0gg(inteval, &(inteval->stack[((hsi*225+145)*1+lsi)*1]), &(inteval->stack[((hsi*210+1096)*1+lsi)*1]), &(inteval->stack[((hsi*150+778)*1+lsi)*1]),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*225+145)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
