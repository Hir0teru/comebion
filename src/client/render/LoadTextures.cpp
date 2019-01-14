#include "LoadTextures.h"
#include <iostream>
#include <stdexcept>

using namespace render;


LoadTextures::LoadTextures(){


  sf::Sprite sprite;
  sf::Texture texture;

  // texturePile:
  if (!texture.loadFromFile("res/textures/cards/back_card_fin.png")){
    std::cout << "error with pile image" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TexturePile = sprite;


  //textureCards
  if( !texture.loadFromFile("res/textures/cards/card_air.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if( !texture.loadFromFile("res/textures/cards/card_water.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if( !texture.loadFromFile("res/textures/cards/card_earth.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if( !texture.loadFromFile("res/textures/cards/card_fire.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  //TextureIcon (ordre alphabétique)
  if(!texture.loadFromFile("res/textures/icons/attack_debuff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/attack_down.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/attack_up.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/attack.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/block_down.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/block_up.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/block.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/buff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/debuff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/evade.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/heal_block.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/heal_buff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/heal.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/retaliate.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/sleep.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/special_training.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/target.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureCard.push_back(sprite);

  //TexturePlayer

  if(!texture.loadFromFile("res/textures/Player/Aang.png")){
    std::cout << "error with player image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TexturePlayer.push_back(sprite);

  if(!texture.loadFromFile("res/textures/Player/Korra.png")){
    std::cout << "error with player image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TexturePlayer.push_back(sprite);

  //TextureEnemy

  //TextureElement

  if(!texture.loadFromFile("res/textures/icons/air.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureElement.push_back(sprite);

  if(!texture.loadFromFile("res/textures/icons/water.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  sprite.setTexture(texture);
  TextureElement.push_back(sprite);

if(!texture.loadFromFile("res/textures/icons/earth.png")){
  std::cout << "error with enemy image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
sprite.setTexture(texture);
TextureElement.push_back(sprite);

if(!texture.loadFromFile("res/textures/icons/fire.png")){
std::cout << "error with enemy image"<<std::endl;
throw std::invalid_argument("error with argument");
}
sprite.setTexture(texture);
TextureElement.push_back(sprite);



}

LoadTextures::~LoadTextures(){}
