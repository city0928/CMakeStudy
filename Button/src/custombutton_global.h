#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CUSTOMBUTTON_LIB)
#  define CUSTOMBUTTON_EXPORT Q_DECL_EXPORT
# else
#  define CUSTOMBUTTON_EXPORT Q_DECL_IMPORT
# endif
#else
# define CUSTOMBUTTON_EXPORT
#endif
