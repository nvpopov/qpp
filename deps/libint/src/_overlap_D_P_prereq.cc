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
void _overlap_D_P_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp30;
fp30 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp62;
fp62 = 0 + fp30;
LIBINT2_REALTYPE fp43;
fp43 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp42;
fp42 = inteval->PB_y[vi] * fp43;
LIBINT2_REALTYPE fp67;
fp67 = 0 + fp42;
LIBINT2_REALTYPE fp44;
fp44 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp50;
fp50 = inteval->oo2z[vi] * fp44;
LIBINT2_REALTYPE fp47;
fp47 = inteval->PA_x[vi] * fp44;
LIBINT2_REALTYPE fp46;
fp46 = inteval->PA_x[vi] * fp47;
LIBINT2_REALTYPE fp45;
fp45 = fp46 + fp50;
LIBINT2_REALTYPE fp73;
fp73 = 0 + fp45;
LIBINT2_REALTYPE fp108;
fp108 = fp73 * fp67;
LIBINT2_REALTYPE fp107;
fp107 = fp108 * fp62;
LIBINT2_REALTYPE fp1;
fp1 = fp107;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp29;
fp29 = inteval->PB_z[vi] * fp30;
LIBINT2_REALTYPE fp61;
fp61 = 0 + fp29;
LIBINT2_REALTYPE fp68;
fp68 = 0 + fp43;
LIBINT2_REALTYPE fp106;
fp106 = fp73 * fp68;
LIBINT2_REALTYPE fp105;
fp105 = fp106 * fp61;
LIBINT2_REALTYPE fp2;
fp2 = fp105;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp41;
fp41 = inteval->PA_y[vi] * fp43;
LIBINT2_REALTYPE fp66;
fp66 = 0 + fp41;
LIBINT2_REALTYPE fp48;
fp48 = inteval->PB_x[vi] * fp44;
LIBINT2_REALTYPE fp51;
fp51 = inteval->PA_x[vi] * fp48;
LIBINT2_REALTYPE fp49;
fp49 = fp51 + fp50;
LIBINT2_REALTYPE fp72;
fp72 = 0 + fp49;
LIBINT2_REALTYPE fp104;
fp104 = fp72 * fp66;
LIBINT2_REALTYPE fp103;
fp103 = fp104 * fp62;
LIBINT2_REALTYPE fp3;
fp3 = fp103;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp71;
fp71 = 0 + fp47;
LIBINT2_REALTYPE fp39;
fp39 = inteval->oo2z[vi] * fp43;
LIBINT2_REALTYPE fp40;
fp40 = inteval->PA_y[vi] * fp42;
LIBINT2_REALTYPE fp38;
fp38 = fp40 + fp39;
LIBINT2_REALTYPE fp65;
fp65 = 0 + fp38;
LIBINT2_REALTYPE fp102;
fp102 = fp71 * fp65;
LIBINT2_REALTYPE fp101;
fp101 = fp102 * fp62;
LIBINT2_REALTYPE fp4;
fp4 = fp101;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp100;
fp100 = fp71 * fp66;
LIBINT2_REALTYPE fp99;
fp99 = fp100 * fp61;
LIBINT2_REALTYPE fp5;
fp5 = fp99;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp28;
fp28 = inteval->PA_z[vi] * fp30;
LIBINT2_REALTYPE fp60;
fp60 = 0 + fp28;
LIBINT2_REALTYPE fp98;
fp98 = fp72 * fp68;
LIBINT2_REALTYPE fp97;
fp97 = fp98 * fp60;
LIBINT2_REALTYPE fp6;
fp6 = fp97;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp96;
fp96 = fp71 * fp67;
LIBINT2_REALTYPE fp95;
fp95 = fp96 * fp60;
LIBINT2_REALTYPE fp7;
fp7 = fp95;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp26;
fp26 = inteval->oo2z[vi] * fp30;
LIBINT2_REALTYPE fp27;
fp27 = inteval->PA_z[vi] * fp29;
LIBINT2_REALTYPE fp25;
fp25 = fp27 + fp26;
LIBINT2_REALTYPE fp59;
fp59 = 0 + fp25;
LIBINT2_REALTYPE fp94;
fp94 = fp71 * fp68;
LIBINT2_REALTYPE fp93;
fp93 = fp94 * fp59;
LIBINT2_REALTYPE fp8;
fp8 = fp93;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp53;
fp53 = inteval->oo2z[vi] * fp47;
LIBINT2_REALTYPE fp55;
fp55 = inteval->oo2z[vi] * fp48;
LIBINT2_REALTYPE fp56;
fp56 = inteval->PA_x[vi] * fp49;
LIBINT2_REALTYPE fp54;
fp54 = fp56 + fp55;
LIBINT2_REALTYPE fp52;
fp52 = fp54 + fp53;
LIBINT2_REALTYPE fp74;
fp74 = 0 + fp52;
LIBINT2_REALTYPE fp110;
fp110 = fp74 * fp68;
LIBINT2_REALTYPE fp109;
fp109 = fp110 * fp62;
LIBINT2_REALTYPE fp0;
fp0 = fp109;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+0)*1+lsi)*1]),&(fp0),1);
LIBINT2_REALTYPE fp69;
fp69 = 0 + fp44;
LIBINT2_REALTYPE fp32;
fp32 = inteval->oo2z[vi] * fp41;
LIBINT2_REALTYPE fp34;
fp34 = inteval->oo2z[vi] * fp42;
LIBINT2_REALTYPE fp35;
fp35 = inteval->PA_y[vi] * fp38;
LIBINT2_REALTYPE fp33;
fp33 = fp35 + fp34;
LIBINT2_REALTYPE fp31;
fp31 = fp33 + fp32;
LIBINT2_REALTYPE fp63;
fp63 = 0 + fp31;
LIBINT2_REALTYPE fp90;
fp90 = fp69 * fp63;
LIBINT2_REALTYPE fp89;
fp89 = fp90 * fp62;
LIBINT2_REALTYPE fp10;
fp10 = fp89;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp37;
fp37 = inteval->PA_y[vi] * fp41;
LIBINT2_REALTYPE fp36;
fp36 = fp37 + fp39;
LIBINT2_REALTYPE fp64;
fp64 = 0 + fp36;
LIBINT2_REALTYPE fp88;
fp88 = fp69 * fp64;
LIBINT2_REALTYPE fp87;
fp87 = fp88 * fp61;
LIBINT2_REALTYPE fp11;
fp11 = fp87;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp70;
fp70 = 0 + fp48;
LIBINT2_REALTYPE fp86;
fp86 = fp70 * fp66;
LIBINT2_REALTYPE fp85;
fp85 = fp86 * fp60;
LIBINT2_REALTYPE fp12;
fp12 = fp85;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+12)*1+lsi)*1]),&(fp12),1);
LIBINT2_REALTYPE fp84;
fp84 = fp69 * fp65;
LIBINT2_REALTYPE fp83;
fp83 = fp84 * fp60;
LIBINT2_REALTYPE fp13;
fp13 = fp83;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+13)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp82;
fp82 = fp69 * fp66;
LIBINT2_REALTYPE fp81;
fp81 = fp82 * fp59;
LIBINT2_REALTYPE fp14;
fp14 = fp81;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+14)*1+lsi)*1]),&(fp14),1);
LIBINT2_REALTYPE fp24;
fp24 = inteval->PA_z[vi] * fp28;
LIBINT2_REALTYPE fp23;
fp23 = fp24 + fp26;
LIBINT2_REALTYPE fp58;
fp58 = 0 + fp23;
LIBINT2_REALTYPE fp80;
fp80 = fp70 * fp68;
LIBINT2_REALTYPE fp79;
fp79 = fp80 * fp58;
LIBINT2_REALTYPE fp15;
fp15 = fp79;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+15)*1+lsi)*1]),&(fp15),1);
LIBINT2_REALTYPE fp78;
fp78 = fp69 * fp67;
LIBINT2_REALTYPE fp77;
fp77 = fp78 * fp58;
LIBINT2_REALTYPE fp16;
fp16 = fp77;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+16)*1+lsi)*1]),&(fp16),1);
LIBINT2_REALTYPE fp19;
fp19 = inteval->oo2z[vi] * fp28;
LIBINT2_REALTYPE fp21;
fp21 = inteval->oo2z[vi] * fp29;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PA_z[vi] * fp25;
LIBINT2_REALTYPE fp20;
fp20 = fp22 + fp21;
LIBINT2_REALTYPE fp18;
fp18 = fp20 + fp19;
LIBINT2_REALTYPE fp57;
fp57 = 0 + fp18;
LIBINT2_REALTYPE fp76;
fp76 = fp69 * fp68;
LIBINT2_REALTYPE fp75;
fp75 = fp76 * fp57;
LIBINT2_REALTYPE fp17;
fp17 = fp75;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+17)*1+lsi)*1]),&(fp17),1);
LIBINT2_REALTYPE fp92;
fp92 = fp70 * fp64;
LIBINT2_REALTYPE fp91;
fp91 = fp92 * fp62;
LIBINT2_REALTYPE fp9;
fp9 = fp91;
_libint2_static_api_inc1_short_(&(stack[((hsi*18+9)*1+lsi)*1]),&(fp9),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 111 */
}

#ifdef __cplusplus
};
#endif
