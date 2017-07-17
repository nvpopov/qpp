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
void CR_aB_s__0___CartesianMultipole_sB_0_c_0_c_3_Sb__g__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp7;
fp7 = 0 + src2[((hsi*8+6)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = 0 + src2[((hsi*8+5)*1+lsi)*1];
LIBINT2_REALTYPE fp9;
fp9 = inteval->BO_z[vi] * fp14;
LIBINT2_REALTYPE fp8;
fp8 = fp7 + fp9;
LIBINT2_REALTYPE fp21;
fp21 = 0 + src2[((hsi*8+4)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->BO_z[vi] * fp21;
LIBINT2_REALTYPE fp15;
fp15 = fp14 + fp16;
LIBINT2_REALTYPE fp11;
fp11 = inteval->BO_z[vi] * fp15;
LIBINT2_REALTYPE fp10;
fp10 = fp8 + fp11;
LIBINT2_REALTYPE fp6;
fp6 = inteval->BO_z[vi] * fp10;
LIBINT2_REALTYPE fp4;
fp4 = inteval->BO_z[vi] * fp8;
LIBINT2_REALTYPE fp2;
fp2 = inteval->BO_z[vi] * fp7;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*8+7)*1+lsi)*1];
LIBINT2_REALTYPE fp1;
fp1 = fp0 + fp2;
LIBINT2_REALTYPE fp3;
fp3 = fp1 + fp4;
LIBINT2_REALTYPE fp5;
fp5 = fp3 + fp6;
LIBINT2_REALTYPE fp48;
fp48 = 0 + src1[((hsi*8+0)*1+lsi)*1];
LIBINT2_REALTYPE fp49;
fp49 = 0 + src0[((hsi*8+0)*1+lsi)*1];
LIBINT2_REALTYPE fp55;
fp55 = fp49 * fp48;
LIBINT2_REALTYPE fp54;
fp54 = fp55 * fp5;
target[((hsi*15+14)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp33;
fp33 = 0 + src2[((hsi*8+3)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->BO_z[vi] * fp33;
LIBINT2_REALTYPE fp22;
fp22 = fp21 + fp23;
LIBINT2_REALTYPE fp18;
fp18 = inteval->BO_z[vi] * fp22;
LIBINT2_REALTYPE fp17;
fp17 = fp15 + fp18;
LIBINT2_REALTYPE fp13;
fp13 = inteval->BO_z[vi] * fp17;
LIBINT2_REALTYPE fp12;
fp12 = fp10 + fp13;
LIBINT2_REALTYPE fp47;
fp47 = 0 + src1[((hsi*8+1)*1+lsi)*1];
LIBINT2_REALTYPE fp57;
fp57 = fp49 * fp47;
LIBINT2_REALTYPE fp56;
fp56 = fp57 * fp12;
target[((hsi*15+13)*1+lsi)*1] = fp56;
LIBINT2_REALTYPE fp32;
fp32 = 0 + src2[((hsi*8+2)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = inteval->BO_z[vi] * fp32;
LIBINT2_REALTYPE fp36;
fp36 = fp33 + fp37;
LIBINT2_REALTYPE fp25;
fp25 = inteval->BO_z[vi] * fp36;
LIBINT2_REALTYPE fp24;
fp24 = fp22 + fp25;
LIBINT2_REALTYPE fp20;
fp20 = inteval->BO_z[vi] * fp24;
LIBINT2_REALTYPE fp19;
fp19 = fp17 + fp20;
LIBINT2_REALTYPE fp46;
fp46 = 0 + src1[((hsi*8+2)*1+lsi)*1];
LIBINT2_REALTYPE fp59;
fp59 = fp49 * fp46;
LIBINT2_REALTYPE fp58;
fp58 = fp59 * fp19;
target[((hsi*15+12)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp31;
fp31 = 0 + src2[((hsi*8+1)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = inteval->BO_z[vi] * fp31;
LIBINT2_REALTYPE fp34;
fp34 = fp32 + fp35;
LIBINT2_REALTYPE fp41;
fp41 = inteval->BO_z[vi] * fp34;
LIBINT2_REALTYPE fp40;
fp40 = fp36 + fp41;
LIBINT2_REALTYPE fp27;
fp27 = inteval->BO_z[vi] * fp40;
LIBINT2_REALTYPE fp26;
fp26 = fp24 + fp27;
LIBINT2_REALTYPE fp45;
fp45 = 0 + src1[((hsi*8+3)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = fp49 * fp45;
LIBINT2_REALTYPE fp60;
fp60 = fp61 * fp26;
target[((hsi*15+11)*1+lsi)*1] = fp60;
LIBINT2_REALTYPE fp28;
fp28 = 0 + src2[((hsi*8+0)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->BO_z[vi] * fp28;
LIBINT2_REALTYPE fp29;
fp29 = fp31 + fp30;
LIBINT2_REALTYPE fp39;
fp39 = inteval->BO_z[vi] * fp29;
LIBINT2_REALTYPE fp38;
fp38 = fp34 + fp39;
LIBINT2_REALTYPE fp43;
fp43 = inteval->BO_z[vi] * fp38;
LIBINT2_REALTYPE fp42;
fp42 = fp40 + fp43;
LIBINT2_REALTYPE fp44;
fp44 = 0 + src1[((hsi*8+4)*1+lsi)*1];
LIBINT2_REALTYPE fp63;
fp63 = fp49 * fp44;
LIBINT2_REALTYPE fp62;
fp62 = fp63 * fp42;
target[((hsi*15+10)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp50;
fp50 = 0 + src0[((hsi*8+1)*1+lsi)*1];
LIBINT2_REALTYPE fp65;
fp65 = fp50 * fp48;
LIBINT2_REALTYPE fp64;
fp64 = fp65 * fp12;
target[((hsi*15+9)*1+lsi)*1] = fp64;
LIBINT2_REALTYPE fp67;
fp67 = fp50 * fp47;
LIBINT2_REALTYPE fp66;
fp66 = fp67 * fp19;
target[((hsi*15+8)*1+lsi)*1] = fp66;
LIBINT2_REALTYPE fp69;
fp69 = fp50 * fp46;
LIBINT2_REALTYPE fp68;
fp68 = fp69 * fp26;
target[((hsi*15+7)*1+lsi)*1] = fp68;
LIBINT2_REALTYPE fp71;
fp71 = fp50 * fp45;
LIBINT2_REALTYPE fp70;
fp70 = fp71 * fp42;
target[((hsi*15+6)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp51;
fp51 = 0 + src0[((hsi*8+2)*1+lsi)*1];
LIBINT2_REALTYPE fp73;
fp73 = fp51 * fp48;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp19;
target[((hsi*15+5)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp75;
fp75 = fp51 * fp47;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp26;
target[((hsi*15+4)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp77;
fp77 = fp51 * fp46;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp42;
target[((hsi*15+3)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp52;
fp52 = 0 + src0[((hsi*8+3)*1+lsi)*1];
LIBINT2_REALTYPE fp79;
fp79 = fp52 * fp48;
LIBINT2_REALTYPE fp78;
fp78 = fp79 * fp26;
target[((hsi*15+2)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp81;
fp81 = fp52 * fp47;
LIBINT2_REALTYPE fp80;
fp80 = fp81 * fp42;
target[((hsi*15+1)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp53;
fp53 = 0 + src0[((hsi*8+4)*1+lsi)*1];
LIBINT2_REALTYPE fp83;
fp83 = fp53 * fp48;
LIBINT2_REALTYPE fp82;
fp82 = fp83 * fp42;
target[((hsi*15+0)*1+lsi)*1] = fp82;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 84 */
}

#ifdef __cplusplus
};
#endif
