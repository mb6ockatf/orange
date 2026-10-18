// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#pragma once

#include <expected>
#include <filesystem>
#include <string_view>

namespace orange::client
{

enum class socket_path_error
{
  runtime_dir_unset,
  runtime_dir_not_absolute,
};

std::string_view describe (socket_path_error error) noexcept;

std::expected<std::filesystem::path, socket_path_error>
agent_socket_path (std::string_view runtime_dir);

std::expected<std::filesystem::path, socket_path_error>
agent_socket_path_from_environment ();

}
