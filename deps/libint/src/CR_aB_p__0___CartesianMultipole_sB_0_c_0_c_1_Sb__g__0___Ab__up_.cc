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
void CR_aB_p__0___CartesianMultipole_sB_0_c_0_c_1_Sb__g__0___Ab__up_(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, const LIBINT2_REALTYPE* src2) {

LIBINT2_REALTYPE*const  stack = target;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp29;
fp29 = 0 + src2[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = 0 + src2[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp31;
fp31 = inteval->BO_z[vi] * fp28;
LIBINT2_REALTYPE fp30;
fp30 = fp29 + fp31;
LIBINT2_REALTYPE fp43;
fp43 = 0 + src0[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp33;
fp33 = 0 + src1[((hsi*12+9)*1+lsi)*1];
LIBINT2_REALTYPE fp99;
fp99 = fp43 * fp33;
LIBINT2_REALTYPE fp98;
fp98 = fp99 * fp30;
target[((hsi*45+21)*1+lsi)*1] = fp98;
LIBINT2_REALTYPE fp22;
fp22 = 0 + src2[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp25;
fp25 = 0 + src2[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->BO_z[vi] * fp25;
LIBINT2_REALTYPE fp23;
fp23 = fp22 + fp24;
LIBINT2_REALTYPE fp44;
fp44 = 0 + src0[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = 0 + src1[((hsi*12+6)*1+lsi)*1];
LIBINT2_REALTYPE fp101;
fp101 = fp44 * fp36;
LIBINT2_REALTYPE fp100;
fp100 = fp101 * fp23;
target[((hsi*45+20)*1+lsi)*1] = fp100;
LIBINT2_REALTYPE fp27;
fp27 = inteval->BO_z[vi] * fp29;
LIBINT2_REALTYPE fp26;
fp26 = fp25 + fp27;
LIBINT2_REALTYPE fp35;
fp35 = 0 + src1[((hsi*12+7)*1+lsi)*1];
LIBINT2_REALTYPE fp103;
fp103 = fp44 * fp35;
LIBINT2_REALTYPE fp102;
fp102 = fp103 * fp26;
target[((hsi*45+19)*1+lsi)*1] = fp102;
LIBINT2_REALTYPE fp34;
fp34 = 0 + src1[((hsi*12+8)*1+lsi)*1];
LIBINT2_REALTYPE fp105;
fp105 = fp44 * fp34;
LIBINT2_REALTYPE fp104;
fp104 = fp105 * fp30;
target[((hsi*45+18)*1+lsi)*1] = fp104;
LIBINT2_REALTYPE fp45;
fp45 = 0 + src0[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp107;
fp107 = fp45 * fp36;
LIBINT2_REALTYPE fp106;
fp106 = fp107 * fp26;
target[((hsi*45+17)*1+lsi)*1] = fp106;
LIBINT2_REALTYPE fp109;
fp109 = fp45 * fp35;
LIBINT2_REALTYPE fp108;
fp108 = fp109 * fp30;
target[((hsi*45+16)*1+lsi)*1] = fp108;
LIBINT2_REALTYPE fp46;
fp46 = 0 + src0[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp111;
fp111 = fp46 * fp36;
LIBINT2_REALTYPE fp110;
fp110 = fp111 * fp30;
target[((hsi*45+15)*1+lsi)*1] = fp110;
LIBINT2_REALTYPE fp19;
fp19 = 0 + src2[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = inteval->BO_z[vi] * fp19;
LIBINT2_REALTYPE fp16;
fp16 = 0 + src2[((hsi*12+5)*1+lsi)*1];
LIBINT2_REALTYPE fp17;
fp17 = fp16 + fp18;
LIBINT2_REALTYPE fp41;
fp41 = 0 + src1[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp47;
fp47 = 0 + src0[((hsi*12+6)*1+lsi)*1];
LIBINT2_REALTYPE fp113;
fp113 = fp47 * fp41;
LIBINT2_REALTYPE fp112;
fp112 = fp113 * fp17;
target[((hsi*45+14)*1+lsi)*1] = fp112;
LIBINT2_REALTYPE fp21;
fp21 = inteval->BO_z[vi] * fp22;
LIBINT2_REALTYPE fp20;
fp20 = fp19 + fp21;
LIBINT2_REALTYPE fp40;
fp40 = 0 + src1[((hsi*12+1)*1+lsi)*1];
LIBINT2_REALTYPE fp115;
fp115 = fp47 * fp40;
LIBINT2_REALTYPE fp114;
fp114 = fp115 * fp20;
target[((hsi*45+13)*1+lsi)*1] = fp114;
LIBINT2_REALTYPE fp39;
fp39 = 0 + src1[((hsi*12+2)*1+lsi)*1];
LIBINT2_REALTYPE fp117;
fp117 = fp47 * fp39;
LIBINT2_REALTYPE fp116;
fp116 = fp117 * fp23;
target[((hsi*45+12)*1+lsi)*1] = fp116;
LIBINT2_REALTYPE fp51;
fp51 = 0 + src0[((hsi*12+10)*1+lsi)*1];
LIBINT2_REALTYPE fp141;
fp141 = fp51 * fp41;
LIBINT2_REALTYPE fp140;
fp140 = fp141 * fp30;
target[((hsi*45+0)*1+lsi)*1] = fp140;
LIBINT2_REALTYPE fp37;
fp37 = 0 + src1[((hsi*12+4)*1+lsi)*1];
LIBINT2_REALTYPE fp121;
fp121 = fp47 * fp37;
LIBINT2_REALTYPE fp120;
fp120 = fp121 * fp30;
target[((hsi*45+10)*1+lsi)*1] = fp120;
LIBINT2_REALTYPE fp48;
fp48 = 0 + src0[((hsi*12+7)*1+lsi)*1];
LIBINT2_REALTYPE fp123;
fp123 = fp48 * fp41;
LIBINT2_REALTYPE fp122;
fp122 = fp123 * fp20;
target[((hsi*45+9)*1+lsi)*1] = fp122;
LIBINT2_REALTYPE fp125;
fp125 = fp48 * fp40;
LIBINT2_REALTYPE fp124;
fp124 = fp125 * fp23;
target[((hsi*45+8)*1+lsi)*1] = fp124;
LIBINT2_REALTYPE fp127;
fp127 = fp48 * fp39;
LIBINT2_REALTYPE fp126;
fp126 = fp127 * fp26;
target[((hsi*45+7)*1+lsi)*1] = fp126;
LIBINT2_REALTYPE fp38;
fp38 = 0 + src1[((hsi*12+3)*1+lsi)*1];
LIBINT2_REALTYPE fp129;
fp129 = fp48 * fp38;
LIBINT2_REALTYPE fp128;
fp128 = fp129 * fp30;
target[((hsi*45+6)*1+lsi)*1] = fp128;
LIBINT2_REALTYPE fp49;
fp49 = 0 + src0[((hsi*12+8)*1+lsi)*1];
LIBINT2_REALTYPE fp131;
fp131 = fp49 * fp41;
LIBINT2_REALTYPE fp130;
fp130 = fp131 * fp23;
target[((hsi*45+5)*1+lsi)*1] = fp130;
LIBINT2_REALTYPE fp133;
fp133 = fp49 * fp40;
LIBINT2_REALTYPE fp132;
fp132 = fp133 * fp26;
target[((hsi*45+4)*1+lsi)*1] = fp132;
LIBINT2_REALTYPE fp135;
fp135 = fp49 * fp39;
LIBINT2_REALTYPE fp134;
fp134 = fp135 * fp30;
target[((hsi*45+3)*1+lsi)*1] = fp134;
LIBINT2_REALTYPE fp50;
fp50 = 0 + src0[((hsi*12+9)*1+lsi)*1];
LIBINT2_REALTYPE fp137;
fp137 = fp50 * fp41;
LIBINT2_REALTYPE fp136;
fp136 = fp137 * fp26;
target[((hsi*45+2)*1+lsi)*1] = fp136;
LIBINT2_REALTYPE fp139;
fp139 = fp50 * fp40;
LIBINT2_REALTYPE fp138;
fp138 = fp139 * fp30;
target[((hsi*45+1)*1+lsi)*1] = fp138;
LIBINT2_REALTYPE fp119;
fp119 = fp47 * fp38;
LIBINT2_REALTYPE fp118;
fp118 = fp119 * fp26;
target[((hsi*45+11)*1+lsi)*1] = fp118;
LIBINT2_REALTYPE fp3;
fp3 = 0 + src2[((hsi*12+10)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->BO_z[vi] * fp3;
LIBINT2_REALTYPE fp0;
fp0 = 0 + src2[((hsi*12+11)*1+lsi)*1];
LIBINT2_REALTYPE fp1;
fp1 = fp0 + fp2;
LIBINT2_REALTYPE fp42;
fp42 = 0 + src0[((hsi*12+0)*1+lsi)*1];
LIBINT2_REALTYPE fp53;
fp53 = fp42 * fp41;
LIBINT2_REALTYPE fp52;
fp52 = fp53 * fp1;
target[((hsi*45+44)*1+lsi)*1] = fp52;
LIBINT2_REALTYPE fp6;
fp6 = 0 + src2[((hsi*12+9)*1+lsi)*1];
LIBINT2_REALTYPE fp5;
fp5 = inteval->BO_z[vi] * fp6;
LIBINT2_REALTYPE fp4;
fp4 = fp3 + fp5;
LIBINT2_REALTYPE fp55;
fp55 = fp42 * fp40;
LIBINT2_REALTYPE fp54;
fp54 = fp55 * fp4;
target[((hsi*45+43)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp9;
fp9 = 0 + src2[((hsi*12+8)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->BO_z[vi] * fp9;
LIBINT2_REALTYPE fp7;
fp7 = fp6 + fp8;
LIBINT2_REALTYPE fp57;
fp57 = fp42 * fp39;
LIBINT2_REALTYPE fp56;
fp56 = fp57 * fp7;
target[((hsi*45+42)*1+lsi)*1] = fp56;
LIBINT2_REALTYPE fp13;
fp13 = 0 + src2[((hsi*12+7)*1+lsi)*1];
LIBINT2_REALTYPE fp11;
fp11 = inteval->BO_z[vi] * fp13;
LIBINT2_REALTYPE fp10;
fp10 = fp9 + fp11;
LIBINT2_REALTYPE fp59;
fp59 = fp42 * fp38;
LIBINT2_REALTYPE fp58;
fp58 = fp59 * fp10;
target[((hsi*45+41)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp12;
fp12 = 0 + src2[((hsi*12+6)*1+lsi)*1];
LIBINT2_REALTYPE fp15;
fp15 = inteval->BO_z[vi] * fp12;
LIBINT2_REALTYPE fp14;
fp14 = fp13 + fp15;
LIBINT2_REALTYPE fp61;
fp61 = fp42 * fp37;
LIBINT2_REALTYPE fp60;
fp60 = fp61 * fp14;
target[((hsi*45+40)*1+lsi)*1] = fp60;
LIBINT2_REALTYPE fp63;
fp63 = fp43 * fp41;
LIBINT2_REALTYPE fp62;
fp62 = fp63 * fp4;
target[((hsi*45+39)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp65;
fp65 = fp43 * fp40;
LIBINT2_REALTYPE fp64;
fp64 = fp65 * fp7;
target[((hsi*45+38)*1+lsi)*1] = fp64;
LIBINT2_REALTYPE fp67;
fp67 = fp43 * fp39;
LIBINT2_REALTYPE fp66;
fp66 = fp67 * fp10;
target[((hsi*45+37)*1+lsi)*1] = fp66;
LIBINT2_REALTYPE fp69;
fp69 = fp43 * fp38;
LIBINT2_REALTYPE fp68;
fp68 = fp69 * fp14;
target[((hsi*45+36)*1+lsi)*1] = fp68;
LIBINT2_REALTYPE fp71;
fp71 = fp44 * fp41;
LIBINT2_REALTYPE fp70;
fp70 = fp71 * fp7;
target[((hsi*45+35)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp97;
fp97 = fp43 * fp34;
LIBINT2_REALTYPE fp96;
fp96 = fp97 * fp26;
target[((hsi*45+22)*1+lsi)*1] = fp96;
LIBINT2_REALTYPE fp75;
fp75 = fp44 * fp39;
LIBINT2_REALTYPE fp74;
fp74 = fp75 * fp14;
target[((hsi*45+33)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp77;
fp77 = fp45 * fp41;
LIBINT2_REALTYPE fp76;
fp76 = fp77 * fp10;
target[((hsi*45+32)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp79;
fp79 = fp45 * fp40;
LIBINT2_REALTYPE fp78;
fp78 = fp79 * fp14;
target[((hsi*45+31)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp81;
fp81 = fp46 * fp41;
LIBINT2_REALTYPE fp80;
fp80 = fp81 * fp14;
target[((hsi*45+30)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp83;
fp83 = fp42 * fp36;
LIBINT2_REALTYPE fp82;
fp82 = fp83 * fp17;
target[((hsi*45+29)*1+lsi)*1] = fp82;
LIBINT2_REALTYPE fp85;
fp85 = fp42 * fp35;
LIBINT2_REALTYPE fp84;
fp84 = fp85 * fp20;
target[((hsi*45+28)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp87;
fp87 = fp42 * fp34;
LIBINT2_REALTYPE fp86;
fp86 = fp87 * fp23;
target[((hsi*45+27)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp89;
fp89 = fp42 * fp33;
LIBINT2_REALTYPE fp88;
fp88 = fp89 * fp26;
target[((hsi*45+26)*1+lsi)*1] = fp88;
LIBINT2_REALTYPE fp32;
fp32 = 0 + src1[((hsi*12+10)*1+lsi)*1];
LIBINT2_REALTYPE fp91;
fp91 = fp42 * fp32;
LIBINT2_REALTYPE fp90;
fp90 = fp91 * fp30;
target[((hsi*45+25)*1+lsi)*1] = fp90;
LIBINT2_REALTYPE fp93;
fp93 = fp43 * fp36;
LIBINT2_REALTYPE fp92;
fp92 = fp93 * fp20;
target[((hsi*45+24)*1+lsi)*1] = fp92;
LIBINT2_REALTYPE fp95;
fp95 = fp43 * fp35;
LIBINT2_REALTYPE fp94;
fp94 = fp95 * fp23;
target[((hsi*45+23)*1+lsi)*1] = fp94;
LIBINT2_REALTYPE fp73;
fp73 = fp44 * fp40;
LIBINT2_REALTYPE fp72;
fp72 = fp73 * fp10;
target[((hsi*45+34)*1+lsi)*1] = fp72;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 142 */
}

#ifdef __cplusplus
};
#endif
