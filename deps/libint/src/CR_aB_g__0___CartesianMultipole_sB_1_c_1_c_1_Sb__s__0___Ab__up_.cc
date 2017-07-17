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
void CR_aB_g__0___CartesianMultipole_sB_1_c_1_c_1_Sb__s__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = inteval->BO_z[vi] * fp0;
LIBINT2_REALTYPE fp1;
fp1 = 0 + src2[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = fp1 + fp3;
LIBINT2_REALTYPE fp36;
fp36 = 0 + src1[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = inteval->BO_y[vi] * fp36;
LIBINT2_REALTYPE fp37;
fp37 = 0 + src1[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = fp37 + fp39;
LIBINT2_REALTYPE fp40;
fp40 = 0 + src0[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp43;
fp43 = inteval->BO_x[vi] * fp40;
LIBINT2_REALTYPE fp41;
fp41 = 0 + src0[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = fp41 + fp43;
LIBINT2_REALTYPE fp61;
fp61 = fp42 * fp38;
LIBINT2_REALTYPE fp60;
fp60 = fp61 * fp2;
target[((hsi*15+14)*1+lsi)*1] = fp60;
LIBINT2_REALTYPE fp4;
fp4 = 0 + src2[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = inteval->BO_z[vi] * fp4;
LIBINT2_REALTYPE fp5;
fp5 = 0 + src2[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = fp5 + fp7;
LIBINT2_REALTYPE fp32;
fp32 = 0 + src1[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = inteval->BO_y[vi] * fp32;
LIBINT2_REALTYPE fp33;
fp33 = 0 + src1[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = fp33 + fp35;
LIBINT2_REALTYPE fp63;
fp63 = fp42 * fp34;
LIBINT2_REALTYPE fp62;
fp62 = fp63 * fp6;
target[((hsi*15+13)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp8;
fp8 = 0 + src2[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = inteval->BO_z[vi] * fp8;
LIBINT2_REALTYPE fp9;
fp9 = 0 + src2[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp9 + fp11;
LIBINT2_REALTYPE fp28;
fp28 = 0 + src1[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->BO_y[vi] * fp28;
LIBINT2_REALTYPE fp29;
fp29 = 0 + src1[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = fp29 + fp31;
LIBINT2_REALTYPE fp65;
fp65 = fp42 * fp30;
LIBINT2_REALTYPE fp64;
fp64 = fp65 * fp10;
target[((hsi*15+12)*1+lsi)*1] = fp64;
LIBINT2_REALTYPE fp12;
fp12 = 0 + src2[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = inteval->BO_z[vi] * fp12;
LIBINT2_REALTYPE fp13;
fp13 = 0 + src2[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = fp13 + fp15;
LIBINT2_REALTYPE fp24;
fp24 = 0 + src1[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = inteval->BO_y[vi] * fp24;
LIBINT2_REALTYPE fp25;
fp25 = 0 + src1[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = fp25 + fp27;
LIBINT2_REALTYPE fp67;
fp67 = fp42 * fp26;
LIBINT2_REALTYPE fp66;
fp66 = fp67 * fp14;
target[((hsi*15+11)*1+lsi)*1] = fp66;
LIBINT2_REALTYPE fp16;
fp16 = 0 + src2[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = inteval->BO_z[vi] * fp16;
LIBINT2_REALTYPE fp17;
fp17 = 0 + src2[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = fp17 + fp19;
LIBINT2_REALTYPE fp20;
fp20 = 0 + src1[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->BO_y[vi] * fp20;
LIBINT2_REALTYPE fp21;
fp21 = 0 + src1[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = fp21 + fp23;
LIBINT2_REALTYPE fp69;
fp69 = fp42 * fp22;
LIBINT2_REALTYPE fp68;
fp68 = fp69 * fp18;
target[((hsi*15+10)*1+lsi)*1] = fp68;
LIBINT2_REALTYPE fp44;
fp44 = 0 + src0[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = inteval->BO_x[vi] * fp44;
LIBINT2_REALTYPE fp45;
fp45 = 0 + src0[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = fp45 + fp47;
LIBINT2_REALTYPE fp71;
fp71 = fp46 * fp38;
LIBINT2_REALTYPE fp70;
fp70 = fp71 * fp6;
target[((hsi*15+9)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp73;
fp73 = fp46 * fp34;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp10;
target[((hsi*15+8)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp75;
fp75 = fp46 * fp30;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp14;
target[((hsi*15+7)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp77;
fp77 = fp46 * fp26;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp18;
target[((hsi*15+6)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp48;
fp48 = 0 + src0[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp51;
fp51 = inteval->BO_x[vi] * fp48;
LIBINT2_REALTYPE fp49;
fp49 = 0 + src0[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = fp49 + fp51;
LIBINT2_REALTYPE fp79;
fp79 = fp50 * fp38;
LIBINT2_REALTYPE fp78;
fp78 = fp79 * fp10;
target[((hsi*15+5)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp81;
fp81 = fp50 * fp34;
LIBINT2_REALTYPE fp80;
fp80 = fp81 * fp14;
target[((hsi*15+4)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp83;
fp83 = fp50 * fp30;
LIBINT2_REALTYPE fp82;
fp82 = fp83 * fp18;
target[((hsi*15+3)*1+lsi)*1] = fp82;
LIBINT2_REALTYPE fp52;
fp52 = 0 + src0[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp55;
fp55 = inteval->BO_x[vi] * fp52;
LIBINT2_REALTYPE fp53;
fp53 = 0 + src0[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = fp53 + fp55;
LIBINT2_REALTYPE fp85;
fp85 = fp54 * fp38;
LIBINT2_REALTYPE fp84;
fp84 = fp85 * fp14;
target[((hsi*15+2)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp87;
fp87 = fp54 * fp34;
LIBINT2_REALTYPE fp86;
fp86 = fp87 * fp18;
target[((hsi*15+1)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp56;
fp56 = 0 + src0[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp59;
fp59 = inteval->BO_x[vi] * fp56;
LIBINT2_REALTYPE fp57;
fp57 = 0 + src0[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = fp57 + fp59;
LIBINT2_REALTYPE fp89;
fp89 = fp58 * fp38;
LIBINT2_REALTYPE fp88;
fp88 = fp89 * fp18;
target[((hsi*15+0)*1+lsi)*1] = fp88;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 90 */
}

#ifdef __cplusplus
};
#endif
