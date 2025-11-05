/***********************************************************************************
 * \file Herald.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-10-12 00:35:11
 *
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 ***********************************************************************************/
#include "HeraldInit.hpp"

#include "inc/hlog.hpp"
#include "log/log.h"

#include <husapp.h>

#include <QQuickWindow>
#include <qqmlcontext.h>

#include "addDefaultImportPaths.hpp"

inline void heraldInitResource()
{
    Q_INIT_RESOURCE(herald);
    Q_INIT_RESOURCE(images);
    Q_INIT_RESOURCE(main);
}

inline void heraldCleanResource()
{
    Q_CLEANUP_RESOURCE(herald);
    Q_CLEANUP_RESOURCE(images);
    Q_CLEANUP_RESOURCE(main);
}

namespace herald
{

namespace
{

void heraldLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static auto *logWriter = spdlog::default_logger_raw();

    QString category = context.category;
    const bool userLogging = category == "USR";

    const auto logLevel = [type, userLogging]() -> common::LogService::level {
        if (userLogging)
        {
            return common::LogService::level::err;
        }
        switch (type)
        {
        case QtDebugMsg:
            return common::LogService::level::debug;
        case QtInfoMsg:
            return common::LogService::level::info;
        case QtWarningMsg:
            return common::LogService::level::warn;
        case QtCriticalMsg:
            return common::LogService::level::err;
        case QtFatalMsg:
            return common::LogService::level::critical;
        }
        HERROR("Unexpected QtMsgType: {}", static_cast<int>(type));

        return common::LogService::level::err;
    }();

    QString finalMessage = msg;

    if (category.length() > 0 && category != "default" && !userLogging)
    {
        finalMessage = QString("%1: %2").arg(category, finalMessage);
    }

    // const char *tag = userLogging ? "USR" : logLevel;
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    logWriter->log(spdlog::source_loc{file, context.line, function}, logLevel, "{}",
                   finalMessage.toLocal8Bit().constData());
}

} // namespace

class HeraldInit::Impl final
{
  public:
    Impl()
    {
        registerQmlTypes();
    }

    ~Impl()
    {
    }

    void initQmlEngine(QQmlEngine &engine)
    {
        HusApp::initialize(&engine);
        addDefaultImportPaths(engine);
    }

    bool loadFullUi(QQmlApplicationEngine &engine)
    {
        const QString mainQmlFile = QStringLiteral("qrc:/herald/main.qml");
        engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
        engine.load(QUrl(mainQmlFile));
        return !engine.rootObjects().isEmpty();
    }

  private:
    void registerQmlTypes()
    {
        heraldInitResource();
    }
};

HeraldInit::HeraldInit() : implM{std::make_unique<Impl>()}
{
}

HeraldInit::~HeraldInit() = default;

void HeraldInit::preApplicationSetup()
{
    static const common::LogService logServiceS{"herald", "log/herald.log"};
    common::LogService::setDefaultLogger(logServiceS);

    qInstallMessageHandler(heraldLogger);

    QQuickWindow::setDefaultAlphaBuffer(true);

    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES, true);
}

void HeraldInit::initQmlEngine(QQmlEngine &engine) const
{
    implM->initQmlEngine(engine);
}

bool HeraldInit::loadFullUi(QQmlApplicationEngine &engine) const
{
    return implM->loadFullUi(engine);
}

} // namespace herald
