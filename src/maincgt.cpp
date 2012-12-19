#ifdef WIN32
#include <windows.h>
#endif

#include "Application.h"
#include <qapplication.h>

using namespace PDC;
using namespace DMC;
using namespace TMC;
using namespace HIC;


int main(int argc, char ** argv)
{
    /*
    double coord[4][4];
    RevoluteLinkType * basetype;
    coord[0][0]=0.0;  coord[0][1]=1.0; coord[0][2]=0.0; coord[0][3]=77.0;
    coord[1][0]=0.0;  coord[1][1]=0.0; coord[1][2]=1.0; coord[1][3]=-15.0;
    coord[2][0]=1.0;  coord[2][1]=0.0; coord[2][2]=0.0; coord[2][3]=-330.0;
    coord[3][0]=0.0;  coord[3][1]=0.0; coord[3][2]=0.0; coord[3][3]=1.0;
    basetype = new RevoluteLinkType();
    basetype->LoadGeometry("robotarm.3ds","Base");
    basetype->SetCoordinateSystem(coord);
    basetype->SetLinkLength(0.0);
    basetype->SetLinkTwist(0.0);
    basetype->SetLinkOffset(550.0);
    basetype->SetLinkTypeFunction(BASE);

    basetype->m_persistentrevolutelinktype->Save("base.tpl");
    */

   Application app;
   return app.Exec(argc,argv);
}

