#include <iostream>
#include <string>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

void testBuff(){
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
}

void testCard(){
  Card* card1 = new Card((std::string) "test", -1, -1,(std::string) "", -1, -1, -1, -1, -1, -1, new Debuff(), new Buff());
  Card* card2 = new Card((std::string)"test", -1, 4,(std::string) "", 5, -1, -1, -1, -1, -1, new Debuff(), new Buff());
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
}

void testDebuff(){
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
}

void testDeck(){
  Deck* deck = new Deck(1, 18);
  if (deck->GetSizeMax() < deck->GetSize()){
    delete deck;
    throw "Deck.sizeMax should be > to Deck.size";
  }
  delete deck;
}

void testDeckParts(){
  try{
    DeckParts* deckpart = new DeckParts((std::shared_ptr<Player>) new Player(), true, true, true);
    delete deckpart;
    throw "no exception detected. Deckpart should be either hand, discardPile or drawPile";
  }
  catch(std::invalid_argument){}
}

void testEnemyRoom(){
  std::vector<std::shared_ptr<Enemy>> noEnemies;
  std::vector<std::shared_ptr<Enemy>> tooManyEnemies;

  tooManyEnemies.push_back((std::shared_ptr<Enemy>) new Enemy());
  tooManyEnemies.push_back((std::shared_ptr<Enemy>) new Enemy());
  tooManyEnemies.push_back((std::shared_ptr<Enemy>) new Enemy());
  tooManyEnemies.push_back((std::shared_ptr<Enemy>) new Enemy());

  try{
    delete new EnemyRoom(1, noEnemies);
    throw "No enemies in the room exception not detected";
  } catch (std::invalid_argument) {}

  try{
    delete new EnemyRoom(1, tooManyEnemies);
    throw "Too many enemies in the room exception not detected";
  } catch(std::invalid_argument){}
}

void testEnemySkill(){
  try{
    EnemySkill* enemyskill1 = new EnemySkill(-1, -1, -1, new Buff(), new Debuff(),(std::string) "", -1, -1);
  }
  EnemySkill* enemyskill1 = new EnemySkill(-1, -1, -1, new Buff(), new Debuff(),(std::string) "", -1, -1);
  EnemySkill* enemyskill2 = new EnemySkill(-1, -1, -1, new Buff(), new Debuff(),(std::string) "", -1, 4);

  if (enemyskill1->GetAttack() < 0){
    delete enemyskill1;
    delete enemyskill2;
    throw "EnemySkill.Attack can not be <0";
  }

  if (enemyskill1->GetHeal() < 0){
    delete enemyskill1;
    delete enemyskill2;
    throw "EnemySkill.Heal can not be <0";
  }

  if (enemyskill1->GetBlock() < 0){
    delete enemyskill1;
    delete enemyskill2;
    throw "EnemySkill.Block can not be <0";
  }

  if (enemyskill1->GetCooldown() < 0){
    delete enemyskill1;
    delete enemyskill2;
    throw "EnemySkill.Cooldown can not be <0";
  }

  delete enemyskill1;
  delete enemyskill2;
}

void testState(){
  testBuff();
  testCard();
  testDebuff();
  testDeck();
  testDeckParts();
  //no test for enemy
  testEnemyRoom();
  testEnemySkill();

}

int main(int argc,char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);

    if (argc == 2 and std::string(argv[1]) == "hello"){
        cout << "Bonjour le monde !" << endl;
    }

    if (argc == 2 and std::string(argv[1]) == "state"){
        testState();
    }

    return 0;
}
