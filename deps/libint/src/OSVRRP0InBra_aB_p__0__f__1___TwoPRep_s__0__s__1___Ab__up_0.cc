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

#ifdef __cplusplus
extern "C" {
#endif
void OSVRRP0InBra_aB_p__0__f__1___TwoPRep_s__0__s__1___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp112;
fp112 = 2 * inteval->oo2ze[vi];
LIBINT2_REALTYPE fp111;
fp111 = fp112 * src2[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp114;
fp114 = inteval->WP_x[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp115;
fp115 = inteval->PA_x[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp113;
fp113 = fp115 + fp114;
LIBINT2_REALTYPE fp110;
fp110 = fp113 + fp111;
target[((hsi*30+1)*1+lsi)*1] = fp110;
LIBINT2_REALTYPE fp106;
fp106 = fp112 * src2[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp108;
fp108 = inteval->WP_x[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp109;
fp109 = inteval->PA_x[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp107;
fp107 = fp109 + fp108;
LIBINT2_REALTYPE fp105;
fp105 = fp107 + fp106;
target[((hsi*30+2)*1+lsi)*1] = fp105;
LIBINT2_REALTYPE fp101;
fp101 = inteval->oo2ze[vi] * src2[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp103;
fp103 = inteval->WP_x[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp104;
fp104 = inteval->PA_x[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp102;
fp102 = fp104 + fp103;
LIBINT2_REALTYPE fp100;
fp100 = fp102 + fp101;
target[((hsi*30+3)*1+lsi)*1] = fp100;
LIBINT2_REALTYPE fp96;
fp96 = inteval->oo2ze[vi] * src2[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp98;
fp98 = inteval->WP_x[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp99;
fp99 = inteval->PA_x[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp97;
fp97 = fp99 + fp98;
LIBINT2_REALTYPE fp95;
fp95 = fp97 + fp96;
target[((hsi*30+4)*1+lsi)*1] = fp95;
LIBINT2_REALTYPE fp91;
fp91 = inteval->oo2ze[vi] * src2[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp93;
fp93 = inteval->WP_x[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp94;
fp94 = inteval->PA_x[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp92;
fp92 = fp94 + fp93;
LIBINT2_REALTYPE fp90;
fp90 = fp92 + fp91;
target[((hsi*30+5)*1+lsi)*1] = fp90;
LIBINT2_REALTYPE fp88;
fp88 = inteval->WP_x[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp89;
fp89 = inteval->PA_x[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp87;
fp87 = fp89 + fp88;
target[((hsi*30+6)*1+lsi)*1] = fp87;
LIBINT2_REALTYPE fp85;
fp85 = inteval->WP_x[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp86;
fp86 = inteval->PA_x[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp84;
fp84 = fp86 + fp85;
target[((hsi*30+7)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp82;
fp82 = inteval->WP_x[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp83;
fp83 = inteval->PA_x[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp81;
fp81 = fp83 + fp82;
target[((hsi*30+8)*1+lsi)*1] = fp81;
LIBINT2_REALTYPE fp79;
fp79 = inteval->WP_x[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp80;
fp80 = inteval->PA_x[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp78;
fp78 = fp80 + fp79;
target[((hsi*30+9)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp76;
fp76 = inteval->WP_y[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp77;
fp77 = inteval->PA_y[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp75;
fp75 = fp77 + fp76;
target[((hsi*30+10)*1+lsi)*1] = fp75;
LIBINT2_REALTYPE fp71;
fp71 = inteval->oo2ze[vi] * src2[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp73;
fp73 = inteval->WP_y[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp74;
fp74 = inteval->PA_y[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = fp74 + fp73;
LIBINT2_REALTYPE fp70;
fp70 = fp72 + fp71;
target[((hsi*30+11)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp68;
fp68 = inteval->WP_y[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp69;
fp69 = inteval->PA_y[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp67;
fp67 = fp69 + fp68;
target[((hsi*30+12)*1+lsi)*1] = fp67;
LIBINT2_REALTYPE fp65;
fp65 = inteval->WP_y[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = inteval->PA_y[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = fp66 + fp65;
LIBINT2_REALTYPE fp63;
fp63 = fp64 + fp111;
target[((hsi*30+13)*1+lsi)*1] = fp63;
LIBINT2_REALTYPE fp59;
fp59 = inteval->oo2ze[vi] * src2[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = inteval->WP_y[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = inteval->PA_y[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = fp62 + fp61;
LIBINT2_REALTYPE fp58;
fp58 = fp60 + fp59;
target[((hsi*30+14)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp118;
fp118 = 3 * inteval->oo2ze[vi];
LIBINT2_REALTYPE fp117;
fp117 = fp118 * src2[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp120;
fp120 = inteval->WP_x[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp121;
fp121 = inteval->PA_x[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp119;
fp119 = fp121 + fp120;
LIBINT2_REALTYPE fp116;
fp116 = fp119 + fp117;
target[((hsi*30+0)*1+lsi)*1] = fp116;
LIBINT2_REALTYPE fp51;
fp51 = fp118 * src2[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp53;
fp53 = inteval->WP_y[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = inteval->PA_y[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = fp54 + fp53;
LIBINT2_REALTYPE fp50;
fp50 = fp52 + fp51;
target[((hsi*30+16)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp46;
fp46 = fp112 * src2[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = inteval->WP_y[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp49;
fp49 = inteval->PA_y[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = fp49 + fp48;
LIBINT2_REALTYPE fp45;
fp45 = fp47 + fp46;
target[((hsi*30+17)*1+lsi)*1] = fp45;
LIBINT2_REALTYPE fp43;
fp43 = inteval->WP_y[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->PA_y[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = fp44 + fp43;
LIBINT2_REALTYPE fp41;
fp41 = fp42 + fp91;
target[((hsi*30+18)*1+lsi)*1] = fp41;
LIBINT2_REALTYPE fp39;
fp39 = inteval->WP_y[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = inteval->PA_y[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = fp40 + fp39;
target[((hsi*30+19)*1+lsi)*1] = fp38;
LIBINT2_REALTYPE fp36;
fp36 = inteval->WP_z[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = inteval->PA_z[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = fp37 + fp36;
target[((hsi*30+20)*1+lsi)*1] = fp35;
LIBINT2_REALTYPE fp33;
fp33 = inteval->WP_z[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->PA_z[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = fp34 + fp33;
target[((hsi*30+21)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp30;
fp30 = inteval->WP_z[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->PA_z[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp29;
fp29 = fp31 + fp30;
LIBINT2_REALTYPE fp28;
fp28 = fp29 + fp71;
target[((hsi*30+22)*1+lsi)*1] = fp28;
LIBINT2_REALTYPE fp26;
fp26 = inteval->WP_z[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = inteval->PA_z[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = fp27 + fp26;
target[((hsi*30+23)*1+lsi)*1] = fp25;
LIBINT2_REALTYPE fp21;
fp21 = inteval->oo2ze[vi] * src2[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->WP_z[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->PA_z[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = fp24 + fp23;
LIBINT2_REALTYPE fp20;
fp20 = fp22 + fp21;
target[((hsi*30+24)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp18;
fp18 = inteval->WP_z[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = inteval->PA_z[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp19 + fp18;
LIBINT2_REALTYPE fp16;
fp16 = fp17 + fp106;
target[((hsi*30+25)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp14;
fp14 = inteval->WP_z[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = inteval->PA_z[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = fp15 + fp14;
target[((hsi*30+26)*1+lsi)*1] = fp13;
LIBINT2_REALTYPE fp11;
fp11 = inteval->WP_z[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = inteval->PA_z[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = fp12 + fp11;
LIBINT2_REALTYPE fp9;
fp9 = fp10 + fp101;
target[((hsi*30+27)*1+lsi)*1] = fp9;
LIBINT2_REALTYPE fp7;
fp7 = inteval->WP_z[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->PA_z[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = fp8 + fp7;
LIBINT2_REALTYPE fp5;
fp5 = fp6 + fp46;
target[((hsi*30+28)*1+lsi)*1] = fp5;
LIBINT2_REALTYPE fp1;
fp1 = fp118 * src2[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = inteval->WP_z[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->PA_z[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = fp4 + fp3;
LIBINT2_REALTYPE fp0;
fp0 = fp2 + fp1;
target[((hsi*30+29)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp56;
fp56 = inteval->WP_y[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp57;
fp57 = inteval->PA_y[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp55;
fp55 = fp57 + fp56;
target[((hsi*30+15)*1+lsi)*1] = fp55;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 122 */
}

#ifdef __cplusplus
};
#endif
