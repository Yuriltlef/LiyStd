/**
* SPDX-License-Identifier: LGPL-3.0-only.
 * @file arraylist.hpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议.
 * @version 0.1
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025, Yurilt.
 *
 */
/* includes-------------------------------------------- */
#include <sstream>

#include "liyUtil.hpp"
/* ---------------------------------------------------- */

LiyStd::OutOfRangeException::OutOfRangeException(const char *msg) : std::runtime_error(msg) {
    std::ostringstream _s;
    _s << "OutOfRangeException: " << msg;
    this->msg = std::move(_s.str());
}

const char *LiyStd::OutOfRangeException::what() const noexcept {
    return msg.c_str();
}
