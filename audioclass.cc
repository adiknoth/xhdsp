#include "audioclass.h"
#include <glibmm/ustring.h>
#include <cmath>
#include <iostream>
#include <iomanip>

const char dest_map_mf_ss[] = {
        0, 1, 2, 3, 4, 5, 6, 7, /* analog */
        16, 17, 18, 19, 20, 21, 22, 23, /* adat */
        24, 25, /* spdif */
        26, 27 /* phones */
};

const char channel_map_mf_ss[26] = {
        0, 1, 2, 3, 4, 5, 6, 7,         /* Line in */
        16, 17, 18, 19, 20, 21, 22, 23, /* ADAT */
        24, 25,                         /* SPDIF */
        26, 27,             /* Phones L+R, only a destination channel */
        -1, -1, -1, -1, -1, -1
};

const char *labels_mf_ss[20] = {
    "AN 1", "AN 2", "AN 3", "AN 4", "AN 5", "AN 6", "AN 7", "AN 8",
    "A 1", "A 2", "A 3", "A 4", "A 5", "A 6", "A 7", "A 8",
    "SP.L", "SP.R", "AN.L", "AN.R"
};


const char* AudioClass::getDestName(int dest)
{
    const char* ret = labels_mf_ss[dest];
    return ret;
}

const char* AudioClass::getSourceName(int source)
{
    const char* ret;

    if (source < getSourceChannels()/2) {
        ret = labels_mf_ss[source];
    } else {
        Glib::ustring *foo = new Glib::ustring("");
        foo->append("Out" + Glib::ustring::format(std::fixed, std::setw(3), (source - getSourceChannels()/2)));
        ret = foo->c_str();
        //ret = labels_mf_ss[source - getSourceChannels()/2];
    }

    return ret;
}

void AudioClass::close()
{
    if (m_handle)
        snd_ctl_close(m_handle);
}

void AudioClass::complain(int err)
{
        //std::cerr << "ALSA error:" << snd_strerror(err) << std::endl;
}

void AudioClass::open(char *cardname)
{
    int err;


    if ((err = snd_ctl_open(&m_handle, "hw:DSP", 0)) < 0) {
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
    long int ret;

    snd_ctl_elem_id_t *m_id;
    snd_ctl_elem_value_t *m_ctl;

    snd_ctl_elem_value_alloca(&m_ctl);
    snd_ctl_elem_id_alloca(&m_id);
    snd_ctl_elem_id_set_name(m_id, "Mixer");
    snd_ctl_elem_id_set_interface(m_id, SND_CTL_ELEM_IFACE_HWDEP);
    snd_ctl_elem_id_set_device(m_id, 0);
    snd_ctl_elem_id_set_index(m_id, 0);
    snd_ctl_elem_value_set_id(m_ctl, m_id);

    snd_ctl_elem_value_set_integer(m_ctl, 0, sourceToALSA(source));
    snd_ctl_elem_value_set_integer(m_ctl, 1, dest_map_mf_ss[dest]);

    if ((err = snd_ctl_elem_read(m_handle, m_ctl)) < 0) {
        complain(err);
        ret = -1;
    } else {
        ret = snd_ctl_elem_value_get_integer(m_ctl, 2);
    }

    //snd_ctl_elem_id_free(m_id);
    //snd_ctl_elem_value_free(m_ctl);

    return ret;

}

void AudioClass::setGain(int source, int dest, int gain)
{
    int err;
    snd_ctl_elem_id_t *m_id;
    snd_ctl_elem_value_t *m_ctl;

    if (!m_handle) {
        open();
    }

    snd_ctl_elem_value_alloca(&m_ctl);
    snd_ctl_elem_id_alloca(&m_id);
    snd_ctl_elem_id_set_name(m_id, "Mixer");
    snd_ctl_elem_id_set_interface(m_id, SND_CTL_ELEM_IFACE_HWDEP);
    snd_ctl_elem_id_set_device(m_id, 0);
    snd_ctl_elem_id_set_index(m_id, 0);
    snd_ctl_elem_value_set_id(m_ctl, m_id);

    snd_ctl_elem_value_set_integer(m_ctl, 0, sourceToALSA(source));
    snd_ctl_elem_value_set_integer(m_ctl, 1, dest_map_mf_ss[dest]);
    snd_ctl_elem_value_set_integer(m_ctl, 2, gain);

    if ((err = snd_ctl_elem_write(m_handle, m_ctl)) < 0) {
        complain(err);
    }
}

int AudioClass::setGaindB(int source, int dest, double gaindB)
{
    int gain;

    if (0.0 == gaindB)
        gain = 32768;
    else if (DBL_MAX == gaindB)
        gain = 0;
    else {
        double tmp = gaindB / 20.0;
        tmp += log10(32768.0);
        gain = pow(10, tmp);
    }

    if (gain > 65535)
        gain = 65535;

    printf ("gain to write: %i\n", gain);

    setGain(source, dest, gain);

    return gain;

}

double AudioClass::getGaindB(int source, int dest)
{
    long int gain = getGain(source, dest);
    double ret;

    switch (gain) {
        case 32768:
            ret = 0.0;
            break;
        case 0:
            ret = DBL_MAX;
            break;
        case 65535:
            ret = 6.0;
            break;
        default:
            ret = 20.0 * log10(gain/32768.0);
            break;
    }

    return ret;
}



AudioClass::AudioClass()
{
    printf ("audioclass opened\n");
}

AudioClass::~AudioClass()
{
    close();
}
