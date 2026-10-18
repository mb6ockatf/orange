# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# The Texinfo manual is the main documentation; the man pages are short
# references that point to it.  Man pages are added to dist_man_MANS by
# server/local.mk and client/local.mk, so they install only with their
# component.

info_TEXINFOS = docs/orange.texi
docs_orange_TEXINFOS = docs/fdl.texi
