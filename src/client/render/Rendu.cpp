#include "Rendu.h"
#include <SFML/Graphics.hpp>
#include <iostream>



using namespace render;
using namespace state;


    Rendu::Rendu(){}

    Rendu::Rendu(std::shared_ptr<GameState>& gameState){
      dimensionX = 1080;
      dimensionY = 720;
      this -> gameState = gameState;
      renderState = 0; //0 = map, 1 = inside room, 2 = inside enemyroom and choosing card, 3 = game lost
      selectedCard = -1;
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
          if(player){
            sprite.setTexture(player -> GetTexture().getTexture());
            sprite.setPosition(player -> GetX(), player -> GetY());
            texture.draw(sprite);
          }
        }
        for (auto& enemy : textureEnemies){
          if(enemy){
            sprite.setTexture(enemy -> GetTexture().getTexture());
            sprite.setPosition(enemy -> GetX(), enemy -> GetY());
            texture.draw(sprite);
          }
        }
        for (auto& pile : texturePiles){
          if(pile){
            sprite.setTexture(pile -> GetTexture().getTexture());
            sprite.setPosition(pile -> GetX(), pile -> GetY());
            texture.draw(sprite);
          }
        }
        for (auto& card : textureCards){
          if(card){
            sprite.setTexture(card -> GetTexture().getTexture());
            sprite.setPosition(card -> GetX(), card -> GetY());
            texture.draw(sprite);
          }
        }
        texture.display();

    }
    std::shared_ptr<state::GameState>& Rendu::GetGameState (){
      return gameState;
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

      sf::Text text;
      sf::Font font;
      if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
        std::cout <<"error with font name" << std::endl;
        throw std::invalid_argument("error with argument");
      }
      text.setFont(font);
      int currentFloor = gameState -> GetMap() ->  GetCurrentFloor();
      int entityTurn = gameState -> GetMap() ->  GetFloors()[currentFloor]->GetCurrentRoom()->GetEntityTurn();
      if(entityTurn >=2){
        text.setString("Playing : enemy " + std::to_string(entityTurn));
      } else text.setString("Playing : player " + std::to_string(entityTurn));
      int scale = 1.;
      text.setColor(sf::Color::White);
      text.setCharacterSize(15 * scale);
      text.setStyle(sf::Text::Bold);
      text.move(480 * scale, 10 * scale);
      textureMap.draw(text);
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
      textureEnemies[index] = std::move(nullptr);
    }


    void Rendu::RemovePlayer (int index){
      if (!(index >= 0 && index < (int) texturePlayers.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      texturePlayers[index] = std::move(nullptr);
    }


    void Rendu::RemoveCard (int index){
      if (!(index >= 0 && index < (int) textureCards.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }
      textureCards[index] = std::move(nullptr);
    }


    void Rendu::RemovePile (int index){
      if (!(index >= 0 && index < (int) texturePiles.size())){
        std::cout << "index not in range" << std::endl;
        throw std::invalid_argument("error with index");
      }

      texturePiles[index] = std::move(nullptr);

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
      int currentFloor = gameState -> GetMap() ->  GetCurrentFloor();
      std::unique_ptr<Floor>& floor = gameState -> GetMap() ->  GetFloors()[currentFloor];
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
        if(currentRoom == floor -> GetCurrentRoom()){
          sf::CircleShape shape(50 * scale);
          shape.setFillColor(sf::Color::Transparent);
          shape.setOutlineThickness(2);
          shape.setOutlineColor(sf::Color::Red);
          shape.setPosition((positionX - 10) * scale, (positionY-10) * scale);
          textureMap.draw(shape);
        }
        positionX += 100 ;
        currentRoom = currentRoom -> GetNextRoom();

      }

      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/other/button1.png")){
        throw std::invalid_argument("error with texture button");
      }
      sf::Sprite sprite;
      sprite.setTexture(tmptexture);
      sprite.scale(scale, scale);
      sprite.move(500 * scale, 500 * scale);
      textureMap.draw(sprite);
      sf::Text text;
      sf::Font font;
      if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
        std::cout <<"error with font name" << std::endl;
        throw std::invalid_argument("error with argument");
      }
      text.setFont(font);
      text.setString("Enter Room");
      text.setColor(sf::Color::Black);
      text.setCharacterSize(15 * scale);
      text.setStyle(sf::Text::Bold);
      text.move(510 * scale, 510 * scale);
      textureMap.draw(text);
      text.move(0 , 2 );
      background.draw(text);
      text.move(2 , 0 );
      background.draw(text);
      text.move(0 , -2 );
      background.draw(text);
      text.setColor(sf::Color::White);
      text.move(-1, 1);
      textureMap.draw(text);

      textureMap.display();
    }


