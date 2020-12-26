#include <engine/AudioBuffer.hpp>

#include <AL/alext.h>

#include <iostream>
#include <engine/sndfile.h>
#include <inttypes.h>
#include <stdlib.h>
#include <limits.h>

namespace audio
{

    AudioBuffer *AudioBuffer::getInstance()
    {
        static AudioBuffer *sndbuf = new AudioBuffer();
        return sndbuf;
    }

    ALuint AudioBuffer::addAudioEffect(const char *filename)
    {

        ALenum err, format;
        ALuint buffer;
        SNDFILE *sndfile;
        SF_INFO sfinfo;
        short *membuf;
        sf_count_t num_frames;
        ALsizei num_bytes;

        // open the audio file and check that it's usable.
        sndfile = sf_open(filename, SFM_READ, &sfinfo);
        if (!sndfile)
        {
            std::cerr << "Could not open audio in " << filename << std::endl;
            return 0;
        }
        if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
        {
            std::cerr << "Bad sample count in " << filename << std::endl;
            return 0;
        }

        // get the audio format, and figure out the OpenAL format
        format = AL_NONE;
        if (sfinfo.channels == 1)
            format = AL_FORMAT_MONO16;
        else if (sfinfo.channels == 2)
            format = AL_FORMAT_STEREO16;
        else if (sfinfo.channels == 3)
        {
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
                format = AL_FORMAT_BFORMAT2D_16;
        }
        else if (sfinfo.channels == 4)
        {
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
                format = AL_FORMAT_BFORMAT3D_16;
        }
        if (!format)
        {
            std::cerr << "Unsupported channel count: " << sfinfo.channels << std::endl;
            sf_close(sndfile);
            return 0;
        }

        // decode the whole audio file to a buffer
        membuf = static_cast<short *>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

        num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
        if (num_frames < 1)
        {
            free(membuf);
            sf_close(sndfile);
            std::cerr << "Failed to read samples in " << filename << std::endl;
            return 0;
        }
        num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

        // buffer the audio data into a new buffer object, then free the data and close the file
        buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

        free(membuf);
        sf_close(sndfile);

        // check if an error occured, and clean up if so
        err = alGetError();
        if (err != AL_NO_ERROR)
        {
            std::cerr << "OpenAL Error: " << alGetString(err) << std::endl;
            if (buffer && alIsBuffer(buffer))
                alDeleteBuffers(1, &buffer);
            return 0;
        }

        // add to the list of known buffers
        m_audioEffectBuffers.push_back(buffer);

        return buffer;
    }

    bool AudioBuffer::removeAudioEffect(const ALuint &buffer)
    {
        auto it = m_audioEffectBuffers.begin();
        while (it != m_audioEffectBuffers.end())
        {
            if (*it == buffer)
            {
                alDeleteBuffers(1, &*it);

                it = m_audioEffectBuffers.erase(it);

                return true;
            }
            else
            {
                ++it;
            }
        }
        // couldn't find to remove
        return false;
    }

    AudioBuffer::AudioBuffer()
    {
        m_audioEffectBuffers.clear();
    }

    AudioBuffer::~AudioBuffer()
    {
        std::cout << "[AudioBuffer] Delete the main audio buffer" << std::endl;

        alDeleteBuffers(m_audioEffectBuffers.size(), m_audioEffectBuffers.data());

        m_audioEffectBuffers.clear();
    }

} // namespace audio
