// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include "client/repl/repl.hpp"

#include <orange/version.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <print>
#include <span>
#include <string_view>

namespace
{

constexpr std::string_view program_name = "orange-cli";
constexpr int exit_usage = 2;

struct command
{
  std::string_view name;
  std::string_view summary;
};

constexpr std::array commands{
  command{ "send", "send a message" },
  command{ "roster", "show the contact list" },
  command{ "log", "show message history" },
  command{ "listen", "print incoming events as they arrive" },
  command{ "repl", "start an interactive session (the default)" },
};

void
print_help ()
{
  std::println ("Usage: {} [OPTION]... [COMMAND [ARGUMENT]...]", program_name);
  std::println ("Use XMPP from the command line, through orange-agent.");
  std::println ("");
  std::println ("Commands:");
  for (command const &entry : commands)
    std::println ("  {:<8} {}", entry.name, entry.summary);
  std::println ("");
  std::println ("Options:");
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

int
usage_error (std::string_view message)
{
  std::println (stderr, "{}: {}", program_name, message);
  std::println (stderr, "Try '{} --help' for more information.", program_name);
  return exit_usage;
}

}

int
main (int argc, char **argv)
{
  std::span arguments (argv, static_cast<std::size_t> (argc));
  if (!arguments.empty ())
    arguments = arguments.subspan (1);

  if (arguments.empty ())
    return orange::repl::run ();

  std::string_view const first = arguments.front ();
  if (first == "--help")
    {
      print_help ();
      return EXIT_SUCCESS;
    }
  if (first == "--version")
    {
      print_version ();
      return EXIT_SUCCESS;
    }
  if (first.starts_with ('-'))
    return usage_error (std::format ("unrecognized option '{}'", first));

  auto const found = std::ranges::find (commands, first, &command::name);
  if (found == commands.end ())
    return usage_error (std::format ("unknown command '{}'", first));

  if (found->name == "repl")
    return orange::repl::run ();

  std::println (stderr, "{}: {}: not implemented yet", program_name,
                found->name);
  return EXIT_FAILURE;
}
