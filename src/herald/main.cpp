#include <QGuiApplication>

#include "inc/hlog.hpp"
#include "Herald.hpp"

int main(int argc, char *argv[])
{
    using namespace herald;

    // initialization that needs to be performed before creating QApp
    HeraldInit::preApplicationSetup();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);

    const HeraldInit herald;
    herald.initQmlEngine(engine);
    Q_ASSERT(herald.loadFullUi(engine));

    const int ret = app.exec();

    HINFO("Exiting with return code: {}", ret);

    return ret;
}
