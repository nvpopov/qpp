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
void _3emultipole_S_S_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp35;
fp35 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp76;
fp76 = 0 + fp35;
LIBINT2_REALTYPE fp44;
fp44 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp92;
fp92 = 0 + fp44;
LIBINT2_REALTYPE fp122;
fp122 = fp92 * fp76;
LIBINT2_REALTYPE fp27;
fp27 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp24;
fp24 = inteval->oo2z[vi] * fp27;
LIBINT2_REALTYPE fp26;
fp26 = inteval->PB_z[vi] * fp27;
LIBINT2_REALTYPE fp25;
fp25 = inteval->PB_z[vi] * fp26;
LIBINT2_REALTYPE fp23;
fp23 = fp25 + fp24;
LIBINT2_REALTYPE fp52;
fp52 = 0 + fp23;
LIBINT2_REALTYPE fp57;
fp57 = 0 + fp26;
LIBINT2_REALTYPE fp54;
fp54 = inteval->BO_z[vi] * fp57;
LIBINT2_REALTYPE fp53;
fp53 = fp52 + fp54;
LIBINT2_REALTYPE fp60;
fp60 = 0 + fp27;
LIBINT2_REALTYPE fp59;
fp59 = inteval->BO_z[vi] * fp60;
LIBINT2_REALTYPE fp58;
fp58 = fp57 + fp59;
LIBINT2_REALTYPE fp56;
fp56 = inteval->BO_z[vi] * fp58;
LIBINT2_REALTYPE fp55;
fp55 = fp53 + fp56;
LIBINT2_REALTYPE fp51;
fp51 = inteval->BO_z[vi] * fp55;
LIBINT2_REALTYPE fp49;
fp49 = inteval->BO_z[vi] * fp53;
LIBINT2_REALTYPE fp47;
fp47 = inteval->BO_z[vi] * fp52;
LIBINT2_REALTYPE fp38;
fp38 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp21;
fp21 = fp38 * fp26;
LIBINT2_REALTYPE fp22;
fp22 = inteval->PB_z[vi] * fp23;
LIBINT2_REALTYPE fp20;
fp20 = fp22 + fp21;
LIBINT2_REALTYPE fp45;
fp45 = 0 + fp20;
LIBINT2_REALTYPE fp46;
fp46 = fp45 + fp47;
LIBINT2_REALTYPE fp48;
fp48 = fp46 + fp49;
LIBINT2_REALTYPE fp50;
fp50 = fp48 + fp51;
LIBINT2_REALTYPE fp93;
fp93 = fp122 * fp50;
LIBINT2_REALTYPE fp19;
fp19 = fp93;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+19)*1+lsi)*1]),&(fp19),1);
LIBINT2_REALTYPE fp34;
fp34 = inteval->PB_y[vi] * fp35;
LIBINT2_REALTYPE fp73;
fp73 = 0 + fp34;
LIBINT2_REALTYPE fp75;
fp75 = inteval->BO_y[vi] * fp76;
LIBINT2_REALTYPE fp74;
fp74 = fp73 + fp75;
LIBINT2_REALTYPE fp118;
fp118 = fp92 * fp74;
LIBINT2_REALTYPE fp94;
fp94 = fp118 * fp55;
LIBINT2_REALTYPE fp18;
fp18 = fp94;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+18)*1+lsi)*1]),&(fp18),1);
LIBINT2_REALTYPE fp32;
fp32 = inteval->oo2z[vi] * fp35;
LIBINT2_REALTYPE fp33;
fp33 = inteval->PB_y[vi] * fp34;
LIBINT2_REALTYPE fp31;
fp31 = fp33 + fp32;
LIBINT2_REALTYPE fp68;
fp68 = 0 + fp31;
LIBINT2_REALTYPE fp70;
fp70 = inteval->BO_y[vi] * fp73;
LIBINT2_REALTYPE fp69;
fp69 = fp68 + fp70;
LIBINT2_REALTYPE fp72;
fp72 = inteval->BO_y[vi] * fp74;
LIBINT2_REALTYPE fp71;
fp71 = fp69 + fp72;
LIBINT2_REALTYPE fp110;
fp110 = fp92 * fp71;
LIBINT2_REALTYPE fp95;
fp95 = fp110 * fp58;
LIBINT2_REALTYPE fp17;
fp17 = fp95;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+17)*1+lsi)*1]),&(fp17),1);
LIBINT2_REALTYPE fp67;
fp67 = inteval->BO_y[vi] * fp71;
LIBINT2_REALTYPE fp65;
fp65 = inteval->BO_y[vi] * fp69;
LIBINT2_REALTYPE fp63;
fp63 = inteval->BO_y[vi] * fp68;
LIBINT2_REALTYPE fp29;
fp29 = fp38 * fp34;
LIBINT2_REALTYPE fp30;
fp30 = inteval->PB_y[vi] * fp31;
LIBINT2_REALTYPE fp28;
fp28 = fp30 + fp29;
LIBINT2_REALTYPE fp61;
fp61 = 0 + fp28;
LIBINT2_REALTYPE fp62;
fp62 = fp61 + fp63;
LIBINT2_REALTYPE fp64;
fp64 = fp62 + fp65;
LIBINT2_REALTYPE fp66;
fp66 = fp64 + fp67;
LIBINT2_REALTYPE fp97;
fp97 = fp92 * fp66;
LIBINT2_REALTYPE fp96;
fp96 = fp97 * fp60;
LIBINT2_REALTYPE fp16;
fp16 = fp96;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+16)*1+lsi)*1]),&(fp16),1);
LIBINT2_REALTYPE fp43;
fp43 = inteval->PB_x[vi] * fp44;
LIBINT2_REALTYPE fp89;
fp89 = 0 + fp43;
LIBINT2_REALTYPE fp91;
fp91 = inteval->BO_x[vi] * fp92;
LIBINT2_REALTYPE fp90;
fp90 = fp89 + fp91;
LIBINT2_REALTYPE fp120;
fp120 = fp90 * fp76;
LIBINT2_REALTYPE fp98;
fp98 = fp120 * fp55;
LIBINT2_REALTYPE fp15;
fp15 = fp98;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+15)*1+lsi)*1]),&(fp15),1);
LIBINT2_REALTYPE fp113;
fp113 = fp90 * fp74;
LIBINT2_REALTYPE fp99;
fp99 = fp113 * fp58;
LIBINT2_REALTYPE fp14;
fp14 = fp99;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+14)*1+lsi)*1]),&(fp14),1);
LIBINT2_REALTYPE fp101;
fp101 = fp90 * fp71;
LIBINT2_REALTYPE fp100;
fp100 = fp101 * fp60;
LIBINT2_REALTYPE fp13;
fp13 = fp100;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+13)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp41;
fp41 = inteval->oo2z[vi] * fp44;
LIBINT2_REALTYPE fp42;
fp42 = inteval->PB_x[vi] * fp43;
LIBINT2_REALTYPE fp40;
fp40 = fp42 + fp41;
LIBINT2_REALTYPE fp84;
fp84 = 0 + fp40;
LIBINT2_REALTYPE fp86;
fp86 = inteval->BO_x[vi] * fp89;
LIBINT2_REALTYPE fp85;
fp85 = fp84 + fp86;
LIBINT2_REALTYPE fp88;
fp88 = inteval->BO_x[vi] * fp90;
LIBINT2_REALTYPE fp87;
fp87 = fp85 + fp88;
LIBINT2_REALTYPE fp115;
fp115 = fp87 * fp76;
LIBINT2_REALTYPE fp102;
fp102 = fp115 * fp58;
LIBINT2_REALTYPE fp12;
fp12 = fp102;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+12)*1+lsi)*1]),&(fp12),1);
LIBINT2_REALTYPE fp104;
fp104 = fp87 * fp74;
LIBINT2_REALTYPE fp103;
fp103 = fp104 * fp60;
LIBINT2_REALTYPE fp11;
fp11 = fp103;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp83;
fp83 = inteval->BO_x[vi] * fp87;
LIBINT2_REALTYPE fp81;
fp81 = inteval->BO_x[vi] * fp85;
LIBINT2_REALTYPE fp79;
fp79 = inteval->BO_x[vi] * fp84;
LIBINT2_REALTYPE fp37;
fp37 = fp38 * fp43;
LIBINT2_REALTYPE fp39;
fp39 = inteval->PB_x[vi] * fp40;
LIBINT2_REALTYPE fp36;
fp36 = fp39 + fp37;
LIBINT2_REALTYPE fp77;
fp77 = 0 + fp36;
LIBINT2_REALTYPE fp78;
fp78 = fp77 + fp79;
LIBINT2_REALTYPE fp80;
fp80 = fp78 + fp81;
LIBINT2_REALTYPE fp82;
fp82 = fp80 + fp83;
LIBINT2_REALTYPE fp106;
fp106 = fp82 * fp76;
LIBINT2_REALTYPE fp105;
fp105 = fp106 * fp60;
LIBINT2_REALTYPE fp10;
fp10 = fp105;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp107;
fp107 = fp122 * fp55;
LIBINT2_REALTYPE fp9;
fp9 = fp107;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+9)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp108;
fp108 = fp118 * fp58;
LIBINT2_REALTYPE fp8;
fp8 = fp108;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp109;
fp109 = fp110 * fp60;
LIBINT2_REALTYPE fp7;
fp7 = fp109;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp111;
fp111 = fp120 * fp58;
LIBINT2_REALTYPE fp6;
fp6 = fp111;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp112;
fp112 = fp113 * fp60;
LIBINT2_REALTYPE fp5;
fp5 = fp112;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp114;
fp114 = fp115 * fp60;
LIBINT2_REALTYPE fp4;
fp4 = fp114;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp116;
fp116 = fp122 * fp58;
LIBINT2_REALTYPE fp3;
fp3 = fp116;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp117;
fp117 = fp118 * fp60;
LIBINT2_REALTYPE fp2;
fp2 = fp117;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp119;
fp119 = fp120 * fp60;
LIBINT2_REALTYPE fp1;
fp1 = fp119;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp121;
fp121 = fp122 * fp60;
LIBINT2_REALTYPE fp0;
fp0 = fp121;
_libint2_static_api_inc1_short_(&(stack[((hsi*1+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 123 */
}

#ifdef __cplusplus
};
#endif
