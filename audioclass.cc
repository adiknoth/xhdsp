#include "audioclass.h"
#include <glibmm/ustring.h>
#include <cmath>
#include <iostream>
#include <iomanip>


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


    if ((err = snd_ctl_open(&m_handle, m_cardname.c_str(), 0)) < 0) {
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



AudioClass::AudioClass(std::string cardname) :
	m_cardname(cardname)
{
    printf ("audioclass opened\n");
}

AudioClass::~AudioClass()
{
    close();
}
