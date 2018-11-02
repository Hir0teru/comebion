// Generated by dia2code
#ifndef RENDER__RENDU__H
#define RENDER__RENDU__H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

namespace state {
  class GameState;
};
namespace render {
  class Editeur;
};
namespace state {
  class Card;
  class Enemy;
  class Player;
  class SpecialTrainingRoom;
  class SleepRoom;
  class EnemyRoom;
}

#include "Editeur.h"
#include "state/Enemy.h"
#include "state/SpecialTrainingRoom.h"
#include "state/SleepRoom.h"
#include "state/EnemyRoom.h"
#include "state/GameState.h"

namespace render {

  /// class Rendu - 
  class Rendu {
    // Associations
    // Attributes
  private:
    int dimensionX;
    int dimensionY;
    state::GameState * gamestate;
    std::vector<std::unique_ptr<Editeur>> textureCards;
    std::vector<std::unique_ptr<Editeur>> texturePiles;
    std::vector<std::unique_ptr<Editeur>> textureEnemies;
    std::vector<std::unique_ptr<Editeur>> texturePlayers;
    sf::RenderTexture background;
    /// 		
    sf::RenderTexture texture;
    sf::RenderTexture textureMap;
    // Operations
  public:
    Rendu ();
    ~Rendu ();
    void Click (int x, int y);
    void DrawInsideRoom ();
    state::GameState*& GetGameState ();
    void SetTextureCards (std::vector<std::unique_ptr<Editeur>>& textureCards);
    void SetTextureEnemies (std::vector<std::unique_ptr<Editeur>>& textureEnemies);
    /// 	
    /// @param texturePlayers		(???) 
    void SetTexturePlayers (std::vector<std::unique_ptr<Editeur>>& texturePlayers);
    std::vector<std::unique_ptr<Editeur>>& GetTextureCards ();
    std::vector<std::unique_ptr<Editeur>>& GetTextureEnemies ();
    std::vector<std::unique_ptr<Editeur>>& GetTexturePlayers ();
    sf::RenderTexture& GetBackground ();
    void SetBackground (std::string image);
    int GetDimensionX ();
    int GetDimensionY ();
    void SetDimensionX (int dimensionX);
    void SetDimensionY (int dimensionY);
    void ChangeTextureCard (float scale, state::Card* card, int index, int statAttack, int statBlock);
    void ChangeTextureEnemy (float scale, std::unique_ptr<state::Enemy>& enemy, int index);
    void ChangeTexturePlayer (float scale, state::Player* player, int index);
    std::vector<std::unique_ptr<Editeur>>& GetTexturePiles ();
    void SetTexturePiles (std::vector<std::unique_ptr<Editeur>>& texturePiles);
    void SetTexturePile (float scale, int index, std::string image, int number);
    void RemoveEnemy (int index);
    void RemovePlayer (int index);
    void RemoveCard (int index);
    void RemovePile (int index);
    void AddTexturePile (int x, int y, float scale, std::string image, int number);
    void AddTextureCard (int x, int y, float scale, state::Card * card, int statAttack, int statBlock);
    void AddTexturePlayer (int x, int y, float scale, state::Player* player);
    void AddTextureEnemy (int x, int y, float scale, std::unique_ptr<state::Enemy>& enemy);
    void RemoveEnemies ();
    void RemovePlayers ();
    void RemovePiles ();
    void RemoveCards ();
    sf::RenderTexture& GetTexture ();
    sf::RenderTexture& GetTextureMap ();
    void SetTextureMap (float scale);
    void SetTextureRoom ();
    // Setters and Getters
  };

};

#endif
