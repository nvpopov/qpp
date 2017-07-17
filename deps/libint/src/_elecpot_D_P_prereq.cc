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
void _elecpot_D_P_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp130;
fp130 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp77;
fp77 = inteval->PC_z[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp78;
fp78 = inteval->PA_z[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp76;
fp76 = fp78 - fp77;
LIBINT2_REALTYPE fp80;
fp80 = inteval->PC_z[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp81;
fp81 = inteval->PA_z[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_0[vi];
LIBINT2_REALTYPE fp79;
fp79 = fp81 - fp80;
LIBINT2_REALTYPE fp18;
fp18 = fp79 - fp76;
LIBINT2_REALTYPE fp17;
fp17 = fp130 * fp18;
LIBINT2_REALTYPE fp117;
fp117 = inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi] - inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp116;
fp116 = inteval->oo2z[vi] * fp117;
LIBINT2_REALTYPE fp37;
fp37 = inteval->PC_z[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_3[vi];
LIBINT2_REALTYPE fp38;
fp38 = inteval->PA_z[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp36;
fp36 = fp38 - fp37;
LIBINT2_REALTYPE fp41;
fp41 = inteval->PC_z[vi] * fp36;
LIBINT2_REALTYPE fp42;
fp42 = inteval->PA_z[vi] * fp76;
LIBINT2_REALTYPE fp40;
fp40 = fp42 - fp41;
LIBINT2_REALTYPE fp39;
fp39 = fp40 + fp116;
LIBINT2_REALTYPE fp20;
fp20 = inteval->PC_z[vi] * fp39;
LIBINT2_REALTYPE fp123;
fp123 = inteval->_aB_s___0___ElecPot_s___0___Ab__up_0[vi] - inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp122;
fp122 = inteval->oo2z[vi] * fp123;
LIBINT2_REALTYPE fp45;
fp45 = inteval->PC_z[vi] * fp76;
LIBINT2_REALTYPE fp46;
fp46 = inteval->PA_z[vi] * fp79;
LIBINT2_REALTYPE fp44;
fp44 = fp46 - fp45;
LIBINT2_REALTYPE fp43;
fp43 = fp44 + fp122;
LIBINT2_REALTYPE fp11;
fp11 = fp43;
LIBINT2_REALTYPE fp21;
fp21 = inteval->PA_z[vi] * fp11;
LIBINT2_REALTYPE fp19;
fp19 = fp21 - fp20;
LIBINT2_REALTYPE fp16;
fp16 = fp19 + fp17;
LIBINT2_REALTYPE fp15;
fp15 = fp16;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+15)*1+lsi)*1]),&(fp15),1);
_libint2_static_api_inc1_short_(&(stack[((hsi*1+14)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp92;
fp92 = inteval->PC_y[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp93;
fp93 = inteval->PA_y[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp91;
fp91 = fp93 - fp92;
LIBINT2_REALTYPE fp95;
fp95 = inteval->PC_y[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp96;
fp96 = inteval->PA_y[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_0[vi];
LIBINT2_REALTYPE fp94;
fp94 = fp96 - fp95;
LIBINT2_REALTYPE fp32;
fp32 = fp94 - fp91;
LIBINT2_REALTYPE fp23;
fp23 = inteval->oo2z[vi] * fp32;
LIBINT2_REALTYPE fp61;
fp61 = inteval->PC_y[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_3[vi];
LIBINT2_REALTYPE fp62;
fp62 = inteval->PA_y[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp60;
fp60 = fp62 - fp61;
LIBINT2_REALTYPE fp52;
fp52 = inteval->PC_z[vi] * fp60;
LIBINT2_REALTYPE fp53;
fp53 = inteval->PA_z[vi] * fp91;
LIBINT2_REALTYPE fp51;
fp51 = fp53 - fp52;
LIBINT2_REALTYPE fp25;
fp25 = inteval->PC_z[vi] * fp51;
LIBINT2_REALTYPE fp55;
fp55 = inteval->PC_z[vi] * fp91;
LIBINT2_REALTYPE fp56;
fp56 = inteval->PA_z[vi] * fp94;
LIBINT2_REALTYPE fp54;
fp54 = fp56 - fp55;
LIBINT2_REALTYPE fp9;
fp9 = fp54;
LIBINT2_REALTYPE fp26;
fp26 = inteval->PA_z[vi] * fp9;
LIBINT2_REALTYPE fp24;
fp24 = fp26 - fp25;
LIBINT2_REALTYPE fp22;
fp22 = fp24 + fp23;
LIBINT2_REALTYPE fp14;
fp14 = fp22;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+13)*1+lsi)*1]),&(fp14),1);
_libint2_static_api_inc1_short_(&(stack[((hsi*1+12)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp65;
fp65 = inteval->PC_y[vi] * fp60;
LIBINT2_REALTYPE fp66;
fp66 = inteval->PA_y[vi] * fp91;
LIBINT2_REALTYPE fp64;
fp64 = fp66 - fp65;
LIBINT2_REALTYPE fp63;
fp63 = fp64 + fp116;
LIBINT2_REALTYPE fp28;
fp28 = inteval->PC_z[vi] * fp63;
LIBINT2_REALTYPE fp69;
fp69 = inteval->PC_y[vi] * fp91;
LIBINT2_REALTYPE fp70;
fp70 = inteval->PA_y[vi] * fp94;
LIBINT2_REALTYPE fp68;
fp68 = fp70 - fp69;
LIBINT2_REALTYPE fp67;
fp67 = fp68 + fp122;
LIBINT2_REALTYPE fp7;
fp7 = fp67;
LIBINT2_REALTYPE fp29;
fp29 = inteval->PA_z[vi] * fp7;
LIBINT2_REALTYPE fp27;
fp27 = fp29 - fp28;
LIBINT2_REALTYPE fp13;
fp13 = fp27;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+11)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp31;
fp31 = fp130 * fp32;
LIBINT2_REALTYPE fp34;
fp34 = inteval->PC_y[vi] * fp63;
LIBINT2_REALTYPE fp35;
fp35 = inteval->PA_y[vi] * fp7;
LIBINT2_REALTYPE fp33;
fp33 = fp35 - fp34;
LIBINT2_REALTYPE fp30;
fp30 = fp33 + fp31;
LIBINT2_REALTYPE fp12;
fp12 = fp30;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+10)*1+lsi)*1]),&(fp12),1);
_libint2_static_api_inc1_short_(&(stack[((hsi*1+9)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp110;
fp110 = inteval->PC_x[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp111;
fp111 = inteval->PA_x[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp109;
fp109 = fp111 - fp110;
LIBINT2_REALTYPE fp113;
fp113 = inteval->PC_x[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_1[vi];
LIBINT2_REALTYPE fp114;
fp114 = inteval->PA_x[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_0[vi];
LIBINT2_REALTYPE fp112;
fp112 = fp114 - fp113;
LIBINT2_REALTYPE fp129;
fp129 = fp112 - fp109;
LIBINT2_REALTYPE fp72;
fp72 = inteval->oo2z[vi] * fp129;
LIBINT2_REALTYPE fp107;
fp107 = inteval->PC_x[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_3[vi];
LIBINT2_REALTYPE fp108;
fp108 = inteval->PA_x[vi] * inteval->_aB_s___0___ElecPot_s___0___Ab__up_2[vi];
LIBINT2_REALTYPE fp106;
fp106 = fp108 - fp107;
LIBINT2_REALTYPE fp83;
fp83 = inteval->PC_z[vi] * fp106;
LIBINT2_REALTYPE fp84;
fp84 = inteval->PA_z[vi] * fp109;
LIBINT2_REALTYPE fp82;
fp82 = fp84 - fp83;
LIBINT2_REALTYPE fp49;
fp49 = inteval->PC_z[vi] * fp82;
LIBINT2_REALTYPE fp86;
fp86 = inteval->PC_z[vi] * fp109;
LIBINT2_REALTYPE fp87;
fp87 = inteval->PA_z[vi] * fp112;
LIBINT2_REALTYPE fp85;
fp85 = fp87 - fp86;
LIBINT2_REALTYPE fp5;
fp5 = fp85;
LIBINT2_REALTYPE fp50;
fp50 = inteval->PA_z[vi] * fp5;
LIBINT2_REALTYPE fp48;
fp48 = fp50 - fp49;
LIBINT2_REALTYPE fp47;
fp47 = fp48 + fp72;
LIBINT2_REALTYPE fp10;
fp10 = fp47;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+8)*1+lsi)*1]),&(fp10),1);
_libint2_static_api_inc1_short_(&(stack[((hsi*1+7)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp98;
fp98 = inteval->PC_y[vi] * fp106;
LIBINT2_REALTYPE fp99;
fp99 = inteval->PA_y[vi] * fp109;
LIBINT2_REALTYPE fp97;
fp97 = fp99 - fp98;
LIBINT2_REALTYPE fp58;
fp58 = inteval->PC_z[vi] * fp97;
LIBINT2_REALTYPE fp101;
fp101 = inteval->PC_y[vi] * fp109;
LIBINT2_REALTYPE fp102;
fp102 = inteval->PA_y[vi] * fp112;
LIBINT2_REALTYPE fp100;
fp100 = fp102 - fp101;
LIBINT2_REALTYPE fp3;
fp3 = fp100;
LIBINT2_REALTYPE fp59;
fp59 = inteval->PA_z[vi] * fp3;
LIBINT2_REALTYPE fp57;
fp57 = fp59 - fp58;
LIBINT2_REALTYPE fp8;
fp8 = fp57;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+6)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp74;
fp74 = inteval->PC_y[vi] * fp97;
LIBINT2_REALTYPE fp75;
fp75 = inteval->PA_y[vi] * fp3;
LIBINT2_REALTYPE fp73;
fp73 = fp75 - fp74;
LIBINT2_REALTYPE fp71;
fp71 = fp73 + fp72;
LIBINT2_REALTYPE fp6;
fp6 = fp71;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+5)*1+lsi)*1]),&(fp6),1);
_libint2_static_api_inc1_short_(&(stack[((hsi*1+4)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp119;
fp119 = inteval->PC_x[vi] * fp106;
LIBINT2_REALTYPE fp120;
fp120 = inteval->PA_x[vi] * fp109;
LIBINT2_REALTYPE fp118;
fp118 = fp120 - fp119;
LIBINT2_REALTYPE fp115;
fp115 = fp118 + fp116;
LIBINT2_REALTYPE fp89;
fp89 = inteval->PC_z[vi] * fp115;
LIBINT2_REALTYPE fp125;
fp125 = inteval->PC_x[vi] * fp109;
LIBINT2_REALTYPE fp126;
fp126 = inteval->PA_x[vi] * fp112;
LIBINT2_REALTYPE fp124;
fp124 = fp126 - fp125;
LIBINT2_REALTYPE fp121;
fp121 = fp124 + fp122;
LIBINT2_REALTYPE fp1;
fp1 = fp121;
LIBINT2_REALTYPE fp90;
fp90 = inteval->PA_z[vi] * fp1;
LIBINT2_REALTYPE fp88;
fp88 = fp90 - fp89;
LIBINT2_REALTYPE fp4;
fp4 = fp88;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+3)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp104;
fp104 = inteval->PC_y[vi] * fp115;
LIBINT2_REALTYPE fp105;
fp105 = inteval->PA_y[vi] * fp1;
LIBINT2_REALTYPE fp103;
fp103 = fp105 - fp104;
LIBINT2_REALTYPE fp2;
fp2 = fp103;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+2)*1+lsi)*1]),&(fp2),1);
_libint2_static_api_inc1_short_(&(stack[((hsi*1+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp128;
fp128 = fp130 * fp129;
LIBINT2_REALTYPE fp132;
fp132 = inteval->PC_x[vi] * fp115;
LIBINT2_REALTYPE fp133;
fp133 = inteval->PA_x[vi] * fp1;
LIBINT2_REALTYPE fp131;
fp131 = fp133 - fp132;
LIBINT2_REALTYPE fp127;
fp127 = fp131 + fp128;
LIBINT2_REALTYPE fp0;
fp0 = fp127;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 134 */
}

#ifdef __cplusplus
};
#endif
