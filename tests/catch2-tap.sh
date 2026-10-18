#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: 2026 The Orange authors

# Run a Catch2 test program so that it prints TAP for tap-driver.sh.
# automake has no other way to pass arguments to a test program.
exec "$@" --reporter tap
