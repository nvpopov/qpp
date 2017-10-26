#include "io.py.hpp"
#include <io/geomio.hpp>

#ifdef PY_EXPORT

void qpp_io_export()
{
  qpp::qpp_export_ioxyz();
}

#endif
