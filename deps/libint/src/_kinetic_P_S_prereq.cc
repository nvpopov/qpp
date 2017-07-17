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
void _kinetic_P_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp52;
fp52 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp48;
fp48 = inteval->PB_z[vi] * fp52;
LIBINT2_REALTYPE fp14;
fp14 = 0.5 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp4;
fp4 = fp14 * fp48;
LIBINT2_REALTYPE fp17;
fp17 = 0.5 * inteval->two_alpha0_bra[vi];
LIBINT2_REALTYPE fp16;
fp16 = fp17 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp47;
fp47 = inteval->PA_z[vi] * fp52;
LIBINT2_REALTYPE fp43;
fp43 = inteval->oo2z[vi] * fp47;
LIBINT2_REALTYPE fp45;
fp45 = inteval->oo2z[vi] * fp48;
LIBINT2_REALTYPE fp50;
fp50 = inteval->oo2z[vi] * fp52;
LIBINT2_REALTYPE fp51;
fp51 = inteval->PA_z[vi] * fp48;
LIBINT2_REALTYPE fp49;
fp49 = fp51 + fp50;
LIBINT2_REALTYPE fp46;
fp46 = inteval->PA_z[vi] * fp49;
LIBINT2_REALTYPE fp44;
fp44 = fp46 + fp45;
LIBINT2_REALTYPE fp42;
fp42 = fp44 + fp43;
LIBINT2_REALTYPE fp5;
fp5 = fp16 * fp42;
LIBINT2_REALTYPE fp3;
fp3 = fp5 - fp4;
LIBINT2_REALTYPE fp63;
fp63 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp73;
fp73 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp20;
fp20 = fp73 * fp63;
LIBINT2_REALTYPE fp19;
fp19 = fp20 * fp3;
LIBINT2_REALTYPE fp61;
fp61 = inteval->oo2z[vi] * fp63;
LIBINT2_REALTYPE fp59;
fp59 = inteval->PB_y[vi] * fp63;
LIBINT2_REALTYPE fp62;
fp62 = inteval->PA_y[vi] * fp59;
LIBINT2_REALTYPE fp60;
fp60 = fp62 + fp61;
LIBINT2_REALTYPE fp10;
fp10 = fp16 * fp60;
LIBINT2_REALTYPE fp23;
fp23 = fp73 * fp10;
LIBINT2_REALTYPE fp22;
fp22 = fp23 * fp47;
LIBINT2_REALTYPE fp65;
fp65 = inteval->oo2z[vi] * fp73;
LIBINT2_REALTYPE fp67;
fp67 = inteval->PB_x[vi] * fp73;
LIBINT2_REALTYPE fp66;
fp66 = inteval->PA_x[vi] * fp67;
LIBINT2_REALTYPE fp64;
fp64 = fp66 + fp65;
LIBINT2_REALTYPE fp11;
fp11 = fp16 * fp64;
LIBINT2_REALTYPE fp25;
fp25 = fp11 * fp63;
LIBINT2_REALTYPE fp24;
fp24 = fp25 * fp47;
LIBINT2_REALTYPE fp21;
fp21 = fp24 + fp22;
LIBINT2_REALTYPE fp18;
fp18 = fp21 + fp19;
LIBINT2_REALTYPE fp2;
fp2 = fp18;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp6;
fp6 = fp16 * fp49;
LIBINT2_REALTYPE fp58;
fp58 = inteval->PA_y[vi] * fp63;
LIBINT2_REALTYPE fp28;
fp28 = fp73 * fp58;
LIBINT2_REALTYPE fp27;
fp27 = fp28 * fp6;
LIBINT2_REALTYPE fp8;
fp8 = fp14 * fp59;
LIBINT2_REALTYPE fp54;
fp54 = inteval->oo2z[vi] * fp58;
LIBINT2_REALTYPE fp56;
fp56 = inteval->oo2z[vi] * fp59;
LIBINT2_REALTYPE fp57;
fp57 = inteval->PA_y[vi] * fp60;
LIBINT2_REALTYPE fp55;
fp55 = fp57 + fp56;
LIBINT2_REALTYPE fp53;
fp53 = fp55 + fp54;
LIBINT2_REALTYPE fp9;
fp9 = fp16 * fp53;
LIBINT2_REALTYPE fp7;
fp7 = fp9 - fp8;
LIBINT2_REALTYPE fp31;
fp31 = fp73 * fp7;
LIBINT2_REALTYPE fp30;
fp30 = fp31 * fp52;
LIBINT2_REALTYPE fp33;
fp33 = fp11 * fp58;
LIBINT2_REALTYPE fp32;
fp32 = fp33 * fp52;
LIBINT2_REALTYPE fp29;
fp29 = fp32 + fp30;
LIBINT2_REALTYPE fp26;
fp26 = fp29 + fp27;
LIBINT2_REALTYPE fp1;
fp1 = fp26;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp74;
fp74 = inteval->PA_x[vi] * fp73;
LIBINT2_REALTYPE fp36;
fp36 = fp74 * fp63;
LIBINT2_REALTYPE fp35;
fp35 = fp36 * fp6;
LIBINT2_REALTYPE fp39;
fp39 = fp74 * fp10;
LIBINT2_REALTYPE fp38;
fp38 = fp39 * fp52;
LIBINT2_REALTYPE fp13;
fp13 = fp14 * fp67;
LIBINT2_REALTYPE fp69;
fp69 = inteval->oo2z[vi] * fp74;
LIBINT2_REALTYPE fp71;
fp71 = inteval->oo2z[vi] * fp67;
LIBINT2_REALTYPE fp72;
fp72 = inteval->PA_x[vi] * fp64;
LIBINT2_REALTYPE fp70;
fp70 = fp72 + fp71;
LIBINT2_REALTYPE fp68;
fp68 = fp70 + fp69;
LIBINT2_REALTYPE fp15;
fp15 = fp16 * fp68;
LIBINT2_REALTYPE fp12;
fp12 = fp15 - fp13;
LIBINT2_REALTYPE fp41;
fp41 = fp12 * fp63;
LIBINT2_REALTYPE fp40;
fp40 = fp41 * fp52;
LIBINT2_REALTYPE fp37;
fp37 = fp40 + fp38;
LIBINT2_REALTYPE fp34;
fp34 = fp37 + fp35;
LIBINT2_REALTYPE fp0;
fp0 = fp34;
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
