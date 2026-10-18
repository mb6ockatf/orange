// SPDX-License-Identifier: LGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include <orange/version.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE ("liborange reports the package version")
{
  CHECK (orange::version () == PACKAGE_VERSION);
}
