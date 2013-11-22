#ifndef _AUDIOCLASS_H
#define _AUDIOCLASS_H

#include <alsa/asoundlib.h>
#include <string>

class AudioClass
{
    public:
        AudioClass();
        virtual ~AudioClass();
        long int getGain(int source, int dest);
        double getGaindB(int source, int dest);
        int getSourceChannels();
        int getDestChannels();
        const char* getDestName(int dest);
        const char* getSourceName(int source);
        void open(char *cardname);
        void open();
        void close();

    private:
        void complain(int err);
        int getPlaybackOffset();
        int sourceToALSA(int source);
        snd_ctl_t *m_handle;

};

#endif /* _AUDIOCLASS_H */
