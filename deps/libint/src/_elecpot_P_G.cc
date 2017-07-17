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
#include <HRRPart0bra0ket0dp.h>
#include <HRRPart0bra0ket0fd.h>
#include <HRRPart0bra0ket0fp.h>
#include <HRRPart0bra0ket0gp.h>
#include <HRRPart0bra0ket0pd.h>
#include <HRRPart0bra0ket0pf.h>
#include <HRRPart0bra0ket0pg.h>
#include <HRRPart0bra0ket0pp.h>
#include <_elecpot_P_G_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _elecpot_P_G(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,55)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_elecpot_P_G_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
HRRPart0bra0ket0dp(inteval, &(inteval->stack[((hsi*18+100)*1+lsi)*1]), &(inteval->stack[((hsi*10+36)*1+lsi)*1]), &(inteval->stack[((hsi*6+46)*1+lsi)*1]),1);
HRRPart0bra0ket0fp(inteval, &(inteval->stack[((hsi*30+118)*1+lsi)*1]), &(inteval->stack[((hsi*15+21)*1+lsi)*1]), &(inteval->stack[((hsi*10+36)*1+lsi)*1]),1);
HRRPart0bra0ket0dd(inteval, &(inteval->stack[((hsi*36+148)*1+lsi)*1]), &(inteval->stack[((hsi*30+118)*1+lsi)*1]), &(inteval->stack[((hsi*18+100)*1+lsi)*1]),1);
HRRPart0bra0ket0pp(inteval, &(inteval->stack[((hsi*9+36)*1+lsi)*1]), &(inteval->stack[((hsi*6+46)*1+lsi)*1]), &(inteval->stack[((hsi*3+52)*1+lsi)*1]),1);
HRRPart0bra0ket0pd(inteval, &(inteval->stack[((hsi*18+184)*1+lsi)*1]), &(inteval->stack[((hsi*18+100)*1+lsi)*1]), &(inteval->stack[((hsi*9+36)*1+lsi)*1]),1);
HRRPart0bra0ket0pf(inteval, &(inteval->stack[((hsi*30+202)*1+lsi)*1]), &(inteval->stack[((hsi*36+148)*1+lsi)*1]), &(inteval->stack[((hsi*18+184)*1+lsi)*1]),1);
HRRPart0bra0ket0gp(inteval, &(inteval->stack[((hsi*45+232)*1+lsi)*1]), &(inteval->stack[((hsi*21+0)*1+lsi)*1]), &(inteval->stack[((hsi*15+21)*1+lsi)*1]),1);
HRRPart0bra0ket0fd(inteval, &(inteval->stack[((hsi*60+277)*1+lsi)*1]), &(inteval->stack[((hsi*45+232)*1+lsi)*1]), &(inteval->stack[((hsi*30+118)*1+lsi)*1]),1);
HRRPart0bra0ket0df(inteval, &(inteval->stack[((hsi*60+337)*1+lsi)*1]), &(inteval->stack[((hsi*60+277)*1+lsi)*1]), &(inteval->stack[((hsi*36+148)*1+lsi)*1]),1);
HRRPart0bra0ket0pg(inteval, &(inteval->stack[((hsi*45+55)*1+lsi)*1]), &(inteval->stack[((hsi*60+337)*1+lsi)*1]), &(inteval->stack[((hsi*30+202)*1+lsi)*1]),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*45+55)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
