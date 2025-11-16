/***********************************************************************************
 * \file Log.h
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief log service
 * \date 2025-10-12 13:46:48
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

#include <memory>

#include "spdlog/common.h"

namespace spdlog
{
class async_logger;

namespace details
{
class thread_pool;
}
} // namespace spdlog

namespace herald::common
{

class LogService
{
public:
    LogService(const std::string &header, const std::string &filePath, int fileMaxSize = 10 /* MB */,
               int fileMaxCount = 3, std::size_t queueSize = 512, std::size_t threadCount = 2);
    ~LogService();

    using level = spdlog::level::level_enum;
    void setDisplayLevel(level level = level::debug) const;
    void setFlushStrategy(level level = level::info) const;

    static void setDefaultLogger(LogService logger);

    static void shutdown();

private:
    std::shared_ptr<spdlog::details::thread_pool> threadPoolM;
    std::shared_ptr<spdlog::async_logger> loggerM;
};

} // namespace herald::common
