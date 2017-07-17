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
void CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_0_Sb__s__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*5+4)*1+lsi)*1];
LIBINT2_REALTYPE fp9;
fp9 = 0 + src1[((hsi*5+0)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = 0 + src0[((hsi*5+0)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = fp10 * fp9;
LIBINT2_REALTYPE fp15;
fp15 = fp16 * fp0;
target[((hsi*15+14)*1+lsi)*1] = fp15;
LIBINT2_REALTYPE fp1;
fp1 = 0 + src2[((hsi*5+3)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = 0 + src1[((hsi*5+1)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = fp10 * fp8;
LIBINT2_REALTYPE fp17;
fp17 = fp18 * fp1;
target[((hsi*15+13)*1+lsi)*1] = fp17;
LIBINT2_REALTYPE fp2;
fp2 = 0 + src2[((hsi*5+2)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = 0 + src1[((hsi*5+2)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = fp10 * fp7;
LIBINT2_REALTYPE fp19;
fp19 = fp20 * fp2;
target[((hsi*15+12)*1+lsi)*1] = fp19;
LIBINT2_REALTYPE fp3;
fp3 = 0 + src2[((hsi*5+1)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = 0 + src1[((hsi*5+3)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = fp10 * fp6;
LIBINT2_REALTYPE fp21;
fp21 = fp22 * fp3;
target[((hsi*15+11)*1+lsi)*1] = fp21;
LIBINT2_REALTYPE fp4;
fp4 = 0 + src2[((hsi*5+0)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = 0 + src1[((hsi*5+4)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = fp10 * fp5;
LIBINT2_REALTYPE fp23;
fp23 = fp24 * fp4;
target[((hsi*15+10)*1+lsi)*1] = fp23;
LIBINT2_REALTYPE fp11;
fp11 = 0 + src0[((hsi*5+1)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = fp11 * fp9;
LIBINT2_REALTYPE fp25;
fp25 = fp26 * fp1;
target[((hsi*15+9)*1+lsi)*1] = fp25;
LIBINT2_REALTYPE fp28;
fp28 = fp11 * fp8;
LIBINT2_REALTYPE fp27;
fp27 = fp28 * fp2;
target[((hsi*15+8)*1+lsi)*1] = fp27;
LIBINT2_REALTYPE fp30;
fp30 = fp11 * fp7;
LIBINT2_REALTYPE fp29;
fp29 = fp30 * fp3;
target[((hsi*15+7)*1+lsi)*1] = fp29;
LIBINT2_REALTYPE fp32;
fp32 = fp11 * fp6;
LIBINT2_REALTYPE fp31;
fp31 = fp32 * fp4;
target[((hsi*15+6)*1+lsi)*1] = fp31;
LIBINT2_REALTYPE fp12;
fp12 = 0 + src0[((hsi*5+2)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = fp12 * fp9;
LIBINT2_REALTYPE fp33;
fp33 = fp34 * fp2;
target[((hsi*15+5)*1+lsi)*1] = fp33;
LIBINT2_REALTYPE fp36;
fp36 = fp12 * fp8;
LIBINT2_REALTYPE fp35;
fp35 = fp36 * fp3;
target[((hsi*15+4)*1+lsi)*1] = fp35;
LIBINT2_REALTYPE fp38;
fp38 = fp12 * fp7;
LIBINT2_REALTYPE fp37;
fp37 = fp38 * fp4;
target[((hsi*15+3)*1+lsi)*1] = fp37;
LIBINT2_REALTYPE fp13;
fp13 = 0 + src0[((hsi*5+3)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = fp13 * fp9;
LIBINT2_REALTYPE fp39;
fp39 = fp40 * fp3;
target[((hsi*15+2)*1+lsi)*1] = fp39;
LIBINT2_REALTYPE fp42;
fp42 = fp13 * fp8;
LIBINT2_REALTYPE fp41;
fp41 = fp42 * fp4;
target[((hsi*15+1)*1+lsi)*1] = fp41;
LIBINT2_REALTYPE fp14;
fp14 = 0 + src0[((hsi*5+4)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = fp14 * fp9;
LIBINT2_REALTYPE fp43;
fp43 = fp44 * fp4;
target[((hsi*15+0)*1+lsi)*1] = fp43;
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
