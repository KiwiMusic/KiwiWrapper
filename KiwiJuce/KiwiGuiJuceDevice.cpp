/*
 ==============================================================================
 
 This file is part of the KIWI library.
 Copyright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
*/

#ifdef __KIWI_JUCE_WRAPPER__

#include "KiwiGuiJuceDevice.h"

namespace Kiwi
{
    KiwiJuceGuiDeviceManager::KiwiJuceGuiDeviceManager() noexcept :
    m_command_manager(make_shared<ApplicationCommandManager>())
    {
        ;
    }
    
    KiwiJuceGuiDeviceManager::~KiwiJuceGuiDeviceManager() noexcept
    {
        ;
    }
    
    GuiPatcher::sView KiwiJuceGuiDeviceManager::createView(sGuiPatcher patcher)
    {
        return make_shared<jPatcher>(patcher);
    }
}

#endif

