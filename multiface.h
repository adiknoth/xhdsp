#ifndef _MULTIFACE_H
#define _MULTIFACE_H

#include "audioclass.h"

class MultiFace : public AudioClass
{
public:
	MultiFace(std::string cardname, int index);
	std::string getDestName(int dest);
	std::string getSourceName(int source);

private:
        int sourceToALSA(int source);
};


#endif /* _MULTIFACE_H */
