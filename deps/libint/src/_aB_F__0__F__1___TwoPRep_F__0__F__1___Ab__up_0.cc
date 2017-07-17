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
#include <HRRPart0bra0ket0fd.h>
#include <HRRPart0bra0ket0ff.h>
#include <HRRPart0bra0ket0fp.h>
#include <HRRPart0bra0ket0gd.h>
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart0bra0ket0hp.h>
#include <HRRPart1bra0ket0fd.h>
#include <HRRPart1bra0ket0ff.h>
#include <HRRPart1bra0ket0fp.h>
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hp.h>
#include <_aB_F__0__F__1___TwoPRep_F__0__F__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_F__0__F__1___TwoPRep_F__0__F__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,5476)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_F__0__F__1___TwoPRep_F__0__F__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*675+15476)*1+lsi)*1]), &(inteval->stack[((hsi*315+4046)*1+lsi)*1]), &(inteval->stack[((hsi*225+4361)*1+lsi)*1]),15);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*450+16151)*1+lsi)*1]), &(inteval->stack[((hsi*225+4361)*1+lsi)*1]), &(inteval->stack[((hsi*150+4586)*1+lsi)*1]),15);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*900+16601)*1+lsi)*1]), &(inteval->stack[((hsi*675+15476)*1+lsi)*1]), &(inteval->stack[((hsi*450+16151)*1+lsi)*1]),15);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*945+17501)*1+lsi)*1]), &(inteval->stack[((hsi*420+3626)*1+lsi)*1]), &(inteval->stack[((hsi*315+4046)*1+lsi)*1]),15);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1350+18446)*1+lsi)*1]), &(inteval->stack[((hsi*945+17501)*1+lsi)*1]), &(inteval->stack[((hsi*675+15476)*1+lsi)*1]),15);
HRRPart1bra0ket0ff(inteval, &(inteval->stack[((hsi*1500+19796)*1+lsi)*1]), &(inteval->stack[((hsi*1350+18446)*1+lsi)*1]), &(inteval->stack[((hsi*900+16601)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*945+15476)*1+lsi)*1]), &(inteval->stack[((hsi*441+2660)*1+lsi)*1]), &(inteval->stack[((hsi*315+3101)*1+lsi)*1]),21);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*630+16421)*1+lsi)*1]), &(inteval->stack[((hsi*315+3101)*1+lsi)*1]), &(inteval->stack[((hsi*210+3416)*1+lsi)*1]),21);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*1260+17051)*1+lsi)*1]), &(inteval->stack[((hsi*945+15476)*1+lsi)*1]), &(inteval->stack[((hsi*630+16421)*1+lsi)*1]),21);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1323+3101)*1+lsi)*1]), &(inteval->stack[((hsi*588+2072)*1+lsi)*1]), &(inteval->stack[((hsi*441+2660)*1+lsi)*1]),21);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*1890+21296)*1+lsi)*1]), &(inteval->stack[((hsi*1323+3101)*1+lsi)*1]), &(inteval->stack[((hsi*945+15476)*1+lsi)*1]),21);
HRRPart1bra0ket0ff(inteval, &(inteval->stack[((hsi*2100+2072)*1+lsi)*1]), &(inteval->stack[((hsi*1890+21296)*1+lsi)*1]), &(inteval->stack[((hsi*1260+17051)*1+lsi)*1]),21);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*4500+21296)*1+lsi)*1]), &(inteval->stack[((hsi*2100+2072)*1+lsi)*1]), &(inteval->stack[((hsi*1500+19796)*1+lsi)*1]),100);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*450+15476)*1+lsi)*1]), &(inteval->stack[((hsi*210+5016)*1+lsi)*1]), &(inteval->stack[((hsi*150+5226)*1+lsi)*1]),10);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*300+15926)*1+lsi)*1]), &(inteval->stack[((hsi*150+5226)*1+lsi)*1]), &(inteval->stack[((hsi*100+5376)*1+lsi)*1]),10);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*600+16226)*1+lsi)*1]), &(inteval->stack[((hsi*450+15476)*1+lsi)*1]), &(inteval->stack[((hsi*300+15926)*1+lsi)*1]),10);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*630+16826)*1+lsi)*1]), &(inteval->stack[((hsi*280+4736)*1+lsi)*1]), &(inteval->stack[((hsi*210+5016)*1+lsi)*1]),10);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*900+17456)*1+lsi)*1]), &(inteval->stack[((hsi*630+16826)*1+lsi)*1]), &(inteval->stack[((hsi*450+15476)*1+lsi)*1]),10);
HRRPart1bra0ket0ff(inteval, &(inteval->stack[((hsi*1000+18356)*1+lsi)*1]), &(inteval->stack[((hsi*900+17456)*1+lsi)*1]), &(inteval->stack[((hsi*600+16226)*1+lsi)*1]),10);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*3000+25796)*1+lsi)*1]), &(inteval->stack[((hsi*1500+19796)*1+lsi)*1]), &(inteval->stack[((hsi*1000+18356)*1+lsi)*1]),100);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*6000+28796)*1+lsi)*1]), &(inteval->stack[((hsi*4500+21296)*1+lsi)*1]), &(inteval->stack[((hsi*3000+25796)*1+lsi)*1]),100);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+15476)*1+lsi)*1]), &(inteval->stack[((hsi*588+784)*1+lsi)*1]), &(inteval->stack[((hsi*420+1372)*1+lsi)*1]),28);
HRRPart1bra0ket0fp(inteval, &(inteval->stack[((hsi*840+16736)*1+lsi)*1]), &(inteval->stack[((hsi*420+1372)*1+lsi)*1]), &(inteval->stack[((hsi*280+1792)*1+lsi)*1]),28);
HRRPart1bra0ket0fd(inteval, &(inteval->stack[((hsi*1680+17576)*1+lsi)*1]), &(inteval->stack[((hsi*1260+15476)*1+lsi)*1]), &(inteval->stack[((hsi*840+16736)*1+lsi)*1]),28);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*1764+25796)*1+lsi)*1]), &(inteval->stack[((hsi*784+0)*1+lsi)*1]), &(inteval->stack[((hsi*588+784)*1+lsi)*1]),28);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*2520+34796)*1+lsi)*1]), &(inteval->stack[((hsi*1764+25796)*1+lsi)*1]), &(inteval->stack[((hsi*1260+15476)*1+lsi)*1]),28);
HRRPart1bra0ket0ff(inteval, &(inteval->stack[((hsi*2800+25796)*1+lsi)*1]), &(inteval->stack[((hsi*2520+34796)*1+lsi)*1]), &(inteval->stack[((hsi*1680+17576)*1+lsi)*1]),28);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*6300+34796)*1+lsi)*1]), &(inteval->stack[((hsi*2800+25796)*1+lsi)*1]), &(inteval->stack[((hsi*2100+2072)*1+lsi)*1]),100);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*9000+41096)*1+lsi)*1]), &(inteval->stack[((hsi*6300+34796)*1+lsi)*1]), &(inteval->stack[((hsi*4500+21296)*1+lsi)*1]),100);
HRRPart0bra0ket0ff(inteval, &(inteval->stack[((hsi*10000+5476)*1+lsi)*1]), &(inteval->stack[((hsi*9000+41096)*1+lsi)*1]), &(inteval->stack[((hsi*6000+28796)*1+lsi)*1]),100);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*10000+5476)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
