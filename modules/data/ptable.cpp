#include <data/ptable.hpp>

qpp::ptable* qpp::ptable::instance;

using namespace qpp;

void qpp::ptable::init_default(){
  assembly_ptable_0();
  assembly_ptable_1();
  assembly_ptable_2();
  assembly_ptable_3();
  assembly_ptable_4();
  assembly_ptable_5();
  assembly_ptable_6();
  assembly_ptable_7();
  assembly_ptable_8();
  assembly_ptable_9();
  init_cache_atom_idx();
}



void qpp::ptable::assembly_ptable_0() {

  this->arecs[0].m_number       = 1;
  this->arecs[0].m_name         = "Hydrogen";
  this->arecs[0].m_symbol       = "H";
  this->arecs[0].m_radius       = 0.79;
  this->arecs[0].m_mass         = 1.008;
  this->arecs[0].m_covrad_slater= 0.53; // gdis
  this->arecs[0].m_ionic_radius  = -0.38;
  this->arecs[0].m_vdw_radius    = 1.1;
  this->arecs[0].m_n_val_elec = 1;
  this->arecs[0].m_elec_conf     = {
    std::make_tuple(1, "s", 1)};
  this->arecs[0].m_color_jmol    = vector3<float>(
        1.0,
        1.0,
        1.0);
  this->arecs[0].m_color_gv      = vector3<float>(
        0.9490196078431372,
        0.9490196078431372,
        0.9490196078431372);
  this->arecs[0].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[1].m_number       = 2;
  this->arecs[1].m_name         = "Helium";
  this->arecs[1].m_symbol       = "He";
  this->arecs[1].m_radius       =  0.79;
  this->arecs[1].m_mass         = 4.002602;
  this->arecs[1].m_covrad_slater= -0.1;
  this->arecs[1].m_ionic_radius  = -0.01;
  this->arecs[1].m_vdw_radius    = 1.4000000000000001;
  this->arecs[1].m_n_val_elec = 2;
  this->arecs[1].m_elec_conf     = {
    std::make_tuple(1, "s", 2)};
  this->arecs[1].m_color_jmol    = vector3<float>(
        0.8509803921568627,
        1.0,
        1.0);
  this->arecs[1].m_color_gv      = vector3<float>(
        0.8509803921568627,
        1.0,
        1.0);
  this->arecs[1].m_color_cpk     = vector3<float>(
        1.0,
        0.7529411764705882,
        0.796078431372549);

  this->arecs[2].m_number       = 3;
  this->arecs[2].m_name         = "Lithium";
  this->arecs[2].m_symbol       = "Li";
  this->arecs[2].m_radius       = 1.55;
  this->arecs[2].m_mass         = 6.94;
  this->arecs[2].m_covrad_slater= 1.45;
  this->arecs[2].m_ionic_radius  = 0.59;
  this->arecs[2].m_vdw_radius    = 1.82;
  this->arecs[2].m_n_val_elec = 1;
  this->arecs[2].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 1)};
  this->arecs[2].m_color_jmol    = vector3<float>(
        0.8,
        0.5019607843137255,
        1.0);
  this->arecs[2].m_color_gv      = vector3<float>(
        0.8,
        0.5019607843137255,
        1.0);
  this->arecs[2].m_color_cpk     = vector3<float>(
        0.6980392156862745,
        0.13333333333333333,
        0.13333333333333333);

  this->arecs[3].m_number       = 4;
  this->arecs[3].m_name         = "Beryllium";
  this->arecs[3].m_symbol       = "Be";
  this->arecs[3].m_radius       = 1.12;
  this->arecs[3].m_mass         = 9.0121831;
  this->arecs[3].m_covrad_slater= 1.05;
  this->arecs[3].m_ionic_radius  = 0.16;
  this->arecs[3].m_vdw_radius    = 1.53;
  this->arecs[3].m_n_val_elec = 2;
  this->arecs[3].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2)};
  this->arecs[3].m_color_jmol    = vector3<float>(
        0.7607843137254902,
        1.0,
        0.0);
  this->arecs[3].m_color_gv      = vector3<float>(
        0.7607843137254902,
        1.0,
        0.0);
  this->arecs[3].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[4].m_number       = 5;
  this->arecs[4].m_name         = "Boron";
  this->arecs[4].m_symbol       = "B";
  this->arecs[4].m_radius       = 0.98;
  this->arecs[4].m_mass         = 10.81;
  this->arecs[4].m_covrad_slater= 0.85;
  this->arecs[4].m_ionic_radius  = 0.01;
  this->arecs[4].m_vdw_radius    = 1.92;
  this->arecs[4].m_n_val_elec = 3;
  this->arecs[4].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 1)};
  this->arecs[4].m_color_jmol    = vector3<float>(
        1.0,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[4].m_color_gv      = vector3<float>(
        1.0,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[4].m_color_cpk     = vector3<float>(
        0.0,
        1.0,
        0.0);

  this->arecs[5].m_number       = 6;
  this->arecs[5].m_name         = "Carbon";
  this->arecs[5].m_symbol       = "C";
  this->arecs[5].m_radius       = 0.91;
  this->arecs[5].m_mass         = 12.011;
  this->arecs[5].m_covrad_slater= 0.86; //gdis
  this->arecs[5].m_ionic_radius  = -0.08;
  this->arecs[5].m_vdw_radius    = 1.7;
  this->arecs[5].m_n_val_elec = 4;
  this->arecs[5].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 2)};
  this->arecs[5].m_color_jmol    = vector3<float>(
        0.5647058823529412,
        0.5647058823529412,
        0.5647058823529412);
  this->arecs[5].m_color_gv      = vector3<float>(
        0.3333333333333333,
        0.3333333333333333,
        0.3333333333333333);
  this->arecs[5].m_color_cpk     = vector3<float>(
        0.7843137254901961,
        0.7843137254901961,
        0.7843137254901961);

  this->arecs[6].m_number       = 7;
  this->arecs[6].m_name         = "Nitrogen";
  this->arecs[6].m_symbol       = "N";
  this->arecs[6].m_radius       = 0.92;
  this->arecs[6].m_mass         = 14.007;
  this->arecs[6].m_covrad_slater= 0.75;
  this->arecs[6].m_ionic_radius  = 1.46;
  this->arecs[6].m_vdw_radius    = 1.55;
  this->arecs[6].m_n_val_elec = 5;
  this->arecs[6].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 3)};
  this->arecs[6].m_color_jmol    = vector3<float>(
        0.18823529411764706,
        0.3137254901960784,
        0.9725490196078431);
  this->arecs[6].m_color_gv      = vector3<float>(
        0.21568627450980393,
        0.3254901960784314,
        0.7333333333333333);
  this->arecs[6].m_color_cpk     = vector3<float>(
        0.5607843137254902,
        0.5607843137254902,
        1.0);

  this->arecs[7].m_number       = 8;
  this->arecs[7].m_name         = "Oxygen";
  this->arecs[7].m_symbol       = "O";
  this->arecs[7].m_radius       = 0.92;
  this->arecs[7].m_mass         = 15.999;
  this->arecs[7].m_covrad_slater= 0.73;
  this->arecs[7].m_ionic_radius  = 1.35;
  this->arecs[7].m_vdw_radius    = 1.52;
  this->arecs[7].m_n_val_elec = 6;
  this->arecs[7].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 4)};
  this->arecs[7].m_color_jmol    = vector3<float>(
        1.0,
        0.050980392156862744,
        0.050980392156862744);
  this->arecs[7].m_color_gv      = vector3<float>(
        0.9529411764705882,
        0.1803921568627451,
        0.25882352941176473);
  this->arecs[7].m_color_cpk     = vector3<float>(
        0.9411764705882353,
        0.0,
        0.0);

  this->arecs[8].m_number       = 9;
  this->arecs[8].m_name         = "Fluorine";
  this->arecs[8].m_symbol       = "F";
  this->arecs[8].m_radius       = 0.92;
  this->arecs[8].m_mass         = 18.998403163;
  this->arecs[8].m_covrad_slater= 0.78;
  this->arecs[8].m_ionic_radius  = 1.285;
  this->arecs[8].m_vdw_radius    = 1.47;
  this->arecs[8].m_n_val_elec = 7;
  this->arecs[8].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 5)};
  this->arecs[8].m_color_jmol    = vector3<float>(
        0.5647058823529412,
        0.8784313725490196,
        0.3137254901960784);
  this->arecs[8].m_color_gv      = vector3<float>(
        0.4980392156862745,
        0.8156862745098039,
        0.23137254901960785);
  this->arecs[8].m_color_cpk     = vector3<float>(
        0.8549019607843137,
        0.6470588235294118,
        0.12549019607843137);

}

