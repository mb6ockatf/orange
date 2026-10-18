// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include "client/core/socket_path.hpp"

#include <cstdlib>

namespace orange::client
{

std::string_view
describe (socket_path_error error) noexcept
{
  switch (error)
    {
    case socket_path_error::runtime_dir_unset:
      return "XDG_RUNTIME_DIR is not set";
    case socket_path_error::runtime_dir_not_absolute:
      return "XDG_RUNTIME_DIR is not an absolute path";
    }
  return "unknown error";
}

std::expected<std::filesystem::path, socket_path_error>
agent_socket_path (std::string_view runtime_dir)
{
  if (runtime_dir.empty ())
    return std::unexpected (socket_path_error::runtime_dir_unset);

  std::filesystem::path base (runtime_dir);
  if (!base.is_absolute ())
    return std::unexpected (socket_path_error::runtime_dir_not_absolute);

  return base / "orange" / "agent.sock";
}

std::expected<std::filesystem::path, socket_path_error>
agent_socket_path_from_environment ()
{
  char const *runtime_dir = std::getenv ("XDG_RUNTIME_DIR");
  return agent_socket_path (runtime_dir == nullptr ? std::string_view ()
                                                   : runtime_dir);
}

}
