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



void qpp::ptable::assembly_ptable_0(){
  this->arecs[0].aNumber       = 1;
  this->arecs[0].aName         = "Hydrogen";
  this->arecs[0].aSymbol       = "H";
  this->arecs[0].aRadius       = 0.79;
  this->arecs[0].aMass         = 1.008;
  this->arecs[0].aCovRad_Slater= 0.53; // gdis
  this->arecs[0].aIonicRadius  = -0.38;
  this->arecs[0].aVdWRadius    = 1.1;
  this->arecs[0].aNValenceElec = 1;
  this->arecs[0].aElecConf     = {
    std::make_tuple(1, "s", 1)};
  this->arecs[0].aColorJmol    = vector3<float>(
        1.0,
        1.0,
        1.0);
  this->arecs[0].aColorGV      = vector3<float>(
        0.9490196078431372,
        0.9490196078431372,
        0.9490196078431372);
  this->arecs[0].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[1].aNumber       = 2;
  this->arecs[1].aName         = "Helium";
  this->arecs[1].aSymbol       = "He";
  this->arecs[1].aRadius       =  0.79;
  this->arecs[1].aMass         = 4.002602;
  this->arecs[1].aCovRad_Slater= -0.1;
  this->arecs[1].aIonicRadius  = -0.01;
  this->arecs[1].aVdWRadius    = 1.4000000000000001;
  this->arecs[1].aNValenceElec = 2;
  this->arecs[1].aElecConf     = {
    std::make_tuple(1, "s", 2)};
  this->arecs[1].aColorJmol    = vector3<float>(
        0.8509803921568627,
        1.0,
        1.0);
  this->arecs[1].aColorGV      = vector3<float>(
        0.8509803921568627,
        1.0,
        1.0);
  this->arecs[1].aColorCPK     = vector3<float>(
        1.0,
        0.7529411764705882,
        0.796078431372549);

  this->arecs[2].aNumber       = 3;
  this->arecs[2].aName         = "Lithium";
  this->arecs[2].aSymbol       = "Li";
  this->arecs[2].aRadius       = 1.55;
  this->arecs[2].aMass         = 6.94;
  this->arecs[2].aCovRad_Slater= 1.45;
  this->arecs[2].aIonicRadius  = 0.59;
  this->arecs[2].aVdWRadius    = 1.82;
  this->arecs[2].aNValenceElec = 1;
  this->arecs[2].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 1)};
  this->arecs[2].aColorJmol    = vector3<float>(
        0.8,
        0.5019607843137255,
        1.0);
  this->arecs[2].aColorGV      = vector3<float>(
        0.8,
        0.5019607843137255,
        1.0);
  this->arecs[2].aColorCPK     = vector3<float>(
        0.6980392156862745,
        0.13333333333333333,
        0.13333333333333333);

  this->arecs[3].aNumber       = 4;
  this->arecs[3].aName         = "Beryllium";
  this->arecs[3].aSymbol       = "Be";
  this->arecs[3].aRadius       = 1.12;
  this->arecs[3].aMass         = 9.0121831;
  this->arecs[3].aCovRad_Slater= 1.05;
  this->arecs[3].aIonicRadius  = 0.16;
  this->arecs[3].aVdWRadius    = 1.53;
  this->arecs[3].aNValenceElec = 2;
  this->arecs[3].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2)};
  this->arecs[3].aColorJmol    = vector3<float>(
        0.7607843137254902,
        1.0,
        0.0);
  this->arecs[3].aColorGV      = vector3<float>(
        0.7607843137254902,
        1.0,
        0.0);
  this->arecs[3].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[4].aNumber       = 5;
  this->arecs[4].aName         = "Boron";
  this->arecs[4].aSymbol       = "B";
  this->arecs[4].aRadius       = 0.98;
  this->arecs[4].aMass         = 10.81;
  this->arecs[4].aCovRad_Slater= 0.85;
  this->arecs[4].aIonicRadius  = 0.01;
  this->arecs[4].aVdWRadius    = 1.92;
  this->arecs[4].aNValenceElec = 3;
  this->arecs[4].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 1)};
  this->arecs[4].aColorJmol    = vector3<float>(
        1.0,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[4].aColorGV      = vector3<float>(
        1.0,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[4].aColorCPK     = vector3<float>(
        0.0,
        1.0,
        0.0);

  this->arecs[5].aNumber       = 6;
  this->arecs[5].aName         = "Carbon";
  this->arecs[5].aSymbol       = "C";
  this->arecs[5].aRadius       = 0.91;
  this->arecs[5].aMass         = 12.011;
  this->arecs[5].aCovRad_Slater= 0.86; //gdis
  this->arecs[5].aIonicRadius  = -0.08;
  this->arecs[5].aVdWRadius    = 1.7;
  this->arecs[5].aNValenceElec = 4;
  this->arecs[5].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 2)};
  this->arecs[5].aColorJmol    = vector3<float>(
        0.5647058823529412,
        0.5647058823529412,
        0.5647058823529412);
  this->arecs[5].aColorGV      = vector3<float>(
        0.3333333333333333,
        0.3333333333333333,
        0.3333333333333333);
  this->arecs[5].aColorCPK     = vector3<float>(
        0.7843137254901961,
        0.7843137254901961,
        0.7843137254901961);

  this->arecs[6].aNumber       = 7;
  this->arecs[6].aName         = "Nitrogen";
  this->arecs[6].aSymbol       = "N";
  this->arecs[6].aRadius       = 0.92;
  this->arecs[6].aMass         = 14.007;
  this->arecs[6].aCovRad_Slater= 0.75;
  this->arecs[6].aIonicRadius  = 1.46;
  this->arecs[6].aVdWRadius    = 1.55;
  this->arecs[6].aNValenceElec = 5;
  this->arecs[6].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 3)};
  this->arecs[6].aColorJmol    = vector3<float>(
        0.18823529411764706,
        0.3137254901960784,
        0.9725490196078431);
  this->arecs[6].aColorGV      = vector3<float>(
        0.21568627450980393,
        0.3254901960784314,
        0.7333333333333333);
  this->arecs[6].aColorCPK     = vector3<float>(
        0.5607843137254902,
        0.5607843137254902,
        1.0);

  this->arecs[7].aNumber       = 8;
  this->arecs[7].aName         = "Oxygen";
  this->arecs[7].aSymbol       = "O";
  this->arecs[7].aRadius       = 0.92;
  this->arecs[7].aMass         = 15.999;
  this->arecs[7].aCovRad_Slater= 0.73;
  this->arecs[7].aIonicRadius  = 1.35;
  this->arecs[7].aVdWRadius    = 1.52;
  this->arecs[7].aNValenceElec = 6;
  this->arecs[7].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 4)};
  this->arecs[7].aColorJmol    = vector3<float>(
        1.0,
        0.050980392156862744,
        0.050980392156862744);
  this->arecs[7].aColorGV      = vector3<float>(
        0.9529411764705882,
        0.1803921568627451,
        0.25882352941176473);
  this->arecs[7].aColorCPK     = vector3<float>(
        0.9411764705882353,
        0.0,
        0.0);

  this->arecs[8].aNumber       = 9;
  this->arecs[8].aName         = "Fluorine";
  this->arecs[8].aSymbol       = "F";
  this->arecs[8].aRadius       = 0.92;
  this->arecs[8].aMass         = 18.998403163;
  this->arecs[8].aCovRad_Slater= 0.78;
  this->arecs[8].aIonicRadius  = 1.285;
  this->arecs[8].aVdWRadius    = 1.47;
  this->arecs[8].aNValenceElec = 7;
  this->arecs[8].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 5)};
  this->arecs[8].aColorJmol    = vector3<float>(
        0.5647058823529412,
        0.8784313725490196,
        0.3137254901960784);
  this->arecs[8].aColorGV      = vector3<float>(
        0.4980392156862745,
        0.8156862745098039,
        0.23137254901960785);
  this->arecs[8].aColorCPK     = vector3<float>(
        0.8549019607843137,
        0.6470588235294118,
        0.12549019607843137);

}

