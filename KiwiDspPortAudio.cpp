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
 
 To release a stopd-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
*/

#ifdef __KIWI_PORT_AUDIO_WRAPPER__

#include "KiwiDspPortAudio.h"

namespace Kiwi
{
    ulong KiwiPortAudioDeviceManager::m_nmanagers = 0;
    
    KiwiPortAudioDeviceManager::DeviceNode::DeviceNode(KiwiPortAudioDeviceManager* _device) :
    device(_device),
    nins(_device->m_paraminput.channelCount),
    inputs(_device->m_sample_ins),
    nouts(_device->m_paramoutput.channelCount),
    outputs(_device->m_sample_outs),
    samplerate(_device->m_samplerate),
    vectorsize(_device->m_vectorsize)
    {
        ;
    }
    
    KiwiPortAudioDeviceManager::KiwiPortAudioDeviceManager() :
    m_stream(nullptr),
    m_sample_ins(nullptr),
    m_sample_outs(nullptr)
    {
        lock_guard<mutex> guard(m_mutex);
        if(!m_nmanagers)
        {
            PaError err = Pa_Initialize();
            if(err != paNoError)
            {
                cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
            }
        }
        m_nmanagers++;
        m_driver = Pa_GetDefaultHostApi();
        m_paraminput.device            = Pa_GetDefaultInputDevice();
        m_paramoutput.device           = Pa_GetDefaultOutputDevice();
        m_paraminput.sampleFormat      = paFloat32;
        m_paramoutput.sampleFormat     = paFloat32;
        m_paraminput.suggestedLatency  = 0;
        m_paramoutput.suggestedLatency = 0;
        m_paraminput.channelCount      = 2;
        m_paramoutput.channelCount     = 2;
        m_vectorsize                   = 64;
        m_samplerate                   = 44100;
        m_stream = nullptr;
        start();
    }
    
    KiwiPortAudioDeviceManager::~KiwiPortAudioDeviceManager()
    {
        stop();
        if(m_nmanagers == 1)
        {
            PaError err = Pa_Terminate();
            if(err != paNoError)
            {
                cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
            }
        }
        m_nmanagers--;
    }
    
    void KiwiPortAudioDeviceManager::getAvailableDrivers(vector<string>& drivers) const
    {
        drivers.clear();
        const PaHostApiIndex numHost = Pa_GetHostApiCount();
        for(PaHostApiIndex i = 0; i < numHost; i++)
        {
            const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(i);
            if(hostInfo)
            {
                drivers.push_back(hostInfo->name);
            }
        }
    }
    
    string KiwiPortAudioDeviceManager::getDriverName() const
    {
        return Pa_GetHostApiInfo(m_driver)->name;
    }
    
    void KiwiPortAudioDeviceManager::getAvailableInputDevices(vector<string>& devices) const
    {
        devices.clear();
        const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(m_driver);
        if(hostInfo)
        {
            const PaDeviceInfo *deviceInfo;
            const int numDevices = hostInfo->deviceCount;
            for(int i = 0; i < numDevices; i++)
            {
                const PaDeviceIndex index = Pa_HostApiDeviceIndexToDeviceIndex(m_driver, i);
                deviceInfo = Pa_GetDeviceInfo(index);
                if(deviceInfo)
                {
                    if(deviceInfo->maxInputChannels)
                    {
                        devices.push_back(deviceInfo->name);
                    }
                }
            }
        }
    }
    
    void KiwiPortAudioDeviceManager::getAvailableOutputDevices(vector<string>& devices) const
    {
        devices.clear();
        const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(m_driver);
        if(hostInfo)
        {
            const PaDeviceInfo *deviceInfo;
            const int numDevices = hostInfo->deviceCount;
            for(int i = 0; i < numDevices; i++)
            {
                const PaDeviceIndex index = Pa_HostApiDeviceIndexToDeviceIndex(m_driver, i);
                deviceInfo = Pa_GetDeviceInfo(index);
                if(deviceInfo)
                {
                    if(deviceInfo->maxOutputChannels)
                    {
                        devices.push_back(deviceInfo->name);
                    }
                }
            }
        }
    }
    
