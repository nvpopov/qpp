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
void HRRPart0bra0ket0sf(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, int lowdim) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int lsi = 0; lsi<lowdim; lsi++) {
{
const int vi = 0;
LIBINT2_REALTYPE fp1;
fp1 = inteval->AB_z[vi] * src1[((hsi*6+5)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = src0[((hsi*18+17)*lowdim+lsi)*1] + fp1;
target[((hsi*10+9)*lowdim+lsi)*1] = fp0;
LIBINT2_REALTYPE fp3;
fp3 = inteval->AB_z[vi] * src1[((hsi*6+4)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = src0[((hsi*18+16)*lowdim+lsi)*1] + fp3;
target[((hsi*10+8)*lowdim+lsi)*1] = fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->AB_z[vi] * src1[((hsi*6+3)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = src0[((hsi*18+15)*lowdim+lsi)*1] + fp5;
target[((hsi*10+7)*lowdim+lsi)*1] = fp4;
LIBINT2_REALTYPE fp7;
fp7 = inteval->AB_y[vi] * src1[((hsi*6+3)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = src0[((hsi*18+9)*lowdim+lsi)*1] + fp7;
target[((hsi*10+6)*lowdim+lsi)*1] = fp6;
LIBINT2_REALTYPE fp9;
fp9 = inteval->AB_z[vi] * src1[((hsi*6+2)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = src0[((hsi*18+14)*lowdim+lsi)*1] + fp9;
target[((hsi*10+5)*lowdim+lsi)*1] = fp8;
LIBINT2_REALTYPE fp11;
fp11 = inteval->AB_z[vi] * src1[((hsi*6+1)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = src0[((hsi*18+13)*lowdim+lsi)*1] + fp11;
target[((hsi*10+4)*lowdim+lsi)*1] = fp10;
LIBINT2_REALTYPE fp13;
fp13 = inteval->AB_y[vi] * src1[((hsi*6+1)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = src0[((hsi*18+7)*lowdim+lsi)*1] + fp13;
target[((hsi*10+3)*lowdim+lsi)*1] = fp12;
LIBINT2_REALTYPE fp15;
fp15 = inteval->AB_z[vi] * src1[((hsi*6+0)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = src0[((hsi*18+12)*lowdim+lsi)*1] + fp15;
target[((hsi*10+2)*lowdim+lsi)*1] = fp14;
LIBINT2_REALTYPE fp17;
fp17 = inteval->AB_y[vi] * src1[((hsi*6+0)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = src0[((hsi*18+6)*lowdim+lsi)*1] + fp17;
target[((hsi*10+1)*lowdim+lsi)*1] = fp16;
LIBINT2_REALTYPE fp19;
fp19 = inteval->AB_x[vi] * src1[((hsi*6+0)*lowdim+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = src0[((hsi*18+0)*lowdim+lsi)*1] + fp19;
target[((hsi*10+0)*lowdim+lsi)*1] = fp18;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 20 */
}

#ifdef __cplusplus
};
#endif
