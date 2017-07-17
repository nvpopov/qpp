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
#include <HRRPart0bra0ket0gf.h>
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart0bra0ket0hd.h>
#include <HRRPart0bra0ket0hp.h>
#include <HRRPart0bra0ket0ip.h>
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gf.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0ip.h>
#include <_aB_G__0__G__1___TwoPRep_F__0__F__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_G__0__G__1___TwoPRep_F__0__F__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,10000)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_G__0__G__1___TwoPRep_F__0__F__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1323+32500)*1+lsi)*1]), &(inteval->stack[((hsi*588+7156)*1+lsi)*1]), &(inteval->stack[((hsi*441+7744)*1+lsi)*1]),21);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*945+33823)*1+lsi)*1]), &(inteval->stack[((hsi*441+7744)*1+lsi)*1]), &(inteval->stack[((hsi*315+8185)*1+lsi)*1]),21);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1890+34768)*1+lsi)*1]), &(inteval->stack[((hsi*1323+32500)*1+lsi)*1]), &(inteval->stack[((hsi*945+33823)*1+lsi)*1]),21);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*1764+36658)*1+lsi)*1]), &(inteval->stack[((hsi*756+6400)*1+lsi)*1]), &(inteval->stack[((hsi*588+7156)*1+lsi)*1]),21);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*2646+38422)*1+lsi)*1]), &(inteval->stack[((hsi*1764+36658)*1+lsi)*1]), &(inteval->stack[((hsi*1323+32500)*1+lsi)*1]),21);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*3150+41068)*1+lsi)*1]), &(inteval->stack[((hsi*2646+38422)*1+lsi)*1]), &(inteval->stack[((hsi*1890+34768)*1+lsi)*1]),21);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1764+32500)*1+lsi)*1]), &(inteval->stack[((hsi*784+4608)*1+lsi)*1]), &(inteval->stack[((hsi*588+5392)*1+lsi)*1]),28);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+34264)*1+lsi)*1]), &(inteval->stack[((hsi*588+5392)*1+lsi)*1]), &(inteval->stack[((hsi*420+5980)*1+lsi)*1]),28);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*2520+35524)*1+lsi)*1]), &(inteval->stack[((hsi*1764+32500)*1+lsi)*1]), &(inteval->stack[((hsi*1260+34264)*1+lsi)*1]),28);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*2352+5392)*1+lsi)*1]), &(inteval->stack[((hsi*1008+3600)*1+lsi)*1]), &(inteval->stack[((hsi*784+4608)*1+lsi)*1]),28);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*3528+44218)*1+lsi)*1]), &(inteval->stack[((hsi*2352+5392)*1+lsi)*1]), &(inteval->stack[((hsi*1764+32500)*1+lsi)*1]),28);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*4200+3600)*1+lsi)*1]), &(inteval->stack[((hsi*3528+44218)*1+lsi)*1]), &(inteval->stack[((hsi*2520+35524)*1+lsi)*1]),28);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*9450+44218)*1+lsi)*1]), &(inteval->stack[((hsi*4200+3600)*1+lsi)*1]), &(inteval->stack[((hsi*3150+41068)*1+lsi)*1]),150);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*945+32500)*1+lsi)*1]), &(inteval->stack[((hsi*420+9040)*1+lsi)*1]), &(inteval->stack[((hsi*315+9460)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+33445)*1+lsi)*1]), &(inteval->stack[((hsi*315+9460)*1+lsi)*1]), &(inteval->stack[((hsi*225+9775)*1+lsi)*1]),15);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1350+34120)*1+lsi)*1]), &(inteval->stack[((hsi*945+32500)*1+lsi)*1]), &(inteval->stack[((hsi*675+33445)*1+lsi)*1]),15);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*1260+35470)*1+lsi)*1]), &(inteval->stack[((hsi*540+8500)*1+lsi)*1]), &(inteval->stack[((hsi*420+9040)*1+lsi)*1]),15);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*1890+36730)*1+lsi)*1]), &(inteval->stack[((hsi*1260+35470)*1+lsi)*1]), &(inteval->stack[((hsi*945+32500)*1+lsi)*1]),15);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*2250+38620)*1+lsi)*1]), &(inteval->stack[((hsi*1890+36730)*1+lsi)*1]), &(inteval->stack[((hsi*1350+34120)*1+lsi)*1]),15);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*6750+53668)*1+lsi)*1]), &(inteval->stack[((hsi*3150+41068)*1+lsi)*1]), &(inteval->stack[((hsi*2250+38620)*1+lsi)*1]),150);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*13500+60418)*1+lsi)*1]), &(inteval->stack[((hsi*9450+44218)*1+lsi)*1]), &(inteval->stack[((hsi*6750+53668)*1+lsi)*1]),150);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*2268+32500)*1+lsi)*1]), &(inteval->stack[((hsi*1008+1296)*1+lsi)*1]), &(inteval->stack[((hsi*756+2304)*1+lsi)*1]),36);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1620+34768)*1+lsi)*1]), &(inteval->stack[((hsi*756+2304)*1+lsi)*1]), &(inteval->stack[((hsi*540+3060)*1+lsi)*1]),36);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*3240+36388)*1+lsi)*1]), &(inteval->stack[((hsi*2268+32500)*1+lsi)*1]), &(inteval->stack[((hsi*1620+34768)*1+lsi)*1]),36);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*3024+53668)*1+lsi)*1]), &(inteval->stack[((hsi*1296+0)*1+lsi)*1]), &(inteval->stack[((hsi*1008+1296)*1+lsi)*1]),36);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*4536+39628)*1+lsi)*1]), &(inteval->stack[((hsi*3024+53668)*1+lsi)*1]), &(inteval->stack[((hsi*2268+32500)*1+lsi)*1]),36);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*5400+53668)*1+lsi)*1]), &(inteval->stack[((hsi*4536+39628)*1+lsi)*1]), &(inteval->stack[((hsi*3240+36388)*1+lsi)*1]),36);
HRRPart0bra0ket0ip(inteval, &(inteval->stack[((hsi*12600+73918)*1+lsi)*1]), &(inteval->stack[((hsi*5400+53668)*1+lsi)*1]), &(inteval->stack[((hsi*4200+3600)*1+lsi)*1]),150);
HRRPart0bra0ket0hd(inteval, &(inteval->stack[((hsi*18900+86518)*1+lsi)*1]), &(inteval->stack[((hsi*12600+73918)*1+lsi)*1]), &(inteval->stack[((hsi*9450+44218)*1+lsi)*1]),150);
HRRPart0bra0ket0gf(inteval, &(inteval->stack[((hsi*22500+10000)*1+lsi)*1]), &(inteval->stack[((hsi*18900+86518)*1+lsi)*1]), &(inteval->stack[((hsi*13500+60418)*1+lsi)*1]),150);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*22500+10000)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
