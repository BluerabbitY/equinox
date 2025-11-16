/***********************************************************************************
 * \file Hlog.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief log
 * \date 2025-10-12 16:09:15
 *
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 ***********************************************************************************/
#pragma once

#include <cassert>

#ifndef CMAKE_BUILD_TYPE
#define CMAKE_BUILD_TYPE 1
#endif

#ifndef SPDLOG_ACTIVE_LEVEL
#if CMAKE_BUILD_TYPE == 0
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif
#endif

#include "spdlog/spdlog.h"

#define HTRACE(...)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        SPDLOG_TRACE(__VA_ARGS__);                                                                                     \
    } while (0)

#define HDEBUG(...)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        SPDLOG_DEBUG(__VA_ARGS__);                                                                                     \
    } while (0)

#define HINFO(...)                                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        SPDLOG_INFO(__VA_ARGS__);                                                                                      \
    } while (0)

#define HWARN(...)                                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        SPDLOG_WARN(__VA_ARGS__);                                                                                      \
    } while (0)

#define HERROR(...)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        SPDLOG_ERROR(__VA_ARGS__);                                                                                     \
    } while (0)

#define HFATAL(...)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        SPDLOG_CRITICAL(__VA_ARGS__);                                                                                  \
        spdlog::assert(false);                                                                                         \
    } while (0)
