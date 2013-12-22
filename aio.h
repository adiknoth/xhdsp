#ifndef _AIO_H
#define _AIO_H

#include "audioclass.h"

class AIO : public AudioClass
{
public:
	AIO(std::string cardname, int index);
};


#endif /* _AIO_H */
