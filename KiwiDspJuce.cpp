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

#include "KiwiDspJuce.h"

namespace Kiwi
{
    KiwiJuceDspDeviceManager::KiwiJuceDspDeviceManager() :
    m_driver_name(""),
    m_input_matrix(nullptr),
    m_output_matrix(nullptr)
    {
        m_setup.sampleRate = 44100;
        juce::AudioDeviceManager manager;
        manager.createAudioDeviceTypes(m_drivers);
        if(m_drivers.size())
        {
            setDriver(m_drivers[0]->getTypeName().toStdString());
        }
    }
    
    KiwiJuceDspDeviceManager::~KiwiJuceDspDeviceManager()
    {
        close();
    }
    
    void KiwiJuceDspDeviceManager::getAvailableDrivers(vector<string>& drivers) const
    {
        drivers.clear();
        for(int i = 0; i < m_drivers.size(); ++i)
        {
            drivers.push_back(m_drivers[i]->getTypeName().toStdString());
        }
    }
    
    juce::AudioIODeviceType* KiwiJuceDspDeviceManager::getDriver() const
    {
        for(int i = 0; i < m_drivers.size(); ++i)
        {
            if(m_drivers.getUnchecked(i)->getTypeName() == String(m_driver_name))
            {
                return m_drivers.getUnchecked(i);
            }
        }
        return nullptr;
    }
    
    string KiwiJuceDspDeviceManager::getDriverName() const
    {
        return m_driver_name;
    }
    
    void KiwiJuceDspDeviceManager::getAvailableInputDevices(vector<string>& devices) const
    {
        devices.clear();
        juce::AudioIODeviceType* driver = getDriver();
        if(driver)
        {
            driver->scanForDevices();
            juce::StringArray deviceNames = driver->getDeviceNames(true);
            for(int j = 0; j < deviceNames.size(); ++j)
            {
                devices.push_back(deviceNames[j].toStdString());
            }
        }
    }
    
    void KiwiJuceDspDeviceManager::getAvailableOutputDevices(vector<string>& devices) const
    {
        devices.clear();
        juce::AudioIODeviceType* driver = getDriver();
        if(driver)
        {
            driver->scanForDevices();
            juce::StringArray deviceNames = driver->getDeviceNames(false);
            for(int j = 0; j < deviceNames.size(); ++j)
            {
                devices.push_back(deviceNames[j].toStdString());
            }
        }
    }
    
    string KiwiJuceDspDeviceManager::getInputDeviceName() const
    {
        return m_setup.inputDeviceName.toStdString();
    }
    
    string KiwiJuceDspDeviceManager::getOutputDeviceName() const
    {
        return m_setup.outputDeviceName.toStdString();
    }
    
    ulong KiwiJuceDspDeviceManager::getNumberOfInputs() const
    {
        return m_setup.inputChannels.getHighestBit() + 1;
    }
    
    ulong KiwiJuceDspDeviceManager::getNumberOfOutputs() const
    {
        return m_setup.outputChannels.getHighestBit() + 1;
    }
    
    void KiwiJuceDspDeviceManager::getAvailableSampleRates(vector<ulong>& samplerates) const
    {
        samplerates.clear();
        if(m_device)
        {
            juce::Array<double> array(m_device->getAvailableSampleRates());
            for(int i = 0; i < array.size(); ++i)
            {
                samplerates.push_back((ulong)array[i]);
            }
        }
    }
    
    ulong KiwiJuceDspDeviceManager::getSampleRate() const
    {
        return (ulong)m_setup.sampleRate;
    }
    
    void KiwiJuceDspDeviceManager::getAvailableVectorSizes(vector<ulong>& vectorsizes) const
    {
        vectorsizes.clear();
        if(m_device)
        {
            juce::Array<int> array(m_device->getAvailableBufferSizes());
            for(int i = 0; i < array.size(); ++i)
            {
                vectorsizes.push_back((ulong)array[i]);
            }
        }
    }
    
