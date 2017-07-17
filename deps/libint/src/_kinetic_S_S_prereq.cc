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
void _kinetic_S_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp5;
fp5 = 0.5 * inteval->two_alpha0_bra[vi];
LIBINT2_REALTYPE fp4;
fp4 = fp5 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp18;
fp18 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp16;
fp16 = inteval->oo2z[vi] * fp18;
LIBINT2_REALTYPE fp14;
fp14 = inteval->PB_z[vi] * fp18;
LIBINT2_REALTYPE fp17;
fp17 = inteval->PA_z[vi] * fp14;
LIBINT2_REALTYPE fp15;
fp15 = fp17 + fp16;
LIBINT2_REALTYPE fp1;
fp1 = fp4 * fp15;
LIBINT2_REALTYPE fp23;
fp23 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp28;
fp28 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp8;
fp8 = fp28 * fp23;
LIBINT2_REALTYPE fp7;
fp7 = fp8 * fp1;
LIBINT2_REALTYPE fp21;
fp21 = inteval->oo2z[vi] * fp23;
LIBINT2_REALTYPE fp19;
fp19 = inteval->PB_y[vi] * fp23;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PA_y[vi] * fp19;
LIBINT2_REALTYPE fp20;
fp20 = fp22 + fp21;
LIBINT2_REALTYPE fp2;
fp2 = fp4 * fp20;
LIBINT2_REALTYPE fp11;
fp11 = fp28 * fp2;
LIBINT2_REALTYPE fp10;
fp10 = fp11 * fp18;
LIBINT2_REALTYPE fp26;
fp26 = inteval->oo2z[vi] * fp28;
LIBINT2_REALTYPE fp24;
fp24 = inteval->PB_x[vi] * fp28;
LIBINT2_REALTYPE fp27;
fp27 = inteval->PA_x[vi] * fp24;
LIBINT2_REALTYPE fp25;
fp25 = fp27 + fp26;
LIBINT2_REALTYPE fp3;
fp3 = fp4 * fp25;
LIBINT2_REALTYPE fp13;
fp13 = fp3 * fp23;
LIBINT2_REALTYPE fp12;
fp12 = fp13 * fp18;
LIBINT2_REALTYPE fp9;
fp9 = fp12 + fp10;
LIBINT2_REALTYPE fp6;
fp6 = fp9 + fp7;
LIBINT2_REALTYPE fp0;
fp0 = fp6;
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
