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

#include "KiwiGuiJuceDoodle.h"

namespace Kiwi
{
    JDoodle::JDoodle(Graphics &_g, juce::Rectangle<int> b) noexcept :
    g(_g), bounds(b.getX(), b.getY(), b.getWidth(), b.getHeight())
    {
        ;
    }
    
    JDoodle::JDoodle(Graphics &_g, Kiwi::Rectangle b) noexcept :
    g(_g), bounds(b)
    {
        ;
    }
    
    JDoodle::~JDoodle() noexcept
    {
        ;
    }
    
    void JDoodle::setColor(Kiwi::Color const& color)
    {
        g.setColour(toJuce(color));
    }
    
    void JDoodle::setFont(Kiwi::Font const& font)
    {
        juce::Font jfont(font.getName(), (float)font.getSize(), font.getStyle());
        g.setFont(jfont);
    }
    
    void JDoodle::fillAll()
    {
        g.fillAll();
    }
    
    void JDoodle::drawText(string const& text, double x, double y, double w, double h, Kiwi::Font::Justification j, bool wrap)
    {
        g.drawText(text, x, y, w, h, juce::Justification(j), wrap);
    }
    
    void JDoodle::drawText(string const& text, Kiwi::Rectangle const& rect, Kiwi::Font::Justification j, bool wrap )
    {
        g.drawText(text, rect.x(), rect.y(), rect.width(), rect.height(), juce::Justification(j), wrap);
    }
    
    void JDoodle::drawFittedText(string const& text, Kiwi::Rectangle const& rect, Kiwi::Font::Justification j, const long maximumNumberOfLines, const double minimumHorizontalScale)
    {
        g.drawFittedText(text, rect.x(), rect.y(), rect.width(), rect.height(), juce::Justification(j), maximumNumberOfLines, minimumHorizontalScale);
    }
    
    void JDoodle::drawFittedText(string const& text, const double x, const double y, const double width, const double height, Kiwi::Font::Justification j, const long maximumNumberOfLines, const double minimumHorizontalScale)
    {
        g.drawFittedText(text, x, y, width, height, juce::Justification(j), maximumNumberOfLines, minimumHorizontalScale);
    }
    
    void JDoodle::drawMultiLineText(wstring const& text, const long startX, const long baselineY, const long maximumLineWidth) const
    {
        g.drawMultiLineText(text.c_str(), startX, baselineY, maximumLineWidth);
    }
    
    void JDoodle::fillPath(Kiwi::Path const& path)
    {
        if(!path.empty())
        {
            /*
             juce::Path jpath;
             Kiwi::Path::Node node = path.getNode(0);
             jpath.startNewSubPath(node.point.x(), node.point.y());
             for(ulong i = 1; i < path.size(); i++)
             {
             node = path.getNode(i);
             switch(node.mode)
             {
             case Kiwi::Path::Move:
             jpath.startNewSubPath(node.point.x(), node.point.y());
             break;
             case Kiwi::Path::Path::Linear:
             jpath.lineTo(node.point.x(), node.point.y());
             break;
             case Kiwi::Path::Path::Quadratic:
             {
             if(++i < path.size())
             {
             Kiwi::Path::Node next_node = path.getNode(i);
             jpath.quadraticTo(node.point.x(), node.point.y(), next_node.point.x(), next_node.point.y());
             }
             
             }
             break;
             case Kiwi::Path::Cubic:
             {
             i += 2;
             if(i < path.size())
             {
             Kiwi::Path::Node next_node = path.getNode(i-1);
             Kiwi::Path::Node next_node2 = path.getNode(i);
             jpath.cubicTo(node.point.x(), node.point.y(), next_node.point.x(), next_node.point.y(), next_node2.point.x(), next_node2.point.y());
             }
             }
             break;
             
             default:
             break;
             }
             }
             g.fillPath(jpath);
             */
        }
    }
    
    void JDoodle::drawPath(const Kiwi::Path& path, double const thickness)
    {
        if(!path.empty())
        {
            /*
             juce::Path jpath;
             Kiwi::Path::Node node = path.getNode(0);
             jpath.startNewSubPath(node.point.x(), node.point.y());
             for(ulong i = 1; i < path.size(); i++)
             {
             node = path.getNode(i);
             switch(node.mode)
             {
             case Kiwi::Path::Move:
             jpath.startNewSubPath(node.point.x(), node.point.y());
             break;
             case Kiwi::Path::Linear:
             jpath.lineTo(node.point.x(), node.point.y());
             break;
             case Kiwi::Path::Quadratic:
             {
             if(++i < path.size())
             {
             Kiwi::Path::Node next_node = path.getNode(i);
             jpath.quadraticTo(node.point.x(), node.point.y(), next_node.point.x(), next_node.point.y());
             }
             
             }
             break;
             case Kiwi::Path::Cubic:
             {
             i += 2;
             if(i < path.size())
             {
             Kiwi::Path::Node next_node = path.getNode(i-1);
             Kiwi::Path::Node next_node2 = path.getNode(i);
             jpath.cubicTo(node.point.x(), node.point.y(), next_node.point.x(), next_node.point.y(), next_node2.point.x(), next_node2.point.y());
             }
             }
             break;
             
             default:
             break;
             }
             }
             g.strokePath(jpath, juce::PathStrokeType(thickness));
             */
        }
    }
    
    void JDoodle::drawLine(double x1, double y1, double x2, double y2, double thickness)
    {
        g.drawLine(x1, y1, x2, y2, thickness);
    }
    
    void JDoodle::drawRectangle(double x, double y, double w, double h, double thickness, double rounded)
    {
        g.drawRoundedRectangle(x, y, w, h, rounded, thickness);
    }
    
    void JDoodle::drawRectangle(Kiwi::Rectangle const& rect, double thickness, double rounded)
    {
        g.drawRoundedRectangle(rect.x(), rect.y(), rect.width(), rect.height(), rounded, thickness);
    }
    
    void JDoodle::fillRectangle(double x, double y, double w, double h, double rounded)
    {
        g.fillRoundedRectangle(x, y, w, h, rounded);
    }
    
    void JDoodle::fillRectangle(Kiwi::Rectangle const& rect, double rounded)
    {
        g.fillRoundedRectangle(rect.x(), rect.y(), rect.width(), rect.height(), rounded);
    }
    
    void JDoodle::drawEllipse(double x, double y, double width, double height, double thickness)
    {
        g.drawEllipse(x, y, width, height, thickness);
    }
    
    void JDoodle::fillEllipse(double x, double y, double width, double height)
    {
        g.fillEllipse(x, y, width, height);
    }
}

#endif

