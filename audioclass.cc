#include "audioclass.h"
#include <iostream>

char dest_map_mf_ss[] = {
        0, 1, 2, 3, 4, 5, 6, 7, /* analog */
        16, 17, 18, 19, 20, 21, 22, 23, /* adat */
        24, 25, /* spdif */
        26, 27 /* phones */
};

char channel_map_mf_ss[26] = {
        0, 1, 2, 3, 4, 5, 6, 7,         /* Line in */
        16, 17, 18, 19, 20, 21, 22, 23, /* ADAT */
        24, 25,                         /* SPDIF */
        26, 27,             /* Phones L+R, only a destination channel */
        -1, -1, -1, -1, -1, -1
};


void AudioClass::close()
{
    snd_ctl_close(m_handle);
}

void AudioClass::complain(int err)
{
        std::cerr << "ALSA error:" << snd_strerror(err) << std::endl;
}

void AudioClass::open(char *cardname)
{
    int err;

    snd_hwdep_info_alloca(&m_info);
    snd_ctl_elem_value_alloca(&m_ctl);
    snd_ctl_elem_id_alloca(&m_id);
    snd_ctl_elem_id_set_name(m_id, "Mixer");
    snd_ctl_elem_id_set_interface(m_id, SND_CTL_ELEM_IFACE_HWDEP);
    snd_ctl_elem_id_set_device(m_id, 0);
    snd_ctl_elem_id_set_index(m_id, 0);
    snd_ctl_elem_value_set_id(m_ctl, m_id);

    if ((err = snd_ctl_open(&m_handle, "hw:DSP", SND_CTL_NONBLOCK)) < 0) {
        complain(err);
        exit (1);
    }
}

void AudioClass::open()
{
    open((char*)"hw:DSP");
}

int AudioClass::getPlaybackOffset() { return 26; };

int AudioClass::sourceToALSA(int source)
{
    if (source < getSourceChannels()/2) {
        /* input channels */
        return channel_map_mf_ss[source];
    } else {
        /* playback channels */
        return getPlaybackOffset()+channel_map_mf_ss[source-getSourceChannels()/2];
    }
};

int AudioClass::getSourceChannels()
{
    return 18*2;
}

int AudioClass::getDestChannels()
{
    return 10*2;
}

long int AudioClass::getGain(int source, int dest)
{
    int err;

    snd_ctl_elem_value_set_integer(m_ctl, 0, sourceToALSA(source));
    snd_ctl_elem_value_set_integer(m_ctl, 1, dest_map_mf_ss[dest]);

    if ((err = snd_ctl_elem_read(m_handle, m_ctl)) < 0) {
        complain(err);
        exit (2);
    }

    return snd_ctl_elem_value_get_integer(m_ctl, 2);

}

double AudioClass::getGaindB(int source, int dest)
{
    long int gain = getGain(source, dest);
    //double db = 20.0 * log10(gain);
    return 0.0;
}



AudioClass::AudioClass()
{
}

AudioClass::~AudioClass()
{
    close();
}
