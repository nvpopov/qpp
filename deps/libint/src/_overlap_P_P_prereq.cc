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
void _overlap_P_P_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp14;
fp14 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp10;
fp10 = inteval->oo2z[vi] * fp14;
LIBINT2_REALTYPE fp13;
fp13 = inteval->PB_z[vi] * fp14;
LIBINT2_REALTYPE fp11;
fp11 = inteval->PA_z[vi] * fp13;
LIBINT2_REALTYPE fp9;
fp9 = fp11 + fp10;
LIBINT2_REALTYPE fp27;
fp27 = 0 + fp9;
LIBINT2_REALTYPE fp20;
fp20 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp34;
fp34 = 0 + fp20;
LIBINT2_REALTYPE fp22;
fp22 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp35;
fp35 = 0 + fp22;
LIBINT2_REALTYPE fp40;
fp40 = fp35 * fp34;
LIBINT2_REALTYPE fp39;
fp39 = fp40 * fp27;
LIBINT2_REALTYPE fp8;
fp8 = fp39;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp12;
fp12 = inteval->PA_z[vi] * fp14;
LIBINT2_REALTYPE fp28;
fp28 = 0 + fp12;
LIBINT2_REALTYPE fp19;
fp19 = inteval->PB_y[vi] * fp20;
LIBINT2_REALTYPE fp33;
fp33 = 0 + fp19;
LIBINT2_REALTYPE fp42;
fp42 = fp35 * fp33;
LIBINT2_REALTYPE fp41;
fp41 = fp42 * fp28;
LIBINT2_REALTYPE fp7;
fp7 = fp41;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp23;
fp23 = inteval->PB_x[vi] * fp22;
LIBINT2_REALTYPE fp36;
fp36 = 0 + fp23;
LIBINT2_REALTYPE fp44;
fp44 = fp36 * fp34;
LIBINT2_REALTYPE fp43;
fp43 = fp44 * fp28;
LIBINT2_REALTYPE fp6;
fp6 = fp43;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp29;
fp29 = 0 + fp13;
LIBINT2_REALTYPE fp18;
fp18 = inteval->PA_y[vi] * fp20;
LIBINT2_REALTYPE fp32;
fp32 = 0 + fp18;
LIBINT2_REALTYPE fp46;
fp46 = fp35 * fp32;
LIBINT2_REALTYPE fp45;
fp45 = fp46 * fp29;
LIBINT2_REALTYPE fp5;
fp5 = fp45;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp30;
fp30 = 0 + fp14;
LIBINT2_REALTYPE fp16;
fp16 = inteval->oo2z[vi] * fp20;
LIBINT2_REALTYPE fp17;
fp17 = inteval->PA_y[vi] * fp19;
LIBINT2_REALTYPE fp15;
fp15 = fp17 + fp16;
LIBINT2_REALTYPE fp31;
fp31 = 0 + fp15;
LIBINT2_REALTYPE fp48;
fp48 = fp35 * fp31;
LIBINT2_REALTYPE fp47;
fp47 = fp48 * fp30;
LIBINT2_REALTYPE fp4;
fp4 = fp47;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp50;
fp50 = fp36 * fp32;
LIBINT2_REALTYPE fp49;
fp49 = fp50 * fp30;
LIBINT2_REALTYPE fp3;
fp3 = fp49;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp21;
fp21 = inteval->PA_x[vi] * fp22;
LIBINT2_REALTYPE fp37;
fp37 = 0 + fp21;
LIBINT2_REALTYPE fp52;
fp52 = fp37 * fp34;
LIBINT2_REALTYPE fp51;
fp51 = fp52 * fp29;
LIBINT2_REALTYPE fp2;
fp2 = fp51;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp54;
fp54 = fp37 * fp33;
LIBINT2_REALTYPE fp53;
fp53 = fp54 * fp30;
LIBINT2_REALTYPE fp1;
fp1 = fp53;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp25;
fp25 = inteval->oo2z[vi] * fp22;
LIBINT2_REALTYPE fp26;
fp26 = inteval->PA_x[vi] * fp23;
LIBINT2_REALTYPE fp24;
fp24 = fp26 + fp25;
LIBINT2_REALTYPE fp38;
fp38 = 0 + fp24;
LIBINT2_REALTYPE fp56;
fp56 = fp38 * fp34;
LIBINT2_REALTYPE fp55;
fp55 = fp56 * fp30;
LIBINT2_REALTYPE fp0;
fp0 = fp55;
_libint2_static_api_inc1_short_(&(stack[((hsi*9+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 57 */
}

#ifdef __cplusplus
};
#endif
