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
#include <HRRPart0bra0ket0dd.h>
#include <HRRPart0bra0ket0df.h>
#include <HRRPart0bra0ket0dg.h>
#include <HRRPart0bra0ket0dp.h>
#include <HRRPart0bra0ket0fd.h>
#include <HRRPart0bra0ket0ff.h>
#include <HRRPart0bra0ket0fp.h>
#include <HRRPart0bra0ket0gd.h>
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart0bra0ket0hp.h>
#include <_elecpot_D_G_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _elecpot_D_G(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,80)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_elecpot_D_G_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*30+170)*1+lsi)*1]), &(inteval->stack[((hsi*15+49)*1+lsi)*1]), &(inteval->stack[((hsi*10+64)*1+lsi)*1]),1);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*45+200)*1+lsi)*1]), &(inteval->stack[((hsi*21+28)*1+lsi)*1]), &(inteval->stack[((hsi*15+49)*1+lsi)*1]),1);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*60+245)*1+lsi)*1]), &(inteval->stack[((hsi*45+200)*1+lsi)*1]), &(inteval->stack[((hsi*30+170)*1+lsi)*1]),1);
HRRPart0bra0ket0dp(inteval, &(inteval->stack[((hsi*18+305)*1+lsi)*1]), &(inteval->stack[((hsi*10+64)*1+lsi)*1]), &(inteval->stack[((hsi*6+74)*1+lsi)*1]),1);
HRRPart0bra0ket0dd(inteval, &(inteval->stack[((hsi*36+323)*1+lsi)*1]), &(inteval->stack[((hsi*30+170)*1+lsi)*1]), &(inteval->stack[((hsi*18+305)*1+lsi)*1]),1);
HRRPart0bra0ket0df(inteval, &(inteval->stack[((hsi*60+359)*1+lsi)*1]), &(inteval->stack[((hsi*60+245)*1+lsi)*1]), &(inteval->stack[((hsi*36+323)*1+lsi)*1]),1);
HRRPart0bra0ket0hp(inteval, &(inteval->stack[((hsi*63+419)*1+lsi)*1]), &(inteval->stack[((hsi*28+0)*1+lsi)*1]), &(inteval->stack[((hsi*21+28)*1+lsi)*1]),1);
HRRPart0bra0ket0gd(inteval, &(inteval->stack[((hsi*90+482)*1+lsi)*1]), &(inteval->stack[((hsi*63+419)*1+lsi)*1]), &(inteval->stack[((hsi*45+200)*1+lsi)*1]),1);
HRRPart0bra0ket0ff(inteval, &(inteval->stack[((hsi*100+572)*1+lsi)*1]), &(inteval->stack[((hsi*90+482)*1+lsi)*1]), &(inteval->stack[((hsi*60+245)*1+lsi)*1]),1);
HRRPart0bra0ket0dg(inteval, &(inteval->stack[((hsi*90+80)*1+lsi)*1]), &(inteval->stack[((hsi*100+572)*1+lsi)*1]), &(inteval->stack[((hsi*60+359)*1+lsi)*1]),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*90+80)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
