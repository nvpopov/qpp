#include <utils.hpp>

void DEBUG_PRINT(std::string dbg){
	std::cout<<std::endl<<"DEBUG::"<<std::endl<<dbg<<std::endl<<std::flush;
}

std::string get_time(){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	return std::string(buffer);
}

void LOG(std::string log,int loglevel){
	std::cout<<"***"<<get_time()<<"::"<<molcad::ll2s(loglevel)<<"::"<<log<<"***"<<std::flush<<std::endl;
}

void LOG(QString log,int loglevel){
	LOG(log.toStdString(),loglevel);
}

std::string molcad::ll2s(int loglevel){
	switch(loglevel){
	case(molcad::LOG_ERROR):return "ERROR";
	case(molcad::LOG_MISC):return "MISC";
	case(molcad::LOG_SYSTEM):return "SYSTEM";
	case(molcad::LOG_WARNING):return "WARNING";
	default:return "UNKNOWN";
	}
}
