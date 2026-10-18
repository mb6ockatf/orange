// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include "client/repl/repl.hpp"

#include <cstdio>
#include <cstdlib>
#include <print>

namespace orange::repl
{

int
run ()
{
  std::println (stderr, "orange-cli: interactive mode is not implemented yet");
  return EXIT_FAILURE;
}

}
