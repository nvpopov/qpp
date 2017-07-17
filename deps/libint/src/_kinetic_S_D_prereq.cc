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
void _kinetic_S_D_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp26;
fp26 = 1 * inteval->two_alpha0_bra[vi];
LIBINT2_REALTYPE fp93;
fp93 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp127;
fp127 = 1 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp91;
fp91 = fp127 * fp93;
LIBINT2_REALTYPE fp89;
fp89 = inteval->PB_z[vi] * fp93;
LIBINT2_REALTYPE fp92;
fp92 = inteval->PA_z[vi] * fp89;
LIBINT2_REALTYPE fp90;
fp90 = fp92 + fp91;
LIBINT2_REALTYPE fp7;
fp7 = fp26 * fp90;
LIBINT2_REALTYPE fp29;
fp29 = 0.5 * inteval->two_alpha0_bra[vi];
LIBINT2_REALTYPE fp28;
fp28 = fp29 * inteval->two_alpha0_ket[vi];
LIBINT2_REALTYPE fp84;
fp84 = inteval->PB_z[vi] * fp89;
LIBINT2_REALTYPE fp83;
fp83 = fp84 + fp91;
LIBINT2_REALTYPE fp121;
fp121 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp81;
fp81 = fp121 * fp83;
LIBINT2_REALTYPE fp115;
fp115 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp86;
fp86 = fp115 * fp89;
LIBINT2_REALTYPE fp79;
fp79 = inteval->PB_z[vi] * fp83;
LIBINT2_REALTYPE fp78;
fp78 = fp79 + fp86;
LIBINT2_REALTYPE fp82;
fp82 = inteval->PA_z[vi] * fp78;
LIBINT2_REALTYPE fp80;
fp80 = fp82 + fp81;
LIBINT2_REALTYPE fp8;
fp8 = fp28 * fp80;
LIBINT2_REALTYPE fp6;
fp6 = fp8 - fp7;
LIBINT2_REALTYPE fp109;
fp109 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp123;
fp123 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp32;
fp32 = fp123 * fp109;
LIBINT2_REALTYPE fp31;
fp31 = fp32 * fp6;
LIBINT2_REALTYPE fp107;
fp107 = fp127 * fp109;
LIBINT2_REALTYPE fp105;
fp105 = inteval->PB_y[vi] * fp109;
LIBINT2_REALTYPE fp108;
fp108 = inteval->PA_y[vi] * fp105;
LIBINT2_REALTYPE fp106;
fp106 = fp108 + fp107;
LIBINT2_REALTYPE fp19;
fp19 = fp28 * fp106;
LIBINT2_REALTYPE fp35;
fp35 = fp123 * fp19;
LIBINT2_REALTYPE fp34;
fp34 = fp35 * fp83;
LIBINT2_REALTYPE fp126;
fp126 = fp127 * fp123;
LIBINT2_REALTYPE fp124;
fp124 = inteval->PB_x[vi] * fp123;
LIBINT2_REALTYPE fp118;
fp118 = inteval->PA_x[vi] * fp124;
LIBINT2_REALTYPE fp117;
fp117 = fp118 + fp126;
LIBINT2_REALTYPE fp20;
fp20 = fp28 * fp117;
LIBINT2_REALTYPE fp37;
fp37 = fp20 * fp109;
LIBINT2_REALTYPE fp36;
fp36 = fp37 * fp83;
LIBINT2_REALTYPE fp33;
fp33 = fp36 + fp34;
LIBINT2_REALTYPE fp30;
fp30 = fp33 + fp31;
LIBINT2_REALTYPE fp5;
fp5 = fp30;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp88;
fp88 = inteval->PA_z[vi] * fp93;
LIBINT2_REALTYPE fp10;
fp10 = fp29 * fp88;
LIBINT2_REALTYPE fp87;
fp87 = inteval->PA_z[vi] * fp83;
LIBINT2_REALTYPE fp85;
fp85 = fp87 + fp86;
LIBINT2_REALTYPE fp11;
fp11 = fp28 * fp85;
LIBINT2_REALTYPE fp9;
fp9 = fp11 - fp10;
LIBINT2_REALTYPE fp40;
fp40 = fp123 * fp105;
LIBINT2_REALTYPE fp39;
fp39 = fp40 * fp9;
LIBINT2_REALTYPE fp104;
fp104 = inteval->PA_y[vi] * fp109;
LIBINT2_REALTYPE fp17;
fp17 = fp29 * fp104;
LIBINT2_REALTYPE fp102;
fp102 = fp115 * fp105;
LIBINT2_REALTYPE fp100;
fp100 = inteval->PB_y[vi] * fp105;
LIBINT2_REALTYPE fp99;
fp99 = fp100 + fp107;
LIBINT2_REALTYPE fp103;
fp103 = inteval->PA_y[vi] * fp99;
LIBINT2_REALTYPE fp101;
fp101 = fp103 + fp102;
LIBINT2_REALTYPE fp18;
fp18 = fp28 * fp101;
LIBINT2_REALTYPE fp16;
fp16 = fp18 - fp17;
LIBINT2_REALTYPE fp43;
fp43 = fp123 * fp16;
LIBINT2_REALTYPE fp42;
fp42 = fp43 * fp89;
LIBINT2_REALTYPE fp45;
fp45 = fp20 * fp105;
LIBINT2_REALTYPE fp44;
fp44 = fp45 * fp89;
LIBINT2_REALTYPE fp41;
fp41 = fp44 + fp42;
LIBINT2_REALTYPE fp38;
fp38 = fp41 + fp39;
LIBINT2_REALTYPE fp4;
fp4 = fp38;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp12;
fp12 = fp28 * fp90;
LIBINT2_REALTYPE fp48;
fp48 = fp123 * fp99;
LIBINT2_REALTYPE fp47;
fp47 = fp48 * fp12;
LIBINT2_REALTYPE fp14;
fp14 = fp26 * fp106;
LIBINT2_REALTYPE fp97;
fp97 = fp121 * fp99;
LIBINT2_REALTYPE fp95;
fp95 = inteval->PB_y[vi] * fp99;
LIBINT2_REALTYPE fp94;
fp94 = fp95 + fp102;
LIBINT2_REALTYPE fp98;
fp98 = inteval->PA_y[vi] * fp94;
LIBINT2_REALTYPE fp96;
fp96 = fp98 + fp97;
LIBINT2_REALTYPE fp15;
fp15 = fp28 * fp96;
LIBINT2_REALTYPE fp13;
fp13 = fp15 - fp14;
LIBINT2_REALTYPE fp51;
fp51 = fp123 * fp13;
LIBINT2_REALTYPE fp50;
fp50 = fp51 * fp93;
LIBINT2_REALTYPE fp53;
fp53 = fp20 * fp99;
LIBINT2_REALTYPE fp52;
fp52 = fp53 * fp93;
LIBINT2_REALTYPE fp49;
fp49 = fp52 + fp50;
LIBINT2_REALTYPE fp46;
fp46 = fp49 + fp47;
LIBINT2_REALTYPE fp3;
fp3 = fp46;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp56;
fp56 = fp124 * fp109;
LIBINT2_REALTYPE fp55;
fp55 = fp56 * fp9;
LIBINT2_REALTYPE fp59;
fp59 = fp124 * fp19;
LIBINT2_REALTYPE fp58;
fp58 = fp59 * fp89;
LIBINT2_REALTYPE fp110;
fp110 = inteval->PA_x[vi] * fp123;
LIBINT2_REALTYPE fp22;
fp22 = fp29 * fp110;
LIBINT2_REALTYPE fp114;
fp114 = fp115 * fp124;
LIBINT2_REALTYPE fp128;
fp128 = inteval->PB_x[vi] * fp124;
LIBINT2_REALTYPE fp125;
fp125 = fp128 + fp126;
LIBINT2_REALTYPE fp112;
fp112 = inteval->PA_x[vi] * fp125;
LIBINT2_REALTYPE fp111;
fp111 = fp112 + fp114;
LIBINT2_REALTYPE fp23;
fp23 = fp28 * fp111;
LIBINT2_REALTYPE fp21;
fp21 = fp23 - fp22;
LIBINT2_REALTYPE fp61;
fp61 = fp21 * fp109;
LIBINT2_REALTYPE fp60;
fp60 = fp61 * fp89;
LIBINT2_REALTYPE fp57;
fp57 = fp60 + fp58;
LIBINT2_REALTYPE fp54;
fp54 = fp57 + fp55;
LIBINT2_REALTYPE fp2;
fp2 = fp54;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp64;
fp64 = fp124 * fp105;
LIBINT2_REALTYPE fp63;
fp63 = fp64 * fp12;
LIBINT2_REALTYPE fp67;
fp67 = fp124 * fp16;
LIBINT2_REALTYPE fp66;
fp66 = fp67 * fp93;
LIBINT2_REALTYPE fp69;
fp69 = fp21 * fp105;
LIBINT2_REALTYPE fp68;
fp68 = fp69 * fp93;
LIBINT2_REALTYPE fp65;
fp65 = fp68 + fp66;
LIBINT2_REALTYPE fp62;
fp62 = fp65 + fp63;
LIBINT2_REALTYPE fp1;
fp1 = fp62;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp72;
fp72 = fp125 * fp109;
LIBINT2_REALTYPE fp71;
fp71 = fp72 * fp12;
LIBINT2_REALTYPE fp75;
fp75 = fp125 * fp19;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp93;
LIBINT2_REALTYPE fp25;
fp25 = fp26 * fp117;
LIBINT2_REALTYPE fp120;
fp120 = fp121 * fp125;
LIBINT2_REALTYPE fp116;
fp116 = inteval->PB_x[vi] * fp125;
LIBINT2_REALTYPE fp113;
fp113 = fp116 + fp114;
LIBINT2_REALTYPE fp122;
fp122 = inteval->PA_x[vi] * fp113;
LIBINT2_REALTYPE fp119;
fp119 = fp122 + fp120;
LIBINT2_REALTYPE fp27;
fp27 = fp28 * fp119;
LIBINT2_REALTYPE fp24;
fp24 = fp27 - fp25;
LIBINT2_REALTYPE fp77;
fp77 = fp24 * fp109;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp93;
LIBINT2_REALTYPE fp73;
fp73 = fp76 + fp74;
LIBINT2_REALTYPE fp70;
fp70 = fp73 + fp71;
LIBINT2_REALTYPE fp0;
fp0 = fp70;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 129 */
}

#ifdef __cplusplus
};
#endif
