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

#ifndef __DEF_KIWI_GUI_JUCE_DEVICE__
#define __DEF_KIWI_GUI_JUCE_DEVICE__

#include "KiwiGuiJuceView.h"

namespace Kiwi
{
    
    class KiwiJuceGuiDeviceManager : public GuiDeviceManager, public enable_shared_from_this<KiwiJuceGuiDeviceManager>
    {
    private:
        const sJuceDeviceCommandManager m_command_manager;
        
    public:
        
        //! Constructor
        /**
         */
        KiwiJuceGuiDeviceManager() noexcept;
        
        //! Destructor
        /**
         */
        ~KiwiJuceGuiDeviceManager() noexcept;
        
        //! Retrieve the command manager of the application.
        /** The function retrieves the command manager of the application.
         @return Thecommand manager.
         */
        inline sJuceDeviceCommandManager getCommandManager() const noexcept
        {
            return m_command_manager;
        }
        
        //! Create a view.
        /** The function creates a view for a controller.
         @param ctrl The controller linked with the view.
         @return The view.
         */
        sGuiView createView(sGuiController ctrl) const noexcept override;
        
        //! Create a window.
        /** The function creates a window.
         @return The window.
         */
        sGuiWindow createWindow() const noexcept override;        
        
    };
}

#endif

#endif

