// #include "Editeur.h"
// #include <SFML/Graphics.hpp>
// #include <iostream>
//
// using namespace render;
// using namespace state;
//
//
// Editeur::Editeur(){
//   x = 0;
//   y = 0;
//   width = 100;
//   height = 200;
// }
//
// Editeur::Editeur( int x, int y, int width, int height, std::shared_ptr<Card>& card){
//   this -> x = x;
//   this -> y = y;
//   this -> width = width;
//   this -> height = height;
//   sf::Font font;
//   // name of the card:
//   if (!font.loadFromFile("././res/text_fonts/Anke Print.ttf")){
//     std::cout <<"error with font name" << std::endl;
//   }
//   sf::Text name;
//   name.setFont(font);
//   name.setString(card->GetName());
//   name.setCharacterSize(20);
//   name.setColor(sf::Color::Black);
//   name.move(10.f, 20.f);
//
//   // texture:
//
//   if (!texture.create(width, height)){
//     std::cout<<"RenderTexture error"<<std::endl;
//   }
//   texture.clear(sf::Color::Transparent);
//   sf::Texture cardtexture;
//   if (!cardtexture.loadFromFile("././res/textures/cards/card_air.png")){
//     std::cout << "error with cardtexture name" << std::endl;
//   }
//   sf::Sprite spriteCard;
//   spriteCard.setTexture(cardtexture);
//   spriteCard.scale(0.5,0.5);
//   // spriteCard.scale(0.5f, 0.5f);
//   // spriteCard.move(10.f, 20.f);
//
//   texture.draw(spriteCard);
//
//   sf::Texture imtexture;
//   if (!imtexture.loadFromFile("././res/textures/icons/attack.png")){
//     std::cout << "error with imtexture name" << std::endl;
//   }
//   spriteCard.setTexture(imtexture);
//   spriteCard.scale(1, 1);
//   spriteCard.move(50,30);
//
//   texture.draw(name);
//   texture.draw(spriteCard);
//   texture.display();
//
// }
//
// Editeur::~Editeur(){}
//
// void Editeur::Click(int x, int y){
//
// }
// int const Editeur::GetX(){
//   return x;
// }
// int const Editeur::GetY(){
//   return y;
// }
// int const Editeur::GetWidth(){
//   return width;
// }
// int const Editeur::GetHeight(){
//   return height;
// }
// sf::RenderTexture&  Editeur::GetTexture(){
//   return texture;
// }
