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
void OSVRRP1InBra_aB_f__0__p__1___TwoPRep_s__0__s__1___Ab__up_0(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp114;
fp114 = inteval->WQ_y[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp115;
fp115 = inteval->QC_y[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp113;
fp113 = fp115 + fp114;
target[((hsi*30+1)*1+lsi)*1] = fp113;
LIBINT2_REALTYPE fp111;
fp111 = inteval->WQ_z[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp112;
fp112 = inteval->QC_z[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp110;
fp110 = fp112 + fp111;
target[((hsi*30+2)*1+lsi)*1] = fp110;
LIBINT2_REALTYPE fp106;
fp106 = 2 * inteval->oo2ze[vi];
LIBINT2_REALTYPE fp105;
fp105 = fp106 * src2[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp108;
fp108 = inteval->WQ_x[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp109;
fp109 = inteval->QC_x[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp107;
fp107 = fp109 + fp108;
LIBINT2_REALTYPE fp104;
fp104 = fp107 + fp105;
target[((hsi*30+3)*1+lsi)*1] = fp104;
LIBINT2_REALTYPE fp100;
fp100 = inteval->oo2ze[vi] * src2[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp102;
fp102 = inteval->WQ_y[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp103;
fp103 = inteval->QC_y[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp101;
fp101 = fp103 + fp102;
LIBINT2_REALTYPE fp99;
fp99 = fp101 + fp100;
target[((hsi*30+4)*1+lsi)*1] = fp99;
LIBINT2_REALTYPE fp97;
fp97 = inteval->WQ_z[vi] * src1[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp98;
fp98 = inteval->QC_z[vi] * src0[((hsi*10+1)*1+lsi)*1];
LIBINT2_REALTYPE fp96;
fp96 = fp98 + fp97;
target[((hsi*30+5)*1+lsi)*1] = fp96;
LIBINT2_REALTYPE fp92;
fp92 = fp106 * src2[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp94;
fp94 = inteval->WQ_x[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp95;
fp95 = inteval->QC_x[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp93;
fp93 = fp95 + fp94;
LIBINT2_REALTYPE fp91;
fp91 = fp93 + fp92;
target[((hsi*30+6)*1+lsi)*1] = fp91;
LIBINT2_REALTYPE fp89;
fp89 = inteval->WQ_y[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp90;
fp90 = inteval->QC_y[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp88;
fp88 = fp90 + fp89;
target[((hsi*30+7)*1+lsi)*1] = fp88;
LIBINT2_REALTYPE fp86;
fp86 = inteval->WQ_z[vi] * src1[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp87;
fp87 = inteval->QC_z[vi] * src0[((hsi*10+2)*1+lsi)*1];
LIBINT2_REALTYPE fp85;
fp85 = fp87 + fp86;
LIBINT2_REALTYPE fp84;
fp84 = fp85 + fp100;
target[((hsi*30+8)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp80;
fp80 = inteval->oo2ze[vi] * src2[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp82;
fp82 = inteval->WQ_x[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp83;
fp83 = inteval->QC_x[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp81;
fp81 = fp83 + fp82;
LIBINT2_REALTYPE fp79;
fp79 = fp81 + fp80;
target[((hsi*30+9)*1+lsi)*1] = fp79;
LIBINT2_REALTYPE fp77;
fp77 = inteval->WQ_y[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp78;
fp78 = inteval->QC_y[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp76;
fp76 = fp78 + fp77;
LIBINT2_REALTYPE fp75;
fp75 = fp76 + fp105;
target[((hsi*30+10)*1+lsi)*1] = fp75;
LIBINT2_REALTYPE fp73;
fp73 = inteval->WQ_z[vi] * src1[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp74;
fp74 = inteval->QC_z[vi] * src0[((hsi*10+3)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = fp74 + fp73;
target[((hsi*30+11)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp68;
fp68 = inteval->oo2ze[vi] * src2[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp70;
fp70 = inteval->WQ_x[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp71;
fp71 = inteval->QC_x[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp69;
fp69 = fp71 + fp70;
LIBINT2_REALTYPE fp67;
fp67 = fp69 + fp68;
target[((hsi*30+12)*1+lsi)*1] = fp67;
LIBINT2_REALTYPE fp63;
fp63 = inteval->oo2ze[vi] * src2[((hsi*6+2)*1+lsi)*1];
LIBINT2_REALTYPE fp65;
fp65 = inteval->WQ_y[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = inteval->QC_y[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = fp66 + fp65;
LIBINT2_REALTYPE fp62;
fp62 = fp64 + fp63;
target[((hsi*30+13)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp58;
fp58 = inteval->oo2ze[vi] * src2[((hsi*6+1)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = inteval->WQ_z[vi] * src1[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp61;
fp61 = inteval->QC_z[vi] * src0[((hsi*10+4)*1+lsi)*1];
LIBINT2_REALTYPE fp59;
fp59 = fp61 + fp60;
LIBINT2_REALTYPE fp57;
fp57 = fp59 + fp58;
target[((hsi*30+14)*1+lsi)*1] = fp57;
LIBINT2_REALTYPE fp118;
fp118 = 3 * inteval->oo2ze[vi];
LIBINT2_REALTYPE fp117;
fp117 = fp118 * src2[((hsi*6+0)*1+lsi)*1];
LIBINT2_REALTYPE fp120;
fp120 = inteval->WQ_x[vi] * src1[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp121;
fp121 = inteval->QC_x[vi] * src0[((hsi*10+0)*1+lsi)*1];
LIBINT2_REALTYPE fp119;
fp119 = fp121 + fp120;
LIBINT2_REALTYPE fp116;
fp116 = fp119 + fp117;
target[((hsi*30+0)*1+lsi)*1] = fp116;
LIBINT2_REALTYPE fp50;
fp50 = inteval->WQ_y[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp51;
fp51 = inteval->QC_y[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp49;
fp49 = fp51 + fp50;
target[((hsi*30+16)*1+lsi)*1] = fp49;
LIBINT2_REALTYPE fp47;
fp47 = inteval->WQ_z[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = inteval->QC_z[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = fp48 + fp47;
LIBINT2_REALTYPE fp45;
fp45 = fp46 + fp92;
target[((hsi*30+17)*1+lsi)*1] = fp45;
LIBINT2_REALTYPE fp43;
fp43 = inteval->WQ_x[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->QC_x[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = fp44 + fp43;
target[((hsi*30+18)*1+lsi)*1] = fp42;
LIBINT2_REALTYPE fp38;
fp38 = fp118 * src2[((hsi*6+3)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = inteval->WQ_y[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp41;
fp41 = inteval->QC_y[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = fp41 + fp40;
LIBINT2_REALTYPE fp37;
fp37 = fp39 + fp38;
target[((hsi*30+19)*1+lsi)*1] = fp37;
LIBINT2_REALTYPE fp35;
fp35 = inteval->WQ_z[vi] * src1[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = inteval->QC_z[vi] * src0[((hsi*10+6)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = fp36 + fp35;
target[((hsi*30+20)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp32;
fp32 = inteval->WQ_x[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = inteval->QC_x[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = fp33 + fp32;
target[((hsi*30+21)*1+lsi)*1] = fp31;
LIBINT2_REALTYPE fp27;
fp27 = fp106 * src2[((hsi*6+4)*1+lsi)*1];
LIBINT2_REALTYPE fp29;
fp29 = inteval->WQ_y[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->QC_y[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = fp30 + fp29;
LIBINT2_REALTYPE fp26;
fp26 = fp28 + fp27;
target[((hsi*30+22)*1+lsi)*1] = fp26;
LIBINT2_REALTYPE fp24;
fp24 = inteval->WQ_z[vi] * src1[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = inteval->QC_z[vi] * src0[((hsi*10+7)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = fp25 + fp24;
LIBINT2_REALTYPE fp22;
fp22 = fp23 + fp80;
target[((hsi*30+23)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp20;
fp20 = inteval->WQ_x[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = inteval->QC_x[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = fp21 + fp20;
target[((hsi*30+24)*1+lsi)*1] = fp19;
LIBINT2_REALTYPE fp53;
fp53 = inteval->oo2ze[vi] * src2[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = inteval->WQ_y[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = inteval->QC_y[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = fp18 + fp17;
LIBINT2_REALTYPE fp15;
fp15 = fp16 + fp53;
target[((hsi*30+25)*1+lsi)*1] = fp15;
LIBINT2_REALTYPE fp13;
fp13 = inteval->WQ_z[vi] * src1[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = inteval->QC_z[vi] * src0[((hsi*10+8)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = fp14 + fp13;
LIBINT2_REALTYPE fp11;
fp11 = fp12 + fp27;
target[((hsi*30+26)*1+lsi)*1] = fp11;
LIBINT2_REALTYPE fp9;
fp9 = inteval->WQ_x[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->QC_x[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = fp10 + fp9;
target[((hsi*30+27)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp6;
fp6 = inteval->WQ_y[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp7;
fp7 = inteval->QC_y[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = fp7 + fp6;
target[((hsi*30+28)*1+lsi)*1] = fp5;
LIBINT2_REALTYPE fp1;
fp1 = fp118 * src2[((hsi*6+5)*1+lsi)*1];
LIBINT2_REALTYPE fp3;
fp3 = inteval->WQ_z[vi] * src1[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->QC_z[vi] * src0[((hsi*10+9)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = fp4 + fp3;
LIBINT2_REALTYPE fp0;
fp0 = fp2 + fp1;
target[((hsi*30+29)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp55;
fp55 = inteval->WQ_x[vi] * src1[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = inteval->QC_x[vi] * src0[((hsi*10+5)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = fp56 + fp55;
LIBINT2_REALTYPE fp52;
fp52 = fp54 + fp53;
target[((hsi*30+15)*1+lsi)*1] = fp52;
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
