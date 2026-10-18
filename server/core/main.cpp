// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors
#include <config.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <orange/version.hpp>
#include <print>
#include <span>
#include <string_view>

namespace
{

constexpr std::string_view program_name = "oranged";
constexpr int exit_usage = 2;

void
print_help ()
{
  std::println ("Usage: {} [OPTION]...", program_name);
  std::println ("Run the Orange XMPP server.");
  std::println ("");
  std::println ("      --help     display this help and exit");
  std::println ("      --version  output version information and exit");
  std::println ("");
  std::println ("Report bugs to: <{}>", PACKAGE_BUGREPORT);
  std::println ("{} home page: <{}>", PACKAGE_NAME, PACKAGE_URL);
}

void
print_version ()
{
  std::println ("{} ({}) {}", program_name, PACKAGE_NAME, orange::version ());
  std::println ("Copyright (C) 2026 The Orange authors");
  std::println ("License AGPLv3+: GNU AGPL version 3 or later "
                "<https://gnu.org/licenses/agpl.html>.");
  std::println (
      "This is free software: you are free to change and redistribute it.");
  std::println ("There is NO WARRANTY, to the extent permitted by law.");
}

}

int
main (int argc, char **argv)
{
  std::span arguments (argv, static_cast<std::size_t> (argc));
  if (!arguments.empty ())
    arguments = arguments.subspan (1);

  for (std::string_view argument : arguments)
    {
      if (argument == "--help")
        {
          print_help ();
          return EXIT_SUCCESS;
        }
      if (argument == "--version")
        {
          print_version ();
          return EXIT_SUCCESS;
        }
      std::println (stderr, "{}: unrecognized argument '{}'", program_name,
                    argument);
      std::println (stderr, "Try '{} --help' for more information.",
                    program_name);
      return exit_usage;
    }

  std::println (stderr, "{}: the server is not implemented yet", program_name);
  return EXIT_FAILURE;
}
