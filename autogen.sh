#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# Generate configure and the Makefile.in files from a git checkout.
# Release tarballs already contain them; there, just run ./configure.
set -e
cd "$(dirname "$0")"
exec autoreconf --force --install --warnings=all "$@"
