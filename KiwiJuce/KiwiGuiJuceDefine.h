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

#ifndef __DEF_KIWI_GUI_JUCE_DEFINE__
#define __DEF_KIWI_GUI_JUCE_DEFINE__

#include "../../KiwiGui/KiwiGui.h"
#include <JuceHeader.h>

namespace Kiwi
{
    typedef shared_ptr<ApplicationCommandManager> sDeviceCommandManager;
    
    template<typename type> static inline juce::Point<type> toJuce(Kiwi::Point const& pt) noexcept
    {
        return juce::Point<type>((type)pt.x(), (type)pt.y());
    }
    
    template<typename type> static inline Kiwi::Point toKiwi(juce::Point<type> const& rect) noexcept
    {
        return Kiwi::Point(rect.getX(), rect.getY());
    }
    
    template<typename type> static inline juce::Rectangle<type> toJuce(Kiwi::Rectangle const& rect) noexcept
    {
        return juce::Rectangle<type>((type)rect.x(), (type)rect.y(), (type)rect.width(), (type)rect.height());
    }
    
    template<typename type> static inline Kiwi::Rectangle toKiwi(juce::Rectangle<type> const& rect) noexcept
    {
        return Kiwi::Rectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
    }
    
    static inline juce::Colour toJuce(Kiwi::Color const& color) noexcept
    {
        return Colour::fromFloatRGBA(color.red(), color.green(), color.blue(), color.alpha());
    }
    
    static inline Kiwi::Color toKiwi(juce::Colour const& color) noexcept
    {
        return Kiwi::Color(color.getFloatRed(), color.getFloatGreen(), color.getFloatBlue(), color.getFloatAlpha());
    }
}

#endif

#endif


