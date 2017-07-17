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
void CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_0_Sb__p__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp7;
fp7 = 0 + src2[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = 0 + src1[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp27;
fp27 = 0 + src1[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->BO_y[vi] * fp27;
LIBINT2_REALTYPE fp29;
fp29 = fp28 + fp30;
LIBINT2_REALTYPE fp48;
fp48 = 0 + src0[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp102;
fp102 = fp48 * fp29;
LIBINT2_REALTYPE fp101;
fp101 = fp102 * fp7;
target[((hsi*45+21)*1+lsi)*1] = fp101;
LIBINT2_REALTYPE fp8;
fp8 = 0 + src2[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = 0 + src0[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp21;
fp21 = 0 + src1[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = 0 + src1[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp23;
fp23 = inteval->BO_y[vi] * fp20;
LIBINT2_REALTYPE fp22;
fp22 = fp21 + fp23;
LIBINT2_REALTYPE fp104;
fp104 = fp47 * fp22;
LIBINT2_REALTYPE fp103;
fp103 = fp104 * fp8;
target[((hsi*45+20)*1+lsi)*1] = fp103;
LIBINT2_REALTYPE fp9;
fp9 = 0 + src2[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp19;
fp19 = inteval->BO_y[vi] * fp21;
LIBINT2_REALTYPE fp17;
fp17 = 0 + src1[((hsi*15+11)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = fp17 + fp19;
LIBINT2_REALTYPE fp106;
fp106 = fp47 * fp18;
LIBINT2_REALTYPE fp105;
fp105 = fp106 * fp9;
target[((hsi*45+19)*1+lsi)*1] = fp105;
LIBINT2_REALTYPE fp108;
fp108 = fp48 * fp22;
LIBINT2_REALTYPE fp107;
fp107 = fp108 * fp9;
target[((hsi*45+18)*1+lsi)*1] = fp107;
LIBINT2_REALTYPE fp4;
fp4 = 0 + src2[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = 0 + src1[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp41;
fp41 = 0 + src1[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->BO_y[vi] * fp41;
LIBINT2_REALTYPE fp43;
fp43 = fp42 + fp44;
LIBINT2_REALTYPE fp49;
fp49 = 0 + src0[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp110;
fp110 = fp49 * fp43;
LIBINT2_REALTYPE fp109;
fp109 = fp110 * fp4;
target[((hsi*45+17)*1+lsi)*1] = fp109;
LIBINT2_REALTYPE fp5;
fp5 = 0 + src2[((hsi*15+6)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = inteval->BO_y[vi] * fp42;
LIBINT2_REALTYPE fp38;
fp38 = 0 + src1[((hsi*15+2)*1+lsi)*1];
LIBINT2_REALTYPE fp39;
fp39 = fp38 + fp40;
LIBINT2_REALTYPE fp112;
fp112 = fp49 * fp39;
LIBINT2_REALTYPE fp111;
fp111 = fp112 * fp5;
target[((hsi*45+16)*1+lsi)*1] = fp111;
LIBINT2_REALTYPE fp50;
fp50 = 0 + src0[((hsi*15+7)*1+lsi)*1];
LIBINT2_REALTYPE fp114;
fp114 = fp50 * fp43;
LIBINT2_REALTYPE fp113;
fp113 = fp114 * fp5;
target[((hsi*45+15)*1+lsi)*1] = fp113;
LIBINT2_REALTYPE fp6;
fp6 = 0 + src2[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp35;
fp35 = 0 + src1[((hsi*15+4)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = 0 + src1[((hsi*15+3)*1+lsi)*1];
LIBINT2_REALTYPE fp37;
fp37 = inteval->BO_y[vi] * fp34;
LIBINT2_REALTYPE fp36;
fp36 = fp35 + fp37;
LIBINT2_REALTYPE fp116;
fp116 = fp49 * fp36;
LIBINT2_REALTYPE fp115;
fp115 = fp116 * fp6;
target[((hsi*45+14)*1+lsi)*1] = fp115;
LIBINT2_REALTYPE fp33;
fp33 = inteval->BO_y[vi] * fp35;
LIBINT2_REALTYPE fp31;
fp31 = 0 + src1[((hsi*15+5)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = fp31 + fp33;
LIBINT2_REALTYPE fp118;
fp118 = fp49 * fp32;
LIBINT2_REALTYPE fp117;
fp117 = fp118 * fp7;
target[((hsi*45+13)*1+lsi)*1] = fp117;
LIBINT2_REALTYPE fp120;
fp120 = fp50 * fp36;
LIBINT2_REALTYPE fp119;
fp119 = fp120 * fp7;
target[((hsi*45+12)*1+lsi)*1] = fp119;
LIBINT2_REALTYPE fp54;
fp54 = 0 + src0[((hsi*15+13)*1+lsi)*1];
LIBINT2_REALTYPE fp144;
fp144 = fp54 * fp43;
LIBINT2_REALTYPE fp143;
fp143 = fp144 * fp9;
target[((hsi*45+0)*1+lsi)*1] = fp143;
LIBINT2_REALTYPE fp26;
fp26 = inteval->BO_y[vi] * fp28;
LIBINT2_REALTYPE fp24;
fp24 = 0 + src1[((hsi*15+8)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = fp24 + fp26;
LIBINT2_REALTYPE fp124;
fp124 = fp49 * fp25;
LIBINT2_REALTYPE fp123;
fp123 = fp124 * fp9;
target[((hsi*45+10)*1+lsi)*1] = fp123;
LIBINT2_REALTYPE fp126;
fp126 = fp50 * fp29;
LIBINT2_REALTYPE fp125;
fp125 = fp126 * fp9;
target[((hsi*45+9)*1+lsi)*1] = fp125;
LIBINT2_REALTYPE fp51;
fp51 = 0 + src0[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp128;
fp128 = fp51 * fp43;
LIBINT2_REALTYPE fp127;
fp127 = fp128 * fp6;
target[((hsi*45+8)*1+lsi)*1] = fp127;
LIBINT2_REALTYPE fp130;
fp130 = fp51 * fp39;
LIBINT2_REALTYPE fp129;
fp129 = fp130 * fp7;
target[((hsi*45+7)*1+lsi)*1] = fp129;
LIBINT2_REALTYPE fp52;
fp52 = 0 + src0[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp132;
fp132 = fp52 * fp43;
LIBINT2_REALTYPE fp131;
fp131 = fp132 * fp7;
target[((hsi*45+6)*1+lsi)*1] = fp131;
LIBINT2_REALTYPE fp134;
fp134 = fp51 * fp36;
LIBINT2_REALTYPE fp133;
fp133 = fp134 * fp8;
target[((hsi*45+5)*1+lsi)*1] = fp133;
LIBINT2_REALTYPE fp136;
fp136 = fp51 * fp32;
LIBINT2_REALTYPE fp135;
fp135 = fp136 * fp9;
target[((hsi*45+4)*1+lsi)*1] = fp135;
LIBINT2_REALTYPE fp138;
fp138 = fp52 * fp36;
LIBINT2_REALTYPE fp137;
fp137 = fp138 * fp9;
target[((hsi*45+3)*1+lsi)*1] = fp137;
LIBINT2_REALTYPE fp53;
fp53 = 0 + src0[((hsi*15+12)*1+lsi)*1];
LIBINT2_REALTYPE fp140;
fp140 = fp53 * fp43;
LIBINT2_REALTYPE fp139;
fp139 = fp140 * fp8;
target[((hsi*45+2)*1+lsi)*1] = fp139;
LIBINT2_REALTYPE fp142;
fp142 = fp53 * fp39;
LIBINT2_REALTYPE fp141;
fp141 = fp142 * fp9;
target[((hsi*45+1)*1+lsi)*1] = fp141;
LIBINT2_REALTYPE fp122;
fp122 = fp49 * fp29;
LIBINT2_REALTYPE fp121;
fp121 = fp122 * fp8;
target[((hsi*45+11)*1+lsi)*1] = fp121;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*15+13)*1+lsi)*1];
LIBINT2_REALTYPE fp45;
fp45 = 0 + src0[((hsi*15+0)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = fp45 * fp43;
LIBINT2_REALTYPE fp55;
fp55 = fp56 * fp0;
target[((hsi*45+44)*1+lsi)*1] = fp55;
LIBINT2_REALTYPE fp1;
fp1 = 0 + src2[((hsi*15+12)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = fp45 * fp39;
LIBINT2_REALTYPE fp57;
fp57 = fp58 * fp1;
target[((hsi*45+43)*1+lsi)*1] = fp57;
LIBINT2_REALTYPE fp46;
fp46 = 0 + src0[((hsi*15+1)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = fp46 * fp43;
LIBINT2_REALTYPE fp59;
fp59 = fp60 * fp1;
target[((hsi*45+42)*1+lsi)*1] = fp59;
LIBINT2_REALTYPE fp2;
fp2 = 0 + src2[((hsi*15+10)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = fp45 * fp36;
LIBINT2_REALTYPE fp61;
fp61 = fp62 * fp2;
target[((hsi*45+41)*1+lsi)*1] = fp61;
LIBINT2_REALTYPE fp3;
fp3 = 0 + src2[((hsi*15+9)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = fp45 * fp32;
LIBINT2_REALTYPE fp63;
fp63 = fp64 * fp3;
target[((hsi*45+40)*1+lsi)*1] = fp63;
LIBINT2_REALTYPE fp66;
fp66 = fp46 * fp36;
LIBINT2_REALTYPE fp65;
fp65 = fp66 * fp3;
target[((hsi*45+39)*1+lsi)*1] = fp65;
LIBINT2_REALTYPE fp68;
fp68 = fp45 * fp29;
LIBINT2_REALTYPE fp67;
fp67 = fp68 * fp4;
target[((hsi*45+38)*1+lsi)*1] = fp67;
LIBINT2_REALTYPE fp70;
fp70 = fp45 * fp25;
LIBINT2_REALTYPE fp69;
fp69 = fp70 * fp5;
target[((hsi*45+37)*1+lsi)*1] = fp69;
LIBINT2_REALTYPE fp72;
fp72 = fp46 * fp29;
LIBINT2_REALTYPE fp71;
fp71 = fp72 * fp5;
target[((hsi*45+36)*1+lsi)*1] = fp71;
LIBINT2_REALTYPE fp74;
fp74 = fp45 * fp22;
LIBINT2_REALTYPE fp73;
fp73 = fp74 * fp6;
target[((hsi*45+35)*1+lsi)*1] = fp73;
LIBINT2_REALTYPE fp100;
fp100 = fp47 * fp25;
LIBINT2_REALTYPE fp99;
fp99 = fp100 * fp7;
target[((hsi*45+22)*1+lsi)*1] = fp99;
LIBINT2_REALTYPE fp78;
fp78 = fp46 * fp22;
LIBINT2_REALTYPE fp77;
fp77 = fp78 * fp7;
target[((hsi*45+33)*1+lsi)*1] = fp77;
LIBINT2_REALTYPE fp14;
fp14 = 0 + src1[((hsi*15+13)*1+lsi)*1];
LIBINT2_REALTYPE fp13;
fp13 = 0 + src1[((hsi*15+12)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->BO_y[vi] * fp13;
LIBINT2_REALTYPE fp15;
fp15 = fp14 + fp16;
LIBINT2_REALTYPE fp80;
fp80 = fp45 * fp15;
LIBINT2_REALTYPE fp79;
fp79 = fp80 * fp8;
target[((hsi*45+32)*1+lsi)*1] = fp79;
LIBINT2_REALTYPE fp12;
fp12 = inteval->BO_y[vi] * fp14;
LIBINT2_REALTYPE fp10;
fp10 = 0 + src1[((hsi*15+14)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = fp10 + fp12;
LIBINT2_REALTYPE fp82;
fp82 = fp45 * fp11;
LIBINT2_REALTYPE fp81;
fp81 = fp82 * fp9;
target[((hsi*45+31)*1+lsi)*1] = fp81;
LIBINT2_REALTYPE fp84;
fp84 = fp46 * fp15;
LIBINT2_REALTYPE fp83;
fp83 = fp84 * fp9;
target[((hsi*45+30)*1+lsi)*1] = fp83;
LIBINT2_REALTYPE fp86;
fp86 = fp47 * fp43;
LIBINT2_REALTYPE fp85;
fp85 = fp86 * fp2;
target[((hsi*45+29)*1+lsi)*1] = fp85;
LIBINT2_REALTYPE fp88;
fp88 = fp47 * fp39;
LIBINT2_REALTYPE fp87;
fp87 = fp88 * fp3;
target[((hsi*45+28)*1+lsi)*1] = fp87;
LIBINT2_REALTYPE fp90;
fp90 = fp48 * fp43;
LIBINT2_REALTYPE fp89;
fp89 = fp90 * fp3;
target[((hsi*45+27)*1+lsi)*1] = fp89;
LIBINT2_REALTYPE fp92;
fp92 = fp47 * fp36;
LIBINT2_REALTYPE fp91;
fp91 = fp92 * fp4;
target[((hsi*45+26)*1+lsi)*1] = fp91;
LIBINT2_REALTYPE fp94;
fp94 = fp47 * fp32;
LIBINT2_REALTYPE fp93;
fp93 = fp94 * fp5;
target[((hsi*45+25)*1+lsi)*1] = fp93;
LIBINT2_REALTYPE fp96;
fp96 = fp48 * fp36;
LIBINT2_REALTYPE fp95;
fp95 = fp96 * fp5;
target[((hsi*45+24)*1+lsi)*1] = fp95;
LIBINT2_REALTYPE fp98;
fp98 = fp47 * fp29;
LIBINT2_REALTYPE fp97;
fp97 = fp98 * fp6;
target[((hsi*45+23)*1+lsi)*1] = fp97;
LIBINT2_REALTYPE fp76;
fp76 = fp45 * fp18;
LIBINT2_REALTYPE fp75;
fp75 = fp76 * fp7;
target[((hsi*45+34)*1+lsi)*1] = fp75;
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
