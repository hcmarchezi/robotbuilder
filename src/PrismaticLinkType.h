// PrismaticLinkType.h: interface for the PrismaticLinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef PRISMATICLINKTYPE_H
#define PRISMATICLINKTYPE_H

#include "LinkType.h"

//namespace DMC
//{
//class PersistentPrismaticLinkType;
//}

using namespace DMC;

namespace PDC
{

class PrismaticLinkType : public LinkType
{
public:	
    PrismaticLinkType();
    virtual ~PrismaticLinkType();

	void SetJointAngle(double angle);
	double GetJointAngle();

    void CalculateFrame(double variableparam,double (* frame)[4][4]);



private:
	double m_joint_angle;	
};

}

#endif
