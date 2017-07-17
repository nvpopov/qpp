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
#include <CR_aB_X4__0___Overlap_X4__0___Ab__up_.h>
#include <CR_aB_X4__0___Overlap_X5__0___Ab__up_.h>
#include <CR_aB_X4__0___Overlap_X6__0___Ab__up_.h>
#include <CR_aB_Y4__0___Overlap_Y4__0___Ab__up_.h>
#include <CR_aB_Y4__0___Overlap_Y5__0___Ab__up_.h>
#include <CR_aB_Y4__0___Overlap_Y6__0___Ab__up_.h>
#include <CR_aB_Z4__0___Overlap_Z4__0___Ab__up_.h>
#include <CR_aB_Z4__0___Overlap_Z5__0___Ab__up_.h>
#include <CR_aB_Z4__0___Overlap_Z6__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_0_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_1_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_2_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_0_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_1_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_0_c_2_c_0_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_1_c_0_c_0_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_1_c_0_c_1_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_1_c_1_c_0_Sb__g__0___Ab__up_.h>
#include <CR_aB_g__0___CartesianMultipole_sB_2_c_0_c_0_Sb__g__0___Ab__up_.h>
#include <GenericContract.h>

#ifdef __cplusplus
extern "C" {
#endif
void _2emultipole_G_G_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
CR_aB_Z4__0___Overlap_Z6__0___Ab__up_(inteval, &(stack[((hsi*35+2250)*1+lsi)*1]), &(inteval->_0_Overlap_0_z[vi]));
CR_aB_Y4__0___Overlap_Y6__0___Ab__up_(inteval, &(stack[((hsi*35+2285)*1+lsi)*1]), &(inteval->_0_Overlap_0_y[vi]));
CR_aB_X4__0___Overlap_X6__0___Ab__up_(inteval, &(stack[((hsi*35+2320)*1+lsi)*1]), &(inteval->_0_Overlap_0_x[vi]));
CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_2_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+2355)*1+lsi)*1]), &(stack[((hsi*35+2320)*1+lsi)*1]), &(stack[((hsi*35+2285)*1+lsi)*1]), &(stack[((hsi*35+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+2025)*1+lsi)*1]),&(stack[((hsi*225+2355)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_1_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+2580)*1+lsi)*1]), &(stack[((hsi*35+2320)*1+lsi)*1]), &(stack[((hsi*35+2285)*1+lsi)*1]), &(stack[((hsi*35+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+1800)*1+lsi)*1]),&(stack[((hsi*225+2580)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_0_c_2_c_0_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+2805)*1+lsi)*1]), &(stack[((hsi*35+2320)*1+lsi)*1]), &(stack[((hsi*35+2285)*1+lsi)*1]), &(stack[((hsi*35+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+1575)*1+lsi)*1]),&(stack[((hsi*225+2805)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_1_c_0_c_1_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+3030)*1+lsi)*1]), &(stack[((hsi*35+2320)*1+lsi)*1]), &(stack[((hsi*35+2285)*1+lsi)*1]), &(stack[((hsi*35+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+1350)*1+lsi)*1]),&(stack[((hsi*225+3030)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_1_c_1_c_0_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+3255)*1+lsi)*1]), &(stack[((hsi*35+2320)*1+lsi)*1]), &(stack[((hsi*35+2285)*1+lsi)*1]), &(stack[((hsi*35+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+1125)*1+lsi)*1]),&(stack[((hsi*225+3255)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_2_c_0_c_0_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+3480)*1+lsi)*1]), &(stack[((hsi*35+2320)*1+lsi)*1]), &(stack[((hsi*35+2285)*1+lsi)*1]), &(stack[((hsi*35+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+900)*1+lsi)*1]),&(stack[((hsi*225+3480)*1+lsi)*1]),225);
CR_aB_Z4__0___Overlap_Z5__0___Ab__up_(inteval, &(stack[((hsi*30+2250)*1+lsi)*1]), &(inteval->_0_Overlap_0_z[vi]));
CR_aB_Y4__0___Overlap_Y5__0___Ab__up_(inteval, &(stack[((hsi*30+2280)*1+lsi)*1]), &(inteval->_0_Overlap_0_y[vi]));
CR_aB_X4__0___Overlap_X5__0___Ab__up_(inteval, &(stack[((hsi*30+2310)*1+lsi)*1]), &(inteval->_0_Overlap_0_x[vi]));
CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_1_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+3705)*1+lsi)*1]), &(stack[((hsi*30+2310)*1+lsi)*1]), &(stack[((hsi*30+2280)*1+lsi)*1]), &(stack[((hsi*30+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+675)*1+lsi)*1]),&(stack[((hsi*225+3705)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_0_c_1_c_0_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+3930)*1+lsi)*1]), &(stack[((hsi*30+2310)*1+lsi)*1]), &(stack[((hsi*30+2280)*1+lsi)*1]), &(stack[((hsi*30+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+450)*1+lsi)*1]),&(stack[((hsi*225+3930)*1+lsi)*1]),225);
CR_aB_g__0___CartesianMultipole_sB_1_c_0_c_0_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+4155)*1+lsi)*1]), &(stack[((hsi*30+2310)*1+lsi)*1]), &(stack[((hsi*30+2280)*1+lsi)*1]), &(stack[((hsi*30+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+225)*1+lsi)*1]),&(stack[((hsi*225+4155)*1+lsi)*1]),225);
CR_aB_Z4__0___Overlap_Z4__0___Ab__up_(inteval, &(stack[((hsi*25+2250)*1+lsi)*1]), &(inteval->_0_Overlap_0_z[vi]));
CR_aB_Y4__0___Overlap_Y4__0___Ab__up_(inteval, &(stack[((hsi*25+2275)*1+lsi)*1]), &(inteval->_0_Overlap_0_y[vi]));
CR_aB_X4__0___Overlap_X4__0___Ab__up_(inteval, &(stack[((hsi*25+2300)*1+lsi)*1]), &(inteval->_0_Overlap_0_x[vi]));
CR_aB_g__0___CartesianMultipole_sB_0_c_0_c_0_Sb__g__0___Ab__up_(inteval, &(stack[((hsi*225+4380)*1+lsi)*1]), &(stack[((hsi*25+2300)*1+lsi)*1]), &(stack[((hsi*25+2275)*1+lsi)*1]), &(stack[((hsi*25+2250)*1+lsi)*1]));
_libint2_static_api_inc1_short_(&(stack[((hsi*225+0)*1+lsi)*1]),&(stack[((hsi*225+4380)*1+lsi)*1]),225);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 2250 */
}

#ifdef __cplusplus
};
#endif
