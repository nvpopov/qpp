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
void _kinetic_D_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp133;
fp133 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp96;
fp96 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp94;
fp94 = fp133 * fp96;
LIBINT2_REALTYPE fp92;
fp92 = inteval->PB_z[vi] * fp96;
LIBINT2_REALTYPE fp95;
fp95 = inteval->PA_z[vi] * fp92;
LIBINT2_REALTYPE fp93;
fp93 = fp95 + fp94;
LIBINT2_REALTYPE fp27;
fp27 = 1 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp7;
fp7 = fp27 * fp93;
LIBINT2_REALTYPE fp30;
fp30 = 0.5 * inteval->two_alpha0_bra[vi];
LIBINT2_REALTYPE fp29;
fp29 = fp30 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp91;
fp91 = inteval->PA_z[vi] * fp96;
LIBINT2_REALTYPE fp85;
fp85 = inteval->PA_z[vi] * fp91;
LIBINT2_REALTYPE fp84;
fp84 = fp85 + fp94;
LIBINT2_REALTYPE fp80;
fp80 = fp133 * fp84;
LIBINT2_REALTYPE fp127;
fp127 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp82;
fp82 = fp127 * fp93;
LIBINT2_REALTYPE fp87;
fp87 = fp133 * fp91;
LIBINT2_REALTYPE fp89;
fp89 = fp133 * fp92;
LIBINT2_REALTYPE fp90;
fp90 = inteval->PA_z[vi] * fp93;
LIBINT2_REALTYPE fp88;
fp88 = fp90 + fp89;
LIBINT2_REALTYPE fp86;
fp86 = fp88 + fp87;
LIBINT2_REALTYPE fp83;
fp83 = inteval->PA_z[vi] * fp86;
LIBINT2_REALTYPE fp81;
fp81 = fp83 + fp82;
LIBINT2_REALTYPE fp79;
fp79 = fp81 + fp80;
LIBINT2_REALTYPE fp8;
fp8 = fp29 * fp79;
LIBINT2_REALTYPE fp6;
fp6 = fp8 - fp7;
LIBINT2_REALTYPE fp114;
fp114 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp129;
fp129 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp33;
fp33 = fp129 * fp114;
LIBINT2_REALTYPE fp32;
fp32 = fp33 * fp6;
LIBINT2_REALTYPE fp112;
fp112 = fp133 * fp114;
LIBINT2_REALTYPE fp110;
fp110 = inteval->PB_y[vi] * fp114;
LIBINT2_REALTYPE fp113;
fp113 = inteval->PA_y[vi] * fp110;
LIBINT2_REALTYPE fp111;
fp111 = fp113 + fp112;
LIBINT2_REALTYPE fp19;
fp19 = fp29 * fp111;
LIBINT2_REALTYPE fp36;
fp36 = fp129 * fp19;
LIBINT2_REALTYPE fp35;
fp35 = fp36 * fp84;
LIBINT2_REALTYPE fp132;
fp132 = fp133 * fp129;
LIBINT2_REALTYPE fp115;
fp115 = inteval->PB_x[vi] * fp129;
LIBINT2_REALTYPE fp122;
fp122 = inteval->PA_x[vi] * fp115;
LIBINT2_REALTYPE fp121;
fp121 = fp122 + fp132;
LIBINT2_REALTYPE fp20;
fp20 = fp29 * fp121;
LIBINT2_REALTYPE fp38;
fp38 = fp20 * fp114;
LIBINT2_REALTYPE fp37;
fp37 = fp38 * fp84;
LIBINT2_REALTYPE fp34;
fp34 = fp37 + fp35;
LIBINT2_REALTYPE fp31;
fp31 = fp34 + fp32;
LIBINT2_REALTYPE fp5;
fp5 = fp31;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp23;
fp23 = 0.5 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp10;
fp10 = fp23 * fp92;
LIBINT2_REALTYPE fp11;
fp11 = fp29 * fp86;
LIBINT2_REALTYPE fp9;
fp9 = fp11 - fp10;
LIBINT2_REALTYPE fp109;
fp109 = inteval->PA_y[vi] * fp114;
LIBINT2_REALTYPE fp41;
fp41 = fp129 * fp109;
LIBINT2_REALTYPE fp40;
fp40 = fp41 * fp9;
LIBINT2_REALTYPE fp17;
fp17 = fp23 * fp110;
LIBINT2_REALTYPE fp105;
fp105 = fp133 * fp109;
LIBINT2_REALTYPE fp107;
fp107 = fp133 * fp110;
LIBINT2_REALTYPE fp108;
fp108 = inteval->PA_y[vi] * fp111;
LIBINT2_REALTYPE fp106;
fp106 = fp108 + fp107;
LIBINT2_REALTYPE fp104;
fp104 = fp106 + fp105;
LIBINT2_REALTYPE fp18;
fp18 = fp29 * fp104;
LIBINT2_REALTYPE fp16;
fp16 = fp18 - fp17;
LIBINT2_REALTYPE fp44;
fp44 = fp129 * fp16;
LIBINT2_REALTYPE fp43;
fp43 = fp44 * fp91;
LIBINT2_REALTYPE fp46;
fp46 = fp20 * fp109;
LIBINT2_REALTYPE fp45;
fp45 = fp46 * fp91;
LIBINT2_REALTYPE fp42;
fp42 = fp45 + fp43;
LIBINT2_REALTYPE fp39;
fp39 = fp42 + fp40;
LIBINT2_REALTYPE fp4;
fp4 = fp39;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp12;
fp12 = fp29 * fp93;
LIBINT2_REALTYPE fp103;
fp103 = inteval->PA_y[vi] * fp109;
LIBINT2_REALTYPE fp102;
fp102 = fp103 + fp112;
LIBINT2_REALTYPE fp49;
fp49 = fp129 * fp102;
LIBINT2_REALTYPE fp48;
fp48 = fp49 * fp12;
LIBINT2_REALTYPE fp14;
fp14 = fp27 * fp111;
LIBINT2_REALTYPE fp98;
fp98 = fp133 * fp102;
LIBINT2_REALTYPE fp100;
fp100 = fp127 * fp111;
LIBINT2_REALTYPE fp101;
fp101 = inteval->PA_y[vi] * fp104;
LIBINT2_REALTYPE fp99;
fp99 = fp101 + fp100;
LIBINT2_REALTYPE fp97;
fp97 = fp99 + fp98;
LIBINT2_REALTYPE fp15;
fp15 = fp29 * fp97;
LIBINT2_REALTYPE fp13;
fp13 = fp15 - fp14;
LIBINT2_REALTYPE fp52;
fp52 = fp129 * fp13;
LIBINT2_REALTYPE fp51;
fp51 = fp52 * fp96;
LIBINT2_REALTYPE fp54;
fp54 = fp20 * fp102;
LIBINT2_REALTYPE fp53;
fp53 = fp54 * fp96;
LIBINT2_REALTYPE fp50;
fp50 = fp53 + fp51;
LIBINT2_REALTYPE fp47;
fp47 = fp50 + fp48;
LIBINT2_REALTYPE fp3;
fp3 = fp47;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp130;
fp130 = inteval->PA_x[vi] * fp129;
LIBINT2_REALTYPE fp57;
fp57 = fp130 * fp114;
LIBINT2_REALTYPE fp56;
fp56 = fp57 * fp9;
LIBINT2_REALTYPE fp60;
fp60 = fp130 * fp19;
LIBINT2_REALTYPE fp59;
fp59 = fp60 * fp91;
LIBINT2_REALTYPE fp22;
fp22 = fp23 * fp115;
LIBINT2_REALTYPE fp117;
fp117 = fp133 * fp130;
LIBINT2_REALTYPE fp119;
fp119 = fp133 * fp115;
LIBINT2_REALTYPE fp120;
fp120 = inteval->PA_x[vi] * fp121;
LIBINT2_REALTYPE fp118;
fp118 = fp120 + fp119;
LIBINT2_REALTYPE fp116;
fp116 = fp118 + fp117;
LIBINT2_REALTYPE fp24;
fp24 = fp29 * fp116;
LIBINT2_REALTYPE fp21;
fp21 = fp24 - fp22;
LIBINT2_REALTYPE fp62;
fp62 = fp21 * fp114;
LIBINT2_REALTYPE fp61;
fp61 = fp62 * fp91;
LIBINT2_REALTYPE fp58;
fp58 = fp61 + fp59;
LIBINT2_REALTYPE fp55;
fp55 = fp58 + fp56;
LIBINT2_REALTYPE fp2;
fp2 = fp55;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp65;
fp65 = fp130 * fp109;
LIBINT2_REALTYPE fp64;
fp64 = fp65 * fp12;
LIBINT2_REALTYPE fp68;
fp68 = fp130 * fp16;
LIBINT2_REALTYPE fp67;
fp67 = fp68 * fp96;
LIBINT2_REALTYPE fp70;
fp70 = fp21 * fp109;
LIBINT2_REALTYPE fp69;
fp69 = fp70 * fp96;
LIBINT2_REALTYPE fp66;
fp66 = fp69 + fp67;
LIBINT2_REALTYPE fp63;
fp63 = fp66 + fp64;
LIBINT2_REALTYPE fp1;
fp1 = fp63;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp134;
fp134 = inteval->PA_x[vi] * fp130;
LIBINT2_REALTYPE fp131;
fp131 = fp134 + fp132;
LIBINT2_REALTYPE fp73;
fp73 = fp131 * fp114;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp12;
LIBINT2_REALTYPE fp76;
fp76 = fp131 * fp19;
LIBINT2_REALTYPE fp75;
fp75 = fp76 * fp96;
LIBINT2_REALTYPE fp26;
fp26 = fp27 * fp121;
LIBINT2_REALTYPE fp124;
fp124 = fp133 * fp131;
LIBINT2_REALTYPE fp126;
fp126 = fp127 * fp121;
LIBINT2_REALTYPE fp128;
fp128 = inteval->PA_x[vi] * fp116;
LIBINT2_REALTYPE fp125;
fp125 = fp128 + fp126;
LIBINT2_REALTYPE fp123;
fp123 = fp125 + fp124;
LIBINT2_REALTYPE fp28;
fp28 = fp29 * fp123;
LIBINT2_REALTYPE fp25;
fp25 = fp28 - fp26;
LIBINT2_REALTYPE fp78;
fp78 = fp25 * fp114;
LIBINT2_REALTYPE fp77;
fp77 = fp78 * fp96;
LIBINT2_REALTYPE fp74;
fp74 = fp77 + fp75;
LIBINT2_REALTYPE fp71;
fp71 = fp74 + fp72;
LIBINT2_REALTYPE fp0;
fp0 = fp71;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 135 */
}

#ifdef __cplusplus
};
#endif
