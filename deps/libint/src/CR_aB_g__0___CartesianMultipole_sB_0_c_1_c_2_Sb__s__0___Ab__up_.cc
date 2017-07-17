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
void CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_2_Sb__s__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp1;
fp1 = 0 + src2[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->BO_z[vi] * fp0;
LIBINT2_REALTYPE fp3;
fp3 = fp1 + fp4;
LIBINT2_REALTYPE fp8;
fp8 = inteval->BO_z[vi] * fp3;
LIBINT2_REALTYPE fp6;
fp6 = inteval->BO_z[vi] * fp1;
LIBINT2_REALTYPE fp2;
fp2 = 0 + src2[((hsi*20+18)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = fp2 + fp6;
LIBINT2_REALTYPE fp7;
fp7 = fp5 + fp8;
LIBINT2_REALTYPE fp61;
fp61 = 0 + src1[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = inteval->BO_y[vi] * fp61;
LIBINT2_REALTYPE fp62;
fp62 = 0 + src1[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp63;
fp63 = fp62 + fp64;
LIBINT2_REALTYPE fp65;
fp65 = 0 + src0[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp71;
fp71 = fp65 * fp63;
LIBINT2_REALTYPE fp70;
fp70 = fp71 * fp7;
target[((hsi*15+14)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp10;
fp10 = 0 + src2[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp9;
fp9 = 0 + src2[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = inteval->BO_z[vi] * fp9;
LIBINT2_REALTYPE fp12;
fp12 = fp10 + fp13;
LIBINT2_REALTYPE fp17;
fp17 = inteval->BO_z[vi] * fp12;
LIBINT2_REALTYPE fp15;
fp15 = inteval->BO_z[vi] * fp10;
LIBINT2_REALTYPE fp11;
fp11 = 0 + src2[((hsi*20+14)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = fp11 + fp15;
LIBINT2_REALTYPE fp16;
fp16 = fp14 + fp17;
LIBINT2_REALTYPE fp57;
fp57 = 0 + src1[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = inteval->BO_y[vi] * fp57;
LIBINT2_REALTYPE fp58;
fp58 = 0 + src1[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp59;
fp59 = fp58 + fp60;
LIBINT2_REALTYPE fp73;
fp73 = fp65 * fp59;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp16;
target[((hsi*15+13)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp19;
fp19 = 0 + src2[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = 0 + src2[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = inteval->BO_z[vi] * fp18;
LIBINT2_REALTYPE fp21;
fp21 = fp19 + fp22;
LIBINT2_REALTYPE fp26;
fp26 = inteval->BO_z[vi] * fp21;
LIBINT2_REALTYPE fp24;
fp24 = inteval->BO_z[vi] * fp19;
LIBINT2_REALTYPE fp20;
fp20 = 0 + src2[((hsi*20+10)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = fp20 + fp24;
LIBINT2_REALTYPE fp25;
fp25 = fp23 + fp26;
LIBINT2_REALTYPE fp53;
fp53 = 0 + src1[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = inteval->BO_y[vi] * fp53;
LIBINT2_REALTYPE fp54;
fp54 = 0 + src1[((hsi*20+9)*1+lsi)*1];
LIBINT2_REALTYPE fp55;
fp55 = fp54 + fp56;
LIBINT2_REALTYPE fp75;
fp75 = fp65 * fp55;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp25;
target[((hsi*15+12)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp28;
fp28 = 0 + src2[((hsi*20+5)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = 0 + src2[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->BO_z[vi] * fp27;
LIBINT2_REALTYPE fp30;
fp30 = fp28 + fp31;
LIBINT2_REALTYPE fp35;
fp35 = inteval->BO_z[vi] * fp30;
LIBINT2_REALTYPE fp33;
fp33 = inteval->BO_z[vi] * fp28;
LIBINT2_REALTYPE fp29;
fp29 = 0 + src2[((hsi*20+6)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = fp29 + fp33;
LIBINT2_REALTYPE fp34;
fp34 = fp32 + fp35;
LIBINT2_REALTYPE fp49;
fp49 = 0 + src1[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = inteval->BO_y[vi] * fp49;
LIBINT2_REALTYPE fp50;
fp50 = 0 + src1[((hsi*20+13)*1+lsi)*1];
LIBINT2_REALTYPE fp51;
fp51 = fp50 + fp52;
LIBINT2_REALTYPE fp77;
fp77 = fp65 * fp51;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp34;
target[((hsi*15+11)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp37;
fp37 = 0 + src2[((hsi*20+1)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = 0 + src2[((hsi*20+0)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = inteval->BO_z[vi] * fp36;
LIBINT2_REALTYPE fp39;
fp39 = fp37 + fp40;
LIBINT2_REALTYPE fp44;
fp44 = inteval->BO_z[vi] * fp39;
LIBINT2_REALTYPE fp42;
fp42 = inteval->BO_z[vi] * fp37;
LIBINT2_REALTYPE fp38;
fp38 = 0 + src2[((hsi*20+2)*1+lsi)*1];
LIBINT2_REALTYPE fp41;
fp41 = fp38 + fp42;
LIBINT2_REALTYPE fp43;
fp43 = fp41 + fp44;
LIBINT2_REALTYPE fp45;
fp45 = 0 + src1[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = inteval->BO_y[vi] * fp45;
LIBINT2_REALTYPE fp46;
fp46 = 0 + src1[((hsi*20+17)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = fp46 + fp48;
LIBINT2_REALTYPE fp79;
fp79 = fp65 * fp47;
LIBINT2_REALTYPE fp78;
fp78 = fp79 * fp43;
target[((hsi*15+10)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp66;
fp66 = 0 + src0[((hsi*20+4)*1+lsi)*1];
LIBINT2_REALTYPE fp81;
fp81 = fp66 * fp63;
LIBINT2_REALTYPE fp80;
fp80 = fp81 * fp16;
target[((hsi*15+9)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp83;
fp83 = fp66 * fp59;
LIBINT2_REALTYPE fp82;
fp82 = fp83 * fp25;
target[((hsi*15+8)*1+lsi)*1] = fp82;
LIBINT2_REALTYPE fp85;
fp85 = fp66 * fp55;
LIBINT2_REALTYPE fp84;
fp84 = fp85 * fp34;
target[((hsi*15+7)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp87;
fp87 = fp66 * fp51;
LIBINT2_REALTYPE fp86;
fp86 = fp87 * fp43;
target[((hsi*15+6)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp67;
fp67 = 0 + src0[((hsi*20+8)*1+lsi)*1];
LIBINT2_REALTYPE fp89;
fp89 = fp67 * fp63;
LIBINT2_REALTYPE fp88;
fp88 = fp89 * fp25;
target[((hsi*15+5)*1+lsi)*1] = fp88;
LIBINT2_REALTYPE fp91;
fp91 = fp67 * fp59;
LIBINT2_REALTYPE fp90;
fp90 = fp91 * fp34;
target[((hsi*15+4)*1+lsi)*1] = fp90;
LIBINT2_REALTYPE fp93;
fp93 = fp67 * fp55;
LIBINT2_REALTYPE fp92;
fp92 = fp93 * fp43;
target[((hsi*15+3)*1+lsi)*1] = fp92;
LIBINT2_REALTYPE fp68;
fp68 = 0 + src0[((hsi*20+12)*1+lsi)*1];
LIBINT2_REALTYPE fp95;
fp95 = fp68 * fp63;
LIBINT2_REALTYPE fp94;
fp94 = fp95 * fp34;
target[((hsi*15+2)*1+lsi)*1] = fp94;
LIBINT2_REALTYPE fp97;
fp97 = fp68 * fp59;
LIBINT2_REALTYPE fp96;
fp96 = fp97 * fp43;
target[((hsi*15+1)*1+lsi)*1] = fp96;
LIBINT2_REALTYPE fp69;
fp69 = 0 + src0[((hsi*20+16)*1+lsi)*1];
LIBINT2_REALTYPE fp99;
fp99 = fp69 * fp63;
LIBINT2_REALTYPE fp98;
fp98 = fp99 * fp43;
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
