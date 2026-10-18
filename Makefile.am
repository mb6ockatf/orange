# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# One non-recursive Makefile: each component keeps its rules in its own
# local.mk, so people working on different components rarely touch the
# same file, and "make -j" sees the whole dependency graph.

AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir) -I$(top_srcdir)/lib/include
AM_CXXFLAGS = $(WARN_CXXFLAGS) $(SANITIZER_FLAGS)
AM_LDFLAGS = $(SANITIZER_FLAGS)

bin_PROGRAMS =
sbin_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
check_PROGRAMS =
TESTS =
EXTRA_DIST = autogen.sh COPYING.AGPL COPYING.DOC COPYING.LESSER CONTRIBUTING.md
dist_man_MANS =

DISTCHECK_CONFIGURE_FLAGS = --enable-werror
# Build HTML instead of DVI during distcheck, so it does not need TeX.
AM_DISTCHECK_DVI_TARGET = html

include lib/local.mk
include server/local.mk
include client/local.mk
include tests/local.mk
include docs/local.mk
