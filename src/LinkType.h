// LinkType.h: interface for the LinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINKTYPE_H
#define LINKTYPE_H

#include "Face.h"
#include "GraphicObject.h"

#include <vector>
#include <string>

#define BASE            0
#define ACTUATOR        1
#define END_EFFECTOR    2

namespace DMC
{
class PersistentLinkType;
}

using namespace std;
using namespace PDC;
using namespace DMC;

namespace PDC
{

class LinkType : public GraphicObject
{
public:
        LinkType();
        virtual ~LinkType();

        void Draw();
	virtual void CalculateFrame(double variableparam,double (* frame)[4][4])=0;

        void SetLinkTwist(double twist);
	double GetLinkTwist();
	void SetLinkLength (double length);
	double GetLinkLength();

	bool SaveLinkType();
	bool LoadLinkType (string name);
	bool LoadGeometry (string filename3DS, string objectname);

	void SetJointRestriction (double lowestmovement,double highestmovement);
	void GetJointRestriction(double &lowestmovement,double &highestmovement);

	void SetCoordinateSystem(double coordinate[4][4]);
	void GetCoordinateSystem(double (*coordinate)[4][4]);

	void SetLinkTypeFunction(long function);
	long GetLinkTypeFunction();

	void SetLinkTypeName(string name);
	string GetLinkTypeName();

	string GetSlideType();

	// Objeto responsave pela persistencia do tipo de link
	PersistentLinkType * m_persistentlinktype;

private:
	// nome do tipo de link (Ex: Puma Base Link)
	string m_name;
	// Embora seja um ponteiro para double (formato OpenGL), esse atributo sera
	// manipulado pelos metodos de Sistemas de Coordenadas como uma matriz 4x4
	double * m_coordinate;
	// Funcao do Tipo de Link, ou seja, (BASE (0), ACTUATOR (1), END_EFFECTOR (2))
	long   m_link_function;
	// Maior abertura que a junta controlada por esse Tipo de Link pode ter
	double m_highest_movement;
	// Menor abertura que a junta controlada por esse Tipo de Link pode ter
	double m_lowest_movement;
	// Geometria do objeto que e composta por um vetor de faces triangulares
	vector<Face> m_faces;
protected:
	// Os atributos abaixo descrevem o tamanho e a torcao do Tipo de Link e
	// foram criados como protected pois sao referenciados pelas subclasses
	// PrismaticLinkType e RevoluteLinkType para o calculo do frame
	double m_link_length;
	double m_link_twist;
	// Informa o tipo de link (Usado apenas pelas classes que herdam desta)
	string m_slide_type;
};

}

#endif
