#include "LoadTextures.h"
#include <iostream>
#include <stdexcept>

using namespace render;


LoadTextures::LoadTextures(){


  //sf::Sprite sprite;
  sf::Texture texture;
  //sf::Image image;

  // texturePile:
  if (!texture.loadFromFile("res/textures/cards/back_card_fin.png")){
    std::cout << "error with pile image" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  // if (!image.loadFromFile("res/textures/cards/back_card_fin.png")){
  //   std::cout << "error with pile image" << std::endl;
  //   throw std::invalid_argument("error with argument");
  // }
  // sprite.setTexture(texture);
  texturePile = texture;


  //textureCard
  if( !texture.loadFromFile("res/textures/cards/card_air.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  ////texture.setTexture(texture);
  textureCard.push_back(texture);

  if( !texture.loadFromFile("res/textures/cards/card_water.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  ////texture.setTexture(texture);
  textureCard.push_back(texture);

  if( !texture.loadFromFile("res/textures/cards/card_earth.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  ////texture.setTexture(texture);
  textureCard.push_back(texture);

  if( !texture.loadFromFile("res/textures/cards/card_fire.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  ////texture.setTexture(texture);
  textureCard.push_back(texture);

  //textureIcon (ordre alphabétique)
  if(!texture.loadFromFile("res/textures/icons/attack_debuff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  ////texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/attack_down.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  ////texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/attack_up.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/attack.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/block_down.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/block_up.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/block.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/buff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/debuff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/evade.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/heal_block.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/heal_buff.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/heal.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/retaliate.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/sleep.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/special_training.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/target.png")){
    std::cout << "error with attack"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureIcon.push_back(texture);

  //texturePlayer

  if(!texture.loadFromFile("res/textures/Player/Aang.png")){
    std::cout << "error with player image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  texturePlayer.push_back(texture);

  if(!texture.loadFromFile("res/textures/Player/Korra.png")){
    std::cout << "error with player image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  texturePlayer.push_back(texture);

  //textureEnemy
  //air
  if(!texture.loadFromFile("res/textures/Enemy/Air/1.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Air/2.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Air/3.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Air/bison.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  //Water

  if(!texture.loadFromFile("res/textures/Enemy/Water/1.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Water/2.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Water/3.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Water/La.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  //Earth
  if(!texture.loadFromFile("res/textures/Enemy/Earth/1.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Earth/2.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Earth/3.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Earth/badgermole.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  //Fire
  if(!texture.loadFromFile("res/textures/Enemy/Fire/1.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Fire/2.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Fire/3.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Fire/blue_dragon.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);

  if(!texture.loadFromFile("res/textures/Enemy/Fire/red_dragon.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureEnemy.push_back(texture);


  //textureElement

  if(!texture.loadFromFile("res/textures/icons/air.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureElement.push_back(texture);

  if(!texture.loadFromFile("res/textures/icons/water.png")){
    std::cout << "error with enemy image"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  //texture.setTexture(texture);
  textureElement.push_back(texture);

if(!texture.loadFromFile("res/textures/icons/earth.png")){
  std::cout << "error with enemy image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureElement.push_back(texture);

if(!texture.loadFromFile("res/textures/icons/fire.png")){
std::cout << "error with enemy image"<<std::endl;
throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureElement.push_back(texture);

//textureBackGround

if(!texture.loadFromFile("res/textures/background/sleep room.png")){
  std::cout << "error with background image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureBackGround.push_back(texture);

if(!texture.loadFromFile("res/textures/background/air_battle_room.png")){
  std::cout << "error with background image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureBackGround.push_back(texture);

if(!texture.loadFromFile("res/textures/background/water_enemy_room.png")){
  std::cout << "error with background image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureBackGround.push_back(texture);

if(!texture.loadFromFile("res/textures/background/earth_enemy_room.png")){
  std::cout << "error with background image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureBackGround.push_back(texture);

if(!texture.loadFromFile("res/textures/background/fire_enemy_room.png")){
  std::cout << "error with background image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureBackGround.push_back(texture);

if(!texture.loadFromFile("res/textures/background/you_died.jpg")){
  std::cout << "error with background image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureBackGround.push_back(texture);
// textureButton

if(!texture.loadFromFile("res/textures/other/button1.png")){
  std::cout << "error with button image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureButton = texture;


// textureMapIcon

if(!texture.loadFromFile("res/textures/Map/sleep.png")){
  std::cout << "error with map icon image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapIcon.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/air_enemy.png")){
  std::cout << "error with map icon image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapIcon.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/water_enemy.png")){
  std::cout << "error with map icon image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapIcon.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/earth_enemy.png")){
  std::cout << "error with map icon image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapIcon.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/fire_enemy.png")){
  std::cout << "error with map icon image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapIcon.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/special_training.png")){
  std::cout << "error with map icon image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapIcon.push_back(texture);

//textureMapBackground

if(!texture.loadFromFile("res/textures/Map/map_white.jpg")){
  std::cout << "error with background map image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapBackground.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/map_blue.jpg")){
  std::cout << "error with background map image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapBackground.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/map_brown.jpg")){
  std::cout << "error with background map image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapBackground.push_back(texture);

if(!texture.loadFromFile("res/textures/Map/map_red.jpg")){
  std::cout << "error with background map image"<<std::endl;
  throw std::invalid_argument("error with argument");
}
//texture.setTexture(texture);
textureMapBackground.push_back(texture);


}

LoadTextures::~LoadTextures(){}