void Rendu::SetTextureRoom(){

  textureCards.clear();
  textureEnemies.clear();
  texturePlayers.clear();
  texturePiles.clear();
  int floorNb = gameState -> GetMap() -> GetCurrentFloor();
  std::shared_ptr<Room>& room = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();


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

    sf::Texture tmptexture;
    if(!tmptexture.loadFromFile("res/textures/other/button1.png")){
      throw std::invalid_argument("error with texture button");
    }
    sf::Sprite sprite;
    sprite.setTexture(tmptexture);
    sprite.scale(scale, scale);
    sprite.setPosition(350 * scale, 280 * scale);
    background.draw(sprite);

    text.setCharacterSize(20 * scale);
    text.setString("Heal");
    text.setColor(sf::Color::White);
    text.move(15, 65 * scale);
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

    sprite.setPosition(540 * scale, 280 * scale);
    background.draw(sprite);

    text.setString("Meditate");
    text.setColor(sf::Color::White);
    text.move(195* scale, -1);
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
      text.setPosition(339 * scale, 219 * scale);
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

      std::vector<Card*> reward =  room -> GetReward();
      int x = 320;
      int y = 250;
      for (auto card : reward){
        AddTextureCard(x * scale, y* scale, scale/3, card, 0, 0);
        x += 150;
      }
      sf::Texture tmptexture;
      if(!tmptexture.loadFromFile("res/textures/other/button1.png")){
        throw std::invalid_argument("error with texture button");
      }
      sf::Sprite sprite;
      sprite.setTexture(tmptexture);
      sprite.scale(scale, scale);
      sprite.setPosition(480 * scale, 450 * scale);
      background.draw(sprite);
      if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
        std::cout <<"error with font name" << std::endl;
        throw std::invalid_argument("error with argument");
      }
      text.setFont(font);
      text.setString("Pass");
      text.setColor(sf::Color::Black);
      text.setCharacterSize(15 * scale);
      text.setStyle(sf::Text::Bold);
      text.setPosition(515 * scale, 460 * scale);
      background.draw(text);
      text.move(0 , 2 );
      background.draw(text);
      text.move(2 , 0 );
      background.draw(text);
      text.move(0 , -2 );
      background.draw(text);
      text.setColor(sf::Color::White);
      text.move(-1, 1);
      background.draw(text);


      background.display();
    }
    else{
      // batlle room
      if( room -> GetIsGameLost()){
        SetBackground("res/textures/background/you_died.jpg");
      } else if( !room -> GetIsFightWon()){
        sf::Texture tmptexture;
        if(!tmptexture.loadFromFile("res/textures/other/button1.png")){
          throw std::invalid_argument("error with texture button");
        }
        sf::Sprite sprite;
        sprite.setTexture(tmptexture);
        sprite.scale(scale, scale);
        sprite.move(880 * scale, 650 * scale);
        background.draw(sprite);
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
          std::cout <<"error with font name" << std::endl;
          throw std::invalid_argument("error with argument");
        }
        text.setFont(font);
        text.setString("End turn");
        text.setColor(sf::Color::Black);
        text.setCharacterSize(15 * scale);
        text.setStyle(sf::Text::Bold);
        text.move(895 * scale, 660 * scale);
        background.draw(text);
        text.move(0 , 2 );
        background.draw(text);
        text.move(2 , 0 );
        background.draw(text);
        text.move(0 , -2 );
        background.draw(text);
        text.setColor(sf::Color::White);
        text.move(-1, 1);
        background.draw(text);

        background.display();



        std::vector<Player*> players = gameState -> GetPlayers();

        int x = 10;
        int y = 300;
        for (auto player : players){
          if(player -> GetIsEntityAlive()){
            AddTexturePlayer(x* scale/1.5, y * scale/1.5, scale/1.5, player);
            x+= 250;
          }

        }

        std::vector<std::unique_ptr<Enemy>>& enemies =room -> GetEnemies();

         x = 1300;
         y = 300;
        for (auto& enemy : enemies){
          if(enemy -> GetIsEntityAlive()){
            AddTextureEnemy(x* scale/1.5, y * scale/1.5, scale/1.5, enemy);
            x-= 250;
          }
        }
        int entityTurn =  room -> GetEntityTurn(); //0, 1 = joueurs, 2,3,4 = ennemis
        if( entityTurn >= 0 && entityTurn < 2){
          std::vector<Card*> cards =  room -> GetHands()[entityTurn] -> GetCards();
          x = 120;
          y = 480;
          int statAttack = players[entityTurn] -> GetStatAttack();
          int statBlock = players[entityTurn] -> GetStatBlock();
          for (auto card : cards){
              AddTextureCard(x * scale, y * scale, scale/3, card, statAttack, statBlock);
              x+= 110;
          }
          AddTexturePile(10 *scale, 480 * scale, scale/4,  "res/textures/cards/back_card_fin.png", room -> GetDrawPiles()[entityTurn] -> GetSize());

          AddTexturePile(900 *scale, 480 * scale, scale/4, "res/textures/cards/back_card_fin.png", room -> GetDiscardPiles()[entityTurn] -> GetSize());
        }
      }
      else{

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
        text.setPosition(339 * scale, 219 * scale);
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

        std::vector<Card*> reward =  room -> GetReward();
        int x = 320;
        int y = 250;
        for (auto card : reward){
          AddTextureCard(x * scale, y* scale, scale/3, card, 0, 0);
          x += 150;
        }
        sf::Texture tmptexture;
        if(!tmptexture.loadFromFile("res/textures/other/button1.png")){
          throw std::invalid_argument("error with texture button");
        }
        sf::Sprite sprite;
        sprite.setTexture(tmptexture);
        sprite.scale(scale, scale);
        sprite.setPosition(480 * scale, 450 * scale);
        background.draw(sprite);
        if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){
          std::cout <<"error with font name" << std::endl;
          throw std::invalid_argument("error with argument");
        }
        text.setFont(font);
        text.setString("Pass");
        text.setColor(sf::Color::Black);
        text.setCharacterSize(15 * scale);
        text.setStyle(sf::Text::Bold);
        text.setPosition(515 * scale, 460 * scale);
        background.draw(text);
        text.move(0 , 2 );
        background.draw(text);
        text.move(2 , 0 );
        background.draw(text);
        text.move(0 , -2 );
        background.draw(text);
        text.setColor(sf::Color::White);
        text.move(-1, 1);
        background.draw(text);


        background.display();
      }
    }
  }
}

