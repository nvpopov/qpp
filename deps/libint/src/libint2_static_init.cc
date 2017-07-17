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
#include <libint2_iface.h>
#include <libint2_iface_internal.h>
#include <cstddef>
#include <cassert>
#include <cstdlib>
#ifdef __cplusplus
extern "C" {
#endif
void (*libint2_build_default[5][5][5][5])(const Libint_t*);
void (*libint2_build_overlap[5][5])(const Libint_t*);
void (*libint2_build_kinetic[5][5])(const Libint_t*);
void (*libint2_build_elecpot[5][5])(const Libint_t*);
void (*libint2_build_1emultipole[5][5])(const Libint_t*);
void (*libint2_build_2emultipole[5][5])(const Libint_t*);
void (*libint2_build_3emultipole[5][5])(const Libint_t*);
void (*libint2_build_eri[5][5][5][5])(const Libint_t*);
void libint2_static_init() {
libint2_build_overlap[0][1] = _overlap_S_P;

libint2_build_overlap[0][2] = _overlap_S_D;

libint2_build_overlap[0][3] = _overlap_S_F;

libint2_build_overlap[0][4] = _overlap_S_G;

libint2_build_overlap[1][0] = _overlap_P_S;

libint2_build_overlap[1][1] = _overlap_P_P;

libint2_build_overlap[1][2] = _overlap_P_D;

libint2_build_overlap[1][3] = _overlap_P_F;

libint2_build_overlap[1][4] = _overlap_P_G;

libint2_build_overlap[2][0] = _overlap_D_S;

libint2_build_overlap[2][1] = _overlap_D_P;

libint2_build_overlap[2][2] = _overlap_D_D;

libint2_build_overlap[2][3] = _overlap_D_F;

libint2_build_overlap[2][4] = _overlap_D_G;

libint2_build_overlap[3][0] = _overlap_F_S;

libint2_build_overlap[3][1] = _overlap_F_P;

libint2_build_overlap[3][2] = _overlap_F_D;

libint2_build_overlap[3][3] = _overlap_F_F;

libint2_build_overlap[3][4] = _overlap_F_G;

libint2_build_overlap[4][0] = _overlap_G_S;

libint2_build_overlap[4][1] = _overlap_G_P;

libint2_build_overlap[4][2] = _overlap_G_D;

libint2_build_overlap[4][3] = _overlap_G_F;

libint2_build_overlap[4][4] = _overlap_G_G;

libint2_build_kinetic[0][0] = _kinetic_S_S;

libint2_build_kinetic[0][1] = _kinetic_S_P;

libint2_build_kinetic[0][2] = _kinetic_S_D;

libint2_build_kinetic[0][3] = _kinetic_S_F;

libint2_build_kinetic[0][4] = _kinetic_S_G;

libint2_build_kinetic[1][0] = _kinetic_P_S;

libint2_build_kinetic[1][1] = _kinetic_P_P;

libint2_build_kinetic[1][2] = _kinetic_P_D;

libint2_build_kinetic[1][3] = _kinetic_P_F;

libint2_build_kinetic[1][4] = _kinetic_P_G;

libint2_build_kinetic[2][0] = _kinetic_D_S;

libint2_build_kinetic[2][1] = _kinetic_D_P;

libint2_build_kinetic[2][2] = _kinetic_D_D;

libint2_build_kinetic[2][3] = _kinetic_D_F;

libint2_build_kinetic[2][4] = _kinetic_D_G;

libint2_build_kinetic[3][0] = _kinetic_F_S;

libint2_build_kinetic[3][1] = _kinetic_F_P;

libint2_build_kinetic[3][2] = _kinetic_F_D;

libint2_build_kinetic[3][3] = _kinetic_F_F;

libint2_build_kinetic[3][4] = _kinetic_F_G;

libint2_build_kinetic[4][0] = _kinetic_G_S;

libint2_build_kinetic[4][1] = _kinetic_G_P;

libint2_build_kinetic[4][2] = _kinetic_G_D;

libint2_build_kinetic[4][3] = _kinetic_G_F;

libint2_build_kinetic[4][4] = _kinetic_G_G;

libint2_build_elecpot[0][1] = _elecpot_S_P;

libint2_build_elecpot[0][2] = _elecpot_S_D;

libint2_build_elecpot[0][3] = _elecpot_S_F;

libint2_build_elecpot[0][4] = _elecpot_S_G;

libint2_build_elecpot[1][0] = _elecpot_P_S;

libint2_build_elecpot[1][1] = _elecpot_P_P;

libint2_build_elecpot[1][2] = _elecpot_P_D;

libint2_build_elecpot[1][3] = _elecpot_P_F;

libint2_build_elecpot[1][4] = _elecpot_P_G;

libint2_build_elecpot[2][0] = _elecpot_D_S;

libint2_build_elecpot[2][1] = _elecpot_D_P;

libint2_build_elecpot[2][2] = _elecpot_D_D;

libint2_build_elecpot[2][3] = _elecpot_D_F;

libint2_build_elecpot[2][4] = _elecpot_D_G;

libint2_build_elecpot[3][0] = _elecpot_F_S;

libint2_build_elecpot[3][1] = _elecpot_F_P;

libint2_build_elecpot[3][2] = _elecpot_F_D;

libint2_build_elecpot[3][3] = _elecpot_F_F;

libint2_build_elecpot[3][4] = _elecpot_F_G;

libint2_build_elecpot[4][0] = _elecpot_G_S;

libint2_build_elecpot[4][1] = _elecpot_G_P;

libint2_build_elecpot[4][2] = _elecpot_G_D;

libint2_build_elecpot[4][3] = _elecpot_G_F;

libint2_build_elecpot[4][4] = _elecpot_G_G;

libint2_build_1emultipole[0][0] = _1emultipole_S_S;

libint2_build_1emultipole[0][1] = _1emultipole_S_P;

libint2_build_1emultipole[0][2] = _1emultipole_S_D;

libint2_build_1emultipole[0][3] = _1emultipole_S_F;

libint2_build_1emultipole[0][4] = _1emultipole_S_G;

libint2_build_1emultipole[1][0] = _1emultipole_P_S;

libint2_build_1emultipole[1][1] = _1emultipole_P_P;

libint2_build_1emultipole[1][2] = _1emultipole_P_D;

libint2_build_1emultipole[1][3] = _1emultipole_P_F;

libint2_build_1emultipole[1][4] = _1emultipole_P_G;

libint2_build_1emultipole[2][0] = _1emultipole_D_S;

libint2_build_1emultipole[2][1] = _1emultipole_D_P;

libint2_build_1emultipole[2][2] = _1emultipole_D_D;

libint2_build_1emultipole[2][3] = _1emultipole_D_F;

libint2_build_1emultipole[2][4] = _1emultipole_D_G;

libint2_build_1emultipole[3][0] = _1emultipole_F_S;

libint2_build_1emultipole[3][1] = _1emultipole_F_P;

libint2_build_1emultipole[3][2] = _1emultipole_F_D;

libint2_build_1emultipole[3][3] = _1emultipole_F_F;

libint2_build_1emultipole[3][4] = _1emultipole_F_G;

libint2_build_1emultipole[4][0] = _1emultipole_G_S;

libint2_build_1emultipole[4][1] = _1emultipole_G_P;

libint2_build_1emultipole[4][2] = _1emultipole_G_D;

libint2_build_1emultipole[4][3] = _1emultipole_G_F;

libint2_build_1emultipole[4][4] = _1emultipole_G_G;

libint2_build_2emultipole[0][0] = _2emultipole_S_S;

libint2_build_2emultipole[0][1] = _2emultipole_S_P;

libint2_build_2emultipole[0][2] = _2emultipole_S_D;

libint2_build_2emultipole[0][3] = _2emultipole_S_F;

libint2_build_2emultipole[0][4] = _2emultipole_S_G;

libint2_build_2emultipole[1][0] = _2emultipole_P_S;

libint2_build_2emultipole[1][1] = _2emultipole_P_P;

libint2_build_2emultipole[1][2] = _2emultipole_P_D;

libint2_build_2emultipole[1][3] = _2emultipole_P_F;

libint2_build_2emultipole[1][4] = _2emultipole_P_G;

libint2_build_2emultipole[2][0] = _2emultipole_D_S;

libint2_build_2emultipole[2][1] = _2emultipole_D_P;

libint2_build_2emultipole[2][2] = _2emultipole_D_D;

libint2_build_2emultipole[2][3] = _2emultipole_D_F;

libint2_build_2emultipole[2][4] = _2emultipole_D_G;

libint2_build_2emultipole[3][0] = _2emultipole_F_S;

libint2_build_2emultipole[3][1] = _2emultipole_F_P;

libint2_build_2emultipole[3][2] = _2emultipole_F_D;

libint2_build_2emultipole[3][3] = _2emultipole_F_F;

libint2_build_2emultipole[3][4] = _2emultipole_F_G;

libint2_build_2emultipole[4][0] = _2emultipole_G_S;

libint2_build_2emultipole[4][1] = _2emultipole_G_P;

libint2_build_2emultipole[4][2] = _2emultipole_G_D;

libint2_build_2emultipole[4][3] = _2emultipole_G_F;

libint2_build_2emultipole[4][4] = _2emultipole_G_G;

libint2_build_3emultipole[0][0] = _3emultipole_S_S;

libint2_build_3emultipole[0][1] = _3emultipole_S_P;

libint2_build_3emultipole[0][2] = _3emultipole_S_D;

libint2_build_3emultipole[0][3] = _3emultipole_S_F;

libint2_build_3emultipole[0][4] = _3emultipole_S_G;

libint2_build_3emultipole[1][0] = _3emultipole_P_S;

libint2_build_3emultipole[1][1] = _3emultipole_P_P;

libint2_build_3emultipole[1][2] = _3emultipole_P_D;

libint2_build_3emultipole[1][3] = _3emultipole_P_F;

libint2_build_3emultipole[1][4] = _3emultipole_P_G;

libint2_build_3emultipole[2][0] = _3emultipole_D_S;

libint2_build_3emultipole[2][1] = _3emultipole_D_P;

libint2_build_3emultipole[2][2] = _3emultipole_D_D;

libint2_build_3emultipole[2][3] = _3emultipole_D_F;

libint2_build_3emultipole[2][4] = _3emultipole_D_G;

libint2_build_3emultipole[3][0] = _3emultipole_F_S;

libint2_build_3emultipole[3][1] = _3emultipole_F_P;

libint2_build_3emultipole[3][2] = _3emultipole_F_D;

libint2_build_3emultipole[3][3] = _3emultipole_F_F;

libint2_build_3emultipole[3][4] = _3emultipole_F_G;

libint2_build_3emultipole[4][0] = _3emultipole_G_S;

libint2_build_3emultipole[4][1] = _3emultipole_G_P;

libint2_build_3emultipole[4][2] = _3emultipole_G_D;

libint2_build_3emultipole[4][3] = _3emultipole_G_F;

libint2_build_3emultipole[4][4] = _3emultipole_G_G;

libint2_build_eri[0][0][0][0] = _aB_S__0__S__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[0][0][1][0] = _aB_S__0__P__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[0][0][1][1] = _aB_S__0__P__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[0][0][2][0] = _aB_S__0__D__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[0][0][2][1] = _aB_S__0__D__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[0][0][2][2] = _aB_S__0__D__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[0][0][3][0] = _aB_S__0__F__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[0][0][3][1] = _aB_S__0__F__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[0][0][3][2] = _aB_S__0__F__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[0][0][3][3] = _aB_S__0__F__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[0][0][4][0] = _aB_S__0__G__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[0][0][4][1] = _aB_S__0__G__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[0][0][4][2] = _aB_S__0__G__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[0][0][4][3] = _aB_S__0__G__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[0][0][4][4] = _aB_S__0__G__1___TwoPRep_S__0__G__1___Ab__up_0;

libint2_build_eri[1][0][1][0] = _aB_P__0__P__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[1][0][1][1] = _aB_P__0__P__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[1][0][2][0] = _aB_P__0__D__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[1][0][2][1] = _aB_P__0__D__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[1][0][2][2] = _aB_P__0__D__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[1][0][3][0] = _aB_P__0__F__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[1][0][3][1] = _aB_P__0__F__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[1][0][3][2] = _aB_P__0__F__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[1][0][3][3] = _aB_P__0__F__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[1][0][4][0] = _aB_P__0__G__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[1][0][4][1] = _aB_P__0__G__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[1][0][4][2] = _aB_P__0__G__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[1][0][4][3] = _aB_P__0__G__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[1][0][4][4] = _aB_P__0__G__1___TwoPRep_S__0__G__1___Ab__up_0;

libint2_build_eri[1][1][1][1] = _aB_P__0__P__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[1][1][2][0] = _aB_P__0__D__1___TwoPRep_P__0__S__1___Ab__up_0;

libint2_build_eri[1][1][2][1] = _aB_P__0__D__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[1][1][2][2] = _aB_P__0__D__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[1][1][3][0] = _aB_P__0__F__1___TwoPRep_P__0__S__1___Ab__up_0;

libint2_build_eri[1][1][3][1] = _aB_P__0__F__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[1][1][3][2] = _aB_P__0__F__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[1][1][3][3] = _aB_P__0__F__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[1][1][4][0] = _aB_P__0__G__1___TwoPRep_P__0__S__1___Ab__up_0;

libint2_build_eri[1][1][4][1] = _aB_P__0__G__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[1][1][4][2] = _aB_P__0__G__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[1][1][4][3] = _aB_P__0__G__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[1][1][4][4] = _aB_P__0__G__1___TwoPRep_P__0__G__1___Ab__up_0;

libint2_build_eri[2][0][1][1] = _aB_D__0__P__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[2][0][2][0] = _aB_D__0__D__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[2][0][2][1] = _aB_D__0__D__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[2][0][2][2] = _aB_D__0__D__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[2][0][3][0] = _aB_D__0__F__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[2][0][3][1] = _aB_D__0__F__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[2][0][3][2] = _aB_D__0__F__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[2][0][3][3] = _aB_D__0__F__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[2][0][4][0] = _aB_D__0__G__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[2][0][4][1] = _aB_D__0__G__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[2][0][4][2] = _aB_D__0__G__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[2][0][4][3] = _aB_D__0__G__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[2][0][4][4] = _aB_D__0__G__1___TwoPRep_S__0__G__1___Ab__up_0;

libint2_build_eri[2][1][2][1] = _aB_D__0__D__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[2][1][2][2] = _aB_D__0__D__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[2][1][3][0] = _aB_D__0__F__1___TwoPRep_P__0__S__1___Ab__up_0;

libint2_build_eri[2][1][3][1] = _aB_D__0__F__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[2][1][3][2] = _aB_D__0__F__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[2][1][3][3] = _aB_D__0__F__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[2][1][4][0] = _aB_D__0__G__1___TwoPRep_P__0__S__1___Ab__up_0;

libint2_build_eri[2][1][4][1] = _aB_D__0__G__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[2][1][4][2] = _aB_D__0__G__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[2][1][4][3] = _aB_D__0__G__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[2][1][4][4] = _aB_D__0__G__1___TwoPRep_P__0__G__1___Ab__up_0;

libint2_build_eri[2][2][2][2] = _aB_D__0__D__1___TwoPRep_D__0__D__1___Ab__up_0;

libint2_build_eri[2][2][3][1] = _aB_D__0__F__1___TwoPRep_D__0__P__1___Ab__up_0;

libint2_build_eri[2][2][3][2] = _aB_D__0__F__1___TwoPRep_D__0__D__1___Ab__up_0;

libint2_build_eri[2][2][3][3] = _aB_D__0__F__1___TwoPRep_D__0__F__1___Ab__up_0;

libint2_build_eri[2][2][4][0] = _aB_D__0__G__1___TwoPRep_D__0__S__1___Ab__up_0;

libint2_build_eri[2][2][4][1] = _aB_D__0__G__1___TwoPRep_D__0__P__1___Ab__up_0;

libint2_build_eri[2][2][4][2] = _aB_D__0__G__1___TwoPRep_D__0__D__1___Ab__up_0;

libint2_build_eri[2][2][4][3] = _aB_D__0__G__1___TwoPRep_D__0__F__1___Ab__up_0;

libint2_build_eri[2][2][4][4] = _aB_D__0__G__1___TwoPRep_D__0__G__1___Ab__up_0;

libint2_build_eri[3][0][2][1] = _aB_F__0__D__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[3][0][2][2] = _aB_F__0__D__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[3][0][3][0] = _aB_F__0__F__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[3][0][3][1] = _aB_F__0__F__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[3][0][3][2] = _aB_F__0__F__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[3][0][3][3] = _aB_F__0__F__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[3][0][4][0] = _aB_F__0__G__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[3][0][4][1] = _aB_F__0__G__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[3][0][4][2] = _aB_F__0__G__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[3][0][4][3] = _aB_F__0__G__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[3][0][4][4] = _aB_F__0__G__1___TwoPRep_S__0__G__1___Ab__up_0;

libint2_build_eri[3][1][2][2] = _aB_F__0__D__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[3][1][3][1] = _aB_F__0__F__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[3][1][3][2] = _aB_F__0__F__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[3][1][3][3] = _aB_F__0__F__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[3][1][4][0] = _aB_F__0__G__1___TwoPRep_P__0__S__1___Ab__up_0;

libint2_build_eri[3][1][4][1] = _aB_F__0__G__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[3][1][4][2] = _aB_F__0__G__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[3][1][4][3] = _aB_F__0__G__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[3][1][4][4] = _aB_F__0__G__1___TwoPRep_P__0__G__1___Ab__up_0;

libint2_build_eri[3][2][3][2] = _aB_F__0__F__1___TwoPRep_D__0__D__1___Ab__up_0;

libint2_build_eri[3][2][3][3] = _aB_F__0__F__1___TwoPRep_D__0__F__1___Ab__up_0;

libint2_build_eri[3][2][4][1] = _aB_F__0__G__1___TwoPRep_D__0__P__1___Ab__up_0;

libint2_build_eri[3][2][4][2] = _aB_F__0__G__1___TwoPRep_D__0__D__1___Ab__up_0;

libint2_build_eri[3][2][4][3] = _aB_F__0__G__1___TwoPRep_D__0__F__1___Ab__up_0;

libint2_build_eri[3][2][4][4] = _aB_F__0__G__1___TwoPRep_D__0__G__1___Ab__up_0;

libint2_build_eri[3][3][3][3] = _aB_F__0__F__1___TwoPRep_F__0__F__1___Ab__up_0;

libint2_build_eri[3][3][4][2] = _aB_F__0__G__1___TwoPRep_F__0__D__1___Ab__up_0;

libint2_build_eri[3][3][4][3] = _aB_F__0__G__1___TwoPRep_F__0__F__1___Ab__up_0;

libint2_build_eri[3][3][4][4] = _aB_F__0__G__1___TwoPRep_F__0__G__1___Ab__up_0;

libint2_build_eri[4][0][2][2] = _aB_G__0__D__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[4][0][3][1] = _aB_G__0__F__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[4][0][3][2] = _aB_G__0__F__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[4][0][3][3] = _aB_G__0__F__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[4][0][4][0] = _aB_G__0__G__1___TwoPRep_S__0__S__1___Ab__up_0;

libint2_build_eri[4][0][4][1] = _aB_G__0__G__1___TwoPRep_S__0__P__1___Ab__up_0;

libint2_build_eri[4][0][4][2] = _aB_G__0__G__1___TwoPRep_S__0__D__1___Ab__up_0;

libint2_build_eri[4][0][4][3] = _aB_G__0__G__1___TwoPRep_S__0__F__1___Ab__up_0;

libint2_build_eri[4][0][4][4] = _aB_G__0__G__1___TwoPRep_S__0__G__1___Ab__up_0;

libint2_build_eri[4][1][3][2] = _aB_G__0__F__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[4][1][3][3] = _aB_G__0__F__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[4][1][4][1] = _aB_G__0__G__1___TwoPRep_P__0__P__1___Ab__up_0;

libint2_build_eri[4][1][4][2] = _aB_G__0__G__1___TwoPRep_P__0__D__1___Ab__up_0;

libint2_build_eri[4][1][4][3] = _aB_G__0__G__1___TwoPRep_P__0__F__1___Ab__up_0;

libint2_build_eri[4][1][4][4] = _aB_G__0__G__1___TwoPRep_P__0__G__1___Ab__up_0;

libint2_build_eri[4][2][3][3] = _aB_G__0__F__1___TwoPRep_D__0__F__1___Ab__up_0;

libint2_build_eri[4][2][4][2] = _aB_G__0__G__1___TwoPRep_D__0__D__1___Ab__up_0;

libint2_build_eri[4][2][4][3] = _aB_G__0__G__1___TwoPRep_D__0__F__1___Ab__up_0;

libint2_build_eri[4][2][4][4] = _aB_G__0__G__1___TwoPRep_D__0__G__1___Ab__up_0;

libint2_build_eri[4][3][4][3] = _aB_G__0__G__1___TwoPRep_F__0__F__1___Ab__up_0;

libint2_build_eri[4][3][4][4] = _aB_G__0__G__1___TwoPRep_F__0__G__1___Ab__up_0;

libint2_build_eri[4][4][4][4] = _aB_G__0__G__1___TwoPRep_G__0__G__1___Ab__up_0;

}
#ifdef __cplusplus
};
#endif


