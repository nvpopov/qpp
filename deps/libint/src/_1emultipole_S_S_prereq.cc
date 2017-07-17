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
#include <GenericContract.h>

#ifdef __cplusplus
extern "C" {
#endif
void _1emultipole_S_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp7;
fp7 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp17;
fp17 = 0 + fp7;
LIBINT2_REALTYPE fp9;
fp9 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp21;
fp21 = 0 + fp9;
LIBINT2_REALTYPE fp28;
fp28 = fp21 * fp17;
LIBINT2_REALTYPE fp5;
fp5 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp13;
fp13 = 0 + fp5;
LIBINT2_REALTYPE fp12;
fp12 = inteval->BO_z[vi] * fp13;
LIBINT2_REALTYPE fp4;
fp4 = inteval->PB_z[vi] * fp5;
LIBINT2_REALTYPE fp10;
fp10 = 0 + fp4;
LIBINT2_REALTYPE fp11;
fp11 = fp10 + fp12;
LIBINT2_REALTYPE fp22;
fp22 = fp28 * fp11;
LIBINT2_REALTYPE fp3;
fp3 = fp22;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp16;
fp16 = inteval->BO_y[vi] * fp17;
LIBINT2_REALTYPE fp6;
fp6 = inteval->PB_y[vi] * fp7;
LIBINT2_REALTYPE fp14;
fp14 = 0 + fp6;
LIBINT2_REALTYPE fp15;
fp15 = fp14 + fp16;
LIBINT2_REALTYPE fp24;
fp24 = fp21 * fp15;
LIBINT2_REALTYPE fp23;
fp23 = fp24 * fp13;
LIBINT2_REALTYPE fp2;
fp2 = fp23;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp20;
fp20 = inteval->BO_x[vi] * fp21;
LIBINT2_REALTYPE fp8;
fp8 = inteval->PB_x[vi] * fp9;
LIBINT2_REALTYPE fp18;
fp18 = 0 + fp8;
LIBINT2_REALTYPE fp19;
fp19 = fp18 + fp20;
LIBINT2_REALTYPE fp26;
fp26 = fp19 * fp17;
LIBINT2_REALTYPE fp25;
fp25 = fp26 * fp13;
LIBINT2_REALTYPE fp1;
fp1 = fp25;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp27;
fp27 = fp28 * fp13;
LIBINT2_REALTYPE fp0;
fp0 = fp27;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 29 */
}

#ifdef __cplusplus
};
#endif