void qpp::ptable::assembly_ptable_1() {

  this->arecs[9].m_number       = 10;
  this->arecs[9].m_name         = "Neon";
  this->arecs[9].m_symbol       = "Ne";
  this->arecs[9].m_radius       = 0.92;
  this->arecs[9].m_mass         = 20.1797;
  this->arecs[9].m_covrad_slater= -0.01;
  this->arecs[9].m_ionic_radius  = -0.01;
  this->arecs[9].m_vdw_radius    = 1.54;
  this->arecs[9].m_n_val_elec = 8;
  this->arecs[9].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6)};
  this->arecs[9].m_color_jmol    = vector3<float>(
        0.7019607843137254,
        0.8901960784313725,
        0.9607843137254902);
  this->arecs[9].m_color_gv      = vector3<float>(
        0.7019607843137254,
        0.8901960784313725,
        0.9607843137254902);
  this->arecs[9].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[10].m_number       = 11;
  this->arecs[10].m_name         = "Sodium";
  this->arecs[10].m_symbol       = "Na";
  this->arecs[10].m_radius       = 1.9000000000000001;
  this->arecs[10].m_mass         = 22.98976928;
  this->arecs[10].m_covrad_slater= 1.8;
  this->arecs[10].m_ionic_radius  = 0.99;
  this->arecs[10].m_vdw_radius    = 2.27;
  this->arecs[10].m_n_val_elec = 1;
  this->arecs[10].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 1)};
  this->arecs[10].m_color_jmol    = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[10].m_color_gv      = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[10].m_color_cpk     = vector3<float>(
        0.0,
        0.0,
        1.0);

  this->arecs[11].m_number       = 12;
  this->arecs[11].m_name         = "Magnesium";
  this->arecs[11].m_symbol       = "Mg";
  this->arecs[11].m_radius       = 1.6;
  this->arecs[11].m_mass         = 24.305;
  this->arecs[11].m_covrad_slater= 1.5;
  this->arecs[11].m_ionic_radius  = 0.57;
  this->arecs[11].m_vdw_radius    = 1.73;
  this->arecs[11].m_n_val_elec = 2;
  this->arecs[11].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2)};
  this->arecs[11].m_color_jmol    = vector3<float>(
        0.5411764705882353,
        1.0,
        0.0);
  this->arecs[11].m_color_gv      = vector3<float>(
        0.5411764705882353,
        1.0,
        0.0);
  this->arecs[11].m_color_cpk     = vector3<float>(
        0.13333333333333333,
        0.5450980392156862,
        0.13333333333333333);

  this->arecs[12].m_number       = 13;
  this->arecs[12].m_name         = "Aluminum";
  this->arecs[12].m_symbol       = "Al";
  this->arecs[12].m_radius       = 1.43;
  this->arecs[12].m_mass         = 26.9815385;
  this->arecs[12].m_covrad_slater= 1.25;
  this->arecs[12].m_ionic_radius  = 0.39;
  this->arecs[12].m_vdw_radius    = 1.84;
  this->arecs[12].m_n_val_elec = 3;
  this->arecs[12].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 1)};
  this->arecs[12].m_color_jmol    = vector3<float>(
        0.7490196078431373,
        0.6509803921568628,
        0.6509803921568628);
  this->arecs[12].m_color_gv      = vector3<float>(
        0.7490196078431373,
        0.6509803921568628,
        0.6509803921568628);
  this->arecs[12].m_color_cpk     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[13].m_number       = 14;
  this->arecs[13].m_name         = "Silicon";
  this->arecs[13].m_symbol       = "Si";
  this->arecs[13].m_radius       = 1.32;
  this->arecs[13].m_mass         = 28.085;
  this->arecs[13].m_covrad_slater= 1.25;
  this->arecs[13].m_ionic_radius  = 0.26;
  this->arecs[13].m_vdw_radius    = 2.1;
  this->arecs[13].m_n_val_elec = 4;
  this->arecs[13].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 2)};
  this->arecs[13].m_color_jmol    = vector3<float>(
        0.9411764705882353,
        0.7843137254901961,
        0.6274509803921569);
  this->arecs[13].m_color_gv      = vector3<float>(
        0.9411764705882353,
        0.7843137254901961,
        0.6274509803921569);
  this->arecs[13].m_color_cpk     = vector3<float>(
        0.8549019607843137,
        0.6470588235294118,
        0.12549019607843137);

  this->arecs[14].m_number       = 15;
  this->arecs[14].m_name         = "Phosphorus";
  this->arecs[14].m_symbol       = "P";
  this->arecs[14].m_radius       = 1.28;
  this->arecs[14].m_mass         = 30.973761998;
  this->arecs[14].m_covrad_slater= 1.0;
  this->arecs[14].m_ionic_radius  = 0.44;
  this->arecs[14].m_vdw_radius    = 1.8;
  this->arecs[14].m_n_val_elec = 5;
  this->arecs[14].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 3)};
  this->arecs[14].m_color_jmol    = vector3<float>(
        1.0,
        0.5019607843137255,
        0.0);
  this->arecs[14].m_color_gv      = vector3<float>(
        1.0,
        0.5019607843137255,
        0.0);
  this->arecs[14].m_color_cpk     = vector3<float>(
        1.0,
        0.6470588235294118,
        0.0);

  this->arecs[15].m_number       = 16;
  this->arecs[15].m_name         = "Sulfur";
  this->arecs[15].m_symbol       = "S";
  this->arecs[15].m_radius       = 1.27;
  this->arecs[15].m_mass         = 32.06;
  this->arecs[15].m_covrad_slater= 1.0;
  this->arecs[15].m_ionic_radius  = 1.84;
  this->arecs[15].m_vdw_radius    = 1.8;
  this->arecs[15].m_n_val_elec = 6;
  this->arecs[15].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 4)};
  this->arecs[15].m_color_jmol    = vector3<float>(
        1.0,
        1.0,
        0.18823529411764706);
  this->arecs[15].m_color_gv      = vector3<float>(
        1.0,
        0.9607843137254902,
        0.1607843137254902);
  this->arecs[15].m_color_cpk     = vector3<float>(
        1.0,
        0.7843137254901961,
        0.19607843137254902);

  this->arecs[16].m_number       = 17;
  this->arecs[16].m_name         = "Chlorine";
  this->arecs[16].m_symbol       = "Cl";
  this->arecs[16].m_radius       = 1.27;
  this->arecs[16].m_mass         = 35.45;
  this->arecs[16].m_covrad_slater= 1.0;
  this->arecs[16].m_ionic_radius  = 1.81;
  this->arecs[16].m_vdw_radius    = 1.75;
  this->arecs[16].m_n_val_elec = 7;
  this->arecs[16].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 5)};
  this->arecs[16].m_color_jmol    = vector3<float>(
        0.12156862745098039,
        0.9411764705882353,
        0.12156862745098039);
  this->arecs[16].m_color_gv      = vector3<float>(
        0.2196078431372549,
        0.7098039215686275,
        0.2196078431372549);
  this->arecs[16].m_color_cpk     = vector3<float>(
        0.0,
        1.0,
        0.0);

  this->arecs[17].m_number       = 18;
  this->arecs[17].m_name         = "Argon";
  this->arecs[17].m_symbol       = "Ar";
  this->arecs[17].m_radius       = 1.27;
  this->arecs[17].m_mass         = 39.948;
  this->arecs[17].m_covrad_slater= -0.01;
  this->arecs[17].m_ionic_radius  = -0.01;
  this->arecs[17].m_vdw_radius    = 1.8800000000000001;
  this->arecs[17].m_n_val_elec = 8;
  this->arecs[17].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6)};
  this->arecs[17].m_color_jmol    = vector3<float>(
        0.5019607843137255,
        0.8196078431372549,
        0.8901960784313725);
  this->arecs[17].m_color_gv      = vector3<float>(
        0.5019607843137255,
        0.8196078431372549,
        0.8901960784313725);
  this->arecs[17].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[18].m_number       = 19;
  this->arecs[18].m_name         = "Potassium";
  this->arecs[18].m_symbol       = "K";
  this->arecs[18].m_radius       = 2.35;
  this->arecs[18].m_mass         = 39.0983;
  this->arecs[18].m_covrad_slater= 2.2;
  this->arecs[18].m_ionic_radius  = 1.37;
  this->arecs[18].m_vdw_radius    = 2.75;
  this->arecs[18].m_n_val_elec = 1;
  this->arecs[18].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 1)};
  this->arecs[18].m_color_jmol    = vector3<float>(
        0.5607843137254902,
        0.25098039215686274,
        0.8313725490196079);
  this->arecs[18].m_color_gv      = vector3<float>(
        0.5607843137254902,
        0.25098039215686274,
        0.8313725490196079);
  this->arecs[18].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_2() {

  this->arecs[19].m_number       = 20;
  this->arecs[19].m_name         = "Calcium";
  this->arecs[19].m_symbol       = "Ca";
  this->arecs[19].m_radius       = 1.97;
  this->arecs[19].m_mass         = 40.078;
  this->arecs[19].m_covrad_slater= 1.8;
  this->arecs[19].m_ionic_radius  = 1.0;
  this->arecs[19].m_vdw_radius    = 2.31;
  this->arecs[19].m_n_val_elec = 2;
  this->arecs[19].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2)};
  this->arecs[19].m_color_jmol    = vector3<float>(
        0.23921568627450981,
        1.0,
        0.0);
  this->arecs[19].m_color_gv      = vector3<float>(
        0.23921568627450981,
        1.0,
        0.0);
  this->arecs[19].m_color_cpk     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[20].m_number       = 21;
  this->arecs[20].m_name         = "Scandium";
  this->arecs[20].m_symbol       = "Sc";
  this->arecs[20].m_radius       = 1.62;
  this->arecs[20].m_mass         = 44.955908;
  this->arecs[20].m_covrad_slater= 1.6;
  this->arecs[20].m_ionic_radius  = 0.745;
  this->arecs[20].m_vdw_radius    = 2.15;
  this->arecs[20].m_n_val_elec = 3;
  this->arecs[20].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 1),
    std::make_tuple(4, "s", 2)};
  this->arecs[20].m_color_jmol    = vector3<float>(
        0.9019607843137255,
        0.9019607843137255,
        0.9019607843137255);
  this->arecs[20].m_color_gv      = vector3<float>(
        0.9019607843137255,
        0.9019607843137255,
        0.9019607843137255);
  this->arecs[20].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[21].m_number       = 22;
  this->arecs[21].m_name         = "Titanium";
  this->arecs[21].m_symbol       = "Ti";
  this->arecs[21].m_radius       = 1.47;
  this->arecs[21].m_mass         = 47.867;
  this->arecs[21].m_covrad_slater= 1.4000000000000001;
  this->arecs[21].m_ionic_radius  = 0.86;
  this->arecs[21].m_vdw_radius    = 2.11;
  this->arecs[21].m_n_val_elec = 4;
  this->arecs[21].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 2),
    std::make_tuple(4, "s", 2)};
  this->arecs[21].m_color_jmol    = vector3<float>(
        0.7490196078431373,
        0.7607843137254902,
        0.7803921568627451);
  this->arecs[21].m_color_gv      = vector3<float>(
        0.7490196078431373,
        0.7607843137254902,
        0.7803921568627451);
  this->arecs[21].m_color_cpk     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[22].m_number       = 23;
  this->arecs[22].m_name         = "Vanadium";
  this->arecs[22].m_symbol       = "V";
  this->arecs[22].m_radius       = 1.34;
  this->arecs[22].m_mass         = 50.9415;
  this->arecs[22].m_covrad_slater= 1.35;
  this->arecs[22].m_ionic_radius  = 0.79;
  this->arecs[22].m_vdw_radius    = 2.07;
  this->arecs[22].m_n_val_elec = 5;
  this->arecs[22].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 3),
    std::make_tuple(4, "s", 2)};
  this->arecs[22].m_color_jmol    = vector3<float>(
        0.6509803921568628,
        0.6509803921568628,
        0.6705882352941176);
  this->arecs[22].m_color_gv      = vector3<float>(
        0.6509803921568628,
        0.6509803921568628,
        0.6705882352941176);
  this->arecs[22].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[23].m_number       = 24;
  this->arecs[23].m_name         = "Chromium";
  this->arecs[23].m_symbol       = "Cr";
  this->arecs[23].m_radius       = 1.3;
  this->arecs[23].m_mass         = 51.9961;
  this->arecs[23].m_covrad_slater= 1.4000000000000001;
  this->arecs[23].m_ionic_radius  = 0.73;
  this->arecs[23].m_vdw_radius    = 2.06;
  this->arecs[23].m_n_val_elec = 6;
  this->arecs[23].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 5),
    std::make_tuple(4, "s", 1)};
  this->arecs[23].m_color_jmol    = vector3<float>(
        0.5411764705882353,
        0.6,
        0.7803921568627451);
  this->arecs[23].m_color_gv      = vector3<float>(
        0.5411764705882353,
        0.6,
        0.7803921568627451);
  this->arecs[23].m_color_cpk     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[24].m_number       = 25;
  this->arecs[24].m_name         = "Manganese";
  this->arecs[24].m_symbol       = "Mn";
  this->arecs[24].m_radius       = 1.35;
  this->arecs[24].m_mass         = 54.938044;
  this->arecs[24].m_covrad_slater= 1.4000000000000001;
  this->arecs[24].m_ionic_radius  = 0.66;
  this->arecs[24].m_vdw_radius    = 2.05;
  this->arecs[24].m_n_val_elec = 7;
  this->arecs[24].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 5),
    std::make_tuple(4, "s", 2)};
  this->arecs[24].m_color_jmol    = vector3<float>(
        0.611764705882353,
        0.47843137254901963,
        0.7803921568627451);
  this->arecs[24].m_color_gv      = vector3<float>(
        0.611764705882353,
        0.47843137254901963,
        0.7803921568627451);
  this->arecs[24].m_color_cpk     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[25].m_number       = 26;
  this->arecs[25].m_name         = "Iron";
  this->arecs[25].m_symbol       = "Fe";
  this->arecs[25].m_radius       = 1.26;
  this->arecs[25].m_mass         = 55.845;
  this->arecs[25].m_covrad_slater= 1.4000000000000001;
  this->arecs[25].m_ionic_radius  = 0.63;
  this->arecs[25].m_vdw_radius    = 2.04;
  this->arecs[25].m_n_val_elec = 8;
  this->arecs[25].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 6),
    std::make_tuple(4, "s", 2)};
  this->arecs[25].m_color_jmol    = vector3<float>(
        0.8784313725490196,
        0.4,
        0.2);
  this->arecs[25].m_color_gv      = vector3<float>(
        0.8784313725490196,
        0.4,
        0.2);
  this->arecs[25].m_color_cpk     = vector3<float>(
        1.0,
        0.6470588235294118,
        0.0);

  this->arecs[26].m_number       = 27;
  this->arecs[26].m_name         = "Cobalt";
  this->arecs[26].m_symbol       = "Co";
  this->arecs[26].m_radius       = 1.25;
  this->arecs[26].m_mass         = 58.933194;
  this->arecs[26].m_covrad_slater= 1.35;
  this->arecs[26].m_ionic_radius  = 0.58;
  this->arecs[26].m_vdw_radius    = 2.0;
  this->arecs[26].m_n_val_elec = 9;
  this->arecs[26].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 7),
    std::make_tuple(4, "s", 2)};
  this->arecs[26].m_color_jmol    = vector3<float>(
        0.9411764705882353,
        0.5647058823529412,
        0.6274509803921569);
  this->arecs[26].m_color_gv      = vector3<float>(
        0.9411764705882353,
        0.5647058823529412,
        0.6274509803921569);
  this->arecs[26].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[27].m_number       = 28;
  this->arecs[27].m_name         = "Nickel";
  this->arecs[27].m_symbol       = "Ni";
  this->arecs[27].m_radius       = 1.24;
  this->arecs[27].m_mass         = 58.6934;
  this->arecs[27].m_covrad_slater= 1.35;
  this->arecs[27].m_ionic_radius  = 0.55;
  this->arecs[27].m_vdw_radius    = 1.97;
  this->arecs[27].m_n_val_elec = 10;
  this->arecs[27].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 8),
    std::make_tuple(4, "s", 2)};
  this->arecs[27].m_color_jmol    = vector3<float>(
        0.3137254901960784,
        0.8156862745098039,
        0.3137254901960784);
  this->arecs[27].m_color_gv      = vector3<float>(
        0.3137254901960784,
        0.8156862745098039,
        0.3137254901960784);
  this->arecs[27].m_color_cpk     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

  this->arecs[28].m_number       = 29;
  this->arecs[28].m_name         = "Copper";
  this->arecs[28].m_symbol       = "Cu";
  this->arecs[28].m_radius       = 1.28;
  this->arecs[28].m_mass         = 63.546;
  this->arecs[28].m_covrad_slater= 1.35;
  this->arecs[28].m_ionic_radius  = 0.46;
  this->arecs[28].m_vdw_radius    = 1.96;
  this->arecs[28].m_n_val_elec = 11;
  this->arecs[28].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 1)};
  this->arecs[28].m_color_jmol    = vector3<float>(
        0.7843137254901961,
        0.5019607843137255,
        0.2);
  this->arecs[28].m_color_gv      = vector3<float>(
        0.7843137254901961,
        0.5019607843137255,
        0.2);
  this->arecs[28].m_color_cpk     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

}

