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
void CR_aB_Z2__0___Overlap_Z5__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
target[((hsi*18+0)*1+lsi)*1] = inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp76;
fp76 = inteval->PB_z[vi] * target[((hsi*18+0)*1+lsi)*1];
target[((hsi*18+1)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp74;
fp74 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp73;
fp73 = fp74 * target[((hsi*18+0)*1+lsi)*1];
LIBINT2_REALTYPE fp75;
fp75 = inteval->PB_z[vi] * target[((hsi*18+1)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = fp75 + fp73;
target[((hsi*18+2)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp70;
fp70 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp69;
fp69 = fp70 * target[((hsi*18+1)*1+lsi)*1];
LIBINT2_REALTYPE fp71;
fp71 = inteval->PB_z[vi] * target[((hsi*18+2)*1+lsi)*1];
LIBINT2_REALTYPE fp68;
fp68 = fp71 + fp69;
target[((hsi*18+3)*1+lsi)*1] = fp68;
LIBINT2_REALTYPE fp66;
fp66 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp65;
fp65 = fp66 * target[((hsi*18+2)*1+lsi)*1];
LIBINT2_REALTYPE fp67;
fp67 = inteval->PB_z[vi] * target[((hsi*18+3)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = fp67 + fp65;
target[((hsi*18+4)*1+lsi)*1] = fp64;
LIBINT2_REALTYPE fp62;
fp62 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp61;
fp61 = fp62 * target[((hsi*18+3)*1+lsi)*1];
LIBINT2_REALTYPE fp63;
fp63 = inteval->PB_z[vi] * target[((hsi*18+4)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = fp63 + fp61;
target[((hsi*18+5)*1+lsi)*1] = fp60;
LIBINT2_REALTYPE fp59;
fp59 = inteval->PA_z[vi] * target[((hsi*18+0)*1+lsi)*1];
target[((hsi*18+6)*1+lsi)*1] = fp59;
LIBINT2_REALTYPE fp57;
fp57 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp56;
fp56 = fp57 * target[((hsi*18+0)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = inteval->PA_z[vi] * target[((hsi*18+1)*1+lsi)*1];
LIBINT2_REALTYPE fp55;
fp55 = fp58 + fp56;
target[((hsi*18+7)*1+lsi)*1] = fp55;
LIBINT2_REALTYPE fp53;
fp53 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp52;
fp52 = fp53 * target[((hsi*18+1)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = inteval->PA_z[vi] * target[((hsi*18+2)*1+lsi)*1];
LIBINT2_REALTYPE fp51;
fp51 = fp54 + fp52;
target[((hsi*18+8)*1+lsi)*1] = fp51;
LIBINT2_REALTYPE fp45;
fp45 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp44;
fp44 = fp45 * target[((hsi*18+3)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = inteval->PA_z[vi] * target[((hsi*18+4)*1+lsi)*1];
LIBINT2_REALTYPE fp43;
fp43 = fp46 + fp44;
target[((hsi*18+10)*1+lsi)*1] = fp43;
LIBINT2_REALTYPE fp49;
fp49 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp48;
fp48 = fp49 * target[((hsi*18+2)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = inteval->PA_z[vi] * target[((hsi*18+3)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = fp50 + fp48;
target[((hsi*18+9)*1+lsi)*1] = fp47;
LIBINT2_REALTYPE fp41;
fp41 = 5 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp40;
fp40 = fp41 * target[((hsi*18+4)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = inteval->PA_z[vi] * target[((hsi*18+5)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = fp42 + fp40;
target[((hsi*18+11)*1+lsi)*1] = fp39;
LIBINT2_REALTYPE fp37;
fp37 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp36;
fp36 = fp37 * target[((hsi*18+0)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = inteval->PA_z[vi] * target[((hsi*18+6)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = fp38 + fp36;
target[((hsi*18+12)*1+lsi)*1] = fp35;
LIBINT2_REALTYPE fp30;
fp30 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp29;
fp29 = fp30 * target[((hsi*18+6)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp32;
fp32 = fp33 * target[((hsi*18+1)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->PA_z[vi] * target[((hsi*18+7)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = fp34 + fp32;
LIBINT2_REALTYPE fp28;
fp28 = fp31 + fp29;
target[((hsi*18+13)*1+lsi)*1] = fp28;
LIBINT2_REALTYPE fp23;
fp23 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp22;
fp22 = fp23 * target[((hsi*18+7)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp25;
fp25 = fp26 * target[((hsi*18+2)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = inteval->PA_z[vi] * target[((hsi*18+8)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = fp27 + fp25;
LIBINT2_REALTYPE fp21;
fp21 = fp24 + fp22;
target[((hsi*18+14)*1+lsi)*1] = fp21;
LIBINT2_REALTYPE fp16;
fp16 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp15;
fp15 = fp16 * target[((hsi*18+8)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp18;
fp18 = fp19 * target[((hsi*18+3)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = inteval->PA_z[vi] * target[((hsi*18+9)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp20 + fp18;
LIBINT2_REALTYPE fp14;
fp14 = fp17 + fp15;
target[((hsi*18+15)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp9;
fp9 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp8;
fp8 = fp9 * target[((hsi*18+9)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp11;
fp11 = fp12 * target[((hsi*18+4)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = inteval->PA_z[vi] * target[((hsi*18+10)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp13 + fp11;
LIBINT2_REALTYPE fp7;
fp7 = fp10 + fp8;
target[((hsi*18+16)*1+lsi)*1] = fp7;
LIBINT2_REALTYPE fp2;
fp2 = 5 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp2 * target[((hsi*18+10)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp4;
fp4 = fp5 * target[((hsi*18+5)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_z[vi] * target[((hsi*18+11)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = fp6 + fp4;
LIBINT2_REALTYPE fp0;
fp0 = fp3 + fp1;
target[((hsi*18+17)*1+lsi)*1] = fp0;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 77 */
}

#ifdef __cplusplus
};
#endif
