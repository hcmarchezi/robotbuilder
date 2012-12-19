// Link.h: interface for the Link class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINK_H
#define LINK_H

#include "RevoluteLinkType.h"
#include "PrismaticLinkType.h"
#include "GraphicObject.h"

using namespace PDC;

namespace PDC
{

class Link : public GraphicObject
{
public:
        Link(LinkType * linktype);
        virtual ~Link();

        LinkType * GetLinkType();

	long   GetLinkNumber();
	void   SetLinkNumber(long number);

	long   GetLinkFunction();

	void   Draw();
        double GetVariableLinkParam();
        void   SetVariableLinkParam(double movement);

	bool   LoadLink(string linkname);
	bool   SaveLink();

	bool   VerifyJointRestriction(double movement);

private:
        // Numero do Link na cadeia de Links do Robo do qual eles faz parte
	long   m_number;
        // Valor do parametro variavel que descreve o Link do Robo, pode ser
        // o angulo ou offset da junta
	double m_variable_link_param;
        // Todo Link eh de um tipo de Link, dai o relacionamento abaixo
	LinkType * m_linktype;
        // Embora seja um ponteiro para double (formato OpenGL), na verdade
        // trata-se de uma matriz 4x4
        double * m_frame;
};

}

#endif
