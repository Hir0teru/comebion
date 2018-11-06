#include "Rendu.h"
#include <SFML/Graphics.hpp>
#include <iostream>



using namespace render;
using namespace state;


    Rendu::Rendu(){
      dimensionX = 1080;
      dimensionY = 720;
      gamestate = std::make_shared<state::GameState>();


    }
    Rendu::~Rendu (){

    }


    void Rendu::Click (int x, int y){

    }




    sf::RenderTexture& Rendu::GetTexture(){
      return texture;
    }
    void Rendu::DrawInsideRoom (){

      if (!texture.create(dimensionX, dimensionY)){
        std::cout<<"RenderTexture error"<<std::endl;
        throw std::invalid_argument("error with argument");
      }

        texture.clear(sf::Color::Transparent);
        sf::Sprite sprite;
        sprite.setTexture(background.getTexture());
        texture.draw(sprite);

        for (auto& player : texturePlayers){
          sprite.setTexture(player -> GetTexture().getTexture());
          sprite.setPosition(player -> GetX(), player -> GetY());
          texture.draw(sprite);
        }
        for (auto& enemy : textureEnemies){
          sprite.setTexture(enemy -> GetTexture().getTexture());
          sprite.setPosition(enemy -> GetX(), enemy -> GetY());
          texture.draw(sprite);
        }
        for (auto& pile : texturePiles){
          sprite.setTexture(pile -> GetTexture().getTexture());
          sprite.setPosition(pile -> GetX(), pile -> GetY());
          texture.draw(sprite);
        }
        for (auto& card : textureCards){
          sprite.setTexture(card -> GetTexture().getTexture());
          sprite.setPosition(card -> GetX(), card -> GetY());
          texture.draw(sprite);
        }
        texture.display();

    }
    std::shared_ptr<state::GameState>& Rendu::GetGameState (){
      return gamestate;
    }
    void Rendu::SetTextureCards (std::vector<std::unique_ptr<Editeur>>& textureCards){
      this -> textureCards = std::move(textureCards);
    }
    void Rendu::SetTextureEnemies (std::vector<std::unique_ptr<Editeur>>& textureEnemies){
      this -> textureEnemies = std::move(textureEnemies);
    }

    void Rendu::SetTexturePlayers (std::vector<std::unique_ptr<Editeur>>& texturePlayers){
      this -> texturePlayers = std::move(texturePlayers);
    }

    void Rendu::SetTexturePiles (std::vector<std::unique_ptr<Editeur>>& texturePiles){
      this -> texturePiles = std::move(texturePiles);
    }
    std::vector<std::unique_ptr<Editeur>>& Rendu::GetTextureCards (){
      return textureCards;
    }
    std::vector<std::unique_ptr<Editeur>>& Rendu::GetTextureEnemies (){
      return textureEnemies;
    }
    std::vector<std::unique_ptr<Editeur>>& Rendu::GetTexturePlayers (){
      return texturePlayers;
    }

    std::vector<std::unique_ptr<Editeur>>& Rendu::GetTexturePiles (){
      return texturePiles;
    }
    sf::RenderTexture& Rendu::GetBackground (){
      return background;
    }
    void Rendu::SetBackground (std::string image){
      if(!background.create(dimensionX, dimensionY)){
        throw std::invalid_argument("error with background creation");
      }
      sf::Texture newBackground;
      if (!newBackground.loadFromFile(image)){
        std::cout << "error with background image";
        throw std::invalid_argument("error with input");
      }
      background.clear(sf::Color::Transparent);
      sf::Sprite sprite;
      sprite.setTexture(newBackground);
      sprite.scale(1080/dimensionX, 720/dimensionY);
      background.draw(sprite);
      background.display();
    }

    //dimensions:
    int Rendu::GetDimensionX (){
      return dimensionX;
    }
    int Rendu::GetDimensionY (){
      return dimensionY;
    }
    void Rendu::SetDimensionX (int dimensionX){
      this -> dimensionX = dimensionX;
    }
    void Rendu::SetDimensionY (int dimensionY){
      this -> dimensionY = dimensionY;
    }


    // change textures:
    void Rendu::ChangeTextureCard (float scale, state::Card* card, int index, int statAttack, int statBlock){
      if (!(index >= 0 && index < (int) textureCards.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      textureCards[index] -> SetEditeurCard(scale, card, statAttack, statBlock);
    }

    void Rendu::ChangeTextureEnemy (float scale, std::unique_ptr<state::Enemy>& enemy, int index){
      if (!(index >= 0 && index < (int) textureEnemies.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      textureEnemies[index] -> SetEditeurEnemy(scale, enemy);
    }

    void Rendu::ChangeTexturePlayer (float scale, state::Player* player, int index){
      if (!(index >= 0 && index < (int) texturePlayers.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      texturePlayers[index] -> SetEditeurPlayer(scale, player);
    }



    void Rendu::SetTexturePile (float scale, int index, std::string image, int number){
      if (!(index >= 0 && index < (int) texturePiles.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      texturePiles[index] -> SetEditeurPile(scale, image, number);
    }


// remove textures
    void Rendu::RemoveEnemy (int index){
      if (!(index >= 0 && index < (int) textureEnemies.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      for (int i = index +1; i < (int) textureEnemies.size() - 1; i++){
        textureEnemies[i] = std::move(textureEnemies[i + 1]);
      }
      textureEnemies[textureEnemies.size() - 1] = std::move(nullptr);
    }


    void Rendu::RemovePlayer (int index){
      if (!(index >= 0 && index < (int) texturePlayers.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      for (int i = index +1; i < (int) texturePlayers.size() - 1; i++){
        texturePlayers[i] = std::move(texturePlayers[i + 1]);
      }
      texturePlayers[texturePlayers.size() - 1] = std::move(nullptr);
    }


    void Rendu::RemoveCard (int index){
      if (!(index >= 0 && index < (int) textureCards.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      for (int i = index +1; i < (int) textureCards.size() - 1; i++){
        textureCards[i] = std::move(textureCards[i + 1]);
      }
      textureCards[textureCards.size() - 1] = std::move(nullptr);
    }


    void Rendu::RemovePile (int index){
      if (!(index >= 0 && index < (int) texturePiles.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      for (int i = index +1; i < (int) texturePiles.size() - 1; i++){
        texturePiles[i] = std::move(texturePiles[i + 1]);
      }
      texturePiles[texturePiles.size() - 1] = std::move(nullptr);

    }


// add texture

    void Rendu::AddTexturePile (int x, int y, float scale, std::string image, int number){
      if (!((int) texturePiles.size() < 2)){
        std::cout << "Max number of pile texture is 2. Can not add any more";
        throw std::invalid_argument("error with newSize of texturePiles");
      }
      texturePiles.push_back(std::make_unique<Editeur>(x, y, scale, image, number));
    }

    void Rendu::AddTextureCard (int x, int y, float scale, state::Card * card, int statAttack, int statBlock){
      if (!((int) textureCards.size() < 7)){
        std::cout << "Max number of card texture is 7. Can not add any more";
        throw std::invalid_argument("error with newSize of textureCards");
      }
      textureCards.push_back(std::make_unique<Editeur>(x, y, scale, card, statAttack, statBlock));
    }

    void Rendu::AddTexturePlayer (int x, int y, float scale, state::Player* player){
      if (!((int) texturePlayers.size() < 2)){
        std::cout << "Max number of player texture is 2. Can not add any more";
        throw std::invalid_argument("error with newSize of texturePlayers");
      }
      texturePlayers.push_back(std::make_unique<Editeur>(x, y, scale, player));
    }

    void Rendu::AddTextureEnemy (int x , int y, float scale, std::unique_ptr<state::Enemy>& enemy){
      if (!((int) textureEnemies.size() < 3)){
        std::cout << "Max number of pile texture is 3. Can not add any more";
        throw std::invalid_argument("error with newSize of textureEnemies");
      }
      textureEnemies.push_back(std::make_unique<Editeur>(x, y, scale, enemy));
    }



// remove all texture
    void Rendu::RemoveEnemies (){
      for (auto& enemy : textureEnemies){
        enemy = std::move(nullptr);
      }
    }
    void Rendu::RemovePlayers (){
      for (auto& player : texturePlayers){
        player = std::move(nullptr);
      }
    }
    void Rendu::RemovePiles (){
      for (auto& pile : texturePiles){
        pile = std::move(nullptr);
      }
    }
    void Rendu::RemoveCards (){
      for (auto& card : textureCards){
        card = std::move(nullptr);
      }
    }

    sf::RenderTexture& Rendu::GetTextureMap (){
      return textureMap;
    }

    void Rendu::SetTextureMap (float scale){
      if (!textureMap.create(dimensionX, dimensionY)){
        std::cout<<"RenderTexture error"<<std::endl;
        throw std::invalid_argument("error with argument");
      }
      texture.clear(sf::Color::Transparent);
      int currentFloor = gamestate -> GetMap() ->  GetCurrentFloor();
      std::unique_ptr<Floor>& floor = gamestate -> GetMap() ->  GetFloors()[currentFloor];
      std::shared_ptr<Room> currentRoom = floor -> GetFirstRoom();

      int element = floor -> GetElement();
      if (element ==1){
        sf::Texture tmptexture;
        if (!tmptexture.loadFromFile("res/textures/Map/map_white.jpg")){
          throw std::invalid_argument("error with map background (air)");
        }
        sf::Sprite tmpsprite;
        tmpsprite.setTexture(tmptexture);
        tmpsprite.scale(dimensionX/1080, dimensionY/720);

        textureMap.draw(tmpsprite);
      }
      else{
        if (element ==2){
          sf::Texture tmptexture;
          if (!tmptexture.loadFromFile("res/textures/Map/map_blue.jpg")){
            throw std::invalid_argument("error with map background (water)");
          }
          sf::Sprite tmpsprite;
          tmpsprite.setTexture(tmptexture);
          tmpsprite.scale(dimensionX/1080, dimensionY/720);

          textureMap.draw(tmpsprite);
        }
        else{
          if (element ==3){
            sf::Texture tmptexture;
            if (!tmptexture.loadFromFile("res/textures/Map/map_brown.jpg")){
              throw std::invalid_argument("error with map background (earth)");
            }
            sf::Sprite tmpsprite;
            tmpsprite.setTexture(tmptexture);
            tmpsprite.scale(dimensionX/1080, dimensionY/720);

            textureMap.draw(tmpsprite);
          }
          else{
            sf::Texture tmptexture;
            if (!tmptexture.loadFromFile("res/textures/Map/map_red.jpg")){
              throw std::invalid_argument("error with map background (fire)");
            }
            sf::Sprite tmpsprite;
            tmpsprite.setTexture(tmptexture);
            tmpsprite.scale(dimensionX/1080, dimensionY/720);

            textureMap.draw(tmpsprite);
          }
        }
      }

      int positionX = 20 ;
      int positionY = 300 ;

      while (currentRoom){
        sf::Texture textureRoom;
        if (!textureRoom.loadFromFile(currentRoom -> GetImageMapRoom())){
          std::cout << "error with image room" << std::endl;
          throw std::invalid_argument("error with image name");
        }
        sf::Sprite sprite;
        sprite.setTexture(textureRoom);
        sprite.setPosition(positionX * scale, positionY * scale);
        sprite.scale(scale/4, scale/4);
        textureMap.draw(sprite);
        positionX += 100 ;
        currentRoom = currentRoom -> GetNextRoom();

      }
      textureMap.display();
    }


void Rendu::SetTextureRoom(){
  textureCards.clear();
  textureEnemies.clear();
  texturePlayers.clear();
  texturePiles.clear();
  int floorNb = gamestate -> GetMap() -> GetCurrentFloor();
  std::shared_ptr<Room> room = gamestate -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();


  SetBackground(room -> GetImageInsideRoom());



  float scale = dimensionX/1080;

  if(room -> GetIsSleepRoom()){
    //text
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("res/text_fonts/Anke Print.ttf")){
      std::cout <<"error with font name" << std::endl;
      throw std::invalid_argument("error with argument");
    }
    text.setFont(font);
    text.setString("Heal for  " + std::to_string(room -> GetHeal())+ " HP or meditate?");
    text.setColor(sf::Color::White);
    text.setCharacterSize(30 * scale);
    text.setStyle(sf::Text::Bold);
    text.move(349 * scale, 219 * scale);
    background.draw(text);
    text.move(0 , 2 );
    background.draw(text);
    text.move(2 , 0 );
    background.draw(text);
    text.move(0 , -2 );
    background.draw(text);
    text.setColor(sf::Color::Black);
    text.move(-1, 1);
    background.draw(text);


    text.setString("Heal");
    text.setColor(sf::Color::White);
    text.move(9, 69 * scale);
    background.draw(text);
    text.move(0 , 2 );
    background.draw(text);
    text.move(2 , 0 );
    background.draw(text);
    text.move(0 , -2 );
    background.draw(text);
    text.setColor(sf::Color::Black);
    text.move(-1, 1);
    background.draw(text);

    text.setString("Meditate");
    text.setColor(sf::Color::White);
    text.move(189* scale, -1);
    background.draw(text);
    text.move(0 , 2 );
    background.draw(text);
    text.move(2 , 0 );
    background.draw(text);
    text.move(0 , -2 );
    background.draw(text);
    text.setColor(sf::Color::Black);
    text.move(-1, 1);
    background.draw(text);

    background.display();


  }
  else{
    if(room -> GetIsSpecialTrainingRoom()){
      //text
      sf::Text text;
      sf::Font font;
      if (!font.loadFromFile("res/text_fonts/Anke Print.ttf")){
        std::cout <<"error with font name" << std::endl;
        throw std::invalid_argument("error with argument");
      }
      text.setFont(font);
      text.setString("Choose a card to obtain : ");
      text.setColor(sf::Color::White);
      text.setCharacterSize(30 * scale);
      text.setStyle(sf::Text::Bold);
      text.move(339 * scale, 219 * scale);
      background.draw(text);
      text.move(0 , 2 );
      background.draw(text);
      text.move(2 , 0 );
      background.draw(text);
      text.move(0 , -2 );
      background.draw(text);
      text.setColor(sf::Color::Black);
      text.move(-1, 1);
      background.draw(text);

      std::vector<Card*> reward =  room -> GetCardReward();
      int x = 320;
      int y = 250;
      for (auto card : reward){
        AddTextureCard(x * scale, y* scale, scale/3, card, 0, 0);
        x += 150;
      }
      background.display();
    }
    else{
      // batlle room
      background.display();

      std::vector<Player*> players = gamestate -> GetPlayers();

      int x = 10;
      int y = 300;
      for (auto player : players){
        AddTexturePlayer(x* scale/1.5, y * scale/1.5, scale/1.5, player);
        x+= 250;

      }

      std::vector<std::unique_ptr<Enemy>>& enemies =room -> GetEnemies();
       x = 1300;
       y = 300;
      for (auto& enemy : enemies){
        AddTextureEnemy(x* scale/1.5, y * scale/1.5, scale/1.5, enemy);
        x-= 250;
      }
      int entityTurn =  room -> GetEntityTurn(); //0, 1 = joueurs, 2,3,4 = ennemis
      if( entityTurn >= 0 && entityTurn < 2){
        std::vector<Card*> cards =  room -> GetHands()[entityTurn] -> GetCards();;
        x = 120;
        y = 480;
        int statAttack = players[entityTurn] -> GetStatAttack();
        int statBlock = players[entityTurn] -> GetStatBlock();
        for (auto card : cards){
          AddTextureCard(x * scale, y * scale, scale/3, card, statAttack, statBlock);
          x+= 110;
        }
        AddTexturePile(10 *scale, 480 * scale, scale/3,  "res/textures/cards/back_card_fin.png", room -> GetDrawPiles()[entityTurn] -> GetSize());
        AddTexturePile(900 *scale, 480 * scale, scale/3, "res/textures/cards/back_card_fin.png", room -> GetDiscardPiles()[entityTurn] -> GetSize());
      }
    }
  }
}
