// Generated by dia2code
#ifndef RENDER__RENDU__H
#define RENDER__RENDU__H


namespace state {
  class GameState;
};
namespace render {
  class Editeur;
}

#include "Editeur.h"
#include "state/GameState.h"

namespace render {

  /// class Rendu - 
  class Rendu {
    // Associations
    // Attributes
  public:
    state::GameState * gamestate;
  private:
    int dimensionX;
    int dimensionY;
    // Operations
  public:
    Rendu ();
    ~Rendu ();
    void Click (int x, int y);
    void DrawEnemyroom ();
    void DrawDeck ();
    void DrawSleepRoom ();
    void DrawMap ();
    void DrawSpecialTrainingRoom ();
    void DrawGame (int dimensionX, int dimensionY);
    // Setters and Getters
  };

};

#endif
