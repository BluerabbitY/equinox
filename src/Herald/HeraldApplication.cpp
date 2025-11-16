/***********************************************************************************
 * \file HeraldApplication.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-11-05 23:35:12
 *
 * \copyright Copyright (C) 2025 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 *
 ***********************************************************************************/
#include "HeraldApplication.hpp"
#include "HeraldInit.hpp"
#include "HeraldTranslator.hpp"

namespace herald
{

HeraldApplication::HeraldApplication(const QString &appName, const QString &version, int &argc, char **argv)
    : QGuiApplication{argc, argv}
{
    setApplicationName(appName);
    setApplicationVersion(version);

    engineM = std::make_unique<QQmlApplicationEngine>();
    heraldTranslatorM = std::make_unique<HeraldTranslator>();
    heraldInitM = std::make_unique<HeraldInit>();
}

HeraldApplication::~HeraldApplication()
{
    heraldTranslatorM.reset();
}

void HeraldApplication::preSetup()
{
    HeraldInit::preApplicationSetup();
}

void HeraldApplication::initHerald() const
{
    HINFO("App: {}, platform: {}, version: {}", applicationName().toStdString(), platformName().toStdString(),
          applicationVersion().toStdString());
    Q_ASSERT(loadTranslaator());
    heraldInitM->initQmlEngine(*engineM);
    engineM->retranslate();
    Q_ASSERT(heraldInitM->loadFullUi(*engineM));
}

bool HeraldApplication::loadTranslaator() const
{
    if (!heraldTranslatorM->load(QLocale::system(), QLocale::system().name(), "", applicationDirPath() + "/i18n",
                                 ".qm"))
    {
        HWARN("Error loading translator file: {}.qm, try to set default", QLocale::system().name().toStdString());

        if (!heraldTranslatorM->load("en_US", "", applicationDirPath() + "/i18n", ".qm"))
        {
            HERROR("Error loading translator file: {}.qm", QLocale::system().name().toStdString());
            return false;
        }
    }

    return installTranslator(heraldTranslatorM.get());
}

} // namespace herald
