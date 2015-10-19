#ifndef _QPP_COMPILE_H
#define _QPP_COMPILE_H
#include <data/qppdata.hpp>

namespace qpp{

  qpp_object * qpp_compile(qpp_object * r);

  void qpp_read_compile(qpp::ISTREAM & is, std::vector<qpp::qpp_object*> & decls, 
			qpp::qpp_array & owner);

  void qpp_read_compile(qpp::ISTREAM & is, qpp::qpp_object* & decl,
			qpp::qpp_array & owner);
};

#endif
