# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# oranged: the XMPP server.  AGPL-3.0-or-later.
#
#   server/core/     connections, stream negotiation, routing, sessions
#   server/modules/  one module per XEP, behind the module interface
#   server/storage/  storage interface and its backends (SQLite first)

if ENABLE_SERVER
sbin_PROGRAMS += server/oranged
dist_man_MANS += docs/oranged.8
endif

server_oranged_SOURCES = server/core/main.cpp
server_oranged_CPPFLAGS = $(AM_CPPFLAGS) $(SQLITE3_CFLAGS)
server_oranged_LDADD = lib/liborange.la $(SQLITE3_LIBS)
