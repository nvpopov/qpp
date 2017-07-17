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
#include <_elecpot_S_P_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _elecpot_S_P(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,4)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_elecpot_S_P_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp1;
fp1 = inteval->AB_z[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp1;
inteval->stack[((hsi*3+6)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp3;
fp3 = inteval->AB_y[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp3;
inteval->stack[((hsi*3+5)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->AB_x[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->stack[((hsi*1+0)*1+lsi)*1] + fp5;
inteval->stack[((hsi*3+4)*1+lsi)*1] = fp4;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*3+4)*1+lsi)*1]);
/** Number of flops = 6 */
}

#ifdef __cplusplus
};
#endif
