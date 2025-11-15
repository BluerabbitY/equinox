/***********************************************************************************
 * \file log.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief log service
 * \date 2025-10-12 13:57:15
 *
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 ***********************************************************************************/
#include "log.h"

#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace herald::common
{

namespace
{
class Formatter final : public spdlog::custom_flag_formatter
{
  public:
    void format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest) override
    {
        static const std::unordered_map<spdlog::level::level_enum, std::string> nameTable = {
            {spdlog::level::trace, "TRA"}, {spdlog::level::debug, "DBG"}, {spdlog::level::info, "NFO"},
            {spdlog::level::warn, "WRN"},  {spdlog::level::err, "ERR"},   {spdlog::level::critical, "FTL"},
            {spdlog::level::off, "OFF"},
        };

        if (const auto itr = nameTable.find(msg.level); itr != nameTable.end())
        {
            dest.append(itr->second.data(), itr->second.data() + itr->second.size());
        }
        else
        {
            dest.push_back('?');
        }
    }

    std::unique_ptr<custom_flag_formatter> clone() const override
    {
        return spdlog::details::make_unique<Formatter>();
    }
};
} // namespace

LogService::LogService(const std::string &header, const std::string &filePath, int fileMaxSize, int fileMaxCount,
                       std::size_t queueSize, std::size_t threadCount)
{
    threadPoolM = std::make_unique<spdlog::details::thread_pool>(queueSize, threadCount);
    const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    const auto rotatingSink =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filePath, fileMaxSize * 1024 * 1024, fileMaxCount);

    std::vector<spdlog::sink_ptr> sinks{consoleSink, rotatingSink};

    loggerM = std::make_shared<spdlog::async_logger>(header, sinks.begin(), sinks.end(), threadPoolM,
                                                     spdlog::async_overflow_policy::block);
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<Formatter>('L');
    formatter->set_pattern("%Y-%m-%d %H:%M:%S.%e %n[%P]: <%^%L%$>|%v|%s:%#|t:%t|%!");
    loggerM->set_formatter(std::move(formatter));

    loggerM->set_level(spdlog::level::debug);
    loggerM->flush_on(spdlog::level::info);
}

LogService::~LogService()
{
    loggerM->flush();
}

void LogService::setDisplayLevel(level level) const
{
    loggerM->set_level(level);
}

void LogService::setFlushStrategy(level level) const
{
    loggerM->flush_on(level);
}

void LogService::setDefaultLogger(LogService logger)
{
    spdlog::set_default_logger(logger.loggerM);
}

void LogService::shutdown()
{
    spdlog::shutdown();
}

} // namespace herald::common
