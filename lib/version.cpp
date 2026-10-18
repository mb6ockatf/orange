// SPDX-License-Identifier: LGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 The Orange authors

#include <config.h>

#include "orange/version.hpp"

namespace orange
{

std::string_view
version () noexcept
{
  return PACKAGE_VERSION;
}

}
