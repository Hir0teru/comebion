#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unistd.h>
#include <cstdlib>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

#include "state.h"
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

void testSFML(){
  PlayerManager* PM = PlayerManager::instance();
  CardManager* CM = CardManager::instance();

  Rendu* rendu = new Rendu();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);

  std::vector<Card*> cards;
  for(int i = 0; i < 7; i++){
    cards.push_back((*CM)[i]);
  }
  rendu -> GetGameState() -> SetPlayers(players);
  int floorNb = rendu -> GetGameState() -> GetMap() -> GetCurrentFloor();
  std::shared_ptr<Room>& room = rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb]-> GetCurrentRoom();
  // if(room -> GetIsEnemyRoom()){
  //   room -> GetHands()[0] ->  SetCards(cards);
  //   room -> GetDrawPiles()[0] -> SetCards(cards);
  //   room -> SetEntityTurn(0);
  // }
  //
  // rendu -> SetTextureMap(1);
  // //
  // rendu -> SetTextureRoom();
  // rendu -> DrawInsideRoom();

  sf::RenderWindow window(sf::VideoMode(rendu -> GetDimensionX(), rendu -> GetDimensionY()), "Test image");
  while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
    }


    room = rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();
    if(room -> GetIsEnemyRoom()){
      room -> GetHands()[0] ->  SetCards(cards);
      room -> GetDrawPiles()[0] -> SetCards(cards);
      room -> SetEntityTurn(0);
    }

    rendu -> SetTextureRoom();
    rendu -> DrawInsideRoom();

    window.clear(sf::Color::White);
    sf::Sprite sprite;
    // sprite.setTexture(rendu -> GetTextureMap().getTexture());
    sprite.setTexture(rendu -> GetTexture().getTexture());

    window.draw(sprite);
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Blue);
    // window.draw(shape);
    window.display();
    sleep(1);
    // room = room -> GetNextRoom();
    if(!room -> GetNextRoom()){
      rendu -> SetTextureMap(1);
      window.clear(sf::Color::White);
      sprite.setTexture(rendu -> GetTextureMap().getTexture());
      window.draw(sprite);
      window.display();
      sleep(0.5);
      if(floorNb == 3){
        rendu -> GetGameState() -> GetMap() -> SetCurrentFloor(0);
        floorNb = rendu -> GetGameState() -> GetMap() -> GetCurrentFloor();
        room = rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb] -> GetFirstRoom();
        rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb] -> SetCurrentRoom(room);
      }
      else{
        rendu -> GetGameState() -> GetMap() -> SetCurrentFloor(floorNb + 1);
        floorNb = rendu -> GetGameState() -> GetMap() -> GetCurrentFloor();
        room = rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb] -> GetFirstRoom();
        rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb] -> SetCurrentRoom(room);
      }
    }
    else{
      rendu -> GetGameState() -> GetMap() -> GetFloors()[floorNb]-> SetCurrentRoom(room -> GetNextRoom());
    }

  }
}


void testSFML2() {
  CardManager* CM = CardManager::instance();
  PlayerManager* PM = PlayerManager::instance();
  SkillManager* SM = SkillManager::instance();
  Buff* buff1 = new Buff(1,0,2,0,3);
  Debuff* debuff1 = new Debuff(0,4);

  Buff* buff2 = new Buff(0,5,0,6,0);
  Debuff* debuff2 = new Debuff(7,0);

  Buff* buff3 = new Buff(4,5,0,0,9);
  Debuff* debuff3 = new Debuff(1,0);

  Player* aang = (*PM)[0];
  aang -> SetBuff(*buff1);
  aang -> SetDebuff(*debuff1);
  aang -> SetLife(42);
  aang -> SetDebuff(*debuff2);

  Player* korra = (*PM)[1];
  korra -> SetBuff(*buff2);
  korra -> SetLife(42);
  korra -> SetDebuff(*debuff2);

  std::vector<EnemySkill*> skills;
  skills.push_back((*SM)[0]);
  skills.push_back((*SM)[1]);
  skills.push_back((*SM)[2]);

  std::unique_ptr<Enemy> enemy1 = std::make_unique<Enemy>( "La", 2, "res/textures/Enemy/Water/La.png", 5, 2, 502, 1, skills, 800);
  std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>("Vaatu", 3, "res/textures/Enemy/Vaatu.png", 10, 0, 450, 2, skills, 900);
  enemy2 -> SetIntent(2);
  enemy1 -> SetDebuff(*debuff3);
  enemy2 -> SetBuff(*buff3);
  enemy2 -> SetBlock(15);

  Editeur* editeur = new Editeur( 10, 10, 1,  (*CM)[0], 5, 5);

  int a;


  sf::RenderWindow window(sf::VideoMode(800, 600), "Test image");
  while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
    }


    window.clear(sf::Color::White);
    sf::Sprite sprite;
    sprite.setTexture(editeur -> GetTexture().getTexture());
    window.draw(sprite);
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Blue);
    // window.draw(shape);
    window.display();

    sleep(1);

    a = rand() % 100;

    if(a < 30){
      a = rand()%4;
      editeur -> SetEditeurCard(1, (*CM)[a], 5, 9);

    }
    else{
      if ( a < 45){
        editeur -> SetEditeurPlayer(1, aang);
      }
      else{
        if (a < 60){
          editeur -> SetEditeurPlayer(1, korra);
        }
        else{
          if (a < 80){
            editeur -> SetEditeurEnemy(1, enemy1);
          }
          else{
            editeur -> SetEditeurEnemy(1, enemy2);
          }
        }
      }
    }


  }

}

