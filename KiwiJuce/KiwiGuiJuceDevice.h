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

#include "KiwiGuiJucePatcher.h"

namespace Kiwi
{    
    class KiwiJuceGuiDeviceManager : public GuiDeviceManager
    {
    private:
        
    public:
        
        //! Constructor
        /**
         */
        KiwiJuceGuiDeviceManager();
        
        //! Destructor
        /**
         */
        ~KiwiJuceGuiDeviceManager();
        
        //! Create the view of a patcher depending on the implementation.
        /** The function retrieves the view of a patcher depending on the implementation.
         @param patcher The patcher.
         @return The patcher view.
         */
        GuiPatcher::sView createView(sGuiPatcher patcher) override;
    };
}

#endif

#endif


