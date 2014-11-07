#ifndef _H_UTILS
#define _H_UTILS

#include <iostream>
#include <QString>
#include <iomanip>
#include <ctime>
#include <string>
namespace  molcad {


/*Default styles */
const QString STYLE_LABEL = "color:white; border: 1px solid black;background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #585858 , stop: 1 #888888)";
const QString STYLE_FANCYBUTTON = "color:white;";

/*XYZ file related*/
const int XYZ_HEADER = 1;
const int XYZ_COMMENT = 2;
const int XYZ_DATA = 3;
const int XYZ_NONE = 4;

/*Log level*/
const int LOG_WARNING = 1;
const int LOG_ERROR   = LOG_WARNING+1;
const int LOG_SYSTEM  = LOG_WARNING+2;
const int LOG_MISC    = LOG_WARNING+3;

/*Obsolete, use LOG*/
void DEBUG_PRINT(std::string dbg);

/*Logging routines*/
void LOG(std::string log,int loglevel=LOG_MISC);
void LOG(QString log,int loglevel=LOG_MISC);

/*Convert log level to string*/
std::string ll2s(int loglevel);
}
#endif
