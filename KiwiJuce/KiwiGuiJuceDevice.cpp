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
    KiwiJuceGuiDeviceManager::KiwiJuceGuiDeviceManager()
    {
        ;
    }
    
    KiwiJuceGuiDeviceManager::~KiwiJuceGuiDeviceManager()
    {
        ;
    }
    
    sGuiView KiwiJuceGuiDeviceManager::createView(sGuiController ctrl) noexcept
    {
        return make_shared<jView>(shared_from_this(), ctrl);
    }
    
    Point KiwiJuceGuiDeviceManager::getMousePosition() const noexcept
    {
        return toKiwi(Desktop::getMousePosition());
    }
    
    Rectangle KiwiJuceGuiDeviceManager::getScreenBounds(Point const& pt) const noexcept
    {
        return toKiwi(Desktop::getInstance().getDisplays().getDisplayContaining(toJuce<int>(pt)).userArea);
    }
    
    Size KiwiJuceGuiDeviceManager::getTextSize(Font const& font, wstring const& text) const noexcept
    {
        juce::Font jfont(font.getName(), (float)font.getSize(), font.getStyle());
        return Size(jfont.getStringWidth(String(text.c_str())), jfont.getHeight());
    }
}

#endif

