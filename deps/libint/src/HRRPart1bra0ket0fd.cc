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
void HRRPart1bra0ket0fd(const Libint_t* inteval, LIBINT2_REALTYPE* target, const LIBINT2_REALTYPE* src0, const LIBINT2_REALTYPE* src1, int highdim) {

LIBINT2_REALTYPE*const  stack = target;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int hsi = 0; hsi<highdim; hsi++) {
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp61;
fp61 = inteval->CD_z[vi] * src1[((hsi*30+14)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = src0[((hsi*45+26)*1+lsi)*1] + fp61;
target[((hsi*60+29)*1+lsi)*1] = fp60;
LIBINT2_REALTYPE fp63;
fp63 = inteval->CD_z[vi] * src1[((hsi*30+13)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = src0[((hsi*45+25)*1+lsi)*1] + fp63;
target[((hsi*60+28)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp65;
fp65 = inteval->CD_y[vi] * src1[((hsi*30+13)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = src0[((hsi*45+22)*1+lsi)*1] + fp65;
target[((hsi*60+27)*1+lsi)*1] = fp64;
LIBINT2_REALTYPE fp67;
fp67 = inteval->CD_z[vi] * src1[((hsi*30+12)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = src0[((hsi*45+24)*1+lsi)*1] + fp67;
target[((hsi*60+26)*1+lsi)*1] = fp66;
LIBINT2_REALTYPE fp69;
fp69 = inteval->CD_y[vi] * src1[((hsi*30+12)*1+lsi)*1];
LIBINT2_REALTYPE fp68;
fp68 = src0[((hsi*45+21)*1+lsi)*1] + fp69;
target[((hsi*60+25)*1+lsi)*1] = fp68;
LIBINT2_REALTYPE fp71;
fp71 = inteval->CD_x[vi] * src1[((hsi*30+12)*1+lsi)*1];
LIBINT2_REALTYPE fp70;
fp70 = src0[((hsi*45+12)*1+lsi)*1] + fp71;
target[((hsi*60+24)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp73;
fp73 = inteval->CD_z[vi] * src1[((hsi*30+11)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = src0[((hsi*45+23)*1+lsi)*1] + fp73;
target[((hsi*60+23)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp75;
fp75 = inteval->CD_z[vi] * src1[((hsi*30+10)*1+lsi)*1];
LIBINT2_REALTYPE fp74;
fp74 = src0[((hsi*45+22)*1+lsi)*1] + fp75;
target[((hsi*60+22)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp77;
fp77 = inteval->CD_y[vi] * src1[((hsi*30+10)*1+lsi)*1];
LIBINT2_REALTYPE fp76;
fp76 = src0[((hsi*45+19)*1+lsi)*1] + fp77;
target[((hsi*60+21)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp79;
fp79 = inteval->CD_z[vi] * src1[((hsi*30+9)*1+lsi)*1];
LIBINT2_REALTYPE fp78;
fp78 = src0[((hsi*45+21)*1+lsi)*1] + fp79;
target[((hsi*60+20)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp81;
fp81 = inteval->CD_y[vi] * src1[((hsi*30+9)*1+lsi)*1];
LIBINT2_REALTYPE fp80;
fp80 = src0[((hsi*45+18)*1+lsi)*1] + fp81;
target[((hsi*60+19)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp83;
fp83 = inteval->CD_x[vi] * src1[((hsi*30+9)*1+lsi)*1];
LIBINT2_REALTYPE fp82;
fp82 = src0[((hsi*45+9)*1+lsi)*1] + fp83;
target[((hsi*60+18)*1+lsi)*1] = fp82;
LIBINT2_REALTYPE fp85;
fp85 = inteval->CD_z[vi] * src1[((hsi*30+8)*1+lsi)*1];
LIBINT2_REALTYPE fp84;
fp84 = src0[((hsi*45+17)*1+lsi)*1] + fp85;
target[((hsi*60+17)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp87;
fp87 = inteval->CD_z[vi] * src1[((hsi*30+7)*1+lsi)*1];
LIBINT2_REALTYPE fp86;
fp86 = src0[((hsi*45+16)*1+lsi)*1] + fp87;
target[((hsi*60+16)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp119;
fp119 = inteval->CD_x[vi] * src1[((hsi*30+0)*1+lsi)*1];
LIBINT2_REALTYPE fp118;
fp118 = src0[((hsi*45+0)*1+lsi)*1] + fp119;
target[((hsi*60+0)*1+lsi)*1] = fp118;
LIBINT2_REALTYPE fp91;
fp91 = inteval->CD_z[vi] * src1[((hsi*30+6)*1+lsi)*1];
LIBINT2_REALTYPE fp90;
fp90 = src0[((hsi*45+15)*1+lsi)*1] + fp91;
target[((hsi*60+14)*1+lsi)*1] = fp90;
LIBINT2_REALTYPE fp93;
fp93 = inteval->CD_y[vi] * src1[((hsi*30+6)*1+lsi)*1];
LIBINT2_REALTYPE fp92;
fp92 = src0[((hsi*45+12)*1+lsi)*1] + fp93;
target[((hsi*60+13)*1+lsi)*1] = fp92;
LIBINT2_REALTYPE fp95;
fp95 = inteval->CD_x[vi] * src1[((hsi*30+6)*1+lsi)*1];
LIBINT2_REALTYPE fp94;
fp94 = src0[((hsi*45+6)*1+lsi)*1] + fp95;
target[((hsi*60+12)*1+lsi)*1] = fp94;
LIBINT2_REALTYPE fp97;
fp97 = inteval->CD_z[vi] * src1[((hsi*30+5)*1+lsi)*1];
LIBINT2_REALTYPE fp96;
fp96 = src0[((hsi*45+14)*1+lsi)*1] + fp97;
target[((hsi*60+11)*1+lsi)*1] = fp96;
LIBINT2_REALTYPE fp99;
fp99 = inteval->CD_z[vi] * src1[((hsi*30+4)*1+lsi)*1];
LIBINT2_REALTYPE fp98;
fp98 = src0[((hsi*45+13)*1+lsi)*1] + fp99;
target[((hsi*60+10)*1+lsi)*1] = fp98;
LIBINT2_REALTYPE fp101;
fp101 = inteval->CD_y[vi] * src1[((hsi*30+4)*1+lsi)*1];
LIBINT2_REALTYPE fp100;
fp100 = src0[((hsi*45+10)*1+lsi)*1] + fp101;
target[((hsi*60+9)*1+lsi)*1] = fp100;
LIBINT2_REALTYPE fp103;
fp103 = inteval->CD_z[vi] * src1[((hsi*30+3)*1+lsi)*1];
LIBINT2_REALTYPE fp102;
fp102 = src0[((hsi*45+12)*1+lsi)*1] + fp103;
target[((hsi*60+8)*1+lsi)*1] = fp102;
LIBINT2_REALTYPE fp105;
fp105 = inteval->CD_y[vi] * src1[((hsi*30+3)*1+lsi)*1];
LIBINT2_REALTYPE fp104;
fp104 = src0[((hsi*45+9)*1+lsi)*1] + fp105;
target[((hsi*60+7)*1+lsi)*1] = fp104;
LIBINT2_REALTYPE fp107;
fp107 = inteval->CD_x[vi] * src1[((hsi*30+3)*1+lsi)*1];
LIBINT2_REALTYPE fp106;
fp106 = src0[((hsi*45+3)*1+lsi)*1] + fp107;
target[((hsi*60+6)*1+lsi)*1] = fp106;
LIBINT2_REALTYPE fp109;
fp109 = inteval->CD_z[vi] * src1[((hsi*30+2)*1+lsi)*1];
LIBINT2_REALTYPE fp108;
fp108 = src0[((hsi*45+8)*1+lsi)*1] + fp109;
target[((hsi*60+5)*1+lsi)*1] = fp108;
LIBINT2_REALTYPE fp111;
fp111 = inteval->CD_z[vi] * src1[((hsi*30+1)*1+lsi)*1];
LIBINT2_REALTYPE fp110;
fp110 = src0[((hsi*45+7)*1+lsi)*1] + fp111;
target[((hsi*60+4)*1+lsi)*1] = fp110;
LIBINT2_REALTYPE fp113;
fp113 = inteval->CD_y[vi] * src1[((hsi*30+1)*1+lsi)*1];
LIBINT2_REALTYPE fp112;
fp112 = src0[((hsi*45+4)*1+lsi)*1] + fp113;
target[((hsi*60+3)*1+lsi)*1] = fp112;
LIBINT2_REALTYPE fp115;
fp115 = inteval->CD_z[vi] * src1[((hsi*30+0)*1+lsi)*1];
LIBINT2_REALTYPE fp114;
fp114 = src0[((hsi*45+6)*1+lsi)*1] + fp115;
target[((hsi*60+2)*1+lsi)*1] = fp114;
LIBINT2_REALTYPE fp117;
fp117 = inteval->CD_y[vi] * src1[((hsi*30+0)*1+lsi)*1];
LIBINT2_REALTYPE fp116;
fp116 = src0[((hsi*45+3)*1+lsi)*1] + fp117;
target[((hsi*60+1)*1+lsi)*1] = fp116;
LIBINT2_REALTYPE fp89;
fp89 = inteval->CD_y[vi] * src1[((hsi*30+7)*1+lsi)*1];
LIBINT2_REALTYPE fp88;
fp88 = src0[((hsi*45+13)*1+lsi)*1] + fp89;
target[((hsi*60+15)*1+lsi)*1] = fp88;
LIBINT2_REALTYPE fp1;
fp1 = inteval->CD_z[vi] * src1[((hsi*30+29)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = src0[((hsi*45+44)*1+lsi)*1] + fp1;
target[((hsi*60+59)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp3;
fp3 = inteval->CD_z[vi] * src1[((hsi*30+28)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = src0[((hsi*45+43)*1+lsi)*1] + fp3;
target[((hsi*60+58)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->CD_y[vi] * src1[((hsi*30+28)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = src0[((hsi*45+40)*1+lsi)*1] + fp5;
target[((hsi*60+57)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp7;
fp7 = inteval->CD_z[vi] * src1[((hsi*30+27)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = src0[((hsi*45+42)*1+lsi)*1] + fp7;
target[((hsi*60+56)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp9;
fp9 = inteval->CD_y[vi] * src1[((hsi*30+27)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = src0[((hsi*45+39)*1+lsi)*1] + fp9;
target[((hsi*60+55)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp11;
fp11 = inteval->CD_x[vi] * src1[((hsi*30+27)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = src0[((hsi*45+27)*1+lsi)*1] + fp11;
target[((hsi*60+54)*1+lsi)*1] = fp10;
LIBINT2_REALTYPE fp13;
fp13 = inteval->CD_z[vi] * src1[((hsi*30+26)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = src0[((hsi*45+41)*1+lsi)*1] + fp13;
target[((hsi*60+53)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp15;
fp15 = inteval->CD_z[vi] * src1[((hsi*30+25)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = src0[((hsi*45+40)*1+lsi)*1] + fp15;
target[((hsi*60+52)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp17;
fp17 = inteval->CD_y[vi] * src1[((hsi*30+25)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = src0[((hsi*45+37)*1+lsi)*1] + fp17;
target[((hsi*60+51)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp19;
fp19 = inteval->CD_z[vi] * src1[((hsi*30+24)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = src0[((hsi*45+39)*1+lsi)*1] + fp19;
target[((hsi*60+50)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp21;
fp21 = inteval->CD_y[vi] * src1[((hsi*30+24)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = src0[((hsi*45+36)*1+lsi)*1] + fp21;
target[((hsi*60+49)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp23;
fp23 = inteval->CD_x[vi] * src1[((hsi*30+24)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = src0[((hsi*45+24)*1+lsi)*1] + fp23;
target[((hsi*60+48)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp25;
fp25 = inteval->CD_z[vi] * src1[((hsi*30+23)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = src0[((hsi*45+38)*1+lsi)*1] + fp25;
target[((hsi*60+47)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp27;
fp27 = inteval->CD_z[vi] * src1[((hsi*30+22)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = src0[((hsi*45+37)*1+lsi)*1] + fp27;
target[((hsi*60+46)*1+lsi)*1] = fp26;
LIBINT2_REALTYPE fp59;
fp59 = inteval->CD_x[vi] * src1[((hsi*30+15)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = src0[((hsi*45+15)*1+lsi)*1] + fp59;
target[((hsi*60+30)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp31;
fp31 = inteval->CD_z[vi] * src1[((hsi*30+21)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = src0[((hsi*45+36)*1+lsi)*1] + fp31;
target[((hsi*60+44)*1+lsi)*1] = fp30;
LIBINT2_REALTYPE fp33;
fp33 = inteval->CD_y[vi] * src1[((hsi*30+21)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = src0[((hsi*45+33)*1+lsi)*1] + fp33;
target[((hsi*60+43)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp35;
fp35 = inteval->CD_x[vi] * src1[((hsi*30+21)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = src0[((hsi*45+21)*1+lsi)*1] + fp35;
target[((hsi*60+42)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp37;
fp37 = inteval->CD_z[vi] * src1[((hsi*30+20)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = src0[((hsi*45+35)*1+lsi)*1] + fp37;
target[((hsi*60+41)*1+lsi)*1] = fp36;
LIBINT2_REALTYPE fp39;
fp39 = inteval->CD_z[vi] * src1[((hsi*30+19)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = src0[((hsi*45+34)*1+lsi)*1] + fp39;
target[((hsi*60+40)*1+lsi)*1] = fp38;
LIBINT2_REALTYPE fp41;
fp41 = inteval->CD_y[vi] * src1[((hsi*30+19)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = src0[((hsi*45+31)*1+lsi)*1] + fp41;
target[((hsi*60+39)*1+lsi)*1] = fp40;
LIBINT2_REALTYPE fp43;
fp43 = inteval->CD_z[vi] * src1[((hsi*30+18)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = src0[((hsi*45+33)*1+lsi)*1] + fp43;
target[((hsi*60+38)*1+lsi)*1] = fp42;
LIBINT2_REALTYPE fp45;
fp45 = inteval->CD_y[vi] * src1[((hsi*30+18)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = src0[((hsi*45+30)*1+lsi)*1] + fp45;
target[((hsi*60+37)*1+lsi)*1] = fp44;
LIBINT2_REALTYPE fp47;
fp47 = inteval->CD_x[vi] * src1[((hsi*30+18)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = src0[((hsi*45+18)*1+lsi)*1] + fp47;
target[((hsi*60+36)*1+lsi)*1] = fp46;
LIBINT2_REALTYPE fp49;
fp49 = inteval->CD_z[vi] * src1[((hsi*30+17)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = src0[((hsi*45+29)*1+lsi)*1] + fp49;
target[((hsi*60+35)*1+lsi)*1] = fp48;
LIBINT2_REALTYPE fp51;
fp51 = inteval->CD_z[vi] * src1[((hsi*30+16)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = src0[((hsi*45+28)*1+lsi)*1] + fp51;
target[((hsi*60+34)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp53;
fp53 = inteval->CD_y[vi] * src1[((hsi*30+16)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = src0[((hsi*45+25)*1+lsi)*1] + fp53;
target[((hsi*60+33)*1+lsi)*1] = fp52;
LIBINT2_REALTYPE fp55;
fp55 = inteval->CD_z[vi] * src1[((hsi*30+15)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = src0[((hsi*45+27)*1+lsi)*1] + fp55;
target[((hsi*60+32)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp57;
fp57 = inteval->CD_y[vi] * src1[((hsi*30+15)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = src0[((hsi*45+24)*1+lsi)*1] + fp57;
target[((hsi*60+31)*1+lsi)*1] = fp56;
LIBINT2_REALTYPE fp29;
fp29 = inteval->CD_y[vi] * src1[((hsi*30+22)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = src0[((hsi*45+34)*1+lsi)*1] + fp29;
target[((hsi*60+45)*1+lsi)*1] = fp28;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 120 */
}

#ifdef __cplusplus
};
#endif
