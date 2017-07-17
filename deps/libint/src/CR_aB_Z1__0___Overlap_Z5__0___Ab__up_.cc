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
void CR_aB_Z1__0___Overlap_Z5__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
target[((hsi*12+0)*1+lsi)*1] = inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp37;
fp37 = inteval->PB_z[vi] * target[((hsi*12+0)*1+lsi)*1];
target[((hsi*12+1)*1+lsi)*1] = fp37;
LIBINT2_REALTYPE fp31;
fp31 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp30;
fp30 = fp31 * target[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp34;
fp34 = fp35 * target[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = inteval->PB_z[vi] * target[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = fp36 + fp34;
target[((hsi*12+2)*1+lsi)*1] = fp33;
LIBINT2_REALTYPE fp32;
fp32 = inteval->PB_z[vi] * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp29;
fp29 = fp32 + fp30;
target[((hsi*12+3)*1+lsi)*1] = fp29;
LIBINT2_REALTYPE fp27;
fp27 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp26;
fp26 = fp27 * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = inteval->PB_z[vi] * target[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = fp28 + fp26;
target[((hsi*12+4)*1+lsi)*1] = fp25;
LIBINT2_REALTYPE fp23;
fp23 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp22;
fp22 = fp23 * target[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->PB_z[vi] * target[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = fp24 + fp22;
target[((hsi*12+5)*1+lsi)*1] = fp21;
LIBINT2_REALTYPE fp2;
fp2 = 5 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp2 * target[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = inteval->PA_z[vi] * target[((hsi*12+5)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = fp3 + fp1;
target[((hsi*12+11)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp6;
fp6 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp5;
fp5 = fp6 * target[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = inteval->PA_z[vi] * target[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = fp7 + fp5;
target[((hsi*12+10)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp10;
fp10 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp9;
fp9 = fp10 * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = inteval->PA_z[vi] * target[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = fp11 + fp9;
target[((hsi*12+9)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp14;
fp14 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp13;
fp13 = fp14 * target[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = inteval->PA_z[vi] * target[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = fp15 + fp13;
target[((hsi*12+8)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp18;
fp18 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp17;
fp17 = fp18 * target[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = inteval->PA_z[vi] * target[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = fp19 + fp17;
target[((hsi*12+7)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp20;
fp20 = inteval->PA_z[vi] * target[((hsi*12+0)*1+lsi)*1];
target[((hsi*12+6)*1+lsi)*1] = fp20;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 38 */
}

#ifdef __cplusplus
};
#endif
