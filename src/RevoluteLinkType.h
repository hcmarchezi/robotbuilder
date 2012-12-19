// RevoluteLinkType.h: interface for the RevoluteLinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REVOLUTELINKTYPE_H
#define REVOLUTELINKTYPE_H

#include "LinkType.h"

//namespace DMC
//{
//class PersistentRevoluteLinkType;
//}

using namespace DMC;

namespace PDC
{

class RevoluteLinkType : public LinkType
{
public:
	RevoluteLinkType();
	virtual ~RevoluteLinkType();

  	void SetLinkOffset(double offset);
  	double GetLinkOffset();

    void CalculateFrame (double variableparam,double (* frame)[4][4]);

private:
	double m_link_offset;
        // OBS (20/02/2003): Onde esta o atributo que guarda o valor do
        //                   parametro variavel ?
};

}

#endif

