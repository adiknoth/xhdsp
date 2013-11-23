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
        void setGain(int source, int dest, int gain);
        int setGaindB(int source, int dest, double gaindB);
        virtual int getSourceChannels() = 0;
        virtual int getDestChannels() = 0;
        virtual const char* getDestName(int dest) = 0;
        virtual const char* getSourceName(int source) = 0;
        void open(char *cardname);
        void open();
        void close();

    private:
        void complain(int err);
        virtual int getPlaybackOffset() = 0;
        virtual int sourceToALSA(int source) = 0;
        virtual int destToALSA(int source) = 0;
        snd_ctl_t *m_handle;
	std::string cardname;

};

#endif /* _AUDIOCLASS_H */
