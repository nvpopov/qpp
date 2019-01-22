#ifndef QPP_ERRORS_H
#define QPP_ERRORS_H

namespace qpp {

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  void PyIndexError(const char *);
  void PyTypeError(const char *);
  void PyKeyError(const char *);
  void PyValueError(const char *);
  void PyOverflowError(const char *);
  void PySyntaxError(const char *);
  void StopIter();

#endif

  void IndexError(const char *);
  void TypeError(const char *);
  void KeyError(const char *);
  void ValueError(const char *);
  void OverflowError(const char *);
  void SyntaxError(const char *);

};

#endif
