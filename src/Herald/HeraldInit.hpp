/***********************************************************************************
 * \file HeraldInit.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2025-10-12 00:18:56
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

#include <QQmlApplicationEngine>

namespace herald
{

class HeraldInit final
{
  public:
    HeraldInit();
    ~HeraldInit();

    static void preApplicationSetup();

    void initQmlEngine(QQmlEngine &engine) const;

    bool loadFullUi(QQmlApplicationEngine &engine) const;

  private:
    class Impl;
    std::unique_ptr<Impl> implM;
};

} // namespace herald
