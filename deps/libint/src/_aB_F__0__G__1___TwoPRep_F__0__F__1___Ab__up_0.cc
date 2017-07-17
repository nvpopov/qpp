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
#include <HRRPart1bra0ket0gd.h>
#include <HRRPart1bra0ket0gf.h>
#include <HRRPart1bra0ket0gp.h>
#include <HRRPart1bra0ket0hd.h>
#include <HRRPart1bra0ket0hp.h>
#include <HRRPart1bra0ket0ip.h>
#include <_aB_F__0__G__1___TwoPRep_F__0__F__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_F__0__G__1___TwoPRep_F__0__F__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,7400)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_F__0__G__1___TwoPRep_F__0__F__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*945+22400)*1+lsi)*1]), &(inteval->stack[((hsi*441+5324)*1+lsi)*1]), &(inteval->stack[((hsi*315+5765)*1+lsi)*1]),21);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*630+23345)*1+lsi)*1]), &(inteval->stack[((hsi*315+5765)*1+lsi)*1]), &(inteval->stack[((hsi*210+6080)*1+lsi)*1]),21);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*1260+23975)*1+lsi)*1]), &(inteval->stack[((hsi*945+22400)*1+lsi)*1]), &(inteval->stack[((hsi*630+23345)*1+lsi)*1]),21);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*1323+25235)*1+lsi)*1]), &(inteval->stack[((hsi*588+4736)*1+lsi)*1]), &(inteval->stack[((hsi*441+5324)*1+lsi)*1]),21);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*1890+26558)*1+lsi)*1]), &(inteval->stack[((hsi*1323+25235)*1+lsi)*1]), &(inteval->stack[((hsi*945+22400)*1+lsi)*1]),21);
HRRPart0bra0ket0ff(inteval, &(inteval->stack[((hsi*2100+28448)*1+lsi)*1]), &(inteval->stack[((hsi*1890+26558)*1+lsi)*1]), &(inteval->stack[((hsi*1260+23975)*1+lsi)*1]),21);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*1260+22400)*1+lsi)*1]), &(inteval->stack[((hsi*588+3448)*1+lsi)*1]), &(inteval->stack[((hsi*420+4036)*1+lsi)*1]),28);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*840+23660)*1+lsi)*1]), &(inteval->stack[((hsi*420+4036)*1+lsi)*1]), &(inteval->stack[((hsi*280+4456)*1+lsi)*1]),28);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*1680+24500)*1+lsi)*1]), &(inteval->stack[((hsi*1260+22400)*1+lsi)*1]), &(inteval->stack[((hsi*840+23660)*1+lsi)*1]),28);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*1764+26180)*1+lsi)*1]), &(inteval->stack[((hsi*784+2664)*1+lsi)*1]), &(inteval->stack[((hsi*588+3448)*1+lsi)*1]),28);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*2520+2664)*1+lsi)*1]), &(inteval->stack[((hsi*1764+26180)*1+lsi)*1]), &(inteval->stack[((hsi*1260+22400)*1+lsi)*1]),28);
HRRPart0bra0ket0ff(inteval, &(inteval->stack[((hsi*2800+30548)*1+lsi)*1]), &(inteval->stack[((hsi*2520+2664)*1+lsi)*1]), &(inteval->stack[((hsi*1680+24500)*1+lsi)*1]),28);
HRRPart1bra0ket0hp(inteval, &(inteval->stack[((hsi*6300+33348)*1+lsi)*1]), &(inteval->stack[((hsi*2800+30548)*1+lsi)*1]), &(inteval->stack[((hsi*2100+28448)*1+lsi)*1]),100);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*675+22400)*1+lsi)*1]), &(inteval->stack[((hsi*315+6710)*1+lsi)*1]), &(inteval->stack[((hsi*225+7025)*1+lsi)*1]),15);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*450+23075)*1+lsi)*1]), &(inteval->stack[((hsi*225+7025)*1+lsi)*1]), &(inteval->stack[((hsi*150+7250)*1+lsi)*1]),15);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*900+23525)*1+lsi)*1]), &(inteval->stack[((hsi*675+22400)*1+lsi)*1]), &(inteval->stack[((hsi*450+23075)*1+lsi)*1]),15);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*945+24425)*1+lsi)*1]), &(inteval->stack[((hsi*420+6290)*1+lsi)*1]), &(inteval->stack[((hsi*315+6710)*1+lsi)*1]),15);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*1350+2664)*1+lsi)*1]), &(inteval->stack[((hsi*945+24425)*1+lsi)*1]), &(inteval->stack[((hsi*675+22400)*1+lsi)*1]),15);
HRRPart0bra0ket0ff(inteval, &(inteval->stack[((hsi*1500+24425)*1+lsi)*1]), &(inteval->stack[((hsi*1350+2664)*1+lsi)*1]), &(inteval->stack[((hsi*900+23525)*1+lsi)*1]),15);
HRRPart1bra0ket0gp(inteval, &(inteval->stack[((hsi*4500+2664)*1+lsi)*1]), &(inteval->stack[((hsi*2100+28448)*1+lsi)*1]), &(inteval->stack[((hsi*1500+24425)*1+lsi)*1]),100);
HRRPart1bra0ket0gd(inteval, &(inteval->stack[((hsi*9000+39648)*1+lsi)*1]), &(inteval->stack[((hsi*6300+33348)*1+lsi)*1]), &(inteval->stack[((hsi*4500+2664)*1+lsi)*1]),100);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*1620+22400)*1+lsi)*1]), &(inteval->stack[((hsi*756+1008)*1+lsi)*1]), &(inteval->stack[((hsi*540+1764)*1+lsi)*1]),36);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*1080+24020)*1+lsi)*1]), &(inteval->stack[((hsi*540+1764)*1+lsi)*1]), &(inteval->stack[((hsi*360+2304)*1+lsi)*1]),36);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*2160+1764)*1+lsi)*1]), &(inteval->stack[((hsi*1620+22400)*1+lsi)*1]), &(inteval->stack[((hsi*1080+24020)*1+lsi)*1]),36);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*2268+24020)*1+lsi)*1]), &(inteval->stack[((hsi*1008+0)*1+lsi)*1]), &(inteval->stack[((hsi*756+1008)*1+lsi)*1]),36);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*3240+26288)*1+lsi)*1]), &(inteval->stack[((hsi*2268+24020)*1+lsi)*1]), &(inteval->stack[((hsi*1620+22400)*1+lsi)*1]),36);
HRRPart0bra0ket0ff(inteval, &(inteval->stack[((hsi*3600+22400)*1+lsi)*1]), &(inteval->stack[((hsi*3240+26288)*1+lsi)*1]), &(inteval->stack[((hsi*2160+1764)*1+lsi)*1]),36);
HRRPart1bra0ket0ip(inteval, &(inteval->stack[((hsi*8400+48648)*1+lsi)*1]), &(inteval->stack[((hsi*3600+22400)*1+lsi)*1]), &(inteval->stack[((hsi*2800+30548)*1+lsi)*1]),100);
HRRPart1bra0ket0hd(inteval, &(inteval->stack[((hsi*12600+57048)*1+lsi)*1]), &(inteval->stack[((hsi*8400+48648)*1+lsi)*1]), &(inteval->stack[((hsi*6300+33348)*1+lsi)*1]),100);
HRRPart1bra0ket0gf(inteval, &(inteval->stack[((hsi*15000+7400)*1+lsi)*1]), &(inteval->stack[((hsi*12600+57048)*1+lsi)*1]), &(inteval->stack[((hsi*9000+39648)*1+lsi)*1]),100);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*15000+7400)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
