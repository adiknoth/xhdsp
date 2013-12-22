#include "multiface.h"
#include <glibmm/ustring.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

static const std::vector<char> dest_map_mf_ss = {
        0, 1, 2, 3, 4, 5, 6, 7, /* analog */
        16, 17, 18, 19, 20, 21, 22, 23, /* adat */
        24, 25, /* spdif */
        26, 27 /* phones */
};

static const std::vector<char> channel_map_mf_ss = {
        0, 1, 2, 3, 4, 5, 6, 7,         /* Line in */
        16, 17, 18, 19, 20, 21, 22, 23, /* ADAT */
        24, 25,                         /* SPDIF */
        26, 27,             /* Phones L+R, only a destination channel */
        -1, -1, -1, -1, -1, -1
};

static const std::vector<std::string> labels_mf_ss = {
    "AN 1", "AN 2", "AN 3", "AN 4", "AN 5", "AN 6", "AN 7", "AN 8",
    "A 1", "A 2", "A 3", "A 4", "A 5", "A 6", "A 7", "A 8",
    "SP.L", "SP.R", "AN.L", "AN.R"
};


std::string MultiFace::getDestName(int dest)
{
    return labels_mf_ss[dest];
}

std::string MultiFace::getSourceName(int source)
{
    std::string ret;

    if (source < getSourceChannels()/2) {
        ret = labels_mf_ss[source];
    } else {
        ret = "Out" + Glib::ustring::format(std::fixed, std::setw(3), (source - getSourceChannels()/2) + 1);
        //ret = labels_mf_ss[source - getSourceChannels()/2];
    }

    return ret;
}

int MultiFace::sourceToALSA(int source)
{
    if (source < getSourceChannels()/2) {
        /* input channels */
        return channel_map_mf_ss[source];
    } else {
        /* playback channels */
        return getPlaybackOffset()+channel_map_mf_ss[source-getSourceChannels()/2];
    }
};

MultiFace::MultiFace(std::string cardname, int index) :
	AudioClass(cardname, index)
{
	m_playbackoffset = 26;
	m_sourcechannels = 18*2;
	m_destchannels = 10*2;
	dest_map_ss = dest_map_mf_ss;
	channel_map_ss = channel_map_mf_ss;
    printf ("multiface opened\n");
}