void qpp::ptable::assembly_ptable_1(){
  this->arecs[9].aNumber       = 10;
  this->arecs[9].aName         = "Neon";
  this->arecs[9].aSymbol       = "Ne";
  this->arecs[9].aRadius       = 0.92;
  this->arecs[9].aMass         = 20.1797;
  this->arecs[9].aCovRad_Slater= -0.01;
  this->arecs[9].aIonicRadius  = -0.01;
  this->arecs[9].aVdWRadius    = 1.54;
  this->arecs[9].aNValenceElec = 8;
  this->arecs[9].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6)};
  this->arecs[9].aColorJmol    = vector3<float>(
        0.7019607843137254,
        0.8901960784313725,
        0.9607843137254902);
  this->arecs[9].aColorGV      = vector3<float>(
        0.7019607843137254,
        0.8901960784313725,
        0.9607843137254902);
  this->arecs[9].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[10].aNumber       = 11;
  this->arecs[10].aName         = "Sodium";
  this->arecs[10].aSymbol       = "Na";
  this->arecs[10].aRadius       = 1.9000000000000001;
  this->arecs[10].aMass         = 22.98976928;
  this->arecs[10].aCovRad_Slater= 1.8;
  this->arecs[10].aIonicRadius  = 0.99;
  this->arecs[10].aVdWRadius    = 2.27;
  this->arecs[10].aNValenceElec = 1;
  this->arecs[10].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 1)};
  this->arecs[10].aColorJmol    = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[10].aColorGV      = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[10].aColorCPK     = vector3<float>(
        0.0,
        0.0,
        1.0);

  this->arecs[11].aNumber       = 12;
  this->arecs[11].aName         = "Magnesium";
  this->arecs[11].aSymbol       = "Mg";
  this->arecs[11].aRadius       = 1.6;
  this->arecs[11].aMass         = 24.305;
  this->arecs[11].aCovRad_Slater= 1.5;
  this->arecs[11].aIonicRadius  = 0.57;
  this->arecs[11].aVdWRadius    = 1.73;
  this->arecs[11].aNValenceElec = 2;
  this->arecs[11].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2)};
  this->arecs[11].aColorJmol    = vector3<float>(
        0.5411764705882353,
        1.0,
        0.0);
  this->arecs[11].aColorGV      = vector3<float>(
        0.5411764705882353,
        1.0,
        0.0);
  this->arecs[11].aColorCPK     = vector3<float>(
        0.13333333333333333,
        0.5450980392156862,
        0.13333333333333333);

  this->arecs[12].aNumber       = 13;
  this->arecs[12].aName         = "Aluminum";
  this->arecs[12].aSymbol       = "Al";
  this->arecs[12].aRadius       = 1.43;
  this->arecs[12].aMass         = 26.9815385;
  this->arecs[12].aCovRad_Slater= 1.25;
  this->arecs[12].aIonicRadius  = 0.39;
  this->arecs[12].aVdWRadius    = 1.84;
  this->arecs[12].aNValenceElec = 3;
  this->arecs[12].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 1)};
  this->arecs[12].aColorJmol    = vector3<float>(
        0.7490196078431373,
        0.6509803921568628,
        0.6509803921568628);
  this->arecs[12].aColorGV      = vector3<float>(
        0.7490196078431373,
        0.6509803921568628,
        0.6509803921568628);
  this->arecs[12].aColorCPK     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[13].aNumber       = 14;
  this->arecs[13].aName         = "Silicon";
  this->arecs[13].aSymbol       = "Si";
  this->arecs[13].aRadius       = 1.32;
  this->arecs[13].aMass         = 28.085;
  this->arecs[13].aCovRad_Slater= 1.25;
  this->arecs[13].aIonicRadius  = 0.26;
  this->arecs[13].aVdWRadius    = 2.1;
  this->arecs[13].aNValenceElec = 4;
  this->arecs[13].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 2)};
  this->arecs[13].aColorJmol    = vector3<float>(
        0.9411764705882353,
        0.7843137254901961,
        0.6274509803921569);
  this->arecs[13].aColorGV      = vector3<float>(
        0.9411764705882353,
        0.7843137254901961,
        0.6274509803921569);
  this->arecs[13].aColorCPK     = vector3<float>(
        0.8549019607843137,
        0.6470588235294118,
        0.12549019607843137);

  this->arecs[14].aNumber       = 15;
  this->arecs[14].aName         = "Phosphorus";
  this->arecs[14].aSymbol       = "P";
  this->arecs[14].aRadius       = 1.28;
  this->arecs[14].aMass         = 30.973761998;
  this->arecs[14].aCovRad_Slater= 1.0;
  this->arecs[14].aIonicRadius  = 0.44;
  this->arecs[14].aVdWRadius    = 1.8;
  this->arecs[14].aNValenceElec = 5;
  this->arecs[14].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 3)};
  this->arecs[14].aColorJmol    = vector3<float>(
        1.0,
        0.5019607843137255,
        0.0);
  this->arecs[14].aColorGV      = vector3<float>(
        1.0,
        0.5019607843137255,
        0.0);
  this->arecs[14].aColorCPK     = vector3<float>(
        1.0,
        0.6470588235294118,
        0.0);

  this->arecs[15].aNumber       = 16;
  this->arecs[15].aName         = "Sulfur";
  this->arecs[15].aSymbol       = "S";
  this->arecs[15].aRadius       = 1.27;
  this->arecs[15].aMass         = 32.06;
  this->arecs[15].aCovRad_Slater= 1.0;
  this->arecs[15].aIonicRadius  = 1.84;
  this->arecs[15].aVdWRadius    = 1.8;
  this->arecs[15].aNValenceElec = 6;
  this->arecs[15].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 4)};
  this->arecs[15].aColorJmol    = vector3<float>(
        1.0,
        1.0,
        0.18823529411764706);
  this->arecs[15].aColorGV      = vector3<float>(
        1.0,
        0.9607843137254902,
        0.1607843137254902);
  this->arecs[15].aColorCPK     = vector3<float>(
        1.0,
        0.7843137254901961,
        0.19607843137254902);

  this->arecs[16].aNumber       = 17;
  this->arecs[16].aName         = "Chlorine";
  this->arecs[16].aSymbol       = "Cl";
  this->arecs[16].aRadius       = 1.27;
  this->arecs[16].aMass         = 35.45;
  this->arecs[16].aCovRad_Slater= 1.0;
  this->arecs[16].aIonicRadius  = 1.81;
  this->arecs[16].aVdWRadius    = 1.75;
  this->arecs[16].aNValenceElec = 7;
  this->arecs[16].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 5)};
  this->arecs[16].aColorJmol    = vector3<float>(
        0.12156862745098039,
        0.9411764705882353,
        0.12156862745098039);
  this->arecs[16].aColorGV      = vector3<float>(
        0.2196078431372549,
        0.7098039215686275,
        0.2196078431372549);
  this->arecs[16].aColorCPK     = vector3<float>(
        0.0,
        1.0,
        0.0);

  this->arecs[17].aNumber       = 18;
  this->arecs[17].aName         = "Argon";
  this->arecs[17].aSymbol       = "Ar";
  this->arecs[17].aRadius       = 1.27;
  this->arecs[17].aMass         = 39.948;
  this->arecs[17].aCovRad_Slater= -0.01;
  this->arecs[17].aIonicRadius  = -0.01;
  this->arecs[17].aVdWRadius    = 1.8800000000000001;
  this->arecs[17].aNValenceElec = 8;
  this->arecs[17].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6)};
  this->arecs[17].aColorJmol    = vector3<float>(
        0.5019607843137255,
        0.8196078431372549,
        0.8901960784313725);
  this->arecs[17].aColorGV      = vector3<float>(
        0.5019607843137255,
        0.8196078431372549,
        0.8901960784313725);
  this->arecs[17].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[18].aNumber       = 19;
  this->arecs[18].aName         = "Potassium";
  this->arecs[18].aSymbol       = "K";
  this->arecs[18].aRadius       = 2.35;
  this->arecs[18].aMass         = 39.0983;
  this->arecs[18].aCovRad_Slater= 2.2;
  this->arecs[18].aIonicRadius  = 1.37;
  this->arecs[18].aVdWRadius    = 2.75;
  this->arecs[18].aNValenceElec = 1;
  this->arecs[18].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 1)};
  this->arecs[18].aColorJmol    = vector3<float>(
        0.5607843137254902,
        0.25098039215686274,
        0.8313725490196079);
  this->arecs[18].aColorGV      = vector3<float>(
        0.5607843137254902,
        0.25098039215686274,
        0.8313725490196079);
  this->arecs[18].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_2(){
  this->arecs[19].aNumber       = 20;
  this->arecs[19].aName         = "Calcium";
  this->arecs[19].aSymbol       = "Ca";
  this->arecs[19].aRadius       = 1.97;
  this->arecs[19].aMass         = 40.078;
  this->arecs[19].aCovRad_Slater= 1.8;
  this->arecs[19].aIonicRadius  = 1.0;
  this->arecs[19].aVdWRadius    = 2.31;
  this->arecs[19].aNValenceElec = 2;
  this->arecs[19].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2)};
  this->arecs[19].aColorJmol    = vector3<float>(
        0.23921568627450981,
        1.0,
        0.0);
  this->arecs[19].aColorGV      = vector3<float>(
        0.23921568627450981,
        1.0,
        0.0);
  this->arecs[19].aColorCPK     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[20].aNumber       = 21;
  this->arecs[20].aName         = "Scandium";
  this->arecs[20].aSymbol       = "Sc";
  this->arecs[20].aRadius       = 1.62;
  this->arecs[20].aMass         = 44.955908;
  this->arecs[20].aCovRad_Slater= 1.6;
  this->arecs[20].aIonicRadius  = 0.745;
  this->arecs[20].aVdWRadius    = 2.15;
  this->arecs[20].aNValenceElec = 3;
  this->arecs[20].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 1),
    std::make_tuple(4, "s", 2)};
  this->arecs[20].aColorJmol    = vector3<float>(
        0.9019607843137255,
        0.9019607843137255,
        0.9019607843137255);
  this->arecs[20].aColorGV      = vector3<float>(
        0.9019607843137255,
        0.9019607843137255,
        0.9019607843137255);
  this->arecs[20].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[21].aNumber       = 22;
  this->arecs[21].aName         = "Titanium";
  this->arecs[21].aSymbol       = "Ti";
  this->arecs[21].aRadius       = 1.47;
  this->arecs[21].aMass         = 47.867;
  this->arecs[21].aCovRad_Slater= 1.4000000000000001;
  this->arecs[21].aIonicRadius  = 0.86;
  this->arecs[21].aVdWRadius    = 2.11;
  this->arecs[21].aNValenceElec = 4;
  this->arecs[21].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 2),
    std::make_tuple(4, "s", 2)};
  this->arecs[21].aColorJmol    = vector3<float>(
        0.7490196078431373,
        0.7607843137254902,
        0.7803921568627451);
  this->arecs[21].aColorGV      = vector3<float>(
        0.7490196078431373,
        0.7607843137254902,
        0.7803921568627451);
  this->arecs[21].aColorCPK     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[22].aNumber       = 23;
  this->arecs[22].aName         = "Vanadium";
  this->arecs[22].aSymbol       = "V";
  this->arecs[22].aRadius       = 1.34;
  this->arecs[22].aMass         = 50.9415;
  this->arecs[22].aCovRad_Slater= 1.35;
  this->arecs[22].aIonicRadius  = 0.79;
  this->arecs[22].aVdWRadius    = 2.07;
  this->arecs[22].aNValenceElec = 5;
  this->arecs[22].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 3),
    std::make_tuple(4, "s", 2)};
  this->arecs[22].aColorJmol    = vector3<float>(
        0.6509803921568628,
        0.6509803921568628,
        0.6705882352941176);
  this->arecs[22].aColorGV      = vector3<float>(
        0.6509803921568628,
        0.6509803921568628,
        0.6705882352941176);
  this->arecs[22].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[23].aNumber       = 24;
  this->arecs[23].aName         = "Chromium";
  this->arecs[23].aSymbol       = "Cr";
  this->arecs[23].aRadius       = 1.3;
  this->arecs[23].aMass         = 51.9961;
  this->arecs[23].aCovRad_Slater= 1.4000000000000001;
  this->arecs[23].aIonicRadius  = 0.73;
  this->arecs[23].aVdWRadius    = 2.06;
  this->arecs[23].aNValenceElec = 6;
  this->arecs[23].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 5),
    std::make_tuple(4, "s", 1)};
  this->arecs[23].aColorJmol    = vector3<float>(
        0.5411764705882353,
        0.6,
        0.7803921568627451);
  this->arecs[23].aColorGV      = vector3<float>(
        0.5411764705882353,
        0.6,
        0.7803921568627451);
  this->arecs[23].aColorCPK     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[24].aNumber       = 25;
  this->arecs[24].aName         = "Manganese";
  this->arecs[24].aSymbol       = "Mn";
  this->arecs[24].aRadius       = 1.35;
  this->arecs[24].aMass         = 54.938044;
  this->arecs[24].aCovRad_Slater= 1.4000000000000001;
  this->arecs[24].aIonicRadius  = 0.66;
  this->arecs[24].aVdWRadius    = 2.05;
  this->arecs[24].aNValenceElec = 7;
  this->arecs[24].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 5),
    std::make_tuple(4, "s", 2)};
  this->arecs[24].aColorJmol    = vector3<float>(
        0.611764705882353,
        0.47843137254901963,
        0.7803921568627451);
  this->arecs[24].aColorGV      = vector3<float>(
        0.611764705882353,
        0.47843137254901963,
        0.7803921568627451);
  this->arecs[24].aColorCPK     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[25].aNumber       = 26;
  this->arecs[25].aName         = "Iron";
  this->arecs[25].aSymbol       = "Fe";
  this->arecs[25].aRadius       = 1.26;
  this->arecs[25].aMass         = 55.845;
  this->arecs[25].aCovRad_Slater= 1.4000000000000001;
  this->arecs[25].aIonicRadius  = 0.63;
  this->arecs[25].aVdWRadius    = 2.04;
  this->arecs[25].aNValenceElec = 8;
  this->arecs[25].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 6),
    std::make_tuple(4, "s", 2)};
  this->arecs[25].aColorJmol    = vector3<float>(
        0.8784313725490196,
        0.4,
        0.2);
  this->arecs[25].aColorGV      = vector3<float>(
        0.8784313725490196,
        0.4,
        0.2);
  this->arecs[25].aColorCPK     = vector3<float>(
        1.0,
        0.6470588235294118,
        0.0);

  this->arecs[26].aNumber       = 27;
  this->arecs[26].aName         = "Cobalt";
  this->arecs[26].aSymbol       = "Co";
  this->arecs[26].aRadius       = 1.25;
  this->arecs[26].aMass         = 58.933194;
  this->arecs[26].aCovRad_Slater= 1.35;
  this->arecs[26].aIonicRadius  = 0.58;
  this->arecs[26].aVdWRadius    = 2.0;
  this->arecs[26].aNValenceElec = 9;
  this->arecs[26].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 7),
    std::make_tuple(4, "s", 2)};
  this->arecs[26].aColorJmol    = vector3<float>(
        0.9411764705882353,
        0.5647058823529412,
        0.6274509803921569);
  this->arecs[26].aColorGV      = vector3<float>(
        0.9411764705882353,
        0.5647058823529412,
        0.6274509803921569);
  this->arecs[26].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[27].aNumber       = 28;
  this->arecs[27].aName         = "Nickel";
  this->arecs[27].aSymbol       = "Ni";
  this->arecs[27].aRadius       = 1.24;
  this->arecs[27].aMass         = 58.6934;
  this->arecs[27].aCovRad_Slater= 1.35;
  this->arecs[27].aIonicRadius  = 0.55;
  this->arecs[27].aVdWRadius    = 1.97;
  this->arecs[27].aNValenceElec = 10;
  this->arecs[27].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 8),
    std::make_tuple(4, "s", 2)};
  this->arecs[27].aColorJmol    = vector3<float>(
        0.3137254901960784,
        0.8156862745098039,
        0.3137254901960784);
  this->arecs[27].aColorGV      = vector3<float>(
        0.3137254901960784,
        0.8156862745098039,
        0.3137254901960784);
  this->arecs[27].aColorCPK     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

  this->arecs[28].aNumber       = 29;
  this->arecs[28].aName         = "Copper";
  this->arecs[28].aSymbol       = "Cu";
  this->arecs[28].aRadius       = 1.28;
  this->arecs[28].aMass         = 63.546;
  this->arecs[28].aCovRad_Slater= 1.35;
  this->arecs[28].aIonicRadius  = 0.46;
  this->arecs[28].aVdWRadius    = 1.96;
  this->arecs[28].aNValenceElec = 11;
  this->arecs[28].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 1)};
  this->arecs[28].aColorJmol    = vector3<float>(
        0.7843137254901961,
        0.5019607843137255,
        0.2);
  this->arecs[28].aColorGV      = vector3<float>(
        0.7843137254901961,
        0.5019607843137255,
        0.2);
  this->arecs[28].aColorCPK     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

}

