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
void OSVRRElecPotInBra_aB_g__0___ElecPot_s__0___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2, const LIBINT2_REALTYPE* src3) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp2;
fp2 = src2[((hsi*6+5)*1+lsi)*1] - src3[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp3 * fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->PC_z[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_z[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = fp6 - fp5;
LIBINT2_REALTYPE fp0;
fp0 = fp4 + fp1;
target[((hsi*15+14)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp9;
fp9 = src2[((hsi*6+4)*1+lsi)*1] - src3[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp8;
fp8 = fp10 * fp9;
LIBINT2_REALTYPE fp12;
fp12 = inteval->PC_z[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = inteval->PA_z[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = fp13 - fp12;
LIBINT2_REALTYPE fp7;
fp7 = fp11 + fp8;
target[((hsi*15+13)*1+lsi)*1] = fp7;
LIBINT2_REALTYPE fp16;
fp16 = src2[((hsi*6+3)*1+lsi)*1] - src3[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp15;
fp15 = fp17 * fp16;
LIBINT2_REALTYPE fp19;
fp19 = inteval->PC_z[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = inteval->PA_z[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = fp20 - fp19;
LIBINT2_REALTYPE fp14;
fp14 = fp18 + fp15;
target[((hsi*15+12)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PC_z[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->PA_z[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = fp23 - fp22;
target[((hsi*15+11)*1+lsi)*1] = fp21;
LIBINT2_REALTYPE fp26;
fp26 = src2[((hsi*6+3)*1+lsi)*1] - src3[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp25;
fp25 = fp27 * fp26;
LIBINT2_REALTYPE fp29;
fp29 = inteval->PC_y[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->PA_y[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = fp30 - fp29;
LIBINT2_REALTYPE fp24;
fp24 = fp28 + fp25;
target[((hsi*15+10)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp33;
fp33 = src2[((hsi*6+2)*1+lsi)*1] - src3[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp32;
fp32 = fp34 * fp33;
LIBINT2_REALTYPE fp36;
fp36 = inteval->PC_z[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = inteval->PA_z[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = fp37 - fp36;
LIBINT2_REALTYPE fp31;
fp31 = fp35 + fp32;
target[((hsi*15+9)*1+lsi)*1] = fp31;
LIBINT2_REALTYPE fp40;
fp40 = src2[((hsi*6+1)*1+lsi)*1] - src3[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp41;
fp41 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp39;
fp39 = fp41 * fp40;
LIBINT2_REALTYPE fp43;
fp43 = inteval->PC_z[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->PA_z[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = fp44 - fp43;
LIBINT2_REALTYPE fp38;
fp38 = fp42 + fp39;
target[((hsi*15+8)*1+lsi)*1] = fp38;
LIBINT2_REALTYPE fp46;
fp46 = inteval->PC_z[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = inteval->PA_z[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp45;
fp45 = fp47 - fp46;
target[((hsi*15+7)*1+lsi)*1] = fp45;
LIBINT2_REALTYPE fp50;
fp50 = src2[((hsi*6+1)*1+lsi)*1] - src3[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp51;
fp51 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp49;
fp49 = fp51 * fp50;
LIBINT2_REALTYPE fp53;
fp53 = inteval->PC_y[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = inteval->PA_y[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = fp54 - fp53;
LIBINT2_REALTYPE fp48;
fp48 = fp52 + fp49;
target[((hsi*15+6)*1+lsi)*1] = fp48;
LIBINT2_REALTYPE fp57;
fp57 = src2[((hsi*6+0)*1+lsi)*1] - src3[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp56;
fp56 = fp58 * fp57;
LIBINT2_REALTYPE fp60;
fp60 = inteval->PC_z[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = inteval->PA_z[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp59;
fp59 = fp61 - fp60;
LIBINT2_REALTYPE fp55;
fp55 = fp59 + fp56;
target[((hsi*15+5)*1+lsi)*1] = fp55;
LIBINT2_REALTYPE fp63;
fp63 = inteval->PC_z[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = inteval->PA_z[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = fp64 - fp63;
target[((hsi*15+4)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp67;
fp67 = src2[((hsi*6+0)*1+lsi)*1] - src3[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp68;
fp68 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp66;
fp66 = fp68 * fp67;
LIBINT2_REALTYPE fp70;
fp70 = inteval->PC_y[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp71;
fp71 = inteval->PA_y[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp69;
fp69 = fp71 - fp70;
LIBINT2_REALTYPE fp65;
fp65 = fp69 + fp66;
target[((hsi*15+3)*1+lsi)*1] = fp65;
LIBINT2_REALTYPE fp73;
fp73 = inteval->PC_z[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp74;
fp74 = inteval->PA_z[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = fp74 - fp73;
target[((hsi*15+2)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp76;
fp76 = inteval->PC_y[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp77;
fp77 = inteval->PA_y[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp75;
fp75 = fp77 - fp76;
target[((hsi*15+1)*1+lsi)*1] = fp75;
LIBINT2_REALTYPE fp80;
fp80 = src2[((hsi*6+0)*1+lsi)*1] - src3[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp81;
fp81 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp79;
fp79 = fp81 * fp80;
LIBINT2_REALTYPE fp83;
fp83 = inteval->PC_x[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp84;
fp84 = inteval->PA_x[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp82;
fp82 = fp84 - fp83;
LIBINT2_REALTYPE fp78;
fp78 = fp82 + fp79;
target[((hsi*15+0)*1+lsi)*1] = fp78;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 85 */
}

#ifdef __cplusplus
};
#endif
