// LinkType.cpp: implementation of the LinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "LinkType.h"

#include "PersistentLinkType.h"

#include <GL/glu.h>
#include <stdio.h> // biblioteca C necessaria para leitura de arquivo binario (3DS)
                   // no metodo LoadGeometry



//////////////////////////////////////////////////////////////////////
// Definicoes de Constantes para leitura de arquivo 3DS
//////////////////////////////////////////////////////////////////////
// Color Chunks
#define RGB1	0x0010 /* cor global RGB */
#define RGB2	0x0011 /* cor global RGB */

/* Main Chunk */
#define MAIN_CHUNK				0x4D4D	/* Main Chunk				*/
	#define VERSION				0x0002  /* Versao do Arquivo 3DS	*/

	#define CHUNK_3D_EDITOR		0x3D3D	/* Chunk do Editor 3D		*/  

		#define MESH_VERSION		0x3D3E	/* Versao da Malha			*/

		#define OBJECT_BLOCK		0x4000	/* Bloco de Objeto 3D		*/
			#define TRIANGULAR_MESH	0x4100	/* Objeto de Malha Triang	*/
				#define VERTICES	0x4110	/* Lista de Vertices X Y Z  */
				#define FACES		0x4120	/* Descricao  das faces		*/
					#define FACES_MAT_LIST 0x4130	/* Lista de material das faces */
				#define LOCAL_COORD	0x4160	/* Coordenadas Locais do Obj*/
				#define OBJ_COLOR	0x4165	/* Cor do Objeto			*/
			#define CAMERA			0x4700	/* Camera					*/

		#define MATERIAL_BLOCK		0xAFFF	/* Bloco de Materiais		*/
			#define MAT_AMB_COLOR	0xA010	/* Cor Ambiente				*/
			#define MAT_DIF_COLOR	0xA020	/* Cor Difusa				*/
			#define MAT_SPE_COLOR	0xA030	/* Cor Especular			*/
			#define TEXTURE_MAP1	0xA200	/* Material de Map de Textur*/
				#define MAP_FILENAME 0xA300	/* Arquivo de Mapeamento    */

	#define KEYFRAMER_CHUNK			0xB000	/* Chunk do KeyFramer */



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::LinkType::LinkType()
{
    m_coordinate = NULL;
	m_link_function = -1;
}

PDC::LinkType::~LinkType()
{
    if (m_coordinate != NULL)
        delete m_coordinate;
}

string PDC::LinkType::GetLinkTypeName()
{
	return m_name;
}

void PDC::LinkType::SetLinkTypeName(string name)
{
	m_name = name;
}

long PDC::LinkType::GetLinkTypeFunction()
{
    return m_link_function;
}

void PDC::LinkType::SetLinkTypeFunction(long function)
{
    m_link_function = function;
}

void PDC::LinkType::GetCoordinateSystem(double (*coordinate)[4][4])
{
    // Os elementos da matriz de frame e do sistema de coordenadas
    // s�o posicionados em locais diferentes daqueles que estamos
    // acostumados para seguir um padr�o estipulado pelo OpenGL
    
    (*coordinate)[0][0] = m_coordinate[0];
    (*coordinate)[1][0] = m_coordinate[1];
    (*coordinate)[2][0] = m_coordinate[2];
    (*coordinate)[3][0] = m_coordinate[3];
    (*coordinate)[0][1] = m_coordinate[4];
    (*coordinate)[1][1] = m_coordinate[5];
    (*coordinate)[2][1] = m_coordinate[6];
    (*coordinate)[3][1] = m_coordinate[7];
    (*coordinate)[0][2] = m_coordinate[8];
    (*coordinate)[1][2] = m_coordinate[9];
    (*coordinate)[2][2] = m_coordinate[10];
    (*coordinate)[3][2] = m_coordinate[11];
    (*coordinate)[0][3] = m_coordinate[12];
    (*coordinate)[1][3] = m_coordinate[13];
    (*coordinate)[2][3] = m_coordinate[14];
    (*coordinate)[3][3] = m_coordinate[15];
    
}

void PDC::LinkType::SetCoordinateSystem(double coordinate[4][4])
{
    delete m_coordinate;
    
    m_coordinate = new double[16];

    // Pega o formato de matriz i j e converte para o 
    // formato j i de acordo com o padr�o do OpenGL

    m_coordinate[0] =  coordinate[0][0];
    m_coordinate[1] =  coordinate[1][0];
    m_coordinate[2] =  coordinate[2][0];
    m_coordinate[3] =  coordinate[3][0];
    m_coordinate[4] =  coordinate[0][1];
    m_coordinate[5] =  coordinate[1][1];
    m_coordinate[6] =  coordinate[2][1];
    m_coordinate[7] =  coordinate[3][1];
    m_coordinate[8] =  coordinate[0][2];
    m_coordinate[9] =  coordinate[1][2];
    m_coordinate[10] = coordinate[2][2];
    m_coordinate[11] = coordinate[3][2];
    m_coordinate[12] = coordinate[0][3];
    m_coordinate[13] = coordinate[1][3];
    m_coordinate[14] = coordinate[2][3];
    m_coordinate[15] = coordinate[3][3];
}