void Rendu::UpdateTexturesPiles(){
  float scale = dimensionX / 1080.;
  int floorNb = gameState -> GetMap() -> GetCurrentFloor();
  std::shared_ptr<Room>& room = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();
  texturePiles.clear();
  int entityTurn =  room -> GetEntityTurn(); //0, 1 = joueurs, 2,3,4 = ennemis
  if( entityTurn >= 0 && entityTurn < 2){

    AddTexturePile(10 *scale, 480 * scale, scale/4,  "res/textures/cards/back_card_fin.png", room -> GetDrawPiles()[entityTurn] -> GetSize());

    AddTexturePile(900 *scale, 480 * scale, scale/4, "res/textures/cards/back_card_fin.png", room -> GetDiscardPiles()[entityTurn] -> GetSize());
  }
}

void Rendu::UpdateTexturesPlayers(){
  float scale = dimensionX / 1080.;
  texturePlayers.clear();
  std::vector<Player*> players = gameState -> GetPlayers();

  int x = 10;
  int y = 300;
  for (auto player : players){
    if(player -> GetIsEntityAlive()){
      AddTexturePlayer(x* scale/1.5, y * scale/1.5, scale/1.5, player);
      x+= 250;
    }
  }
}

void Rendu::UpdateTexturesCards(){
  float scale = dimensionX / 1080.;
  textureCards.clear();
  int floorNb = gameState -> GetMap() -> GetCurrentFloor();
  std::shared_ptr<Room>& room = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();
  std::vector<Player*> players = gameState -> GetPlayers();
  int entityTurn =  room -> GetEntityTurn(); //0, 1 = joueurs, 2,3,4 = ennemis
  if( entityTurn >= 0 && entityTurn < 2){
    std::vector<Card*> cards =  room -> GetHands()[entityTurn] -> GetCards();
    int x = 120;
    int y = 480;
    int statAttack = players[entityTurn] -> GetStatAttack();
    int statBlock = players[entityTurn] -> GetStatBlock();
    for (auto card : cards){
        AddTextureCard(x * scale, y * scale, scale/3, card, statAttack, statBlock);
        x+= 110;
    }
  }
}

void Rendu::UpdateTexturesEnemies(){
  float scale = dimensionX / 1080.;
  textureEnemies.clear();
  int floorNb = gameState -> GetMap() -> GetCurrentFloor();
  std::shared_ptr<Room>& room = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();
  std::vector<std::unique_ptr<Enemy>>& enemies =room -> GetEnemies();

   int x = 1300;
   int y = 300;
  for (auto& enemy : enemies){
    if(enemy -> GetIsEntityAlive()){
      AddTextureEnemy(x* scale/1.5, y * scale/1.5, scale/1.5, enemy);
      x-= 250;
    }
  }
}

int Rendu::GetSelectedCard(){
  return selectedCard;
}

void Rendu::SetSelectedCard(int selectedCard){
  this -> selectedCard = selectedCard;
}

int Rendu::GetRenderState(){
  return renderState;
}

void Rendu::SetRenderState(int renderState){
  this->renderState = renderState;
}
