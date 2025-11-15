#include "HeraldApplication.hpp"

int main(int argc, char *argv[])
{
    using namespace herald;

    // initialization that needs to be performed before creating QApp
    HeraldApplication::preSetup();

    const HeraldApplication app(APP_NAME, APP_VERSION, argc, argv);

    app.initHerald();

    const int ret = app.exec();

    HINFO("Exiting with return code: {}", ret);

    return ret;
}
