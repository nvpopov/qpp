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
#include <CR_aB_X4__0___Overlap_X1__0___Ab__up_.h>
#include <CR_aB_X4__0___Overlap_X2__0___Ab__up_.h>
#include <CR_aB_Y4__0___Overlap_Y1__0___Ab__up_.h>
#include <CR_aB_Y4__0___Overlap_Y2__0___Ab__up_.h>
#include <CR_aB_Z4__0___Overlap_Z1__0___Ab__up_.h>
#include <CR_aB_Z4__0___Overlap_Z2__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_0_Sb__p__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_1_Sb__p__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_0_Sb__p__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_1_c_0_c_0_Sb__p__0___Ab__up_.h>
#include <GenericContract.h>

#ifdef __cplusplus
extern "C" {
#endif
void _1emultipole_G_P_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
CR_aB_Z4__0___Overlap_Z2__0___Ab__up_(inteval, &(stack[((hsi*15+180)*1+lsi)*1]), &(inteval->_0_Overlap_0_z[vi]));
CR_aB_Y4__0___Overlap_Y2__0___Ab__up_(inteval, &(stack[((hsi*15+195)*1+lsi)*1]), &(inteval->_0_Overlap_0_y[vi]));
CR_aB_X4__0___Overlap_X2__0___Ab__up_(inteval, &(stack[((hsi*15+210)*1+lsi)*1]), &(inteval->_0_Overlap_0_x[vi]));
CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_1_Sb__p__0___Ab__up_(inteval, &(stack[((hsi*45+225)*1+lsi)*1]), &(stack[((hsi*15+210)*1+lsi)*1]), &(stack[((hsi*15+195)*1+lsi)*1]), &(stack[((hsi*15+180)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*45+135)*1+lsi)*1]),&(stack[((hsi*45+225)*1+lsi)*1]),45);
CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_0_Sb__p__0___Ab__up_(inteval, &(stack[((hsi*45+270)*1+lsi)*1]), &(stack[((hsi*15+210)*1+lsi)*1]), &(stack[((hsi*15+195)*1+lsi)*1]), &(stack[((hsi*15+180)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*45+90)*1+lsi)*1]),&(stack[((hsi*45+270)*1+lsi)*1]),45);
CR_aB_g__0___CartesianMultipole_sB_1_c_0_c_0_Sb__p__0___Ab__up_(inteval, &(stack[((hsi*45+315)*1+lsi)*1]), &(stack[((hsi*15+210)*1+lsi)*1]), &(stack[((hsi*15+195)*1+lsi)*1]), &(stack[((hsi*15+180)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*45+45)*1+lsi)*1]),&(stack[((hsi*45+315)*1+lsi)*1]),45);
CR_aB_Z4__0___Overlap_Z1__0___Ab__up_(inteval, &(stack[((hsi*10+180)*1+lsi)*1]), &(inteval->_0_Overlap_0_z[vi]));
CR_aB_Y4__0___Overlap_Y1__0___Ab__up_(inteval, &(stack[((hsi*10+190)*1+lsi)*1]), &(inteval->_0_Overlap_0_y[vi]));
CR_aB_X4__0___Overlap_X1__0___Ab__up_(inteval, &(stack[((hsi*10+200)*1+lsi)*1]), &(inteval->_0_Overlap_0_x[vi]));
CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_0_Sb__p__0___Ab__up_(inteval, &(stack[((hsi*45+360)*1+lsi)*1]), &(stack[((hsi*10+200)*1+lsi)*1]), &(stack[((hsi*10+190)*1+lsi)*1]), &(stack[((hsi*10+180)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*45+0)*1+lsi)*1]),&(stack[((hsi*45+360)*1+lsi)*1]),45);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 180 */
}

#ifdef __cplusplus
};
#endif
