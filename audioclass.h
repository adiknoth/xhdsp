#ifndef _AUDIOCLASS_H
#define _AUDIOCLASS_H

#include <alsa/asoundlib.h>

class AudioClass
{
    public:
        AudioClass();
        virtual ~AudioClass();
        long int getGain(int source, int dest);
        double getGaindB(int source, int dest);
        int getSourceChannels();
        int getDestChannels();
        void open(char *cardname);
        void open();

    protected:
        snd_hwdep_info_t *m_info;

        snd_ctl_elem_id_t *m_id;
        snd_ctl_elem_value_t *m_ctl;
        snd_ctl_t *m_handle;

    private:
        void complain(int err);
        void close();
        int getPlaybackOffset();
        int sourceToALSA(int source);

};

#endif /* _AUDIOCLASS_H */
