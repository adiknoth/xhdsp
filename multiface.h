#ifndef _MULTIFACE_H
#define _MULTIFACE_H

#include "audioclass.h"

class MultiFace : public AudioClass
{
public:
	MultiFace(std::string cardname, int index);
};


#endif /* _MULTIFACE_H */
