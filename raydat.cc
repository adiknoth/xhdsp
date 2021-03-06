#include "raydat.h"
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


RayDat::RayDat(std::string cardname, int index) :
	AudioClass(cardname, index)
{
	m_playbackoffset = 64;
	m_inputchannels = 36;
	m_sourcechannels = 2 * m_inputchannels;
	m_destchannels = 36;
	dest_map_ss = dest_map_raydat_ss;
	channel_map_in_ss = channel_map_raydat_ss;
	channel_map_out_ss = channel_map_raydat_ss;
	labels_in_ss = labels_raydat_ss;
	labels_out_ss = labels_raydat_ss;
    printf ("RayDAT opened\n");
}
