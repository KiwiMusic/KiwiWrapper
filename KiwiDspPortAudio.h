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

#ifdef __KIWI_PORT_AUDIO_WRAPPER__

#ifndef __DEF_KIWI_DSP_PORTAUDIO__
#define __DEF_KIWI_DSP_PORTAUDIO__

#include "../KiwiDsp/KiwiDsp.h"
#include <portaudio.h>

namespace Kiwi
{
    class KiwiPortAudioDeviceManager : public DspDeviceManager
    {
        struct DeviceNode
        {
            const KiwiPortAudioDeviceManager*      device;
            const ulong                        nins;
            sample *const                      inputs;
            const ulong                        nouts;
            sample *const                      outputs;
            const ulong                        samplerate;
            const ulong                        vectorsize;
            
            DeviceNode(KiwiPortAudioDeviceManager* _device);
        };
        
        static ulong        m_nmanagers;

        PaHostApiIndex      m_driver;
        PaStreamParameters  m_paraminput;
        PaStreamParameters  m_paramoutput;
        ulong               m_samplerate;
        ulong               m_vectorsize;
        
        PaStream*           m_stream;
        sample*             m_sample_ins;
        sample*             m_sample_outs;
        vector<sDspContext> m_contexts;
        mutable mutex       m_mutex;
        
        void start();
        
        void stop();
        
        inline void tick() const noexcept
        {
            DspDeviceManager::tick();
        }
        
        static int callback(const void *inputBuffer, void *outputBuffer, ulong framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
        
        static void finish(void *userData);
        
    public:
        //! Constructor
        /**
         */
        KiwiPortAudioDeviceManager();
        
        //! Destructor
        /**
         */
        ~KiwiPortAudioDeviceManager();
        
        //! Retrieve the names of the available drivers.
        /** This function retrieves the names of the available drivers.
         @param drivers The names of the drivers.
         */
        void getAvailableDrivers(vector<string>& drivers) const override;
        
        //! Retrieve the names of the current driver.
        /** This function retrieves the names of the current driver.
         @return The names of the current driver.
         */
        string getDriverName() const override;
        
        //! Retrieve the names of the available input devices.
        /** This function retrieves the names of the available input devices.
         @param devices The names of the input devices.
         */
        void getAvailableInputDevices(vector<string>& devices) const override;
        
        //! Retrieve the names of the available output devices.
        /** This function retrieves the names of the available output devices.
         @param devices The names of the output devices.
         */
        void getAvailableOutputDevices(vector<string>& devices) const override;
        
        //! Retrieve the names of the current input device.
        /** This function retrieves the names of the current input device.
         @return The name of the current input device.
         */
        string getInputDeviceName() const override;
        
        //! Retrieve the names of the current output device.
        /** This function retrieves the names of the current output device.
         @return The name of the current output device.
         */
        string getOutputDeviceName() const override;
        
        //! Retrieve the number of inputs of the current device.
        /** This function retrieves the number of inputs of the current device.
         @return The number of inputs of the current device.
         */
        ulong getNumberOfInputs() const override;
        
        //! Retrieve the number of outputs of the current device.
        /** This function retrieves the number of outputs of the current device.
         @return The number of outputs of the current device.
         */
        ulong getNumberOfOutputs() const override;
        
        //! Retrieve the available sample rates for the current devices.
        /** This function retrieves the available sample rates for the current devices.
         @param samplerates The available sample rates.
         */
        void getAvailableSampleRates(vector<ulong>& samplerates) const override;
        
        //! Retrieve the current sample rate.
        /** This function retrieves the current sample rate.
         @return The current sample rate.
         */
        ulong getSampleRate() const override;
        
        //! Retrieve the available vector sizes for the current devices.
        /** This function retrieves the available vector sizes for the current devices.
         @param vectorsizes The available vector sizes.
         */
        void getAvailableVectorSizes(vector<ulong>& vectorsizes) const override;
        
        //! Retrieve the current vector size.
        /** This function retrieves the current vector size.
         @return The current vector size.
         */
        ulong getVectorSize() const override;
        
        //! Set the driver.
        /** This function sets the driver.
         @param The names of the driver.
         */
        void setDriver(string const& driver) override;
        
        //! Set the input device.
        /** This function sets the inputdevice.
         @param The names of the device.
         */
        void setInputDevice(string const& device) override;
        
        //! Set the output device.
        /** This function sets the output device.
         @param The names of the device.
         */
        void setOutputDevice(string const& device) override;
        
        //! Set the vector size.
        /** This function sets the svector size.
         @param vectorsize The vector size.
         */
        void setVectorSize(ulong const vectorsize) override;
        
        //! Set the sample rate.
        /** This function sets the sample rate.
         @param samplerate The sample rate.
         */
        void setSampleRate(ulong const samplerate) override;
        
        //! Retrieve the inputs sample matrix.
        /** This function retrieves the inputs sample matrix.
         @param channel the index of the channel.
         @return The inputs sample matrix.
         */
        sample const* getInputsSamples(const ulong channel) const noexcept override;
        
        //! Retrieve the outputs sample matrix.
        /** This function retrieves the outputs sample matrix.
         @param channel the index of the channel.
         @return The outputs sample matrix.
         */
        sample* getOutputsSamples(const ulong channel) const noexcept override;
    };
}

#endif
#endif