// Fin test SFML



void testBuff(){
  std::cout << "#### Test of class Buff ####" << std::endl;
  Buff* buff= new Buff(-1, -1, -1, -1, -1);
  if (buff->GetBlockPlus() < 0){
    delete buff;
    throw "Buff.blockPlus should be > 0";
  }
  if (buff->GetAttackPlus() < 0){
    delete buff;
    throw "Buff.attackPlus should be > 0";
  }
  if (buff->GetHeal() < 0){
    delete buff;
    throw "Buff.heal should be > 0";
  }
  if (buff->GetEvade() < 0){
    delete buff;
    throw "Buff.evade should be > 0";
  }
  if (buff->GetBlockPlus() < 0){
    delete buff;
    throw "Buff.blockPlus should be > 0";
  }
  delete buff;
  std::cout << "#### End test of class Buff ####" << std::endl;
}

void testCard(){
  std::cout << "#### Test of class Card ####" << std::endl;
  Card* card1 = new Card((std::string) "test", -1, -1,(std::string) "", -1, -1, -1, -1, -1, -1, std::make_unique<Debuff>(), std::make_unique<Buff>());
  Card* card2 = new Card((std::string) "test", -1, 4,(std::string) "", 5, -1, -1, -1, -1, -1, std::make_unique<Debuff>(), std::make_unique<Buff>());
  if (card1->GetCost() < 0){
    delete card1;
    delete card2;
    throw "Card.cost should be > 0";
  }

  if (card1->GetTarget() < 0 || card2->GetTarget() > 3){
    delete card1;
    delete card2;
    throw "Card.target should be between 0 and 3";
  }

  if (card1->GetElement() < 0 || card2->GetElement() > 4){
    delete card1;
    delete card2;
    throw "Card.element should be between 0 and 4";
  }

  if (card1->GetAttack() < 0){
    delete card1;
    delete card2;
    throw "Card.Attack should be > 0";
  }

  if (card1->GetBlock() < 0){
    delete card1;
    delete card2;
    throw "Card.Block should be > 0";
  }

  if (card1->GetDraw() < 0){
    delete card1;
    delete card2;
    throw "Card.Draw should be > 0";
  }

  if (card1->GetDiscard() < 0){
    delete card1;
    delete card2;
    throw "Card.Discard should be > 0";
  }

  if (card1->GetHeal() < 0){
    delete card1;
    delete card2;
    throw "Card.Heal should be > 0";
  }

  delete card1;
  delete card2;
  std::cout << "#### End test of class Card ####" << std::endl;
}

void testDebuff(){
  std::cout << "#### Test of class Debuff ####" << std::endl;
  Debuff* debuff = new Debuff(-1, -1);

  if (debuff->GetBlockMinus() < 0){
    delete debuff;
    throw "Debuff.BlockMinus should be > 0";
  }

  if (debuff->GetAttackMinus() < 0){
    delete debuff;
    throw "Debuff.AttackMinus should be > 0";
  }
  delete debuff;
  std::cout << "#### End test of class Debuff ####" << std::endl;
}

void testDeck(){
  std::cout << "#### Test of class Deck ####" << std::endl;
  Deck* deck = new Deck(1, 18);
  if (deck->GetSizeMax() < deck->GetSize()){
    delete deck;
    throw "Deck.sizeMax should be > to Deck.size";
  }
  delete deck;
  std::cout << "#### End test of class Deck ####" << std::endl;
}

void testDeckParts(){
  PlayerManager* PM = PlayerManager::instance();
  std::cout << "#### Test of class DeckParts ####" << std::endl;
  try{
    DeckParts* deckpart = new DeckParts((*PM)[0], true, true, true);
    delete deckpart;
    throw std::invalid_argument("no exception detected. Deckpart should be either hand, discardPile or drawPile");
  }
  catch(std::out_of_range){}
  catch(std::invalid_argument){
    std::cout << "no exception detected. Deckpart should be either hand, discardPile or drawPile"<<std::endl;
    throw "no exception detected. Deckpart should be either hand, discardPile or drawPile";
  }
  std::cout << "#### End test of class DeckParts ####" << std::endl;
}

