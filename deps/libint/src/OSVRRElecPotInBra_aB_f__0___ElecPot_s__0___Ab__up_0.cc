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
void OSVRRElecPotInBra_aB_f__0___ElecPot_s__0___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2, const LIBINT2_REALTYPE* src3) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp41;
fp41 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp2;
fp2 = src2[((hsi*3+2)*1+lsi)*1] - src3[((hsi*3+2)*1+lsi)*1];
LIBINT2_REALTYPE fp1;
fp1 = fp41 * fp2;
LIBINT2_REALTYPE fp4;
fp4 = inteval->PC_z[vi] * src1[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = inteval->PA_z[vi] * src0[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = fp5 - fp4;
LIBINT2_REALTYPE fp0;
fp0 = fp3 + fp1;
target[((hsi*10+9)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp16;
fp16 = src2[((hsi*3+1)*1+lsi)*1] - src3[((hsi*3+1)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = inteval->oo2z[vi] * fp16;
LIBINT2_REALTYPE fp9;
fp9 = inteval->PC_z[vi] * src1[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->PA_z[vi] * src0[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = fp10 - fp9;
LIBINT2_REALTYPE fp6;
fp6 = fp8 + fp7;
target[((hsi*10+8)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp12;
fp12 = inteval->PC_z[vi] * src1[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = inteval->PA_z[vi] * src0[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = fp13 - fp12;
target[((hsi*10+7)*1+lsi)*1] = fp11;
LIBINT2_REALTYPE fp15;
fp15 = fp41 * fp16;
LIBINT2_REALTYPE fp18;
fp18 = inteval->PC_y[vi] * src1[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = inteval->PA_y[vi] * src0[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp19 - fp18;
LIBINT2_REALTYPE fp14;
fp14 = fp17 + fp15;
target[((hsi*10+6)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp40;
fp40 = src2[((hsi*3+0)*1+lsi)*1] - src3[((hsi*3+0)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = inteval->oo2z[vi] * fp40;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PC_z[vi] * src1[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->PA_z[vi] * src0[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = fp23 - fp22;
LIBINT2_REALTYPE fp20;
fp20 = fp21 + fp28;
target[((hsi*10+5)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp25;
fp25 = inteval->PC_z[vi] * src1[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = inteval->PA_z[vi] * src0[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = fp26 - fp25;
target[((hsi*10+4)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp30;
fp30 = inteval->PC_y[vi] * src1[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->PA_y[vi] * src0[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp29;
fp29 = fp31 - fp30;
LIBINT2_REALTYPE fp27;
fp27 = fp29 + fp28;
target[((hsi*10+3)*1+lsi)*1] = fp27;
LIBINT2_REALTYPE fp33;
fp33 = inteval->PC_z[vi] * src1[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->PA_z[vi] * src0[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = fp34 - fp33;
target[((hsi*10+2)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp36;
fp36 = inteval->PC_y[vi] * src1[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = inteval->PA_y[vi] * src0[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = fp37 - fp36;
target[((hsi*10+1)*1+lsi)*1] = fp35;
LIBINT2_REALTYPE fp39;
fp39 = fp41 * fp40;
LIBINT2_REALTYPE fp43;
fp43 = inteval->PC_x[vi] * src1[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->PA_x[vi] * src0[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = fp44 - fp43;
LIBINT2_REALTYPE fp38;
fp38 = fp42 + fp39;
target[((hsi*10+0)*1+lsi)*1] = fp38;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 45 */
}

#ifdef __cplusplus
};
#endif
