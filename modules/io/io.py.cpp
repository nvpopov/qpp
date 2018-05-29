#include "io.py.hpp"
#include <io/geomio.hpp>
//#include <io/gmsio.hpp>

#ifdef PY_EXPORT

void qpp_io_export()
{
  qpp::qpp_export_ioxyz();
//  qpp::qpp_export_gmsio();
}

#endif
