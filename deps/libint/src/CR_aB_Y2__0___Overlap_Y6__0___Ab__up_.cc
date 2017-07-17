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
void CR_aB_Y2__0___Overlap_Y6__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
target[((hsi*21+0)*1+lsi)*1] = inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp91;
fp91 = inteval->PB_y[vi] * target[((hsi*21+0)*1+lsi)*1];
target[((hsi*21+1)*1+lsi)*1] = fp91;
LIBINT2_REALTYPE fp89;
fp89 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp88;
fp88 = fp89 * target[((hsi*21+0)*1+lsi)*1];
LIBINT2_REALTYPE fp90;
fp90 = inteval->PB_y[vi] * target[((hsi*21+1)*1+lsi)*1];
LIBINT2_REALTYPE fp87;
fp87 = fp90 + fp88;
target[((hsi*21+2)*1+lsi)*1] = fp87;
LIBINT2_REALTYPE fp85;
fp85 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp84;
fp84 = fp85 * target[((hsi*21+1)*1+lsi)*1];
LIBINT2_REALTYPE fp86;
fp86 = inteval->PB_y[vi] * target[((hsi*21+2)*1+lsi)*1];
LIBINT2_REALTYPE fp83;
fp83 = fp86 + fp84;
target[((hsi*21+3)*1+lsi)*1] = fp83;
LIBINT2_REALTYPE fp81;
fp81 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp80;
fp80 = fp81 * target[((hsi*21+2)*1+lsi)*1];
LIBINT2_REALTYPE fp82;
fp82 = inteval->PB_y[vi] * target[((hsi*21+3)*1+lsi)*1];
LIBINT2_REALTYPE fp79;
fp79 = fp82 + fp80;
target[((hsi*21+4)*1+lsi)*1] = fp79;
LIBINT2_REALTYPE fp77;
fp77 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp76;
fp76 = fp77 * target[((hsi*21+3)*1+lsi)*1];
LIBINT2_REALTYPE fp78;
fp78 = inteval->PB_y[vi] * target[((hsi*21+4)*1+lsi)*1];
LIBINT2_REALTYPE fp75;
fp75 = fp78 + fp76;
target[((hsi*21+5)*1+lsi)*1] = fp75;
LIBINT2_REALTYPE fp73;
fp73 = 5 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp72;
fp72 = fp73 * target[((hsi*21+4)*1+lsi)*1];
LIBINT2_REALTYPE fp74;
fp74 = inteval->PB_y[vi] * target[((hsi*21+5)*1+lsi)*1];
LIBINT2_REALTYPE fp71;
fp71 = fp74 + fp72;
target[((hsi*21+6)*1+lsi)*1] = fp71;
LIBINT2_REALTYPE fp70;
fp70 = inteval->PA_y[vi] * target[((hsi*21+0)*1+lsi)*1];
target[((hsi*21+7)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp68;
fp68 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp67;
fp67 = fp68 * target[((hsi*21+0)*1+lsi)*1];
LIBINT2_REALTYPE fp69;
fp69 = inteval->PA_y[vi] * target[((hsi*21+1)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = fp69 + fp67;
target[((hsi*21+8)*1+lsi)*1] = fp66;
LIBINT2_REALTYPE fp64;
fp64 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp63;
fp63 = fp64 * target[((hsi*21+1)*1+lsi)*1];
LIBINT2_REALTYPE fp65;
fp65 = inteval->PA_y[vi] * target[((hsi*21+2)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = fp65 + fp63;
target[((hsi*21+9)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp56;
fp56 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp55;
fp55 = fp56 * target[((hsi*21+3)*1+lsi)*1];
LIBINT2_REALTYPE fp57;
fp57 = inteval->PA_y[vi] * target[((hsi*21+4)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = fp57 + fp55;
target[((hsi*21+11)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp52;
fp52 = 5 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp51;
fp51 = fp52 * target[((hsi*21+4)*1+lsi)*1];
LIBINT2_REALTYPE fp53;
fp53 = inteval->PA_y[vi] * target[((hsi*21+5)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = fp53 + fp51;
target[((hsi*21+12)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp60;
fp60 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp59;
fp59 = fp60 * target[((hsi*21+2)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = inteval->PA_y[vi] * target[((hsi*21+3)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = fp61 + fp59;
target[((hsi*21+10)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp48;
fp48 = 6 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp47;
fp47 = fp48 * target[((hsi*21+5)*1+lsi)*1];
LIBINT2_REALTYPE fp49;
fp49 = inteval->PA_y[vi] * target[((hsi*21+6)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = fp49 + fp47;
target[((hsi*21+13)*1+lsi)*1] = fp46;
LIBINT2_REALTYPE fp44;
fp44 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp43;
fp43 = fp44 * target[((hsi*21+0)*1+lsi)*1];
LIBINT2_REALTYPE fp45;
fp45 = inteval->PA_y[vi] * target[((hsi*21+7)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = fp45 + fp43;
target[((hsi*21+14)*1+lsi)*1] = fp42;
LIBINT2_REALTYPE fp37;
fp37 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp36;
fp36 = fp37 * target[((hsi*21+7)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp39;
fp39 = fp40 * target[((hsi*21+1)*1+lsi)*1];
LIBINT2_REALTYPE fp41;
fp41 = inteval->PA_y[vi] * target[((hsi*21+8)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = fp41 + fp39;
LIBINT2_REALTYPE fp35;
fp35 = fp38 + fp36;
target[((hsi*21+15)*1+lsi)*1] = fp35;
LIBINT2_REALTYPE fp30;
fp30 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp29;
fp29 = fp30 * target[((hsi*21+8)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp32;
fp32 = fp33 * target[((hsi*21+2)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->PA_y[vi] * target[((hsi*21+9)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = fp34 + fp32;
LIBINT2_REALTYPE fp28;
fp28 = fp31 + fp29;
target[((hsi*21+16)*1+lsi)*1] = fp28;
LIBINT2_REALTYPE fp23;
fp23 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp22;
fp22 = fp23 * target[((hsi*21+9)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp25;
fp25 = fp26 * target[((hsi*21+3)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = inteval->PA_y[vi] * target[((hsi*21+10)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = fp27 + fp25;
LIBINT2_REALTYPE fp21;
fp21 = fp24 + fp22;
target[((hsi*21+17)*1+lsi)*1] = fp21;
LIBINT2_REALTYPE fp16;
fp16 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp15;
fp15 = fp16 * target[((hsi*21+10)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp18;
fp18 = fp19 * target[((hsi*21+4)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = inteval->PA_y[vi] * target[((hsi*21+11)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp20 + fp18;
LIBINT2_REALTYPE fp14;
fp14 = fp17 + fp15;
target[((hsi*21+18)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp9;
fp9 = 5 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp8;
fp8 = fp9 * target[((hsi*21+11)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp11;
fp11 = fp12 * target[((hsi*21+5)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = inteval->PA_y[vi] * target[((hsi*21+12)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp13 + fp11;
LIBINT2_REALTYPE fp7;
fp7 = fp10 + fp8;
target[((hsi*21+19)*1+lsi)*1] = fp7;
LIBINT2_REALTYPE fp2;
fp2 = 6 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp2 * target[((hsi*21+12)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp4;
fp4 = fp5 * target[((hsi*21+6)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_y[vi] * target[((hsi*21+13)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = fp6 + fp4;
LIBINT2_REALTYPE fp0;
fp0 = fp3 + fp1;
target[((hsi*21+20)*1+lsi)*1] = fp0;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 92 */
}

#ifdef __cplusplus
};
#endif
