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
void HRRPart1bra0ket0fp(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, int highdim) {

LIBINT2_REALTYPE*const  stack = target;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int hsi = 0; hsi<highdim; hsi++) {
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp57;
fp57 = inteval->CD_y[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = src0[((hsi*15+1)*1+lsi)*1] + fp57;
target[((hsi*30+1)*1+lsi)*1] = fp56;
LIBINT2_REALTYPE fp55;
fp55 = inteval->CD_z[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = src0[((hsi*15+2)*1+lsi)*1] + fp55;
target[((hsi*30+2)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp53;
fp53 = inteval->CD_x[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = src0[((hsi*15+1)*1+lsi)*1] + fp53;
target[((hsi*30+3)*1+lsi)*1] = fp52;
LIBINT2_REALTYPE fp51;
fp51 = inteval->CD_y[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = src0[((hsi*15+3)*1+lsi)*1] + fp51;
target[((hsi*30+4)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp49;
fp49 = inteval->CD_z[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = src0[((hsi*15+4)*1+lsi)*1] + fp49;
target[((hsi*30+5)*1+lsi)*1] = fp48;
LIBINT2_REALTYPE fp47;
fp47 = inteval->CD_x[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = src0[((hsi*15+2)*1+lsi)*1] + fp47;
target[((hsi*30+6)*1+lsi)*1] = fp46;
LIBINT2_REALTYPE fp45;
fp45 = inteval->CD_y[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = src0[((hsi*15+4)*1+lsi)*1] + fp45;
target[((hsi*30+7)*1+lsi)*1] = fp44;
LIBINT2_REALTYPE fp43;
fp43 = inteval->CD_z[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = src0[((hsi*15+5)*1+lsi)*1] + fp43;
target[((hsi*30+8)*1+lsi)*1] = fp42;
LIBINT2_REALTYPE fp41;
fp41 = inteval->CD_x[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = src0[((hsi*15+3)*1+lsi)*1] + fp41;
target[((hsi*30+9)*1+lsi)*1] = fp40;
LIBINT2_REALTYPE fp39;
fp39 = inteval->CD_y[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = src0[((hsi*15+6)*1+lsi)*1] + fp39;
target[((hsi*30+10)*1+lsi)*1] = fp38;
LIBINT2_REALTYPE fp37;
fp37 = inteval->CD_z[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = src0[((hsi*15+7)*1+lsi)*1] + fp37;
target[((hsi*30+11)*1+lsi)*1] = fp36;
LIBINT2_REALTYPE fp35;
fp35 = inteval->CD_x[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = src0[((hsi*15+4)*1+lsi)*1] + fp35;
target[((hsi*30+12)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp33;
fp33 = inteval->CD_y[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = src0[((hsi*15+7)*1+lsi)*1] + fp33;
target[((hsi*30+13)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp31;
fp31 = inteval->CD_z[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = src0[((hsi*15+8)*1+lsi)*1] + fp31;
target[((hsi*30+14)*1+lsi)*1] = fp30;
LIBINT2_REALTYPE fp59;
fp59 = inteval->CD_x[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = src0[((hsi*15+0)*1+lsi)*1] + fp59;
target[((hsi*30+0)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp27;
fp27 = inteval->CD_y[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = src0[((hsi*15+8)*1+lsi)*1] + fp27;
target[((hsi*30+16)*1+lsi)*1] = fp26;
LIBINT2_REALTYPE fp25;
fp25 = inteval->CD_z[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = src0[((hsi*15+9)*1+lsi)*1] + fp25;
target[((hsi*30+17)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp23;
fp23 = inteval->CD_x[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = src0[((hsi*15+6)*1+lsi)*1] + fp23;
target[((hsi*30+18)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp21;
fp21 = inteval->CD_y[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = src0[((hsi*15+10)*1+lsi)*1] + fp21;
target[((hsi*30+19)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp19;
fp19 = inteval->CD_z[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = src0[((hsi*15+11)*1+lsi)*1] + fp19;
target[((hsi*30+20)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp17;
fp17 = inteval->CD_x[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = src0[((hsi*15+7)*1+lsi)*1] + fp17;
target[((hsi*30+21)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp15;
fp15 = inteval->CD_y[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = src0[((hsi*15+11)*1+lsi)*1] + fp15;
target[((hsi*30+22)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp13;
fp13 = inteval->CD_z[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = src0[((hsi*15+12)*1+lsi)*1] + fp13;
target[((hsi*30+23)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp11;
fp11 = inteval->CD_x[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = src0[((hsi*15+8)*1+lsi)*1] + fp11;
target[((hsi*30+24)*1+lsi)*1] = fp10;
LIBINT2_REALTYPE fp9;
fp9 = inteval->CD_y[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = src0[((hsi*15+12)*1+lsi)*1] + fp9;
target[((hsi*30+25)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp7;
fp7 = inteval->CD_z[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = src0[((hsi*15+13)*1+lsi)*1] + fp7;
target[((hsi*30+26)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp5;
fp5 = inteval->CD_x[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = src0[((hsi*15+9)*1+lsi)*1] + fp5;
target[((hsi*30+27)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp3;
fp3 = inteval->CD_y[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = src0[((hsi*15+13)*1+lsi)*1] + fp3;
target[((hsi*30+28)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp1;
fp1 = inteval->CD_z[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = src0[((hsi*15+14)*1+lsi)*1] + fp1;
target[((hsi*30+29)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp29;
fp29 = inteval->CD_x[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = src0[((hsi*15+5)*1+lsi)*1] + fp29;
target[((hsi*30+15)*1+lsi)*1] = fp28;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 60 */
}

#ifdef __cplusplus
};
#endif
