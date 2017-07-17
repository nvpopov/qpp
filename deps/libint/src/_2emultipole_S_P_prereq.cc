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
void _2emultipole_S_P_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp45;
fp45 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp82;
fp82 = 0 + fp45;
LIBINT2_REALTYPE fp53;
fp53 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp95;
fp95 = 0 + fp53;
LIBINT2_REALTYPE fp140;
fp140 = fp95 * fp82;
LIBINT2_REALTYPE fp37;
fp37 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp34;
fp34 = inteval->oo2z[vi] * fp37;
LIBINT2_REALTYPE fp36;
fp36 = inteval->PB_z[vi] * fp37;
LIBINT2_REALTYPE fp35;
fp35 = inteval->PB_z[vi] * fp36;
LIBINT2_REALTYPE fp33;
fp33 = fp35 + fp34;
LIBINT2_REALTYPE fp62;
fp62 = 0 + fp33;
LIBINT2_REALTYPE fp67;
fp67 = 0 + fp36;
LIBINT2_REALTYPE fp64;
fp64 = inteval->BO_z[vi] * fp67;
LIBINT2_REALTYPE fp63;
fp63 = fp62 + fp64;
LIBINT2_REALTYPE fp59;
fp59 = inteval->BO_z[vi] * fp63;
LIBINT2_REALTYPE fp57;
fp57 = inteval->BO_z[vi] * fp62;
LIBINT2_REALTYPE fp48;
fp48 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp31;
fp31 = fp48 * fp36;
LIBINT2_REALTYPE fp32;
fp32 = inteval->PB_z[vi] * fp33;
LIBINT2_REALTYPE fp30;
fp30 = fp32 + fp31;
LIBINT2_REALTYPE fp55;
fp55 = 0 + fp30;
LIBINT2_REALTYPE fp56;
fp56 = fp55 + fp57;
LIBINT2_REALTYPE fp58;
fp58 = fp56 + fp59;
LIBINT2_REALTYPE fp97;
fp97 = fp140 * fp58;
LIBINT2_REALTYPE fp29;
fp29 = fp97;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+29)*1+lsi)*1]),&(fp29),1);
LIBINT2_REALTYPE fp44;
fp44 = inteval->PB_y[vi] * fp45;
LIBINT2_REALTYPE fp81;
fp81 = 0 + fp44;
LIBINT2_REALTYPE fp142;
fp142 = fp95 * fp81;
LIBINT2_REALTYPE fp68;
fp68 = 0 + fp37;
LIBINT2_REALTYPE fp66;
fp66 = inteval->BO_z[vi] * fp68;
LIBINT2_REALTYPE fp65;
fp65 = fp67 + fp66;
LIBINT2_REALTYPE fp61;
fp61 = inteval->BO_z[vi] * fp65;
LIBINT2_REALTYPE fp60;
fp60 = fp63 + fp61;
LIBINT2_REALTYPE fp98;
fp98 = fp142 * fp60;
LIBINT2_REALTYPE fp28;
fp28 = fp98;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+28)*1+lsi)*1]),&(fp28),1);
LIBINT2_REALTYPE fp54;
fp54 = inteval->PB_x[vi] * fp53;
LIBINT2_REALTYPE fp96;
fp96 = 0 + fp54;
LIBINT2_REALTYPE fp144;
fp144 = fp96 * fp82;
LIBINT2_REALTYPE fp99;
fp99 = fp144 * fp60;
LIBINT2_REALTYPE fp27;
fp27 = fp99;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+27)*1+lsi)*1]),&(fp27),1);
LIBINT2_REALTYPE fp80;
fp80 = inteval->BO_y[vi] * fp82;
LIBINT2_REALTYPE fp79;
fp79 = fp81 + fp80;
LIBINT2_REALTYPE fp128;
fp128 = fp95 * fp79;
LIBINT2_REALTYPE fp100;
fp100 = fp128 * fp63;
LIBINT2_REALTYPE fp26;
fp26 = fp100;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+26)*1+lsi)*1]),&(fp26),1);
LIBINT2_REALTYPE fp42;
fp42 = inteval->oo2z[vi] * fp45;
LIBINT2_REALTYPE fp43;
fp43 = inteval->PB_y[vi] * fp44;
LIBINT2_REALTYPE fp41;
fp41 = fp43 + fp42;
LIBINT2_REALTYPE fp76;
fp76 = 0 + fp41;
LIBINT2_REALTYPE fp78;
fp78 = inteval->BO_y[vi] * fp81;
LIBINT2_REALTYPE fp77;
fp77 = fp76 + fp78;
LIBINT2_REALTYPE fp130;
fp130 = fp95 * fp77;
LIBINT2_REALTYPE fp101;
fp101 = fp130 * fp65;
LIBINT2_REALTYPE fp25;
fp25 = fp101;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+25)*1+lsi)*1]),&(fp25),1);
LIBINT2_REALTYPE fp132;
fp132 = fp96 * fp79;
LIBINT2_REALTYPE fp102;
fp102 = fp132 * fp65;
LIBINT2_REALTYPE fp24;
fp24 = fp102;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+24)*1+lsi)*1]),&(fp24),1);
LIBINT2_REALTYPE fp75;
fp75 = inteval->BO_y[vi] * fp79;
LIBINT2_REALTYPE fp74;
fp74 = fp77 + fp75;
LIBINT2_REALTYPE fp104;
fp104 = fp95 * fp74;
LIBINT2_REALTYPE fp103;
fp103 = fp104 * fp67;
LIBINT2_REALTYPE fp23;
fp23 = fp103;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+23)*1+lsi)*1]),&(fp23),1);
LIBINT2_REALTYPE fp73;
fp73 = inteval->BO_y[vi] * fp77;
LIBINT2_REALTYPE fp71;
fp71 = inteval->BO_y[vi] * fp76;
LIBINT2_REALTYPE fp39;
fp39 = fp48 * fp44;
LIBINT2_REALTYPE fp40;
fp40 = inteval->PB_y[vi] * fp41;
LIBINT2_REALTYPE fp38;
fp38 = fp40 + fp39;
LIBINT2_REALTYPE fp69;
fp69 = 0 + fp38;
LIBINT2_REALTYPE fp70;
fp70 = fp69 + fp71;
LIBINT2_REALTYPE fp72;
fp72 = fp70 + fp73;
LIBINT2_REALTYPE fp106;
fp106 = fp95 * fp72;
LIBINT2_REALTYPE fp105;
fp105 = fp106 * fp68;
LIBINT2_REALTYPE fp22;
fp22 = fp105;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+22)*1+lsi)*1]),&(fp22),1);
LIBINT2_REALTYPE fp108;
fp108 = fp96 * fp74;
LIBINT2_REALTYPE fp107;
fp107 = fp108 * fp68;
LIBINT2_REALTYPE fp21;
fp21 = fp107;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+21)*1+lsi)*1]),&(fp21),1);
LIBINT2_REALTYPE fp91;
fp91 = inteval->BO_x[vi] * fp95;
LIBINT2_REALTYPE fp90;
fp90 = fp96 + fp91;
LIBINT2_REALTYPE fp134;
fp134 = fp90 * fp82;
LIBINT2_REALTYPE fp109;
fp109 = fp134 * fp63;
LIBINT2_REALTYPE fp20;
fp20 = fp109;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+20)*1+lsi)*1]),&(fp20),1);
LIBINT2_REALTYPE fp136;
fp136 = fp90 * fp81;
LIBINT2_REALTYPE fp110;
fp110 = fp136 * fp65;
LIBINT2_REALTYPE fp19;
fp19 = fp110;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+19)*1+lsi)*1]),&(fp19),1);
LIBINT2_REALTYPE fp51;
fp51 = inteval->oo2z[vi] * fp53;
LIBINT2_REALTYPE fp52;
fp52 = inteval->PB_x[vi] * fp54;
LIBINT2_REALTYPE fp50;
fp50 = fp52 + fp51;
LIBINT2_REALTYPE fp92;
fp92 = 0 + fp50;
LIBINT2_REALTYPE fp94;
fp94 = inteval->BO_x[vi] * fp96;
LIBINT2_REALTYPE fp93;
fp93 = fp92 + fp94;
LIBINT2_REALTYPE fp138;
fp138 = fp93 * fp82;
LIBINT2_REALTYPE fp111;
fp111 = fp138 * fp65;
LIBINT2_REALTYPE fp18;
fp18 = fp111;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+18)*1+lsi)*1]),&(fp18),1);
LIBINT2_REALTYPE fp113;
fp113 = fp90 * fp79;
LIBINT2_REALTYPE fp112;
fp112 = fp113 * fp67;
LIBINT2_REALTYPE fp17;
fp17 = fp112;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+17)*1+lsi)*1]),&(fp17),1);
LIBINT2_REALTYPE fp115;
fp115 = fp90 * fp77;
LIBINT2_REALTYPE fp114;
fp114 = fp115 * fp68;
LIBINT2_REALTYPE fp16;
fp16 = fp114;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+16)*1+lsi)*1]),&(fp16),1);
LIBINT2_REALTYPE fp117;
fp117 = fp93 * fp79;
LIBINT2_REALTYPE fp116;
fp116 = fp117 * fp68;
LIBINT2_REALTYPE fp15;
fp15 = fp116;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+15)*1+lsi)*1]),&(fp15),1);
LIBINT2_REALTYPE fp84;
fp84 = inteval->BO_x[vi] * fp90;
LIBINT2_REALTYPE fp83;
fp83 = fp93 + fp84;
LIBINT2_REALTYPE fp119;
fp119 = fp83 * fp82;
LIBINT2_REALTYPE fp118;
fp118 = fp119 * fp67;
LIBINT2_REALTYPE fp14;
fp14 = fp118;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+14)*1+lsi)*1]),&(fp14),1);
LIBINT2_REALTYPE fp121;
fp121 = fp83 * fp81;
LIBINT2_REALTYPE fp120;
fp120 = fp121 * fp68;
LIBINT2_REALTYPE fp13;
fp13 = fp120;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+13)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp89;
fp89 = inteval->BO_x[vi] * fp93;
LIBINT2_REALTYPE fp87;
fp87 = inteval->BO_x[vi] * fp92;
LIBINT2_REALTYPE fp47;
fp47 = fp48 * fp54;
LIBINT2_REALTYPE fp49;
fp49 = inteval->PB_x[vi] * fp50;
LIBINT2_REALTYPE fp46;
fp46 = fp49 + fp47;
LIBINT2_REALTYPE fp85;
fp85 = 0 + fp46;
LIBINT2_REALTYPE fp86;
fp86 = fp85 + fp87;
LIBINT2_REALTYPE fp88;
fp88 = fp86 + fp89;
LIBINT2_REALTYPE fp123;
fp123 = fp88 * fp82;
LIBINT2_REALTYPE fp122;
fp122 = fp123 * fp68;
LIBINT2_REALTYPE fp12;
fp12 = fp122;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+12)*1+lsi)*1]),&(fp12),1);
LIBINT2_REALTYPE fp124;
fp124 = fp140 * fp63;
LIBINT2_REALTYPE fp11;
fp11 = fp124;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp125;
fp125 = fp142 * fp65;
LIBINT2_REALTYPE fp10;
fp10 = fp125;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp126;
fp126 = fp144 * fp65;
LIBINT2_REALTYPE fp9;
fp9 = fp126;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+9)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp127;
fp127 = fp128 * fp67;
LIBINT2_REALTYPE fp8;
fp8 = fp127;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp129;
fp129 = fp130 * fp68;
LIBINT2_REALTYPE fp7;
fp7 = fp129;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp131;
fp131 = fp132 * fp68;
LIBINT2_REALTYPE fp6;
fp6 = fp131;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp133;
fp133 = fp134 * fp67;
LIBINT2_REALTYPE fp5;
fp5 = fp133;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp135;
fp135 = fp136 * fp68;
LIBINT2_REALTYPE fp4;
fp4 = fp135;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp137;
fp137 = fp138 * fp68;
LIBINT2_REALTYPE fp3;
fp3 = fp137;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp139;
fp139 = fp140 * fp67;
LIBINT2_REALTYPE fp2;
fp2 = fp139;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp141;
fp141 = fp142 * fp68;
LIBINT2_REALTYPE fp1;
fp1 = fp141;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp143;
fp143 = fp144 * fp68;
LIBINT2_REALTYPE fp0;
fp0 = fp143;
_libint2_static_api_inc1_short_(&(stack[((hsi*3+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 145 */
}

#ifdef __cplusplus
};
#endif
