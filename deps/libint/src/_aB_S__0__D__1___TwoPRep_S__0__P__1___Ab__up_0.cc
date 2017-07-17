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
#include <_aB_S__0__D__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_S__0__D__1___TwoPRep_S__0__P__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,16)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_S__0__D__1___TwoPRep_S__0__P__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp33;
fp33 = inteval->CD_y[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp33;
inteval->stack[((hsi*18+17)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp31;
fp31 = inteval->CD_z[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp31;
inteval->stack[((hsi*18+18)*1+lsi)*1] = fp30;
LIBINT2_REALTYPE fp29;
fp29 = inteval->CD_x[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp29;
inteval->stack[((hsi*18+19)*1+lsi)*1] = fp28;
LIBINT2_REALTYPE fp27;
fp27 = inteval->CD_y[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = inteval->stack[((hsi*1+5)*1+lsi)*1] + fp27;
inteval->stack[((hsi*18+20)*1+lsi)*1] = fp26;
LIBINT2_REALTYPE fp25;
fp25 = inteval->CD_z[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp25;
inteval->stack[((hsi*18+21)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp23;
fp23 = inteval->CD_x[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp23;
inteval->stack[((hsi*18+22)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp21;
fp21 = inteval->CD_y[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp21;
inteval->stack[((hsi*18+23)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp19;
fp19 = inteval->CD_z[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = inteval->stack[((hsi*1+8)*1+lsi)*1] + fp19;
inteval->stack[((hsi*18+24)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp35;
fp35 = inteval->CD_x[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->stack[((hsi*1+0)*1+lsi)*1] + fp35;
inteval->stack[((hsi*18+16)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp15;
fp15 = inteval->CD_y[vi] * inteval->stack[((hsi*1+9)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = inteval->stack[((hsi*1+10)*1+lsi)*1] + fp15;
inteval->stack[((hsi*18+26)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp13;
fp13 = inteval->CD_z[vi] * inteval->stack[((hsi*1+9)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = inteval->stack[((hsi*1+11)*1+lsi)*1] + fp13;
inteval->stack[((hsi*18+27)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp11;
fp11 = inteval->CD_x[vi] * inteval->stack[((hsi*1+12)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp11;
inteval->stack[((hsi*18+28)*1+lsi)*1] = fp10;
LIBINT2_REALTYPE fp9;
fp9 = inteval->CD_y[vi] * inteval->stack[((hsi*1+12)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->stack[((hsi*1+11)*1+lsi)*1] + fp9;
inteval->stack[((hsi*18+29)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp7;
fp7 = inteval->CD_z[vi] * inteval->stack[((hsi*1+12)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->stack[((hsi*1+13)*1+lsi)*1] + fp7;
inteval->stack[((hsi*18+30)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp5;
fp5 = inteval->CD_x[vi] * inteval->stack[((hsi*1+14)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->stack[((hsi*1+8)*1+lsi)*1] + fp5;
inteval->stack[((hsi*18+31)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp3;
fp3 = inteval->CD_y[vi] * inteval->stack[((hsi*1+14)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->stack[((hsi*1+13)*1+lsi)*1] + fp3;
inteval->stack[((hsi*18+32)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp1;
fp1 = inteval->CD_z[vi] * inteval->stack[((hsi*1+14)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = inteval->stack[((hsi*1+15)*1+lsi)*1] + fp1;
inteval->stack[((hsi*18+33)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp17;
fp17 = inteval->CD_x[vi] * inteval->stack[((hsi*1+9)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->stack[((hsi*1+5)*1+lsi)*1] + fp17;
inteval->stack[((hsi*18+25)*1+lsi)*1] = fp16;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*18+16)*1+lsi)*1]);
/** Number of flops = 36 */
}

#ifdef __cplusplus
};
#endif
