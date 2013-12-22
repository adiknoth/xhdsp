#include "raydat.h"
#include <glibmm/ustring.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

static const std::vector<char> dest_map_raydat_ss = {
        4, 5, 6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27,
        28, 29, 30, 31, 32, 33, 34, 35,
        0, 1, 2, 3
};

static const std::vector<char> channel_map_raydat_ss = {
        4, 5, 6, 7, 8, 9, 10, 11,       /* ADAT 1 */
        12, 13, 14, 15, 16, 17, 18, 19, /* ADAT 2 */
        20, 21, 22, 23, 24, 25, 26, 27, /* ADAT 3 */
        28, 29, 30, 31, 32, 33, 34, 35, /* ADAT 4 */
        0, 1,                   /* AES */
        2, 3,                   /* SPDIF */
        -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
};


static const std::vector<std::string> labels_raydat_ss = {
  "A1.1", "A1.2", "A1.3", "A1.4", "A1.5", "A1.6", "A1.7", "A1.8",
  "A2.1", "A2.2", "A2.3", "A2.4", "A2.5", "A2.6", "A2.7", "A2.8",
  "A3.1", "A3.2", "A3.3", "A3.4", "A3.5", "A3.6", "A3.7", "A3.8",
  "A4.1", "A4.2", "A4.3", "A4.4", "A4.5", "A4.6", "A4.7", "A4.8",
  "AES.L", "AES.R",
  "SP.L", "SP.R"
};


std::string RayDat::getSourceName(int source)
{
    std::string ret;

    if (source < getSourceChannels()/2) {
        ret = labels_raydat_ss[source];
    } else {
        ret = "Out" + Glib::ustring::format(std::fixed, std::setw(3), (source - getSourceChannels()/2) + 1);
        //ret = labels_mf_ss[source - getSourceChannels()/2];
    }

    return ret;
}

RayDat::RayDat(std::string cardname, int index) :
	AudioClass(cardname, index)
{
	m_playbackoffset = 64;
	m_sourcechannels = 36*2;
	m_destchannels = 36;
	dest_map_ss = dest_map_raydat_ss;
	channel_map_ss = channel_map_raydat_ss;
	labels_ss = labels_raydat_ss;
    printf ("RayDAT opened\n");
}