void qpp::ptable::assembly_ptable_3() {

  this->arecs[29].m_number       = 30;
  this->arecs[29].m_name         = "Zinc";
  this->arecs[29].m_symbol       = "Zn";
  this->arecs[29].m_radius       = 1.3800000000000001;
  this->arecs[29].m_mass         = 65.38;
  this->arecs[29].m_covrad_slater= 1.35;
  this->arecs[29].m_ionic_radius  = 0.6;
  this->arecs[29].m_vdw_radius    = 2.01;
  this->arecs[29].m_n_val_elec = 12;
  this->arecs[29].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2)};
  this->arecs[29].m_color_jmol    = vector3<float>(
        0.49019607843137253,
        0.5019607843137255,
        0.6901960784313725);
  this->arecs[29].m_color_gv      = vector3<float>(
        0.49019607843137253,
        0.5019607843137255,
        0.6901960784313725);
  this->arecs[29].m_color_cpk     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

  this->arecs[30].m_number       = 31;
  this->arecs[30].m_name         = "Gallium";
  this->arecs[30].m_symbol       = "Ga";
  this->arecs[30].m_radius       = 1.41;
  this->arecs[30].m_mass         = 69.723;
  this->arecs[30].m_covrad_slater= 1.3;
  this->arecs[30].m_ionic_radius  = 0.47000000000000003;
  this->arecs[30].m_vdw_radius    = 1.87;
  this->arecs[30].m_n_val_elec = 3;
  this->arecs[30].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 1)};
  this->arecs[30].m_color_jmol    = vector3<float>(
        0.7607843137254902,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[30].m_color_gv      = vector3<float>(
        0.7607843137254902,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[30].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[31].m_number       = 32;
  this->arecs[31].m_name         = "Germanium";
  this->arecs[31].m_symbol       = "Ge";
  this->arecs[31].m_radius       = 1.37;
  this->arecs[31].m_mass         = 72.63;
  this->arecs[31].m_covrad_slater= 1.25;
  this->arecs[31].m_ionic_radius  = 0.73;
  this->arecs[31].m_vdw_radius    = 2.11;
  this->arecs[31].m_n_val_elec = 4;
  this->arecs[31].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 2)};
  this->arecs[31].m_color_jmol    = vector3<float>(
        0.4,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[31].m_color_gv      = vector3<float>(
        0.4,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[31].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[32].m_number       = 33;
  this->arecs[32].m_name         = "Arsenic";
  this->arecs[32].m_symbol       = "As";
  this->arecs[32].m_radius       = 1.3900000000000001;
  this->arecs[32].m_mass         = 74.921595;
  this->arecs[32].m_covrad_slater= 1.15;
  this->arecs[32].m_ionic_radius  = 0.58;
  this->arecs[32].m_vdw_radius    = 1.85;
  this->arecs[32].m_n_val_elec = 5;
  this->arecs[32].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 3)};
  this->arecs[32].m_color_jmol    = vector3<float>(
        0.7411764705882353,
        0.5019607843137255,
        0.8901960784313725);
  this->arecs[32].m_color_gv      = vector3<float>(
        0.7411764705882353,
        0.5019607843137255,
        0.8901960784313725);
  this->arecs[32].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[33].m_number       = 34;
  this->arecs[33].m_name         = "Selenium";
  this->arecs[33].m_symbol       = "Se";
  this->arecs[33].m_radius       = 1.4000000000000001;
  this->arecs[33].m_mass         = 78.971;
  this->arecs[33].m_covrad_slater= 1.22;
  this->arecs[33].m_ionic_radius  = 1.98;
  this->arecs[33].m_vdw_radius    = 1.9000000000000001;
  this->arecs[33].m_n_val_elec = 6;
  this->arecs[33].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 4)};
  this->arecs[33].m_color_jmol    = vector3<float>(
        1.0,
        0.6313725490196078,
        0.0);
  this->arecs[33].m_color_gv      = vector3<float>(
        1.0,
        0.6313725490196078,
        0.0);
  this->arecs[33].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[34].m_number       = 35;
  this->arecs[34].m_name         = "Bromine";
  this->arecs[34].m_symbol       = "Br";
  this->arecs[34].m_radius       = 1.4000;
  this->arecs[34].m_mass         = 79.904;
  this->arecs[34].m_covrad_slater= 1.31;
  this->arecs[34].m_ionic_radius  = 1.96;
  this->arecs[34].m_vdw_radius    = 1.85;
  this->arecs[34].m_n_val_elec = 7;
  this->arecs[34].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 5)};
  this->arecs[34].m_color_jmol    = vector3<float>(
        0.6509803921568628,
        0.1607843137254902,
        0.1607843137254902);
  this->arecs[34].m_color_gv      = vector3<float>(
        0.6509803921568628,
        0.1607843137254902,
        0.1607843137254902);
  this->arecs[34].m_color_cpk     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

  this->arecs[35].m_number       = 36;
  this->arecs[35].m_name         = "Krypton";
  this->arecs[35].m_symbol       = "Kr";
  this->arecs[35].m_radius       = 1.4000;
  this->arecs[35].m_mass         = 83.798;
  this->arecs[35].m_covrad_slater= -0.01;
  this->arecs[35].m_ionic_radius  = -0.01;
  this->arecs[35].m_vdw_radius    = 2.02;
  this->arecs[35].m_n_val_elec = 8;
  this->arecs[35].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 6)};
  this->arecs[35].m_color_jmol    = vector3<float>(
        0.3607843137254902,
        0.7215686274509804,
        0.8196078431372549);
  this->arecs[35].m_color_gv      = vector3<float>(
        0.3607843137254902,
        0.7215686274509804,
        0.8196078431372549);
  this->arecs[35].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[36].m_number       = 37;
  this->arecs[36].m_name         = "Rubidium";
  this->arecs[36].m_symbol       = "Rb";
  this->arecs[36].m_radius       = 2.48;
  this->arecs[36].m_mass         = 85.4678;
  this->arecs[36].m_covrad_slater= 2.35;
  this->arecs[36].m_ionic_radius  = 1.52;
  this->arecs[36].m_vdw_radius    = 3.0300000000000002;
  this->arecs[36].m_n_val_elec = 1;
  this->arecs[36].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 1)};
  this->arecs[36].m_color_jmol    = vector3<float>(
        0.4392156862745098,
        0.1803921568627451,
        0.6901960784313725);
  this->arecs[36].m_color_gv      = vector3<float>(
        0.4392156862745098,
        0.1803921568627451,
        0.6901960784313725);
  this->arecs[36].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[37].m_number       = 38;
  this->arecs[37].m_name         = "Strontium";
  this->arecs[37].m_symbol       = "Sr";
  this->arecs[37].m_radius       = 2.15;
  this->arecs[37].m_mass         = 87.62;
  this->arecs[37].m_covrad_slater= 2.0;
  this->arecs[37].m_ionic_radius  = 1.18;
  this->arecs[37].m_vdw_radius    = 2.49;
  this->arecs[37].m_n_val_elec = 2;
  this->arecs[37].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2)};
  this->arecs[37].m_color_jmol    = vector3<float>(
        0.0,
        1.0,
        0.0);
  this->arecs[37].m_color_gv      = vector3<float>(
        0.0,
        1.0,
        0.0);
  this->arecs[37].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[38].m_number       = 39;
  this->arecs[38].m_name         = "Yttrium";
  this->arecs[38].m_symbol       = "Y";
  this->arecs[38].m_radius       = 1.78;
  this->arecs[38].m_mass         = 88.90584;
  this->arecs[38].m_covrad_slater= 1.8;
  this->arecs[38].m_ionic_radius  = 0.9;
  this->arecs[38].m_vdw_radius    = 2.32;
  this->arecs[38].m_n_val_elec = 3;
  this->arecs[38].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 1),
    std::make_tuple(5, "s", 2)};
  this->arecs[38].m_color_jmol    = vector3<float>(
        0.5803921568627451,
        1.0,
        1.0);
  this->arecs[38].m_color_gv      = vector3<float>(
        0.5803921568627451,
        1.0,
        1.0);
  this->arecs[38].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_4() {

  this->arecs[39].m_number       = 40;
  this->arecs[39].m_name         = "Zirconium";
  this->arecs[39].m_symbol       = "Zr";
  this->arecs[39].m_radius       = 1.6;
  this->arecs[39].m_mass         = 91.224;
  this->arecs[39].m_covrad_slater= 1.55;
  this->arecs[39].m_ionic_radius  = 0.59;
  this->arecs[39].m_vdw_radius    = 2.23;
  this->arecs[39].m_n_val_elec = 4;
  this->arecs[39].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 2),
    std::make_tuple(5, "s", 2)};
  this->arecs[39].m_color_jmol    = vector3<float>(
        0.5803921568627451,
        0.8784313725490196,
        0.8784313725490196);
  this->arecs[39].m_color_gv      = vector3<float>(
        0.5803921568627451,
        0.8784313725490196,
        0.8784313725490196);
  this->arecs[39].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[40].m_number       = 41;
  this->arecs[40].m_name         = "Niobium";
  this->arecs[40].m_symbol       = "Nb";
  this->arecs[40].m_radius       = 1.46;
  this->arecs[40].m_mass         = 92.90637;
  this->arecs[40].m_covrad_slater= 1.45;
  this->arecs[40].m_ionic_radius  = 0.72;
  this->arecs[40].m_vdw_radius    = 2.18;
  this->arecs[40].m_n_val_elec = 5;
  this->arecs[40].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 4),
    std::make_tuple(5, "s", 1)};
  this->arecs[40].m_color_jmol    = vector3<float>(
        0.45098039215686275,
        0.7607843137254902,
        0.788235294117647);
  this->arecs[40].m_color_gv      = vector3<float>(
        0.45098039215686275,
        0.7607843137254902,
        0.788235294117647);
  this->arecs[40].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[41].m_number       = 42;
  this->arecs[41].m_name         = "Molybdenum";
  this->arecs[41].m_symbol       = "Mo";
  this->arecs[41].m_radius       = 1.3900000000000001;
  this->arecs[41].m_mass         = 95.95;
  this->arecs[41].m_covrad_slater= 1.45;
  this->arecs[41].m_ionic_radius  = 0.6900000000000001;
  this->arecs[41].m_vdw_radius    = 2.17;
  this->arecs[41].m_n_val_elec = 6;
  this->arecs[41].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 5),
    std::make_tuple(5, "s", 1)};
  this->arecs[41].m_color_jmol    = vector3<float>(
        0.32941176470588235,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[41].m_color_gv      = vector3<float>(
        0.32941176470588235,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[41].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[42].m_number       = 43;
  this->arecs[42].m_name         = "Technetium";
  this->arecs[42].m_symbol       = "Tc";
  this->arecs[42].m_radius       = 1.36;
  this->arecs[42].m_mass         = 97.90721;
  this->arecs[42].m_covrad_slater= 1.35;
  this->arecs[42].m_ionic_radius  = 0.645;
  this->arecs[42].m_vdw_radius    = 2.16;
  this->arecs[42].m_n_val_elec = 7;
  this->arecs[42].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 5),
    std::make_tuple(5, "s", 2)};
  this->arecs[42].m_color_jmol    = vector3<float>(
        0.23137254901960785,
        0.6196078431372549,
        0.6196078431372549);
  this->arecs[42].m_color_gv      = vector3<float>(
        0.23137254901960785,
        0.6196078431372549,
        0.6196078431372549);
  this->arecs[42].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[43].m_number       = 44;
  this->arecs[43].m_name         = "Ruthenium";
  this->arecs[43].m_symbol       = "Ru";
  this->arecs[43].m_radius       = 1.34;
  this->arecs[43].m_mass         = 101.07;
  this->arecs[43].m_covrad_slater= 1.3;
  this->arecs[43].m_ionic_radius  = 0.68;
  this->arecs[43].m_vdw_radius    = 2.13;
  this->arecs[43].m_n_val_elec = 8;
  this->arecs[43].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 7),
    std::make_tuple(5, "s", 1)};
  this->arecs[43].m_color_jmol    = vector3<float>(
        0.1411764705882353,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[43].m_color_gv      = vector3<float>(
        0.1411764705882353,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[43].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[44].m_number       = 45;
  this->arecs[44].m_name         = "Rhodium";
  this->arecs[44].m_symbol       = "Rh";
  this->arecs[44].m_radius       = 1.34;
  this->arecs[44].m_mass         = 102.9055;
  this->arecs[44].m_covrad_slater= 1.35;
  this->arecs[44].m_ionic_radius  = 0.665;
  this->arecs[44].m_vdw_radius    = 2.1;
  this->arecs[44].m_n_val_elec = 9;
  this->arecs[44].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 8),
    std::make_tuple(5, "s", 1)};
  this->arecs[44].m_color_jmol    = vector3<float>(
        0.0392156862745098,
        0.49019607843137253,
        0.5490196078431373);
  this->arecs[44].m_color_gv      = vector3<float>(
        0.0392156862745098,
        0.49019607843137253,
        0.5490196078431373);
  this->arecs[44].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[45].m_number       = 46;
  this->arecs[45].m_name         = "Palladium";
  this->arecs[45].m_symbol       = "Pd";
  this->arecs[45].m_radius       = 1.37;
  this->arecs[45].m_mass         = 106.42;
  this->arecs[45].m_covrad_slater= 1.4000000000000001;
  this->arecs[45].m_ionic_radius  = 0.59;
  this->arecs[45].m_vdw_radius    = 2.1;
  this->arecs[45].m_n_val_elec = 12;
  this->arecs[45].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10)};
  this->arecs[45].m_color_jmol    = vector3<float>(
        0.0,
        0.4117647058823529,
        0.5215686274509804);
  this->arecs[45].m_color_gv      = vector3<float>(
        0.0,
        0.4117647058823529,
        0.5215686274509804);
  this->arecs[45].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[46].m_number       = 47;
  this->arecs[46].m_name         = "Silver";
  this->arecs[46].m_symbol       = "Ag";
  this->arecs[46].m_radius       = 1.44;
  this->arecs[46].m_mass         = 107.8682;
  this->arecs[46].m_covrad_slater= 1.6;
  this->arecs[46].m_ionic_radius  = 0.67;
  this->arecs[46].m_vdw_radius    = 2.11;
  this->arecs[46].m_n_val_elec = 11;
  this->arecs[46].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 1)};
  this->arecs[46].m_color_jmol    = vector3<float>(
        0.7529411764705882,
        0.7529411764705882,
        0.7529411764705882);
  this->arecs[46].m_color_gv      = vector3<float>(
        0.7529411764705882,
        0.7529411764705882,
        0.7529411764705882);
  this->arecs[46].m_color_cpk     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[47].m_number       = 48;
  this->arecs[47].m_name         = "Cadmium";
  this->arecs[47].m_symbol       = "Cd";
  this->arecs[47].m_radius       = 1.54;
  this->arecs[47].m_mass         = 112.414;
  this->arecs[47].m_covrad_slater= 1.69;
  this->arecs[47].m_ionic_radius  = 0.78;
  this->arecs[47].m_vdw_radius    = 2.18;
  this->arecs[47].m_n_val_elec = 12;
  this->arecs[47].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2)};
  this->arecs[47].m_color_jmol    = vector3<float>(
        1.0,
        0.8509803921568627,
        0.5607843137254902);
  this->arecs[47].m_color_gv      = vector3<float>(
        1.0,
        0.8509803921568627,
        0.5607843137254902);
  this->arecs[47].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[48].m_number       = 49;
  this->arecs[48].m_name         = "Indium";
  this->arecs[48].m_symbol       = "In";
  this->arecs[48].m_radius       = 1.6600000000000001;
  this->arecs[48].m_mass         = 114.818;
  this->arecs[48].m_covrad_slater= 1.55;
  this->arecs[48].m_ionic_radius  = 0.62;
  this->arecs[48].m_vdw_radius    = 1.93;
  this->arecs[48].m_n_val_elec = 3;
  this->arecs[48].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2),
    std::make_tuple(5, "p", 1)};
  this->arecs[48].m_color_jmol    = vector3<float>(
        0.6509803921568628,
        0.4588235294117647,
        0.45098039215686275);
  this->arecs[48].m_color_gv      = vector3<float>(
        0.6509803921568628,
        0.4588235294117647,
        0.45098039215686275);
  this->arecs[48].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_5() {

  this->arecs[49].m_number       = 50;
  this->arecs[49].m_name         = "Tin";
  this->arecs[49].m_symbol       = "Sn";
  this->arecs[49].m_radius       = 1.62;
  this->arecs[49].m_mass         = 118.71;
  this->arecs[49].m_covrad_slater= 1.45;
  this->arecs[49].m_ionic_radius  = 0.55;
  this->arecs[49].m_vdw_radius    = 2.17;
  this->arecs[49].m_n_val_elec = 4;
  this->arecs[49].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2),
    std::make_tuple(5, "p", 2)};
  this->arecs[49].m_color_jmol    = vector3<float>(
        0.4,
        0.5019607843137255,
        0.5019607843137255);
  this->arecs[49].m_color_gv      = vector3<float>(
        0.4,
        0.5019607843137255,
        0.5019607843137255);
  this->arecs[49].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[50].m_number       = 51;
  this->arecs[50].m_name         = "Antimony";
  this->arecs[50].m_symbol       = "Sb";
  this->arecs[50].m_radius       = 1.59;
  this->arecs[50].m_mass         = 121.76;
  this->arecs[50].m_covrad_slater= 1.45;
  this->arecs[50].m_ionic_radius  = 0.76;
  this->arecs[50].m_vdw_radius    = 2.06;
  this->arecs[50].m_n_val_elec = 5;
  this->arecs[50].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2),
    std::make_tuple(5, "p", 3)};
  this->arecs[50].m_color_jmol    = vector3<float>(
        0.6196078431372549,
        0.38823529411764707,
        0.7098039215686275);
  this->arecs[50].m_color_gv      = vector3<float>(
        0.6196078431372549,
        0.38823529411764707,
        0.7098039215686275);
  this->arecs[50].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[51].m_number       = 52;
  this->arecs[51].m_name         = "Tellurium";
  this->arecs[51].m_symbol       = "Te";
  this->arecs[51].m_radius       = 1.6;
  this->arecs[51].m_mass         = 127.6;
  this->arecs[51].m_covrad_slater= 1.4000000000000001;
  this->arecs[51].m_ionic_radius  = 2.21;
  this->arecs[51].m_vdw_radius    = 2.06;
  this->arecs[51].m_n_val_elec = 6;
  this->arecs[51].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2),
    std::make_tuple(5, "p", 4)};
  this->arecs[51].m_color_jmol    = vector3<float>(
        0.8313725490196079,
        0.47843137254901963,
        0.0);
  this->arecs[51].m_color_gv      = vector3<float>(
        0.8313725490196079,
        0.47843137254901963,
        0.0);
  this->arecs[51].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[52].m_number       = 53;
  this->arecs[52].m_name         = "Iodine";
  this->arecs[52].m_symbol       = "I";
  this->arecs[52].m_radius       = 1.6;
  this->arecs[52].m_mass         = 126.90447;
  this->arecs[52].m_covrad_slater= 1.7;
  this->arecs[52].m_ionic_radius  = 2.2;
  this->arecs[52].m_vdw_radius    = 1.98;
  this->arecs[52].m_n_val_elec = 7;
  this->arecs[52].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2),
    std::make_tuple(5, "p", 5)};
  this->arecs[52].m_color_jmol    = vector3<float>(
        0.5803921568627451,
        0.0,
        0.5803921568627451);
  this->arecs[52].m_color_gv      = vector3<float>(
        0.5803921568627451,
        0.0,
        0.5803921568627451);
  this->arecs[52].m_color_cpk     = vector3<float>(
        0.6274509803921569,
        0.12549019607843137,
        0.9411764705882353);

  this->arecs[53].m_number       = 54;
  this->arecs[53].m_name         = "Xenon";
  this->arecs[53].m_symbol       = "Xe";
  this->arecs[53].m_radius       = -0.01;
  this->arecs[53].m_mass         = 131.293;
  this->arecs[53].m_covrad_slater= -0.01;
  this->arecs[53].m_ionic_radius  = 0.4;
  this->arecs[53].m_vdw_radius    = 2.16;
  this->arecs[53].m_n_val_elec = 8;
  this->arecs[53].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "s", 2),
    std::make_tuple(5, "p", 6)};
  this->arecs[53].m_color_jmol    = vector3<float>(
        0.25882352941176473,
        0.6196078431372549,
        0.6901960784313725);
  this->arecs[53].m_color_gv      = vector3<float>(
        0.25882352941176473,
        0.6196078431372549,
        0.6901960784313725);
  this->arecs[53].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[54].m_number       = 55;
  this->arecs[54].m_name         = "Cesium";
  this->arecs[54].m_symbol       = "Cs";
  this->arecs[54].m_radius       = 2.67;
  this->arecs[54].m_mass         = 132.90545196;
  this->arecs[54].m_covrad_slater= 2.6;
  this->arecs[54].m_ionic_radius  = 1.67;
  this->arecs[54].m_vdw_radius    = 3.43;
  this->arecs[54].m_n_val_elec = 1;
  this->arecs[54].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 1)};
  this->arecs[54].m_color_jmol    = vector3<float>(
        0.3411764705882353,
        0.09019607843137255,
        0.5607843137254902);
  this->arecs[54].m_color_gv      = vector3<float>(
        0.3411764705882353,
        0.09019607843137255,
        0.5607843137254902);
  this->arecs[54].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[55].m_number       = 56;
  this->arecs[55].m_name         = "Barium";
  this->arecs[55].m_symbol       = "Ba";
  this->arecs[55].m_radius       = 2.22;
  this->arecs[55].m_mass         = 137.327;
  this->arecs[55].m_covrad_slater= 2.15;
  this->arecs[55].m_ionic_radius  = 1.35;
  this->arecs[55].m_vdw_radius    = 2.68;
  this->arecs[55].m_n_val_elec = 2;
  this->arecs[55].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2)};
  this->arecs[55].m_color_jmol    = vector3<float>(
        0.0,
        0.788235294117647,
        0.0);
  this->arecs[55].m_color_gv      = vector3<float>(
        0.0,
        0.788235294117647,
        0.0);
  this->arecs[55].m_color_cpk     = vector3<float>(
        1.0,
        0.6470588235294118,
        0.0);

  this->arecs[56].m_number       = 57;
  this->arecs[56].m_name         = "Lanthanum";
  this->arecs[56].m_symbol       = "La";
  this->arecs[56].m_radius       = 1.87;
  this->arecs[56].m_mass         = 138.90547;
  this->arecs[56].m_covrad_slater= 2.05;
  this->arecs[56].m_ionic_radius  = 1.032;
  this->arecs[56].m_vdw_radius    = 2.43;
  this->arecs[56].m_n_val_elec = 2;
  this->arecs[56].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(5, "d", 1),
    std::make_tuple(6, "s", 2)};
  this->arecs[56].m_color_jmol    = vector3<float>(
        0.4392156862745098,
        0.8313725490196079,
        1.0);
  this->arecs[56].m_color_gv      = vector3<float>(
        0.4392156862745098,
        0.8313725490196079,
        1.0);
  this->arecs[56].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[57].m_number       = 58;
  this->arecs[57].m_name         = "Cerium";
  this->arecs[57].m_symbol       = "Ce";
  this->arecs[57].m_radius       = 1.81;
  this->arecs[57].m_mass         = 140.116;
  this->arecs[57].m_covrad_slater= 1.85;
  this->arecs[57].m_ionic_radius  = 1.01;
  this->arecs[57].m_vdw_radius    = 2.42;
  this->arecs[57].m_n_val_elec = 2;
  this->arecs[57].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 1),
    std::make_tuple(5, "d", 1),
    std::make_tuple(6, "s", 2)};
  this->arecs[57].m_color_jmol    = vector3<float>(
        1.0,
        1.0,
        0.7803921568627451);
  this->arecs[57].m_color_gv      = vector3<float>(
        1.0,
        1.0,
        0.7803921568627451);
  this->arecs[57].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[58].m_number       = 59;
  this->arecs[58].m_name         = "Praseodymium";
  this->arecs[58].m_symbol       = "Pr";
  this->arecs[58].m_radius       = 1.82;
  this->arecs[58].m_mass         = 140.90766;
  this->arecs[58].m_covrad_slater= 1.85;
  this->arecs[58].m_ionic_radius  = 0.99;
  this->arecs[58].m_vdw_radius    = 2.4;
  this->arecs[58].m_n_val_elec = 2;
  this->arecs[58].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 3),
    std::make_tuple(6, "s", 2)};
  this->arecs[58].m_color_jmol    = vector3<float>(
        0.8509803921568627,
        1.0,
        0.7803921568627451);
  this->arecs[58].m_color_gv      = vector3<float>(
        0.8509803921568627,
        1.0,
        0.7803921568627451);
  this->arecs[58].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_6() {

  this->arecs[59].m_number       = 60;
  this->arecs[59].m_name         = "Neodymium";
  this->arecs[59].m_symbol       = "Nd";
  this->arecs[59].m_radius       = 1.82;
  this->arecs[59].m_mass         = 144.242;
  this->arecs[59].m_covrad_slater= 1.85;
  this->arecs[59].m_ionic_radius  = 1.29;
  this->arecs[59].m_vdw_radius    = 2.39;
  this->arecs[59].m_n_val_elec = 2;
  this->arecs[59].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 4),
    std::make_tuple(6, "s", 2)};
  this->arecs[59].m_color_jmol    = vector3<float>(
        0.7803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[59].m_color_gv      = vector3<float>(
        0.7803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[59].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[60].m_number       = 61;
  this->arecs[60].m_name         = "Promethium";
  this->arecs[60].m_symbol       = "Pm";
  this->arecs[60].m_radius       = -0.01;
  this->arecs[60].m_mass         = 144.91276;
  this->arecs[60].m_covrad_slater= 1.85;
  this->arecs[60].m_ionic_radius  = 0.97;
  this->arecs[60].m_vdw_radius    = 2.38;
  this->arecs[60].m_n_val_elec = 2;
  this->arecs[60].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 5),
    std::make_tuple(6, "s", 2)};
  this->arecs[60].m_color_jmol    = vector3<float>(
        0.6392156862745098,
        1.0,
        0.7803921568627451);
  this->arecs[60].m_color_gv      = vector3<float>(
        0.6392156862745098,
        1.0,
        0.7803921568627451);
  this->arecs[60].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[61].m_number       = 62;
  this->arecs[61].m_name         = "Samarium";
  this->arecs[61].m_symbol       = "Sm";
  this->arecs[61].m_radius       = 1.81;
  this->arecs[61].m_mass         = 150.36;
  this->arecs[61].m_covrad_slater= 1.85;
  this->arecs[61].m_ionic_radius  = 1.22;
  this->arecs[61].m_vdw_radius    = 2.36;
  this->arecs[61].m_n_val_elec = 2;
  this->arecs[61].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 6),
    std::make_tuple(6, "s", 2)};
  this->arecs[61].m_color_jmol    = vector3<float>(
        0.5607843137254902,
        1.0,
        0.7803921568627451);
  this->arecs[61].m_color_gv      = vector3<float>(
        0.5607843137254902,
        1.0,
        0.7803921568627451);
  this->arecs[61].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[62].m_number       = 63;
  this->arecs[62].m_name         = "Europium";
  this->arecs[62].m_symbol       = "Eu";
  this->arecs[62].m_radius       = 1.99;
  this->arecs[62].m_mass         = 151.964;
  this->arecs[62].m_covrad_slater= 1.85;
  this->arecs[62].m_ionic_radius  = 1.17;
  this->arecs[62].m_vdw_radius    = 2.35;
  this->arecs[62].m_n_val_elec = 2;
  this->arecs[62].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 7),
    std::make_tuple(6, "s", 2)};
  this->arecs[62].m_color_jmol    = vector3<float>(
        0.3803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[62].m_color_gv      = vector3<float>(
        0.3803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[62].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[63].m_number       = 64;
  this->arecs[63].m_name         = "Gadolinium";
  this->arecs[63].m_symbol       = "Gd";
  this->arecs[63].m_radius       = 1.79;
  this->arecs[63].m_mass         = 157.25;
  this->arecs[63].m_covrad_slater= 1.8;
  this->arecs[63].m_ionic_radius  = 0.938;
  this->arecs[63].m_vdw_radius    = 2.34;
  this->arecs[63].m_n_val_elec = 2;
  this->arecs[63].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 7),
    std::make_tuple(5, "d", 1),
    std::make_tuple(6, "s", 2)};
  this->arecs[63].m_color_jmol    = vector3<float>(
        0.27058823529411763,
        1.0,
        0.7803921568627451);
  this->arecs[63].m_color_gv      = vector3<float>(
        0.27058823529411763,
        1.0,
        0.7803921568627451);
  this->arecs[63].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[64].m_number       = 65;
  this->arecs[64].m_name         = "Terbium";
  this->arecs[64].m_symbol       = "Tb";
  this->arecs[64].m_radius       = 1.8;
  this->arecs[64].m_mass         = 158.92535;
  this->arecs[64].m_covrad_slater= 1.75;
  this->arecs[64].m_ionic_radius  = 0.9230000000000002;
  this->arecs[64].m_vdw_radius    = 2.33;
  this->arecs[64].m_n_val_elec = 2;
  this->arecs[64].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 9),
    std::make_tuple(6, "s", 2)};
  this->arecs[64].m_color_jmol    = vector3<float>(
        0.18823529411764706,
        1.0,
        0.7803921568627451);
  this->arecs[64].m_color_gv      = vector3<float>(
        0.18823529411764706,
        1.0,
        0.7803921568627451);
  this->arecs[64].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[65].m_number       = 66;
  this->arecs[65].m_name         = "Dysprosium";
  this->arecs[65].m_symbol       = "Dy";
  this->arecs[65].m_radius       = 1.8;
  this->arecs[65].m_mass         = 162.5;
  this->arecs[65].m_covrad_slater= 1.75;
  this->arecs[65].m_ionic_radius  = 1.07;
  this->arecs[65].m_vdw_radius    = 2.31;
  this->arecs[65].m_n_val_elec = 2;
  this->arecs[65].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 10),
    std::make_tuple(6, "s", 2)};
  this->arecs[65].m_color_jmol    = vector3<float>(
        0.12156862745098039,
        1.0,
        0.7803921568627451);
  this->arecs[65].m_color_gv      = vector3<float>(
        0.12156862745098039,
        1.0,
        0.7803921568627451);
  this->arecs[65].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[66].m_number       = 67;
  this->arecs[66].m_name         = "Holmium";
  this->arecs[66].m_symbol       = "Ho";
  this->arecs[66].m_radius       = 1.79;
  this->arecs[66].m_mass         = 164.93033;
  this->arecs[66].m_covrad_slater= 1.75;
  this->arecs[66].m_ionic_radius  = 0.9010000000000001;
  this->arecs[66].m_vdw_radius    = 2.3;
  this->arecs[66].m_n_val_elec = 2;
  this->arecs[66].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 11),
    std::make_tuple(6, "s", 2)};
  this->arecs[66].m_color_jmol    = vector3<float>(
        0.0,
        1.0,
        0.611764705882353);
  this->arecs[66].m_color_gv      = vector3<float>(
        0.0,
        1.0,
        0.611764705882353);
  this->arecs[66].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[67].m_number       = 68;
  this->arecs[67].m_name         = "Erbium";
  this->arecs[67].m_symbol       = "Er";
  this->arecs[67].m_radius       = 1.78;
  this->arecs[67].m_mass         = 167.259;
  this->arecs[67].m_covrad_slater= 1.75;
  this->arecs[67].m_ionic_radius  = 0.89;
  this->arecs[67].m_vdw_radius    = 2.29;
  this->arecs[67].m_n_val_elec = 2;
  this->arecs[67].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 12),
    std::make_tuple(6, "s", 2)};
  this->arecs[67].m_color_jmol    = vector3<float>(
        0.0,
        0.9019607843137255,
        0.4588235294117647);
  this->arecs[67].m_color_gv      = vector3<float>(
        0.0,
        0.9019607843137255,
        0.4588235294117647);
  this->arecs[67].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[68].m_number       = 69;
  this->arecs[68].m_name         = "Thulium";
  this->arecs[68].m_symbol       = "Tm";
  this->arecs[68].m_radius       = 1.77;
  this->arecs[68].m_mass         = 168.93422;
  this->arecs[68].m_covrad_slater= 1.75;
  this->arecs[68].m_ionic_radius  = 1.03;
  this->arecs[68].m_vdw_radius    = 2.27;
  this->arecs[68].m_n_val_elec = 2;
  this->arecs[68].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 13),
    std::make_tuple(6, "s", 2)};
  this->arecs[68].m_color_jmol    = vector3<float>(
        0.0,
        0.8313725490196079,
        0.3215686274509804);
  this->arecs[68].m_color_gv      = vector3<float>(
        0.0,
        0.8313725490196079,
        0.3215686274509804);
  this->arecs[68].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_7() {

  this->arecs[69].m_number       = 70;
  this->arecs[69].m_name         = "Ytterbium";
  this->arecs[69].m_symbol       = "Yb";
  this->arecs[69].m_radius       = 1.94;
  this->arecs[69].m_mass         = 173.045;
  this->arecs[69].m_covrad_slater= 1.75;
  this->arecs[69].m_ionic_radius  = 1.02;
  this->arecs[69].m_vdw_radius    = 2.26;
  this->arecs[69].m_n_val_elec = 2;
  this->arecs[69].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(6, "s", 2)};
  this->arecs[69].m_color_jmol    = vector3<float>(
        0.0,
        0.7490196078431373,
        0.2196078431372549);
  this->arecs[69].m_color_gv      = vector3<float>(
        0.0,
        0.7490196078431373,
        0.2196078431372549);
  this->arecs[69].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[70].m_number       = 71;
  this->arecs[70].m_name         = "Lutetium";
  this->arecs[70].m_symbol       = "Lu";
  this->arecs[70].m_radius       = 1.75;
  this->arecs[70].m_mass         = 174.9668;
  this->arecs[70].m_covrad_slater= 1.75;
  this->arecs[70].m_ionic_radius  = 0.861;
  this->arecs[70].m_vdw_radius    = 2.24;
  this->arecs[70].m_n_val_elec = 3;
  this->arecs[70].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 1),
    std::make_tuple(6, "s", 2)};
  this->arecs[70].m_color_jmol    = vector3<float>(
        0.0,
        0.6705882352941176,
        0.1411764705882353);
  this->arecs[70].m_color_gv      = vector3<float>(
        0.0,
        0.6705882352941176,
        0.1411764705882353);
  this->arecs[70].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[71].m_number       = 72;
  this->arecs[71].m_name         = "Hafnium";
  this->arecs[71].m_symbol       = "Hf";
  this->arecs[71].m_radius       = 1.67;
  this->arecs[71].m_mass         = 178.49;
  this->arecs[71].m_covrad_slater= 1.55;
  this->arecs[71].m_ionic_radius  = 0.58;
  this->arecs[71].m_vdw_radius    = 2.23;
  this->arecs[71].m_n_val_elec = 4;
  this->arecs[71].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 2),
    std::make_tuple(6, "s", 2)};
  this->arecs[71].m_color_jmol    = vector3<float>(
        0.30196078431372547,
        0.7607843137254902,
        1.0);
  this->arecs[71].m_color_gv      = vector3<float>(
        0.30196078431372547,
        0.7607843137254902,
        1.0);
  this->arecs[71].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[72].m_number       = 73;
  this->arecs[72].m_name         = "Tantalum";
  this->arecs[72].m_symbol       = "Ta";
  this->arecs[72].m_radius       = 1.49;
  this->arecs[72].m_mass         = 180.94788;
  this->arecs[72].m_covrad_slater= 1.45;
  this->arecs[72].m_ionic_radius  = 0.72;
  this->arecs[72].m_vdw_radius    = 2.22;
  this->arecs[72].m_n_val_elec = 5;
  this->arecs[72].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 3),
    std::make_tuple(6, "s", 2)};
  this->arecs[72].m_color_jmol    = vector3<float>(
        0.30196078431372547,
        0.6509803921568628,
        1.0);
  this->arecs[72].m_color_gv      = vector3<float>(
        0.30196078431372547,
        0.6509803921568628,
        1.0);
  this->arecs[72].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[73].m_number       = 74;
  this->arecs[73].m_name         = "Tungsten";
  this->arecs[73].m_symbol       = "W";
  this->arecs[73].m_radius       = 1.41;
  this->arecs[73].m_mass         = 183.84;
  this->arecs[73].m_covrad_slater= 1.35;
  this->arecs[73].m_ionic_radius  = 0.66;
  this->arecs[73].m_vdw_radius    = 2.18;
  this->arecs[73].m_n_val_elec = 6;
  this->arecs[73].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 4),
    std::make_tuple(6, "s", 2)};
  this->arecs[73].m_color_jmol    = vector3<float>(
        0.12941176470588237,
        0.5803921568627451,
        0.8392156862745098);
  this->arecs[73].m_color_gv      = vector3<float>(
        0.12941176470588237,
        0.5803921568627451,
        0.8392156862745098);
  this->arecs[73].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[74].m_number       = 75;
  this->arecs[74].m_name         = "Rhenium";
  this->arecs[74].m_symbol       = "Re";
  this->arecs[74].m_radius       = 1.37;
  this->arecs[74].m_mass         = 186.207;
  this->arecs[74].m_covrad_slater= 1.35;
  this->arecs[74].m_ionic_radius  = 0.63;
  this->arecs[74].m_vdw_radius    = 2.16;
  this->arecs[74].m_n_val_elec = 7;
  this->arecs[74].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 5),
    std::make_tuple(6, "s", 2)};
  this->arecs[74].m_color_jmol    = vector3<float>(
        0.14901960784313725,
        0.49019607843137253,
        0.6705882352941176);
  this->arecs[74].m_color_gv      = vector3<float>(
        0.14901960784313725,
        0.49019607843137253,
        0.6705882352941176);
  this->arecs[74].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[75].m_number       = 76;
  this->arecs[75].m_name         = "Osmium";
  this->arecs[75].m_symbol       = "Os";
  this->arecs[75].m_radius       = 1.35;
  this->arecs[75].m_mass         = 190.23;
  this->arecs[75].m_covrad_slater= 1.3;
  this->arecs[75].m_ionic_radius  = 0.63;
  this->arecs[75].m_vdw_radius    = 2.16;
  this->arecs[75].m_n_val_elec = 8;
  this->arecs[75].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 6),
    std::make_tuple(6, "s", 2)};
  this->arecs[75].m_color_jmol    = vector3<float>(
        0.14901960784313725,
        0.4,
        0.5882352941176471);
  this->arecs[75].m_color_gv      = vector3<float>(
        0.14901960784313725,
        0.4,
        0.5882352941176471);
  this->arecs[75].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[76].m_number       = 77;
  this->arecs[76].m_name         = "Iridium";
  this->arecs[76].m_symbol       = "Ir";
  this->arecs[76].m_radius       = 1.36;
  this->arecs[76].m_mass         = 192.217;
  this->arecs[76].m_covrad_slater= 1.35;
  this->arecs[76].m_ionic_radius  = 0.68;
  this->arecs[76].m_vdw_radius    = 2.13;
  this->arecs[76].m_n_val_elec = 9;
  this->arecs[76].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 7),
    std::make_tuple(6, "s", 2)};
  this->arecs[76].m_color_jmol    = vector3<float>(
        0.09019607843137255,
        0.32941176470588235,
        0.5294117647058824);
  this->arecs[76].m_color_gv      = vector3<float>(
        0.09019607843137255,
        0.32941176470588235,
        0.5294117647058824);
  this->arecs[76].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[77].m_number       = 78;
  this->arecs[77].m_name         = "Platinum";
  this->arecs[77].m_symbol       = "Pt";
  this->arecs[77].m_radius       = 1.3900000000000001;
  this->arecs[77].m_mass         = 195.084;
  this->arecs[77].m_covrad_slater= 1.35;
  this->arecs[77].m_ionic_radius  = 0.6;
  this->arecs[77].m_vdw_radius    = 2.13;
  this->arecs[77].m_n_val_elec = 10;
  this->arecs[77].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 9),
    std::make_tuple(6, "s", 1)};
  this->arecs[77].m_color_jmol    = vector3<float>(
        0.8156862745098039,
        0.8156862745098039,
        0.8784313725490196);
  this->arecs[77].m_color_gv      = vector3<float>(
        0.8156862745098039,
        0.8156862745098039,
        0.8784313725490196);
  this->arecs[77].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[78].m_number       = 79;
  this->arecs[78].m_name         = "Gold";
  this->arecs[78].m_symbol       = "Au";
  this->arecs[78].m_radius       = 1.46;
  this->arecs[78].m_mass         = 196.966569;
  this->arecs[78].m_covrad_slater= 1.35;
  this->arecs[78].m_ionic_radius  = 1.37;
  this->arecs[78].m_vdw_radius    = 2.14;
  this->arecs[78].m_n_val_elec = 11;
  this->arecs[78].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 1)};
  this->arecs[78].m_color_jmol    = vector3<float>(
        1.0,
        0.8196078431372549,
        0.13725490196078433);
  this->arecs[78].m_color_gv      = vector3<float>(
        1.0,
        0.8196078431372549,
        0.13725490196078433);
  this->arecs[78].m_color_cpk     = vector3<float>(
        0.8549019607843137,
        0.6470588235294118,
        0.12549019607843137);

}

