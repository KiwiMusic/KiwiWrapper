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

#include "KiwiGuiJuceEvent.h"

namespace Kiwi
{
    void jSketch::setColor(Kiwi::Color const& color)
    {
        g.setColour(toJuce(color));
    }
    
    void jSketch::setFont(Kiwi::Font const& font)
    {
        juce::Font jfont(font.getName(), (float)font.getSize(), font.getStyle());
        g.setFont(jfont);
    }
    
    void jSketch::fillAll() const
    {
        g.fillAll();
    }
    
    void jSketch::drawText(string const& text, double x, double y, double w, double h, Kiwi::Font::Justification j, bool wrap) const
    {
        g.drawText(String(text), juce::Rectangle<float>(x, y, w, h), juce::Justification(j), wrap);
    }
    
    void jSketch::fillPath(Kiwi::Path const& path) const
    {
        if(!path.empty())
        {
            juce::Path jpath;
            /*
             
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
             
             */
            g.fillPath(jpath);
        }
    }
    
    void jSketch::drawPath(const Kiwi::Path& path, double const thickness) const
    {
        if(!path.empty())
        {
            juce::Path jpath;
            Kiwi::Path::Node node = path.getNode(0);
            jpath.startNewSubPath(node.point().x(), node.point().y());
            for(ulong i = 1; i < path.size(); i++)
            {
                node = path.getNode(i);
                switch(node.mode())
                {
                    case Kiwi::Path::Move:
                        jpath.startNewSubPath(node.point().x(), node.point().y());
                        break;
                    case Kiwi::Path::Linear:
                        jpath.lineTo(node.point().x(), node.point().y());
                        break;
                    case Kiwi::Path::Quadratic:
                    {
                        if(++i < path.size())
                        {
                            Kiwi::Path::Node next_node = path.getNode(i);
                            jpath.quadraticTo(node.point().x(), node.point().y(),
                                              next_node.point().x(), next_node.point().y());
                        }
                        break;
                    }
                    case Kiwi::Path::Cubic:
                    {
                        i += 2;
                        if(i < path.size())
                        {
                            Kiwi::Path::Node next_node = path.getNode(i-1);
                            Kiwi::Path::Node next_node2 = path.getNode(i);
                            jpath.cubicTo(node.point().x(), node.point().y(),
                                          next_node.point().x(), next_node.point().y(),
                                          next_node2.point().x(), next_node2.point().y());
                        }
                        break;
                    }
                        
                    default:
                        break;
                }
            }
            g.strokePath(jpath, juce::PathStrokeType(thickness));
        }
    }
    
    void jSketch::drawLine(double x1, double y1, double x2, double y2, double thickness) const
    {
        g.drawLine(x1, y1, x2, y2, thickness);
    }
    
    void jSketch::drawRectangle(double x, double y, double w, double h, double thickness, double rounded) const
    {
        g.drawRoundedRectangle(x, y, w, h, rounded, thickness);
    }

    void jSketch::fillRectangle(double x, double y, double w, double h, double rounded) const
    {
        g.fillRoundedRectangle(x, y, w, h, rounded);
    }
    
    void jSketch::drawEllipse(double x, double y, double width, double height, double thickness) const
    {
        g.drawEllipse(x, y, width, height, thickness);
    }
    
    void jSketch::fillEllipse(double x, double y, double width, double height) const
    {
        g.fillEllipse(x, y, width, height);
    }
    
    jEventMouse::jEventMouse(Type const& type, juce::MouseEvent const& event) noexcept :
    Kiwi::MouseEvent(type, event.x, event.y, event.mods.getRawFlags(), 0., 0., event.mouseWasClicked(), event.getMouseDownPosition().x, event.getMouseDownPosition().y, event.getNumberOfClicks()),
    m_source(event.source)
    {
        ;
    }
    
    jEventMouse::jEventMouse(juce::MouseEvent const& event, MouseWheelDetails const& wheel) noexcept :
    Kiwi::MouseEvent(Kiwi::MouseEvent::Type::Wheel, event.x, event.y, event.mods.getRawFlags(), wheel.deltaX, wheel.deltaY, event.mouseWasClicked(), event.getMouseDownPosition().x, event.getMouseDownPosition().y, event.getNumberOfClicks()),
    m_source(event.source)
    {
        ;
    }
    
    jEventMouse::~jEventMouse() noexcept
    {
        ;
    }
    
    void jEventMouse::setMouseUnlimited(bool isLimited, bool visibleUntilLimits) const
    {
        m_source.enableUnboundedMouseMovement(isLimited, visibleUntilLimits);
    }
}

#endif

