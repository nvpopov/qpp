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
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0ip.h>
#include <_aB_G__0__G__1___TwoPRep_D__0__F__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_G__0__G__1___TwoPRep_D__0__F__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,6400)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_G__0__G__1___TwoPRep_D__0__F__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1323+19900)*1+lsi)*1]), &(inteval->stack[((hsi*588+3556)*1+lsi)*1]), &(inteval->stack[((hsi*441+4144)*1+lsi)*1]),21);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*945+21223)*1+lsi)*1]), &(inteval->stack[((hsi*441+4144)*1+lsi)*1]), &(inteval->stack[((hsi*315+4585)*1+lsi)*1]),21);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1890+22168)*1+lsi)*1]), &(inteval->stack[((hsi*1323+19900)*1+lsi)*1]), &(inteval->stack[((hsi*945+21223)*1+lsi)*1]),21);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*1764+24058)*1+lsi)*1]), &(inteval->stack[((hsi*756+2800)*1+lsi)*1]), &(inteval->stack[((hsi*588+3556)*1+lsi)*1]),21);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*2646+25822)*1+lsi)*1]), &(inteval->stack[((hsi*1764+24058)*1+lsi)*1]), &(inteval->stack[((hsi*1323+19900)*1+lsi)*1]),21);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*3150+28468)*1+lsi)*1]), &(inteval->stack[((hsi*2646+25822)*1+lsi)*1]), &(inteval->stack[((hsi*1890+22168)*1+lsi)*1]),21);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*945+19900)*1+lsi)*1]), &(inteval->stack[((hsi*420+5440)*1+lsi)*1]), &(inteval->stack[((hsi*315+5860)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+20845)*1+lsi)*1]), &(inteval->stack[((hsi*315+5860)*1+lsi)*1]), &(inteval->stack[((hsi*225+6175)*1+lsi)*1]),15);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1350+21520)*1+lsi)*1]), &(inteval->stack[((hsi*945+19900)*1+lsi)*1]), &(inteval->stack[((hsi*675+20845)*1+lsi)*1]),15);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*1260+22870)*1+lsi)*1]), &(inteval->stack[((hsi*540+4900)*1+lsi)*1]), &(inteval->stack[((hsi*420+5440)*1+lsi)*1]),15);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*1890+24130)*1+lsi)*1]), &(inteval->stack[((hsi*1260+22870)*1+lsi)*1]), &(inteval->stack[((hsi*945+19900)*1+lsi)*1]),15);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*2250+2800)*1+lsi)*1]), &(inteval->stack[((hsi*1890+24130)*1+lsi)*1]), &(inteval->stack[((hsi*1350+21520)*1+lsi)*1]),15);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*6750+19900)*1+lsi)*1]), &(inteval->stack[((hsi*3150+28468)*1+lsi)*1]), &(inteval->stack[((hsi*2250+2800)*1+lsi)*1]),150);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1764+2800)*1+lsi)*1]), &(inteval->stack[((hsi*784+1008)*1+lsi)*1]), &(inteval->stack[((hsi*588+1792)*1+lsi)*1]),28);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+4564)*1+lsi)*1]), &(inteval->stack[((hsi*588+1792)*1+lsi)*1]), &(inteval->stack[((hsi*420+2380)*1+lsi)*1]),28);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*2520+31618)*1+lsi)*1]), &(inteval->stack[((hsi*1764+2800)*1+lsi)*1]), &(inteval->stack[((hsi*1260+4564)*1+lsi)*1]),28);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*2352+34138)*1+lsi)*1]), &(inteval->stack[((hsi*1008+0)*1+lsi)*1]), &(inteval->stack[((hsi*784+1008)*1+lsi)*1]),28);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*3528+36490)*1+lsi)*1]), &(inteval->stack[((hsi*2352+34138)*1+lsi)*1]), &(inteval->stack[((hsi*1764+2800)*1+lsi)*1]),28);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*4200+0)*1+lsi)*1]), &(inteval->stack[((hsi*3528+36490)*1+lsi)*1]), &(inteval->stack[((hsi*2520+31618)*1+lsi)*1]),28);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*9450+31618)*1+lsi)*1]), &(inteval->stack[((hsi*4200+0)*1+lsi)*1]), &(inteval->stack[((hsi*3150+28468)*1+lsi)*1]),150);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*13500+6400)*1+lsi)*1]), &(inteval->stack[((hsi*9450+31618)*1+lsi)*1]), &(inteval->stack[((hsi*6750+19900)*1+lsi)*1]),150);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*13500+6400)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
