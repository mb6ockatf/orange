# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

AC_DEFUN([ORANGE_CXX23],
[AC_REQUIRE([AC_PROG_CXX])dnl
AC_LANG_PUSH([C++])
CXX=`AS_ECHO(["$CXX"]) | sed 's/ -std=[[^ ]]*//g'`
AC_CACHE_CHECK([for $CXX option to enable C++23], [orange_cv_cxx23],
[orange_cv_cxx23=no
orange_save_CXX=$CXX
for orange_std_option in '' -std=c++23 -std=c++2b; do
  CXX="$orange_save_CXX${orange_std_option:+ $orange_std_option}"
  AC_LINK_IFELSE([_ORANGE_CXX23_PROGRAM],
    [orange_cv_cxx23=${orange_std_option:-none needed}
     break])
done
CXX=$orange_save_CXX])
AC_LANG_POP([C++])
AS_CASE([$orange_cv_cxx23],
  [no], [AC_MSG_ERROR([$CXX cannot compile C++23 with <expected> and <print>; GCC 14 or Clang 18 (with libstdc++ 14) or newer is required])],
  ["none needed"], [],
  [CXX="$CXX $orange_cv_cxx23"])
])

m4_define([_ORANGE_CXX23_PROGRAM],
[AC_LANG_SOURCE([[
#include <expected>
#include <print>
#include <string_view>

#if !defined __cpp_lib_expected || __cpp_lib_expected < 202211L
# error "std::expected with monadic operations is required"
#endif
#if !defined __cpp_lib_print || __cpp_lib_print < 202207L
# error "std::print is required"
#endif

struct counter
{
  int value = 0;
  int get (this counter const &self) { return self.value; }
};

static std::expected<int, std::string_view>
parse (std::string_view text)
{
  if (text.empty ())
    return std::unexpected (text);
  return static_cast<int> (text.size ());
}

int
main ()
{
  counter fallback;
  auto result = parse ("abc").and_then (
    [] (int length) -> std::expected<int, std::string_view> {
      return length + 1;
    });
  std::println ("{}", result.value_or (fallback.get ()));
  return 0;
}
]])])
