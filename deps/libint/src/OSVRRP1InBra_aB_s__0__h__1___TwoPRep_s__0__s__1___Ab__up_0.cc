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
void OSVRRP1InBra_aB_s__0__h__1___TwoPRep_s__0__s__1___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2, const LIBINT2_REALTYPE* src3) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp128;
fp128 = inteval->WQ_y[vi] * src1[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp129;
fp129 = inteval->QC_y[vi] * src0[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp127;
fp127 = fp129 + fp128;
target[((hsi*21+1)*1+lsi)*1] = fp127;
LIBINT2_REALTYPE fp125;
fp125 = inteval->WQ_z[vi] * src1[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp126;
fp126 = inteval->QC_z[vi] * src0[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp124;
fp124 = fp126 + fp125;
target[((hsi*21+2)*1+lsi)*1] = fp124;
LIBINT2_REALTYPE fp119;
fp119 = inteval->roe[vi] * src3[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp118;
fp118 = src2[((hsi*10+0)*1+lsi)*1] - fp119;
LIBINT2_REALTYPE fp120;
fp120 = 1 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp117;
fp117 = fp120 * fp118;
LIBINT2_REALTYPE fp122;
fp122 = inteval->WQ_y[vi] * src1[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp123;
fp123 = inteval->QC_y[vi] * src0[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp121;
fp121 = fp123 + fp122;
LIBINT2_REALTYPE fp116;
fp116 = fp121 + fp117;
target[((hsi*21+3)*1+lsi)*1] = fp116;
LIBINT2_REALTYPE fp114;
fp114 = inteval->WQ_z[vi] * src1[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp115;
fp115 = inteval->QC_z[vi] * src0[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp113;
fp113 = fp115 + fp114;
target[((hsi*21+4)*1+lsi)*1] = fp113;
LIBINT2_REALTYPE fp108;
fp108 = inteval->roe[vi] * src3[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp107;
fp107 = src2[((hsi*10+0)*1+lsi)*1] - fp108;
LIBINT2_REALTYPE fp109;
fp109 = 1 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp106;
fp106 = fp109 * fp107;
LIBINT2_REALTYPE fp111;
fp111 = inteval->WQ_z[vi] * src1[((hsi*15+2)*1+lsi)*1];
LIBINT2_REALTYPE fp112;
fp112 = inteval->QC_z[vi] * src0[((hsi*15+2)*1+lsi)*1];
LIBINT2_REALTYPE fp110;
fp110 = fp112 + fp111;
LIBINT2_REALTYPE fp105;
fp105 = fp110 + fp106;
target[((hsi*21+5)*1+lsi)*1] = fp105;
LIBINT2_REALTYPE fp100;
fp100 = inteval->roe[vi] * src3[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp99;
fp99 = src2[((hsi*10+1)*1+lsi)*1] - fp100;
LIBINT2_REALTYPE fp101;
fp101 = 2 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp98;
fp98 = fp101 * fp99;
LIBINT2_REALTYPE fp103;
fp103 = inteval->WQ_y[vi] * src1[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp104;
fp104 = inteval->QC_y[vi] * src0[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp102;
fp102 = fp104 + fp103;
LIBINT2_REALTYPE fp97;
fp97 = fp102 + fp98;
target[((hsi*21+6)*1+lsi)*1] = fp97;
LIBINT2_REALTYPE fp95;
fp95 = inteval->WQ_z[vi] * src1[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp96;
fp96 = inteval->QC_z[vi] * src0[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp94;
fp94 = fp96 + fp95;
target[((hsi*21+7)*1+lsi)*1] = fp94;
LIBINT2_REALTYPE fp89;
fp89 = inteval->roe[vi] * src3[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp88;
fp88 = src2[((hsi*10+1)*1+lsi)*1] - fp89;
LIBINT2_REALTYPE fp90;
fp90 = 1 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp87;
fp87 = fp90 * fp88;
LIBINT2_REALTYPE fp92;
fp92 = inteval->WQ_z[vi] * src1[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp93;
fp93 = inteval->QC_z[vi] * src0[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp91;
fp91 = fp93 + fp92;
LIBINT2_REALTYPE fp86;
fp86 = fp91 + fp87;
target[((hsi*21+8)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp81;
fp81 = inteval->roe[vi] * src3[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp80;
fp80 = src2[((hsi*10+2)*1+lsi)*1] - fp81;
LIBINT2_REALTYPE fp82;
fp82 = 2 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp79;
fp79 = fp82 * fp80;
LIBINT2_REALTYPE fp84;
fp84 = inteval->WQ_z[vi] * src1[((hsi*15+5)*1+lsi)*1];
LIBINT2_REALTYPE fp85;
fp85 = inteval->QC_z[vi] * src0[((hsi*15+5)*1+lsi)*1];
LIBINT2_REALTYPE fp83;
fp83 = fp85 + fp84;
LIBINT2_REALTYPE fp78;
fp78 = fp83 + fp79;
target[((hsi*21+9)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp133;
fp133 = inteval->roe[vi] * src3[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp132;
fp132 = src2[((hsi*10+0)*1+lsi)*1] - fp133;
LIBINT2_REALTYPE fp134;
fp134 = 4 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp131;
fp131 = fp134 * fp132;
LIBINT2_REALTYPE fp136;
fp136 = inteval->WQ_x[vi] * src1[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp137;
fp137 = inteval->QC_x[vi] * src0[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp135;
fp135 = fp137 + fp136;
LIBINT2_REALTYPE fp130;
fp130 = fp135 + fp131;
target[((hsi*21+0)*1+lsi)*1] = fp130;
LIBINT2_REALTYPE fp68;
fp68 = inteval->WQ_z[vi] * src1[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp69;
fp69 = inteval->QC_z[vi] * src0[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp67;
fp67 = fp69 + fp68;
target[((hsi*21+11)*1+lsi)*1] = fp67;
LIBINT2_REALTYPE fp62;
fp62 = inteval->roe[vi] * src3[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = src2[((hsi*10+3)*1+lsi)*1] - fp62;
LIBINT2_REALTYPE fp63;
fp63 = 1 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp60;
fp60 = fp63 * fp61;
LIBINT2_REALTYPE fp65;
fp65 = inteval->WQ_z[vi] * src1[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = inteval->QC_z[vi] * src0[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = fp66 + fp65;
LIBINT2_REALTYPE fp59;
fp59 = fp64 + fp60;
target[((hsi*21+12)*1+lsi)*1] = fp59;
LIBINT2_REALTYPE fp54;
fp54 = inteval->roe[vi] * src3[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp53;
fp53 = src2[((hsi*10+4)*1+lsi)*1] - fp54;
LIBINT2_REALTYPE fp55;
fp55 = 2 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp52;
fp52 = fp55 * fp53;
LIBINT2_REALTYPE fp57;
fp57 = inteval->WQ_z[vi] * src1[((hsi*15+8)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = inteval->QC_z[vi] * src0[((hsi*15+8)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = fp58 + fp57;
LIBINT2_REALTYPE fp51;
fp51 = fp56 + fp52;
target[((hsi*21+13)*1+lsi)*1] = fp51;
LIBINT2_REALTYPE fp46;
fp46 = inteval->roe[vi] * src3[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp45;
fp45 = src2[((hsi*10+5)*1+lsi)*1] - fp46;
LIBINT2_REALTYPE fp47;
fp47 = 3 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp44;
fp44 = fp47 * fp45;
LIBINT2_REALTYPE fp49;
fp49 = inteval->WQ_z[vi] * src1[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = inteval->QC_z[vi] * src0[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = fp50 + fp49;
LIBINT2_REALTYPE fp43;
fp43 = fp48 + fp44;
target[((hsi*21+14)*1+lsi)*1] = fp43;
LIBINT2_REALTYPE fp38;
fp38 = inteval->roe[vi] * src3[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = src2[((hsi*10+6)*1+lsi)*1] - fp38;
LIBINT2_REALTYPE fp39;
fp39 = 4 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp36;
fp36 = fp39 * fp37;
LIBINT2_REALTYPE fp41;
fp41 = inteval->WQ_y[vi] * src1[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = inteval->QC_y[vi] * src0[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = fp42 + fp41;
LIBINT2_REALTYPE fp35;
fp35 = fp40 + fp36;
target[((hsi*21+15)*1+lsi)*1] = fp35;
LIBINT2_REALTYPE fp33;
fp33 = inteval->WQ_z[vi] * src1[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->QC_z[vi] * src0[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = fp34 + fp33;
target[((hsi*21+16)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp27;
fp27 = inteval->roe[vi] * src3[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = src2[((hsi*10+6)*1+lsi)*1] - fp27;
LIBINT2_REALTYPE fp28;
fp28 = 1 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp25;
fp25 = fp28 * fp26;
LIBINT2_REALTYPE fp30;
fp30 = inteval->WQ_z[vi] * src1[((hsi*15+11)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->QC_z[vi] * src0[((hsi*15+11)*1+lsi)*1];
LIBINT2_REALTYPE fp29;
fp29 = fp31 + fp30;
LIBINT2_REALTYPE fp24;
fp24 = fp29 + fp25;
target[((hsi*21+17)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp19;
fp19 = inteval->roe[vi] * src3[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = src2[((hsi*10+7)*1+lsi)*1] - fp19;
LIBINT2_REALTYPE fp20;
fp20 = 2 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp17;
fp17 = fp20 * fp18;
LIBINT2_REALTYPE fp22;
fp22 = inteval->WQ_z[vi] * src1[((hsi*15+12)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->QC_z[vi] * src0[((hsi*15+12)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = fp23 + fp22;
LIBINT2_REALTYPE fp16;
fp16 = fp21 + fp17;
target[((hsi*21+18)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp11;
fp11 = inteval->roe[vi] * src3[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = src2[((hsi*10+8)*1+lsi)*1] - fp11;
LIBINT2_REALTYPE fp12;
fp12 = 3 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp9;
fp9 = fp12 * fp10;
LIBINT2_REALTYPE fp14;
fp14 = inteval->WQ_z[vi] * src1[((hsi*15+13)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = inteval->QC_z[vi] * src0[((hsi*15+13)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = fp15 + fp14;
LIBINT2_REALTYPE fp8;
fp8 = fp13 + fp9;
target[((hsi*21+19)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp3;
fp3 = inteval->roe[vi] * src3[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = src2[((hsi*10+9)*1+lsi)*1] - fp3;
LIBINT2_REALTYPE fp4;
fp4 = 4 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp1;
fp1 = fp4 * fp2;
LIBINT2_REALTYPE fp6;
fp6 = inteval->WQ_z[vi] * src1[((hsi*15+14)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = inteval->QC_z[vi] * src0[((hsi*15+14)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = fp7 + fp6;
LIBINT2_REALTYPE fp0;
fp0 = fp5 + fp1;
target[((hsi*21+20)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp73;
fp73 = inteval->roe[vi] * src3[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = src2[((hsi*10+3)*1+lsi)*1] - fp73;
LIBINT2_REALTYPE fp74;
fp74 = 3 * inteval->oo2e[vi];
LIBINT2_REALTYPE fp71;
fp71 = fp74 * fp72;
LIBINT2_REALTYPE fp76;
fp76 = inteval->WQ_y[vi] * src1[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp77;
fp77 = inteval->QC_y[vi] * src0[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp75;
fp75 = fp77 + fp76;
LIBINT2_REALTYPE fp70;
fp70 = fp75 + fp71;
target[((hsi*21+10)*1+lsi)*1] = fp70;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 138 */
}

#ifdef __cplusplus
};
#endif
