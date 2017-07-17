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
void _1emultipole_P_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp23;
fp23 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp45;
fp45 = 0 + fp23;
LIBINT2_REALTYPE fp28;
fp28 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp52;
fp52 = 0 + fp28;
LIBINT2_REALTYPE fp70;
fp70 = fp52 * fp45;
LIBINT2_REALTYPE fp17;
fp17 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp16;
fp16 = inteval->PA_z[vi] * fp17;
LIBINT2_REALTYPE fp36;
fp36 = 0 + fp16;
LIBINT2_REALTYPE fp32;
fp32 = inteval->BO_z[vi] * fp36;
LIBINT2_REALTYPE fp13;
fp13 = inteval->oo2z[vi] * fp17;
LIBINT2_REALTYPE fp15;
fp15 = inteval->PB_z[vi] * fp17;
LIBINT2_REALTYPE fp14;
fp14 = inteval->PA_z[vi] * fp15;
LIBINT2_REALTYPE fp12;
fp12 = fp14 + fp13;
LIBINT2_REALTYPE fp30;
fp30 = 0 + fp12;
LIBINT2_REALTYPE fp31;
fp31 = fp30 + fp32;
LIBINT2_REALTYPE fp54;
fp54 = fp70 * fp31;
LIBINT2_REALTYPE fp11;
fp11 = fp54;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp37;
fp37 = 0 + fp17;
LIBINT2_REALTYPE fp35;
fp35 = inteval->BO_z[vi] * fp37;
LIBINT2_REALTYPE fp33;
fp33 = 0 + fp15;
LIBINT2_REALTYPE fp34;
fp34 = fp33 + fp35;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PA_y[vi] * fp23;
LIBINT2_REALTYPE fp44;
fp44 = 0 + fp22;
LIBINT2_REALTYPE fp72;
fp72 = fp52 * fp44;
LIBINT2_REALTYPE fp55;
fp55 = fp72 * fp34;
LIBINT2_REALTYPE fp10;
fp10 = fp55;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp29;
fp29 = inteval->PA_x[vi] * fp28;
LIBINT2_REALTYPE fp53;
fp53 = 0 + fp29;
LIBINT2_REALTYPE fp74;
fp74 = fp53 * fp45;
LIBINT2_REALTYPE fp56;
fp56 = fp74 * fp34;
LIBINT2_REALTYPE fp9;
fp9 = fp56;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+9)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp43;
fp43 = inteval->BO_y[vi] * fp45;
LIBINT2_REALTYPE fp21;
fp21 = inteval->PB_y[vi] * fp23;
LIBINT2_REALTYPE fp41;
fp41 = 0 + fp21;
LIBINT2_REALTYPE fp42;
fp42 = fp41 + fp43;
LIBINT2_REALTYPE fp58;
fp58 = fp52 * fp42;
LIBINT2_REALTYPE fp57;
fp57 = fp58 * fp36;
LIBINT2_REALTYPE fp8;
fp8 = fp57;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp40;
fp40 = inteval->BO_y[vi] * fp44;
LIBINT2_REALTYPE fp19;
fp19 = inteval->oo2z[vi] * fp23;
LIBINT2_REALTYPE fp20;
fp20 = inteval->PA_y[vi] * fp21;
LIBINT2_REALTYPE fp18;
fp18 = fp20 + fp19;
LIBINT2_REALTYPE fp38;
fp38 = 0 + fp18;
LIBINT2_REALTYPE fp39;
fp39 = fp38 + fp40;
LIBINT2_REALTYPE fp60;
fp60 = fp52 * fp39;
LIBINT2_REALTYPE fp59;
fp59 = fp60 * fp37;
LIBINT2_REALTYPE fp7;
fp7 = fp59;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp62;
fp62 = fp53 * fp42;
LIBINT2_REALTYPE fp61;
fp61 = fp62 * fp37;
LIBINT2_REALTYPE fp6;
fp6 = fp61;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp48;
fp48 = inteval->BO_x[vi] * fp52;
LIBINT2_REALTYPE fp24;
fp24 = inteval->PB_x[vi] * fp28;
LIBINT2_REALTYPE fp46;
fp46 = 0 + fp24;
LIBINT2_REALTYPE fp47;
fp47 = fp46 + fp48;
LIBINT2_REALTYPE fp64;
fp64 = fp47 * fp45;
LIBINT2_REALTYPE fp63;
fp63 = fp64 * fp36;
LIBINT2_REALTYPE fp5;
fp5 = fp63;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp66;
fp66 = fp47 * fp44;
LIBINT2_REALTYPE fp65;
fp65 = fp66 * fp37;
LIBINT2_REALTYPE fp4;
fp4 = fp65;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp51;
fp51 = inteval->BO_x[vi] * fp53;
LIBINT2_REALTYPE fp26;
fp26 = inteval->oo2z[vi] * fp28;
LIBINT2_REALTYPE fp27;
fp27 = inteval->PA_x[vi] * fp24;
LIBINT2_REALTYPE fp25;
fp25 = fp27 + fp26;
LIBINT2_REALTYPE fp49;
fp49 = 0 + fp25;
LIBINT2_REALTYPE fp50;
fp50 = fp49 + fp51;
LIBINT2_REALTYPE fp68;
fp68 = fp50 * fp45;
LIBINT2_REALTYPE fp67;
fp67 = fp68 * fp37;
LIBINT2_REALTYPE fp3;
fp3 = fp67;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp69;
fp69 = fp70 * fp36;
LIBINT2_REALTYPE fp2;
fp2 = fp69;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp71;
fp71 = fp72 * fp37;
LIBINT2_REALTYPE fp1;
fp1 = fp71;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp73;
fp73 = fp74 * fp37;
LIBINT2_REALTYPE fp0;
fp0 = fp73;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 75 */
}

#ifdef __cplusplus
};
#endif