    ulong KiwiJuceDspDeviceManager::getVectorSize() const
    {
        return (ulong)m_setup.bufferSize;
    }
    
    void KiwiJuceDspDeviceManager::setDriver(string const& driver)
    {
        if(driver != getDriverName() && isDriverAvailable(driver))
        {
            m_driver_name = driver;
            initialize();
        }
    }
    
    void KiwiJuceDspDeviceManager::setInputDevice(string const& device)
    {
        if(device != getInputDeviceName() && isInputDeviceAvailable(device))
        {
            m_setup.inputDeviceName = juce::String(device);
            initialize();
        }
    }
    
    void KiwiJuceDspDeviceManager::setOutputDevice(string const& device)
    {
        if(device != getOutputDeviceName() && isOutputDeviceAvailable(device))
        {
            m_setup.outputDeviceName = juce::String(device);
            initialize();
        }
    }
    
    void KiwiJuceDspDeviceManager::setSampleRate(ulong const samplerate)
    {
        if(samplerate != getSampleRate() && isSampleRateAvailable(samplerate))
        {
            m_setup.sampleRate = (double)samplerate;
            initialize();
        }
    }
    
    void KiwiJuceDspDeviceManager::setVectorSize(ulong const vectorsize)
    {
        if(vectorsize != getVectorSize() && isVectorSizeAvailable(vectorsize))
        {
            m_setup.bufferSize = (int)vectorsize;
            initialize();
        }
    }
    
    sample const* KiwiJuceDspDeviceManager::getInputsSamples(const ulong channel) const noexcept
    {
        if(m_input_matrix && channel < getNumberOfInputs())
        {
            return m_input_matrix[channel];
        }
        else
        {
            return nullptr;
        }
    }
    
    sample* KiwiJuceDspDeviceManager::getOutputsSamples(const ulong channel) const noexcept
    {
        if(m_output_matrix && channel < getNumberOfOutputs())
        {
            return m_output_matrix[channel];
        }
        else
        {
            return nullptr;
        }
    }
    
    void KiwiJuceDspDeviceManager::close()
    {
        if(m_device)
        {
            if(m_device->isPlaying())
            {
                m_device->stop();
            }
            if(m_device->isOpen())
            {
                m_device->close();
            }
            if(m_input_matrix)
            {
                for(int i = 0; i < m_device->getInputChannelNames().size(); i++)
                {
                    if(m_input_matrix[i])
                    {
                        delete [] m_input_matrix[i];
                    }
                    m_input_matrix[i] = nullptr;
                }
                delete [] m_input_matrix;
            }
            m_input_matrix = nullptr;
            if(m_output_matrix)
            {
                for(int i = 0; i < m_device->getOutputChannelNames().size(); i++)
                {
                    if(m_output_matrix[i])
                    {
                        delete [] m_output_matrix[i];
                    }
                    m_output_matrix[i] = nullptr;
                }
                delete [] m_output_matrix;
            }
            m_output_matrix = nullptr;
        }
    }
    
