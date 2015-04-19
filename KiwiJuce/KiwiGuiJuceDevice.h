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
    
    class KiwiJuceGuiDeviceManager : public GuiDeviceManager, public ApplicationCommandManager, public enable_shared_from_this<KiwiJuceGuiDeviceManager>
    {
    public:
        
        //! Constructor
        /**
         */
        KiwiJuceGuiDeviceManager();
        
        //! Destructor
        /**
         */
        ~KiwiJuceGuiDeviceManager();
        
        //! Create a view.
        /** The function creates a view for a controller.
         @param ctrl The controller linked with the view.
         @return The view.
         */
        sGuiView createView(sGuiController ctrl) noexcept override;
        
        //! Retrieves the mouse absolute position.
        /** The function retrieves the mouse absolute position.
         @return The mouse absolute position.
         */
        Point getMousePosition() const noexcept override;
        
        //! Retrieves the screen bounds.
        /** The function retrieves the screen bounds for a point. Since there can be several screens, the point determines wichs screen to select.
         @param pt The point.
         @return The screen bounds.
         */
        Rectangle getScreenBounds(Point const& pt) const noexcept override;
        
        //! Retrieves the size of a text.
        /** The function the size of a text depending on a font.
         @param font The font.
         @param text The text.
         @return The size of the text.
         */
        Size getTextSize(Font const& font, wstring const& text) const noexcept override;
        
    };
}

#endif

#endif


