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
#include <HRRPart0bra0ket0pp.h>
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gf.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0ip.h>
#include <_aB_P__0__G__1___TwoPRep_P__0__F__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_P__0__G__1___TwoPRep_P__0__F__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,900)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_P__0__G__1___TwoPRep_P__0__F__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*189+2250)*1+lsi)*1]), &(inteval->stack[((hsi*84+708)*1+lsi)*1]), &(inteval->stack[((hsi*63+792)*1+lsi)*1]),3);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*135+2439)*1+lsi)*1]), &(inteval->stack[((hsi*63+792)*1+lsi)*1]), &(inteval->stack[((hsi*45+855)*1+lsi)*1]),3);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*270+2574)*1+lsi)*1]), &(inteval->stack[((hsi*189+2250)*1+lsi)*1]), &(inteval->stack[((hsi*135+2439)*1+lsi)*1]),3);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*252+2844)*1+lsi)*1]), &(inteval->stack[((hsi*108+600)*1+lsi)*1]), &(inteval->stack[((hsi*84+708)*1+lsi)*1]),3);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*378+3096)*1+lsi)*1]), &(inteval->stack[((hsi*252+2844)*1+lsi)*1]), &(inteval->stack[((hsi*189+2250)*1+lsi)*1]),3);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*450+3474)*1+lsi)*1]), &(inteval->stack[((hsi*378+3096)*1+lsi)*1]), &(inteval->stack[((hsi*270+2574)*1+lsi)*1]),3);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*378+2250)*1+lsi)*1]), &(inteval->stack[((hsi*168+216)*1+lsi)*1]), &(inteval->stack[((hsi*126+384)*1+lsi)*1]),6);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*270+2628)*1+lsi)*1]), &(inteval->stack[((hsi*126+384)*1+lsi)*1]), &(inteval->stack[((hsi*90+510)*1+lsi)*1]),6);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*540+2898)*1+lsi)*1]), &(inteval->stack[((hsi*378+2250)*1+lsi)*1]), &(inteval->stack[((hsi*270+2628)*1+lsi)*1]),6);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*504+384)*1+lsi)*1]), &(inteval->stack[((hsi*216+0)*1+lsi)*1]), &(inteval->stack[((hsi*168+216)*1+lsi)*1]),6);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*756+3924)*1+lsi)*1]), &(inteval->stack[((hsi*504+384)*1+lsi)*1]), &(inteval->stack[((hsi*378+2250)*1+lsi)*1]),6);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*900+0)*1+lsi)*1]), &(inteval->stack[((hsi*756+3924)*1+lsi)*1]), &(inteval->stack[((hsi*540+2898)*1+lsi)*1]),6);
HRRPart0bra0ket0pp(inteval, &(inteval->stack[((hsi*1350+900)*1+lsi)*1]), &(inteval->stack[((hsi*900+0)*1+lsi)*1]), &(inteval->stack[((hsi*450+3474)*1+lsi)*1]),150);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*1350+900)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
