#include <data/ptable.hpp>

qpp::ptable* qpp::ptable::instance;

void qpp::ptable::init_default(){
  this->arecs[0].aNumber=1;
  this->arecs[0].aName="Hydrogen";
  this->arecs[0].aSymbol="H";
  this->arecs[0].aRadius=79.0;
  this->arecs[0].aMass=1.008;
  this->arecs[0].aCovRad_Slater=25.0;

  this->arecs[1].aNumber=2;
  this->arecs[1].aName="Helium";
  this->arecs[1].aSymbol="He";
  this->arecs[1].aRadius=-1;
  this->arecs[1].aMass=4.002602;
  this->arecs[1].aCovRad_Slater=-1;

  this->arecs[2].aNumber=3;
  this->arecs[2].aName="Lithium";
  this->arecs[2].aSymbol="Li";
  this->arecs[2].aRadius=155.0;
  this->arecs[2].aMass=6.94;
  this->arecs[2].aCovRad_Slater=145.0;

  this->arecs[3].aNumber=4;
  this->arecs[3].aName="Beryllium";
  this->arecs[3].aSymbol="Be";
  this->arecs[3].aRadius=112.0;
  this->arecs[3].aMass=9.0121831;
  this->arecs[3].aCovRad_Slater=105.0;

  this->arecs[4].aNumber=5;
  this->arecs[4].aName="Boron";
  this->arecs[4].aSymbol="B";
  this->arecs[4].aRadius=98.0;
  this->arecs[4].aMass=10.81;
  this->arecs[4].aCovRad_Slater=85.0;

  this->arecs[5].aNumber=6;
  this->arecs[5].aName="Carbon";
  this->arecs[5].aSymbol="C";
  this->arecs[5].aRadius=91.0;
  this->arecs[5].aMass=12.011;
  this->arecs[5].aCovRad_Slater=70.0;

  this->arecs[6].aNumber=7;
  this->arecs[6].aName="Nitrogen";
  this->arecs[6].aSymbol="N";
  this->arecs[6].aRadius=92.0;
  this->arecs[6].aMass=14.007;
  this->arecs[6].aCovRad_Slater=65.0;

  this->arecs[7].aNumber=8;
  this->arecs[7].aName="Oxygen";
  this->arecs[7].aSymbol="O";
  this->arecs[7].aRadius=-1;
  this->arecs[7].aMass=15.999;
  this->arecs[7].aCovRad_Slater=60.0;

  this->arecs[8].aNumber=9;
  this->arecs[8].aName="Fluorine";
  this->arecs[8].aSymbol="F";
  this->arecs[8].aRadius=-1;
  this->arecs[8].aMass=18.998403163;
  this->arecs[8].aCovRad_Slater=50.0;

  this->arecs[9].aNumber=10;
  this->arecs[9].aName="Neon";
  this->arecs[9].aSymbol="Ne";
  this->arecs[9].aRadius=-1;
  this->arecs[9].aMass=20.1797;
  this->arecs[9].aCovRad_Slater=-1;

  this->arecs[10].aNumber=11;
  this->arecs[10].aName="Sodium";
  this->arecs[10].aSymbol="Na";
  this->arecs[10].aRadius=190.0;
  this->arecs[10].aMass=22.98976928;
  this->arecs[10].aCovRad_Slater=180.0;

  this->arecs[11].aNumber=12;
  this->arecs[11].aName="Magnesium";
  this->arecs[11].aSymbol="Mg";
  this->arecs[11].aRadius=160.0;
  this->arecs[11].aMass=24.305;
  this->arecs[11].aCovRad_Slater=150.0;

  this->arecs[12].aNumber=13;
  this->arecs[12].aName="Aluminum";
  this->arecs[12].aSymbol="Al";
  this->arecs[12].aRadius=143.0;
  this->arecs[12].aMass=26.9815385;
  this->arecs[12].aCovRad_Slater=125.0;

  this->arecs[13].aNumber=14;
  this->arecs[13].aName="Silicon";
  this->arecs[13].aSymbol="Si";
  this->arecs[13].aRadius=132.0;
  this->arecs[13].aMass=28.085;
  this->arecs[13].aCovRad_Slater=110.00000000000001;

  this->arecs[14].aNumber=15;
  this->arecs[14].aName="Phosphorus";
  this->arecs[14].aSymbol="P";
  this->arecs[14].aRadius=128.0;
  this->arecs[14].aMass=30.973761998;
  this->arecs[14].aCovRad_Slater=100.0;

  this->arecs[15].aNumber=16;
  this->arecs[15].aName="Sulfur";
  this->arecs[15].aSymbol="S";
  this->arecs[15].aRadius=127.0;
  this->arecs[15].aMass=32.06;
  this->arecs[15].aCovRad_Slater=100.0;

  this->arecs[16].aNumber=17;
  this->arecs[16].aName="Chlorine";
  this->arecs[16].aSymbol="Cl";
  this->arecs[16].aRadius=-1;
  this->arecs[16].aMass=35.45;
  this->arecs[16].aCovRad_Slater=100.0;

  this->arecs[17].aNumber=18;
  this->arecs[17].aName="Argon";
  this->arecs[17].aSymbol="Ar";
  this->arecs[17].aRadius=-1;
  this->arecs[17].aMass=39.948;
  this->arecs[17].aCovRad_Slater=-1;

  this->arecs[18].aNumber=19;
  this->arecs[18].aName="Potassium";
  this->arecs[18].aSymbol="K";
  this->arecs[18].aRadius=235.0;
  this->arecs[18].aMass=39.0983;
  this->arecs[18].aCovRad_Slater=220.00000000000003;

  this->arecs[19].aNumber=20;
  this->arecs[19].aName="Calcium";
  this->arecs[19].aSymbol="Ca";
  this->arecs[19].aRadius=197.0;
  this->arecs[19].aMass=40.078;
  this->arecs[19].aCovRad_Slater=180.0;

  this->arecs[20].aNumber=21;
  this->arecs[20].aName="Scandium";
  this->arecs[20].aSymbol="Sc";
  this->arecs[20].aRadius=162.0;
  this->arecs[20].aMass=44.955908;
  this->arecs[20].aCovRad_Slater=160.0;

  this->arecs[21].aNumber=22;
  this->arecs[21].aName="Titanium";
  this->arecs[21].aSymbol="Ti";
  this->arecs[21].aRadius=147.0;
  this->arecs[21].aMass=47.867;
  this->arecs[21].aCovRad_Slater=140.0;

  this->arecs[22].aNumber=23;
  this->arecs[22].aName="Vanadium";
  this->arecs[22].aSymbol="V";
  this->arecs[22].aRadius=134.0;
  this->arecs[22].aMass=50.9415;
  this->arecs[22].aCovRad_Slater=135.0;

  this->arecs[23].aNumber=24;
  this->arecs[23].aName="Chromium";
  this->arecs[23].aSymbol="Cr";
  this->arecs[23].aRadius=130.0;
  this->arecs[23].aMass=51.9961;
  this->arecs[23].aCovRad_Slater=140.0;

  this->arecs[24].aNumber=25;
  this->arecs[24].aName="Manganese";
  this->arecs[24].aSymbol="Mn";
  this->arecs[24].aRadius=135.0;
  this->arecs[24].aMass=54.938044;
  this->arecs[24].aCovRad_Slater=140.0;

  this->arecs[25].aNumber=26;
  this->arecs[25].aName="Iron";
  this->arecs[25].aSymbol="Fe";
  this->arecs[25].aRadius=126.0;
  this->arecs[25].aMass=55.845;
  this->arecs[25].aCovRad_Slater=140.0;

  this->arecs[26].aNumber=27;
  this->arecs[26].aName="Cobalt";
  this->arecs[26].aSymbol="Co";
  this->arecs[26].aRadius=125.0;
  this->arecs[26].aMass=58.933194;
  this->arecs[26].aCovRad_Slater=135.0;

  this->arecs[27].aNumber=28;
  this->arecs[27].aName="Nickel";
  this->arecs[27].aSymbol="Ni";
  this->arecs[27].aRadius=124.0;
  this->arecs[27].aMass=58.6934;
  this->arecs[27].aCovRad_Slater=135.0;

  this->arecs[28].aNumber=29;
  this->arecs[28].aName="Copper";
  this->arecs[28].aSymbol="Cu";
  this->arecs[28].aRadius=128.0;
  this->arecs[28].aMass=63.546;
  this->arecs[28].aCovRad_Slater=135.0;

  this->arecs[29].aNumber=30;
  this->arecs[29].aName="Zinc";
  this->arecs[29].aSymbol="Zn";
  this->arecs[29].aRadius=138.0;
  this->arecs[29].aMass=65.38;
  this->arecs[29].aCovRad_Slater=135.0;

  this->arecs[30].aNumber=31;
  this->arecs[30].aName="Gallium";
  this->arecs[30].aSymbol="Ga";
  this->arecs[30].aRadius=141.0;
  this->arecs[30].aMass=69.723;
  this->arecs[30].aCovRad_Slater=130.0;

  this->arecs[31].aNumber=32;
  this->arecs[31].aName="Germanium";
  this->arecs[31].aSymbol="Ge";
  this->arecs[31].aRadius=137.0;
  this->arecs[31].aMass=72.63;
  this->arecs[31].aCovRad_Slater=125.0;

  this->arecs[32].aNumber=33;
  this->arecs[32].aName="Arsenic";
  this->arecs[32].aSymbol="As";
  this->arecs[32].aRadius=139.0;
  this->arecs[32].aMass=74.921595;
  this->arecs[32].aCovRad_Slater=114.99999999999999;

  this->arecs[33].aNumber=34;
  this->arecs[33].aName="Selenium";
  this->arecs[33].aSymbol="Se";
  this->arecs[33].aRadius=140.0;
  this->arecs[33].aMass=78.971;
  this->arecs[33].aCovRad_Slater=114.99999999999999;

  this->arecs[34].aNumber=35;
  this->arecs[34].aName="Bromine";
  this->arecs[34].aSymbol="Br";
  this->arecs[34].aRadius=-1;
  this->arecs[34].aMass=79.904;
  this->arecs[34].aCovRad_Slater=114.99999999999999;

  this->arecs[35].aNumber=36;
  this->arecs[35].aName="Krypton";
  this->arecs[35].aSymbol="Kr";
  this->arecs[35].aRadius=-1;
  this->arecs[35].aMass=83.798;
  this->arecs[35].aCovRad_Slater=-1;

  this->arecs[36].aNumber=37;
  this->arecs[36].aName="Rubidium";
  this->arecs[36].aSymbol="Rb";
  this->arecs[36].aRadius=248.0;
  this->arecs[36].aMass=85.4678;
  this->arecs[36].aCovRad_Slater=235.0;

  this->arecs[37].aNumber=38;
  this->arecs[37].aName="Strontium";
  this->arecs[37].aSymbol="Sr";
  this->arecs[37].aRadius=215.0;
  this->arecs[37].aMass=87.62;
  this->arecs[37].aCovRad_Slater=200.0;

  this->arecs[38].aNumber=39;
  this->arecs[38].aName="Yttrium";
  this->arecs[38].aSymbol="Y";
  this->arecs[38].aRadius=178.0;
  this->arecs[38].aMass=88.90584;
  this->arecs[38].aCovRad_Slater=180.0;

  this->arecs[39].aNumber=40;
  this->arecs[39].aName="Zirconium";
  this->arecs[39].aSymbol="Zr";
  this->arecs[39].aRadius=160.0;
  this->arecs[39].aMass=91.224;
  this->arecs[39].aCovRad_Slater=155.0;

  this->arecs[40].aNumber=41;
  this->arecs[40].aName="Niobium";
  this->arecs[40].aSymbol="Nb";
  this->arecs[40].aRadius=146.0;
  this->arecs[40].aMass=92.90637;
  this->arecs[40].aCovRad_Slater=145.0;

  this->arecs[41].aNumber=42;
  this->arecs[41].aName="Molybdenum";
  this->arecs[41].aSymbol="Mo";
  this->arecs[41].aRadius=139.0;
  this->arecs[41].aMass=95.95;
  this->arecs[41].aCovRad_Slater=145.0;

  this->arecs[42].aNumber=43;
  this->arecs[42].aName="Technetium";
  this->arecs[42].aSymbol="Tc";
  this->arecs[42].aRadius=136.0;
  this->arecs[42].aMass=97.90721;
  this->arecs[42].aCovRad_Slater=135.0;

  this->arecs[43].aNumber=44;
  this->arecs[43].aName="Ruthenium";
  this->arecs[43].aSymbol="Ru";
  this->arecs[43].aRadius=134.0;
  this->arecs[43].aMass=101.07;
  this->arecs[43].aCovRad_Slater=130.0;

  this->arecs[44].aNumber=45;
  this->arecs[44].aName="Rhodium";
  this->arecs[44].aSymbol="Rh";
  this->arecs[44].aRadius=134.0;
  this->arecs[44].aMass=102.9055;
  this->arecs[44].aCovRad_Slater=135.0;

  this->arecs[45].aNumber=46;
  this->arecs[45].aName="Palladium";
  this->arecs[45].aSymbol="Pd";
  this->arecs[45].aRadius=137.0;
  this->arecs[45].aMass=106.42;
  this->arecs[45].aCovRad_Slater=140.0;

  this->arecs[46].aNumber=47;
  this->arecs[46].aName="Silver";
  this->arecs[46].aSymbol="Ag";
  this->arecs[46].aRadius=144.0;
  this->arecs[46].aMass=107.8682;
  this->arecs[46].aCovRad_Slater=160.0;

  this->arecs[47].aNumber=48;
  this->arecs[47].aName="Cadmium";
  this->arecs[47].aSymbol="Cd";
  this->arecs[47].aRadius=154.0;
  this->arecs[47].aMass=112.414;
  this->arecs[47].aCovRad_Slater=155.0;

  this->arecs[48].aNumber=49;
  this->arecs[48].aName="Indium";
  this->arecs[48].aSymbol="In";
  this->arecs[48].aRadius=166.0;
  this->arecs[48].aMass=114.818;
  this->arecs[48].aCovRad_Slater=155.0;

  this->arecs[49].aNumber=50;
  this->arecs[49].aName="Tin";
  this->arecs[49].aSymbol="Sn";
  this->arecs[49].aRadius=162.0;
  this->arecs[49].aMass=118.71;
  this->arecs[49].aCovRad_Slater=145.0;

  this->arecs[50].aNumber=51;
  this->arecs[50].aName="Antimony";
  this->arecs[50].aSymbol="Sb";
  this->arecs[50].aRadius=159.0;
  this->arecs[50].aMass=121.76;
  this->arecs[50].aCovRad_Slater=145.0;

  this->arecs[51].aNumber=52;
  this->arecs[51].aName="Tellurium";
  this->arecs[51].aSymbol="Te";
  this->arecs[51].aRadius=160.0;
  this->arecs[51].aMass=127.6;
  this->arecs[51].aCovRad_Slater=140.0;

  this->arecs[52].aNumber=53;
  this->arecs[52].aName="Iodine";
  this->arecs[52].aSymbol="I";
  this->arecs[52].aRadius=-1;
  this->arecs[52].aMass=126.90447;
  this->arecs[52].aCovRad_Slater=140.0;

  this->arecs[53].aNumber=54;
  this->arecs[53].aName="Xenon";
  this->arecs[53].aSymbol="Xe";
  this->arecs[53].aRadius=-1;
  this->arecs[53].aMass=131.293;
  this->arecs[53].aCovRad_Slater=-1;

  this->arecs[54].aNumber=55;
  this->arecs[54].aName="Cesium";
  this->arecs[54].aSymbol="Cs";
  this->arecs[54].aRadius=267.0;
  this->arecs[54].aMass=132.90545196;
  this->arecs[54].aCovRad_Slater=260.0;

  this->arecs[55].aNumber=56;
  this->arecs[55].aName="Barium";
  this->arecs[55].aSymbol="Ba";
  this->arecs[55].aRadius=222.0;
  this->arecs[55].aMass=137.327;
  this->arecs[55].aCovRad_Slater=215.0;

  this->arecs[56].aNumber=57;
  this->arecs[56].aName="Lanthanum";
  this->arecs[56].aSymbol="La";
  this->arecs[56].aRadius=187.0;
  this->arecs[56].aMass=138.90547;
  this->arecs[56].aCovRad_Slater=195.0;

  this->arecs[57].aNumber=58;
  this->arecs[57].aName="Cerium";
  this->arecs[57].aSymbol="Ce";
  this->arecs[57].aRadius=181.0;
  this->arecs[57].aMass=140.116;
  this->arecs[57].aCovRad_Slater=185.0;

  this->arecs[58].aNumber=59;
  this->arecs[58].aName="Praseodymium";
  this->arecs[58].aSymbol="Pr";
  this->arecs[58].aRadius=182.0;
  this->arecs[58].aMass=140.90766;
  this->arecs[58].aCovRad_Slater=185.0;

  this->arecs[59].aNumber=60;
  this->arecs[59].aName="Neodymium";
  this->arecs[59].aSymbol="Nd";
  this->arecs[59].aRadius=182.0;
  this->arecs[59].aMass=144.242;
  this->arecs[59].aCovRad_Slater=185.0;

  this->arecs[60].aNumber=61;
  this->arecs[60].aName="Promethium";
  this->arecs[60].aSymbol="Pm";
  this->arecs[60].aRadius=-1;
  this->arecs[60].aMass=144.91276;
  this->arecs[60].aCovRad_Slater=185.0;

  this->arecs[61].aNumber=62;
  this->arecs[61].aName="Samarium";
  this->arecs[61].aSymbol="Sm";
  this->arecs[61].aRadius=181.0;
  this->arecs[61].aMass=150.36;
  this->arecs[61].aCovRad_Slater=185.0;

  this->arecs[62].aNumber=63;
  this->arecs[62].aName="Europium";
  this->arecs[62].aSymbol="Eu";
  this->arecs[62].aRadius=199.0;
  this->arecs[62].aMass=151.964;
  this->arecs[62].aCovRad_Slater=185.0;

  this->arecs[63].aNumber=64;
  this->arecs[63].aName="Gadolinium";
  this->arecs[63].aSymbol="Gd";
  this->arecs[63].aRadius=179.0;
  this->arecs[63].aMass=157.25;
  this->arecs[63].aCovRad_Slater=180.0;

  this->arecs[64].aNumber=65;
  this->arecs[64].aName="Terbium";
  this->arecs[64].aSymbol="Tb";
  this->arecs[64].aRadius=180.0;
  this->arecs[64].aMass=158.92535;
  this->arecs[64].aCovRad_Slater=175.0;

  this->arecs[65].aNumber=66;
  this->arecs[65].aName="Dysprosium";
  this->arecs[65].aSymbol="Dy";
  this->arecs[65].aRadius=180.0;
  this->arecs[65].aMass=162.5;
  this->arecs[65].aCovRad_Slater=175.0;

  this->arecs[66].aNumber=67;
  this->arecs[66].aName="Holmium";
  this->arecs[66].aSymbol="Ho";
  this->arecs[66].aRadius=179.0;
  this->arecs[66].aMass=164.93033;
  this->arecs[66].aCovRad_Slater=175.0;

  this->arecs[67].aNumber=68;
  this->arecs[67].aName="Erbium";
  this->arecs[67].aSymbol="Er";
  this->arecs[67].aRadius=178.0;
  this->arecs[67].aMass=167.259;
  this->arecs[67].aCovRad_Slater=175.0;

  this->arecs[68].aNumber=69;
  this->arecs[68].aName="Thulium";
  this->arecs[68].aSymbol="Tm";
  this->arecs[68].aRadius=177.0;
  this->arecs[68].aMass=168.93422;
  this->arecs[68].aCovRad_Slater=175.0;

  this->arecs[69].aNumber=70;
  this->arecs[69].aName="Ytterbium";
  this->arecs[69].aSymbol="Yb";
  this->arecs[69].aRadius=194.0;
  this->arecs[69].aMass=173.045;
  this->arecs[69].aCovRad_Slater=175.0;

  this->arecs[70].aNumber=71;
  this->arecs[70].aName="Lutetium";
  this->arecs[70].aSymbol="Lu";
  this->arecs[70].aRadius=175.0;
  this->arecs[70].aMass=174.9668;
  this->arecs[70].aCovRad_Slater=175.0;

  this->arecs[71].aNumber=72;
  this->arecs[71].aName="Hafnium";
  this->arecs[71].aSymbol="Hf";
  this->arecs[71].aRadius=167.0;
  this->arecs[71].aMass=178.49;
  this->arecs[71].aCovRad_Slater=155.0;

  this->arecs[72].aNumber=73;
  this->arecs[72].aName="Tantalum";
  this->arecs[72].aSymbol="Ta";
  this->arecs[72].aRadius=149.0;
  this->arecs[72].aMass=180.94788;
  this->arecs[72].aCovRad_Slater=145.0;

  this->arecs[73].aNumber=74;
  this->arecs[73].aName="Tungsten";
  this->arecs[73].aSymbol="W";
  this->arecs[73].aRadius=141.0;
  this->arecs[73].aMass=183.84;
  this->arecs[73].aCovRad_Slater=135.0;

  this->arecs[74].aNumber=75;
  this->arecs[74].aName="Rhenium";
  this->arecs[74].aSymbol="Re";
  this->arecs[74].aRadius=137.0;
  this->arecs[74].aMass=186.207;
  this->arecs[74].aCovRad_Slater=135.0;

  this->arecs[75].aNumber=76;
  this->arecs[75].aName="Osmium";
  this->arecs[75].aSymbol="Os";
  this->arecs[75].aRadius=135.0;
  this->arecs[75].aMass=190.23;
  this->arecs[75].aCovRad_Slater=130.0;

  this->arecs[76].aNumber=77;
  this->arecs[76].aName="Iridium";
  this->arecs[76].aSymbol="Ir";
  this->arecs[76].aRadius=136.0;
  this->arecs[76].aMass=192.217;
  this->arecs[76].aCovRad_Slater=135.0;

  this->arecs[77].aNumber=78;
  this->arecs[77].aName="Platinum";
  this->arecs[77].aSymbol="Pt";
  this->arecs[77].aRadius=139.0;
  this->arecs[77].aMass=195.084;
  this->arecs[77].aCovRad_Slater=135.0;

  this->arecs[78].aNumber=79;
  this->arecs[78].aName="Gold";
  this->arecs[78].aSymbol="Au";
  this->arecs[78].aRadius=146.0;
  this->arecs[78].aMass=196.966569;
  this->arecs[78].aCovRad_Slater=135.0;

  this->arecs[79].aNumber=80;
  this->arecs[79].aName="Mercury";
  this->arecs[79].aSymbol="Hg";
  this->arecs[79].aRadius=157.0;
  this->arecs[79].aMass=200.592;
  this->arecs[79].aCovRad_Slater=150.0;

  this->arecs[80].aNumber=81;
  this->arecs[80].aName="Thallium";
  this->arecs[80].aSymbol="Tl";
  this->arecs[80].aRadius=171.0;
  this->arecs[80].aMass=204.38;
  this->arecs[80].aCovRad_Slater=190.0;

  this->arecs[81].aNumber=82;
  this->arecs[81].aName="Lead";
  this->arecs[81].aSymbol="Pb";
  this->arecs[81].aRadius=175.0;
  this->arecs[81].aMass=207.2;
  this->arecs[81].aCovRad_Slater=-1;

  this->arecs[82].aNumber=83;
  this->arecs[82].aName="Bismuth";
  this->arecs[82].aSymbol="Bi";
  this->arecs[82].aRadius=170.0;
  this->arecs[82].aMass=208.9804;
  this->arecs[82].aCovRad_Slater=160.0;

  this->arecs[83].aNumber=84;
  this->arecs[83].aName="Polonium";
  this->arecs[83].aSymbol="Po";
  this->arecs[83].aRadius=176.0;
  this->arecs[83].aMass=209.0;
  this->arecs[83].aCovRad_Slater=190.0;

  this->arecs[84].aNumber=85;
  this->arecs[84].aName="Astatine";
  this->arecs[84].aSymbol="At";
  this->arecs[84].aRadius=-1;
  this->arecs[84].aMass=210.0;
  this->arecs[84].aCovRad_Slater=-1;

  this->arecs[85].aNumber=86;
  this->arecs[85].aName="Radon";
  this->arecs[85].aSymbol="Rn";
  this->arecs[85].aRadius=-1;
  this->arecs[85].aMass=222.0;
  this->arecs[85].aCovRad_Slater=-1;

  this->arecs[86].aNumber=87;
  this->arecs[86].aName="Francium";
  this->arecs[86].aSymbol="Fr";
  this->arecs[86].aRadius=-1;
  this->arecs[86].aMass=223.0;
  this->arecs[86].aCovRad_Slater=-1;

  this->arecs[87].aNumber=88;
  this->arecs[87].aName="Radium";
  this->arecs[87].aSymbol="Ra";
  this->arecs[87].aRadius=-1;
  this->arecs[87].aMass=226.0;
  this->arecs[87].aCovRad_Slater=215.0;

  this->arecs[88].aNumber=89;
  this->arecs[88].aName="Actinium";
  this->arecs[88].aSymbol="Ac";
  this->arecs[88].aRadius=188.0;
  this->arecs[88].aMass=227.0;
  this->arecs[88].aCovRad_Slater=195.0;

  this->arecs[89].aNumber=90;
  this->arecs[89].aName="Thorium";
  this->arecs[89].aSymbol="Th";
  this->arecs[89].aRadius=180.0;
  this->arecs[89].aMass=232.0377;
  this->arecs[89].aCovRad_Slater=180.0;

  this->arecs[90].aNumber=91;
  this->arecs[90].aName="Protactinium";
  this->arecs[90].aSymbol="Pa";
  this->arecs[90].aRadius=161.0;
  this->arecs[90].aMass=231.03588;
  this->arecs[90].aCovRad_Slater=180.0;

  this->arecs[91].aNumber=92;
  this->arecs[91].aName="Uranium";
  this->arecs[91].aSymbol="U";
  this->arecs[91].aRadius=138.0;
  this->arecs[91].aMass=238.02891;
  this->arecs[91].aCovRad_Slater=175.0;

  this->arecs[92].aNumber=93;
  this->arecs[92].aName="Neptunium";
  this->arecs[92].aSymbol="Np";
  this->arecs[92].aRadius=130.0;
  this->arecs[92].aMass=237.0;
  this->arecs[92].aCovRad_Slater=175.0;

  this->arecs[93].aNumber=94;
  this->arecs[93].aName="Plutonium";
  this->arecs[93].aSymbol="Pu";
  this->arecs[93].aRadius=151.0;
  this->arecs[93].aMass=244.0;
  this->arecs[93].aCovRad_Slater=175.0;

  this->arecs[94].aNumber=95;
  this->arecs[94].aName="Americium";
  this->arecs[94].aSymbol="Am";
  this->arecs[94].aRadius=173.0;
  this->arecs[94].aMass=243.0;
  this->arecs[94].aCovRad_Slater=175.0;

  this->arecs[95].aNumber=96;
  this->arecs[95].aName="Curium";
  this->arecs[95].aSymbol="Cm";
  this->arecs[95].aRadius=299.0;
  this->arecs[95].aMass=247.0;
  this->arecs[95].aCovRad_Slater=-1;

  this->arecs[96].aNumber=97;
  this->arecs[96].aName="Berkelium";
  this->arecs[96].aSymbol="Bk";
  this->arecs[96].aRadius=297.0;
  this->arecs[96].aMass=247.0;
  this->arecs[96].aCovRad_Slater=-1;

  this->arecs[97].aNumber=98;
  this->arecs[97].aName="Californium";
  this->arecs[97].aSymbol="Cf";
  this->arecs[97].aRadius=295.0;
  this->arecs[97].aMass=251.0;
  this->arecs[97].aCovRad_Slater=-1;

  this->arecs[98].aNumber=99;
  this->arecs[98].aName="Einsteinium";
  this->arecs[98].aSymbol="Es";
  this->arecs[98].aRadius=292.0;
  this->arecs[98].aMass=252.0;
  this->arecs[98].aCovRad_Slater=-1;

  this->arecs[99].aNumber=100;
  this->arecs[99].aName="Fermium";
  this->arecs[99].aSymbol="Fm";
  this->arecs[99].aRadius=290.0;
  this->arecs[99].aMass=257.0;
  this->arecs[99].aCovRad_Slater=-1;

}
