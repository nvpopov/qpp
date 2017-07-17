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
#include <_elecpot_G_F_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _elecpot_G_F(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,100)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_elecpot_G_F_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*63+250)*1+lsi)*1]), &(inteval->stack[((hsi*28+36)*1+lsi)*1]), &(inteval->stack[((hsi*21+64)*1+lsi)*1]),1);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*45+313)*1+lsi)*1]), &(inteval->stack[((hsi*21+64)*1+lsi)*1]), &(inteval->stack[((hsi*15+85)*1+lsi)*1]),1);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*90+358)*1+lsi)*1]), &(inteval->stack[((hsi*63+250)*1+lsi)*1]), &(inteval->stack[((hsi*45+313)*1+lsi)*1]),1);
HRRPart0bra0ket0ip(inteval, &(inteval->stack[((hsi*84+448)*1+lsi)*1]), &(inteval->stack[((hsi*36+0)*1+lsi)*1]), &(inteval->stack[((hsi*28+36)*1+lsi)*1]),1);
HRRPart0bra0ket0hd(inteval, &(inteval->stack[((hsi*126+532)*1+lsi)*1]), &(inteval->stack[((hsi*84+448)*1+lsi)*1]), &(inteval->stack[((hsi*63+250)*1+lsi)*1]),1);
HRRPart0bra0ket0gf(inteval, &(inteval->stack[((hsi*150+100)*1+lsi)*1]), &(inteval->stack[((hsi*126+532)*1+lsi)*1]), &(inteval->stack[((hsi*90+358)*1+lsi)*1]),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*150+100)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
