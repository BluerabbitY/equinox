/***********************************************************************************
 * \file HeraldApplication.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief herald application
 * \date 2025-11-05 23:34:10
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

#include <QGuiApplication>
#include "inc/hlog.hpp"

class QQmlApplicationEngine;

namespace herald
{

class HeraldTranslator;
class HeraldInit;

class HeraldApplication final : public QGuiApplication
{
  public:
    HeraldApplication(const QString & appName, const QString & version, int &argc, char **argv);

    ~HeraldApplication() override;

public:
    static void preSetup();

    void initHerald() const;

private:
    [[nodiscard]] bool loadTranslaator() const;

    std::unique_ptr<QQmlApplicationEngine> engineM;
    std::unique_ptr<HeraldTranslator> heraldTranslatorM;
    std::unique_ptr<HeraldInit> heraldInitM;
};

} // namespace herald
