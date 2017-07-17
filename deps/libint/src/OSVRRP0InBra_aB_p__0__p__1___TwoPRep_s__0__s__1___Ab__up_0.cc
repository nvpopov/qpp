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

#ifdef __cplusplus
extern "C" {
#endif
void OSVRRP0InBra_aB_p__0__p__1___TwoPRep_s__0__s__1___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp27;
fp27 = inteval->oo2ze[vi] * src2[((hsi*1+0)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->WP_z[vi] * src1[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = inteval->PA_z[vi] * src0[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp1;
fp1 = fp3 + fp2;
LIBINT2_REALTYPE fp0;
fp0 = fp1 + fp27;
target[((hsi*9+8)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp5;
fp5 = inteval->WP_z[vi] * src1[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_z[vi] * src0[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = fp6 + fp5;
target[((hsi*9+7)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp8;
fp8 = inteval->WP_z[vi] * src1[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp9;
fp9 = inteval->PA_z[vi] * src0[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = fp9 + fp8;
target[((hsi*9+6)*1+lsi)*1] = fp7;
LIBINT2_REALTYPE fp11;
fp11 = inteval->WP_y[vi] * src1[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = inteval->PA_y[vi] * src0[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp12 + fp11;
target[((hsi*9+5)*1+lsi)*1] = fp10;
LIBINT2_REALTYPE fp15;
fp15 = inteval->WP_y[vi] * src1[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->PA_y[vi] * src0[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = fp16 + fp15;
LIBINT2_REALTYPE fp13;
fp13 = fp14 + fp27;
target[((hsi*9+4)*1+lsi)*1] = fp13;
LIBINT2_REALTYPE fp18;
fp18 = inteval->WP_y[vi] * src1[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = inteval->PA_y[vi] * src0[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp19 + fp18;
target[((hsi*9+3)*1+lsi)*1] = fp17;
LIBINT2_REALTYPE fp21;
fp21 = inteval->WP_x[vi] * src1[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = inteval->PA_x[vi] * src0[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = fp22 + fp21;
target[((hsi*9+2)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp24;
fp24 = inteval->WP_x[vi] * src1[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = inteval->PA_x[vi] * src0[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = fp25 + fp24;
target[((hsi*9+1)*1+lsi)*1] = fp23;
LIBINT2_REALTYPE fp29;
fp29 = inteval->WP_x[vi] * src1[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->PA_x[vi] * src0[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = fp30 + fp29;
LIBINT2_REALTYPE fp26;
fp26 = fp28 + fp27;
target[((hsi*9+0)*1+lsi)*1] = fp26;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 31 */
}

#ifdef __cplusplus
};
#endif
