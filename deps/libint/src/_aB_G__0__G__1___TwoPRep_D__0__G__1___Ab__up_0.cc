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
#include <HRRPart1bra0ket0gf.h>
#include <HRRPart1bra0ket0gg.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hf.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0id.h>
#include <HRRPart1bra0ket0ip.h>
#include <HRRPart1bra0ket0kp.h>
#include <_aB_G__0__G__1___TwoPRep_D__0__G__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_G__0__G__1___TwoPRep_D__0__G__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,9280)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_G__0__G__1___TwoPRep_D__0__G__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1323+29530)*1+lsi)*1]), &(inteval->stack[((hsi*588+5761)*1+lsi)*1]), &(inteval->stack[((hsi*441+6349)*1+lsi)*1]),21);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*1764+30853)*1+lsi)*1]), &(inteval->stack[((hsi*756+5005)*1+lsi)*1]), &(inteval->stack[((hsi*588+5761)*1+lsi)*1]),21);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*2646+32617)*1+lsi)*1]), &(inteval->stack[((hsi*1764+30853)*1+lsi)*1]), &(inteval->stack[((hsi*1323+29530)*1+lsi)*1]),21);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*945+35263)*1+lsi)*1]), &(inteval->stack[((hsi*441+6349)*1+lsi)*1]), &(inteval->stack[((hsi*315+6790)*1+lsi)*1]),21);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1890+36208)*1+lsi)*1]), &(inteval->stack[((hsi*1323+29530)*1+lsi)*1]), &(inteval->stack[((hsi*945+35263)*1+lsi)*1]),21);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*3150+38098)*1+lsi)*1]), &(inteval->stack[((hsi*2646+32617)*1+lsi)*1]), &(inteval->stack[((hsi*1890+36208)*1+lsi)*1]),21);
HRRPart1bra0ket0kp(inteval, &(inteval->stack[((hsi*2268+35263)*1+lsi)*1]), &(inteval->stack[((hsi*945+4060)*1+lsi)*1]), &(inteval->stack[((hsi*756+5005)*1+lsi)*1]),21);
HRRPart1bra0ket0id(inteval, &(inteval->stack[((hsi*3528+41248)*1+lsi)*1]), &(inteval->stack[((hsi*2268+35263)*1+lsi)*1]), &(inteval->stack[((hsi*1764+30853)*1+lsi)*1]),21);
HRRPart1bra0ket0hf(inteval, &(inteval->stack[((hsi*4410+44776)*1+lsi)*1]), &(inteval->stack[((hsi*3528+41248)*1+lsi)*1]), &(inteval->stack[((hsi*2646+32617)*1+lsi)*1]),21);
HRRPart1bra0ket0gg(inteval, &(inteval->stack[((hsi*4725+29530)*1+lsi)*1]), &(inteval->stack[((hsi*4410+44776)*1+lsi)*1]), &(inteval->stack[((hsi*3150+38098)*1+lsi)*1]),21);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*945+4060)*1+lsi)*1]), &(inteval->stack[((hsi*420+8320)*1+lsi)*1]), &(inteval->stack[((hsi*315+8740)*1+lsi)*1]),15);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*1260+5005)*1+lsi)*1]), &(inteval->stack[((hsi*540+7780)*1+lsi)*1]), &(inteval->stack[((hsi*420+8320)*1+lsi)*1]),15);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*1890+34255)*1+lsi)*1]), &(inteval->stack[((hsi*1260+5005)*1+lsi)*1]), &(inteval->stack[((hsi*945+4060)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+6265)*1+lsi)*1]), &(inteval->stack[((hsi*315+8740)*1+lsi)*1]), &(inteval->stack[((hsi*225+9055)*1+lsi)*1]),15);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1350+36145)*1+lsi)*1]), &(inteval->stack[((hsi*945+4060)*1+lsi)*1]), &(inteval->stack[((hsi*675+6265)*1+lsi)*1]),15);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*2250+37495)*1+lsi)*1]), &(inteval->stack[((hsi*1890+34255)*1+lsi)*1]), &(inteval->stack[((hsi*1350+36145)*1+lsi)*1]),15);
HRRPart1bra0ket0kp(inteval, &(inteval->stack[((hsi*1620+39745)*1+lsi)*1]), &(inteval->stack[((hsi*675+7105)*1+lsi)*1]), &(inteval->stack[((hsi*540+7780)*1+lsi)*1]),15);
HRRPart1bra0ket0id(inteval, &(inteval->stack[((hsi*2520+6265)*1+lsi)*1]), &(inteval->stack[((hsi*1620+39745)*1+lsi)*1]), &(inteval->stack[((hsi*1260+5005)*1+lsi)*1]),15);
HRRPart1bra0ket0hf(inteval, &(inteval->stack[((hsi*3150+39745)*1+lsi)*1]), &(inteval->stack[((hsi*2520+6265)*1+lsi)*1]), &(inteval->stack[((hsi*1890+34255)*1+lsi)*1]),15);
HRRPart1bra0ket0gg(inteval, &(inteval->stack[((hsi*3375+4060)*1+lsi)*1]), &(inteval->stack[((hsi*3150+39745)*1+lsi)*1]), &(inteval->stack[((hsi*2250+37495)*1+lsi)*1]),15);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*10125+34255)*1+lsi)*1]), &(inteval->stack[((hsi*4725+29530)*1+lsi)*1]), &(inteval->stack[((hsi*3375+4060)*1+lsi)*1]),225);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1764+4060)*1+lsi)*1]), &(inteval->stack[((hsi*784+2268)*1+lsi)*1]), &(inteval->stack[((hsi*588+3052)*1+lsi)*1]),28);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*2352+5824)*1+lsi)*1]), &(inteval->stack[((hsi*1008+1260)*1+lsi)*1]), &(inteval->stack[((hsi*784+2268)*1+lsi)*1]),28);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*3528+44380)*1+lsi)*1]), &(inteval->stack[((hsi*2352+5824)*1+lsi)*1]), &(inteval->stack[((hsi*1764+4060)*1+lsi)*1]),28);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+47908)*1+lsi)*1]), &(inteval->stack[((hsi*588+3052)*1+lsi)*1]), &(inteval->stack[((hsi*420+3640)*1+lsi)*1]),28);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*2520+49168)*1+lsi)*1]), &(inteval->stack[((hsi*1764+4060)*1+lsi)*1]), &(inteval->stack[((hsi*1260+47908)*1+lsi)*1]),28);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*4200+51688)*1+lsi)*1]), &(inteval->stack[((hsi*3528+44380)*1+lsi)*1]), &(inteval->stack[((hsi*2520+49168)*1+lsi)*1]),28);
HRRPart1bra0ket0kp(inteval, &(inteval->stack[((hsi*3024+47908)*1+lsi)*1]), &(inteval->stack[((hsi*1260+0)*1+lsi)*1]), &(inteval->stack[((hsi*1008+1260)*1+lsi)*1]),28);
HRRPart1bra0ket0id(inteval, &(inteval->stack[((hsi*4704+0)*1+lsi)*1]), &(inteval->stack[((hsi*3024+47908)*1+lsi)*1]), &(inteval->stack[((hsi*2352+5824)*1+lsi)*1]),28);
HRRPart1bra0ket0hf(inteval, &(inteval->stack[((hsi*5880+55888)*1+lsi)*1]), &(inteval->stack[((hsi*4704+0)*1+lsi)*1]), &(inteval->stack[((hsi*3528+44380)*1+lsi)*1]),28);
HRRPart1bra0ket0gg(inteval, &(inteval->stack[((hsi*6300+0)*1+lsi)*1]), &(inteval->stack[((hsi*5880+55888)*1+lsi)*1]), &(inteval->stack[((hsi*4200+51688)*1+lsi)*1]),28);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*14175+44380)*1+lsi)*1]), &(inteval->stack[((hsi*6300+0)*1+lsi)*1]), &(inteval->stack[((hsi*4725+29530)*1+lsi)*1]),225);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*20250+9280)*1+lsi)*1]), &(inteval->stack[((hsi*14175+44380)*1+lsi)*1]), &(inteval->stack[((hsi*10125+34255)*1+lsi)*1]),225);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*20250+9280)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
