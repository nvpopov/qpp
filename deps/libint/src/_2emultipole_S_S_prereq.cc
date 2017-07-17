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
void _2emultipole_S_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp19;
fp19 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp42;
fp42 = 0 + fp19;
LIBINT2_REALTYPE fp24;
fp24 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp51;
fp51 = 0 + fp24;
LIBINT2_REALTYPE fp67;
fp67 = fp51 * fp42;
LIBINT2_REALTYPE fp14;
fp14 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp13;
fp13 = inteval->PB_z[vi] * fp14;
LIBINT2_REALTYPE fp30;
fp30 = 0 + fp13;
LIBINT2_REALTYPE fp33;
fp33 = 0 + fp14;
LIBINT2_REALTYPE fp32;
fp32 = inteval->BO_z[vi] * fp33;
LIBINT2_REALTYPE fp31;
fp31 = fp30 + fp32;
LIBINT2_REALTYPE fp29;
fp29 = inteval->BO_z[vi] * fp31;
LIBINT2_REALTYPE fp27;
fp27 = inteval->BO_z[vi] * fp30;
LIBINT2_REALTYPE fp11;
fp11 = inteval->oo2z[vi] * fp14;
LIBINT2_REALTYPE fp12;
fp12 = inteval->PB_z[vi] * fp13;
LIBINT2_REALTYPE fp10;
fp10 = fp12 + fp11;
LIBINT2_REALTYPE fp25;
fp25 = 0 + fp10;
LIBINT2_REALTYPE fp26;
fp26 = fp25 + fp27;
LIBINT2_REALTYPE fp28;
fp28 = fp26 + fp29;
LIBINT2_REALTYPE fp52;
fp52 = fp67 * fp28;
LIBINT2_REALTYPE fp9;
fp9 = fp52;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+9)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp18;
fp18 = inteval->PB_y[vi] * fp19;
LIBINT2_REALTYPE fp39;
fp39 = 0 + fp18;
LIBINT2_REALTYPE fp41;
fp41 = inteval->BO_y[vi] * fp42;
LIBINT2_REALTYPE fp40;
fp40 = fp39 + fp41;
LIBINT2_REALTYPE fp63;
fp63 = fp51 * fp40;
LIBINT2_REALTYPE fp53;
fp53 = fp63 * fp31;
LIBINT2_REALTYPE fp8;
fp8 = fp53;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp38;
fp38 = inteval->BO_y[vi] * fp40;
LIBINT2_REALTYPE fp36;
fp36 = inteval->BO_y[vi] * fp39;
LIBINT2_REALTYPE fp16;
fp16 = inteval->oo2z[vi] * fp19;
LIBINT2_REALTYPE fp17;
fp17 = inteval->PB_y[vi] * fp18;
LIBINT2_REALTYPE fp15;
fp15 = fp17 + fp16;
LIBINT2_REALTYPE fp34;
fp34 = 0 + fp15;
LIBINT2_REALTYPE fp35;
fp35 = fp34 + fp36;
LIBINT2_REALTYPE fp37;
fp37 = fp35 + fp38;
LIBINT2_REALTYPE fp55;
fp55 = fp51 * fp37;
LIBINT2_REALTYPE fp54;
fp54 = fp55 * fp33;
LIBINT2_REALTYPE fp7;
fp7 = fp54;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp23;
fp23 = inteval->PB_x[vi] * fp24;
LIBINT2_REALTYPE fp48;
fp48 = 0 + fp23;
LIBINT2_REALTYPE fp50;
fp50 = inteval->BO_x[vi] * fp51;
LIBINT2_REALTYPE fp49;
fp49 = fp48 + fp50;
LIBINT2_REALTYPE fp65;
fp65 = fp49 * fp42;
LIBINT2_REALTYPE fp56;
fp56 = fp65 * fp31;
LIBINT2_REALTYPE fp6;
fp6 = fp56;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp58;
fp58 = fp49 * fp40;
LIBINT2_REALTYPE fp57;
fp57 = fp58 * fp33;
LIBINT2_REALTYPE fp5;
fp5 = fp57;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp47;
fp47 = inteval->BO_x[vi] * fp49;
LIBINT2_REALTYPE fp45;
fp45 = inteval->BO_x[vi] * fp48;
LIBINT2_REALTYPE fp21;
fp21 = inteval->oo2z[vi] * fp24;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PB_x[vi] * fp23;
LIBINT2_REALTYPE fp20;
fp20 = fp22 + fp21;
LIBINT2_REALTYPE fp43;
fp43 = 0 + fp20;
LIBINT2_REALTYPE fp44;
fp44 = fp43 + fp45;
LIBINT2_REALTYPE fp46;
fp46 = fp44 + fp47;
LIBINT2_REALTYPE fp60;
fp60 = fp46 * fp42;
LIBINT2_REALTYPE fp59;
fp59 = fp60 * fp33;
LIBINT2_REALTYPE fp4;
fp4 = fp59;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp61;
fp61 = fp67 * fp31;
LIBINT2_REALTYPE fp3;
fp3 = fp61;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp62;
fp62 = fp63 * fp33;
LIBINT2_REALTYPE fp2;
fp2 = fp62;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp64;
fp64 = fp65 * fp33;
LIBINT2_REALTYPE fp1;
fp1 = fp64;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp66;
fp66 = fp67 * fp33;
LIBINT2_REALTYPE fp0;
fp0 = fp66;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+0)*1+lsi)*1]),&(fp0),1);
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
