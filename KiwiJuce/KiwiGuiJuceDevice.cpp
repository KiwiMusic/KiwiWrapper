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
        if(ctrl->wantKeyboard() && !ctrl->wantActions())
        {
            //return make_shared<jViewTextInput>(shared_from_this(), ctrl);
        }
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
    
    vector<Font> KiwiJuceGuiDeviceManager::getSystemFonts() const noexcept
    {
        vector<Font>        fonts;
        Array<juce::Font>   results;
        juce::Font::findFonts(results);
        for(int i = 0; i < results.size(); i++)
        {
            fonts.push_back(Font(results.getUnchecked(i).getTypefaceName().toStdString()));
        }
        return fonts;
    }
    
    double KiwiJuceGuiDeviceManager::getLineWidth(Font const& font, string const& line) const noexcept
    {
        juce::Font jfont(font.getName(), float(font.getHeight()), font.getStyle());
        return jfont.getStringWidth(String(line.c_str()));
    }
    
    double KiwiJuceGuiDeviceManager::getLineWidth(Font const& font, wstring const& line) const noexcept
    {
        juce::Font jfont(font.getName(), float(font.getHeight()), font.getStyle());
        return jfont.getStringWidth(String(line.c_str()));
    }
    
    Size KiwiJuceGuiDeviceManager::getTextSize(Font const& font, string const& text, const double width) const noexcept
    {
        juce::GlyphArrangement glypher;
        glypher.addJustifiedText(juce::Font(font.getName(), float(font.getHeight()), font.getStyle()), String(text.c_str()), 0., 0., width > 0. ? width : numeric_limits<float>::max(), juce::Justification::left);
        const juce::Rectangle<float> bounds = glypher.getBoundingBox(0, -1, true);
        return Size(bounds.getWidth(), bounds.getHeight());
    }
    
    Size KiwiJuceGuiDeviceManager::getTextSize(Font const& font, wstring const& text, const double width) const noexcept
    {
        juce::GlyphArrangement glypher;
        glypher.addJustifiedText(juce::Font(font.getName(), float(font.getHeight()), font.getStyle()), String(text.c_str()), 0., 0., width > 0. ? width : numeric_limits<float>::max(), juce::Justification::left);
        const juce::Rectangle<float> bounds = glypher.getBoundingBox(0, -1, true);
        return Size(bounds.getWidth(), bounds.getHeight());
    }
}

#endif

