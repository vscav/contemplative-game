#include <engine/AudioBuffer.hpp>
#include <engine/utils/common.hpp>
#include <engine/utils/cout_colors.hpp>
#include <engine/dependencies/sndfile.h>

#include <AL/alext.h>

#include <iostream>
#include <inttypes.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>

namespace engine
{

    ALuint AudioBuffer::addAudioEffect(const char *filename)
    {

        ALenum err, format;
        ALuint buffer;
        SNDFILE *sndfile;
        SF_INFO sfinfo;
        short *membuf;
        sf_count_t num_frames;
        ALsizei num_bytes;

        memset(&sfinfo, 0, sizeof(SF_INFO));

        // open the audio file and check that it's usable.
        sndfile = sf_open(filename, SFM_READ, &sfinfo);
        //f_perror(sndfile); To get a verbose error from sndfile
        if (!sndfile)
        {
            std::cerr << COLOR_RED << "[AudioBuffer] sndfile : Could not open audio in " << filename << COLOR_RESET << std::endl;
            return 0;
        }
        if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
        {
            std::cerr << "[AudioBuffer] sndfile : Bad sample count in " << filename << COLOR_RESET << std::endl;
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
            std::cerr << COLOR_RED << "[AudioBuffer] Unsupported channel count: " << sfinfo.channels << COLOR_RESET << std::endl;
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
            std::cerr << COLOR_RED << "[AudioBuffer] Failed to read samples in " << filename << COLOR_RESET << std::endl;
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
            std::cerr << COLOR_RED << "[OpenAL] Error: " << alGetString(err) << COLOR_RESET << std::endl;
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
        if (applicationDebug)
            std::cout << COLOR_CYAN << "[AudioBuffer]" << COLOR_RESET << " Delete the main audio buffer" << std::endl;

        alDeleteBuffers(m_audioEffectBuffers.size(), m_audioEffectBuffers.data());

        m_audioEffectBuffers.clear();
    }

} // namespace engine