    void KiwiJuceDspDeviceManager::initialize()
    {
        juce::AudioIODeviceType* driver = getDriver();
        if(driver)
        {
            driver->scanForDevices();
            if(!isOutputDeviceAvailable(m_setup.outputDeviceName.toStdString()))
            {
                juce::StringArray deviceNames = driver->getDeviceNames(false);
                if(deviceNames.size())
                {
                    m_setup.outputDeviceName = deviceNames[0];
                }
                else
                {
                    m_setup.outputDeviceName = juce::String();
                }
            }
            if(!isInputDeviceAvailable(m_setup.inputDeviceName.toStdString()))
            {
                juce::StringArray deviceNames = driver->getDeviceNames(true);
                if(deviceNames.size())
                {
                    m_setup.inputDeviceName = deviceNames[0];
                }
                else
                {
                    m_setup.inputDeviceName = juce::String();
                }
            }
        
            close();

            m_device = driver->createDevice(m_setup.outputDeviceName, m_setup.inputDeviceName);
            if(m_device)
            {
                if(!isSampleRateAvailable(m_setup.sampleRate))
                {
                    juce::Array<double> array(m_device->getAvailableSampleRates());
                    if(array.size())
                    {
                        m_setup.sampleRate = array[0];
                    }
                    else
                    {
                        m_setup.sampleRate = 0;
                    }
                }
                if(!isVectorSizeAvailable(m_setup.bufferSize))
                {
                    m_setup.bufferSize = m_device->getDefaultBufferSize();
                }
                m_setup.inputChannels.setRange(0, m_device->getInputChannelNames().size(), true);
                m_setup.outputChannels.setRange(0, m_device->getOutputChannelNames().size(), true);
            }
            
            if(!m_device->isOpen())
            {
                juce::String err = m_device->open(m_setup.inputChannels, m_setup.outputChannels, m_setup.sampleRate, m_setup.bufferSize);
                if(err.isEmpty())
                {
                    m_device->start(this);
                }
            }
            else if(!m_device->isPlaying())
            {
                m_device->start(this);
            }
            
        }
    }
    
    void KiwiJuceDspDeviceManager::audioDeviceAboutToStart(juce::AudioIODevice *device)
    {
        m_setup.bufferSize = m_device->getCurrentBufferSizeSamples();
        m_setup.sampleRate = m_device->getCurrentSampleRate();
        m_setup.inputChannels = m_device->getActiveInputChannels();
        m_setup.outputChannels = m_device->getActiveOutputChannels();
        
        m_input_matrix = new sample*[m_setup.inputChannels.getHighestBit() + 1];
        for(int i = 0; i < m_setup.inputChannels.getHighestBit() + 1; i++)
        {
            m_input_matrix[i] = new sample[m_setup.bufferSize];
        }
        m_output_matrix = new sample*[m_setup.outputChannels.getHighestBit() + 1];
        for(int i = 0; i < m_setup.outputChannels.getHighestBit() + 1; i++)
        {
            m_output_matrix[i] = new sample[m_setup.bufferSize];
            Signal::vclear(m_setup.bufferSize, m_output_matrix[i]);
        }
    }
    
    void KiwiJuceDspDeviceManager::audioDeviceStopped()
    {
        ;
    }
    
    void KiwiJuceDspDeviceManager::audioDeviceIOCallback(const float** inputChannelData, int numInputChannels, float** outputChannelData, int numOutputChannels, int numSamples)
    {
#ifdef __KIWI_DSP_DOUBLE__
        for(int i = 0; i < numInputChannels; i++)
        {
            sample* input = m_input_matrix[i];
            float* real = inputChannelData[i];
            for(int j = 0; j < numSamples; j++)
            {
                *(input++) = *(real++);
            }
        }
        for(int i = 0; i < numOutputChannels; i++)
        {
            Signal::vclear(numSamples, m_output_matrix[i]);
        }
        tick();
        for(int i = 0; i < numOutputChannels; i++)
        {
            sample* output = m_output_matrix[i];
            float* real = outputChannelData[i];
            for(int j = 0; j < numSamples; j++)
            {
                *(real++) = *(output++);
            }
        }
#else
        for(int i = 0; i < numInputChannels; i++)
        {
            Signal::vcopy(numSamples, inputChannelData[i], m_input_matrix[i]);
        }
        tick();
        for(int i = 0; i < numOutputChannels; i++)
        {
            Signal::vcopy(numSamples, m_output_matrix[i], outputChannelData[i]);
        }
        for(int i = 0; i < numOutputChannels; i++)
        {
            Signal::vclear(numSamples, m_output_matrix[i]);
        }
#endif
    }
    
    void KiwiJuceDspDeviceManager::stop()
    {
        m_device->start(this);
    }
    
    void KiwiJuceDspDeviceManager::start()
    {
        m_device->stop();
    }
}

#endif

