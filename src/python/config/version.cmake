# SPDX-License-Identifier: BSD-3-Clause
# Copyright Contributors to the OpenEXR Project.

set(PYIMATH_VERSION_MAJOR 3)
set(PYIMATH_VERSION_MINOR 0)
set(PYIMATH_VERSION_PATCH 0)
set(PYIMATH_VERSION       ${PYIMATH_VERSION_MAJOR}.${PYIMATH_VERSION_MINOR}.${PYIMATH_VERSION_PATCH})
set(PYIMATH_VERSION_API   ${PYIMATH_VERSION_MAJOR}_${PYIMATH_VERSION_MINOR})
set(PYIMATH_SOCURRENT 26)
set(PYIMATH_SOREVISION 0)
set(PYIMATH_SOAGE 0)
math(EXPR PYIMATH_SOVERSION "${PYIMATH_SOCURRENT} - ${PYIMATH_SOAGE}")
set(PYIMATH_LIB_VERSION "${PYIMATH_SOVERSION}.${PYIMATH_SOAGE}.${PYIMATH_SOREVISION}")
message(STATUS "Configure PyImath Version: ${PYIMATH_VERSION} Lib API: ${PYIMATH_LIB_VERSION}")
