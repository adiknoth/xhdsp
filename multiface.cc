#include "multiface.h"
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


MultiFace::MultiFace(std::string cardname, int index) :
	AudioClass(cardname, index)
{
	m_playbackoffset = 26;
	m_inputchannels = 18;
	m_sourcechannels = 2 * m_inputchannels;
	m_destchannels = 10*2;
	dest_map_ss = dest_map_mf_ss;
	channel_map_in_ss = channel_map_mf_ss;
	channel_map_out_ss = channel_map_mf_ss;
	labels_in_ss = labels_mf_ss;
	labels_out_ss = labels_mf_ss;
    printf ("multiface opened\n");
}
