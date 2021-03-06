#include "audioclass.h"
#include <cfloat>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <glibmm/ustring.h>


void AudioClass::close()
{
    if (m_handle)
        snd_ctl_close(m_handle);
}

void AudioClass::complain(int err)
{
        //std::cerr << "ALSA error:" << snd_strerror(err) << std::endl;
}

void AudioClass::open()
{
    int err;


    if ((err = snd_ctl_open(&m_handle, m_devicename.c_str(), 0)) < 0) {
        complain(err);
        exit (1);
    }
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
    snd_ctl_elem_value_set_integer(m_ctl, 1, destToALSA(dest));

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
        printf ("Kein handle. WTF?");
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
    snd_ctl_elem_value_set_integer(m_ctl, 1, destToALSA(dest));
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

    if (gain < 0)
	    gain = 0;


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


std::string AudioClass::getCardname()
{
	return m_cardname;
}

int AudioClass::destToALSA(int dest)
{
    return dest_map_ss[dest];
}

int AudioClass::sourceToALSA(int source)
{
    if (source < m_inputchannels) {
        /* input channels */
        return channel_map_in_ss[source];
    } else {
        /* playback channels */
        return getPlaybackOffset()+channel_map_out_ss[source-m_inputchannels];
    }
};

std::string AudioClass::getDestName(int dest)
{
    return labels_out_ss[dest];
}

std::string AudioClass::getSourceName(int source)
{
    std::string ret;

    if (source < m_inputchannels) {
        ret = labels_in_ss[source];
    } else {
        ret = "Out" + Glib::ustring::format(std::fixed, std::setw(3), (source - m_inputchannels) + 1);
    }

    return ret;
}


AudioClass::AudioClass(std::string cardname, int index) :
	m_cardname(cardname)
{
    m_devicename = "hw:" + std::to_string(index);
    printf ("audioclass opened\n");
}

AudioClass::~AudioClass()
{
    close();
}