    string KiwiPortAudioDeviceManager::getInputDeviceName() const
    {
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(m_paraminput.device);
        if(deviceInfo)
        {
            return deviceInfo->name;
        }
        else
        {
            return "";
        }
    }
    
    string KiwiPortAudioDeviceManager::getOutputDeviceName() const
    {
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(m_paramoutput.device);
        if(deviceInfo)
        {
            return deviceInfo->name;
        }
        else
        {
            return "";
        }
    }
    
    ulong KiwiPortAudioDeviceManager::getNumberOfInputs() const
    {
        return m_paraminput.channelCount;
    }
    
    ulong KiwiPortAudioDeviceManager::getNumberOfOutputs() const
    {
        return m_paramoutput.channelCount;
    }
    
    void KiwiPortAudioDeviceManager::getAvailableSampleRates(vector<ulong>& samplerates) const
    {
        for(ulong i = 1; i < 6; i++)
        {
            if(Pa_IsFormatSupported(&m_paraminput, &m_paramoutput, (double)(11025 * i)) == paFormatIsSupported)
            {
                samplerates.push_back((double)(11025 * i));
            }
            if(Pa_IsFormatSupported(&m_paraminput, &m_paramoutput, (double)(12000 * i)) == paFormatIsSupported)
            {
                samplerates.push_back((double)(12000 * i));
            }
            if(Pa_IsFormatSupported(&m_paraminput, &m_paramoutput, (double)(16000 * i)) == paFormatIsSupported)
            {
                samplerates.push_back((double)(16000 * i));
            }
        }
    }
    
    ulong KiwiPortAudioDeviceManager::getSampleRate() const
    {
        return m_samplerate;
    }
    
    void KiwiPortAudioDeviceManager::getAvailableVectorSizes(vector<ulong>& vectorsizes) const
    {
        for(ulong i = 1; i <= 8192; i *= 2)
        {
            vectorsizes.push_back(i);
        }
    }
    
    ulong KiwiPortAudioDeviceManager::getVectorSize() const
    {
        return m_vectorsize;
    }
    
    void KiwiPortAudioDeviceManager::setDriver(string const& driver)
    {
        const PaHostApiIndex numHost = Pa_GetHostApiCount();
        for(PaHostApiIndex i = 0; i < numHost; i++)
        {
            if(i != m_driver)
            {
                const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(i);
                if(hostInfo && hostInfo->name == driver)
                {
                    m_driver = i;
                    start();
                }
            }
        }
    }
    
    void KiwiPortAudioDeviceManager::setInputDevice(string const& device)
    {
        const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(m_driver);
        if(hostInfo)
        {
            const PaDeviceInfo *deviceInfo;
            const int numDevices = hostInfo->deviceCount;
            for(int i = 0; i < numDevices; i++)
            {
                const PaDeviceIndex index = Pa_HostApiDeviceIndexToDeviceIndex(m_driver, i);
                if(index != m_paraminput.device)
                {
                    deviceInfo = Pa_GetDeviceInfo(index);
                    if(deviceInfo && deviceInfo->name == device)
                    {
                        m_paraminput.device = index;
                        start();
                    }
                }
            }
        }
    }
    
    void KiwiPortAudioDeviceManager::setOutputDevice(string const& device)
    {
        const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(m_driver);
        if(hostInfo)
        {
            const PaDeviceInfo *deviceInfo;
            const int numDevices = hostInfo->deviceCount;
            for(int i = 0; i < numDevices; i++)
            {
                const PaDeviceIndex index = Pa_HostApiDeviceIndexToDeviceIndex(m_driver, i);
                if(index != m_paramoutput.device)
                {
                    deviceInfo = Pa_GetDeviceInfo(index);
                    if(deviceInfo && deviceInfo->name == device)
                    {
                        m_paramoutput.device = index;
                        start();
                    }
                }
            }
        }
    }
    
    void KiwiPortAudioDeviceManager::setSampleRate(ulong const samplerate)
    {
        if(samplerate != getSampleRate() && isSampleRateAvailable(samplerate))
        {
            m_samplerate = (ulong)samplerate;
            start();
        }
    }
    