void qpp::ptable::assembly_ptable_8() {

  this->arecs[79].m_number       = 80;
  this->arecs[79].m_name         = "Mercury";
  this->arecs[79].m_symbol       = "Hg";
  this->arecs[79].m_radius       = 1.57;
  this->arecs[79].m_mass         = 200.592;
  this->arecs[79].m_covrad_slater= 1.5;
  this->arecs[79].m_ionic_radius  = 0.97;
  this->arecs[79].m_vdw_radius    = 2.23;
  this->arecs[79].m_n_val_elec = 12;
  this->arecs[79].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2)};
  this->arecs[79].m_color_jmol    = vector3<float>(
        0.7215686274509804,
        0.7215686274509804,
        0.8156862745098039);
  this->arecs[79].m_color_gv      = vector3<float>(
        0.7215686274509804,
        0.7215686274509804,
        0.8156862745098039);
  this->arecs[79].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[80].m_number       = 81;
  this->arecs[80].m_name         = "Thallium";
  this->arecs[80].m_symbol       = "Tl";
  this->arecs[80].m_radius       = 1.71;
  this->arecs[80].m_mass         = 204.38;
  this->arecs[80].m_covrad_slater= 1.9000000000000001;
  this->arecs[80].m_ionic_radius  = 1.5;
  this->arecs[80].m_vdw_radius    = 1.96;
  this->arecs[80].m_n_val_elec = 3;
  this->arecs[80].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2),
    std::make_tuple(6, "p", 1)};
  this->arecs[80].m_color_jmol    = vector3<float>(
        0.6509803921568628,
        0.32941176470588235,
        0.30196078431372547);
  this->arecs[80].m_color_gv      = vector3<float>(
        0.6509803921568628,
        0.32941176470588235,
        0.30196078431372547);
  this->arecs[80].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[81].m_number       = 82;
  this->arecs[81].m_name         = "Lead";
  this->arecs[81].m_symbol       = "Pb";
  this->arecs[81].m_radius       = 1.75;
  this->arecs[81].m_mass         = 207.2;
  this->arecs[81].m_covrad_slater= -0.01;
  this->arecs[81].m_ionic_radius  = 0.98;
  this->arecs[81].m_vdw_radius    = 2.02;
  this->arecs[81].m_n_val_elec = 4;
  this->arecs[81].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2),
    std::make_tuple(6, "p", 2)};
  this->arecs[81].m_color_jmol    = vector3<float>(
        0.3411764705882353,
        0.34901960784313724,
        0.3803921568627451);
  this->arecs[81].m_color_gv      = vector3<float>(
        0.3411764705882353,
        0.34901960784313724,
        0.3803921568627451);
  this->arecs[81].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[82].m_number       = 83;
  this->arecs[82].m_name         = "Bismuth";
  this->arecs[82].m_symbol       = "Bi";
  this->arecs[82].m_radius       = 1.7;
  this->arecs[82].m_mass         = 208.9804;
  this->arecs[82].m_covrad_slater= 1.6;
  this->arecs[82].m_ionic_radius  = 0.96;
  this->arecs[82].m_vdw_radius    = 2.07;
  this->arecs[82].m_n_val_elec = 5;
  this->arecs[82].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2),
    std::make_tuple(6, "p", 3)};
  this->arecs[82].m_color_jmol    = vector3<float>(
        0.6196078431372549,
        0.30980392156862746,
        0.7098039215686275);
  this->arecs[82].m_color_gv      = vector3<float>(
        0.6196078431372549,
        0.30980392156862746,
        0.7098039215686275);
  this->arecs[82].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[83].m_number       = 84;
  this->arecs[83].m_name         = "Polonium";
  this->arecs[83].m_symbol       = "Po";
  this->arecs[83].m_radius       = 1.76;
  this->arecs[83].m_mass         = 209.0;
  this->arecs[83].m_covrad_slater= 1.9000000000000001;
  this->arecs[83].m_ionic_radius  = 0.9400000000000001;
  this->arecs[83].m_vdw_radius    = 1.97;
  this->arecs[83].m_n_val_elec = 6;
  this->arecs[83].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2),
    std::make_tuple(6, "p", 4)};
  this->arecs[83].m_color_jmol    = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.0);
  this->arecs[83].m_color_gv      = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.0);
  this->arecs[83].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[84].m_number       = 85;
  this->arecs[84].m_name         = "Astatine";
  this->arecs[84].m_symbol       = "At";
  this->arecs[84].m_radius       = -0.01;
  this->arecs[84].m_mass         = 210.0;
  this->arecs[84].m_covrad_slater= -0.01;
  this->arecs[84].m_ionic_radius  = 0.62;
  this->arecs[84].m_vdw_radius    = 2.02;
  this->arecs[84].m_n_val_elec = 7;
  this->arecs[84].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2),
    std::make_tuple(6, "p", 5)};
  this->arecs[84].m_color_jmol    = vector3<float>(
        0.4588235294117647,
        0.30980392156862746,
        0.27058823529411763);
  this->arecs[84].m_color_gv      = vector3<float>(
        0.4588235294117647,
        0.30980392156862746,
        0.27058823529411763);
  this->arecs[84].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[85].m_number       = 86;
  this->arecs[85].m_name         = "Radon";
  this->arecs[85].m_symbol       = "Rn";
  this->arecs[85].m_radius       = -0.01;
  this->arecs[85].m_mass         = 222.0;
  this->arecs[85].m_covrad_slater= -0.01;
  this->arecs[85].m_ionic_radius  = -0.01;
  this->arecs[85].m_vdw_radius    = 2.2;
  this->arecs[85].m_n_val_elec = 8;
  this->arecs[85].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "s", 2),
    std::make_tuple(6, "p", 6)};
  this->arecs[85].m_color_jmol    = vector3<float>(
        0.25882352941176473,
        0.5098039215686274,
        0.5882352941176471);
  this->arecs[85].m_color_gv      = vector3<float>(
        0.25882352941176473,
        0.5098039215686274,
        0.5882352941176471);
  this->arecs[85].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[86].m_number       = 87;
  this->arecs[86].m_name         = "Francium";
  this->arecs[86].m_symbol       = "Fr";
  this->arecs[86].m_radius       = -0.01;
  this->arecs[86].m_mass         = 223.0;
  this->arecs[86].m_covrad_slater= -0.01;
  this->arecs[86].m_ionic_radius  = 1.8;
  this->arecs[86].m_vdw_radius    = 3.48;
  this->arecs[86].m_n_val_elec = 1;
  this->arecs[86].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(7, "s", 1)};
  this->arecs[86].m_color_jmol    = vector3<float>(
        0.25882352941176473,
        0.0,
        0.4);
  this->arecs[86].m_color_gv      = vector3<float>(
        0.25882352941176473,
        0.0,
        0.4);
  this->arecs[86].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[87].m_number       = 88;
  this->arecs[87].m_name         = "Radium";
  this->arecs[87].m_symbol       = "Ra";
  this->arecs[87].m_radius       = -0.01;
  this->arecs[87].m_mass         = 226.0;
  this->arecs[87].m_covrad_slater= 2.15;
  this->arecs[87].m_ionic_radius  = 1.48;
  this->arecs[87].m_vdw_radius    = 2.83;
  this->arecs[87].m_n_val_elec = 2;
  this->arecs[87].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(7, "s", 2)};
  this->arecs[87].m_color_jmol    = vector3<float>(
        0.0,
        0.49019607843137253,
        0.0);
  this->arecs[87].m_color_gv      = vector3<float>(
        0.0,
        0.49019607843137253,
        0.0);
  this->arecs[87].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[88].m_number       = 89;
  this->arecs[88].m_name         = "Actinium";
  this->arecs[88].m_symbol       = "Ac";
  this->arecs[88].m_radius       = 1.8800000000000001;
  this->arecs[88].m_mass         = 227.0;
  this->arecs[88].m_covrad_slater= 1.95;
  this->arecs[88].m_ionic_radius  = 1.12;
  this->arecs[88].m_vdw_radius    = 2.47;
  this->arecs[88].m_n_val_elec = 2;
  this->arecs[88].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(6, "d", 1),
    std::make_tuple(7, "s", 2)};
  this->arecs[88].m_color_jmol    = vector3<float>(
        0.4392156862745098,
        0.6705882352941176,
        0.9803921568627451);
  this->arecs[88].m_color_gv      = vector3<float>(
        0.4392156862745098,
        0.6705882352941176,
        0.9803921568627451);
  this->arecs[88].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

}

