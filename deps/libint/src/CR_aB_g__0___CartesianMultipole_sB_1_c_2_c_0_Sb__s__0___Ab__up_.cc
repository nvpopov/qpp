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
void CR_aB_g__0___CartesianMultipole_sB_1_c_2_c_0_Sb__s__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = 0 + src1[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp41;
fp41 = 0 + src1[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp45;
fp45 = inteval->BO_y[vi] * fp41;
LIBINT2_REALTYPE fp44;
fp44 = fp42 + fp45;
LIBINT2_REALTYPE fp49;
fp49 = inteval->BO_y[vi] * fp44;
LIBINT2_REALTYPE fp47;
fp47 = inteval->BO_y[vi] * fp42;
LIBINT2_REALTYPE fp43;
fp43 = 0 + src1[((hsi*20+2)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = fp43 + fp47;
LIBINT2_REALTYPE fp48;
fp48 = fp46 + fp49;
LIBINT2_REALTYPE fp50;
fp50 = 0 + src0[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp53;
fp53 = inteval->BO_x[vi] * fp50;
LIBINT2_REALTYPE fp51;
fp51 = 0 + src0[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = fp51 + fp53;
LIBINT2_REALTYPE fp71;
fp71 = fp52 * fp48;
LIBINT2_REALTYPE fp70;
fp70 = fp71 * fp0;
target[((hsi*15+14)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp1;
fp1 = 0 + src2[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = 0 + src1[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = 0 + src1[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = inteval->BO_y[vi] * fp32;
LIBINT2_REALTYPE fp35;
fp35 = fp33 + fp36;
LIBINT2_REALTYPE fp40;
fp40 = inteval->BO_y[vi] * fp35;
LIBINT2_REALTYPE fp38;
fp38 = inteval->BO_y[vi] * fp33;
LIBINT2_REALTYPE fp34;
fp34 = 0 + src1[((hsi*20+6)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = fp34 + fp38;
LIBINT2_REALTYPE fp39;
fp39 = fp37 + fp40;
LIBINT2_REALTYPE fp73;
fp73 = fp52 * fp39;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp1;
target[((hsi*15+13)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp2;
fp2 = 0 + src2[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = 0 + src1[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = 0 + src1[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = inteval->BO_y[vi] * fp23;
LIBINT2_REALTYPE fp26;
fp26 = fp24 + fp27;
LIBINT2_REALTYPE fp31;
fp31 = inteval->BO_y[vi] * fp26;
LIBINT2_REALTYPE fp29;
fp29 = inteval->BO_y[vi] * fp24;
LIBINT2_REALTYPE fp25;
fp25 = 0 + src1[((hsi*20+10)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = fp25 + fp29;
LIBINT2_REALTYPE fp30;
fp30 = fp28 + fp31;
LIBINT2_REALTYPE fp75;
fp75 = fp52 * fp30;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp2;
target[((hsi*15+12)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp3;
fp3 = 0 + src2[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = 0 + src1[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = 0 + src1[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = inteval->BO_y[vi] * fp14;
LIBINT2_REALTYPE fp17;
fp17 = fp15 + fp18;
LIBINT2_REALTYPE fp22;
fp22 = inteval->BO_y[vi] * fp17;
LIBINT2_REALTYPE fp20;
fp20 = inteval->BO_y[vi] * fp15;
LIBINT2_REALTYPE fp16;
fp16 = 0 + src1[((hsi*20+14)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = fp16 + fp20;
LIBINT2_REALTYPE fp21;
fp21 = fp19 + fp22;
LIBINT2_REALTYPE fp77;
fp77 = fp52 * fp21;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp3;
target[((hsi*15+11)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp4;
fp4 = 0 + src2[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = 0 + src1[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = 0 + src1[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp9;
fp9 = inteval->BO_y[vi] * fp5;
LIBINT2_REALTYPE fp8;
fp8 = fp6 + fp9;
LIBINT2_REALTYPE fp13;
fp13 = inteval->BO_y[vi] * fp8;
LIBINT2_REALTYPE fp11;
fp11 = inteval->BO_y[vi] * fp6;
LIBINT2_REALTYPE fp7;
fp7 = 0 + src1[((hsi*20+18)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp7 + fp11;
LIBINT2_REALTYPE fp12;
fp12 = fp10 + fp13;
LIBINT2_REALTYPE fp79;
fp79 = fp52 * fp12;
LIBINT2_REALTYPE fp78;
fp78 = fp79 * fp4;
target[((hsi*15+10)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp54;
fp54 = 0 + src0[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp57;
fp57 = inteval->BO_x[vi] * fp54;
LIBINT2_REALTYPE fp55;
fp55 = 0 + src0[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = fp55 + fp57;
LIBINT2_REALTYPE fp81;
fp81 = fp56 * fp48;
LIBINT2_REALTYPE fp80;
fp80 = fp81 * fp1;
target[((hsi*15+9)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp83;
fp83 = fp56 * fp39;
LIBINT2_REALTYPE fp82;
fp82 = fp83 * fp2;
target[((hsi*15+8)*1+lsi)*1] = fp82;
LIBINT2_REALTYPE fp85;
fp85 = fp56 * fp30;
LIBINT2_REALTYPE fp84;
fp84 = fp85 * fp3;
target[((hsi*15+7)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp87;
fp87 = fp56 * fp21;
LIBINT2_REALTYPE fp86;
fp86 = fp87 * fp4;
target[((hsi*15+6)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp58;
fp58 = 0 + src0[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = inteval->BO_x[vi] * fp58;
LIBINT2_REALTYPE fp59;
fp59 = 0 + src0[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = fp59 + fp61;
LIBINT2_REALTYPE fp89;
fp89 = fp60 * fp48;
LIBINT2_REALTYPE fp88;
fp88 = fp89 * fp2;
target[((hsi*15+5)*1+lsi)*1] = fp88;
LIBINT2_REALTYPE fp91;
fp91 = fp60 * fp39;
LIBINT2_REALTYPE fp90;
fp90 = fp91 * fp3;
target[((hsi*15+4)*1+lsi)*1] = fp90;
LIBINT2_REALTYPE fp93;
fp93 = fp60 * fp30;
LIBINT2_REALTYPE fp92;
fp92 = fp93 * fp4;
target[((hsi*15+3)*1+lsi)*1] = fp92;
LIBINT2_REALTYPE fp62;
fp62 = 0 + src0[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp65;
fp65 = inteval->BO_x[vi] * fp62;
LIBINT2_REALTYPE fp63;
fp63 = 0 + src0[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = fp63 + fp65;
LIBINT2_REALTYPE fp95;
fp95 = fp64 * fp48;
LIBINT2_REALTYPE fp94;
fp94 = fp95 * fp3;
target[((hsi*15+2)*1+lsi)*1] = fp94;
LIBINT2_REALTYPE fp97;
fp97 = fp64 * fp39;
LIBINT2_REALTYPE fp96;
fp96 = fp97 * fp4;
target[((hsi*15+1)*1+lsi)*1] = fp96;
LIBINT2_REALTYPE fp66;
fp66 = 0 + src0[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp69;
fp69 = inteval->BO_x[vi] * fp66;
LIBINT2_REALTYPE fp67;
fp67 = 0 + src0[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp68;
fp68 = fp67 + fp69;
LIBINT2_REALTYPE fp99;
fp99 = fp68 * fp48;
LIBINT2_REALTYPE fp98;
fp98 = fp99 * fp4;
target[((hsi*15+0)*1+lsi)*1] = fp98;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 100 */
}

#ifdef __cplusplus
};
#endif
