#ifndef _QPPERRORS_H
#define _QPPERRORS_H

namespace qpp{

#ifdef PY_EXPORT

  void PyIndexError(const char *);
  void PyTypeError(const char *);
  void PyKeyError(const char *);
  void StopIter();

#endif

  void IndexError(const char *);
  void TypeError(const char *);
  void KeyError(const char *);

};

#endif