void qpp::ptable::assembly_ptable_9() {

  this->arecs[89].m_number       = 90;
  this->arecs[89].m_name         = "Thorium";
  this->arecs[89].m_symbol       = "Th";
  this->arecs[89].m_radius       = 1.8;
  this->arecs[89].m_mass         = 232.0377;
  this->arecs[89].m_covrad_slater= 1.8;
  this->arecs[89].m_ionic_radius  = 0.9400000000000001;
  this->arecs[89].m_vdw_radius    = 2.45;
  this->arecs[89].m_n_val_elec = 2;
  this->arecs[89].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(6, "d", 2),
    std::make_tuple(7, "s", 2)};
  this->arecs[89].m_color_jmol    = vector3<float>(
        0.0,
        0.7294117647058823,
        1.0);
  this->arecs[89].m_color_gv      = vector3<float>(
        0.0,
        0.7294117647058823,
        1.0);
  this->arecs[89].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[90].m_number       = 91;
  this->arecs[90].m_name         = "Protactinium";
  this->arecs[90].m_symbol       = "Pa";
  this->arecs[90].m_radius       = 1.61;
  this->arecs[90].m_mass         = 231.03588;
  this->arecs[90].m_covrad_slater= 1.8;
  this->arecs[90].m_ionic_radius  = 1.04;
  this->arecs[90].m_vdw_radius    = 2.43;
  this->arecs[90].m_n_val_elec = 2;
  this->arecs[90].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 2),
    std::make_tuple(6, "d", 1),
    std::make_tuple(7, "s", 2)};
  this->arecs[90].m_color_jmol    = vector3<float>(
        0.0,
        0.6313725490196078,
        1.0);
  this->arecs[90].m_color_gv      = vector3<float>(
        0.0,
        0.6313725490196078,
        1.0);
  this->arecs[90].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[91].m_number       = 92;
  this->arecs[91].m_name         = "Uranium";
  this->arecs[91].m_symbol       = "U";
  this->arecs[91].m_radius       = 1.3800000000000001;
  this->arecs[91].m_mass         = 238.02891;
  this->arecs[91].m_covrad_slater= 1.75;
  this->arecs[91].m_ionic_radius  = 1.025;
  this->arecs[91].m_vdw_radius    = 2.41;
  this->arecs[91].m_n_val_elec = 2;
  this->arecs[91].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 3),
    std::make_tuple(6, "d", 1),
    std::make_tuple(7, "s", 2)};
  this->arecs[91].m_color_jmol    = vector3<float>(
        0.0,
        0.5607843137254902,
        1.0);
  this->arecs[91].m_color_gv      = vector3<float>(
        0.0,
        0.5607843137254902,
        1.0);
  this->arecs[91].m_color_cpk     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[92].m_number       = 93;
  this->arecs[92].m_name         = "Neptunium";
  this->arecs[92].m_symbol       = "Np";
  this->arecs[92].m_radius       = 1.3;
  this->arecs[92].m_mass         = 237.0;
  this->arecs[92].m_covrad_slater= 1.75;
  this->arecs[92].m_ionic_radius  = 1.1;
  this->arecs[92].m_vdw_radius    = 2.39;
  this->arecs[92].m_n_val_elec = 2;
  this->arecs[92].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 4),
    std::make_tuple(6, "d", 1),
    std::make_tuple(7, "s", 2)};
  this->arecs[92].m_color_jmol    = vector3<float>(
        0.0,
        0.5019607843137255,
        1.0);
  this->arecs[92].m_color_gv      = vector3<float>(
        0.0,
        0.5019607843137255,
        1.0);
  this->arecs[92].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[93].m_number       = 94;
  this->arecs[93].m_name         = "Plutonium";
  this->arecs[93].m_symbol       = "Pu";
  this->arecs[93].m_radius       = 1.51;
  this->arecs[93].m_mass         = 244.0;
  this->arecs[93].m_covrad_slater= 1.75;
  this->arecs[93].m_ionic_radius  = 1.0;
  this->arecs[93].m_vdw_radius    = 2.43;
  this->arecs[93].m_n_val_elec = 2;
  this->arecs[93].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 6),
    std::make_tuple(7, "s", 2)};
  this->arecs[93].m_color_jmol    = vector3<float>(
        0.0,
        0.4196078431372549,
        1.0);
  this->arecs[93].m_color_gv      = vector3<float>(
        0.0,
        0.4196078431372549,
        1.0);
  this->arecs[93].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[94].m_number       = 95;
  this->arecs[94].m_name         = "Americium";
  this->arecs[94].m_symbol       = "Am";
  this->arecs[94].m_radius       = 1.73;
  this->arecs[94].m_mass         = 243.0;
  this->arecs[94].m_covrad_slater= 1.75;
  this->arecs[94].m_ionic_radius  = 1.21;
  this->arecs[94].m_vdw_radius    = 2.44;
  this->arecs[94].m_n_val_elec = 2;
  this->arecs[94].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 7),
    std::make_tuple(7, "s", 2)};
  this->arecs[94].m_color_jmol    = vector3<float>(
        0.32941176470588235,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[94].m_color_gv      = vector3<float>(
        0.32941176470588235,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[94].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[95].m_number       = 96;
  this->arecs[95].m_name         = "Curium";
  this->arecs[95].m_symbol       = "Cm";
  this->arecs[95].m_radius       = 2.99;
  this->arecs[95].m_mass         = 247.0;
  this->arecs[95].m_covrad_slater= -0.01;
  this->arecs[95].m_ionic_radius  = 0.97;
  this->arecs[95].m_vdw_radius    = 2.45;
  this->arecs[95].m_n_val_elec = 2;
  this->arecs[95].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 7),
    std::make_tuple(6, "d", 1),
    std::make_tuple(7, "s", 2)};
  this->arecs[95].m_color_jmol    = vector3<float>(
        0.47058823529411764,
        0.3607843137254902,
        0.8901960784313725);
  this->arecs[95].m_color_gv      = vector3<float>(
        0.47058823529411764,
        0.3607843137254902,
        0.8901960784313725);
  this->arecs[95].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[96].m_number       = 97;
  this->arecs[96].m_name         = "Berkelium";
  this->arecs[96].m_symbol       = "Bk";
  this->arecs[96].m_radius       = 2.97;
  this->arecs[96].m_mass         = 247.0;
  this->arecs[96].m_covrad_slater= -0.01;
  this->arecs[96].m_ionic_radius  = 0.96;
  this->arecs[96].m_vdw_radius    = 2.44;
  this->arecs[96].m_n_val_elec = 2;
  this->arecs[96].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 9),
    std::make_tuple(7, "s", 2)};
  this->arecs[96].m_color_jmol    = vector3<float>(
        0.5411764705882353,
        0.30980392156862746,
        0.8901960784313725);
  this->arecs[96].m_color_gv      = vector3<float>(
        0.5411764705882353,
        0.30980392156862746,
        0.8901960784313725);
  this->arecs[96].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[97].m_number       = 98;
  this->arecs[97].m_name         = "Californium";
  this->arecs[97].m_symbol       = "Cf";
  this->arecs[97].m_radius       = 2.95;
  this->arecs[97].m_mass         = 251.0;
  this->arecs[97].m_covrad_slater= -0.01;
  this->arecs[97].m_ionic_radius  = 0.9500000000000001;
  this->arecs[97].m_vdw_radius    = 2.45;
  this->arecs[97].m_n_val_elec = 2;
  this->arecs[97].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 10),
    std::make_tuple(7, "s", 2)};
  this->arecs[97].m_color_jmol    = vector3<float>(
        0.6313725490196078,
        0.21176470588235294,
        0.8313725490196079);
  this->arecs[97].m_color_gv      = vector3<float>(
        0.6313725490196078,
        0.21176470588235294,
        0.8313725490196079);
  this->arecs[97].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[98].m_number       = 99;
  this->arecs[98].m_name         = "Einsteinium";
  this->arecs[98].m_symbol       = "Es";
  this->arecs[98].m_radius       = 2.92;
  this->arecs[98].m_mass         = 252.0;
  this->arecs[98].m_covrad_slater= -0.01;
  this->arecs[98].m_ionic_radius  = -0.01;
  this->arecs[98].m_vdw_radius    = 2.45;
  this->arecs[98].m_n_val_elec = 2;
  this->arecs[98].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 11),
    std::make_tuple(7, "s", 2)};
  this->arecs[98].m_color_jmol    = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.8313725490196079);
  this->arecs[98].m_color_gv      = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.8313725490196079);
  this->arecs[98].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[99].m_number       = 100;
  this->arecs[99].m_name         = "Fermium";
  this->arecs[99].m_symbol       = "Fm";
  this->arecs[99].m_radius       = 2.9;
  this->arecs[99].m_mass         = 257.0;
  this->arecs[99].m_covrad_slater= -0.01;
  this->arecs[99].m_ionic_radius  = -0.01;
  this->arecs[99].m_vdw_radius    = 2.45;
  this->arecs[99].m_n_val_elec = 2;
  this->arecs[99].m_elec_conf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2),
    std::make_tuple(4, "d", 10),
    std::make_tuple(5, "p", 6),
    std::make_tuple(6, "s", 2),
    std::make_tuple(4, "f", 14),
    std::make_tuple(5, "d", 10),
    std::make_tuple(6, "p", 6),
    std::make_tuple(5, "f", 12),
    std::make_tuple(7, "s", 2)};
  this->arecs[99].m_color_jmol    = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.7294117647058823);
  this->arecs[99].m_color_gv      = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.7294117647058823);
  this->arecs[99].m_color_cpk     = vector3<float>(
        1.0,
        1.0,
        1.0);
}

void ptable::init_cache_atom_idx() {

  for (int i = 0; i < 100; i++)
    cache_atom_idx[this->arecs[i].m_symbol] = this->arecs[i].m_number;

}
