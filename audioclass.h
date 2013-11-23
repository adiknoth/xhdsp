#ifndef _AUDIOCLASS_H
#define _AUDIOCLASS_H

#include <alsa/asoundlib.h>
#include <string>

class AudioClass
{
    public:
        AudioClass(std::string& cardname);
        virtual ~AudioClass();
        long int getGain(int source, int dest);
        double getGaindB(int source, int dest);
        void setGain(int source, int dest, int gain);
        int setGaindB(int source, int dest, double gaindB);
        virtual int getSourceChannels() { return m_sourcechannels; };
        virtual int getDestChannels() { return m_destchannels; };
        virtual const char* getDestName(int dest) = 0;
        virtual const char* getSourceName(int source) = 0;
        void open();
        void close();

    protected:
        virtual int getPlaybackOffset() { return m_playbackoffset; };
	int m_playbackoffset;
	int m_sourcechannels;
	int m_destchannels;

    private:
        void complain(int err);
        virtual int sourceToALSA(int source) = 0;
        virtual int destToALSA(int source) = 0;
        snd_ctl_t *m_handle;
	std::string m_cardname;

};

#endif /* _AUDIOCLASS_H */
