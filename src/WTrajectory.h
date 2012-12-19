#ifndef WTRAJECTORY_H
#define WTRAJECTORY_H

#include <qwidget.h>

namespace HIC
{

class WTrajectory : public Widget
{
  private:   
     vector< vector<qlineedit *> > m_trajectory; // Descricao da trajetoria
     vector< bool > m_exclude; // Posicoes de Robo Marcadas para Exclusao
  
  public:
     WTrajectory();
     ~WTrajectory();
     AddRobotPosition(); // Cria uma trajetoria vazia para ser preenchida
     ExcludeRobotPositions(); // Exclui Posicoes de Robo Selecionadas
     UpdateRobotPositions(): // Atualiza e Verifica as Posicoes de Robo
};

}
          
#endif