# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# Unit tests are Catch2 programs without an extension.  They run through
# catch2-tap.sh (which adds --reporter tap) and automake's TAP driver, so
# every test case shows up in the .log file.  Shell tests (.sh) use the
# plain exit-status driver.

TEST_EXTENSIONS = .sh
LOG_COMPILER = $(SHELL) $(top_srcdir)/tests/catch2-tap.sh
LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh
SH_LOG_COMPILER = $(SHELL)

# verify_asan_link_order=0: with --enable-sanitizers, ASan refuses to start
# when something in LD_PRELOAD (such as libgtk3-nocsd on some desktops)
# loads before its runtime.  It has no effect without ASan.
AM_TESTS_ENVIRONMENT = \
	ORANGE_PROGRAMS='$(sbin_PROGRAMS) $(bin_PROGRAMS)'; \
	PACKAGE_VERSION='$(PACKAGE_VERSION)'; \
	ASAN_OPTIONS="verify_asan_link_order=0$${ASAN_OPTIONS:+:$$ASAN_OPTIONS}"; \
	export ORANGE_PROGRAMS PACKAGE_VERSION ASAN_OPTIONS;

TESTS += tests/std-options.sh
EXTRA_DIST += tests/catch2-tap.sh tests/std-options.sh

if HAVE_CATCH2
check_PROGRAMS += tests/liborange-tests
TESTS += tests/liborange-tests
if ENABLE_CLIENT
check_PROGRAMS += tests/client-core-tests
TESTS += tests/client-core-tests
endif
endif

tests_liborange_tests_SOURCES = tests/version_test.cpp
tests_liborange_tests_CXXFLAGS = $(AM_CXXFLAGS) $(CATCH2_CFLAGS)
tests_liborange_tests_LDADD = lib/liborange.la $(CATCH2_LIBS)

tests_client_core_tests_SOURCES = tests/socket_path_test.cpp
tests_client_core_tests_CXXFLAGS = $(AM_CXXFLAGS) $(CATCH2_CFLAGS)
tests_client_core_tests_LDADD = client/core/libclientcore.la $(CATCH2_LIBS)
