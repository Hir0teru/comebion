// Generated by dia2code
#ifndef RENDER__EDITEUR__H
#define RENDER__EDITEUR__H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

namespace state {
  class Card;
  class Player;
  class Enemy;
  class Entity;
}

#include "state/Enemy.h"
#include "state/Entity.h"
#include "state/Player.h"
#include "state/Card.h"

namespace render {

  /// class Editeur - 
  class Editeur {
    // Associations
    // Attributes
  private:
    int x;
    int y;
    sf::RenderTexture  texture;
    // Operations
  public:
    Editeur ();
    ~Editeur ();
    Editeur (int x, int y, float scale, std::string image, int number);
    Editeur (int x, int y, float scale, state::Card* card, int statAttack, int statBlock);
    Editeur (int x, int y, float scale, state::Player* player);
    Editeur (int x, int y, float scale, std::unique_ptr<state::Enemy>& enemy);
    bool Click (int x, int y);
    int const GetX ();
    void SetX (int x);
    int const GetY ();
    void SetY (int y);
    sf::RenderTexture& GetTexture ();
    void SetEditeurPlayer (float scale, state::Player* player);
    void SetEditeurCard (float scale, state::Card* card, int statAttack, int statBlock);
    void SetEditeurEnemy (float scale, std::unique_ptr<state::Enemy>& enemy);
    void SetEditeurPile (float scale, std::string image, int number);
    // Setters and Getters
  };

};

#endif