void testEnemyRoom(){
  std::cout << "#### Test of class EnemyRoom ####" << std::endl;
  std::vector<std::unique_ptr<Enemy>> noEnemies;
  std::vector<std::unique_ptr<Enemy>> tooManyEnemies;

  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));
  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));
  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));
  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));

  try{
    delete new EnemyRoom(1, std::move(noEnemies));
    throw std::invalid_argument("No enemies in the room exception not detected");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "No enemies in the room exception not detected"<<std::endl;
    throw "No enemies in the room exception not detected";
  }

  try{
    delete new EnemyRoom(1, std::move(tooManyEnemies));
    throw std::invalid_argument("Too many enemies in the room exception not detected");
  } catch(std::out_of_range){}
  catch(std::invalid_argument){
    std::cout << "Too many enemies in the room exception not detected"<<std::endl;
    throw "Too many enemies in the room exception not detected";
  }
  std::cout << "#### End test of class EnemyRoom ####" << std::endl;
}

void testEnemySkill(){
  std::cout << "#### Test of class EnemySkill ####" << std::endl;
  EnemySkill* enemyskill1;
  EnemySkill* enemyskill2;
  try{
    enemyskill1 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),(std::string) "", -1, -1);
    throw std::invalid_argument("Invalid Target");
  } catch (std::out_of_range){
    enemyskill1 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),(std::string) "", -1, 2);
  } catch (std::invalid_argument){
    std::cout << "invalid_target_minus"<<std::endl;
    throw "Invalid target";
  }

  try{
    enemyskill2 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),(std::string) "", -1, 4);
    throw std::invalid_argument("Invalid Target");
  } catch (std::out_of_range){
    enemyskill2 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),(std::string) "", -1, 2);
  } catch (std::invalid_argument){
    std::cout << "invalid_target_plus"<<std::endl;
    throw "Invalid target";
  }

  if (enemyskill1->GetAttack() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Attack can not be <0"<<std::endl;
    throw "EnemySkill.Attack can not be <0";
  }

  if (enemyskill1->GetHeal() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Heal can not be <0"<<std::endl;
    throw "EnemySkill.Heal can not be <0";
  }

  if (enemyskill1->GetBlock() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Block can not be <0"<<std::endl;
    throw "EnemySkill.Block can not be <0";
  }

  if (enemyskill1->GetCooldown() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Cooldown can not be <0"<<std::endl;
    throw "EnemySkill.Cooldown can not be <0";
  }

  delete enemyskill1;
  delete enemyskill2;
  std::cout << "#### End Test of class EnemySkill ####" << std::endl;
}

void testEntity(){
  std::cout << "#### Test of class Entity ####" << std::endl;
  Entity* entity1;
  Entity* entity2 = new Entity((std::string) "entity1", 4, (std::string) "", -1, -1, true, -1, 1, 60);

  try {
    entity1 = new Entity((std::string) "entity1", -1, (std::string) "", -1, -1, true, -1, -1, 60);
    throw std::invalid_argument("id should not be negative");
  } catch (std::out_of_range){
    entity1 = new Entity((std::string) "entity1", -1, (std::string) "", -1, -1, true, -1, 1, 60);
  }
  catch(std::invalid_argument){
    std::cout << "Entity.id should not be negative" << std::endl;
    throw "Entity.id should not be negative";
  }

  if (entity1->GetElement() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.Element should be between 0 and 4";
  }

  if (entity2->GetElement() >4){
    delete entity1;
    delete entity2;
    throw "Entity.Element should be between 0 and 4";
  }

  if (entity1->GetStatAttack() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.StatAttack should be > 0";
  }

  if (entity1->GetStatBlock() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.StatBlock should be > 0";
  }

  if (entity1->GetLife() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.life should be > 0";
  }
  delete entity1;
  delete entity2;
  std::cout << "#### End test of class Entity ####" << std::endl;
}

void testFloor(){
  std::cout << "#### Test of class Floor ####" << std::endl;
  try{
    delete new Floor(-1, 1);
    throw std::invalid_argument("Floor.floorNumber should be between 0 and 3");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.floorNumber should be between 0 and 3" << std::endl;
    throw "Floor.floorNumber should be between 0 and 3";
  }

  try{
    delete new Floor(4, 1);
    throw std::invalid_argument("Floor.floorNumber should be between 0 and 3");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.floorNumber should be between 0 and 3" << std::endl;
    throw "Floor.floorNumber should be between 0 and 3";
  }

  try{
    delete new Floor(1, -1);
    throw std::invalid_argument("Floor.element should be between 0 and 4");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.element should be between 0 and 4" << std::endl;
    throw "Floor.element should be between 0 and 4";
  }

  try{
    delete new Floor(1, 5);
    throw std::invalid_argument("Floor.element should be between 0 and 4");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.element should be between 0 and 4" << std::endl;
    throw "Floor.element should be between 0 and 4";
  }
  std::cout << "#### End test of class Floor ####" << std::endl;
}

