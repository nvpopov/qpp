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
void _kinetic_S_P_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp16;
fp16 = 0.5 * inteval->two_alpha0_bra[vi];
LIBINT2_REALTYPE fp50;
fp50 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp51;
fp51 = inteval->PA_z[vi] * fp50;
LIBINT2_REALTYPE fp4;
fp4 = fp16 * fp51;
LIBINT2_REALTYPE fp15;
fp15 = fp16 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp46;
fp46 = inteval->PB_z[vi] * fp50;
LIBINT2_REALTYPE fp70;
fp70 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp44;
fp44 = fp70 * fp46;
LIBINT2_REALTYPE fp48;
fp48 = inteval->oo2z[vi] * fp50;
LIBINT2_REALTYPE fp42;
fp42 = inteval->PB_z[vi] * fp46;
LIBINT2_REALTYPE fp41;
fp41 = fp42 + fp48;
LIBINT2_REALTYPE fp45;
fp45 = inteval->PA_z[vi] * fp41;
LIBINT2_REALTYPE fp43;
fp43 = fp45 + fp44;
LIBINT2_REALTYPE fp5;
fp5 = fp15 * fp43;
LIBINT2_REALTYPE fp3;
fp3 = fp5 - fp4;
LIBINT2_REALTYPE fp61;
fp61 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp72;
fp72 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp19;
fp19 = fp72 * fp61;
LIBINT2_REALTYPE fp18;
fp18 = fp19 * fp3;
LIBINT2_REALTYPE fp59;
fp59 = inteval->oo2z[vi] * fp61;
LIBINT2_REALTYPE fp57;
fp57 = inteval->PB_y[vi] * fp61;
LIBINT2_REALTYPE fp60;
fp60 = inteval->PA_y[vi] * fp57;
LIBINT2_REALTYPE fp58;
fp58 = fp60 + fp59;
LIBINT2_REALTYPE fp10;
fp10 = fp15 * fp58;
LIBINT2_REALTYPE fp22;
fp22 = fp72 * fp10;
LIBINT2_REALTYPE fp21;
fp21 = fp22 * fp46;
LIBINT2_REALTYPE fp66;
fp66 = inteval->oo2z[vi] * fp72;
LIBINT2_REALTYPE fp73;
fp73 = inteval->PB_x[vi] * fp72;
LIBINT2_REALTYPE fp64;
fp64 = inteval->PA_x[vi] * fp73;
LIBINT2_REALTYPE fp63;
fp63 = fp64 + fp66;
LIBINT2_REALTYPE fp11;
fp11 = fp15 * fp63;
LIBINT2_REALTYPE fp24;
fp24 = fp11 * fp61;
LIBINT2_REALTYPE fp23;
fp23 = fp24 * fp46;
LIBINT2_REALTYPE fp20;
fp20 = fp23 + fp21;
LIBINT2_REALTYPE fp17;
fp17 = fp20 + fp18;
LIBINT2_REALTYPE fp2;
fp2 = fp17;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp49;
fp49 = inteval->PA_z[vi] * fp46;
LIBINT2_REALTYPE fp47;
fp47 = fp49 + fp48;
LIBINT2_REALTYPE fp6;
fp6 = fp15 * fp47;
LIBINT2_REALTYPE fp27;
fp27 = fp72 * fp57;
LIBINT2_REALTYPE fp26;
fp26 = fp27 * fp6;
LIBINT2_REALTYPE fp62;
fp62 = inteval->PA_y[vi] * fp61;
LIBINT2_REALTYPE fp8;
fp8 = fp16 * fp62;
LIBINT2_REALTYPE fp55;
fp55 = fp70 * fp57;
LIBINT2_REALTYPE fp53;
fp53 = inteval->PB_y[vi] * fp57;
LIBINT2_REALTYPE fp52;
fp52 = fp53 + fp59;
LIBINT2_REALTYPE fp56;
fp56 = inteval->PA_y[vi] * fp52;
LIBINT2_REALTYPE fp54;
fp54 = fp56 + fp55;
LIBINT2_REALTYPE fp9;
fp9 = fp15 * fp54;
LIBINT2_REALTYPE fp7;
fp7 = fp9 - fp8;
LIBINT2_REALTYPE fp30;
fp30 = fp72 * fp7;
LIBINT2_REALTYPE fp29;
fp29 = fp30 * fp50;
LIBINT2_REALTYPE fp32;
fp32 = fp11 * fp57;
LIBINT2_REALTYPE fp31;
fp31 = fp32 * fp50;
LIBINT2_REALTYPE fp28;
fp28 = fp31 + fp29;
LIBINT2_REALTYPE fp25;
fp25 = fp28 + fp26;
LIBINT2_REALTYPE fp1;
fp1 = fp25;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp35;
fp35 = fp73 * fp61;
LIBINT2_REALTYPE fp34;
fp34 = fp35 * fp6;
LIBINT2_REALTYPE fp38;
fp38 = fp73 * fp10;
LIBINT2_REALTYPE fp37;
fp37 = fp38 * fp50;
LIBINT2_REALTYPE fp74;
fp74 = inteval->PA_x[vi] * fp72;
LIBINT2_REALTYPE fp13;
fp13 = fp16 * fp74;
LIBINT2_REALTYPE fp69;
fp69 = fp70 * fp73;
LIBINT2_REALTYPE fp67;
fp67 = inteval->PB_x[vi] * fp73;
LIBINT2_REALTYPE fp65;
fp65 = fp67 + fp66;
LIBINT2_REALTYPE fp71;
fp71 = inteval->PA_x[vi] * fp65;
LIBINT2_REALTYPE fp68;
fp68 = fp71 + fp69;
LIBINT2_REALTYPE fp14;
fp14 = fp15 * fp68;
LIBINT2_REALTYPE fp12;
fp12 = fp14 - fp13;
LIBINT2_REALTYPE fp40;
fp40 = fp12 * fp61;
LIBINT2_REALTYPE fp39;
fp39 = fp40 * fp50;
LIBINT2_REALTYPE fp36;
fp36 = fp39 + fp37;
LIBINT2_REALTYPE fp33;
fp33 = fp36 + fp34;
LIBINT2_REALTYPE fp0;
fp0 = fp33;
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
