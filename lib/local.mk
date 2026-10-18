# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# liborange: protocol code shared by the server and the client.
# LGPL-3.0-or-later.

lib_LTLIBRARIES += lib/liborange.la
lib_liborange_la_SOURCES = lib/version.cpp
lib_liborange_la_CPPFLAGS = $(AM_CPPFLAGS) $(EXPAT_CFLAGS) $(OPENSSL_CFLAGS)
lib_liborange_la_LIBADD = $(EXPAT_LIBS) $(OPENSSL_LIBS)
# Bump by the libtool rules (current:revision:age) at each release that
# changes the library; see "Updating version info" in the libtool manual.
lib_liborange_la_LDFLAGS = $(AM_LDFLAGS) -version-info 0:0:0 -no-undefined

orangeincludedir = $(includedir)/orange
orangeinclude_HEADERS = lib/include/orange/version.hpp

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = lib/liborange.pc