void qpp::ptable::assembly_ptable_3(){
  this->arecs[29].aNumber       = 30;
  this->arecs[29].aName         = "Zinc";
  this->arecs[29].aSymbol       = "Zn";
  this->arecs[29].aRadius       = 1.3800000000000001;
  this->arecs[29].aMass         = 65.38;
  this->arecs[29].aCovRad_Slater= 1.35;
  this->arecs[29].aIonicRadius  = 0.6;
  this->arecs[29].aVdWRadius    = 2.01;
  this->arecs[29].aNValenceElec = 12;
  this->arecs[29].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2)};
  this->arecs[29].aColorJmol    = vector3<float>(
        0.49019607843137253,
        0.5019607843137255,
        0.6901960784313725);
  this->arecs[29].aColorGV      = vector3<float>(
        0.49019607843137253,
        0.5019607843137255,
        0.6901960784313725);
  this->arecs[29].aColorCPK     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

  this->arecs[30].aNumber       = 31;
  this->arecs[30].aName         = "Gallium";
  this->arecs[30].aSymbol       = "Ga";
  this->arecs[30].aRadius       = 1.41;
  this->arecs[30].aMass         = 69.723;
  this->arecs[30].aCovRad_Slater= 1.3;
  this->arecs[30].aIonicRadius  = 0.47000000000000003;
  this->arecs[30].aVdWRadius    = 1.87;
  this->arecs[30].aNValenceElec = 3;
  this->arecs[30].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 1)};
  this->arecs[30].aColorJmol    = vector3<float>(
        0.7607843137254902,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[30].aColorGV      = vector3<float>(
        0.7607843137254902,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[30].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[31].aNumber       = 32;
  this->arecs[31].aName         = "Germanium";
  this->arecs[31].aSymbol       = "Ge";
  this->arecs[31].aRadius       = 1.37;
  this->arecs[31].aMass         = 72.63;
  this->arecs[31].aCovRad_Slater= 1.25;
  this->arecs[31].aIonicRadius  = 0.73;
  this->arecs[31].aVdWRadius    = 2.11;
  this->arecs[31].aNValenceElec = 4;
  this->arecs[31].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 2)};
  this->arecs[31].aColorJmol    = vector3<float>(
        0.4,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[31].aColorGV      = vector3<float>(
        0.4,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[31].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[32].aNumber       = 33;
  this->arecs[32].aName         = "Arsenic";
  this->arecs[32].aSymbol       = "As";
  this->arecs[32].aRadius       = 1.3900000000000001;
  this->arecs[32].aMass         = 74.921595;
  this->arecs[32].aCovRad_Slater= 1.15;
  this->arecs[32].aIonicRadius  = 0.58;
  this->arecs[32].aVdWRadius    = 1.85;
  this->arecs[32].aNValenceElec = 5;
  this->arecs[32].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 3)};
  this->arecs[32].aColorJmol    = vector3<float>(
        0.7411764705882353,
        0.5019607843137255,
        0.8901960784313725);
  this->arecs[32].aColorGV      = vector3<float>(
        0.7411764705882353,
        0.5019607843137255,
        0.8901960784313725);
  this->arecs[32].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[33].aNumber       = 34;
  this->arecs[33].aName         = "Selenium";
  this->arecs[33].aSymbol       = "Se";
  this->arecs[33].aRadius       = 1.4000000000000001;
  this->arecs[33].aMass         = 78.971;
  this->arecs[33].aCovRad_Slater= 1.22;
  this->arecs[33].aIonicRadius  = 1.98;
  this->arecs[33].aVdWRadius    = 1.9000000000000001;
  this->arecs[33].aNValenceElec = 6;
  this->arecs[33].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 4)};
  this->arecs[33].aColorJmol    = vector3<float>(
        1.0,
        0.6313725490196078,
        0.0);
  this->arecs[33].aColorGV      = vector3<float>(
        1.0,
        0.6313725490196078,
        0.0);
  this->arecs[33].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[34].aNumber       = 35;
  this->arecs[34].aName         = "Bromine";
  this->arecs[34].aSymbol       = "Br";
  this->arecs[34].aRadius       = 1.4000;
  this->arecs[34].aMass         = 79.904;
  this->arecs[34].aCovRad_Slater= 1.31;
  this->arecs[34].aIonicRadius  = 1.96;
  this->arecs[34].aVdWRadius    = 1.85;
  this->arecs[34].aNValenceElec = 7;
  this->arecs[34].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 5)};
  this->arecs[34].aColorJmol    = vector3<float>(
        0.6509803921568628,
        0.1607843137254902,
        0.1607843137254902);
  this->arecs[34].aColorGV      = vector3<float>(
        0.6509803921568628,
        0.1607843137254902,
        0.1607843137254902);
  this->arecs[34].aColorCPK     = vector3<float>(
        0.6470588235294118,
        0.16470588235294117,
        0.16470588235294117);

  this->arecs[35].aNumber       = 36;
  this->arecs[35].aName         = "Krypton";
  this->arecs[35].aSymbol       = "Kr";
  this->arecs[35].aRadius       = 1.4000;
  this->arecs[35].aMass         = 83.798;
  this->arecs[35].aCovRad_Slater= -0.01;
  this->arecs[35].aIonicRadius  = -0.01;
  this->arecs[35].aVdWRadius    = 2.02;
  this->arecs[35].aNValenceElec = 8;
  this->arecs[35].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "s", 2),
    std::make_tuple(4, "p", 6)};
  this->arecs[35].aColorJmol    = vector3<float>(
        0.3607843137254902,
        0.7215686274509804,
        0.8196078431372549);
  this->arecs[35].aColorGV      = vector3<float>(
        0.3607843137254902,
        0.7215686274509804,
        0.8196078431372549);
  this->arecs[35].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[36].aNumber       = 37;
  this->arecs[36].aName         = "Rubidium";
  this->arecs[36].aSymbol       = "Rb";
  this->arecs[36].aRadius       = 2.48;
  this->arecs[36].aMass         = 85.4678;
  this->arecs[36].aCovRad_Slater= 2.35;
  this->arecs[36].aIonicRadius  = 1.52;
  this->arecs[36].aVdWRadius    = 3.0300000000000002;
  this->arecs[36].aNValenceElec = 1;
  this->arecs[36].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 1)};
  this->arecs[36].aColorJmol    = vector3<float>(
        0.4392156862745098,
        0.1803921568627451,
        0.6901960784313725);
  this->arecs[36].aColorGV      = vector3<float>(
        0.4392156862745098,
        0.1803921568627451,
        0.6901960784313725);
  this->arecs[36].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[37].aNumber       = 38;
  this->arecs[37].aName         = "Strontium";
  this->arecs[37].aSymbol       = "Sr";
  this->arecs[37].aRadius       = 2.15;
  this->arecs[37].aMass         = 87.62;
  this->arecs[37].aCovRad_Slater= 2.0;
  this->arecs[37].aIonicRadius  = 1.18;
  this->arecs[37].aVdWRadius    = 2.49;
  this->arecs[37].aNValenceElec = 2;
  this->arecs[37].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(5, "s", 2)};
  this->arecs[37].aColorJmol    = vector3<float>(
        0.0,
        1.0,
        0.0);
  this->arecs[37].aColorGV      = vector3<float>(
        0.0,
        1.0,
        0.0);
  this->arecs[37].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[38].aNumber       = 39;
  this->arecs[38].aName         = "Yttrium";
  this->arecs[38].aSymbol       = "Y";
  this->arecs[38].aRadius       = 1.78;
  this->arecs[38].aMass         = 88.90584;
  this->arecs[38].aCovRad_Slater= 1.8;
  this->arecs[38].aIonicRadius  = 0.9;
  this->arecs[38].aVdWRadius    = 2.32;
  this->arecs[38].aNValenceElec = 3;
  this->arecs[38].aElecConf     = {
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
  this->arecs[38].aColorJmol    = vector3<float>(
        0.5803921568627451,
        1.0,
        1.0);
  this->arecs[38].aColorGV      = vector3<float>(
        0.5803921568627451,
        1.0,
        1.0);
  this->arecs[38].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_4(){
  this->arecs[39].aNumber       = 40;
  this->arecs[39].aName         = "Zirconium";
  this->arecs[39].aSymbol       = "Zr";
  this->arecs[39].aRadius       = 1.6;
  this->arecs[39].aMass         = 91.224;
  this->arecs[39].aCovRad_Slater= 1.55;
  this->arecs[39].aIonicRadius  = 0.59;
  this->arecs[39].aVdWRadius    = 2.23;
  this->arecs[39].aNValenceElec = 4;
  this->arecs[39].aElecConf     = {
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
  this->arecs[39].aColorJmol    = vector3<float>(
        0.5803921568627451,
        0.8784313725490196,
        0.8784313725490196);
  this->arecs[39].aColorGV      = vector3<float>(
        0.5803921568627451,
        0.8784313725490196,
        0.8784313725490196);
  this->arecs[39].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[40].aNumber       = 41;
  this->arecs[40].aName         = "Niobium";
  this->arecs[40].aSymbol       = "Nb";
  this->arecs[40].aRadius       = 1.46;
  this->arecs[40].aMass         = 92.90637;
  this->arecs[40].aCovRad_Slater= 1.45;
  this->arecs[40].aIonicRadius  = 0.72;
  this->arecs[40].aVdWRadius    = 2.18;
  this->arecs[40].aNValenceElec = 5;
  this->arecs[40].aElecConf     = {
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
  this->arecs[40].aColorJmol    = vector3<float>(
        0.45098039215686275,
        0.7607843137254902,
        0.788235294117647);
  this->arecs[40].aColorGV      = vector3<float>(
        0.45098039215686275,
        0.7607843137254902,
        0.788235294117647);
  this->arecs[40].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[41].aNumber       = 42;
  this->arecs[41].aName         = "Molybdenum";
  this->arecs[41].aSymbol       = "Mo";
  this->arecs[41].aRadius       = 1.3900000000000001;
  this->arecs[41].aMass         = 95.95;
  this->arecs[41].aCovRad_Slater= 1.45;
  this->arecs[41].aIonicRadius  = 0.6900000000000001;
  this->arecs[41].aVdWRadius    = 2.17;
  this->arecs[41].aNValenceElec = 6;
  this->arecs[41].aElecConf     = {
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
  this->arecs[41].aColorJmol    = vector3<float>(
        0.32941176470588235,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[41].aColorGV      = vector3<float>(
        0.32941176470588235,
        0.7098039215686275,
        0.7098039215686275);
  this->arecs[41].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[42].aNumber       = 43;
  this->arecs[42].aName         = "Technetium";
  this->arecs[42].aSymbol       = "Tc";
  this->arecs[42].aRadius       = 1.36;
  this->arecs[42].aMass         = 97.90721;
  this->arecs[42].aCovRad_Slater= 1.35;
  this->arecs[42].aIonicRadius  = 0.645;
  this->arecs[42].aVdWRadius    = 2.16;
  this->arecs[42].aNValenceElec = 7;
  this->arecs[42].aElecConf     = {
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
  this->arecs[42].aColorJmol    = vector3<float>(
        0.23137254901960785,
        0.6196078431372549,
        0.6196078431372549);
  this->arecs[42].aColorGV      = vector3<float>(
        0.23137254901960785,
        0.6196078431372549,
        0.6196078431372549);
  this->arecs[42].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[43].aNumber       = 44;
  this->arecs[43].aName         = "Ruthenium";
  this->arecs[43].aSymbol       = "Ru";
  this->arecs[43].aRadius       = 1.34;
  this->arecs[43].aMass         = 101.07;
  this->arecs[43].aCovRad_Slater= 1.3;
  this->arecs[43].aIonicRadius  = 0.68;
  this->arecs[43].aVdWRadius    = 2.13;
  this->arecs[43].aNValenceElec = 8;
  this->arecs[43].aElecConf     = {
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
  this->arecs[43].aColorJmol    = vector3<float>(
        0.1411764705882353,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[43].aColorGV      = vector3<float>(
        0.1411764705882353,
        0.5607843137254902,
        0.5607843137254902);
  this->arecs[43].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[44].aNumber       = 45;
  this->arecs[44].aName         = "Rhodium";
  this->arecs[44].aSymbol       = "Rh";
  this->arecs[44].aRadius       = 1.34;
  this->arecs[44].aMass         = 102.9055;
  this->arecs[44].aCovRad_Slater= 1.35;
  this->arecs[44].aIonicRadius  = 0.665;
  this->arecs[44].aVdWRadius    = 2.1;
  this->arecs[44].aNValenceElec = 9;
  this->arecs[44].aElecConf     = {
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
  this->arecs[44].aColorJmol    = vector3<float>(
        0.0392156862745098,
        0.49019607843137253,
        0.5490196078431373);
  this->arecs[44].aColorGV      = vector3<float>(
        0.0392156862745098,
        0.49019607843137253,
        0.5490196078431373);
  this->arecs[44].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[45].aNumber       = 46;
  this->arecs[45].aName         = "Palladium";
  this->arecs[45].aSymbol       = "Pd";
  this->arecs[45].aRadius       = 1.37;
  this->arecs[45].aMass         = 106.42;
  this->arecs[45].aCovRad_Slater= 1.4000000000000001;
  this->arecs[45].aIonicRadius  = 0.59;
  this->arecs[45].aVdWRadius    = 2.1;
  this->arecs[45].aNValenceElec = 12;
  this->arecs[45].aElecConf     = {
    std::make_tuple(1, "s", 2),
    std::make_tuple(2, "s", 2),
    std::make_tuple(2, "p", 6),
    std::make_tuple(3, "s", 2),
    std::make_tuple(3, "p", 6),
    std::make_tuple(4, "s", 2),
    std::make_tuple(3, "d", 10),
    std::make_tuple(4, "p", 6),
    std::make_tuple(4, "d", 10)};
  this->arecs[45].aColorJmol    = vector3<float>(
        0.0,
        0.4117647058823529,
        0.5215686274509804);
  this->arecs[45].aColorGV      = vector3<float>(
        0.0,
        0.4117647058823529,
        0.5215686274509804);
  this->arecs[45].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[46].aNumber       = 47;
  this->arecs[46].aName         = "Silver";
  this->arecs[46].aSymbol       = "Ag";
  this->arecs[46].aRadius       = 1.44;
  this->arecs[46].aMass         = 107.8682;
  this->arecs[46].aCovRad_Slater= 1.6;
  this->arecs[46].aIonicRadius  = 0.67;
  this->arecs[46].aVdWRadius    = 2.11;
  this->arecs[46].aNValenceElec = 11;
  this->arecs[46].aElecConf     = {
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
  this->arecs[46].aColorJmol    = vector3<float>(
        0.7529411764705882,
        0.7529411764705882,
        0.7529411764705882);
  this->arecs[46].aColorGV      = vector3<float>(
        0.7529411764705882,
        0.7529411764705882,
        0.7529411764705882);
  this->arecs[46].aColorCPK     = vector3<float>(
        0.5019607843137255,
        0.5019607843137255,
        0.5647058823529412);

  this->arecs[47].aNumber       = 48;
  this->arecs[47].aName         = "Cadmium";
  this->arecs[47].aSymbol       = "Cd";
  this->arecs[47].aRadius       = 1.54;
  this->arecs[47].aMass         = 112.414;
  this->arecs[47].aCovRad_Slater= 1.69;
  this->arecs[47].aIonicRadius  = 0.78;
  this->arecs[47].aVdWRadius    = 2.18;
  this->arecs[47].aNValenceElec = 12;
  this->arecs[47].aElecConf     = {
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
  this->arecs[47].aColorJmol    = vector3<float>(
        1.0,
        0.8509803921568627,
        0.5607843137254902);
  this->arecs[47].aColorGV      = vector3<float>(
        1.0,
        0.8509803921568627,
        0.5607843137254902);
  this->arecs[47].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[48].aNumber       = 49;
  this->arecs[48].aName         = "Indium";
  this->arecs[48].aSymbol       = "In";
  this->arecs[48].aRadius       = 1.6600000000000001;
  this->arecs[48].aMass         = 114.818;
  this->arecs[48].aCovRad_Slater= 1.55;
  this->arecs[48].aIonicRadius  = 0.62;
  this->arecs[48].aVdWRadius    = 1.93;
  this->arecs[48].aNValenceElec = 3;
  this->arecs[48].aElecConf     = {
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
  this->arecs[48].aColorJmol    = vector3<float>(
        0.6509803921568628,
        0.4588235294117647,
        0.45098039215686275);
  this->arecs[48].aColorGV      = vector3<float>(
        0.6509803921568628,
        0.4588235294117647,
        0.45098039215686275);
  this->arecs[48].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_5(){
  this->arecs[49].aNumber       = 50;
  this->arecs[49].aName         = "Tin";
  this->arecs[49].aSymbol       = "Sn";
  this->arecs[49].aRadius       = 1.62;
  this->arecs[49].aMass         = 118.71;
  this->arecs[49].aCovRad_Slater= 1.45;
  this->arecs[49].aIonicRadius  = 0.55;
  this->arecs[49].aVdWRadius    = 2.17;
  this->arecs[49].aNValenceElec = 4;
  this->arecs[49].aElecConf     = {
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
  this->arecs[49].aColorJmol    = vector3<float>(
        0.4,
        0.5019607843137255,
        0.5019607843137255);
  this->arecs[49].aColorGV      = vector3<float>(
        0.4,
        0.5019607843137255,
        0.5019607843137255);
  this->arecs[49].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[50].aNumber       = 51;
  this->arecs[50].aName         = "Antimony";
  this->arecs[50].aSymbol       = "Sb";
  this->arecs[50].aRadius       = 1.59;
  this->arecs[50].aMass         = 121.76;
  this->arecs[50].aCovRad_Slater= 1.45;
  this->arecs[50].aIonicRadius  = 0.76;
  this->arecs[50].aVdWRadius    = 2.06;
  this->arecs[50].aNValenceElec = 5;
  this->arecs[50].aElecConf     = {
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
  this->arecs[50].aColorJmol    = vector3<float>(
        0.6196078431372549,
        0.38823529411764707,
        0.7098039215686275);
  this->arecs[50].aColorGV      = vector3<float>(
        0.6196078431372549,
        0.38823529411764707,
        0.7098039215686275);
  this->arecs[50].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[51].aNumber       = 52;
  this->arecs[51].aName         = "Tellurium";
  this->arecs[51].aSymbol       = "Te";
  this->arecs[51].aRadius       = 1.6;
  this->arecs[51].aMass         = 127.6;
  this->arecs[51].aCovRad_Slater= 1.4000000000000001;
  this->arecs[51].aIonicRadius  = 2.21;
  this->arecs[51].aVdWRadius    = 2.06;
  this->arecs[51].aNValenceElec = 6;
  this->arecs[51].aElecConf     = {
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
  this->arecs[51].aColorJmol    = vector3<float>(
        0.8313725490196079,
        0.47843137254901963,
        0.0);
  this->arecs[51].aColorGV      = vector3<float>(
        0.8313725490196079,
        0.47843137254901963,
        0.0);
  this->arecs[51].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[52].aNumber       = 53;
  this->arecs[52].aName         = "Iodine";
  this->arecs[52].aSymbol       = "I";
  this->arecs[52].aRadius       = 1.6;
  this->arecs[52].aMass         = 126.90447;
  this->arecs[52].aCovRad_Slater= 1.7;
  this->arecs[52].aIonicRadius  = 2.2;
  this->arecs[52].aVdWRadius    = 1.98;
  this->arecs[52].aNValenceElec = 7;
  this->arecs[52].aElecConf     = {
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
  this->arecs[52].aColorJmol    = vector3<float>(
        0.5803921568627451,
        0.0,
        0.5803921568627451);
  this->arecs[52].aColorGV      = vector3<float>(
        0.5803921568627451,
        0.0,
        0.5803921568627451);
  this->arecs[52].aColorCPK     = vector3<float>(
        0.6274509803921569,
        0.12549019607843137,
        0.9411764705882353);

  this->arecs[53].aNumber       = 54;
  this->arecs[53].aName         = "Xenon";
  this->arecs[53].aSymbol       = "Xe";
  this->arecs[53].aRadius       = -0.01;
  this->arecs[53].aMass         = 131.293;
  this->arecs[53].aCovRad_Slater= -0.01;
  this->arecs[53].aIonicRadius  = 0.4;
  this->arecs[53].aVdWRadius    = 2.16;
  this->arecs[53].aNValenceElec = 8;
  this->arecs[53].aElecConf     = {
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
  this->arecs[53].aColorJmol    = vector3<float>(
        0.25882352941176473,
        0.6196078431372549,
        0.6901960784313725);
  this->arecs[53].aColorGV      = vector3<float>(
        0.25882352941176473,
        0.6196078431372549,
        0.6901960784313725);
  this->arecs[53].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[54].aNumber       = 55;
  this->arecs[54].aName         = "Cesium";
  this->arecs[54].aSymbol       = "Cs";
  this->arecs[54].aRadius       = 2.67;
  this->arecs[54].aMass         = 132.90545196;
  this->arecs[54].aCovRad_Slater= 2.6;
  this->arecs[54].aIonicRadius  = 1.67;
  this->arecs[54].aVdWRadius    = 3.43;
  this->arecs[54].aNValenceElec = 1;
  this->arecs[54].aElecConf     = {
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
  this->arecs[54].aColorJmol    = vector3<float>(
        0.3411764705882353,
        0.09019607843137255,
        0.5607843137254902);
  this->arecs[54].aColorGV      = vector3<float>(
        0.3411764705882353,
        0.09019607843137255,
        0.5607843137254902);
  this->arecs[54].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[55].aNumber       = 56;
  this->arecs[55].aName         = "Barium";
  this->arecs[55].aSymbol       = "Ba";
  this->arecs[55].aRadius       = 2.22;
  this->arecs[55].aMass         = 137.327;
  this->arecs[55].aCovRad_Slater= 2.15;
  this->arecs[55].aIonicRadius  = 1.35;
  this->arecs[55].aVdWRadius    = 2.68;
  this->arecs[55].aNValenceElec = 2;
  this->arecs[55].aElecConf     = {
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
  this->arecs[55].aColorJmol    = vector3<float>(
        0.0,
        0.788235294117647,
        0.0);
  this->arecs[55].aColorGV      = vector3<float>(
        0.0,
        0.788235294117647,
        0.0);
  this->arecs[55].aColorCPK     = vector3<float>(
        1.0,
        0.6470588235294118,
        0.0);

  this->arecs[56].aNumber       = 57;
  this->arecs[56].aName         = "Lanthanum";
  this->arecs[56].aSymbol       = "La";
  this->arecs[56].aRadius       = 1.87;
  this->arecs[56].aMass         = 138.90547;
  this->arecs[56].aCovRad_Slater= 2.05;
  this->arecs[56].aIonicRadius  = 1.032;
  this->arecs[56].aVdWRadius    = 2.43;
  this->arecs[56].aNValenceElec = 2;
  this->arecs[56].aElecConf     = {
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
  this->arecs[56].aColorJmol    = vector3<float>(
        0.4392156862745098,
        0.8313725490196079,
        1.0);
  this->arecs[56].aColorGV      = vector3<float>(
        0.4392156862745098,
        0.8313725490196079,
        1.0);
  this->arecs[56].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[57].aNumber       = 58;
  this->arecs[57].aName         = "Cerium";
  this->arecs[57].aSymbol       = "Ce";
  this->arecs[57].aRadius       = 1.81;
  this->arecs[57].aMass         = 140.116;
  this->arecs[57].aCovRad_Slater= 1.85;
  this->arecs[57].aIonicRadius  = 1.01;
  this->arecs[57].aVdWRadius    = 2.42;
  this->arecs[57].aNValenceElec = 2;
  this->arecs[57].aElecConf     = {
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
  this->arecs[57].aColorJmol    = vector3<float>(
        1.0,
        1.0,
        0.7803921568627451);
  this->arecs[57].aColorGV      = vector3<float>(
        1.0,
        1.0,
        0.7803921568627451);
  this->arecs[57].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[58].aNumber       = 59;
  this->arecs[58].aName         = "Praseodymium";
  this->arecs[58].aSymbol       = "Pr";
  this->arecs[58].aRadius       = 1.82;
  this->arecs[58].aMass         = 140.90766;
  this->arecs[58].aCovRad_Slater= 1.85;
  this->arecs[58].aIonicRadius  = 0.99;
  this->arecs[58].aVdWRadius    = 2.4;
  this->arecs[58].aNValenceElec = 2;
  this->arecs[58].aElecConf     = {
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
  this->arecs[58].aColorJmol    = vector3<float>(
        0.8509803921568627,
        1.0,
        0.7803921568627451);
  this->arecs[58].aColorGV      = vector3<float>(
        0.8509803921568627,
        1.0,
        0.7803921568627451);
  this->arecs[58].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_6(){
  this->arecs[59].aNumber       = 60;
  this->arecs[59].aName         = "Neodymium";
  this->arecs[59].aSymbol       = "Nd";
  this->arecs[59].aRadius       = 1.82;
  this->arecs[59].aMass         = 144.242;
  this->arecs[59].aCovRad_Slater= 1.85;
  this->arecs[59].aIonicRadius  = 1.29;
  this->arecs[59].aVdWRadius    = 2.39;
  this->arecs[59].aNValenceElec = 2;
  this->arecs[59].aElecConf     = {
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
  this->arecs[59].aColorJmol    = vector3<float>(
        0.7803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[59].aColorGV      = vector3<float>(
        0.7803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[59].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[60].aNumber       = 61;
  this->arecs[60].aName         = "Promethium";
  this->arecs[60].aSymbol       = "Pm";
  this->arecs[60].aRadius       = -0.01;
  this->arecs[60].aMass         = 144.91276;
  this->arecs[60].aCovRad_Slater= 1.85;
  this->arecs[60].aIonicRadius  = 0.97;
  this->arecs[60].aVdWRadius    = 2.38;
  this->arecs[60].aNValenceElec = 2;
  this->arecs[60].aElecConf     = {
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
  this->arecs[60].aColorJmol    = vector3<float>(
        0.6392156862745098,
        1.0,
        0.7803921568627451);
  this->arecs[60].aColorGV      = vector3<float>(
        0.6392156862745098,
        1.0,
        0.7803921568627451);
  this->arecs[60].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[61].aNumber       = 62;
  this->arecs[61].aName         = "Samarium";
  this->arecs[61].aSymbol       = "Sm";
  this->arecs[61].aRadius       = 1.81;
  this->arecs[61].aMass         = 150.36;
  this->arecs[61].aCovRad_Slater= 1.85;
  this->arecs[61].aIonicRadius  = 1.22;
  this->arecs[61].aVdWRadius    = 2.36;
  this->arecs[61].aNValenceElec = 2;
  this->arecs[61].aElecConf     = {
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
  this->arecs[61].aColorJmol    = vector3<float>(
        0.5607843137254902,
        1.0,
        0.7803921568627451);
  this->arecs[61].aColorGV      = vector3<float>(
        0.5607843137254902,
        1.0,
        0.7803921568627451);
  this->arecs[61].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[62].aNumber       = 63;
  this->arecs[62].aName         = "Europium";
  this->arecs[62].aSymbol       = "Eu";
  this->arecs[62].aRadius       = 1.99;
  this->arecs[62].aMass         = 151.964;
  this->arecs[62].aCovRad_Slater= 1.85;
  this->arecs[62].aIonicRadius  = 1.17;
  this->arecs[62].aVdWRadius    = 2.35;
  this->arecs[62].aNValenceElec = 2;
  this->arecs[62].aElecConf     = {
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
  this->arecs[62].aColorJmol    = vector3<float>(
        0.3803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[62].aColorGV      = vector3<float>(
        0.3803921568627451,
        1.0,
        0.7803921568627451);
  this->arecs[62].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[63].aNumber       = 64;
  this->arecs[63].aName         = "Gadolinium";
  this->arecs[63].aSymbol       = "Gd";
  this->arecs[63].aRadius       = 1.79;
  this->arecs[63].aMass         = 157.25;
  this->arecs[63].aCovRad_Slater= 1.8;
  this->arecs[63].aIonicRadius  = 0.938;
  this->arecs[63].aVdWRadius    = 2.34;
  this->arecs[63].aNValenceElec = 2;
  this->arecs[63].aElecConf     = {
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
  this->arecs[63].aColorJmol    = vector3<float>(
        0.27058823529411763,
        1.0,
        0.7803921568627451);
  this->arecs[63].aColorGV      = vector3<float>(
        0.27058823529411763,
        1.0,
        0.7803921568627451);
  this->arecs[63].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[64].aNumber       = 65;
  this->arecs[64].aName         = "Terbium";
  this->arecs[64].aSymbol       = "Tb";
  this->arecs[64].aRadius       = 1.8;
  this->arecs[64].aMass         = 158.92535;
  this->arecs[64].aCovRad_Slater= 1.75;
  this->arecs[64].aIonicRadius  = 0.9230000000000002;
  this->arecs[64].aVdWRadius    = 2.33;
  this->arecs[64].aNValenceElec = 2;
  this->arecs[64].aElecConf     = {
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
  this->arecs[64].aColorJmol    = vector3<float>(
        0.18823529411764706,
        1.0,
        0.7803921568627451);
  this->arecs[64].aColorGV      = vector3<float>(
        0.18823529411764706,
        1.0,
        0.7803921568627451);
  this->arecs[64].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[65].aNumber       = 66;
  this->arecs[65].aName         = "Dysprosium";
  this->arecs[65].aSymbol       = "Dy";
  this->arecs[65].aRadius       = 1.8;
  this->arecs[65].aMass         = 162.5;
  this->arecs[65].aCovRad_Slater= 1.75;
  this->arecs[65].aIonicRadius  = 1.07;
  this->arecs[65].aVdWRadius    = 2.31;
  this->arecs[65].aNValenceElec = 2;
  this->arecs[65].aElecConf     = {
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
  this->arecs[65].aColorJmol    = vector3<float>(
        0.12156862745098039,
        1.0,
        0.7803921568627451);
  this->arecs[65].aColorGV      = vector3<float>(
        0.12156862745098039,
        1.0,
        0.7803921568627451);
  this->arecs[65].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[66].aNumber       = 67;
  this->arecs[66].aName         = "Holmium";
  this->arecs[66].aSymbol       = "Ho";
  this->arecs[66].aRadius       = 1.79;
  this->arecs[66].aMass         = 164.93033;
  this->arecs[66].aCovRad_Slater= 1.75;
  this->arecs[66].aIonicRadius  = 0.9010000000000001;
  this->arecs[66].aVdWRadius    = 2.3;
  this->arecs[66].aNValenceElec = 2;
  this->arecs[66].aElecConf     = {
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
  this->arecs[66].aColorJmol    = vector3<float>(
        0.0,
        1.0,
        0.611764705882353);
  this->arecs[66].aColorGV      = vector3<float>(
        0.0,
        1.0,
        0.611764705882353);
  this->arecs[66].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[67].aNumber       = 68;
  this->arecs[67].aName         = "Erbium";
  this->arecs[67].aSymbol       = "Er";
  this->arecs[67].aRadius       = 1.78;
  this->arecs[67].aMass         = 167.259;
  this->arecs[67].aCovRad_Slater= 1.75;
  this->arecs[67].aIonicRadius  = 0.89;
  this->arecs[67].aVdWRadius    = 2.29;
  this->arecs[67].aNValenceElec = 2;
  this->arecs[67].aElecConf     = {
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
  this->arecs[67].aColorJmol    = vector3<float>(
        0.0,
        0.9019607843137255,
        0.4588235294117647);
  this->arecs[67].aColorGV      = vector3<float>(
        0.0,
        0.9019607843137255,
        0.4588235294117647);
  this->arecs[67].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[68].aNumber       = 69;
  this->arecs[68].aName         = "Thulium";
  this->arecs[68].aSymbol       = "Tm";
  this->arecs[68].aRadius       = 1.77;
  this->arecs[68].aMass         = 168.93422;
  this->arecs[68].aCovRad_Slater= 1.75;
  this->arecs[68].aIonicRadius  = 1.03;
  this->arecs[68].aVdWRadius    = 2.27;
  this->arecs[68].aNValenceElec = 2;
  this->arecs[68].aElecConf     = {
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
  this->arecs[68].aColorJmol    = vector3<float>(
        0.0,
        0.8313725490196079,
        0.3215686274509804);
  this->arecs[68].aColorGV      = vector3<float>(
        0.0,
        0.8313725490196079,
        0.3215686274509804);
  this->arecs[68].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

}

void qpp::ptable::assembly_ptable_7(){
  this->arecs[69].aNumber       = 70;
  this->arecs[69].aName         = "Ytterbium";
  this->arecs[69].aSymbol       = "Yb";
  this->arecs[69].aRadius       = 1.94;
  this->arecs[69].aMass         = 173.045;
  this->arecs[69].aCovRad_Slater= 1.75;
  this->arecs[69].aIonicRadius  = 1.02;
  this->arecs[69].aVdWRadius    = 2.26;
  this->arecs[69].aNValenceElec = 2;
  this->arecs[69].aElecConf     = {
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
  this->arecs[69].aColorJmol    = vector3<float>(
        0.0,
        0.7490196078431373,
        0.2196078431372549);
  this->arecs[69].aColorGV      = vector3<float>(
        0.0,
        0.7490196078431373,
        0.2196078431372549);
  this->arecs[69].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[70].aNumber       = 71;
  this->arecs[70].aName         = "Lutetium";
  this->arecs[70].aSymbol       = "Lu";
  this->arecs[70].aRadius       = 1.75;
  this->arecs[70].aMass         = 174.9668;
  this->arecs[70].aCovRad_Slater= 1.75;
  this->arecs[70].aIonicRadius  = 0.861;
  this->arecs[70].aVdWRadius    = 2.24;
  this->arecs[70].aNValenceElec = 3;
  this->arecs[70].aElecConf     = {
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
  this->arecs[70].aColorJmol    = vector3<float>(
        0.0,
        0.6705882352941176,
        0.1411764705882353);
  this->arecs[70].aColorGV      = vector3<float>(
        0.0,
        0.6705882352941176,
        0.1411764705882353);
  this->arecs[70].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[71].aNumber       = 72;
  this->arecs[71].aName         = "Hafnium";
  this->arecs[71].aSymbol       = "Hf";
  this->arecs[71].aRadius       = 1.67;
  this->arecs[71].aMass         = 178.49;
  this->arecs[71].aCovRad_Slater= 1.55;
  this->arecs[71].aIonicRadius  = 0.58;
  this->arecs[71].aVdWRadius    = 2.23;
  this->arecs[71].aNValenceElec = 4;
  this->arecs[71].aElecConf     = {
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
  this->arecs[71].aColorJmol    = vector3<float>(
        0.30196078431372547,
        0.7607843137254902,
        1.0);
  this->arecs[71].aColorGV      = vector3<float>(
        0.30196078431372547,
        0.7607843137254902,
        1.0);
  this->arecs[71].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[72].aNumber       = 73;
  this->arecs[72].aName         = "Tantalum";
  this->arecs[72].aSymbol       = "Ta";
  this->arecs[72].aRadius       = 1.49;
  this->arecs[72].aMass         = 180.94788;
  this->arecs[72].aCovRad_Slater= 1.45;
  this->arecs[72].aIonicRadius  = 0.72;
  this->arecs[72].aVdWRadius    = 2.22;
  this->arecs[72].aNValenceElec = 5;
  this->arecs[72].aElecConf     = {
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
  this->arecs[72].aColorJmol    = vector3<float>(
        0.30196078431372547,
        0.6509803921568628,
        1.0);
  this->arecs[72].aColorGV      = vector3<float>(
        0.30196078431372547,
        0.6509803921568628,
        1.0);
  this->arecs[72].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[73].aNumber       = 74;
  this->arecs[73].aName         = "Tungsten";
  this->arecs[73].aSymbol       = "W";
  this->arecs[73].aRadius       = 1.41;
  this->arecs[73].aMass         = 183.84;
  this->arecs[73].aCovRad_Slater= 1.35;
  this->arecs[73].aIonicRadius  = 0.66;
  this->arecs[73].aVdWRadius    = 2.18;
  this->arecs[73].aNValenceElec = 6;
  this->arecs[73].aElecConf     = {
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
  this->arecs[73].aColorJmol    = vector3<float>(
        0.12941176470588237,
        0.5803921568627451,
        0.8392156862745098);
  this->arecs[73].aColorGV      = vector3<float>(
        0.12941176470588237,
        0.5803921568627451,
        0.8392156862745098);
  this->arecs[73].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[74].aNumber       = 75;
  this->arecs[74].aName         = "Rhenium";
  this->arecs[74].aSymbol       = "Re";
  this->arecs[74].aRadius       = 1.37;
  this->arecs[74].aMass         = 186.207;
  this->arecs[74].aCovRad_Slater= 1.35;
  this->arecs[74].aIonicRadius  = 0.63;
  this->arecs[74].aVdWRadius    = 2.16;
  this->arecs[74].aNValenceElec = 7;
  this->arecs[74].aElecConf     = {
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
  this->arecs[74].aColorJmol    = vector3<float>(
        0.14901960784313725,
        0.49019607843137253,
        0.6705882352941176);
  this->arecs[74].aColorGV      = vector3<float>(
        0.14901960784313725,
        0.49019607843137253,
        0.6705882352941176);
  this->arecs[74].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[75].aNumber       = 76;
  this->arecs[75].aName         = "Osmium";
  this->arecs[75].aSymbol       = "Os";
  this->arecs[75].aRadius       = 1.35;
  this->arecs[75].aMass         = 190.23;
  this->arecs[75].aCovRad_Slater= 1.3;
  this->arecs[75].aIonicRadius  = 0.63;
  this->arecs[75].aVdWRadius    = 2.16;
  this->arecs[75].aNValenceElec = 8;
  this->arecs[75].aElecConf     = {
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
  this->arecs[75].aColorJmol    = vector3<float>(
        0.14901960784313725,
        0.4,
        0.5882352941176471);
  this->arecs[75].aColorGV      = vector3<float>(
        0.14901960784313725,
        0.4,
        0.5882352941176471);
  this->arecs[75].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[76].aNumber       = 77;
  this->arecs[76].aName         = "Iridium";
  this->arecs[76].aSymbol       = "Ir";
  this->arecs[76].aRadius       = 1.36;
  this->arecs[76].aMass         = 192.217;
  this->arecs[76].aCovRad_Slater= 1.35;
  this->arecs[76].aIonicRadius  = 0.68;
  this->arecs[76].aVdWRadius    = 2.13;
  this->arecs[76].aNValenceElec = 9;
  this->arecs[76].aElecConf     = {
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
  this->arecs[76].aColorJmol    = vector3<float>(
        0.09019607843137255,
        0.32941176470588235,
        0.5294117647058824);
  this->arecs[76].aColorGV      = vector3<float>(
        0.09019607843137255,
        0.32941176470588235,
        0.5294117647058824);
  this->arecs[76].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[77].aNumber       = 78;
  this->arecs[77].aName         = "Platinum";
  this->arecs[77].aSymbol       = "Pt";
  this->arecs[77].aRadius       = 1.3900000000000001;
  this->arecs[77].aMass         = 195.084;
  this->arecs[77].aCovRad_Slater= 1.35;
  this->arecs[77].aIonicRadius  = 0.6;
  this->arecs[77].aVdWRadius    = 2.13;
  this->arecs[77].aNValenceElec = 10;
  this->arecs[77].aElecConf     = {
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
  this->arecs[77].aColorJmol    = vector3<float>(
        0.8156862745098039,
        0.8156862745098039,
        0.8784313725490196);
  this->arecs[77].aColorGV      = vector3<float>(
        0.8156862745098039,
        0.8156862745098039,
        0.8784313725490196);
  this->arecs[77].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[78].aNumber       = 79;
  this->arecs[78].aName         = "Gold";
  this->arecs[78].aSymbol       = "Au";
  this->arecs[78].aRadius       = 1.46;
  this->arecs[78].aMass         = 196.966569;
  this->arecs[78].aCovRad_Slater= 1.35;
  this->arecs[78].aIonicRadius  = 1.37;
  this->arecs[78].aVdWRadius    = 2.14;
  this->arecs[78].aNValenceElec = 11;
  this->arecs[78].aElecConf     = {
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
  this->arecs[78].aColorJmol    = vector3<float>(
        1.0,
        0.8196078431372549,
        0.13725490196078433);
  this->arecs[78].aColorGV      = vector3<float>(
        1.0,
        0.8196078431372549,
        0.13725490196078433);
  this->arecs[78].aColorCPK     = vector3<float>(
        0.8549019607843137,
        0.6470588235294118,
        0.12549019607843137);

}

void qpp::ptable::assembly_ptable_8(){
  this->arecs[79].aNumber       = 80;
  this->arecs[79].aName         = "Mercury";
  this->arecs[79].aSymbol       = "Hg";
  this->arecs[79].aRadius       = 1.57;
  this->arecs[79].aMass         = 200.592;
  this->arecs[79].aCovRad_Slater= 1.5;
  this->arecs[79].aIonicRadius  = 0.97;
  this->arecs[79].aVdWRadius    = 2.23;
  this->arecs[79].aNValenceElec = 12;
  this->arecs[79].aElecConf     = {
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
  this->arecs[79].aColorJmol    = vector3<float>(
        0.7215686274509804,
        0.7215686274509804,
        0.8156862745098039);
  this->arecs[79].aColorGV      = vector3<float>(
        0.7215686274509804,
        0.7215686274509804,
        0.8156862745098039);
  this->arecs[79].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[80].aNumber       = 81;
  this->arecs[80].aName         = "Thallium";
  this->arecs[80].aSymbol       = "Tl";
  this->arecs[80].aRadius       = 1.71;
  this->arecs[80].aMass         = 204.38;
  this->arecs[80].aCovRad_Slater= 1.9000000000000001;
  this->arecs[80].aIonicRadius  = 1.5;
  this->arecs[80].aVdWRadius    = 1.96;
  this->arecs[80].aNValenceElec = 3;
  this->arecs[80].aElecConf     = {
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
  this->arecs[80].aColorJmol    = vector3<float>(
        0.6509803921568628,
        0.32941176470588235,
        0.30196078431372547);
  this->arecs[80].aColorGV      = vector3<float>(
        0.6509803921568628,
        0.32941176470588235,
        0.30196078431372547);
  this->arecs[80].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[81].aNumber       = 82;
  this->arecs[81].aName         = "Lead";
  this->arecs[81].aSymbol       = "Pb";
  this->arecs[81].aRadius       = 1.75;
  this->arecs[81].aMass         = 207.2;
  this->arecs[81].aCovRad_Slater= -0.01;
  this->arecs[81].aIonicRadius  = 0.98;
  this->arecs[81].aVdWRadius    = 2.02;
  this->arecs[81].aNValenceElec = 4;
  this->arecs[81].aElecConf     = {
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
  this->arecs[81].aColorJmol    = vector3<float>(
        0.3411764705882353,
        0.34901960784313724,
        0.3803921568627451);
  this->arecs[81].aColorGV      = vector3<float>(
        0.3411764705882353,
        0.34901960784313724,
        0.3803921568627451);
  this->arecs[81].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[82].aNumber       = 83;
  this->arecs[82].aName         = "Bismuth";
  this->arecs[82].aSymbol       = "Bi";
  this->arecs[82].aRadius       = 1.7;
  this->arecs[82].aMass         = 208.9804;
  this->arecs[82].aCovRad_Slater= 1.6;
  this->arecs[82].aIonicRadius  = 0.96;
  this->arecs[82].aVdWRadius    = 2.07;
  this->arecs[82].aNValenceElec = 5;
  this->arecs[82].aElecConf     = {
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
  this->arecs[82].aColorJmol    = vector3<float>(
        0.6196078431372549,
        0.30980392156862746,
        0.7098039215686275);
  this->arecs[82].aColorGV      = vector3<float>(
        0.6196078431372549,
        0.30980392156862746,
        0.7098039215686275);
  this->arecs[82].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[83].aNumber       = 84;
  this->arecs[83].aName         = "Polonium";
  this->arecs[83].aSymbol       = "Po";
  this->arecs[83].aRadius       = 1.76;
  this->arecs[83].aMass         = 209.0;
  this->arecs[83].aCovRad_Slater= 1.9000000000000001;
  this->arecs[83].aIonicRadius  = 0.9400000000000001;
  this->arecs[83].aVdWRadius    = 1.97;
  this->arecs[83].aNValenceElec = 6;
  this->arecs[83].aElecConf     = {
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
  this->arecs[83].aColorJmol    = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.0);
  this->arecs[83].aColorGV      = vector3<float>(
        0.6705882352941176,
        0.3607843137254902,
        0.0);
  this->arecs[83].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[84].aNumber       = 85;
  this->arecs[84].aName         = "Astatine";
  this->arecs[84].aSymbol       = "At";
  this->arecs[84].aRadius       = -0.01;
  this->arecs[84].aMass         = 210.0;
  this->arecs[84].aCovRad_Slater= -0.01;
  this->arecs[84].aIonicRadius  = 0.62;
  this->arecs[84].aVdWRadius    = 2.02;
  this->arecs[84].aNValenceElec = 7;
  this->arecs[84].aElecConf     = {
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
  this->arecs[84].aColorJmol    = vector3<float>(
        0.4588235294117647,
        0.30980392156862746,
        0.27058823529411763);
  this->arecs[84].aColorGV      = vector3<float>(
        0.4588235294117647,
        0.30980392156862746,
        0.27058823529411763);
  this->arecs[84].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[85].aNumber       = 86;
  this->arecs[85].aName         = "Radon";
  this->arecs[85].aSymbol       = "Rn";
  this->arecs[85].aRadius       = -0.01;
  this->arecs[85].aMass         = 222.0;
  this->arecs[85].aCovRad_Slater= -0.01;
  this->arecs[85].aIonicRadius  = -0.01;
  this->arecs[85].aVdWRadius    = 2.2;
  this->arecs[85].aNValenceElec = 8;
  this->arecs[85].aElecConf     = {
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
  this->arecs[85].aColorJmol    = vector3<float>(
        0.25882352941176473,
        0.5098039215686274,
        0.5882352941176471);
  this->arecs[85].aColorGV      = vector3<float>(
        0.25882352941176473,
        0.5098039215686274,
        0.5882352941176471);
  this->arecs[85].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[86].aNumber       = 87;
  this->arecs[86].aName         = "Francium";
  this->arecs[86].aSymbol       = "Fr";
  this->arecs[86].aRadius       = -0.01;
  this->arecs[86].aMass         = 223.0;
  this->arecs[86].aCovRad_Slater= -0.01;
  this->arecs[86].aIonicRadius  = 1.8;
  this->arecs[86].aVdWRadius    = 3.48;
  this->arecs[86].aNValenceElec = 1;
  this->arecs[86].aElecConf     = {
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
  this->arecs[86].aColorJmol    = vector3<float>(
        0.25882352941176473,
        0.0,
        0.4);
  this->arecs[86].aColorGV      = vector3<float>(
        0.25882352941176473,
        0.0,
        0.4);
  this->arecs[86].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[87].aNumber       = 88;
  this->arecs[87].aName         = "Radium";
  this->arecs[87].aSymbol       = "Ra";
  this->arecs[87].aRadius       = -0.01;
  this->arecs[87].aMass         = 226.0;
  this->arecs[87].aCovRad_Slater= 2.15;
  this->arecs[87].aIonicRadius  = 1.48;
  this->arecs[87].aVdWRadius    = 2.83;
  this->arecs[87].aNValenceElec = 2;
  this->arecs[87].aElecConf     = {
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
  this->arecs[87].aColorJmol    = vector3<float>(
        0.0,
        0.49019607843137253,
        0.0);
  this->arecs[87].aColorGV      = vector3<float>(
        0.0,
        0.49019607843137253,
        0.0);
  this->arecs[87].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[88].aNumber       = 89;
  this->arecs[88].aName         = "Actinium";
  this->arecs[88].aSymbol       = "Ac";
  this->arecs[88].aRadius       = 1.8800000000000001;
  this->arecs[88].aMass         = 227.0;
  this->arecs[88].aCovRad_Slater= 1.95;
  this->arecs[88].aIonicRadius  = 1.12;
  this->arecs[88].aVdWRadius    = 2.47;
  this->arecs[88].aNValenceElec = 2;
  this->arecs[88].aElecConf     = {
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
  this->arecs[88].aColorJmol    = vector3<float>(
        0.4392156862745098,
        0.6705882352941176,
        0.9803921568627451);
  this->arecs[88].aColorGV      = vector3<float>(
        0.4392156862745098,
        0.6705882352941176,
        0.9803921568627451);
  this->arecs[88].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

}

void qpp::ptable::assembly_ptable_9(){
  this->arecs[89].aNumber       = 90;
  this->arecs[89].aName         = "Thorium";
  this->arecs[89].aSymbol       = "Th";
  this->arecs[89].aRadius       = 1.8;
  this->arecs[89].aMass         = 232.0377;
  this->arecs[89].aCovRad_Slater= 1.8;
  this->arecs[89].aIonicRadius  = 0.9400000000000001;
  this->arecs[89].aVdWRadius    = 2.45;
  this->arecs[89].aNValenceElec = 2;
  this->arecs[89].aElecConf     = {
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
  this->arecs[89].aColorJmol    = vector3<float>(
        0.0,
        0.7294117647058823,
        1.0);
  this->arecs[89].aColorGV      = vector3<float>(
        0.0,
        0.7294117647058823,
        1.0);
  this->arecs[89].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[90].aNumber       = 91;
  this->arecs[90].aName         = "Protactinium";
  this->arecs[90].aSymbol       = "Pa";
  this->arecs[90].aRadius       = 1.61;
  this->arecs[90].aMass         = 231.03588;
  this->arecs[90].aCovRad_Slater= 1.8;
  this->arecs[90].aIonicRadius  = 1.04;
  this->arecs[90].aVdWRadius    = 2.43;
  this->arecs[90].aNValenceElec = 2;
  this->arecs[90].aElecConf     = {
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
  this->arecs[90].aColorJmol    = vector3<float>(
        0.0,
        0.6313725490196078,
        1.0);
  this->arecs[90].aColorGV      = vector3<float>(
        0.0,
        0.6313725490196078,
        1.0);
  this->arecs[90].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[91].aNumber       = 92;
  this->arecs[91].aName         = "Uranium";
  this->arecs[91].aSymbol       = "U";
  this->arecs[91].aRadius       = 1.3800000000000001;
  this->arecs[91].aMass         = 238.02891;
  this->arecs[91].aCovRad_Slater= 1.75;
  this->arecs[91].aIonicRadius  = 1.025;
  this->arecs[91].aVdWRadius    = 2.41;
  this->arecs[91].aNValenceElec = 2;
  this->arecs[91].aElecConf     = {
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
  this->arecs[91].aColorJmol    = vector3<float>(
        0.0,
        0.5607843137254902,
        1.0);
  this->arecs[91].aColorGV      = vector3<float>(
        0.0,
        0.5607843137254902,
        1.0);
  this->arecs[91].aColorCPK     = vector3<float>(
        1.0,
        0.0784313725490196,
        0.5764705882352941);

  this->arecs[92].aNumber       = 93;
  this->arecs[92].aName         = "Neptunium";
  this->arecs[92].aSymbol       = "Np";
  this->arecs[92].aRadius       = 1.3;
  this->arecs[92].aMass         = 237.0;
  this->arecs[92].aCovRad_Slater= 1.75;
  this->arecs[92].aIonicRadius  = 1.1;
  this->arecs[92].aVdWRadius    = 2.39;
  this->arecs[92].aNValenceElec = 2;
  this->arecs[92].aElecConf     = {
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
  this->arecs[92].aColorJmol    = vector3<float>(
        0.0,
        0.5019607843137255,
        1.0);
  this->arecs[92].aColorGV      = vector3<float>(
        0.0,
        0.5019607843137255,
        1.0);
  this->arecs[92].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[93].aNumber       = 94;
  this->arecs[93].aName         = "Plutonium";
  this->arecs[93].aSymbol       = "Pu";
  this->arecs[93].aRadius       = 1.51;
  this->arecs[93].aMass         = 244.0;
  this->arecs[93].aCovRad_Slater= 1.75;
  this->arecs[93].aIonicRadius  = 1.0;
  this->arecs[93].aVdWRadius    = 2.43;
  this->arecs[93].aNValenceElec = 2;
  this->arecs[93].aElecConf     = {
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
  this->arecs[93].aColorJmol    = vector3<float>(
        0.0,
        0.4196078431372549,
        1.0);
  this->arecs[93].aColorGV      = vector3<float>(
        0.0,
        0.4196078431372549,
        1.0);
  this->arecs[93].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[94].aNumber       = 95;
  this->arecs[94].aName         = "Americium";
  this->arecs[94].aSymbol       = "Am";
  this->arecs[94].aRadius       = 1.73;
  this->arecs[94].aMass         = 243.0;
  this->arecs[94].aCovRad_Slater= 1.75;
  this->arecs[94].aIonicRadius  = 1.21;
  this->arecs[94].aVdWRadius    = 2.44;
  this->arecs[94].aNValenceElec = 2;
  this->arecs[94].aElecConf     = {
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
  this->arecs[94].aColorJmol    = vector3<float>(
        0.32941176470588235,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[94].aColorGV      = vector3<float>(
        0.32941176470588235,
        0.3607843137254902,
        0.9490196078431372);
  this->arecs[94].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[95].aNumber       = 96;
  this->arecs[95].aName         = "Curium";
  this->arecs[95].aSymbol       = "Cm";
  this->arecs[95].aRadius       = 2.99;
  this->arecs[95].aMass         = 247.0;
  this->arecs[95].aCovRad_Slater= -0.01;
  this->arecs[95].aIonicRadius  = 0.97;
  this->arecs[95].aVdWRadius    = 2.45;
  this->arecs[95].aNValenceElec = 2;
  this->arecs[95].aElecConf     = {
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
  this->arecs[95].aColorJmol    = vector3<float>(
        0.47058823529411764,
        0.3607843137254902,
        0.8901960784313725);
  this->arecs[95].aColorGV      = vector3<float>(
        0.47058823529411764,
        0.3607843137254902,
        0.8901960784313725);
  this->arecs[95].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[96].aNumber       = 97;
  this->arecs[96].aName         = "Berkelium";
  this->arecs[96].aSymbol       = "Bk";
  this->arecs[96].aRadius       = 2.97;
  this->arecs[96].aMass         = 247.0;
  this->arecs[96].aCovRad_Slater= -0.01;
  this->arecs[96].aIonicRadius  = 0.96;
  this->arecs[96].aVdWRadius    = 2.44;
  this->arecs[96].aNValenceElec = 2;
  this->arecs[96].aElecConf     = {
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
  this->arecs[96].aColorJmol    = vector3<float>(
        0.5411764705882353,
        0.30980392156862746,
        0.8901960784313725);
  this->arecs[96].aColorGV      = vector3<float>(
        0.5411764705882353,
        0.30980392156862746,
        0.8901960784313725);
  this->arecs[96].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[97].aNumber       = 98;
  this->arecs[97].aName         = "Californium";
  this->arecs[97].aSymbol       = "Cf";
  this->arecs[97].aRadius       = 2.95;
  this->arecs[97].aMass         = 251.0;
  this->arecs[97].aCovRad_Slater= -0.01;
  this->arecs[97].aIonicRadius  = 0.9500000000000001;
  this->arecs[97].aVdWRadius    = 2.45;
  this->arecs[97].aNValenceElec = 2;
  this->arecs[97].aElecConf     = {
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
  this->arecs[97].aColorJmol    = vector3<float>(
        0.6313725490196078,
        0.21176470588235294,
        0.8313725490196079);
  this->arecs[97].aColorGV      = vector3<float>(
        0.6313725490196078,
        0.21176470588235294,
        0.8313725490196079);
  this->arecs[97].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[98].aNumber       = 99;
  this->arecs[98].aName         = "Einsteinium";
  this->arecs[98].aSymbol       = "Es";
  this->arecs[98].aRadius       = 2.92;
  this->arecs[98].aMass         = 252.0;
  this->arecs[98].aCovRad_Slater= -0.01;
  this->arecs[98].aIonicRadius  = -0.01;
  this->arecs[98].aVdWRadius    = 2.45;
  this->arecs[98].aNValenceElec = 2;
  this->arecs[98].aElecConf     = {
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
  this->arecs[98].aColorJmol    = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.8313725490196079);
  this->arecs[98].aColorGV      = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.8313725490196079);
  this->arecs[98].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);

  this->arecs[99].aNumber       = 100;
  this->arecs[99].aName         = "Fermium";
  this->arecs[99].aSymbol       = "Fm";
  this->arecs[99].aRadius       = 2.9;
  this->arecs[99].aMass         = 257.0;
  this->arecs[99].aCovRad_Slater= -0.01;
  this->arecs[99].aIonicRadius  = -0.01;
  this->arecs[99].aVdWRadius    = 2.45;
  this->arecs[99].aNValenceElec = 2;
  this->arecs[99].aElecConf     = {
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
  this->arecs[99].aColorJmol    = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.7294117647058823);
  this->arecs[99].aColorGV      = vector3<float>(
        0.7019607843137254,
        0.12156862745098039,
        0.7294117647058823);
  this->arecs[99].aColorCPK     = vector3<float>(
        1.0,
        1.0,
        1.0);
}

void ptable::init_cache_atom_idx(){
  for(int i = 0; i < 100; i++)
    cache_atom_idx[this->arecs[i].aSymbol] = this->arecs[i].aNumber;
}
