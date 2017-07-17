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
#include <_elecpot_P_P_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _elecpot_P_P(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,9)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_elecpot_P_P_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp1;
fp1 = inteval->AB_z[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = inteval->stack[((hsi*1+8)*1+lsi)*1] + fp1;
inteval->stack[((hsi*9+17)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp3;
fp3 = inteval->AB_y[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp3;
inteval->stack[((hsi*9+16)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->AB_x[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp5;
inteval->stack[((hsi*9+15)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp13;
fp13 = inteval->AB_z[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp13;
inteval->stack[((hsi*9+14)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp7;
fp7 = inteval->AB_y[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->stack[((hsi*1+5)*1+lsi)*1] + fp7;
inteval->stack[((hsi*9+13)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp9;
fp9 = inteval->AB_x[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp9;
inteval->stack[((hsi*9+12)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp15;
fp15 = inteval->AB_z[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp15;
inteval->stack[((hsi*9+11)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp17;
fp17 = inteval->AB_y[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp17;
inteval->stack[((hsi*9+10)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp11;
fp11 = inteval->AB_x[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->stack[((hsi*1+0)*1+lsi)*1] + fp11;
inteval->stack[((hsi*9+9)*1+lsi)*1] = fp10;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*9+9)*1+lsi)*1]);
/** Number of flops = 18 */
}

#ifdef __cplusplus
};
#endif
