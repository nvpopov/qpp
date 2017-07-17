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
void CR_aB_Z5__0___Overlap_Z1__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
target[((hsi*12+0)*1+lsi)*1] = inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp48;
fp48 = inteval->PA_z[vi] * target[((hsi*12+0)*1+lsi)*1];
target[((hsi*12+2)*1+lsi)*1] = fp48;
LIBINT2_REALTYPE fp31;
fp31 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp30;
fp30 = fp31 * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp41;
fp41 = fp42 * target[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp43;
fp43 = inteval->PA_z[vi] * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = fp43 + fp41;
target[((hsi*12+4)*1+lsi)*1] = fp40;
LIBINT2_REALTYPE fp32;
fp32 = inteval->PA_z[vi] * target[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp29;
fp29 = fp32 + fp30;
target[((hsi*12+6)*1+lsi)*1] = fp29;
LIBINT2_REALTYPE fp20;
fp20 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp19;
fp19 = fp20 * target[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = inteval->PA_z[vi] * target[((hsi*12+6)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = fp21 + fp19;
target[((hsi*12+8)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp24;
fp24 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp23;
fp23 = fp24 * target[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp45;
fp45 = fp46 * target[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp49;
fp49 = inteval->PB_z[vi] * target[((hsi*12+0)*1+lsi)*1];
target[((hsi*12+1)*1+lsi)*1] = fp49;
LIBINT2_REALTYPE fp47;
fp47 = inteval->PA_z[vi] * target[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = fp47 + fp45;
target[((hsi*12+3)*1+lsi)*1] = fp44;
LIBINT2_REALTYPE fp27;
fp27 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp26;
fp26 = fp27 * target[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp34;
fp34 = fp35 * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp37;
fp37 = fp38 * target[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = inteval->PA_z[vi] * target[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = fp39 + fp37;
LIBINT2_REALTYPE fp33;
fp33 = fp36 + fp34;
target[((hsi*12+5)*1+lsi)*1] = fp33;
LIBINT2_REALTYPE fp28;
fp28 = inteval->PA_z[vi] * target[((hsi*12+5)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = fp28 + fp26;
LIBINT2_REALTYPE fp22;
fp22 = fp25 + fp23;
target[((hsi*12+7)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp13;
fp13 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp12;
fp12 = fp13 * target[((hsi*12+6)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp15;
fp15 = fp16 * target[((hsi*12+5)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = inteval->PA_z[vi] * target[((hsi*12+7)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = fp17 + fp15;
LIBINT2_REALTYPE fp11;
fp11 = fp14 + fp12;
target[((hsi*12+9)*1+lsi)*1] = fp11;
LIBINT2_REALTYPE fp2;
fp2 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp2 * target[((hsi*12+8)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp4;
fp4 = fp5 * target[((hsi*12+7)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->PA_z[vi] * target[((hsi*12+9)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = fp6 + fp4;
LIBINT2_REALTYPE fp0;
fp0 = fp3 + fp1;
target[((hsi*12+11)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp9;
fp9 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp8;
fp8 = fp9 * target[((hsi*12+6)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->PA_z[vi] * target[((hsi*12+8)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = fp10 + fp8;
target[((hsi*12+10)*1+lsi)*1] = fp7;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 50 */
}

#ifdef __cplusplus
};
#endif