void PDC::LinkType::GetJointRestriction(double &lowestmovement, double &highestmovement)
{
    lowestmovement  = m_lowest_movement;
    highestmovement = m_highest_movement;
}

void PDC::LinkType::SetJointRestriction(double lowestmovement, double highestmovement)
{
    m_lowest_movement  = lowestmovement;
    m_highest_movement = highestmovement;
}

bool PDC::LinkType::LoadGeometry(string filename3DS,string objectname)
{
    vector<Point> vetpoints;

	// Passa o nome do arquivo e do objeto para
	// o correspondente objeto persistente
	this->m_persistentlinktype->SetGeometryFileName(filename3DS);
	this->m_persistentlinktype->SetGeometricObject(objectname);

    // Arquivo de leitura binaria
    FILE * arq = fopen(filename3DS.c_str(),"rb");

	if (arq==NULL) {
		printf ("Erro na leitura do arquivo %s.\n",filename3DS.c_str());
		return false;
	}

    char carac;
    string name;
	int k; // contador
	unsigned short num_vertices, num_faces;
	// WORD  -> short (2 bytes)
	// DWORD -> long  (4 bytes)
	// FLOAT -> float (4 bytes)
	unsigned short chunk_id;		// Identificacao do chunk
	unsigned long  chunk_length; // Tamanho do chunk em bytes

    long blue  = 255;
    long red   = 255;
    long green = 255;

    do {

		if (fread(&chunk_id,2,1,arq)==0) {
			fclose(arq);
			printf ("Objetos Mesh Lidos: \n");
			return true;
		}

		switch(chunk_id) {

		case(MAIN_CHUNK):
			printf ("Chunk principal achado\n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk(Arquivo): %li\n",chunk_length);

			break;

		case(VERSION):
			printf ("Chunk da vers�o\n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);

			long versao;
			fread(&versao,4,1,arq);
			printf ("versao %li\n",versao);
			break;

		case(CHUNK_3D_EDITOR):
			printf ("Chunk do Editor 3D\n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);
			break;

		case(OBJECT_BLOCK):
			printf ("Definicao de um objeto \n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);

            // � um novo objeto 3D
            vetpoints.clear();

            // Nome do objeto
			name = "";
            do 	{
				fread(&carac,1,1,arq);
				if (carac != 0) name = name + carac;
			} while (carac!=0);
			printf ("nome objeto = %s \n",name.c_str());
			break;

        case(TRIANGULAR_MESH):
			printf ("Definicao de uma malha triangular\n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);
			break;

		case(VERTICES):
			printf ("Lista de Vertices\n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);

			fread(&num_vertices,2,1,arq);
			printf ("numero de vertices=%i\n",num_vertices);

			for (k=0;k<num_vertices;k++) {
                float x;
                float y;
                float z;
                fread(&x,4,1,arq);
				fread(&y,4,1,arq);
				fread(&z,4,1,arq);

                Point ponto;
                ponto.x = x;
                ponto.y = y;
                ponto.z = z;
                vetpoints.push_back(ponto);

			}
			break;

        case(FACES):
			printf ("Lista de faces\n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);

			fread(&num_faces,2,1,arq);
			printf ("numero de faces=%i\n",num_faces);

            for (k=0;k<num_faces;k++) {
                unsigned short faceA;
                unsigned short faceB;
                unsigned short faceC;
                unsigned short flag;
                Face  face;

				fread(&faceA,2,1,arq);
				fread(&faceB,2,1,arq);
				fread(&faceC,2,1,arq);
				fread(&flag, 2,1,arq);

                if (name == objectname)
                {
                    face.SetParameters(vetpoints[faceA],vetpoints[faceB],vetpoints[faceC],red,green,blue);
                    m_faces.push_back(face);
                }

            }
			//calcula as normais do objeto
			break;

        default:
			printf ("Chunk Nao Definido \n");
			fread(&chunk_length,4,1,arq);
			printf ("Tamanho do Chunk: %li\n",chunk_length);
			// Pula o chunk desconhecido
			fseek(arq,chunk_length-6,SEEK_CUR);
			break;
		}

	} while (!(feof(arq)));

	fclose(arq);
	printf ("Objetos Mesh Lidos: \n");

    return false;
}

bool PDC::LinkType::LoadLinkType(string name)
{
    return false;
}

bool PDC::LinkType::SaveLinkType()
{
    return false;
}

double PDC::LinkType::GetLinkLength()
{
    return m_link_length;
}


void PDC::LinkType::SetLinkLength(double length)
{
    m_link_length = length;
}

double PDC::LinkType::GetLinkTwist()
{
    return m_link_twist;
}

void PDC::LinkType::SetLinkTwist(double twist)
{
    m_link_twist = twist;
}

void PDC::LinkType::Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Move para o sistema de coordenadas para a primeira junta do
    // tipo de link
    glMultMatrixd(m_coordinate);

    // Desenhas todas as faces do tipo de link
    for (unsigned long count = 0;count < m_faces.size(); count++)
        m_faces[count].Draw();

    glPopMatrix();
}

string PDC::LinkType::GetSlideType()
{
	return m_slide_type;
}