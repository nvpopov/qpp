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
#include <GenericContract.h>

#ifdef __cplusplus
extern "C" {
#endif
void _3emultipole_S_D_prereq(const Libint_t* inteval, LIBINT2_REALTYPE* parent_stack) {

LIBINT2_REALTYPE*const  stack = parent_stack;
{
const int hsi = 0;
{
const int lsi = 0;
{
const int vi = 0;
LIBINT2_REALTYPE fp147;
fp147 = 0 + inteval->_0_Overlap_0_y[vi];
LIBINT2_REALTYPE fp224;
fp224 = 0 + fp147;
LIBINT2_REALTYPE fp160;
fp160 = 0 + inteval->_0_Overlap_0_x[vi];
LIBINT2_REALTYPE fp252;
fp252 = 0 + fp160;
LIBINT2_REALTYPE fp424;
fp424 = fp252 * fp224;
LIBINT2_REALTYPE fp133;
fp133 = 0 + inteval->_0_Overlap_0_z[vi];
LIBINT2_REALTYPE fp130;
fp130 = inteval->oo2z[vi] * fp133;
LIBINT2_REALTYPE fp132;
fp132 = inteval->PB_z[vi] * fp133;
LIBINT2_REALTYPE fp131;
fp131 = inteval->PB_z[vi] * fp132;
LIBINT2_REALTYPE fp129;
fp129 = fp131 + fp130;
LIBINT2_REALTYPE fp154;
fp154 = 3 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp124;
fp124 = fp154 * fp129;
LIBINT2_REALTYPE fp158;
fp158 = 2 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp127;
fp127 = fp158 * fp132;
LIBINT2_REALTYPE fp128;
fp128 = inteval->PB_z[vi] * fp129;
LIBINT2_REALTYPE fp126;
fp126 = fp128 + fp127;
LIBINT2_REALTYPE fp125;
fp125 = inteval->PB_z[vi] * fp126;
LIBINT2_REALTYPE fp123;
fp123 = fp125 + fp124;
LIBINT2_REALTYPE fp176;
fp176 = 0 + fp123;
LIBINT2_REALTYPE fp185;
fp185 = 0 + fp126;
LIBINT2_REALTYPE fp178;
fp178 = inteval->BO_z[vi] * fp185;
LIBINT2_REALTYPE fp177;
fp177 = fp176 + fp178;
LIBINT2_REALTYPE fp192;
fp192 = 0 + fp129;
LIBINT2_REALTYPE fp187;
fp187 = inteval->BO_z[vi] * fp192;
LIBINT2_REALTYPE fp186;
fp186 = fp185 + fp187;
LIBINT2_REALTYPE fp180;
fp180 = inteval->BO_z[vi] * fp186;
LIBINT2_REALTYPE fp179;
fp179 = fp177 + fp180;
LIBINT2_REALTYPE fp171;
fp171 = inteval->BO_z[vi] * fp179;
LIBINT2_REALTYPE fp169;
fp169 = inteval->BO_z[vi] * fp177;
LIBINT2_REALTYPE fp167;
fp167 = inteval->BO_z[vi] * fp176;
LIBINT2_REALTYPE fp150;
fp150 = 4 * inteval->oo2z[vi];
LIBINT2_REALTYPE fp121;
fp121 = fp150 * fp126;
LIBINT2_REALTYPE fp122;
fp122 = inteval->PB_z[vi] * fp123;
LIBINT2_REALTYPE fp120;
fp120 = fp122 + fp121;
LIBINT2_REALTYPE fp165;
fp165 = 0 + fp120;
LIBINT2_REALTYPE fp166;
fp166 = fp165 + fp167;
LIBINT2_REALTYPE fp168;
fp168 = fp166 + fp169;
LIBINT2_REALTYPE fp170;
fp170 = fp168 + fp171;
LIBINT2_REALTYPE fp255;
fp255 = fp424 * fp170;
LIBINT2_REALTYPE fp119;
fp119 = fp255;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+119)*1+lsi)*1]),&(fp119),1);
LIBINT2_REALTYPE fp146;
fp146 = inteval->PB_y[vi] * fp147;
LIBINT2_REALTYPE fp223;
fp223 = 0 + fp146;
LIBINT2_REALTYPE fp426;
fp426 = fp252 * fp223;
LIBINT2_REALTYPE fp193;
fp193 = 0 + fp132;
LIBINT2_REALTYPE fp189;
fp189 = inteval->BO_z[vi] * fp193;
LIBINT2_REALTYPE fp188;
fp188 = fp192 + fp189;
LIBINT2_REALTYPE fp182;
fp182 = inteval->BO_z[vi] * fp188;
LIBINT2_REALTYPE fp181;
fp181 = fp186 + fp182;
LIBINT2_REALTYPE fp173;
fp173 = inteval->BO_z[vi] * fp181;
LIBINT2_REALTYPE fp172;
fp172 = fp179 + fp173;
LIBINT2_REALTYPE fp256;
fp256 = fp426 * fp172;
LIBINT2_REALTYPE fp118;
fp118 = fp256;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+118)*1+lsi)*1]),&(fp118),1);
LIBINT2_REALTYPE fp144;
fp144 = inteval->oo2z[vi] * fp147;
LIBINT2_REALTYPE fp145;
fp145 = inteval->PB_y[vi] * fp146;
LIBINT2_REALTYPE fp143;
fp143 = fp145 + fp144;
LIBINT2_REALTYPE fp222;
fp222 = 0 + fp143;
LIBINT2_REALTYPE fp428;
fp428 = fp252 * fp222;
LIBINT2_REALTYPE fp194;
fp194 = 0 + fp133;
LIBINT2_REALTYPE fp191;
fp191 = inteval->BO_z[vi] * fp194;
LIBINT2_REALTYPE fp190;
fp190 = fp193 + fp191;
LIBINT2_REALTYPE fp184;
fp184 = inteval->BO_z[vi] * fp190;
LIBINT2_REALTYPE fp183;
fp183 = fp188 + fp184;
LIBINT2_REALTYPE fp175;
fp175 = inteval->BO_z[vi] * fp183;
LIBINT2_REALTYPE fp174;
fp174 = fp181 + fp175;
LIBINT2_REALTYPE fp257;
fp257 = fp428 * fp174;
LIBINT2_REALTYPE fp117;
fp117 = fp257;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+117)*1+lsi)*1]),&(fp117),1);
LIBINT2_REALTYPE fp161;
fp161 = inteval->PB_x[vi] * fp160;
LIBINT2_REALTYPE fp253;
fp253 = 0 + fp161;
LIBINT2_REALTYPE fp430;
fp430 = fp253 * fp224;
LIBINT2_REALTYPE fp258;
fp258 = fp430 * fp172;
LIBINT2_REALTYPE fp116;
fp116 = fp258;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+116)*1+lsi)*1]),&(fp116),1);
LIBINT2_REALTYPE fp432;
fp432 = fp253 * fp223;
LIBINT2_REALTYPE fp259;
fp259 = fp432 * fp174;
LIBINT2_REALTYPE fp115;
fp115 = fp259;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+115)*1+lsi)*1]),&(fp115),1);
LIBINT2_REALTYPE fp163;
fp163 = inteval->oo2z[vi] * fp160;
LIBINT2_REALTYPE fp164;
fp164 = inteval->PB_x[vi] * fp161;
LIBINT2_REALTYPE fp162;
fp162 = fp164 + fp163;
LIBINT2_REALTYPE fp254;
fp254 = 0 + fp162;
LIBINT2_REALTYPE fp434;
fp434 = fp254 * fp224;
LIBINT2_REALTYPE fp260;
fp260 = fp434 * fp174;
LIBINT2_REALTYPE fp114;
fp114 = fp260;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+114)*1+lsi)*1]),&(fp114),1);
LIBINT2_REALTYPE fp221;
fp221 = inteval->BO_y[vi] * fp224;
LIBINT2_REALTYPE fp220;
fp220 = fp223 + fp221;
LIBINT2_REALTYPE fp400;
fp400 = fp252 * fp220;
LIBINT2_REALTYPE fp261;
fp261 = fp400 * fp179;
LIBINT2_REALTYPE fp113;
fp113 = fp261;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+113)*1+lsi)*1]),&(fp113),1);
LIBINT2_REALTYPE fp219;
fp219 = inteval->BO_y[vi] * fp223;
LIBINT2_REALTYPE fp218;
fp218 = fp222 + fp219;
LIBINT2_REALTYPE fp402;
fp402 = fp252 * fp218;
LIBINT2_REALTYPE fp262;
fp262 = fp402 * fp181;
LIBINT2_REALTYPE fp112;
fp112 = fp262;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+112)*1+lsi)*1]),&(fp112),1);
LIBINT2_REALTYPE fp141;
fp141 = fp158 * fp146;
LIBINT2_REALTYPE fp142;
fp142 = inteval->PB_y[vi] * fp143;
LIBINT2_REALTYPE fp140;
fp140 = fp142 + fp141;
LIBINT2_REALTYPE fp215;
fp215 = 0 + fp140;
LIBINT2_REALTYPE fp217;
fp217 = inteval->BO_y[vi] * fp222;
LIBINT2_REALTYPE fp216;
fp216 = fp215 + fp217;
LIBINT2_REALTYPE fp404;
fp404 = fp252 * fp216;
LIBINT2_REALTYPE fp263;
fp263 = fp404 * fp183;
LIBINT2_REALTYPE fp111;
fp111 = fp263;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+111)*1+lsi)*1]),&(fp111),1);
LIBINT2_REALTYPE fp406;
fp406 = fp253 * fp220;
LIBINT2_REALTYPE fp264;
fp264 = fp406 * fp181;
LIBINT2_REALTYPE fp110;
fp110 = fp264;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+110)*1+lsi)*1]),&(fp110),1);
LIBINT2_REALTYPE fp408;
fp408 = fp253 * fp218;
LIBINT2_REALTYPE fp265;
fp265 = fp408 * fp183;
LIBINT2_REALTYPE fp109;
fp109 = fp265;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+109)*1+lsi)*1]),&(fp109),1);
LIBINT2_REALTYPE fp410;
fp410 = fp254 * fp220;
LIBINT2_REALTYPE fp266;
fp266 = fp410 * fp183;
LIBINT2_REALTYPE fp108;
fp108 = fp266;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+108)*1+lsi)*1]),&(fp108),1);
LIBINT2_REALTYPE fp214;
fp214 = inteval->BO_y[vi] * fp220;
LIBINT2_REALTYPE fp213;
fp213 = fp218 + fp214;
LIBINT2_REALTYPE fp352;
fp352 = fp252 * fp213;
LIBINT2_REALTYPE fp267;
fp267 = fp352 * fp186;
LIBINT2_REALTYPE fp107;
fp107 = fp267;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+107)*1+lsi)*1]),&(fp107),1);
LIBINT2_REALTYPE fp212;
fp212 = inteval->BO_y[vi] * fp218;
LIBINT2_REALTYPE fp211;
fp211 = fp216 + fp212;
LIBINT2_REALTYPE fp354;
fp354 = fp252 * fp211;
LIBINT2_REALTYPE fp268;
fp268 = fp354 * fp188;
LIBINT2_REALTYPE fp106;
fp106 = fp268;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+106)*1+lsi)*1]),&(fp106),1);
LIBINT2_REALTYPE fp138;
fp138 = fp154 * fp143;
LIBINT2_REALTYPE fp139;
fp139 = inteval->PB_y[vi] * fp140;
LIBINT2_REALTYPE fp137;
fp137 = fp139 + fp138;
LIBINT2_REALTYPE fp206;
fp206 = 0 + fp137;
LIBINT2_REALTYPE fp208;
fp208 = inteval->BO_y[vi] * fp215;
LIBINT2_REALTYPE fp207;
fp207 = fp206 + fp208;
LIBINT2_REALTYPE fp210;
fp210 = inteval->BO_y[vi] * fp216;
LIBINT2_REALTYPE fp209;
fp209 = fp207 + fp210;
LIBINT2_REALTYPE fp356;
fp356 = fp252 * fp209;
LIBINT2_REALTYPE fp269;
fp269 = fp356 * fp190;
LIBINT2_REALTYPE fp105;
fp105 = fp269;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+105)*1+lsi)*1]),&(fp105),1);
LIBINT2_REALTYPE fp358;
fp358 = fp253 * fp213;
LIBINT2_REALTYPE fp270;
fp270 = fp358 * fp188;
LIBINT2_REALTYPE fp104;
fp104 = fp270;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+104)*1+lsi)*1]),&(fp104),1);
LIBINT2_REALTYPE fp360;
fp360 = fp253 * fp211;
LIBINT2_REALTYPE fp271;
fp271 = fp360 * fp190;
LIBINT2_REALTYPE fp103;
fp103 = fp271;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+103)*1+lsi)*1]),&(fp103),1);
LIBINT2_REALTYPE fp362;
fp362 = fp254 * fp213;
LIBINT2_REALTYPE fp272;
fp272 = fp362 * fp190;
LIBINT2_REALTYPE fp102;
fp102 = fp272;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+102)*1+lsi)*1]),&(fp102),1);
LIBINT2_REALTYPE fp205;
fp205 = inteval->BO_y[vi] * fp213;
LIBINT2_REALTYPE fp204;
fp204 = fp211 + fp205;
LIBINT2_REALTYPE fp274;
fp274 = fp252 * fp204;
LIBINT2_REALTYPE fp273;
fp273 = fp274 * fp192;
LIBINT2_REALTYPE fp101;
fp101 = fp273;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+101)*1+lsi)*1]),&(fp101),1);
LIBINT2_REALTYPE fp203;
fp203 = inteval->BO_y[vi] * fp211;
LIBINT2_REALTYPE fp202;
fp202 = fp209 + fp203;
LIBINT2_REALTYPE fp276;
fp276 = fp252 * fp202;
LIBINT2_REALTYPE fp275;
fp275 = fp276 * fp193;
LIBINT2_REALTYPE fp100;
fp100 = fp275;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+100)*1+lsi)*1]),&(fp100),1);
LIBINT2_REALTYPE fp201;
fp201 = inteval->BO_y[vi] * fp209;
LIBINT2_REALTYPE fp199;
fp199 = inteval->BO_y[vi] * fp207;
LIBINT2_REALTYPE fp197;
fp197 = inteval->BO_y[vi] * fp206;
LIBINT2_REALTYPE fp135;
fp135 = fp150 * fp140;
LIBINT2_REALTYPE fp136;
fp136 = inteval->PB_y[vi] * fp137;
LIBINT2_REALTYPE fp134;
fp134 = fp136 + fp135;
LIBINT2_REALTYPE fp195;
fp195 = 0 + fp134;
LIBINT2_REALTYPE fp196;
fp196 = fp195 + fp197;
LIBINT2_REALTYPE fp198;
fp198 = fp196 + fp199;
LIBINT2_REALTYPE fp200;
fp200 = fp198 + fp201;
LIBINT2_REALTYPE fp278;
fp278 = fp252 * fp200;
LIBINT2_REALTYPE fp277;
fp277 = fp278 * fp194;
LIBINT2_REALTYPE fp99;
fp99 = fp277;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+99)*1+lsi)*1]),&(fp99),1);
LIBINT2_REALTYPE fp280;
fp280 = fp253 * fp204;
LIBINT2_REALTYPE fp279;
fp279 = fp280 * fp193;
LIBINT2_REALTYPE fp98;
fp98 = fp279;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+98)*1+lsi)*1]),&(fp98),1);
LIBINT2_REALTYPE fp282;
fp282 = fp253 * fp202;
LIBINT2_REALTYPE fp281;
fp281 = fp282 * fp194;
LIBINT2_REALTYPE fp97;
fp97 = fp281;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+97)*1+lsi)*1]),&(fp97),1);
LIBINT2_REALTYPE fp284;
fp284 = fp254 * fp204;
LIBINT2_REALTYPE fp283;
fp283 = fp284 * fp194;
LIBINT2_REALTYPE fp96;
fp96 = fp283;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+96)*1+lsi)*1]),&(fp96),1);
LIBINT2_REALTYPE fp246;
fp246 = inteval->BO_x[vi] * fp252;
LIBINT2_REALTYPE fp245;
fp245 = fp253 + fp246;
LIBINT2_REALTYPE fp412;
fp412 = fp245 * fp224;
LIBINT2_REALTYPE fp285;
fp285 = fp412 * fp179;
LIBINT2_REALTYPE fp95;
fp95 = fp285;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+95)*1+lsi)*1]),&(fp95),1);
LIBINT2_REALTYPE fp414;
fp414 = fp245 * fp223;
LIBINT2_REALTYPE fp286;
fp286 = fp414 * fp181;
LIBINT2_REALTYPE fp94;
fp94 = fp286;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+94)*1+lsi)*1]),&(fp94),1);
LIBINT2_REALTYPE fp416;
fp416 = fp245 * fp222;
LIBINT2_REALTYPE fp287;
fp287 = fp416 * fp183;
LIBINT2_REALTYPE fp93;
fp93 = fp287;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+93)*1+lsi)*1]),&(fp93),1);
LIBINT2_REALTYPE fp248;
fp248 = inteval->BO_x[vi] * fp253;
LIBINT2_REALTYPE fp247;
fp247 = fp254 + fp248;
LIBINT2_REALTYPE fp418;
fp418 = fp247 * fp224;
LIBINT2_REALTYPE fp288;
fp288 = fp418 * fp181;
LIBINT2_REALTYPE fp92;
fp92 = fp288;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+92)*1+lsi)*1]),&(fp92),1);
LIBINT2_REALTYPE fp420;
fp420 = fp247 * fp223;
LIBINT2_REALTYPE fp289;
fp289 = fp420 * fp183;
LIBINT2_REALTYPE fp91;
fp91 = fp289;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+91)*1+lsi)*1]),&(fp91),1);
LIBINT2_REALTYPE fp157;
fp157 = fp158 * fp161;
LIBINT2_REALTYPE fp159;
fp159 = inteval->PB_x[vi] * fp162;
LIBINT2_REALTYPE fp156;
fp156 = fp159 + fp157;
LIBINT2_REALTYPE fp249;
fp249 = 0 + fp156;
LIBINT2_REALTYPE fp251;
fp251 = inteval->BO_x[vi] * fp254;
LIBINT2_REALTYPE fp250;
fp250 = fp249 + fp251;
LIBINT2_REALTYPE fp422;
fp422 = fp250 * fp224;
LIBINT2_REALTYPE fp290;
fp290 = fp422 * fp183;
LIBINT2_REALTYPE fp90;
fp90 = fp290;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+90)*1+lsi)*1]),&(fp90),1);
LIBINT2_REALTYPE fp370;
fp370 = fp245 * fp220;
LIBINT2_REALTYPE fp291;
fp291 = fp370 * fp186;
LIBINT2_REALTYPE fp89;
fp89 = fp291;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+89)*1+lsi)*1]),&(fp89),1);
LIBINT2_REALTYPE fp372;
fp372 = fp245 * fp218;
LIBINT2_REALTYPE fp292;
fp292 = fp372 * fp188;
LIBINT2_REALTYPE fp88;
fp88 = fp292;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+88)*1+lsi)*1]),&(fp88),1);
LIBINT2_REALTYPE fp374;
fp374 = fp245 * fp216;
LIBINT2_REALTYPE fp293;
fp293 = fp374 * fp190;
LIBINT2_REALTYPE fp87;
fp87 = fp293;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+87)*1+lsi)*1]),&(fp87),1);
LIBINT2_REALTYPE fp376;
fp376 = fp247 * fp220;
LIBINT2_REALTYPE fp294;
fp294 = fp376 * fp188;
LIBINT2_REALTYPE fp86;
fp86 = fp294;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+86)*1+lsi)*1]),&(fp86),1);
LIBINT2_REALTYPE fp378;
fp378 = fp247 * fp218;
LIBINT2_REALTYPE fp295;
fp295 = fp378 * fp190;
LIBINT2_REALTYPE fp85;
fp85 = fp295;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+85)*1+lsi)*1]),&(fp85),1);
LIBINT2_REALTYPE fp380;
fp380 = fp250 * fp220;
LIBINT2_REALTYPE fp296;
fp296 = fp380 * fp190;
LIBINT2_REALTYPE fp84;
fp84 = fp296;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+84)*1+lsi)*1]),&(fp84),1);
LIBINT2_REALTYPE fp298;
fp298 = fp245 * fp213;
LIBINT2_REALTYPE fp297;
fp297 = fp298 * fp192;
LIBINT2_REALTYPE fp83;
fp83 = fp297;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+83)*1+lsi)*1]),&(fp83),1);
LIBINT2_REALTYPE fp300;
fp300 = fp245 * fp211;
LIBINT2_REALTYPE fp299;
fp299 = fp300 * fp193;
LIBINT2_REALTYPE fp82;
fp82 = fp299;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+82)*1+lsi)*1]),&(fp82),1);
LIBINT2_REALTYPE fp302;
fp302 = fp245 * fp209;
LIBINT2_REALTYPE fp301;
fp301 = fp302 * fp194;
LIBINT2_REALTYPE fp81;
fp81 = fp301;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+81)*1+lsi)*1]),&(fp81),1);
LIBINT2_REALTYPE fp304;
fp304 = fp247 * fp213;
LIBINT2_REALTYPE fp303;
fp303 = fp304 * fp193;
LIBINT2_REALTYPE fp80;
fp80 = fp303;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+80)*1+lsi)*1]),&(fp80),1);
LIBINT2_REALTYPE fp306;
fp306 = fp247 * fp211;
LIBINT2_REALTYPE fp305;
fp305 = fp306 * fp194;
LIBINT2_REALTYPE fp79;
fp79 = fp305;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+79)*1+lsi)*1]),&(fp79),1);
LIBINT2_REALTYPE fp308;
fp308 = fp250 * fp213;
LIBINT2_REALTYPE fp307;
fp307 = fp308 * fp194;
LIBINT2_REALTYPE fp78;
fp78 = fp307;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+78)*1+lsi)*1]),&(fp78),1);
LIBINT2_REALTYPE fp237;
fp237 = inteval->BO_x[vi] * fp245;
LIBINT2_REALTYPE fp236;
fp236 = fp247 + fp237;
LIBINT2_REALTYPE fp382;
fp382 = fp236 * fp224;
LIBINT2_REALTYPE fp309;
fp309 = fp382 * fp186;
LIBINT2_REALTYPE fp77;
fp77 = fp309;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+77)*1+lsi)*1]),&(fp77),1);
LIBINT2_REALTYPE fp384;
fp384 = fp236 * fp223;
LIBINT2_REALTYPE fp310;
fp310 = fp384 * fp188;
LIBINT2_REALTYPE fp76;
fp76 = fp310;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+76)*1+lsi)*1]),&(fp76),1);
LIBINT2_REALTYPE fp386;
fp386 = fp236 * fp222;
LIBINT2_REALTYPE fp311;
fp311 = fp386 * fp190;
LIBINT2_REALTYPE fp75;
fp75 = fp311;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+75)*1+lsi)*1]),&(fp75),1);
LIBINT2_REALTYPE fp239;
fp239 = inteval->BO_x[vi] * fp247;
LIBINT2_REALTYPE fp238;
fp238 = fp250 + fp239;
LIBINT2_REALTYPE fp388;
fp388 = fp238 * fp224;
LIBINT2_REALTYPE fp312;
fp312 = fp388 * fp188;
LIBINT2_REALTYPE fp74;
fp74 = fp312;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+74)*1+lsi)*1]),&(fp74),1);
LIBINT2_REALTYPE fp390;
fp390 = fp238 * fp223;
LIBINT2_REALTYPE fp313;
fp313 = fp390 * fp190;
LIBINT2_REALTYPE fp73;
fp73 = fp313;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+73)*1+lsi)*1]),&(fp73),1);
LIBINT2_REALTYPE fp153;
fp153 = fp154 * fp162;
LIBINT2_REALTYPE fp155;
fp155 = inteval->PB_x[vi] * fp156;
LIBINT2_REALTYPE fp152;
fp152 = fp155 + fp153;
LIBINT2_REALTYPE fp240;
fp240 = 0 + fp152;
LIBINT2_REALTYPE fp242;
fp242 = inteval->BO_x[vi] * fp249;
LIBINT2_REALTYPE fp241;
fp241 = fp240 + fp242;
LIBINT2_REALTYPE fp244;
fp244 = inteval->BO_x[vi] * fp250;
LIBINT2_REALTYPE fp243;
fp243 = fp241 + fp244;
LIBINT2_REALTYPE fp392;
fp392 = fp243 * fp224;
LIBINT2_REALTYPE fp314;
fp314 = fp392 * fp190;
LIBINT2_REALTYPE fp72;
fp72 = fp314;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+72)*1+lsi)*1]),&(fp72),1);
LIBINT2_REALTYPE fp316;
fp316 = fp236 * fp220;
LIBINT2_REALTYPE fp315;
fp315 = fp316 * fp192;
LIBINT2_REALTYPE fp71;
fp71 = fp315;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+71)*1+lsi)*1]),&(fp71),1);
LIBINT2_REALTYPE fp318;
fp318 = fp236 * fp218;
LIBINT2_REALTYPE fp317;
fp317 = fp318 * fp193;
LIBINT2_REALTYPE fp70;
fp70 = fp317;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+70)*1+lsi)*1]),&(fp70),1);
LIBINT2_REALTYPE fp320;
fp320 = fp236 * fp216;
LIBINT2_REALTYPE fp319;
fp319 = fp320 * fp194;
LIBINT2_REALTYPE fp69;
fp69 = fp319;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+69)*1+lsi)*1]),&(fp69),1);
LIBINT2_REALTYPE fp322;
fp322 = fp238 * fp220;
LIBINT2_REALTYPE fp321;
fp321 = fp322 * fp193;
LIBINT2_REALTYPE fp68;
fp68 = fp321;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+68)*1+lsi)*1]),&(fp68),1);
LIBINT2_REALTYPE fp324;
fp324 = fp238 * fp218;
LIBINT2_REALTYPE fp323;
fp323 = fp324 * fp194;
LIBINT2_REALTYPE fp67;
fp67 = fp323;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+67)*1+lsi)*1]),&(fp67),1);
LIBINT2_REALTYPE fp326;
fp326 = fp243 * fp220;
LIBINT2_REALTYPE fp325;
fp325 = fp326 * fp194;
LIBINT2_REALTYPE fp66;
fp66 = fp325;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+66)*1+lsi)*1]),&(fp66),1);
LIBINT2_REALTYPE fp226;
fp226 = inteval->BO_x[vi] * fp236;
LIBINT2_REALTYPE fp225;
fp225 = fp238 + fp226;
LIBINT2_REALTYPE fp328;
fp328 = fp225 * fp224;
LIBINT2_REALTYPE fp327;
fp327 = fp328 * fp192;
LIBINT2_REALTYPE fp65;
fp65 = fp327;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+65)*1+lsi)*1]),&(fp65),1);
LIBINT2_REALTYPE fp330;
fp330 = fp225 * fp223;
LIBINT2_REALTYPE fp329;
fp329 = fp330 * fp193;
LIBINT2_REALTYPE fp64;
fp64 = fp329;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+64)*1+lsi)*1]),&(fp64),1);
LIBINT2_REALTYPE fp332;
fp332 = fp225 * fp222;
LIBINT2_REALTYPE fp331;
fp331 = fp332 * fp194;
LIBINT2_REALTYPE fp63;
fp63 = fp331;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+63)*1+lsi)*1]),&(fp63),1);
LIBINT2_REALTYPE fp228;
fp228 = inteval->BO_x[vi] * fp238;
LIBINT2_REALTYPE fp227;
fp227 = fp243 + fp228;
LIBINT2_REALTYPE fp334;
fp334 = fp227 * fp224;
LIBINT2_REALTYPE fp333;
fp333 = fp334 * fp193;
LIBINT2_REALTYPE fp62;
fp62 = fp333;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+62)*1+lsi)*1]),&(fp62),1);
LIBINT2_REALTYPE fp336;
fp336 = fp227 * fp223;
LIBINT2_REALTYPE fp335;
fp335 = fp336 * fp194;
LIBINT2_REALTYPE fp61;
fp61 = fp335;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+61)*1+lsi)*1]),&(fp61),1);
LIBINT2_REALTYPE fp235;
fp235 = inteval->BO_x[vi] * fp243;
LIBINT2_REALTYPE fp233;
fp233 = inteval->BO_x[vi] * fp241;
LIBINT2_REALTYPE fp231;
fp231 = inteval->BO_x[vi] * fp240;
LIBINT2_REALTYPE fp149;
fp149 = fp150 * fp156;
LIBINT2_REALTYPE fp151;
fp151 = inteval->PB_x[vi] * fp152;
LIBINT2_REALTYPE fp148;
fp148 = fp151 + fp149;
LIBINT2_REALTYPE fp229;
fp229 = 0 + fp148;
LIBINT2_REALTYPE fp230;
fp230 = fp229 + fp231;
LIBINT2_REALTYPE fp232;
fp232 = fp230 + fp233;
LIBINT2_REALTYPE fp234;
fp234 = fp232 + fp235;
LIBINT2_REALTYPE fp338;
fp338 = fp234 * fp224;
LIBINT2_REALTYPE fp337;
fp337 = fp338 * fp194;
LIBINT2_REALTYPE fp60;
fp60 = fp337;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+60)*1+lsi)*1]),&(fp60),1);
LIBINT2_REALTYPE fp339;
fp339 = fp424 * fp179;
LIBINT2_REALTYPE fp59;
fp59 = fp339;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+59)*1+lsi)*1]),&(fp59),1);
LIBINT2_REALTYPE fp340;
fp340 = fp426 * fp181;
LIBINT2_REALTYPE fp58;
fp58 = fp340;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+58)*1+lsi)*1]),&(fp58),1);
LIBINT2_REALTYPE fp341;
fp341 = fp428 * fp183;
LIBINT2_REALTYPE fp57;
fp57 = fp341;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+57)*1+lsi)*1]),&(fp57),1);
LIBINT2_REALTYPE fp342;
fp342 = fp430 * fp181;
LIBINT2_REALTYPE fp56;
fp56 = fp342;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+56)*1+lsi)*1]),&(fp56),1);
LIBINT2_REALTYPE fp343;
fp343 = fp432 * fp183;
LIBINT2_REALTYPE fp55;
fp55 = fp343;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+55)*1+lsi)*1]),&(fp55),1);
LIBINT2_REALTYPE fp344;
fp344 = fp434 * fp183;
LIBINT2_REALTYPE fp54;
fp54 = fp344;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+54)*1+lsi)*1]),&(fp54),1);
LIBINT2_REALTYPE fp345;
fp345 = fp400 * fp186;
LIBINT2_REALTYPE fp53;
fp53 = fp345;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+53)*1+lsi)*1]),&(fp53),1);
LIBINT2_REALTYPE fp346;
fp346 = fp402 * fp188;
LIBINT2_REALTYPE fp52;
fp52 = fp346;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+52)*1+lsi)*1]),&(fp52),1);
LIBINT2_REALTYPE fp347;
fp347 = fp404 * fp190;
LIBINT2_REALTYPE fp51;
fp51 = fp347;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+51)*1+lsi)*1]),&(fp51),1);
LIBINT2_REALTYPE fp348;
fp348 = fp406 * fp188;
LIBINT2_REALTYPE fp50;
fp50 = fp348;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+50)*1+lsi)*1]),&(fp50),1);
LIBINT2_REALTYPE fp349;
fp349 = fp408 * fp190;
LIBINT2_REALTYPE fp49;
fp49 = fp349;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+49)*1+lsi)*1]),&(fp49),1);
LIBINT2_REALTYPE fp350;
fp350 = fp410 * fp190;
LIBINT2_REALTYPE fp48;
fp48 = fp350;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+48)*1+lsi)*1]),&(fp48),1);
LIBINT2_REALTYPE fp351;
fp351 = fp352 * fp192;
LIBINT2_REALTYPE fp47;
fp47 = fp351;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+47)*1+lsi)*1]),&(fp47),1);
LIBINT2_REALTYPE fp353;
fp353 = fp354 * fp193;
LIBINT2_REALTYPE fp46;
fp46 = fp353;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+46)*1+lsi)*1]),&(fp46),1);
LIBINT2_REALTYPE fp355;
fp355 = fp356 * fp194;
LIBINT2_REALTYPE fp45;
fp45 = fp355;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+45)*1+lsi)*1]),&(fp45),1);
LIBINT2_REALTYPE fp357;
fp357 = fp358 * fp193;
LIBINT2_REALTYPE fp44;
fp44 = fp357;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+44)*1+lsi)*1]),&(fp44),1);
LIBINT2_REALTYPE fp359;
fp359 = fp360 * fp194;
LIBINT2_REALTYPE fp43;
fp43 = fp359;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+43)*1+lsi)*1]),&(fp43),1);
LIBINT2_REALTYPE fp361;
fp361 = fp362 * fp194;
LIBINT2_REALTYPE fp42;
fp42 = fp361;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+42)*1+lsi)*1]),&(fp42),1);
LIBINT2_REALTYPE fp363;
fp363 = fp412 * fp186;
LIBINT2_REALTYPE fp41;
fp41 = fp363;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+41)*1+lsi)*1]),&(fp41),1);
LIBINT2_REALTYPE fp364;
fp364 = fp414 * fp188;
LIBINT2_REALTYPE fp40;
fp40 = fp364;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+40)*1+lsi)*1]),&(fp40),1);
LIBINT2_REALTYPE fp365;
fp365 = fp416 * fp190;
LIBINT2_REALTYPE fp39;
fp39 = fp365;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+39)*1+lsi)*1]),&(fp39),1);
LIBINT2_REALTYPE fp366;
fp366 = fp418 * fp188;
LIBINT2_REALTYPE fp38;
fp38 = fp366;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+38)*1+lsi)*1]),&(fp38),1);
LIBINT2_REALTYPE fp367;
fp367 = fp420 * fp190;
LIBINT2_REALTYPE fp37;
fp37 = fp367;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+37)*1+lsi)*1]),&(fp37),1);
LIBINT2_REALTYPE fp368;
fp368 = fp422 * fp190;
LIBINT2_REALTYPE fp36;
fp36 = fp368;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+36)*1+lsi)*1]),&(fp36),1);
LIBINT2_REALTYPE fp369;
fp369 = fp370 * fp192;
LIBINT2_REALTYPE fp35;
fp35 = fp369;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+35)*1+lsi)*1]),&(fp35),1);
LIBINT2_REALTYPE fp371;
fp371 = fp372 * fp193;
LIBINT2_REALTYPE fp34;
fp34 = fp371;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+34)*1+lsi)*1]),&(fp34),1);
LIBINT2_REALTYPE fp373;
fp373 = fp374 * fp194;
LIBINT2_REALTYPE fp33;
fp33 = fp373;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+33)*1+lsi)*1]),&(fp33),1);
LIBINT2_REALTYPE fp375;
fp375 = fp376 * fp193;
LIBINT2_REALTYPE fp32;
fp32 = fp375;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+32)*1+lsi)*1]),&(fp32),1);
LIBINT2_REALTYPE fp377;
fp377 = fp378 * fp194;
LIBINT2_REALTYPE fp31;
fp31 = fp377;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+31)*1+lsi)*1]),&(fp31),1);
LIBINT2_REALTYPE fp379;
fp379 = fp380 * fp194;
LIBINT2_REALTYPE fp30;
fp30 = fp379;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+30)*1+lsi)*1]),&(fp30),1);
LIBINT2_REALTYPE fp381;
fp381 = fp382 * fp192;
LIBINT2_REALTYPE fp29;
fp29 = fp381;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+29)*1+lsi)*1]),&(fp29),1);
LIBINT2_REALTYPE fp383;
fp383 = fp384 * fp193;
LIBINT2_REALTYPE fp28;
fp28 = fp383;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+28)*1+lsi)*1]),&(fp28),1);
LIBINT2_REALTYPE fp385;
fp385 = fp386 * fp194;
LIBINT2_REALTYPE fp27;
fp27 = fp385;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+27)*1+lsi)*1]),&(fp27),1);
LIBINT2_REALTYPE fp387;
fp387 = fp388 * fp193;
LIBINT2_REALTYPE fp26;
fp26 = fp387;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+26)*1+lsi)*1]),&(fp26),1);
LIBINT2_REALTYPE fp389;
fp389 = fp390 * fp194;
LIBINT2_REALTYPE fp25;
fp25 = fp389;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+25)*1+lsi)*1]),&(fp25),1);
LIBINT2_REALTYPE fp391;
fp391 = fp392 * fp194;
LIBINT2_REALTYPE fp24;
fp24 = fp391;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+24)*1+lsi)*1]),&(fp24),1);
LIBINT2_REALTYPE fp393;
fp393 = fp424 * fp186;
LIBINT2_REALTYPE fp23;
fp23 = fp393;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+23)*1+lsi)*1]),&(fp23),1);
LIBINT2_REALTYPE fp394;
fp394 = fp426 * fp188;
LIBINT2_REALTYPE fp22;
fp22 = fp394;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+22)*1+lsi)*1]),&(fp22),1);
LIBINT2_REALTYPE fp395;
fp395 = fp428 * fp190;
LIBINT2_REALTYPE fp21;
fp21 = fp395;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+21)*1+lsi)*1]),&(fp21),1);
LIBINT2_REALTYPE fp396;
fp396 = fp430 * fp188;
LIBINT2_REALTYPE fp20;
fp20 = fp396;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+20)*1+lsi)*1]),&(fp20),1);
LIBINT2_REALTYPE fp397;
fp397 = fp432 * fp190;
LIBINT2_REALTYPE fp19;
fp19 = fp397;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+19)*1+lsi)*1]),&(fp19),1);
LIBINT2_REALTYPE fp398;
fp398 = fp434 * fp190;
LIBINT2_REALTYPE fp18;
fp18 = fp398;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+18)*1+lsi)*1]),&(fp18),1);
LIBINT2_REALTYPE fp399;
fp399 = fp400 * fp192;
LIBINT2_REALTYPE fp17;
fp17 = fp399;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+17)*1+lsi)*1]),&(fp17),1);
LIBINT2_REALTYPE fp401;
fp401 = fp402 * fp193;
LIBINT2_REALTYPE fp16;
fp16 = fp401;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+16)*1+lsi)*1]),&(fp16),1);
LIBINT2_REALTYPE fp403;
fp403 = fp404 * fp194;
LIBINT2_REALTYPE fp15;
fp15 = fp403;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+15)*1+lsi)*1]),&(fp15),1);
LIBINT2_REALTYPE fp405;
fp405 = fp406 * fp193;
LIBINT2_REALTYPE fp14;
fp14 = fp405;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+14)*1+lsi)*1]),&(fp14),1);
LIBINT2_REALTYPE fp407;
fp407 = fp408 * fp194;
LIBINT2_REALTYPE fp13;
fp13 = fp407;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+13)*1+lsi)*1]),&(fp13),1);
LIBINT2_REALTYPE fp409;
fp409 = fp410 * fp194;
LIBINT2_REALTYPE fp12;
fp12 = fp409;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+12)*1+lsi)*1]),&(fp12),1);
LIBINT2_REALTYPE fp411;
fp411 = fp412 * fp192;
LIBINT2_REALTYPE fp11;
fp11 = fp411;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+11)*1+lsi)*1]),&(fp11),1);
LIBINT2_REALTYPE fp413;
fp413 = fp414 * fp193;
LIBINT2_REALTYPE fp10;
fp10 = fp413;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+10)*1+lsi)*1]),&(fp10),1);
LIBINT2_REALTYPE fp415;
fp415 = fp416 * fp194;
LIBINT2_REALTYPE fp9;
fp9 = fp415;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+9)*1+lsi)*1]),&(fp9),1);
LIBINT2_REALTYPE fp417;
fp417 = fp418 * fp193;
LIBINT2_REALTYPE fp8;
fp8 = fp417;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+8)*1+lsi)*1]),&(fp8),1);
LIBINT2_REALTYPE fp419;
fp419 = fp420 * fp194;
LIBINT2_REALTYPE fp7;
fp7 = fp419;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+7)*1+lsi)*1]),&(fp7),1);
LIBINT2_REALTYPE fp421;
fp421 = fp422 * fp194;
LIBINT2_REALTYPE fp6;
fp6 = fp421;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+6)*1+lsi)*1]),&(fp6),1);
LIBINT2_REALTYPE fp423;
fp423 = fp424 * fp192;
LIBINT2_REALTYPE fp5;
fp5 = fp423;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+5)*1+lsi)*1]),&(fp5),1);
LIBINT2_REALTYPE fp425;
fp425 = fp426 * fp193;
LIBINT2_REALTYPE fp4;
fp4 = fp425;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+4)*1+lsi)*1]),&(fp4),1);
LIBINT2_REALTYPE fp427;
fp427 = fp428 * fp194;
LIBINT2_REALTYPE fp3;
fp3 = fp427;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+3)*1+lsi)*1]),&(fp3),1);
LIBINT2_REALTYPE fp429;
fp429 = fp430 * fp193;
LIBINT2_REALTYPE fp2;
fp2 = fp429;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+2)*1+lsi)*1]),&(fp2),1);
LIBINT2_REALTYPE fp431;
fp431 = fp432 * fp194;
LIBINT2_REALTYPE fp1;
fp1 = fp431;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+1)*1+lsi)*1]),&(fp1),1);
LIBINT2_REALTYPE fp433;
fp433 = fp434 * fp194;
LIBINT2_REALTYPE fp0;
fp0 = fp433;
_libint2_static_api_inc1_short_(&(stack[((hsi*6+0)*1+lsi)*1]),&(fp0),1);
}
}
}
const int hsi = 0;
const int lsi = 0;
const int vi = 0;
/** Number of flops = 435 */
}

#ifdef __cplusplus
};
#endif