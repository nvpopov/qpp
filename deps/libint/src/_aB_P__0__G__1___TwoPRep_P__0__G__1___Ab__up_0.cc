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
#include <HRRPart1bra0ket0gg.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hf.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0id.h>
#include <HRRPart1bra0ket0ip.h>
#include <HRRPart1bra0ket0kp.h>
#include <_aB_P__0__G__1___TwoPRep_P__0__G__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_P__0__G__1___TwoPRep_P__0__G__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,1305)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_P__0__G__1___TwoPRep_P__0__G__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*189+3330)*1+lsi)*1]), &(inteval->stack[((hsi*84+1113)*1+lsi)*1]), &(inteval->stack[((hsi*63+1197)*1+lsi)*1]),3);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*252+3519)*1+lsi)*1]), &(inteval->stack[((hsi*108+1005)*1+lsi)*1]), &(inteval->stack[((hsi*84+1113)*1+lsi)*1]),3);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*378+3771)*1+lsi)*1]), &(inteval->stack[((hsi*252+3519)*1+lsi)*1]), &(inteval->stack[((hsi*189+3330)*1+lsi)*1]),3);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*135+4149)*1+lsi)*1]), &(inteval->stack[((hsi*63+1197)*1+lsi)*1]), &(inteval->stack[((hsi*45+1260)*1+lsi)*1]),3);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*270+4284)*1+lsi)*1]), &(inteval->stack[((hsi*189+3330)*1+lsi)*1]), &(inteval->stack[((hsi*135+4149)*1+lsi)*1]),3);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*450+4554)*1+lsi)*1]), &(inteval->stack[((hsi*378+3771)*1+lsi)*1]), &(inteval->stack[((hsi*270+4284)*1+lsi)*1]),3);
HRRPart1bra0ket0kp(inteval, &(inteval->stack[((hsi*324+4149)*1+lsi)*1]), &(inteval->stack[((hsi*135+870)*1+lsi)*1]), &(inteval->stack[((hsi*108+1005)*1+lsi)*1]),3);
HRRPart1bra0ket0id(inteval, &(inteval->stack[((hsi*504+5004)*1+lsi)*1]), &(inteval->stack[((hsi*324+4149)*1+lsi)*1]), &(inteval->stack[((hsi*252+3519)*1+lsi)*1]),3);
HRRPart1bra0ket0hf(inteval, &(inteval->stack[((hsi*630+5508)*1+lsi)*1]), &(inteval->stack[((hsi*504+5004)*1+lsi)*1]), &(inteval->stack[((hsi*378+3771)*1+lsi)*1]),3);
HRRPart1bra0ket0gg(inteval, &(inteval->stack[((hsi*675+3330)*1+lsi)*1]), &(inteval->stack[((hsi*630+5508)*1+lsi)*1]), &(inteval->stack[((hsi*450+4554)*1+lsi)*1]),3);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*378+870)*1+lsi)*1]), &(inteval->stack[((hsi*168+486)*1+lsi)*1]), &(inteval->stack[((hsi*126+654)*1+lsi)*1]),6);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*504+4005)*1+lsi)*1]), &(inteval->stack[((hsi*216+270)*1+lsi)*1]), &(inteval->stack[((hsi*168+486)*1+lsi)*1]),6);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*756+4509)*1+lsi)*1]), &(inteval->stack[((hsi*504+4005)*1+lsi)*1]), &(inteval->stack[((hsi*378+870)*1+lsi)*1]),6);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*270+5265)*1+lsi)*1]), &(inteval->stack[((hsi*126+654)*1+lsi)*1]), &(inteval->stack[((hsi*90+780)*1+lsi)*1]),6);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*540+5535)*1+lsi)*1]), &(inteval->stack[((hsi*378+870)*1+lsi)*1]), &(inteval->stack[((hsi*270+5265)*1+lsi)*1]),6);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*900+6075)*1+lsi)*1]), &(inteval->stack[((hsi*756+4509)*1+lsi)*1]), &(inteval->stack[((hsi*540+5535)*1+lsi)*1]),6);
HRRPart1bra0ket0kp(inteval, &(inteval->stack[((hsi*648+486)*1+lsi)*1]), &(inteval->stack[((hsi*270+0)*1+lsi)*1]), &(inteval->stack[((hsi*216+270)*1+lsi)*1]),6);
HRRPart1bra0ket0id(inteval, &(inteval->stack[((hsi*1008+6975)*1+lsi)*1]), &(inteval->stack[((hsi*648+486)*1+lsi)*1]), &(inteval->stack[((hsi*504+4005)*1+lsi)*1]),6);
HRRPart1bra0ket0hf(inteval, &(inteval->stack[((hsi*1260+0)*1+lsi)*1]), &(inteval->stack[((hsi*1008+6975)*1+lsi)*1]), &(inteval->stack[((hsi*756+4509)*1+lsi)*1]),6);
HRRPart1bra0ket0gg(inteval, &(inteval->stack[((hsi*1350+4005)*1+lsi)*1]), &(inteval->stack[((hsi*1260+0)*1+lsi)*1]), &(inteval->stack[((hsi*900+6075)*1+lsi)*1]),6);
HRRPart0bra0ket0pp(inteval, &(inteval->stack[((hsi*2025+1305)*1+lsi)*1]), &(inteval->stack[((hsi*1350+4005)*1+lsi)*1]), &(inteval->stack[((hsi*675+3330)*1+lsi)*1]),225);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*2025+1305)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
