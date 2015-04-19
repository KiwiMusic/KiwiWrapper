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

#ifndef __DEF_KIWI_GUI_JUCE_EVENT__
#define __DEF_KIWI_GUI_JUCE_EVENT__

#include "KiwiGuiJuceDefine.h"

namespace Kiwi
{
    
    template<typename type> static inline juce::Point<type> toJuce(Kiwi::Point const& pt) noexcept {
        return juce::Point<type>((type)pt.x(), (type)pt.y());
    }
    
    template<typename type> static inline Kiwi::Point toKiwi(juce::Point<type> const& rect) noexcept {
        return Kiwi::Point(rect.getX(), rect.getY());
    }
    
    template<typename type> static inline juce::Rectangle<type> toJuce(Kiwi::Rectangle const& rect) noexcept {
        return juce::Rectangle<type>((type)rect.x(), (type)rect.y(), (type)rect.width(), (type)rect.height());
    }
    
    template<typename type> static inline Kiwi::Rectangle toKiwi(juce::Rectangle<type> const& rect) noexcept {
        return Kiwi::Rectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
    }
    
    static inline juce::Colour toJuce(Kiwi::Color const& color) noexcept {
        return Colour::fromFloatRGBA(color.red(), color.green(), color.blue(), color.alpha());
    }
    
    static inline Kiwi::Color toKiwi(juce::Colour const& color) noexcept {
        return Kiwi::Color(color.getFloatRed(), color.getFloatGreen(), color.getFloatBlue(), color.getFloatAlpha());
    }
    
    class jSketch : public Sketch
    {
    private:
        Graphics &g;
        Kiwi::Rectangle bounds;
    public:
        
        inline jSketch(Graphics& graphics) noexcept :
        g(graphics), bounds(toKiwi(graphics.getClipBounds())){}
        
        inline ~jSketch() noexcept {}
        
        inline Kiwi::Point getPosition() const noexcept override {return bounds.position();}
        
        inline Kiwi::Point getSize() const noexcept override {return bounds.size();}
        
        inline Kiwi::Rectangle getBounds() const noexcept override {return bounds;}
        
        void setColor(Kiwi::Color const& color) override;
        
        void setFont(Kiwi::Font const& font) override;
        
        void fillAll() const override;
        
        void drawText(string const& text, double x, double y, double w, double h, Kiwi::Font::Justification j, bool truncated = false) const override;

        void fillPath(Kiwi::Path const& path) const override;
        
        void drawPath(const Kiwi::Path& path, double const thickness) const override;
        
        void drawLine(double x1, double y1, double x2, double y2, double thickness) const override;
        
        void drawRectangle(double x, double y, double w, double h, double thickness, double rounded = 0.) const override;
        
        void fillRectangle(double x, double y, double w, double h, double rounded = 0.) const override;
        
        void drawEllipse(double x, double y, double width, double height, double thickness = 0.) const override;
        
        void fillEllipse(double x, double y, double width, double height) const override;
    };
    
    class jEventMouse : public Kiwi::MouseEvent
    {
    private:
        const MouseInputSource m_source;
    public:
        
        jEventMouse(Type const& type, juce::MouseEvent const& event) noexcept;
        
        jEventMouse(juce::MouseEvent const& event, MouseWheelDetails const& wheel) noexcept;
        
        ~jEventMouse() noexcept;
        
        void setMouseUnlimited(bool isLimited, bool visibleUntilLimits = false) const override;
    };
}

#endif

#endif


