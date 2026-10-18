// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include "client/core/socket_path.hpp"

#include <orange/version.hpp>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <print>
#include <span>
#include <string_view>

namespace
{

constexpr std::string_view program_name = "orange-agent";
constexpr int exit_usage = 2;

void
print_help ()
{
  std::println ("Usage: {} [OPTION]...", program_name);
  std::println ("Keep XMPP sessions open for orange-cli and serve them on a "
                "unix socket.");
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
  std::println ("License GPLv3+: GNU GPL version 3 or later "
                "<https://gnu.org/licenses/gpl.html>.");
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

  auto const socket_path
      = orange::client::agent_socket_path_from_environment ();
  if (!socket_path)
    {
      std::println (stderr, "{}: {}", program_name,
                    orange::client::describe (socket_path.error ()));
      return EXIT_FAILURE;
    }

  std::println (stderr,
                "{}: would listen on {}, but the agent is not implemented yet",
                program_name, socket_path->string ());
  return EXIT_FAILURE;
}
