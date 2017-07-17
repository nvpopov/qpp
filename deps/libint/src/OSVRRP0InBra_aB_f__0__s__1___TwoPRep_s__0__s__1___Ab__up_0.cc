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
void OSVRRP0InBra_aB_f__0__s__1___TwoPRep_s__0__s__1___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2, const LIBINT2_REALTYPE* src3) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp44;
fp44 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp3;
fp3 = inteval->roz[vi] * src3[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = src2[((hsi*3+2)*1+lsi)*1] - fp3;
LIBINT2_REALTYPE fp1;
fp1 = fp44 * fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->WP_z[vi] * src1[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_z[vi] * src0[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = fp6 + fp5;
LIBINT2_REALTYPE fp0;
fp0 = fp4 + fp1;
target[((hsi*10+9)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp18;
fp18 = inteval->roz[vi] * src3[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = src2[((hsi*3+1)*1+lsi)*1] - fp18;
LIBINT2_REALTYPE fp8;
fp8 = inteval->oo2z[vi] * fp17;
LIBINT2_REALTYPE fp10;
fp10 = inteval->WP_z[vi] * src1[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = inteval->PA_z[vi] * src0[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp9;
fp9 = fp11 + fp10;
LIBINT2_REALTYPE fp7;
fp7 = fp9 + fp8;
target[((hsi*10+8)*1+lsi)*1] = fp7;
LIBINT2_REALTYPE fp13;
fp13 = inteval->WP_z[vi] * src1[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = inteval->PA_z[vi] * src0[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = fp14 + fp13;
target[((hsi*10+7)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp16;
fp16 = fp44 * fp17;
LIBINT2_REALTYPE fp20;
fp20 = inteval->WP_y[vi] * src1[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = inteval->PA_y[vi] * src0[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = fp21 + fp20;
LIBINT2_REALTYPE fp15;
fp15 = fp19 + fp16;
target[((hsi*10+6)*1+lsi)*1] = fp15;
LIBINT2_REALTYPE fp43;
fp43 = inteval->roz[vi] * src3[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = src2[((hsi*3+0)*1+lsi)*1] - fp43;
LIBINT2_REALTYPE fp30;
fp30 = inteval->oo2z[vi] * fp42;
LIBINT2_REALTYPE fp24;
fp24 = inteval->WP_z[vi] * src1[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = inteval->PA_z[vi] * src0[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = fp25 + fp24;
LIBINT2_REALTYPE fp22;
fp22 = fp23 + fp30;
target[((hsi*10+5)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp27;
fp27 = inteval->WP_z[vi] * src1[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = inteval->PA_z[vi] * src0[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = fp28 + fp27;
target[((hsi*10+4)*1+lsi)*1] = fp26;
LIBINT2_REALTYPE fp32;
fp32 = inteval->WP_y[vi] * src1[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = inteval->PA_y[vi] * src0[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = fp33 + fp32;
LIBINT2_REALTYPE fp29;
fp29 = fp31 + fp30;
target[((hsi*10+3)*1+lsi)*1] = fp29;
LIBINT2_REALTYPE fp35;
fp35 = inteval->WP_z[vi] * src1[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = inteval->PA_z[vi] * src0[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = fp36 + fp35;
target[((hsi*10+2)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp38;
fp38 = inteval->WP_y[vi] * src1[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = inteval->PA_y[vi] * src0[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = fp39 + fp38;
target[((hsi*10+1)*1+lsi)*1] = fp37;
LIBINT2_REALTYPE fp41;
fp41 = fp44 * fp42;
LIBINT2_REALTYPE fp46;
fp46 = inteval->WP_x[vi] * src1[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = inteval->PA_x[vi] * src0[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp45;
fp45 = fp47 + fp46;
LIBINT2_REALTYPE fp40;
fp40 = fp45 + fp41;
target[((hsi*10+0)*1+lsi)*1] = fp40;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 48 */
}

#ifdef __cplusplus
};
#endif
