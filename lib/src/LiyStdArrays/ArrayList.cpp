/**
 * SPDX-License-Identifier: LGPL-3.0-only.
 * @file ArrayList.cpp
 * @author Yurilt (yurilt15312@outlook.com)
 * @brief 这是LiyStd库的一部分,遵循 LGPLv3协议. 
 * @version 0.1
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025, Yurilt.
 * 
 */
/* includes-------------------------------------------- */
#include "ArrayList.hpp"
/* ---------------------------------------------------- */

template class LiyStd::ArrayListVirtual<int>;
template class LiyStd::ArrayListVirtual<LiyStd::LiySizeType>;
template class LiyStd::ArrayListVirtual<float>;
template class LiyStd::ArrayListVirtual<double>;
template class LiyStd::ArrayListVirtual<std::string>;
template class LiyStd::ArrayListVirtual<const char*>;