void testInfoPlayer(){
  std::cout << "#### Test of class InfoPlayer ####" << std::endl;

  try{
    delete new InfoPlayer(0, true);;
    throw std::invalid_argument("Element not valid");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument){
    throw "Element not valid";
  }

  try{
    delete new InfoPlayer(5, true);
    throw std::invalid_argument("Element not valid");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument){
    throw "Element not valid";
  }

  std::cout << "#### End test of class InfoPlayer ####" << std::endl;
}

void testMap(){
  std::cout << "#### Test of class Map ####" << std::endl;

  Map* map = new Map();
  try{
    map->SetCurrentFloor(-1);
    throw std::invalid_argument("Invalid value of floor");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument) {
    std::cout<<"Invalid value of floor <0" << std::endl;
    throw "Invalid value of floor";
  }

  try{
    map->SetCurrentFloor(4);
    throw std::invalid_argument("Invalid value of floor");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument) {
    std::cout<<"Invalid value of floor >3" << std::endl;
    throw "Invalid value of floor";
  }

  std::cout << "#### End test of class Map ####" << std::endl;
}

void testRoom(){
  std::cout << "#### Test of class Room ####" << std::endl;
  Room* room;

  try{
    delete new Room(0, true, true, true);
    throw std::invalid_argument("error: room is STR ant SR and ER");
  } catch (std::out_of_range) {
  } catch (std::invalid_argument) {
    throw "error: room is STR ant SR and ER";
  }

  room = new Room(-1, true, false, false);

  if (room->GetElement() < 0 or room->GetElement() > 4) {
    delete room;
    std::cout << room->GetElement()<<std::endl;
    throw "Element of Room not defined";
  }
  delete room;
  std::cout << "#### End test of class Room ####" << std::endl;
}

void testRules(){
  std::cout << "#### Test of class Rules ####" << std::endl;
  Rules* rules;
  std::vector<std::unique_ptr<InfoPlayer>> infos;
  infos.push_back(std::move(std::make_unique<InfoPlayer>()));

  try{
    delete new Rules(2, std::move(infos));
    throw std::invalid_argument("not enough rules");
  } catch (std::out_of_range){
  } catch (std::invalid_argument){
    throw "not enough rules";
  }
  infos.clear();
  infos.push_back(std::move(std::make_unique<InfoPlayer>()));
  rules = new Rules(-1, std::move(infos));
  if (rules->GetNbPlayers()< 1 || rules->GetNbPlayers()>2){
    throw "invalid Rules.nbPlayer";
  }
  delete rules;
  std::cout << "#### End test of class Rules ####" << std::endl;
}

void testSleepRoom(){
  std::cout << "#### Test of class SleepRoom ####" << std::endl;
  SleepRoom* sleeproom = new SleepRoom(0,-1);

  if (sleeproom->GetHeal() < 0){
    throw "Heal < 0";
  }
  delete sleeproom;
  std::cout << "#### End test of class SleepRoom ####" << std::endl;
}


void testSpecialTrainingRoom(){
  std::cout << "#### Test of class SpecialTrainingRoom ####" << std::endl;
  std::vector<Card*> cardreward;

  try{
    delete new SpecialTrainingRoom(1, cardreward);
    throw std::invalid_argument("The reward should be 3 cards");
  } catch (std::out_of_range){
  } catch (std::invalid_argument){
    throw "The reward should be 3 cards";
  }
  std::cout << "#### End test of class SpecialTrainingRoom ####" << std::endl;
}

void testState(){
  testBuff();
  testCard();
  testDebuff();
  testDeck();
  testDeckParts();
  testEnemyRoom();
  testEnemySkill();
  testEntity();
  testFloor();
  testInfoPlayer();
  testMap();
  testRoom();
  testRules();
  testSleepRoom();
  testSpecialTrainingRoom();

}

int main(int argc,char* argv[])
{
    SkillManager::instance();
    CardManager::instance();
    PlayerManager::instance();
    //Exemple exemple;
    //exemple.setX(53);

    if (argc == 2 and std::string(argv[1]) == "hello"){
        cout << "Bonjour le monde !" << endl;
    }

    if (argc == 2 and std::string(argv[1]) == "state"){
        testState();
    }


    if (argc == 2 and std::string(argv[1] )== "render"){
      testSFML();
    }
    if (argc == 2 and std::string(argv[1] )== "render2"){
      testSFML2();
    }

    delete SkillManager::instance();
    delete CardManager::instance();
    delete PlayerManager::instance();
    return 0;
}
