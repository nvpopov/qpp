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
#include <_3emultipole_P_D_prereq.h>

#ifdef __cplusplus
extern "C" {
#endif
void _3emultipole_P_D(const Libint_t* inteval) {

_libint2_static_api_bzero_short_(inteval->stack+0*1,360)
const int contrdepth = inteval->contrdepth;
#ifdef __INTEL_COMPILER
#pragma ivdep
#endif
for(int c = 0; c<contrdepth; c++) {
_3emultipole_P_D_prereq(inteval+c, inteval->stack);
}

LIBINT2_REALTYPE*const  stack = inteval->stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
inteval->targets[0] = &(inteval->stack[((hsi*18+0)*1+lsi)*1]);
inteval->targets[1] = &(inteval->stack[((hsi*18+18)*1+lsi)*1]);
inteval->targets[2] = &(inteval->stack[((hsi*18+36)*1+lsi)*1]);
inteval->targets[3] = &(inteval->stack[((hsi*18+54)*1+lsi)*1]);
inteval->targets[4] = &(inteval->stack[((hsi*18+72)*1+lsi)*1]);
inteval->targets[5] = &(inteval->stack[((hsi*18+90)*1+lsi)*1]);
inteval->targets[6] = &(inteval->stack[((hsi*18+108)*1+lsi)*1]);
inteval->targets[7] = &(inteval->stack[((hsi*18+126)*1+lsi)*1]);
inteval->targets[8] = &(inteval->stack[((hsi*18+144)*1+lsi)*1]);
inteval->targets[9] = &(inteval->stack[((hsi*18+162)*1+lsi)*1]);
inteval->targets[10] = &(inteval->stack[((hsi*18+180)*1+lsi)*1]);
inteval->targets[11] = &(inteval->stack[((hsi*18+198)*1+lsi)*1]);
inteval->targets[12] = &(inteval->stack[((hsi*18+216)*1+lsi)*1]);
inteval->targets[13] = &(inteval->stack[((hsi*18+234)*1+lsi)*1]);
inteval->targets[14] = &(inteval->stack[((hsi*18+252)*1+lsi)*1]);
inteval->targets[15] = &(inteval->stack[((hsi*18+270)*1+lsi)*1]);
inteval->targets[16] = &(inteval->stack[((hsi*18+288)*1+lsi)*1]);
inteval->targets[17] = &(inteval->stack[((hsi*18+306)*1+lsi)*1]);
inteval->targets[18] = &(inteval->stack[((hsi*18+324)*1+lsi)*1]);
inteval->targets[19] = &(inteval->stack[((hsi*18+342)*1+lsi)*1]);
/** Number of flops = 0 */
}

#ifdef __cplusplus
};
#endif
