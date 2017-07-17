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
#include <_aB_D__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_D__0__P__1___TwoPRep_S__0__P__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,54)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_D__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp55;
fp55 = inteval->CD_z[vi] * inteval->stack[((hsi*1+25)*1+lsi)*1];
LIBINT2_REALTYPE fp54;
fp54 = inteval->stack[((hsi*1+26)*1+lsi)*1] + fp55;
inteval->stack[((hsi*54+80)*1+lsi)*1] = fp54;
LIBINT2_REALTYPE fp57;
fp57 = inteval->CD_y[vi] * inteval->stack[((hsi*1+25)*1+lsi)*1];
LIBINT2_REALTYPE fp56;
fp56 = inteval->stack[((hsi*1+24)*1+lsi)*1] + fp57;
inteval->stack[((hsi*54+79)*1+lsi)*1] = fp56;
LIBINT2_REALTYPE fp59;
fp59 = inteval->CD_x[vi] * inteval->stack[((hsi*1+25)*1+lsi)*1];
LIBINT2_REALTYPE fp58;
fp58 = inteval->stack[((hsi*1+21)*1+lsi)*1] + fp59;
inteval->stack[((hsi*54+78)*1+lsi)*1] = fp58;
LIBINT2_REALTYPE fp61;
fp61 = inteval->CD_z[vi] * inteval->stack[((hsi*1+22)*1+lsi)*1];
LIBINT2_REALTYPE fp60;
fp60 = inteval->stack[((hsi*1+24)*1+lsi)*1] + fp61;
inteval->stack[((hsi*54+77)*1+lsi)*1] = fp60;
LIBINT2_REALTYPE fp63;
fp63 = inteval->CD_y[vi] * inteval->stack[((hsi*1+22)*1+lsi)*1];
LIBINT2_REALTYPE fp62;
fp62 = inteval->stack[((hsi*1+23)*1+lsi)*1] + fp63;
inteval->stack[((hsi*54+76)*1+lsi)*1] = fp62;
LIBINT2_REALTYPE fp65;
fp65 = inteval->CD_x[vi] * inteval->stack[((hsi*1+22)*1+lsi)*1];
LIBINT2_REALTYPE fp64;
fp64 = inteval->stack[((hsi*1+20)*1+lsi)*1] + fp65;
inteval->stack[((hsi*54+75)*1+lsi)*1] = fp64;
LIBINT2_REALTYPE fp67;
fp67 = inteval->CD_z[vi] * inteval->stack[((hsi*1+19)*1+lsi)*1];
LIBINT2_REALTYPE fp66;
fp66 = inteval->stack[((hsi*1+21)*1+lsi)*1] + fp67;
inteval->stack[((hsi*54+74)*1+lsi)*1] = fp66;
LIBINT2_REALTYPE fp69;
fp69 = inteval->CD_y[vi] * inteval->stack[((hsi*1+19)*1+lsi)*1];
LIBINT2_REALTYPE fp68;
fp68 = inteval->stack[((hsi*1+20)*1+lsi)*1] + fp69;
inteval->stack[((hsi*54+73)*1+lsi)*1] = fp68;
LIBINT2_REALTYPE fp71;
fp71 = inteval->CD_x[vi] * inteval->stack[((hsi*1+19)*1+lsi)*1];
LIBINT2_REALTYPE fp70;
fp70 = inteval->stack[((hsi*1+18)*1+lsi)*1] + fp71;
inteval->stack[((hsi*54+72)*1+lsi)*1] = fp70;
LIBINT2_REALTYPE fp73;
fp73 = inteval->CD_z[vi] * inteval->stack[((hsi*1+16)*1+lsi)*1];
LIBINT2_REALTYPE fp72;
fp72 = inteval->stack[((hsi*1+17)*1+lsi)*1] + fp73;
inteval->stack[((hsi*54+71)*1+lsi)*1] = fp72;
LIBINT2_REALTYPE fp75;
fp75 = inteval->CD_y[vi] * inteval->stack[((hsi*1+16)*1+lsi)*1];
LIBINT2_REALTYPE fp74;
fp74 = inteval->stack[((hsi*1+15)*1+lsi)*1] + fp75;
inteval->stack[((hsi*54+70)*1+lsi)*1] = fp74;
LIBINT2_REALTYPE fp77;
fp77 = inteval->CD_x[vi] * inteval->stack[((hsi*1+16)*1+lsi)*1];
LIBINT2_REALTYPE fp76;
fp76 = inteval->stack[((hsi*1+12)*1+lsi)*1] + fp77;
inteval->stack[((hsi*54+69)*1+lsi)*1] = fp76;
LIBINT2_REALTYPE fp107;
fp107 = inteval->CD_x[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp106;
fp106 = inteval->stack[((hsi*1+0)*1+lsi)*1] + fp107;
inteval->stack[((hsi*54+54)*1+lsi)*1] = fp106;
LIBINT2_REALTYPE fp81;
fp81 = inteval->CD_y[vi] * inteval->stack[((hsi*1+13)*1+lsi)*1];
LIBINT2_REALTYPE fp80;
fp80 = inteval->stack[((hsi*1+14)*1+lsi)*1] + fp81;
inteval->stack[((hsi*54+67)*1+lsi)*1] = fp80;
LIBINT2_REALTYPE fp83;
fp83 = inteval->CD_x[vi] * inteval->stack[((hsi*1+13)*1+lsi)*1];
LIBINT2_REALTYPE fp82;
fp82 = inteval->stack[((hsi*1+11)*1+lsi)*1] + fp83;
inteval->stack[((hsi*54+66)*1+lsi)*1] = fp82;
LIBINT2_REALTYPE fp85;
fp85 = inteval->CD_z[vi] * inteval->stack[((hsi*1+10)*1+lsi)*1];
LIBINT2_REALTYPE fp84;
fp84 = inteval->stack[((hsi*1+12)*1+lsi)*1] + fp85;
inteval->stack[((hsi*54+65)*1+lsi)*1] = fp84;
LIBINT2_REALTYPE fp87;
fp87 = inteval->CD_y[vi] * inteval->stack[((hsi*1+10)*1+lsi)*1];
LIBINT2_REALTYPE fp86;
fp86 = inteval->stack[((hsi*1+11)*1+lsi)*1] + fp87;
inteval->stack[((hsi*54+64)*1+lsi)*1] = fp86;
LIBINT2_REALTYPE fp89;
fp89 = inteval->CD_x[vi] * inteval->stack[((hsi*1+10)*1+lsi)*1];
LIBINT2_REALTYPE fp88;
fp88 = inteval->stack[((hsi*1+9)*1+lsi)*1] + fp89;
inteval->stack[((hsi*54+63)*1+lsi)*1] = fp88;
LIBINT2_REALTYPE fp91;
fp91 = inteval->CD_z[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp90;
fp90 = inteval->stack[((hsi*1+8)*1+lsi)*1] + fp91;
inteval->stack[((hsi*54+62)*1+lsi)*1] = fp90;
LIBINT2_REALTYPE fp93;
fp93 = inteval->CD_y[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp92;
fp92 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp93;
inteval->stack[((hsi*54+61)*1+lsi)*1] = fp92;
LIBINT2_REALTYPE fp95;
fp95 = inteval->CD_x[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp94;
fp94 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp95;
inteval->stack[((hsi*54+60)*1+lsi)*1] = fp94;
LIBINT2_REALTYPE fp97;
fp97 = inteval->CD_z[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp96;
fp96 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp97;
inteval->stack[((hsi*54+59)*1+lsi)*1] = fp96;
LIBINT2_REALTYPE fp99;
fp99 = inteval->CD_y[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp98;
fp98 = inteval->stack[((hsi*1+5)*1+lsi)*1] + fp99;
inteval->stack[((hsi*54+58)*1+lsi)*1] = fp98;
LIBINT2_REALTYPE fp101;
fp101 = inteval->CD_x[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp100;
fp100 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp101;
inteval->stack[((hsi*54+57)*1+lsi)*1] = fp100;
LIBINT2_REALTYPE fp103;
fp103 = inteval->CD_z[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp102;
fp102 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp103;
inteval->stack[((hsi*54+56)*1+lsi)*1] = fp102;
LIBINT2_REALTYPE fp105;
fp105 = inteval->CD_y[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp104;
fp104 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp105;
inteval->stack[((hsi*54+55)*1+lsi)*1] = fp104;
LIBINT2_REALTYPE fp79;
fp79 = inteval->CD_z[vi] * inteval->stack[((hsi*1+13)*1+lsi)*1];
LIBINT2_REALTYPE fp78;
fp78 = inteval->stack[((hsi*1+15)*1+lsi)*1] + fp79;
inteval->stack[((hsi*54+68)*1+lsi)*1] = fp78;
LIBINT2_REALTYPE fp1;
fp1 = inteval->CD_z[vi] * inteval->stack[((hsi*1+52)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = inteval->stack[((hsi*1+53)*1+lsi)*1] + fp1;
inteval->stack[((hsi*54+107)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp3;
fp3 = inteval->CD_y[vi] * inteval->stack[((hsi*1+52)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->stack[((hsi*1+51)*1+lsi)*1] + fp3;
inteval->stack[((hsi*54+106)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp5;
fp5 = inteval->CD_x[vi] * inteval->stack[((hsi*1+52)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->stack[((hsi*1+48)*1+lsi)*1] + fp5;
inteval->stack[((hsi*54+105)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp7;
fp7 = inteval->CD_z[vi] * inteval->stack[((hsi*1+49)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->stack[((hsi*1+51)*1+lsi)*1] + fp7;
inteval->stack[((hsi*54+104)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp9;
fp9 = inteval->CD_y[vi] * inteval->stack[((hsi*1+49)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->stack[((hsi*1+50)*1+lsi)*1] + fp9;
inteval->stack[((hsi*54+103)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp11;
fp11 = inteval->CD_x[vi] * inteval->stack[((hsi*1+49)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->stack[((hsi*1+47)*1+lsi)*1] + fp11;
inteval->stack[((hsi*54+102)*1+lsi)*1] = fp10;
LIBINT2_REALTYPE fp13;
fp13 = inteval->CD_z[vi] * inteval->stack[((hsi*1+46)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = inteval->stack[((hsi*1+48)*1+lsi)*1] + fp13;
inteval->stack[((hsi*54+101)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp15;
fp15 = inteval->CD_y[vi] * inteval->stack[((hsi*1+46)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = inteval->stack[((hsi*1+47)*1+lsi)*1] + fp15;
inteval->stack[((hsi*54+100)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp17;
fp17 = inteval->CD_x[vi] * inteval->stack[((hsi*1+46)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->stack[((hsi*1+45)*1+lsi)*1] + fp17;
inteval->stack[((hsi*54+99)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp19;
fp19 = inteval->CD_z[vi] * inteval->stack[((hsi*1+43)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = inteval->stack[((hsi*1+44)*1+lsi)*1] + fp19;
inteval->stack[((hsi*54+98)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp21;
fp21 = inteval->CD_y[vi] * inteval->stack[((hsi*1+43)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = inteval->stack[((hsi*1+42)*1+lsi)*1] + fp21;
inteval->stack[((hsi*54+97)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp23;
fp23 = inteval->CD_x[vi] * inteval->stack[((hsi*1+43)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = inteval->stack[((hsi*1+39)*1+lsi)*1] + fp23;
inteval->stack[((hsi*54+96)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp53;
fp53 = inteval->CD_x[vi] * inteval->stack[((hsi*1+28)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = inteval->stack[((hsi*1+27)*1+lsi)*1] + fp53;
inteval->stack[((hsi*54+81)*1+lsi)*1] = fp52;
LIBINT2_REALTYPE fp27;
fp27 = inteval->CD_y[vi] * inteval->stack[((hsi*1+40)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = inteval->stack[((hsi*1+41)*1+lsi)*1] + fp27;
inteval->stack[((hsi*54+94)*1+lsi)*1] = fp26;
LIBINT2_REALTYPE fp29;
fp29 = inteval->CD_x[vi] * inteval->stack[((hsi*1+40)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = inteval->stack[((hsi*1+38)*1+lsi)*1] + fp29;
inteval->stack[((hsi*54+93)*1+lsi)*1] = fp28;
LIBINT2_REALTYPE fp31;
fp31 = inteval->CD_z[vi] * inteval->stack[((hsi*1+37)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->stack[((hsi*1+39)*1+lsi)*1] + fp31;
inteval->stack[((hsi*54+92)*1+lsi)*1] = fp30;
LIBINT2_REALTYPE fp33;
fp33 = inteval->CD_y[vi] * inteval->stack[((hsi*1+37)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = inteval->stack[((hsi*1+38)*1+lsi)*1] + fp33;
inteval->stack[((hsi*54+91)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp35;
fp35 = inteval->CD_x[vi] * inteval->stack[((hsi*1+37)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->stack[((hsi*1+36)*1+lsi)*1] + fp35;
inteval->stack[((hsi*54+90)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp37;
fp37 = inteval->CD_z[vi] * inteval->stack[((hsi*1+34)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = inteval->stack[((hsi*1+35)*1+lsi)*1] + fp37;
inteval->stack[((hsi*54+89)*1+lsi)*1] = fp36;
LIBINT2_REALTYPE fp39;
fp39 = inteval->CD_y[vi] * inteval->stack[((hsi*1+34)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = inteval->stack[((hsi*1+33)*1+lsi)*1] + fp39;
inteval->stack[((hsi*54+88)*1+lsi)*1] = fp38;
LIBINT2_REALTYPE fp41;
fp41 = inteval->CD_x[vi] * inteval->stack[((hsi*1+34)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = inteval->stack[((hsi*1+30)*1+lsi)*1] + fp41;
inteval->stack[((hsi*54+87)*1+lsi)*1] = fp40;
LIBINT2_REALTYPE fp43;
fp43 = inteval->CD_z[vi] * inteval->stack[((hsi*1+31)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = inteval->stack[((hsi*1+33)*1+lsi)*1] + fp43;
inteval->stack[((hsi*54+86)*1+lsi)*1] = fp42;
LIBINT2_REALTYPE fp45;
fp45 = inteval->CD_y[vi] * inteval->stack[((hsi*1+31)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->stack[((hsi*1+32)*1+lsi)*1] + fp45;
inteval->stack[((hsi*54+85)*1+lsi)*1] = fp44;
LIBINT2_REALTYPE fp47;
fp47 = inteval->CD_x[vi] * inteval->stack[((hsi*1+31)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = inteval->stack[((hsi*1+29)*1+lsi)*1] + fp47;
inteval->stack[((hsi*54+84)*1+lsi)*1] = fp46;
LIBINT2_REALTYPE fp49;
fp49 = inteval->CD_z[vi] * inteval->stack[((hsi*1+28)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = inteval->stack[((hsi*1+30)*1+lsi)*1] + fp49;
inteval->stack[((hsi*54+83)*1+lsi)*1] = fp48;
LIBINT2_REALTYPE fp51;
fp51 = inteval->CD_y[vi] * inteval->stack[((hsi*1+28)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = inteval->stack[((hsi*1+29)*1+lsi)*1] + fp51;
inteval->stack[((hsi*54+82)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp25;
fp25 = inteval->CD_z[vi] * inteval->stack[((hsi*1+40)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->stack[((hsi*1+42)*1+lsi)*1] + fp25;
inteval->stack[((hsi*54+95)*1+lsi)*1] = fp24;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*54+54)*1+lsi)*1]);
/** Number of flops = 108 */
}

#ifdef __cplusplus
};
#endif
