#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# Every program must answer --help and --version.  Gnits strictness checks
# this on installed programs in "make installcheck"; this test catches it
# earlier, in "make check", on the programs in the build tree.
# ORANGE_PROGRAMS and PACKAGE_VERSION come from AM_TESTS_ENVIRONMENT.

status=0

for program in $ORANGE_PROGRAMS; do
  "./$program" --help >/dev/null || {
    echo "FAIL: $program --help exited with status $?"
    status=1
  }
  version_output=$("./$program" --version) || {
    echo "FAIL: $program --version exited with status $?"
    status=1
    continue
  }
  case $version_output in
    *"$PACKAGE_VERSION"*) echo "ok: $program" ;;
    *) echo "FAIL: $program --version does not mention $PACKAGE_VERSION"
       status=1 ;;
  esac
done

exit $status
