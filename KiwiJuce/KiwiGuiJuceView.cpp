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

#include "KiwiGuiJuceView.h"
#include "KiwiGuiJuceDevice.h"

namespace Kiwi
{	
	// ================================================================================ //
	//										JVIEW										//
	// ================================================================================ //

    jView::jView(sGuiController ctrl) noexcept : GuiView(ctrl)
    {
        setInterceptsMouseClicks(ctrl->wantMouse(), true);
        setBounds(toJuce<int>(ctrl->getBounds()));
    }
    
    jView::~jView()
    {
        ;
    }
    
    void jView::redraw()
    {
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            repaint();
        }
    }
    
    void jView::addChild(sGuiView child)
    {
        if(child)
        {
            sjView jchild = dynamic_pointer_cast<jView>(child);
            if(jchild)
            {
                addAndMakeVisible(jchild.get());
                jchild->setBounds(toJuce<int>(jchild->getController()->getBounds()));
            }
        }
    }
    
    void jView::removeChild(sGuiView child)
    {
        if(child)
        {
            sjView jchild = dynamic_pointer_cast<jView>(child);
            if(jchild)
            {
                removeChildComponent(jchild.get());
            }
        }
    }
    
    void jView::paint(Graphics& g)
    {
        sGuiController ctrl = getController();
        if(ctrl)
        {
            jSketch d(g, g.getClipBounds());
            ctrl->draw(d);
        }
    }
    
    void jView::mouseDown(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::Down, e));
    }
    
    void jView::mouseDrag(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::Drag, e));
    }
    
    void jView::mouseUp(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::Up, e));
    }
    
    void jView::mouseMove(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::Move, e));
    }
    
    void jView::mouseEnter(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::Enter, e));
    }
    
    void jView::mouseExit(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::Leave, e));
    }
    
    void jView::mouseDoubleClick(const juce::MouseEvent& e)
    {
        receive(jEventMouse(MouseEvent::Type::DoubleClick, e));
    }
    
    void jView::mouseWheelMove(const juce::MouseEvent& event, const MouseWheelDetails& wheel)
    {
        receive(jEventMouse(event, wheel));
    }
    
    void jView::focusGained(FocusChangeType cause)
    {
        receive(KeyboardFocusIn);
    }
    
    void jView::focusLost(FocusChangeType cause)
    {
        receive(KeyboardFocusOut);
    }
    
    bool jView::keyPressed(const KeyPress& key)
    {
        return receive(jEventKeyboard(key));
    }
    
    // ================================================================================ //
    //                                      JWINDOW                                     //
    // ================================================================================ //
    
    jWindow::jWindow(scJuceGuiDeviceManager device) :
    GuiWindow(),
    DocumentWindow("untitled", Colour(0xffdddddd), DocumentWindow::allButtons, true),
    m_device(device),
    m_view(new View())
    {
#if ! JUCE_MAC
        setMenuBar(Application::getApp().m_menu_model);
#endif
        setUsingNativeTitleBar(true);
        if(m_device)
        {
            sJuceDeviceCommandManager cmd = m_device->getCommandManager();
            if(cmd)
            {
                ;
            }
        }

        setBackgroundColour(Colours::lightgrey);
        setResizable(true, true);
        setSize(800, 600);
        setResizeLimits (20, 20, 320000, 320000);
        setVisible(true);
        setContentNonOwned(m_view, false);
        m_view->setInterceptsMouseClicks(false, true);
        m_view->setBounds(0, 0, 800, 600);
        
        //Application::bindToCommandManager(this);
        //Application::bindToKeyMapping(this);
    }
    
    jWindow::~jWindow()
    {
        if(m_device)
        {
            sJuceDeviceCommandManager cmd = m_device->getCommandManager();
            if(cmd)
            {
                removeKeyListener(cmd->getKeyMappings());
            }
        }
    }
    
    void jWindow::closeButtonPressed()
    {
        //Application::getController()->closeMainWindow(this);
    }
    
    ApplicationCommandTarget* jWindow::getNextCommandTarget()
    {
        return findFirstTargetParentComponent();
    }
    
    void jWindow::getAllCommands(Array <CommandID>& commands)
    {
        commands.add(CommandIDs::closeWindow);
        commands.add(CommandIDs::minimizeWindow);
        commands.add(CommandIDs::maximizeWindow);
    }
    
    void jWindow::getCommandInfo(const CommandID commandID, ApplicationCommandInfo& result)
    {
        switch (commandID)
        {
            case CommandIDs::closeWindow:
                result.setInfo (TRANS("Close"), TRANS("Close Window"), CommandCategories::windows, 0);
                result.addDefaultKeypress ('w', ModifierKeys::commandModifier);
                result.setActive(getDesktopWindowStyleFlags() & DocumentWindow::closeButton);
                break;
                
            case CommandIDs::minimizeWindow:
                result.setInfo (TRANS("Minimize"), TRANS("Minimize Window"), CommandCategories::windows, 0);
                result.setActive(getDesktopWindowStyleFlags() & DocumentWindow::minimiseButton);
                break;
                
            case CommandIDs::maximizeWindow:
                result.setInfo (TRANS("Maximize"), TRANS("Maximize Window"), CommandCategories::windows, 0);
                result.setActive(getDesktopWindowStyleFlags() & DocumentWindow::maximiseButton);
                break;
                
            default:
                break;
        }
    }
    
    bool jWindow::perform (const InvocationInfo& info)
    {
        switch (info.commandID)
        {
            case CommandIDs::minimizeWindow: minimiseButtonPressed(); break;
            case CommandIDs::maximizeWindow: maximiseButtonPressed(); break;
            case CommandIDs::closeWindow:    closeButtonPressed();    break;
            default: return false;
        }
        return true;
    }
    
    void jWindow::display(sGuiView view)
    {
        sjView jview = dynamic_pointer_cast<jView>(view);
        if(jview)
        {
            m_view->addAndMakeVisible(jview.get());
        }
    }
    
    void jWindow::setTitle(string const& title)
    {
        setName(title);
    }
}

#endif
