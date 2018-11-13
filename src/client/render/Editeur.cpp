#include "Editeur.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdexcept>


using namespace render;
using namespace state;


Editeur::Editeur(){
  x = 0;
  y = 0;

}

Editeur::Editeur (int x, int y, float scale,  std::string image, int number){
    this -> x = x;
    this -> y = y;

    if (!texture.create(int(400*scale), int(600*scale))){
      std::cout<<"RenderTexture error"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    texture.clear(sf::Color::Transparent);

    sf::Sprite sprite;
    sf::Texture texturePile;
    if (!texturePile.loadFromFile(image)){
      std::cout << "error with image" << std::endl;
      throw std::invalid_argument("error with argument");
    }
    sprite.setTexture(texturePile);
    sprite.scale(scale, scale);

    sf::Font font;

    if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
      std::cout <<"error with font name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(number));
    text.setColor(sf::Color::White);
    text.setCharacterSize(50 * scale);
    text.move(200 * scale, 500 * scale);
    text.setStyle(sf::Text::Bold);

    texture.draw(sprite);

    texture.draw(text);
    texture.display();


  }

Editeur::Editeur( int x, int y, float scale,state::Card* card, int statAttack, int statBlock){
  this -> x = x;
  this -> y = y;

  sf::Font font;
  // name of the card:
  if (!font.loadFromFile("res/text_fonts/Anke Print.ttf")){
    std::cout <<"error with font name" << std::endl;
    throw std::invalid_argument("error with argument");
  }


  // texture:

  if (!texture.create(int(400*scale), int(600*scale))){
    std::cout<<"RenderTexture error"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  texture.clear(sf::Color::Transparent);
  sf::Texture cardtexture;

  //choose good back card according to the element
  int element = card -> GetElement();
  sf::Color tmpColor;
  if (element == 1){
    tmpColor = sf::Color(0,100,100);
    if( !cardtexture.loadFromFile("res/textures/cards/card_air.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
  }
  else{
  if (element == 2 ){
    tmpColor = sf::Color::Blue;
    if( !cardtexture.loadFromFile("res/textures/cards/card_water.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }

  }
  else{
  if (element == 3 ){
    tmpColor = sf::Color(0, 128, 0);
    if( !cardtexture.loadFromFile("res/textures/cards/card_earth.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
  }
  else{
  if (element == 4 ){
    tmpColor = sf::Color::Red;
    if( !cardtexture.loadFromFile("res/textures/cards/card_fire.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
  }
  else{
  tmpColor = sf::Color::Black;
  if (!cardtexture.loadFromFile("res/textures/cards/card_air.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }}}}}

//name card
  sf::Text name;
  name.setFont(font);
  name.setString(card -> GetName());
  name.setCharacterSize(30);
  name.setColor(tmpColor);
  name.move(100*scale, 40*scale);
  name.scale(scale, scale);


  //Fond de carte
  sf::Sprite spriteCard;
  spriteCard.setTexture(cardtexture);
  spriteCard.scale(scale, scale);


  texture.draw(spriteCard);


  // Image de carte
  sf::Sprite spriteImage;
  sf::Texture imtexture;
  if (!imtexture.loadFromFile(card -> GetImage())){
    std::cout << "error with imtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  spriteImage.setTexture(imtexture);
  spriteImage.move(100*scale,120*scale);
  spriteImage.scale(scale, scale);

  texture.draw(name);
  texture.draw(spriteImage);
  //Textbox de la carte:


  int positionX = 70;
  int positionY = 340;

  if (card -> GetAttack() > 0){
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/icons/attack.png")){
        std::cout << "error with attack"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      sf::Sprite tmpsprite;
      tmpsprite.setTexture(tmptexture);
      tmpsprite.move(positionX*scale, positionY*scale);
      tmpsprite.scale(scale/4, scale/4);
      texture.draw(tmpsprite);
      //text for value of attack/buff/debuff/block
      sf::Text tmptext;
      tmptext.setString(std::to_string(card -> GetAttack() + statAttack));
      tmptext.setFont(font);
      tmptext.setStyle(1);
      tmptext.setCharacterSize(25 * scale);
      tmptext.setColor(tmpColor);
      tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
      texture.draw(tmptext);

      if (positionX == 250){
        positionX = 70;
        positionY +=70;
      }
      else{
        positionX += 60;  //200 = limit
      }

  }
  if (card -> GetDebuff() -> GetAttackMinus() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_down.png")){
      std::cout << "error with attack_down"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/6, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDebuff() -> GetAttackMinus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }


  }
  if (card -> GetDebuff() -> GetBlockMinus() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block_down.png")){
      std::cout << "error with block_down"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDebuff() -> GetBlockMinus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBlock() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block.png")){
      std::cout << "error with block"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBlock() + statBlock));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetBlockPlus()> 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block_up.png")){
      std::cout << "error with block_up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetBlockPlus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetAttackPlus() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_up.png")){
      std::cout << "error with attack_up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move((positionX)*scale, (positionY) *scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetAttackPlus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetHeal() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/heal_buff.png")){
      std::cout << "error with heal"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetHeal()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetEvade() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/evade.png")){
      std::cout << "error with evade"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetEvade()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetRetaliate() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/retaliate.png")){
      std::cout << "error with retaliate"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetRetaliate()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }
  if (card -> GetDraw() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/special_training.png")){
      std::cout << "error with draw"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDraw()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }

  if (card -> GetDiscard() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/special_training.png")){
      std::cout << "error with discard"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    tmpsprite.setColor(sf::Color::Black);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDiscard()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }

  if (card -> GetHeal() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/heal.png")){
      std::cout << "error with heal(card)"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetHeal()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }

//Target:
  if (card -> GetTarget() == 0 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(325*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color(0,128,0));
    texture.draw(tmpsprite);
  }

  if (card -> GetTarget() == 1 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(325*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color::Red);
    texture.draw(tmpsprite);
  }

  if (card -> GetTarget() == 2 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    sf::Sprite tmpsprite2;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(315*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color::Red);
    texture.draw(tmpsprite);
    tmpsprite2.setTexture(tmptexture);
    tmpsprite2.move(330*scale, 50*scale);
    tmpsprite2.scale(scale/6, scale/6);
    tmpsprite2.setColor(sf::Color::Red);
    texture.draw(tmpsprite2);
  }

  if (card -> GetTarget() == 3 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(315*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color(0,128,0));
    texture.draw(tmpsprite);
    sf::Sprite tmpsprite2;
    tmpsprite2.setTexture(tmptexture);
    tmpsprite2.move(330*scale, 50*scale);
    tmpsprite2.scale(scale/6, scale/6);
    tmpsprite2.setColor(sf::Color(0,128,0));
    texture.draw(tmpsprite2);
  }

  // coût

  sf::Text cost;
  cost.setFont(font);
  cost.setString(std::to_string(card -> GetCost()));
  cost.setCharacterSize(40);
  cost.setColor(tmpColor);
  cost.move(40*scale, 20*scale);
  cost.scale(scale, scale);

  texture.draw(cost);

  texture.display();

}


Editeur::Editeur (int x, int y, float scale, state::Player* player){
  this -> x = x;
  this -> y = y;

  if (!texture.create(int(230*scale), int(400*scale))){
    std::cout<<"RenderTexture error"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  texture.clear(sf::Color::Transparent);

  sf::Texture playerTexture;
  if (!playerTexture.loadFromFile(player -> GetImage())){
    std::cout << "error with player image" << std::endl;
    throw std::invalid_argument("error with argument");
  }

  sf::Sprite playerSprite;
  playerSprite.setTexture(playerTexture);
  playerSprite.move( scale,80* scale);
  playerSprite.scale( scale/1.5, scale/1.5);

  texture.draw(playerSprite);

  sf::Font font;
  // name of the player:
  if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
    std::cout <<"error with font name" << std::endl;
    throw std::invalid_argument("error with argument");
  }

  //name
  sf::Text name;
  name.setFont(font);
  name.setString(player -> GetName());
  name.setColor(sf::Color::White);
  name.setCharacterSize(15.5 * scale);
  name.move(10 * scale, 280 * scale);

  texture.draw(name);

  name.setColor(sf::Color::Black);
  name.setCharacterSize(15 * scale);

  texture.draw(name);

  // Element:

  sf::Texture elementTexture;
  if (player -> GetElement() == 1 && !elementTexture.loadFromFile("res/textures/icons/air.png")){
    throw std::invalid_argument("error with image air");
  }
  else{
    if (player -> GetElement() == 2 && !elementTexture.loadFromFile("res/textures/icons/water.png")){
      throw std::invalid_argument("error with image air");
    }
    else{
      if (player -> GetElement() == 3 && !elementTexture.loadFromFile("res/textures/icons/earth.png")){
        throw std::invalid_argument("error with image air");
      }
      else{
        if (player -> GetElement() == 4 && !elementTexture.loadFromFile("res/textures/icons/fire.png")){
          throw std::invalid_argument("error with image air");
        }
      }
    }
  }
  sf::Sprite elementSprite;
  elementSprite.setTexture(elementTexture);
  elementSprite.move(170 * scale, 275 * scale);
  elementSprite.scale(scale/6, scale/6);

  texture.draw(elementSprite);


  //life:
  sf::RectangleShape backgroundLife(sf::Vector2f(200 * scale , 10 * scale));
  backgroundLife.setOutlineThickness(2);
  backgroundLife.setOutlineColor(sf::Color::White);
  backgroundLife.setFillColor(sf::Color::Black);
  backgroundLife.move(10, 310 * scale);



  sf::RectangleShape life(sf::Vector2f(200 * scale *(((float) player -> GetLife()/(float) player -> GetMaxLife())) , 10 * scale));
  life.setOutlineThickness(2);
  life.setOutlineColor(sf::Color::Transparent);
  life.setFillColor(sf::Color::Red);
  life.move(10, 310 * scale);

  texture.draw(backgroundLife);
  texture.draw(life);

  sf::Text lifetxt;
  sf::Font lifefont;
  // life of the player:
  if (!lifefont.loadFromFile("res/text_fonts/Upon Request.ttf")){
    std::cout << "error with life font" << std::endl;
    throw std::invalid_argument("argument invalide");
  }
  lifetxt.setFont(lifefont);
  lifetxt.setString(std::to_string(player -> GetLife()) + " / " + std::to_string(player -> GetMaxLife()));
  lifetxt.move(80 * scale,310*scale);
  lifetxt.setColor(sf::Color::Black);
  lifetxt.setCharacterSize(10.5 * scale);
  texture.draw(lifetxt);
  lifetxt.setColor(sf::Color::White);
  lifetxt.setCharacterSize(10 * scale);
  texture.draw(lifetxt);

  //Block:

  if (player -> GetBlock() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(-15, 290 *scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(player -> GetBlock()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((5) * scale, (315) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

  }

  //Energy

  sf::CircleShape circle(10.f * scale);
  circle.setOutlineThickness(1.f * scale);
  circle.setOutlineColor(sf::Color::Black);
  circle.setFillColor(sf::Color(250, 250, 0));
  circle.move(200 * scale, 306 * scale);

  texture.draw(circle);

  sf::Text energytxt;
  energytxt.setFont(lifefont);
  energytxt.setColor(sf::Color::Black);
  energytxt.setString(std::to_string(player -> GetEnergy()));
  energytxt.setCharacterSize(20 * scale);
  energytxt.setStyle(1);
  energytxt.move(205 * scale, 302 * scale);

  texture.draw(energytxt);


  // Buffs:
  int positionX = 10;
  int positionY = 330;

  if (player -> GetBuff().GetAttackPlus() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_up.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/6, scale/6);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(player -> GetBuff(). GetAttackPlus()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

    if (positionX +40 > 200){
      positionX = 10;
      positionY +=35;
    }
    else{
      positionX += 40;  //200 = limit
    }
  }

  if (player -> GetBuff().GetBlockPlus() > 0){
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/icons/block_up.png")){
        std::cout << "error with attack up"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      sf::Sprite tmpsprite;
      tmpsprite.setTexture(tmptexture);
      tmpsprite.move(positionX*scale, positionY*scale);
      tmpsprite.scale(scale/6, scale/6);
      texture.draw(tmpsprite);
      //text for value of attack/buff/debuff/block
      sf::Text tmptext;
      tmptext.setString(std::to_string(player -> GetBuff(). GetBlockPlus()));
      tmptext.setFont(lifefont);
      tmptext.setStyle(1);
      tmptext.setCharacterSize(18 * scale);
      tmptext.setColor(sf::Color::Black);
      tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
      texture.draw(tmptext);
      tmptext.setCharacterSize(15 * scale);
      tmptext.setColor(sf::Color::White);
      tmptext.move(0,2 * scale);
      texture.draw(tmptext);

      if (positionX +40 > 200){
        positionX = 10;
        positionY +=35;
      }
      else{
        positionX += 40;  //200 = limit
      }
    }

    if (player -> GetBuff().GetEvade() > 0){
        sf::Texture tmptexture;
        if(!tmptexture.loadFromFile("res/textures/icons/evade.png")){
          std::cout << "error with attack up"<<std::endl;
          throw std::invalid_argument("error with argument");
        }
        sf::Sprite tmpsprite;
        tmpsprite.setTexture(tmptexture);
        tmpsprite.move(positionX*scale, positionY*scale);
        tmpsprite.scale(scale/6, scale/6);
        texture.draw(tmpsprite);
        //text for value of attack/buff/debuff/block
        sf::Text tmptext;
        tmptext.setString(std::to_string(player -> GetBuff(). GetEvade()));
        tmptext.setFont(lifefont);
        tmptext.setStyle(1);
        tmptext.setCharacterSize(18 * scale);
        tmptext.setColor(sf::Color::Black);
        tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
        texture.draw(tmptext);
        tmptext.setCharacterSize(15 * scale);
        tmptext.setColor(sf::Color::White);
        tmptext.move(0,2 * scale);
        texture.draw(tmptext);

        if (positionX +40 > 200){
          positionX = 10;
          positionY +=35;
        }
        else{
          positionX += 40;  //200 = limit
        }
      }

      if (player -> GetBuff().GetHeal() > 0){
          sf::Texture tmptexture;
          if(!tmptexture.loadFromFile("res/textures/icons/heal.png")){
            std::cout << "error with attack up"<<std::endl;
            throw std::invalid_argument("error with argument");
          }
          sf::Sprite tmpsprite;
          tmpsprite.setTexture(tmptexture);
          tmpsprite.move(positionX *scale, positionY *scale);
          tmpsprite.scale(scale/6, scale/6);
          texture.draw(tmpsprite);
          //text for value of attack/buff/debuff/block
          sf::Text tmptext;
          tmptext.setString(std::to_string(player -> GetBuff(). GetHeal()));
          tmptext.setFont(lifefont);
          tmptext.setStyle(1);
          tmptext.setCharacterSize(18 * scale);
          tmptext.setColor(sf::Color::Black);
          tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
          texture.draw(tmptext);
          tmptext.setCharacterSize(15 * scale);
          tmptext.setColor(sf::Color::White);
          tmptext.move(0,2 * scale);
          texture.draw(tmptext);

          if (positionX +40 > 200){
            positionX = 10;
            positionY +=35;
          }
          else{
            positionX += 40;  //200 = limit
          }
        }

        if (player -> GetBuff().GetRetaliate() > 0){
            sf::Texture tmptexture;
            if(!tmptexture.loadFromFile("res/textures/icons/retaliate.png")){
              std::cout << "error with attack up"<<std::endl;
              throw std::invalid_argument("error with argument");
            }
            sf::Sprite tmpsprite;
            tmpsprite.setTexture(tmptexture);
            tmpsprite.move(positionX*scale,  positionY  *scale);
            tmpsprite.scale(scale/6, scale/6);
            texture.draw(tmpsprite);
            //text for value of attack/buff/debuff/block
            sf::Text tmptext;
            tmptext.setString(std::to_string(player -> GetBuff(). GetRetaliate()));
            tmptext.setFont(lifefont);
            tmptext.setStyle(1);
            tmptext.setCharacterSize(18 * scale);
            tmptext.setColor(sf::Color::Black);
            tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
            texture.draw(tmptext);
            tmptext.setCharacterSize(15 * scale);
            tmptext.setColor(sf::Color::White);
            tmptext.move(0,2 * scale);
            texture.draw(tmptext);

            if (positionX +40 > 200){
              positionX = 10;
              positionY +=35;
            }
            else{
              positionX += 40;  //200 = limit
            }
          }

          if (player -> GetDebuff().GetBlockMinus() > 0){
              sf::Texture tmptexture;
              if(!tmptexture.loadFromFile("res/textures/icons/block_down.png")){
                // std::cout << "error with attack up"<<std::endl;
                throw std::invalid_argument("error with argument");
              }
              sf::Sprite tmpsprite;
              tmpsprite.setTexture(tmptexture);
              tmpsprite.move(positionX*scale, positionY*scale);
              tmpsprite.scale(scale/6, scale/6);
              texture.draw(tmpsprite);
              //text for value of attack/buff/debuff/block
              sf::Text tmptext;
              tmptext.setString(std::to_string(player -> GetDebuff(). GetBlockMinus()));
              tmptext.setFont(lifefont);
              tmptext.setStyle(1);
              tmptext.setCharacterSize(18 * scale);
              tmptext.setColor(sf::Color::Black);
              tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
              texture.draw(tmptext);
              tmptext.setCharacterSize(15 * scale);
              tmptext.setColor(sf::Color::White);
              tmptext.move(0,2 * scale);
              texture.draw(tmptext);

              if (positionX +40 > 200){
                positionX = 10;
                positionY +=35;
              }
              else{
                positionX += 40;  //200 = limit
              }
            }

            if (player -> GetDebuff().GetBlockMinus() > 0){
                sf::Texture tmptexture;
                if(!tmptexture.loadFromFile("res/textures/icons/attack_down.png")){
                  std::cout << "error with attack up"<<std::endl;
                  throw std::invalid_argument("error with argument");
                }
                sf::Sprite tmpsprite;
                tmpsprite.setTexture(tmptexture);
                tmpsprite.move(positionX*scale, positionY*scale);
                tmpsprite.scale(scale/6, scale/6);
                texture.draw(tmpsprite);
                //text for value of attack/buff/debuff/block
                sf::Text tmptext;
                tmptext.setString(std::to_string(player -> GetDebuff(). GetBlockMinus()));
                tmptext.setFont(lifefont);
                tmptext.setStyle(1);
                tmptext.setCharacterSize(18 * scale);
                tmptext.setColor(sf::Color::Black);
                tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
                texture.draw(tmptext);
                tmptext.setCharacterSize(15 * scale);
                tmptext.setColor(sf::Color::White);
                tmptext.move(0,2 * scale);
                texture.draw(tmptext);

                if (positionX +40 > 200){
                  positionX = 10;
                  positionY +=35;
                }
                else{
                  positionX += 40;  //200 = limit
                }
              }


  texture.display();

}


Editeur::Editeur(int x, int y, float scale, std::unique_ptr<state::Enemy>& enemy){

  this -> x = x;
  this -> y = y;

  if (!texture.create(int(230*scale), int(400*scale))){
    std::cout<<"RenderTexture error"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  texture.clear(sf::Color::Transparent);

  sf::Texture enemyTexture;
  if (!enemyTexture.loadFromFile(enemy -> GetImage())){
    std::cout << "error with enemy image" << std::endl;
    throw std::invalid_argument("error with argument");
  }

  sf::Sprite enemySprite;
  enemySprite.setTexture(enemyTexture);
  enemySprite.move(0, 80 *scale);
  enemySprite.scale(  scale/1.5,  scale/1.5);

  texture.draw(enemySprite);

  sf::Font font;
  // name of the enemy:
  if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
    std::cout <<"error with font name" << std::endl;
    throw std::invalid_argument("error with argument");
  }

//name
  sf::Text name;
  name.setFont(font);
  name.setString(enemy -> GetName());
  name.setColor(sf::Color::White);
  name.setCharacterSize(15.5 * scale);
  name.move(10 * scale, 280 * scale);

  texture.draw(name);

  name.setColor(sf::Color::Black);
  name.setCharacterSize(15 * scale);

  texture.draw(name);

// Element:

  sf::Texture elementTexture;
  if (enemy -> GetElement() == 1 && !elementTexture.loadFromFile("res/textures/icons/air.png")){
    throw std::invalid_argument("error with image air");
  }
  else{
    if (enemy -> GetElement() == 2 && !elementTexture.loadFromFile("res/textures/icons/water.png")){
      throw std::invalid_argument("error with image air");
    }
    else{
      if (enemy -> GetElement() == 3 && !elementTexture.loadFromFile("res/textures/icons/earth.png")){
        throw std::invalid_argument("error with image air");
      }
      else{
        if (enemy -> GetElement() == 4 && !elementTexture.loadFromFile("res/textures/icons/fire.png")){
          throw std::invalid_argument("error with image air");
        }
      }
    }
  }
  sf::Sprite elementSprite;
  elementSprite.setTexture(elementTexture);
  elementSprite.move(170 * scale, 275 * scale);
  elementSprite.scale(scale/6, scale/6);

  texture.draw(elementSprite);


//life:
  sf::RectangleShape backgroundLife(sf::Vector2f(200 * scale , 10 * scale));
  backgroundLife.setOutlineThickness(2);
  backgroundLife.setOutlineColor(sf::Color::White);
  backgroundLife.setFillColor(sf::Color::Black);
  backgroundLife.move(10, 310 * scale);



  sf::RectangleShape life(sf::Vector2f(200 * scale *(((float) enemy -> GetLife()/(float) enemy -> GetMaxLife())) , 10 * scale));
  life.setOutlineThickness(2);
  life.setOutlineColor(sf::Color::Transparent);
  life.setFillColor(sf::Color::Red);
  life.move(10, 310 * scale);

  texture.draw(backgroundLife);
  texture.draw(life);

  sf::Text lifetxt;
  sf::Font lifefont;
  // life of the enemy:
  if (!lifefont.loadFromFile("res/text_fonts/Upon Request.ttf")){
    std::cout << "error with life font" << std::endl;
    throw std::invalid_argument("argument invalide");
  }
  lifetxt.setFont(lifefont);
  lifetxt.setString(std::to_string(enemy -> GetLife()) + " / " + std::to_string(enemy -> GetMaxLife()));
  lifetxt.move(80 * scale,310*scale);
  lifetxt.setColor(sf::Color::Black);
  lifetxt.setCharacterSize(10.5 * scale);
  texture.draw(lifetxt);
  lifetxt.setColor(sf::Color::White);
  lifetxt.setCharacterSize(10 * scale);
  texture.draw(lifetxt);

//Block:

if (enemy -> GetBlock() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(-15, 290 *scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(enemy -> GetBlock()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((5) * scale, (315) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

  }

//Intent:

sf::Texture intenttext;
if(!intenttext.loadFromFile(enemy -> GetSkills()[enemy -> GetIntent()] -> GetIntentImage())){
  throw std::invalid_argument("error with intentImage");
}
sf::Sprite intentSprite;
intentSprite.setTexture(intenttext);
intentSprite.scale(scale/3, scale/3);
intentSprite.move(70 * scale,250 * scale);
texture.draw(intentSprite);

if(enemy -> GetSkills()[enemy -> GetIntent()] -> GetAttack() > 0){
  sf::Text tmptext;
  tmptext.setString(std::to_string(enemy -> GetSkills()[enemy -> GetIntent()] -> GetAttack()));
  tmptext.setFont(lifefont);
  tmptext.setStyle(1);
  tmptext.setCharacterSize(18 * scale);
  tmptext.setColor(sf::Color::Black);
  tmptext.move((85) * scale, (270) * scale);
  texture.draw(tmptext);
  tmptext.setCharacterSize(15 * scale);
  tmptext.setColor(sf::Color::White);
  tmptext.move(0,2 * scale);
  texture.draw(tmptext);
}



// Buffs:
int positionX = 10;
int positionY = 330;

if (enemy -> GetBuff().GetAttackPlus() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_up.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/6, scale/6);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(enemy -> GetBuff(). GetAttackPlus()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

    if (positionX +40 > 200){
      positionX = 10;
      positionY +=35;
    }
    else{
      positionX += 40;  //200 = limit
    }
  }

  if (enemy -> GetBuff().GetBlockPlus() > 0){
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/icons/block_up.png")){
        std::cout << "error with attack up"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      sf::Sprite tmpsprite;
      tmpsprite.setTexture(tmptexture);
      tmpsprite.move(positionX*scale, positionY*scale);
      tmpsprite.scale(scale/6, scale/6);
      texture.draw(tmpsprite);
      //text for value of attack/buff/debuff/block
      sf::Text tmptext;
      tmptext.setString(std::to_string(enemy -> GetBuff(). GetBlockPlus()));
      tmptext.setFont(lifefont);
      tmptext.setStyle(1);
      tmptext.setCharacterSize(18 * scale);
      tmptext.setColor(sf::Color::Black);
      tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
      texture.draw(tmptext);
      tmptext.setCharacterSize(15 * scale);
      tmptext.setColor(sf::Color::White);
      tmptext.move(0,2 * scale);
      texture.draw(tmptext);

      if (positionX +40 > 200){
        positionX = 10;
        positionY +=35;
      }
      else{
        positionX += 40;  //200 = limit
      }
    }

    if (enemy -> GetBuff().GetEvade() > 0){
        sf::Texture tmptexture;
        if(!tmptexture.loadFromFile("res/textures/icons/evade.png")){
          std::cout << "error with attack up"<<std::endl;
          throw std::invalid_argument("error with argument");
        }
        sf::Sprite tmpsprite;
        tmpsprite.setTexture(tmptexture);
        tmpsprite.move(positionX*scale, positionY*scale);
        tmpsprite.scale(scale/6, scale/6);
        texture.draw(tmpsprite);
        //text for value of attack/buff/debuff/block
        sf::Text tmptext;
        tmptext.setString(std::to_string(enemy -> GetBuff(). GetEvade()));
        tmptext.setFont(lifefont);
        tmptext.setStyle(1);
        tmptext.setCharacterSize(18 * scale);
        tmptext.setColor(sf::Color::Black);
        tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
        texture.draw(tmptext);
        tmptext.setCharacterSize(15 * scale);
        tmptext.setColor(sf::Color::White);
        tmptext.move(0,2 * scale);
        texture.draw(tmptext);

        if (positionX +40 > 200){
          positionX = 10;
          positionY +=35;
        }
        else{
          positionX += 40;  //200 = limit
        }
      }

      if (enemy -> GetBuff().GetHeal() > 0){
          sf::Texture tmptexture;
          if(!tmptexture.loadFromFile("res/textures/icons/heal.png")){
            std::cout << "error with attack up"<<std::endl;
            throw std::invalid_argument("error with argument");
          }
          sf::Sprite tmpsprite;
          tmpsprite.setTexture(tmptexture);
          tmpsprite.move(positionX *scale, positionY *scale);
          tmpsprite.scale(scale/6, scale/6);
          texture.draw(tmpsprite);
          //text for value of attack/buff/debuff/block
          sf::Text tmptext;
          tmptext.setString(std::to_string(enemy -> GetBuff(). GetHeal()));
          tmptext.setFont(lifefont);
          tmptext.setStyle(1);
          tmptext.setCharacterSize(18 * scale);
          tmptext.setColor(sf::Color::Black);
          tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
          texture.draw(tmptext);
          tmptext.setCharacterSize(15 * scale);
          tmptext.setColor(sf::Color::White);
          tmptext.move(0,2 * scale);
          texture.draw(tmptext);

          if (positionX +40 > 200){
            positionX = 10;
            positionY +=35;
          }
          else{
            positionX += 40;  //200 = limit
          }
        }

        if (enemy -> GetBuff().GetRetaliate() > 0){
            sf::Texture tmptexture;
            if(!tmptexture.loadFromFile("res/textures/icons/retaliate.png")){
              std::cout << "error with attack up"<<std::endl;
              throw std::invalid_argument("error with argument");
            }
            sf::Sprite tmpsprite;
            tmpsprite.setTexture(tmptexture);
            tmpsprite.move(positionX*scale, positionY  *scale);
            tmpsprite.scale(scale/6, scale/6);
            texture.draw(tmpsprite);
            //text for value of attack/buff/debuff/block
            sf::Text tmptext;
            tmptext.setString(std::to_string(enemy -> GetBuff(). GetRetaliate()));
            tmptext.setFont(lifefont);
            tmptext.setStyle(1);
            tmptext.setCharacterSize(18 * scale);
            tmptext.setColor(sf::Color::Black);
            tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
            texture.draw(tmptext);
            tmptext.setCharacterSize(15 * scale);
            tmptext.setColor(sf::Color::White);
            tmptext.move(0,2 * scale);
            texture.draw(tmptext);

            if (positionX +40 > 200){
              positionX = 10;
              positionY +=35;
            }
            else{
              positionX += 40;  //200 = limit
            }
          }

          if (enemy -> GetDebuff().GetBlockMinus() > 0){
              sf::Texture tmptexture;
              if(!tmptexture.loadFromFile("res/textures/icons/block_down.png")){
                // std::cout << "error with attack up"<<std::endl;
                throw std::invalid_argument("error with argument");
              }
              sf::Sprite tmpsprite;
              tmpsprite.setTexture(tmptexture);
              tmpsprite.move(positionX*scale, positionY*scale);
              tmpsprite.scale(scale/6, scale/6);
              texture.draw(tmpsprite);
              //text for value of attack/buff/debuff/block
              sf::Text tmptext;
              tmptext.setString(std::to_string(enemy -> GetDebuff(). GetBlockMinus()));
              tmptext.setFont(lifefont);
              tmptext.setStyle(1);
              tmptext.setCharacterSize(18 * scale);
              tmptext.setColor(sf::Color::Black);
              tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
              texture.draw(tmptext);
              tmptext.setCharacterSize(15 * scale);
              tmptext.setColor(sf::Color::White);
              tmptext.move(0,2 * scale);
              texture.draw(tmptext);

              if (positionX +40 > 200){
                positionX = 10;
                positionY +=35;
              }
              else{
                positionX += 40;  //200 = limit
              }
            }

            if (enemy -> GetDebuff().GetBlockMinus() > 0){
                sf::Texture tmptexture;
                if(!tmptexture.loadFromFile("res/textures/icons/attack_down.png")){
                  std::cout << "error with attack up"<<std::endl;
                  throw std::invalid_argument("error with argument");
                }
                sf::Sprite tmpsprite;
                tmpsprite.setTexture(tmptexture);
                tmpsprite.move(positionX*scale, positionY*scale);
                tmpsprite.scale(scale/6, scale/6);
                texture.draw(tmpsprite);
                //text for value of attack/buff/debuff/block
                sf::Text tmptext;
                tmptext.setString(std::to_string(enemy -> GetDebuff(). GetBlockMinus()));
                tmptext.setFont(lifefont);
                tmptext.setStyle(1);
                tmptext.setCharacterSize(18 * scale);
                tmptext.setColor(sf::Color::Black);
                tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
                texture.draw(tmptext);
                tmptext.setCharacterSize(15 * scale);
                tmptext.setColor(sf::Color::White);
                tmptext.move(0,2 * scale);
                texture.draw(tmptext);

                if (positionX +40 > 200){
                  positionX = 10;
                  positionY +=35;
                }
                else{
                  positionX += 40;  //200 = limit
                }
              }


  texture.display();

}



Editeur::~Editeur(){}

bool Editeur::Click(int x, int y){
  sf::Vector2u size = texture.getSize();
  if(x > (this -> x ) && x <= (this -> x +(int) size.x ) && y > (this -> y ) && y <= (this -> y +(int) size.y -20)){
    return true;
  } else return false;
}

int const Editeur::GetX(){
  return x;
}
int const Editeur::GetY(){
  return y;
}
sf::RenderTexture&  Editeur::GetTexture(){
  return texture;
}

void Editeur::SetX(int x){
  this -> x = x;
}

void Editeur::SetY( int y){
  this -> y = y;
}

void Editeur::SetEditeurCard( float scale, state::Card* card, int statAttack , int statBlock){


  sf::Font font;
  // name of the card:
  if (!font.loadFromFile("res/text_fonts/Anke Print.ttf")){
    std::cout <<"error with font name" << std::endl;
    throw std::invalid_argument("error with argument");
  }


  // texture:

  if (!texture.create(int(400*scale), int(600*scale))){
    std::cout<<"RenderTexture error"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  texture.clear(sf::Color::Transparent);
  sf::Texture cardtexture;

  //choose good back card according to the element
  int element = card -> GetElement();
  sf::Color tmpColor;
  if (element == 1){
    tmpColor = sf::Color(0,100,100);
    if( !cardtexture.loadFromFile("res/textures/cards/card_air.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
  }
  else{
  if (element == 2 ){
    tmpColor = sf::Color::Blue;
    if( !cardtexture.loadFromFile("res/textures/cards/card_water.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }

  }
  else{
  if (element == 3 ){
    tmpColor = sf::Color(0, 128, 0);
    if( !cardtexture.loadFromFile("res/textures/cards/card_earth.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
  }
  else{
  if (element == 4 ){
    tmpColor = sf::Color::Red;
    if( !cardtexture.loadFromFile("res/textures/cards/card_fire.png")){
      std::cout << "error with cardtexture name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
  }
  else{
  tmpColor = sf::Color::Black;
  if (!cardtexture.loadFromFile("res/textures/cards/card_air.png")){
    std::cout << "error with cardtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }}}}}

//name card
  sf::Text name;
  name.setFont(font);
  name.setString(card -> GetName());
  name.setCharacterSize(30);
  name.setColor(tmpColor);
  name.move(100*scale, 40*scale);
  name.scale(scale, scale);


  //Fond de carte
  sf::Sprite spriteCard;
  spriteCard.setTexture(cardtexture);
  spriteCard.scale(scale, scale);


  texture.draw(spriteCard);


  // Image de carte
  sf::Sprite spriteImage;
  sf::Texture imtexture;
  if (!imtexture.loadFromFile(card -> GetImage())){
    std::cout << "error with imtexture name" << std::endl;
    throw std::invalid_argument("error with argument");
  }
  spriteImage.setTexture(imtexture);
  spriteImage.move(100*scale,120*scale);
  spriteImage.scale(scale, scale);

  texture.draw(name);
  texture.draw(spriteImage);
  //Textbox de la carte:


  int positionX = 70;
  int positionY = 340;

  if (card -> GetAttack() > 0){
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/icons/attack.png")){
        std::cout << "error with attack"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      sf::Sprite tmpsprite;
      tmpsprite.setTexture(tmptexture);
      tmpsprite.move(positionX*scale, positionY*scale);
      tmpsprite.scale(scale/4, scale/4);
      texture.draw(tmpsprite);
      //text for value of attack/buff/debuff/block
      sf::Text tmptext;
      tmptext.setString(std::to_string(card -> GetAttack() + statAttack));
      tmptext.setFont(font);
      tmptext.setStyle(1);
      tmptext.setCharacterSize(25 * scale);
      tmptext.setColor(tmpColor);
      tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
      texture.draw(tmptext);

      if (positionX == 250){
        positionX = 70;
        positionY +=70;
      }
      else{
        positionX += 60;  //200 = limit
      }

  }
  if (card -> GetDebuff() -> GetAttackMinus() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_down.png")){
      std::cout << "error with attack_down"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDebuff() -> GetAttackMinus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }


  }
  if (card -> GetDebuff() -> GetBlockMinus() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block_down.png")){
      std::cout << "error with block_down"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDebuff() -> GetBlockMinus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBlock() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block.png")){
      std::cout << "error with block"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBlock() + statBlock));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetBlockPlus()> 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block_up.png")){
      std::cout << "error with block_up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetBlockPlus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetAttackPlus() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_up.png")){
      std::cout << "error with attack_up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move((positionX)*scale, (positionY) *scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetAttackPlus()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetHeal() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/heal_buff.png")){
      std::cout << "error with heal"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetHeal()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetEvade() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/evade.png")){
      std::cout << "error with evade"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetEvade()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 35) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }

  }
  if (card -> GetBuff() -> GetRetaliate() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/retaliate.png")){
      std::cout << "error with retaliate"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetBuff() -> GetRetaliate()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }
  if (card -> GetDraw() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/special_training.png")){
      std::cout << "error with draw"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDraw()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }

  if (card -> GetDiscard() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/special_training.png")){
      std::cout << "error with discard"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    tmpsprite.setColor(sf::Color::Black);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetDiscard()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }

  if (card -> GetHeal() > 0){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/heal.png")){
      std::cout << "error with heal(card)"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(card -> GetHeal()));
    tmptext.setFont(font);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(25 * scale);
    tmptext.setColor(tmpColor);
    tmptext.move((positionX + 45) * scale, (positionY + 25) * scale);
    texture.draw(tmptext);

    if (positionX == 250){
      positionX = 70;
      positionY +=70;
    }
    else{
      positionX += 60;  //200 = limit
    }
  }

//Target:
  if (card -> GetTarget() == 0 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(325*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color(0,128,0));
    texture.draw(tmpsprite);
  }

  if (card -> GetTarget() == 1 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(325*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color::Red);
    texture.draw(tmpsprite);
  }

  if (card -> GetTarget() == 2 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    sf::Sprite tmpsprite2;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(315*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color::Red);
    texture.draw(tmpsprite);
    tmpsprite2.setTexture(tmptexture);
    tmpsprite2.move(330*scale, 50*scale);
    tmpsprite2.scale(scale/6, scale/6);
    tmpsprite2.setColor(sf::Color::Red);
    texture.draw(tmpsprite2);
  }

  if (card -> GetTarget() == 3 ){

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/target.png")){
      std::cout << "error with target"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(315*scale, 50*scale);
    tmpsprite.scale(scale/6, scale/6);
    tmpsprite.setColor(sf::Color(0,128,0));
    texture.draw(tmpsprite);
    sf::Sprite tmpsprite2;
    tmpsprite2.setTexture(tmptexture);
    tmpsprite2.move(330*scale, 50*scale);
    tmpsprite2.scale(scale/6, scale/6);
    tmpsprite2.setColor(sf::Color(0,128,0));
    texture.draw(tmpsprite2);
  }

  // coût

  sf::Text cost;
  cost.setFont(font);
  cost.setString(std::to_string(card -> GetCost()));
  cost.setCharacterSize(40);
  cost.setColor(tmpColor);
  cost.move(40*scale, 20*scale);
  cost.scale(scale, scale);

  texture.draw(cost);

  texture.display();

}


void Editeur::SetEditeurPlayer(float scale, state::Player* player){

  if (!texture.create(int(230*scale), int(400*scale))){
    std::cout<<"RenderTexture error"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  texture.clear(sf::Color::Transparent);

  sf::Texture playerTexture;
  if (!playerTexture.loadFromFile(player -> GetImage())){
    std::cout << "error with player image" << std::endl;
    throw std::invalid_argument("error with argument");
  }

  sf::Sprite playerSprite;
  playerSprite.setTexture(playerTexture);
  playerSprite.move( scale,80* scale);
  playerSprite.scale( scale/1.5, scale/1.5);

  texture.draw(playerSprite);

  sf::Font font;
  // name of the player:
  if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
    std::cout <<"error with font name" << std::endl;
    throw std::invalid_argument("error with argument");
  }

  //name
  sf::Text name;
  name.setFont(font);
  name.setString(player -> GetName());
  name.setColor(sf::Color::White);
  name.setCharacterSize(15.5 * scale);
  name.move(10 * scale, 280 * scale);

  texture.draw(name);

  name.setColor(sf::Color::Black);
  name.setCharacterSize(15 * scale);

  texture.draw(name);

  // Element:

  sf::Texture elementTexture;
  if (player -> GetElement() == 1 && !elementTexture.loadFromFile("res/textures/icons/air.png")){
    throw std::invalid_argument("error with image air");
  }
  else{
    if (player -> GetElement() == 2 && !elementTexture.loadFromFile("res/textures/icons/water.png")){
      throw std::invalid_argument("error with image air");
    }
    else{
      if (player -> GetElement() == 3 && !elementTexture.loadFromFile("res/textures/icons/earth.png")){
        throw std::invalid_argument("error with image air");
      }
      else{
        if (player -> GetElement() == 4 && !elementTexture.loadFromFile("res/textures/icons/fire.png")){
          throw std::invalid_argument("error with image air");
        }
      }
    }
  }
  sf::Sprite elementSprite;
  elementSprite.setTexture(elementTexture);
  elementSprite.move(170 * scale, 275 * scale);
  elementSprite.scale(scale/6, scale/6);

  texture.draw(elementSprite);


  //life:
  sf::RectangleShape backgroundLife(sf::Vector2f(200 * scale , 10 * scale));
  backgroundLife.setOutlineThickness(2);
  backgroundLife.setOutlineColor(sf::Color::White);
  backgroundLife.setFillColor(sf::Color::Black);
  backgroundLife.move(10, 310 * scale);



  sf::RectangleShape life(sf::Vector2f(200 * scale *(((float) player -> GetLife()/(float) player -> GetMaxLife())) , 10 * scale));
  life.setOutlineThickness(2);
  life.setOutlineColor(sf::Color::Transparent);
  life.setFillColor(sf::Color::Red);
  life.move(10, 310 * scale);

  texture.draw(backgroundLife);
  texture.draw(life);

  sf::Text lifetxt;
  sf::Font lifefont;
  // life of the player:
  if (!lifefont.loadFromFile("res/text_fonts/Upon Request.ttf")){
    std::cout << "error with life font" << std::endl;
    throw std::invalid_argument("argument invalide");
  }
  lifetxt.setFont(lifefont);
  lifetxt.setString(std::to_string(player -> GetLife()) + " / " + std::to_string(player -> GetMaxLife()));
  lifetxt.move(80 * scale,310*scale);
  lifetxt.setColor(sf::Color::Black);
  lifetxt.setCharacterSize(10.5 * scale);
  texture.draw(lifetxt);
  lifetxt.setColor(sf::Color::White);
  lifetxt.setCharacterSize(10 * scale);
  texture.draw(lifetxt);

  //Block:

  if (player -> GetBlock() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(-15, 290 *scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(player -> GetBlock()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((5) * scale, (315) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

  }

  //Energy

  sf::CircleShape circle(10.f * scale);
  circle.setOutlineThickness(1.f * scale);
  circle.setOutlineColor(sf::Color::Black);
  circle.setFillColor(sf::Color(250, 250, 0));
  circle.move(200 * scale, 306 * scale);

  texture.draw(circle);

  sf::Text energytxt;
  energytxt.setFont(lifefont);
  energytxt.setColor(sf::Color::Black);
  energytxt.setString(std::to_string(player -> GetEnergy()));
  energytxt.setCharacterSize(20 * scale);
  energytxt.setStyle(1);
  energytxt.move(205 * scale, 302 * scale);

  texture.draw(energytxt);


  // Buffs:
  int positionX = 10;
  int positionY = 330;

  if (player -> GetBuff().GetAttackPlus() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_up.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/6, scale/6);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(player -> GetBuff(). GetAttackPlus()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

    if (positionX +40 > 200){
      positionX = 10;
      positionY +=35;
    }
    else{
      positionX += 40;  //200 = limit
    }
  }

  if (player -> GetBuff().GetBlockPlus() > 0){
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/icons/block_up.png")){
        std::cout << "error with attack up"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      sf::Sprite tmpsprite;
      tmpsprite.setTexture(tmptexture);
      tmpsprite.move(positionX*scale, positionY*scale);
      tmpsprite.scale(scale/6, scale/6);
      texture.draw(tmpsprite);
      //text for value of attack/buff/debuff/block
      sf::Text tmptext;
      tmptext.setString(std::to_string(player -> GetBuff(). GetBlockPlus()));
      tmptext.setFont(lifefont);
      tmptext.setStyle(1);
      tmptext.setCharacterSize(18 * scale);
      tmptext.setColor(sf::Color::Black);
      tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
      texture.draw(tmptext);
      tmptext.setCharacterSize(15 * scale);
      tmptext.setColor(sf::Color::White);
      tmptext.move(0,2 * scale);
      texture.draw(tmptext);

      if (positionX +40 > 200){
        positionX = 10;
        positionY +=35;
      }
      else{
        positionX += 40;  //200 = limit
      }
    }

    if (player -> GetBuff().GetEvade() > 0){
        sf::Texture tmptexture;
        if(!tmptexture.loadFromFile("res/textures/icons/evade.png")){
          std::cout << "error with attack up"<<std::endl;
          throw std::invalid_argument("error with argument");
        }
        sf::Sprite tmpsprite;
        tmpsprite.setTexture(tmptexture);
        tmpsprite.move(positionX*scale, positionY*scale);
        tmpsprite.scale(scale/6, scale/6);
        texture.draw(tmpsprite);
        //text for value of attack/buff/debuff/block
        sf::Text tmptext;
        tmptext.setString(std::to_string(player -> GetBuff(). GetEvade()));
        tmptext.setFont(lifefont);
        tmptext.setStyle(1);
        tmptext.setCharacterSize(18 * scale);
        tmptext.setColor(sf::Color::Black);
        tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
        texture.draw(tmptext);
        tmptext.setCharacterSize(15 * scale);
        tmptext.setColor(sf::Color::White);
        tmptext.move(0,2 * scale);
        texture.draw(tmptext);

        if (positionX +40 > 200){
          positionX = 10;
          positionY +=35;
        }
        else{
          positionX += 40;  //200 = limit
        }
      }

      if (player -> GetBuff().GetHeal() > 0){
          sf::Texture tmptexture;
          if(!tmptexture.loadFromFile("res/textures/icons/heal.png")){
            std::cout << "error with attack up"<<std::endl;
            throw std::invalid_argument("error with argument");
          }
          sf::Sprite tmpsprite;
          tmpsprite.setTexture(tmptexture);
          tmpsprite.move(positionX *scale, positionY *scale);
          tmpsprite.scale(scale/6, scale/6);
          texture.draw(tmpsprite);
          //text for value of attack/buff/debuff/block
          sf::Text tmptext;
          tmptext.setString(std::to_string(player -> GetBuff(). GetHeal()));
          tmptext.setFont(lifefont);
          tmptext.setStyle(1);
          tmptext.setCharacterSize(18 * scale);
          tmptext.setColor(sf::Color::Black);
          tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
          texture.draw(tmptext);
          tmptext.setCharacterSize(15 * scale);
          tmptext.setColor(sf::Color::White);
          tmptext.move(0,2 * scale);
          texture.draw(tmptext);

          if (positionX +40 > 200){
            positionX = 10;
            positionY +=35;
          }
          else{
            positionX += 40;  //200 = limit
          }
        }

        if (player -> GetBuff().GetRetaliate() > 0){
            sf::Texture tmptexture;
            if(!tmptexture.loadFromFile("res/textures/icons/retaliate.png")){
              std::cout << "error with attack up"<<std::endl;
              throw std::invalid_argument("error with argument");
            }
            sf::Sprite tmpsprite;
            tmpsprite.setTexture(tmptexture);
            tmpsprite.move(positionX*scale,  positionY  *scale);
            tmpsprite.scale(scale/6, scale/6);
            texture.draw(tmpsprite);
            //text for value of attack/buff/debuff/block
            sf::Text tmptext;
            tmptext.setString(std::to_string(player -> GetBuff(). GetRetaliate()));
            tmptext.setFont(lifefont);
            tmptext.setStyle(1);
            tmptext.setCharacterSize(18 * scale);
            tmptext.setColor(sf::Color::Black);
            tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
            texture.draw(tmptext);
            tmptext.setCharacterSize(15 * scale);
            tmptext.setColor(sf::Color::White);
            tmptext.move(0,2 * scale);
            texture.draw(tmptext);

            if (positionX +40 > 200){
              positionX = 10;
              positionY +=35;
            }
            else{
              positionX += 40;  //200 = limit
            }
          }

          if (player -> GetDebuff().GetBlockMinus() > 0){
              sf::Texture tmptexture;
              if(!tmptexture.loadFromFile("res/textures/icons/block_down.png")){
                // std::cout << "error with attack up"<<std::endl;
                throw std::invalid_argument("error with argument");
              }
              sf::Sprite tmpsprite;
              tmpsprite.setTexture(tmptexture);
              tmpsprite.move(positionX*scale, positionY*scale);
              tmpsprite.scale(scale/6, scale/6);
              texture.draw(tmpsprite);
              //text for value of attack/buff/debuff/block
              sf::Text tmptext;
              tmptext.setString(std::to_string(player -> GetDebuff(). GetBlockMinus()));
              tmptext.setFont(lifefont);
              tmptext.setStyle(1);
              tmptext.setCharacterSize(18 * scale);
              tmptext.setColor(sf::Color::Black);
              tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
              texture.draw(tmptext);
              tmptext.setCharacterSize(15 * scale);
              tmptext.setColor(sf::Color::White);
              tmptext.move(0,2 * scale);
              texture.draw(tmptext);

              if (positionX +40 > 200){
                positionX = 10;
                positionY +=35;
              }
              else{
                positionX += 40;  //200 = limit
              }
            }

            if (player -> GetDebuff().GetBlockMinus() > 0){
                sf::Texture tmptexture;
                if(!tmptexture.loadFromFile("res/textures/icons/attack_down.png")){
                  std::cout << "error with attack up"<<std::endl;
                  throw std::invalid_argument("error with argument");
                }
                sf::Sprite tmpsprite;
                tmpsprite.setTexture(tmptexture);
                tmpsprite.move(positionX*scale, positionY*scale);
                tmpsprite.scale(scale/6, scale/6);
                texture.draw(tmpsprite);
                //text for value of attack/buff/debuff/block
                sf::Text tmptext;
                tmptext.setString(std::to_string(player -> GetDebuff(). GetBlockMinus()));
                tmptext.setFont(lifefont);
                tmptext.setStyle(1);
                tmptext.setCharacterSize(18 * scale);
                tmptext.setColor(sf::Color::Black);
                tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
                texture.draw(tmptext);
                tmptext.setCharacterSize(15 * scale);
                tmptext.setColor(sf::Color::White);
                tmptext.move(0,2 * scale);
                texture.draw(tmptext);

                if (positionX +40 > 200){
                  positionX = 10;
                  positionY +=35;
                }
                else{
                  positionX += 40;  //200 = limit
                }
              }


  texture.display();

}

void Editeur::SetEditeurEnemy(float scale, std::unique_ptr<Enemy>& enemy){
  if (!texture.create(int(230*scale), int(400*scale))){
    std::cout<<"RenderTexture error"<<std::endl;
    throw std::invalid_argument("error with argument");
  }
  texture.clear(sf::Color::Transparent);

  sf::Texture enemyTexture;
  if (!enemyTexture.loadFromFile(enemy -> GetImage())){
    std::cout << "error with enemy image" << std::endl;
    throw std::invalid_argument("error with argument");
  }

  sf::Sprite enemySprite;
  enemySprite.setTexture(enemyTexture);
  enemySprite.move(0, 80 *scale);
  enemySprite.scale(  scale/1.5,  scale/1.5);

  texture.draw(enemySprite);

  sf::Font font;
  // name of the enemy:
  if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
    std::cout <<"error with font name" << std::endl;
    throw std::invalid_argument("error with argument");
  }

//name
  sf::Text name;
  name.setFont(font);
  name.setString(enemy -> GetName());
  name.setColor(sf::Color::White);
  name.setCharacterSize(15.5 * scale);
  name.move(10 * scale, 280 * scale);

  texture.draw(name);

  name.setColor(sf::Color::Black);
  name.setCharacterSize(15 * scale);

  texture.draw(name);

// Element:

  sf::Texture elementTexture;
  if (enemy -> GetElement() == 1 && !elementTexture.loadFromFile("res/textures/icons/air.png")){
    throw std::invalid_argument("error with image air");
  }
  else{
    if (enemy -> GetElement() == 2 && !elementTexture.loadFromFile("res/textures/icons/water.png")){
      throw std::invalid_argument("error with image air");
    }
    else{
      if (enemy -> GetElement() == 3 && !elementTexture.loadFromFile("res/textures/icons/earth.png")){
        throw std::invalid_argument("error with image air");
      }
      else{
        if (enemy -> GetElement() == 4 && !elementTexture.loadFromFile("res/textures/icons/fire.png")){
          throw std::invalid_argument("error with image air");
        }
      }
    }
  }
  sf::Sprite elementSprite;
  elementSprite.setTexture(elementTexture);
  elementSprite.move(170 * scale, 275 * scale);
  elementSprite.scale(scale/6, scale/6);

  texture.draw(elementSprite);


//life:
  sf::RectangleShape backgroundLife(sf::Vector2f(200 * scale , 10 * scale));
  backgroundLife.setOutlineThickness(2);
  backgroundLife.setOutlineColor(sf::Color::White);
  backgroundLife.setFillColor(sf::Color::Black);
  backgroundLife.move(10, 310 * scale);



  sf::RectangleShape life(sf::Vector2f(200 * scale *(((float) enemy -> GetLife()/(float) enemy -> GetMaxLife())) , 10 * scale));
  life.setOutlineThickness(2);
  life.setOutlineColor(sf::Color::Transparent);
  life.setFillColor(sf::Color::Red);
  life.move(10, 310 * scale);

  texture.draw(backgroundLife);
  texture.draw(life);

  sf::Text lifetxt;
  sf::Font lifefont;
  // life of the enemy:
  if (!lifefont.loadFromFile("res/text_fonts/Upon Request.ttf")){
    std::cout << "error with life font" << std::endl;
    throw std::invalid_argument("argument invalide");
  }
  lifetxt.setFont(lifefont);
  lifetxt.setString(std::to_string(enemy -> GetLife()) + " / " + std::to_string(enemy -> GetMaxLife()));
  lifetxt.move(80 * scale,310*scale);
  lifetxt.setColor(sf::Color::Black);
  lifetxt.setCharacterSize(10.5 * scale);
  texture.draw(lifetxt);
  lifetxt.setColor(sf::Color::White);
  lifetxt.setCharacterSize(10 * scale);
  texture.draw(lifetxt);

//Block:

if (enemy -> GetBlock() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/block.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(-15, 290 *scale);
    tmpsprite.scale(scale/4, scale/4);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(enemy -> GetBlock()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((5) * scale, (315) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

  }

//Intent:

sf::Texture intenttext;
if(!intenttext.loadFromFile(enemy -> GetSkills()[enemy -> GetIntent()] -> GetIntentImage())){
  throw std::invalid_argument("error with intentImage");
}
sf::Sprite intentSprite;
intentSprite.setTexture(intenttext);
intentSprite.scale(scale/3, scale/3);
intentSprite.move(70 * scale,250 * scale);
texture.draw(intentSprite);

if(enemy -> GetSkills()[enemy -> GetIntent()] -> GetAttack() > 0){
  sf::Text tmptext;
  tmptext.setString(std::to_string(enemy -> GetSkills()[enemy -> GetIntent()] -> GetAttack()));
  tmptext.setFont(lifefont);
  tmptext.setStyle(1);
  tmptext.setCharacterSize(18 * scale);
  tmptext.setColor(sf::Color::Black);
  tmptext.move((85) * scale, (270) * scale);
  texture.draw(tmptext);
  tmptext.setCharacterSize(15 * scale);
  tmptext.setColor(sf::Color::White);
  tmptext.move(0,2 * scale);
  texture.draw(tmptext);
}



// Buffs:
int positionX = 10;
int positionY = 330;

if (enemy -> GetBuff().GetAttackPlus() > 0){
    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/icons/attack_up.png")){
      std::cout << "error with attack up"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Sprite tmpsprite;
    tmpsprite.setTexture(tmptexture);
    tmpsprite.move(positionX*scale, positionY*scale);
    tmpsprite.scale(scale/6, scale/6);
    texture.draw(tmpsprite);
    //text for value of attack/buff/debuff/block
    sf::Text tmptext;
    tmptext.setString(std::to_string(enemy -> GetBuff(). GetAttackPlus()));
    tmptext.setFont(lifefont);
    tmptext.setStyle(1);
    tmptext.setCharacterSize(18 * scale);
    tmptext.setColor(sf::Color::Black);
    tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
    texture.draw(tmptext);
    tmptext.setCharacterSize(15 * scale);
    tmptext.setColor(sf::Color::White);
    tmptext.move(0,2 * scale);
    texture.draw(tmptext);

    if (positionX +40 > 200){
      positionX = 10;
      positionY +=35;
    }
    else{
      positionX += 40;  //200 = limit
    }
  }

  if (enemy -> GetBuff().GetBlockPlus() > 0){
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/icons/block_up.png")){
        std::cout << "error with attack up"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      sf::Sprite tmpsprite;
      tmpsprite.setTexture(tmptexture);
      tmpsprite.move(positionX*scale, positionY*scale);
      tmpsprite.scale(scale/6, scale/6);
      texture.draw(tmpsprite);
      //text for value of attack/buff/debuff/block
      sf::Text tmptext;
      tmptext.setString(std::to_string(enemy -> GetBuff(). GetBlockPlus()));
      tmptext.setFont(lifefont);
      tmptext.setStyle(1);
      tmptext.setCharacterSize(18 * scale);
      tmptext.setColor(sf::Color::Black);
      tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
      texture.draw(tmptext);
      tmptext.setCharacterSize(15 * scale);
      tmptext.setColor(sf::Color::White);
      tmptext.move(0,2 * scale);
      texture.draw(tmptext);

      if (positionX +40 > 200){
        positionX = 10;
        positionY +=35;
      }
      else{
        positionX += 40;  //200 = limit
      }
    }

    if (enemy -> GetBuff().GetEvade() > 0){
        sf::Texture tmptexture;
        if(!tmptexture.loadFromFile("res/textures/icons/evade.png")){
          std::cout << "error with attack up"<<std::endl;
          throw std::invalid_argument("error with argument");
        }
        sf::Sprite tmpsprite;
        tmpsprite.setTexture(tmptexture);
        tmpsprite.move(positionX*scale, positionY*scale);
        tmpsprite.scale(scale/6, scale/6);
        texture.draw(tmpsprite);
        //text for value of attack/buff/debuff/block
        sf::Text tmptext;
        tmptext.setString(std::to_string(enemy -> GetBuff(). GetEvade()));
        tmptext.setFont(lifefont);
        tmptext.setStyle(1);
        tmptext.setCharacterSize(18 * scale);
        tmptext.setColor(sf::Color::Black);
        tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
        texture.draw(tmptext);
        tmptext.setCharacterSize(15 * scale);
        tmptext.setColor(sf::Color::White);
        tmptext.move(0,2 * scale);
        texture.draw(tmptext);

        if (positionX +40 > 200){
          positionX = 10;
          positionY +=35;
        }
        else{
          positionX += 40;  //200 = limit
        }
      }

      if (enemy -> GetBuff().GetHeal() > 0){
          sf::Texture tmptexture;
          if(!tmptexture.loadFromFile("res/textures/icons/heal.png")){
            std::cout << "error with attack up"<<std::endl;
            throw std::invalid_argument("error with argument");
          }
          sf::Sprite tmpsprite;
          tmpsprite.setTexture(tmptexture);
          tmpsprite.move(positionX *scale, positionY *scale);
          tmpsprite.scale(scale/6, scale/6);
          texture.draw(tmpsprite);
          //text for value of attack/buff/debuff/block
          sf::Text tmptext;
          tmptext.setString(std::to_string(enemy -> GetBuff(). GetHeal()));
          tmptext.setFont(lifefont);
          tmptext.setStyle(1);
          tmptext.setCharacterSize(18 * scale);
          tmptext.setColor(sf::Color::Black);
          tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
          texture.draw(tmptext);
          tmptext.setCharacterSize(15 * scale);
          tmptext.setColor(sf::Color::White);
          tmptext.move(0,2 * scale);
          texture.draw(tmptext);

          if (positionX +40 > 200){
            positionX = 10;
            positionY +=35;
          }
          else{
            positionX += 40;  //200 = limit
          }
        }

        if (enemy -> GetBuff().GetRetaliate() > 0){
            sf::Texture tmptexture;
            if(!tmptexture.loadFromFile("res/textures/icons/retaliate.png")){
              std::cout << "error with attack up"<<std::endl;
              throw std::invalid_argument("error with argument");
            }
            sf::Sprite tmpsprite;
            tmpsprite.setTexture(tmptexture);
            tmpsprite.move(positionX*scale, positionY  *scale);
            tmpsprite.scale(scale/6, scale/6);
            texture.draw(tmpsprite);
            //text for value of attack/buff/debuff/block
            sf::Text tmptext;
            tmptext.setString(std::to_string(enemy -> GetBuff(). GetRetaliate()));
            tmptext.setFont(lifefont);
            tmptext.setStyle(1);
            tmptext.setCharacterSize(18 * scale);
            tmptext.setColor(sf::Color::Black);
            tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
            texture.draw(tmptext);
            tmptext.setCharacterSize(15 * scale);
            tmptext.setColor(sf::Color::White);
            tmptext.move(0,2 * scale);
            texture.draw(tmptext);

            if (positionX +40 > 200){
              positionX = 10;
              positionY +=35;
            }
            else{
              positionX += 40;  //200 = limit
            }
          }

          if (enemy -> GetDebuff().GetBlockMinus() > 0){
              sf::Texture tmptexture;
              if(!tmptexture.loadFromFile("res/textures/icons/block_down.png")){
                // std::cout << "error with attack up"<<std::endl;
                throw std::invalid_argument("error with argument");
              }
              sf::Sprite tmpsprite;
              tmpsprite.setTexture(tmptexture);
              tmpsprite.move(positionX*scale, positionY*scale);
              tmpsprite.scale(scale/6, scale/6);
              texture.draw(tmpsprite);
              //text for value of attack/buff/debuff/block
              sf::Text tmptext;
              tmptext.setString(std::to_string(enemy -> GetDebuff(). GetBlockMinus()));
              tmptext.setFont(lifefont);
              tmptext.setStyle(1);
              tmptext.setCharacterSize(18 * scale);
              tmptext.setColor(sf::Color::Black);
              tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
              texture.draw(tmptext);
              tmptext.setCharacterSize(15 * scale);
              tmptext.setColor(sf::Color::White);
              tmptext.move(0,2 * scale);
              texture.draw(tmptext);

              if (positionX +40 > 200){
                positionX = 10;
                positionY +=35;
              }
              else{
                positionX += 40;  //200 = limit
              }
            }

            if (enemy -> GetDebuff().GetBlockMinus() > 0){
                sf::Texture tmptexture;
                if(!tmptexture.loadFromFile("res/textures/icons/attack_down.png")){
                  std::cout << "error with attack up"<<std::endl;
                  throw std::invalid_argument("error with argument");
                }
                sf::Sprite tmpsprite;
                tmpsprite.setTexture(tmptexture);
                tmpsprite.move(positionX*scale, positionY*scale);
                tmpsprite.scale(scale/6, scale/6);
                texture.draw(tmpsprite);
                //text for value of attack/buff/debuff/block
                sf::Text tmptext;
                tmptext.setString(std::to_string(enemy -> GetDebuff(). GetBlockMinus()));
                tmptext.setFont(lifefont);
                tmptext.setStyle(1);
                tmptext.setCharacterSize(18 * scale);
                tmptext.setColor(sf::Color::Black);
                tmptext.move((positionX + 10) * scale, (positionY + 15) * scale);
                texture.draw(tmptext);
                tmptext.setCharacterSize(15 * scale);
                tmptext.setColor(sf::Color::White);
                tmptext.move(0,2 * scale);
                texture.draw(tmptext);

                if (positionX +40 > 200){
                  positionX = 10;
                  positionY +=35;
                }
                else{
                  positionX += 40;  //200 = limit
                }
              }


  texture.display();

}

void Editeur::SetEditeurPile ( float scale,  std::string image, int number){

    if (!texture.create(int(400*scale), int(600*scale))){
      std::cout<<"RenderTexture error"<<std::endl;
      throw std::invalid_argument("error with argument");
    }
    texture.clear(sf::Color::Transparent);

    sf::Sprite sprite;
    sf::Texture texturePile;
    if (!texturePile.loadFromFile(image)){
      std::cout << "error with image" << std::endl;
      throw std::invalid_argument("error with argument");
    }
    sprite.setTexture(texturePile);
    sprite.scale(scale, scale);

    sf::Font font;

    if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
      std::cout <<"error with font name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(number));
    text.setColor(sf::Color::White);
    text.setCharacterSize(20 * scale);
    text.move(50 * scale, 250 * scale);

    texture.draw(sprite);

    texture.draw(text);
    texture.display();

  }
