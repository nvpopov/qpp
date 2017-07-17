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
void _overlap_P_D_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp28;
fp28 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp57;
fp57 = 0 + fp28;
LIBINT2_REALTYPE fp39;
fp39 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp38;
fp38 = inteval->PB_y[vi] * fp39;
LIBINT2_REALTYPE fp62;
fp62 = 0 + fp38;
LIBINT2_REALTYPE fp40;
fp40 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp46;
fp46 = inteval->oo2z[vi] * fp40;
LIBINT2_REALTYPE fp44;
fp44 = inteval->PB_x[vi] * fp40;
LIBINT2_REALTYPE fp43;
fp43 = inteval->PA_x[vi] * fp44;
LIBINT2_REALTYPE fp42;
fp42 = fp43 + fp46;
LIBINT2_REALTYPE fp68;
fp68 = 0 + fp42;
LIBINT2_REALTYPE fp103;
fp103 = fp68 * fp62;
LIBINT2_REALTYPE fp102;
fp102 = fp103 * fp57;
LIBINT2_REALTYPE fp1;
fp1 = fp102;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp27;
fp27 = inteval->PB_z[vi] * fp28;
LIBINT2_REALTYPE fp56;
fp56 = 0 + fp27;
LIBINT2_REALTYPE fp63;
fp63 = 0 + fp39;
LIBINT2_REALTYPE fp101;
fp101 = fp68 * fp63;
LIBINT2_REALTYPE fp100;
fp100 = fp101 * fp56;
LIBINT2_REALTYPE fp2;
fp2 = fp100;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp41;
fp41 = inteval->PA_x[vi] * fp40;
LIBINT2_REALTYPE fp67;
fp67 = 0 + fp41;
LIBINT2_REALTYPE fp36;
fp36 = inteval->oo2z[vi] * fp39;
LIBINT2_REALTYPE fp37;
fp37 = inteval->PB_y[vi] * fp38;
LIBINT2_REALTYPE fp35;
fp35 = fp37 + fp36;
LIBINT2_REALTYPE fp61;
fp61 = 0 + fp35;
LIBINT2_REALTYPE fp99;
fp99 = fp67 * fp61;
LIBINT2_REALTYPE fp98;
fp98 = fp99 * fp57;
LIBINT2_REALTYPE fp3;
fp3 = fp98;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp97;
fp97 = fp67 * fp62;
LIBINT2_REALTYPE fp96;
fp96 = fp97 * fp56;
LIBINT2_REALTYPE fp4;
fp4 = fp96;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp25;
fp25 = inteval->oo2z[vi] * fp28;
LIBINT2_REALTYPE fp26;
fp26 = inteval->PB_z[vi] * fp27;
LIBINT2_REALTYPE fp24;
fp24 = fp26 + fp25;
LIBINT2_REALTYPE fp55;
fp55 = 0 + fp24;
LIBINT2_REALTYPE fp95;
fp95 = fp67 * fp63;
LIBINT2_REALTYPE fp94;
fp94 = fp95 * fp55;
LIBINT2_REALTYPE fp5;
fp5 = fp94;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp34;
fp34 = inteval->PA_y[vi] * fp39;
LIBINT2_REALTYPE fp60;
fp60 = 0 + fp34;
LIBINT2_REALTYPE fp47;
fp47 = inteval->PB_x[vi] * fp44;
LIBINT2_REALTYPE fp45;
fp45 = fp47 + fp46;
LIBINT2_REALTYPE fp66;
fp66 = 0 + fp45;
LIBINT2_REALTYPE fp93;
fp93 = fp66 * fp60;
LIBINT2_REALTYPE fp92;
fp92 = fp93 * fp57;
LIBINT2_REALTYPE fp6;
fp6 = fp92;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp65;
fp65 = 0 + fp44;
LIBINT2_REALTYPE fp33;
fp33 = inteval->PA_y[vi] * fp38;
LIBINT2_REALTYPE fp32;
fp32 = fp33 + fp36;
LIBINT2_REALTYPE fp59;
fp59 = 0 + fp32;
LIBINT2_REALTYPE fp91;
fp91 = fp65 * fp59;
LIBINT2_REALTYPE fp90;
fp90 = fp91 * fp57;
LIBINT2_REALTYPE fp7;
fp7 = fp90;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp89;
fp89 = fp65 * fp60;
LIBINT2_REALTYPE fp88;
fp88 = fp89 * fp56;
LIBINT2_REALTYPE fp8;
fp8 = fp88;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp50;
fp50 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp49;
fp49 = fp50 * fp44;
LIBINT2_REALTYPE fp51;
fp51 = inteval->PA_x[vi] * fp45;
LIBINT2_REALTYPE fp48;
fp48 = fp51 + fp49;
LIBINT2_REALTYPE fp69;
fp69 = 0 + fp48;
LIBINT2_REALTYPE fp105;
fp105 = fp69 * fp63;
LIBINT2_REALTYPE fp104;
fp104 = fp105 * fp57;
LIBINT2_REALTYPE fp0;
fp0 = fp104;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+0)*1+lsi)*1]),&(fp0),1);
LIBINT2_REALTYPE fp64;
fp64 = 0 + fp40;
LIBINT2_REALTYPE fp85;
fp85 = fp64 * fp59;
LIBINT2_REALTYPE fp84;
fp84 = fp85 * fp56;
LIBINT2_REALTYPE fp10;
fp10 = fp84;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp83;
fp83 = fp64 * fp60;
LIBINT2_REALTYPE fp82;
fp82 = fp83 * fp55;
LIBINT2_REALTYPE fp11;
fp11 = fp82;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp23;
fp23 = inteval->PA_z[vi] * fp28;
LIBINT2_REALTYPE fp54;
fp54 = 0 + fp23;
LIBINT2_REALTYPE fp81;
fp81 = fp66 * fp63;
LIBINT2_REALTYPE fp80;
fp80 = fp81 * fp54;
LIBINT2_REALTYPE fp12;
fp12 = fp80;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+12)*1+lsi)*1]),&(fp12),1);
LIBINT2_REALTYPE fp79;
fp79 = fp65 * fp62;
LIBINT2_REALTYPE fp78;
fp78 = fp79 * fp54;
LIBINT2_REALTYPE fp13;
fp13 = fp78;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+13)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp22;
fp22 = inteval->PA_z[vi] * fp27;
LIBINT2_REALTYPE fp21;
fp21 = fp22 + fp25;
LIBINT2_REALTYPE fp53;
fp53 = 0 + fp21;
LIBINT2_REALTYPE fp77;
fp77 = fp65 * fp63;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp53;
LIBINT2_REALTYPE fp14;
fp14 = fp76;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+14)*1+lsi)*1]),&(fp14),1);
LIBINT2_REALTYPE fp75;
fp75 = fp64 * fp61;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp54;
LIBINT2_REALTYPE fp15;
fp15 = fp74;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+15)*1+lsi)*1]),&(fp15),1);
LIBINT2_REALTYPE fp73;
fp73 = fp64 * fp62;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp53;
LIBINT2_REALTYPE fp16;
fp16 = fp72;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+16)*1+lsi)*1]),&(fp16),1);
LIBINT2_REALTYPE fp19;
fp19 = fp50 * fp27;
LIBINT2_REALTYPE fp20;
fp20 = inteval->PA_z[vi] * fp24;
LIBINT2_REALTYPE fp18;
fp18 = fp20 + fp19;
LIBINT2_REALTYPE fp52;
fp52 = 0 + fp18;
LIBINT2_REALTYPE fp71;
fp71 = fp64 * fp63;
LIBINT2_REALTYPE fp70;
fp70 = fp71 * fp52;
LIBINT2_REALTYPE fp17;
fp17 = fp70;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+17)*1+lsi)*1]),&(fp17),1);
LIBINT2_REALTYPE fp30;
fp30 = fp50 * fp38;
LIBINT2_REALTYPE fp31;
fp31 = inteval->PA_y[vi] * fp35;
LIBINT2_REALTYPE fp29;
fp29 = fp31 + fp30;
LIBINT2_REALTYPE fp58;
fp58 = 0 + fp29;
LIBINT2_REALTYPE fp87;
fp87 = fp64 * fp58;
LIBINT2_REALTYPE fp86;
fp86 = fp87 * fp57;
LIBINT2_REALTYPE fp9;
fp9 = fp86;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+9)*1+lsi)*1]),&(fp9),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 106 */
}

#ifdef __cplusplus
};
#endif
