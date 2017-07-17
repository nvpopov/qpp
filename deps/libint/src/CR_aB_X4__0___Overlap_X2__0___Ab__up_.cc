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
void CR_aB_X4__0___Overlap_X2__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
target[((hsi*15+0)*1+lsi)*1] = inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp67;
fp67 = inteval->PB_x[vi] * target[((hsi*15+0)*1+lsi)*1];
target[((hsi*15+1)*1+lsi)*1] = fp67;
LIBINT2_REALTYPE fp62;
fp62 = inteval->PA_x[vi] * target[((hsi*15+0)*1+lsi)*1];
target[((hsi*15+3)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp45;
fp45 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp44;
fp44 = fp45 * target[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp47;
fp47 = fp48 * target[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp59;
fp59 = fp60 * target[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = inteval->PA_x[vi] * target[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = fp61 + fp59;
target[((hsi*15+4)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp49;
fp49 = inteval->PA_x[vi] * target[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = fp49 + fp47;
LIBINT2_REALTYPE fp43;
fp43 = fp46 + fp44;
target[((hsi*15+7)*1+lsi)*1] = fp43;
LIBINT2_REALTYPE fp52;
fp52 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp51;
fp51 = fp52 * target[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp53;
fp53 = inteval->PA_x[vi] * target[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = fp53 + fp51;
target[((hsi*15+6)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp27;
fp27 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp26;
fp26 = fp27 * target[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp29;
fp29 = fp30 * target[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->PA_x[vi] * target[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = fp31 + fp29;
LIBINT2_REALTYPE fp25;
fp25 = fp28 + fp26;
target[((hsi*15+10)*1+lsi)*1] = fp25;
LIBINT2_REALTYPE fp34;
fp34 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp33;
fp33 = fp34 * target[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = inteval->PA_x[vi] * target[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = fp35 + fp33;
target[((hsi*15+9)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp38;
fp38 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp37;
fp37 = fp38 * target[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp65;
fp65 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp64;
fp64 = fp65 * target[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = inteval->PB_x[vi] * target[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp63;
fp63 = fp66 + fp64;
target[((hsi*15+2)*1+lsi)*1] = fp63;
LIBINT2_REALTYPE fp41;
fp41 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp40;
fp40 = fp41 * target[((hsi*15+2)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp55;
fp55 = fp56 * target[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp57;
fp57 = inteval->PA_x[vi] * target[((hsi*15+2)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = fp57 + fp55;
target[((hsi*15+5)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp42;
fp42 = inteval->PA_x[vi] * target[((hsi*15+5)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = fp42 + fp40;
LIBINT2_REALTYPE fp36;
fp36 = fp39 + fp37;
target[((hsi*15+8)*1+lsi)*1] = fp36;
LIBINT2_REALTYPE fp20;
fp20 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp19;
fp19 = fp20 * target[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp22;
fp22 = fp23 * target[((hsi*15+5)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->PA_x[vi] * target[((hsi*15+8)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = fp24 + fp22;
LIBINT2_REALTYPE fp18;
fp18 = fp21 + fp19;
target[((hsi*15+11)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp2;
fp2 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp2 * target[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp4;
fp4 = fp5 * target[((hsi*15+8)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_x[vi] * target[((hsi*15+11)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = fp6 + fp4;
LIBINT2_REALTYPE fp0;
fp0 = fp3 + fp1;
target[((hsi*15+14)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp9;
fp9 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp8;
fp8 = fp9 * target[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp11;
fp11 = fp12 * target[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = inteval->PA_x[vi] * target[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp13 + fp11;
LIBINT2_REALTYPE fp7;
fp7 = fp10 + fp8;
target[((hsi*15+13)*1+lsi)*1] = fp7;
LIBINT2_REALTYPE fp16;
fp16 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp15;
fp15 = fp16 * target[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = inteval->PA_x[vi] * target[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = fp17 + fp15;
target[((hsi*15+12)*1+lsi)*1] = fp14;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 68 */
}

#ifdef __cplusplus
};
#endif
