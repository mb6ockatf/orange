// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include "client/core/socket_path.hpp"

#include <catch2/catch_test_macros.hpp>

#include <filesystem>

using orange::client::agent_socket_path;
using orange::client::describe;
using orange::client::socket_path_error;

TEST_CASE ("the agent socket lives under the runtime directory")
{
  auto const socket_path = agent_socket_path ("/run/user/1000");
  REQUIRE (socket_path.has_value ());
  CHECK (*socket_path
         == std::filesystem::path ("/run/user/1000/orange/agent.sock"));
}

TEST_CASE ("an empty runtime directory is rejected")
{
  auto const socket_path = agent_socket_path ("");
  REQUIRE_FALSE (socket_path.has_value ());
  CHECK (socket_path.error () == socket_path_error::runtime_dir_unset);
}

TEST_CASE ("a relative runtime directory is rejected")
{
  auto const socket_path = agent_socket_path ("run/user/1000");
  REQUIRE_FALSE (socket_path.has_value ());
  CHECK (socket_path.error () == socket_path_error::runtime_dir_not_absolute);
}

TEST_CASE ("every socket path error has a description")
{
  CHECK_FALSE (describe (socket_path_error::runtime_dir_unset).empty ());
  CHECK_FALSE (
      describe (socket_path_error::runtime_dir_not_absolute).empty ());
}
