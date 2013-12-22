#include "aio.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

static const std::vector<char> dest_map_aio_ss = {
   0,  1, // Analogue
   8,  9, // AES
  10, 11, // SPDIF
  12, 13, 14, 15, 16, 17, 18, 19, // ADAT
   6, 7, // Phones
   2, 3, // AEB 1+2
   4, 5  // AEB 3+4
};

static const std::vector<char> channel_map_aio_in_ss = {
        0, 1,                   /* line in */
        8, 9,                   /* aes in, */
        10, 11,                 /* spdif in */
        12, 13, 14, 15, 16, 17, 18, 19, /* ADAT in */
        2, 3, 4, 5,             /* AEB */
        -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
};


static const std::vector<std::string> labels_aio_in_ss = {
  "AN 1",  "AN 2",
  "SP.L", "SP.R",
  "AES.L",  "AES.R",
  "A 1", "A 2", "A 3", "A 4",
  "A 5", "A 6", "A 7", "A 8",
  "AEB 1", "AEB 2", "AEB 3," "AEB 4"
};


AIO::AIO(std::string cardname, int index) :
	AudioClass(cardname, index)
{
	m_playbackoffset = 64;
	m_inputchannels = 18;
	m_sourcechannels = m_inputchannels + 20; // 18in + 20 playback (phones)
	m_destchannels = 20;
	dest_map_ss = dest_map_aio_ss;
	channel_map_in_ss = channel_map_aio_in_ss;
	channel_map_out_ss = dest_map_aio_ss; // luckily, they're the same
	labels_in_ss = labels_aio_in_ss;
	labels_out_ss = labels_aio_in_ss;
	labels_out_ss.insert(labels_out_ss.begin()+14, "PH.L");
	labels_out_ss.insert(labels_out_ss.begin()+15, "PH.R");
	printf ("AIO opened\n");
}
