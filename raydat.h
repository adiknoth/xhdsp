#ifndef _RAYDAT_H
#define _RAYDAT_H

#include "audioclass.h"

class RayDat : public AudioClass
{
public:
	RayDat(std::string cardname, int index);
	std::string getSourceName(int source);
};


#endif /* _RAYDAT_H */
