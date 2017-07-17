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
#include <_aB_P__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _aB_P__0__P__1___TwoPRep_S__0__P__1___Ab__up_0(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,27)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_aB_P__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp51;
fp51 = inteval->CD_y[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp50;
fp50 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp51;
inteval->stack[((hsi*27+28)*1+lsi)*1] = fp50;
LIBINT2_REALTYPE fp49;
fp49 = inteval->CD_z[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp48;
fp48 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp49;
inteval->stack[((hsi*27+29)*1+lsi)*1] = fp48;
LIBINT2_REALTYPE fp47;
fp47 = inteval->CD_x[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp46;
fp46 = inteval->stack[((hsi*1+2)*1+lsi)*1] + fp47;
inteval->stack[((hsi*27+30)*1+lsi)*1] = fp46;
LIBINT2_REALTYPE fp45;
fp45 = inteval->CD_y[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp44;
fp44 = inteval->stack[((hsi*1+5)*1+lsi)*1] + fp45;
inteval->stack[((hsi*27+31)*1+lsi)*1] = fp44;
LIBINT2_REALTYPE fp43;
fp43 = inteval->CD_z[vi] * inteval->stack[((hsi*1+4)*1+lsi)*1];
LIBINT2_REALTYPE fp42;
fp42 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp43;
inteval->stack[((hsi*27+32)*1+lsi)*1] = fp42;
LIBINT2_REALTYPE fp41;
fp41 = inteval->CD_x[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp40;
fp40 = inteval->stack[((hsi*1+3)*1+lsi)*1] + fp41;
inteval->stack[((hsi*27+33)*1+lsi)*1] = fp40;
LIBINT2_REALTYPE fp39;
fp39 = inteval->CD_y[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp38;
fp38 = inteval->stack[((hsi*1+6)*1+lsi)*1] + fp39;
inteval->stack[((hsi*27+34)*1+lsi)*1] = fp38;
LIBINT2_REALTYPE fp37;
fp37 = inteval->CD_z[vi] * inteval->stack[((hsi*1+7)*1+lsi)*1];
LIBINT2_REALTYPE fp36;
fp36 = inteval->stack[((hsi*1+8)*1+lsi)*1] + fp37;
inteval->stack[((hsi*27+35)*1+lsi)*1] = fp36;
LIBINT2_REALTYPE fp35;
fp35 = inteval->CD_x[vi] * inteval->stack[((hsi*1+10)*1+lsi)*1];
LIBINT2_REALTYPE fp34;
fp34 = inteval->stack[((hsi*1+9)*1+lsi)*1] + fp35;
inteval->stack[((hsi*27+36)*1+lsi)*1] = fp34;
LIBINT2_REALTYPE fp33;
fp33 = inteval->CD_y[vi] * inteval->stack[((hsi*1+10)*1+lsi)*1];
LIBINT2_REALTYPE fp32;
fp32 = inteval->stack[((hsi*1+11)*1+lsi)*1] + fp33;
inteval->stack[((hsi*27+37)*1+lsi)*1] = fp32;
LIBINT2_REALTYPE fp31;
fp31 = inteval->CD_z[vi] * inteval->stack[((hsi*1+10)*1+lsi)*1];
LIBINT2_REALTYPE fp30;
fp30 = inteval->stack[((hsi*1+12)*1+lsi)*1] + fp31;
inteval->stack[((hsi*27+38)*1+lsi)*1] = fp30;
LIBINT2_REALTYPE fp29;
fp29 = inteval->CD_x[vi] * inteval->stack[((hsi*1+13)*1+lsi)*1];
LIBINT2_REALTYPE fp28;
fp28 = inteval->stack[((hsi*1+11)*1+lsi)*1] + fp29;
inteval->stack[((hsi*27+39)*1+lsi)*1] = fp28;
LIBINT2_REALTYPE fp53;
fp53 = inteval->CD_x[vi] * inteval->stack[((hsi*1+1)*1+lsi)*1];
LIBINT2_REALTYPE fp52;
fp52 = inteval->stack[((hsi*1+0)*1+lsi)*1] + fp53;
inteval->stack[((hsi*27+27)*1+lsi)*1] = fp52;
LIBINT2_REALTYPE fp25;
fp25 = inteval->CD_z[vi] * inteval->stack[((hsi*1+13)*1+lsi)*1];
LIBINT2_REALTYPE fp24;
fp24 = inteval->stack[((hsi*1+15)*1+lsi)*1] + fp25;
inteval->stack[((hsi*27+41)*1+lsi)*1] = fp24;
LIBINT2_REALTYPE fp23;
fp23 = inteval->CD_x[vi] * inteval->stack[((hsi*1+16)*1+lsi)*1];
LIBINT2_REALTYPE fp22;
fp22 = inteval->stack[((hsi*1+12)*1+lsi)*1] + fp23;
inteval->stack[((hsi*27+42)*1+lsi)*1] = fp22;
LIBINT2_REALTYPE fp21;
fp21 = inteval->CD_y[vi] * inteval->stack[((hsi*1+16)*1+lsi)*1];
LIBINT2_REALTYPE fp20;
fp20 = inteval->stack[((hsi*1+15)*1+lsi)*1] + fp21;
inteval->stack[((hsi*27+43)*1+lsi)*1] = fp20;
LIBINT2_REALTYPE fp19;
fp19 = inteval->CD_z[vi] * inteval->stack[((hsi*1+16)*1+lsi)*1];
LIBINT2_REALTYPE fp18;
fp18 = inteval->stack[((hsi*1+17)*1+lsi)*1] + fp19;
inteval->stack[((hsi*27+44)*1+lsi)*1] = fp18;
LIBINT2_REALTYPE fp17;
fp17 = inteval->CD_x[vi] * inteval->stack[((hsi*1+19)*1+lsi)*1];
LIBINT2_REALTYPE fp16;
fp16 = inteval->stack[((hsi*1+18)*1+lsi)*1] + fp17;
inteval->stack[((hsi*27+45)*1+lsi)*1] = fp16;
LIBINT2_REALTYPE fp15;
fp15 = inteval->CD_y[vi] * inteval->stack[((hsi*1+19)*1+lsi)*1];
LIBINT2_REALTYPE fp14;
fp14 = inteval->stack[((hsi*1+20)*1+lsi)*1] + fp15;
inteval->stack[((hsi*27+46)*1+lsi)*1] = fp14;
LIBINT2_REALTYPE fp13;
fp13 = inteval->CD_z[vi] * inteval->stack[((hsi*1+19)*1+lsi)*1];
LIBINT2_REALTYPE fp12;
fp12 = inteval->stack[((hsi*1+21)*1+lsi)*1] + fp13;
inteval->stack[((hsi*27+47)*1+lsi)*1] = fp12;
LIBINT2_REALTYPE fp11;
fp11 = inteval->CD_x[vi] * inteval->stack[((hsi*1+22)*1+lsi)*1];
LIBINT2_REALTYPE fp10;
fp10 = inteval->stack[((hsi*1+20)*1+lsi)*1] + fp11;
inteval->stack[((hsi*27+48)*1+lsi)*1] = fp10;
LIBINT2_REALTYPE fp9;
fp9 = inteval->CD_y[vi] * inteval->stack[((hsi*1+22)*1+lsi)*1];
LIBINT2_REALTYPE fp8;
fp8 = inteval->stack[((hsi*1+23)*1+lsi)*1] + fp9;
inteval->stack[((hsi*27+49)*1+lsi)*1] = fp8;
LIBINT2_REALTYPE fp7;
fp7 = inteval->CD_z[vi] * inteval->stack[((hsi*1+22)*1+lsi)*1];
LIBINT2_REALTYPE fp6;
fp6 = inteval->stack[((hsi*1+24)*1+lsi)*1] + fp7;
inteval->stack[((hsi*27+50)*1+lsi)*1] = fp6;
LIBINT2_REALTYPE fp5;
fp5 = inteval->CD_x[vi] * inteval->stack[((hsi*1+25)*1+lsi)*1];
LIBINT2_REALTYPE fp4;
fp4 = inteval->stack[((hsi*1+21)*1+lsi)*1] + fp5;
inteval->stack[((hsi*27+51)*1+lsi)*1] = fp4;
LIBINT2_REALTYPE fp3;
fp3 = inteval->CD_y[vi] * inteval->stack[((hsi*1+25)*1+lsi)*1];
LIBINT2_REALTYPE fp2;
fp2 = inteval->stack[((hsi*1+24)*1+lsi)*1] + fp3;
inteval->stack[((hsi*27+52)*1+lsi)*1] = fp2;
LIBINT2_REALTYPE fp1;
fp1 = inteval->CD_z[vi] * inteval->stack[((hsi*1+25)*1+lsi)*1];
LIBINT2_REALTYPE fp0;
fp0 = inteval->stack[((hsi*1+26)*1+lsi)*1] + fp1;
inteval->stack[((hsi*27+53)*1+lsi)*1] = fp0;
LIBINT2_REALTYPE fp27;
fp27 = inteval->CD_y[vi] * inteval->stack[((hsi*1+13)*1+lsi)*1];
LIBINT2_REALTYPE fp26;
fp26 = inteval->stack[((hsi*1+14)*1+lsi)*1] + fp27;
inteval->stack[((hsi*27+40)*1+lsi)*1] = fp26;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*27+27)*1+lsi)*1]);
/** Number of flops = 54 */
}

#ifdef __cplusplus
};
#endif
