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
#include <CR_aB_X5__0___Overlap_X3__0___Ab__up_.h>
#include <CR_aB_Y5__0___Overlap_Y3__0___Ab__up_.h>
#include <CR_aB_Z5__0___Overlap_Z3__0___Ab__up_.h>
#include <CR_aB_g__0___Kinetic_d__0___Ab__up_.h>
#include <GenericContract.h>

#ifdef __cplusplus
extern "C" {
#endif
void _kinetic_G_D_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
CR_aB_Z5__0___Overlap_Z3__0___Ab__up_(inteval, &(stack[((hsi*24+90)*1+lsi)*1]), &(inteval->_0_Overlap_0_z[vi]));
CR_aB_Y5__0___Overlap_Y3__0___Ab__up_(inteval, &(stack[((hsi*24+114)*1+lsi)*1]), &(inteval->_0_Overlap_0_y[vi]));
CR_aB_X5__0___Overlap_X3__0___Ab__up_(inteval, &(stack[((hsi*24+138)*1+lsi)*1]), &(inteval->_0_Overlap_0_x[vi]));
CR_aB_g__0___Kinetic_d__0___Ab__up_(inteval, &(stack[((hsi*90+162)*1+lsi)*1]), &(stack[((hsi*24+138)*1+lsi)*1]), &(stack[((hsi*24+114)*1+lsi)*1]), &(stack[((hsi*24+90)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*90+0)*1+lsi)*1]),&(stack[((hsi*90+162)*1+lsi)*1]),90);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 90 */
}

#ifdef __cplusplus
};
#endif
