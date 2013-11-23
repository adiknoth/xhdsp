#ifndef _MULTIFACE_H
#define _MULTIFACE_H

#include "audioclass.h"

class MultiFace : public AudioClass
{
public:
	int getSourceChannels();
	int getDestChannels();
        const char* getDestName(int dest);
        const char* getSourceName(int source);

private:
        int getPlaybackOffset();
        int sourceToALSA(int source);
        int destToALSA(int source);
};


#endif /* _MULTIFACE_H */
