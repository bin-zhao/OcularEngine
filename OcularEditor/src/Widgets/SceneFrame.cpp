/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdafx.h"

#include "Widgets/SceneFrame.hpp"
#include "Widgets/SceneBox.hpp"
#include "Widgets/SceneTree.hpp"
#include "Widgets/ConsoleBox.hpp"
#include "Widgets/ConsoleText.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneFrame::SceneFrame(QWidget *parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
            setFrameStyle(QFrame::Panel | QFrame::Plain);
            setStyleSheet(GeneralStyles::frameStyle);
            setLineWidth(0);

            m_SceneBox = new SceneBox();
            m_ConsoleBox = new ConsoleBox();
            
            m_Splitter = new QSplitter();
            m_Splitter->setOrientation(Qt::Vertical);
            m_Splitter->addWidget(m_SceneBox);
            m_Splitter->addWidget(m_ConsoleBox);
            m_Splitter->setStretchFactor(0, 1);      // When window is resized, the scene tree will take the majority of the stretch difference
                                                     // leaving the console box relatively the same size
            m_Layout = new QVBoxLayout();
            m_Layout->addWidget(m_Splitter);
            m_Layout->setContentsMargins(0, 0, 0, 0);

            setLayout(m_Layout);
        }

        SceneFrame::~SceneFrame()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize SceneFrame::sizeHint() const
        {
            return QSize(325, 700);
        }

        SceneTree* SceneFrame::getSceneTree() const
        {
            return m_SceneBox->getSceneTree();
        }

        ConsoleText* SceneFrame::getConsoleText() const
        {
            return m_ConsoleBox->getConsoleText();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}