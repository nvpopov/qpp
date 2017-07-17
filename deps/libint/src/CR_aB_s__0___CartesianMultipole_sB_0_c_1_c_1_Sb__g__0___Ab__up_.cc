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
void CR_aB_s__0___CartesianMultipole_sB_0_c_1_c_1_Sb__g__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp3;
fp3 = 0 + src2[((hsi*7+4)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->BO_z[vi] * fp3;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*7+5)*1+lsi)*1];
LIBINT2_REALTYPE fp1;
fp1 = fp0 + fp2;
LIBINT2_REALTYPE fp29;
fp29 = 0 + src1[((hsi*7+1)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = 0 + src1[((hsi*7+0)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->BO_y[vi] * fp28;
LIBINT2_REALTYPE fp30;
fp30 = fp29 + fp31;
LIBINT2_REALTYPE fp32;
fp32 = 0 + src0[((hsi*7+0)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = fp32 * fp30;
LIBINT2_REALTYPE fp37;
fp37 = fp38 * fp1;
target[((hsi*15+14)*1+lsi)*1] = fp37;
LIBINT2_REALTYPE fp6;
fp6 = 0 + src2[((hsi*7+3)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = inteval->BO_z[vi] * fp6;
LIBINT2_REALTYPE fp4;
fp4 = fp3 + fp5;
LIBINT2_REALTYPE fp25;
fp25 = 0 + src1[((hsi*7+2)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = inteval->BO_y[vi] * fp29;
LIBINT2_REALTYPE fp26;
fp26 = fp25 + fp27;
LIBINT2_REALTYPE fp40;
fp40 = fp32 * fp26;
LIBINT2_REALTYPE fp39;
fp39 = fp40 * fp4;
target[((hsi*15+13)*1+lsi)*1] = fp39;
LIBINT2_REALTYPE fp9;
fp9 = 0 + src2[((hsi*7+2)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->BO_z[vi] * fp9;
LIBINT2_REALTYPE fp7;
fp7 = fp6 + fp8;
LIBINT2_REALTYPE fp22;
fp22 = 0 + src1[((hsi*7+3)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->BO_y[vi] * fp25;
LIBINT2_REALTYPE fp23;
fp23 = fp22 + fp24;
LIBINT2_REALTYPE fp42;
fp42 = fp32 * fp23;
LIBINT2_REALTYPE fp41;
fp41 = fp42 * fp7;
target[((hsi*15+12)*1+lsi)*1] = fp41;
LIBINT2_REALTYPE fp13;
fp13 = 0 + src2[((hsi*7+1)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = inteval->BO_z[vi] * fp13;
LIBINT2_REALTYPE fp10;
fp10 = fp9 + fp11;
LIBINT2_REALTYPE fp19;
fp19 = 0 + src1[((hsi*7+4)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = inteval->BO_y[vi] * fp22;
LIBINT2_REALTYPE fp20;
fp20 = fp19 + fp21;
LIBINT2_REALTYPE fp44;
fp44 = fp32 * fp20;
LIBINT2_REALTYPE fp43;
fp43 = fp44 * fp10;
target[((hsi*15+11)*1+lsi)*1] = fp43;
LIBINT2_REALTYPE fp12;
fp12 = 0 + src2[((hsi*7+0)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = inteval->BO_z[vi] * fp12;
LIBINT2_REALTYPE fp14;
fp14 = fp13 + fp15;
LIBINT2_REALTYPE fp18;
fp18 = inteval->BO_y[vi] * fp19;
LIBINT2_REALTYPE fp16;
fp16 = 0 + src1[((hsi*7+5)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp16 + fp18;
LIBINT2_REALTYPE fp46;
fp46 = fp32 * fp17;
LIBINT2_REALTYPE fp45;
fp45 = fp46 * fp14;
target[((hsi*15+10)*1+lsi)*1] = fp45;
LIBINT2_REALTYPE fp33;
fp33 = 0 + src0[((hsi*7+1)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = fp33 * fp30;
LIBINT2_REALTYPE fp47;
fp47 = fp48 * fp4;
target[((hsi*15+9)*1+lsi)*1] = fp47;
LIBINT2_REALTYPE fp50;
fp50 = fp33 * fp26;
LIBINT2_REALTYPE fp49;
fp49 = fp50 * fp7;
target[((hsi*15+8)*1+lsi)*1] = fp49;
LIBINT2_REALTYPE fp52;
fp52 = fp33 * fp23;
LIBINT2_REALTYPE fp51;
fp51 = fp52 * fp10;
target[((hsi*15+7)*1+lsi)*1] = fp51;
LIBINT2_REALTYPE fp54;
fp54 = fp33 * fp20;
LIBINT2_REALTYPE fp53;
fp53 = fp54 * fp14;
target[((hsi*15+6)*1+lsi)*1] = fp53;
LIBINT2_REALTYPE fp34;
fp34 = 0 + src0[((hsi*7+2)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = fp34 * fp30;
LIBINT2_REALTYPE fp55;
fp55 = fp56 * fp7;
target[((hsi*15+5)*1+lsi)*1] = fp55;
LIBINT2_REALTYPE fp58;
fp58 = fp34 * fp26;
LIBINT2_REALTYPE fp57;
fp57 = fp58 * fp10;
target[((hsi*15+4)*1+lsi)*1] = fp57;
LIBINT2_REALTYPE fp60;
fp60 = fp34 * fp23;
LIBINT2_REALTYPE fp59;
fp59 = fp60 * fp14;
target[((hsi*15+3)*1+lsi)*1] = fp59;
LIBINT2_REALTYPE fp35;
fp35 = 0 + src0[((hsi*7+3)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = fp35 * fp30;
LIBINT2_REALTYPE fp61;
fp61 = fp62 * fp10;
target[((hsi*15+2)*1+lsi)*1] = fp61;
LIBINT2_REALTYPE fp64;
fp64 = fp35 * fp26;
LIBINT2_REALTYPE fp63;
fp63 = fp64 * fp14;
target[((hsi*15+1)*1+lsi)*1] = fp63;
LIBINT2_REALTYPE fp36;
fp36 = 0 + src0[((hsi*7+4)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = fp36 * fp30;
LIBINT2_REALTYPE fp65;
fp65 = fp66 * fp14;
target[((hsi*15+0)*1+lsi)*1] = fp65;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 67 */
}

#ifdef __cplusplus
};
#endif
