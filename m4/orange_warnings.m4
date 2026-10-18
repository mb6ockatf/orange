# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

AC_DEFUN([ORANGE_WARNINGS],
[AC_REQUIRE([AC_PROG_CXX])dnl
AC_LANG_PUSH([C++])
WARN_CXXFLAGS=
for orange_warning in \
    -Wall -Wextra -Wpedantic \
    -Wshadow -Wconversion -Wold-style-cast -Wcast-align \
    -Wnon-virtual-dtor -Woverloaded-virtual \
    -Wnull-dereference -Wdouble-promotion -Wformat=2 \
    -Wimplicit-fallthrough -Wmissing-declarations
do
  AC_MSG_CHECKING([whether $CXX accepts $orange_warning])
  orange_save_CXXFLAGS=$CXXFLAGS
  CXXFLAGS="$CXXFLAGS -Werror $orange_warning"
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [])],
    [AC_MSG_RESULT([yes])
     WARN_CXXFLAGS="$WARN_CXXFLAGS $orange_warning"],
    [AC_MSG_RESULT([no])])
  CXXFLAGS=$orange_save_CXXFLAGS
done
AC_LANG_POP([C++])
AC_SUBST([WARN_CXXFLAGS])
])