    void KiwiPortAudioDeviceManager::setVectorSize(ulong const vectorsize)
    {
        if(vectorsize != getVectorSize() && isVectorSizeAvailable(vectorsize))
        {
            m_vectorsize = (ulong)vectorsize;
            start();
        }
    }
    
    sample const* KiwiPortAudioDeviceManager::getInputsSamples(const ulong channel) const noexcept
    {
        if(m_sample_ins && channel < getNumberOfInputs())
        {
            return m_sample_ins + channel * getVectorSize();
        }
        else
        {
            return nullptr;
        }
    }
    
    sample* KiwiPortAudioDeviceManager::getOutputsSamples(const ulong channel) const noexcept
    {
        if(m_sample_outs && channel < getNumberOfOutputs())
        {
            return m_sample_outs + channel * getVectorSize();
        }
        else
        {
            return nullptr;
        }
    }
    
    void KiwiPortAudioDeviceManager::stop()
    {
        if(m_stream)
        {
            if(Pa_IsStreamActive(m_stream))
            {
                PaError err = Pa_StopStream(m_stream);
                if(err != paNoError)
                {
                    cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
                    err = Pa_AbortStream(m_stream);
                    if(err != paNoError)
                    {
                        cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
                    }
                }
                while(!Pa_IsStreamStopped(m_stream))
                {
                    ;
                }
                m_stream = nullptr;
            }
        }
        if(m_sample_ins)
        {
            delete [] m_sample_ins;
            m_sample_ins = nullptr;
        }
        if(m_sample_outs)
        {
            delete [] m_sample_outs;
            m_sample_ins = nullptr;
        }
    }
    
    void KiwiPortAudioDeviceManager::start()
    {
        if(m_stream)
        {
            stop();
        }

        m_sample_ins    = new sample[m_paraminput.channelCount * m_vectorsize];
        m_sample_outs   = new sample[m_paramoutput.channelCount * m_vectorsize];
        
        DeviceNode* node = new DeviceNode(this);
        PaError err = Pa_OpenStream(&m_stream, &m_paraminput, &m_paramoutput, m_samplerate, m_vectorsize, paClipOff, &callback, node);
        if(err != paNoError)
        {
            cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
            return;
        }
        
        err = Pa_SetStreamFinishedCallback(m_stream, &finish);
        if(err != paNoError)
        {
            cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
            return;
        }
        
        
        err = Pa_StartStream(m_stream);
        if(err != paNoError)
        {
            cout << "PortAudio error: %s\n" << Pa_GetErrorText(err) << endl;
            return;
        }
    }

    
    int KiwiPortAudioDeviceManager::callback(const void *inputBuffer, void *outputBuffer, ulong framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
    {
        DeviceNode* d = (DeviceNode*)userData;
#ifdef __KIWI_DSP_DOUBLE__
        const ulong nins    = d->nins;
        const ulong nouts   = d->nouts;
        const ulong vecsize = d->vectorsize;
        float*  vec1     = (float*)inputBuffer;
        sample* vec2     = d->inputs;
        
        for(ulong i = 0; i < nins; i++)
        {
            for(ulong j = 0; j < vecsize; j++)
            {
                *(vec2++) = *(vec1+nins+j*nins);
            }
        }
        Signal::vclear(d->vectorsize * d->nouts, d->outputs);
        d->device->tick();
        
        vec2    = d->outputs;
        vec1    = (float*)inputBuffer;
        for(ulong i = 0; i < nouts; i++)
        {
            for(ulong j = 0; j < vecsize; j++)
            {
                *(vec1++) = *(vec2+nouts+j*nouts);
            }
        }
#else
        Signal::vdeterleave(d->vectorsize, d->nins, (float *)inputBuffer, d->inputs);
        Signal::vclear(d->vectorsize * d->nouts, d->outputs);
        d->device->tick();
        Signal::vinterleave(d->vectorsize, d->nouts, (float *)d->outputs, (float *)outputBuffer);
#endif
        return paContinue;
    }
    
    void KiwiPortAudioDeviceManager::finish(void *userData )
    {
        DeviceNode* d = (DeviceNode*)userData;
        delete d;
    }
}

#endif

