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
void _1emultipole_D_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp49;
fp49 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp86;
fp86 = 0 + fp49;
LIBINT2_REALTYPE fp58;
fp58 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp96;
fp96 = 0 + fp58;
LIBINT2_REALTYPE fp130;
fp130 = fp96 * fp86;
LIBINT2_REALTYPE fp36;
fp36 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp33;
fp33 = inteval->oo2z[vi] * fp36;
LIBINT2_REALTYPE fp35;
fp35 = inteval->PA_z[vi] * fp36;
LIBINT2_REALTYPE fp34;
fp34 = inteval->PA_z[vi] * fp35;
LIBINT2_REALTYPE fp32;
fp32 = fp34 + fp33;
LIBINT2_REALTYPE fp72;
fp72 = 0 + fp32;
LIBINT2_REALTYPE fp65;
fp65 = inteval->BO_z[vi] * fp72;
LIBINT2_REALTYPE fp25;
fp25 = inteval->oo2z[vi] * fp35;
LIBINT2_REALTYPE fp31;
fp31 = inteval->PB_z[vi] * fp36;
LIBINT2_REALTYPE fp27;
fp27 = inteval->oo2z[vi] * fp31;
LIBINT2_REALTYPE fp30;
fp30 = inteval->PA_z[vi] * fp31;
LIBINT2_REALTYPE fp29;
fp29 = fp30 + fp33;
LIBINT2_REALTYPE fp28;
fp28 = inteval->PA_z[vi] * fp29;
LIBINT2_REALTYPE fp26;
fp26 = fp28 + fp27;
LIBINT2_REALTYPE fp24;
fp24 = fp26 + fp25;
LIBINT2_REALTYPE fp63;
fp63 = 0 + fp24;
LIBINT2_REALTYPE fp64;
fp64 = fp63 + fp65;
LIBINT2_REALTYPE fp99;
fp99 = fp130 * fp64;
LIBINT2_REALTYPE fp23;
fp23 = fp99;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+23)*1+lsi)*1]),&(fp23),1);
LIBINT2_REALTYPE fp73;
fp73 = 0 + fp35;
LIBINT2_REALTYPE fp68;
fp68 = inteval->BO_z[vi] * fp73;
LIBINT2_REALTYPE fp66;
fp66 = 0 + fp29;
LIBINT2_REALTYPE fp67;
fp67 = fp66 + fp68;
LIBINT2_REALTYPE fp48;
fp48 = inteval->PA_y[vi] * fp49;
LIBINT2_REALTYPE fp85;
fp85 = 0 + fp48;
LIBINT2_REALTYPE fp132;
fp132 = fp96 * fp85;
LIBINT2_REALTYPE fp100;
fp100 = fp132 * fp67;
LIBINT2_REALTYPE fp22;
fp22 = fp100;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+22)*1+lsi)*1]),&(fp22),1);
LIBINT2_REALTYPE fp74;
fp74 = 0 + fp36;
LIBINT2_REALTYPE fp71;
fp71 = inteval->BO_z[vi] * fp74;
LIBINT2_REALTYPE fp69;
fp69 = 0 + fp31;
LIBINT2_REALTYPE fp70;
fp70 = fp69 + fp71;
LIBINT2_REALTYPE fp46;
fp46 = inteval->oo2z[vi] * fp49;
LIBINT2_REALTYPE fp47;
fp47 = inteval->PA_y[vi] * fp48;
LIBINT2_REALTYPE fp45;
fp45 = fp47 + fp46;
LIBINT2_REALTYPE fp84;
fp84 = 0 + fp45;
LIBINT2_REALTYPE fp134;
fp134 = fp96 * fp84;
LIBINT2_REALTYPE fp101;
fp101 = fp134 * fp70;
LIBINT2_REALTYPE fp21;
fp21 = fp101;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+21)*1+lsi)*1]),&(fp21),1);
LIBINT2_REALTYPE fp59;
fp59 = inteval->PA_x[vi] * fp58;
LIBINT2_REALTYPE fp97;
fp97 = 0 + fp59;
LIBINT2_REALTYPE fp136;
fp136 = fp97 * fp86;
LIBINT2_REALTYPE fp102;
fp102 = fp136 * fp67;
LIBINT2_REALTYPE fp20;
fp20 = fp102;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+20)*1+lsi)*1]),&(fp20),1);
LIBINT2_REALTYPE fp138;
fp138 = fp97 * fp85;
LIBINT2_REALTYPE fp103;
fp103 = fp138 * fp70;
LIBINT2_REALTYPE fp19;
fp19 = fp103;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+19)*1+lsi)*1]),&(fp19),1);
LIBINT2_REALTYPE fp61;
fp61 = inteval->oo2z[vi] * fp58;
LIBINT2_REALTYPE fp62;
fp62 = inteval->PA_x[vi] * fp59;
LIBINT2_REALTYPE fp60;
fp60 = fp62 + fp61;
LIBINT2_REALTYPE fp98;
fp98 = 0 + fp60;
LIBINT2_REALTYPE fp140;
fp140 = fp98 * fp86;
LIBINT2_REALTYPE fp104;
fp104 = fp140 * fp70;
LIBINT2_REALTYPE fp18;
fp18 = fp104;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+18)*1+lsi)*1]),&(fp18),1);
LIBINT2_REALTYPE fp83;
fp83 = inteval->BO_y[vi] * fp86;
LIBINT2_REALTYPE fp44;
fp44 = inteval->PB_y[vi] * fp49;
LIBINT2_REALTYPE fp81;
fp81 = 0 + fp44;
LIBINT2_REALTYPE fp82;
fp82 = fp81 + fp83;
LIBINT2_REALTYPE fp106;
fp106 = fp96 * fp82;
LIBINT2_REALTYPE fp105;
fp105 = fp106 * fp72;
LIBINT2_REALTYPE fp17;
fp17 = fp105;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+17)*1+lsi)*1]),&(fp17),1);
LIBINT2_REALTYPE fp80;
fp80 = inteval->BO_y[vi] * fp85;
LIBINT2_REALTYPE fp43;
fp43 = inteval->PA_y[vi] * fp44;
LIBINT2_REALTYPE fp42;
fp42 = fp43 + fp46;
LIBINT2_REALTYPE fp78;
fp78 = 0 + fp42;
LIBINT2_REALTYPE fp79;
fp79 = fp78 + fp80;
LIBINT2_REALTYPE fp108;
fp108 = fp96 * fp79;
LIBINT2_REALTYPE fp107;
fp107 = fp108 * fp73;
LIBINT2_REALTYPE fp16;
fp16 = fp107;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+16)*1+lsi)*1]),&(fp16),1);
LIBINT2_REALTYPE fp77;
fp77 = inteval->BO_y[vi] * fp84;
LIBINT2_REALTYPE fp38;
fp38 = inteval->oo2z[vi] * fp48;
LIBINT2_REALTYPE fp40;
fp40 = inteval->oo2z[vi] * fp44;
LIBINT2_REALTYPE fp41;
fp41 = inteval->PA_y[vi] * fp42;
LIBINT2_REALTYPE fp39;
fp39 = fp41 + fp40;
LIBINT2_REALTYPE fp37;
fp37 = fp39 + fp38;
LIBINT2_REALTYPE fp75;
fp75 = 0 + fp37;
LIBINT2_REALTYPE fp76;
fp76 = fp75 + fp77;
LIBINT2_REALTYPE fp110;
fp110 = fp96 * fp76;
LIBINT2_REALTYPE fp109;
fp109 = fp110 * fp74;
LIBINT2_REALTYPE fp15;
fp15 = fp109;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+15)*1+lsi)*1]),&(fp15),1);
LIBINT2_REALTYPE fp112;
fp112 = fp97 * fp82;
LIBINT2_REALTYPE fp111;
fp111 = fp112 * fp73;
LIBINT2_REALTYPE fp14;
fp14 = fp111;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+14)*1+lsi)*1]),&(fp14),1);
LIBINT2_REALTYPE fp114;
fp114 = fp97 * fp79;
LIBINT2_REALTYPE fp113;
fp113 = fp114 * fp74;
LIBINT2_REALTYPE fp13;
fp13 = fp113;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+13)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp116;
fp116 = fp98 * fp82;
LIBINT2_REALTYPE fp115;
fp115 = fp116 * fp74;
LIBINT2_REALTYPE fp12;
fp12 = fp115;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+12)*1+lsi)*1]),&(fp12),1);
LIBINT2_REALTYPE fp89;
fp89 = inteval->BO_x[vi] * fp96;
LIBINT2_REALTYPE fp50;
fp50 = inteval->PB_x[vi] * fp58;
LIBINT2_REALTYPE fp87;
fp87 = 0 + fp50;
LIBINT2_REALTYPE fp88;
fp88 = fp87 + fp89;
LIBINT2_REALTYPE fp118;
fp118 = fp88 * fp86;
LIBINT2_REALTYPE fp117;
fp117 = fp118 * fp72;
LIBINT2_REALTYPE fp11;
fp11 = fp117;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp120;
fp120 = fp88 * fp85;
LIBINT2_REALTYPE fp119;
fp119 = fp120 * fp73;
LIBINT2_REALTYPE fp10;
fp10 = fp119;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp122;
fp122 = fp88 * fp84;
LIBINT2_REALTYPE fp121;
fp121 = fp122 * fp74;
LIBINT2_REALTYPE fp9;
fp9 = fp121;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+9)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp92;
fp92 = inteval->BO_x[vi] * fp97;
LIBINT2_REALTYPE fp52;
fp52 = inteval->PA_x[vi] * fp50;
LIBINT2_REALTYPE fp51;
fp51 = fp52 + fp61;
LIBINT2_REALTYPE fp90;
fp90 = 0 + fp51;
LIBINT2_REALTYPE fp91;
fp91 = fp90 + fp92;
LIBINT2_REALTYPE fp124;
fp124 = fp91 * fp86;
LIBINT2_REALTYPE fp123;
fp123 = fp124 * fp73;
LIBINT2_REALTYPE fp8;
fp8 = fp123;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp126;
fp126 = fp91 * fp85;
LIBINT2_REALTYPE fp125;
fp125 = fp126 * fp74;
LIBINT2_REALTYPE fp7;
fp7 = fp125;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp95;
fp95 = inteval->BO_x[vi] * fp98;
LIBINT2_REALTYPE fp54;
fp54 = inteval->oo2z[vi] * fp59;
LIBINT2_REALTYPE fp56;
fp56 = inteval->oo2z[vi] * fp50;
LIBINT2_REALTYPE fp57;
fp57 = inteval->PA_x[vi] * fp51;
LIBINT2_REALTYPE fp55;
fp55 = fp57 + fp56;
LIBINT2_REALTYPE fp53;
fp53 = fp55 + fp54;
LIBINT2_REALTYPE fp93;
fp93 = 0 + fp53;
LIBINT2_REALTYPE fp94;
fp94 = fp93 + fp95;
LIBINT2_REALTYPE fp128;
fp128 = fp94 * fp86;
LIBINT2_REALTYPE fp127;
fp127 = fp128 * fp74;
LIBINT2_REALTYPE fp6;
fp6 = fp127;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp129;
fp129 = fp130 * fp72;
LIBINT2_REALTYPE fp5;
fp5 = fp129;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp131;
fp131 = fp132 * fp73;
LIBINT2_REALTYPE fp4;
fp4 = fp131;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp133;
fp133 = fp134 * fp74;
LIBINT2_REALTYPE fp3;
fp3 = fp133;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp135;
fp135 = fp136 * fp73;
LIBINT2_REALTYPE fp2;
fp2 = fp135;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp137;
fp137 = fp138 * fp74;
LIBINT2_REALTYPE fp1;
fp1 = fp137;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp139;
fp139 = fp140 * fp74;
LIBINT2_REALTYPE fp0;
fp0 = fp139;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 141 */
}

#ifdef __cplusplus
};
#endif
