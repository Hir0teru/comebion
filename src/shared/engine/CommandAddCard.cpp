#include "CommandAddCard.h"
#include "CommandRemoveCard.h"
#include "state/PlayerManager.h"
#include "state/CardManager.h"
#include <iostream>
#include <limits>

using namespace state;
using namespace engine;
using namespace std;

CommandAddCard::CommandAddCard (int playerID, int card, bool isDeckFull): playerID(playerID), card(card), isDeckFull(isDeckFull){}

CommandAddCard::CommandAddCard (){}

void CommandAddCard::Execute (std::shared_ptr<state::GameState>& gameState){

  if (playerID >= 0 && playerID < 2 && card >=0 && card < 3){
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
    std::vector<Card*> cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
    if (isDeckFull){
      // int index = rand() % 15;
      int index = 0;
      int i = 0;
      int min = std::numeric_limits<int>::max() ;
      for(auto card : cards){
        int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                    card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                    card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                    - 2 * card -> GetCost();
        if(card -> GetTarget() >=2) score +=5;
        if (min > score){
          min = score;
          index = i;
        } else if(min == score && rand() % 2 < 1){
          min = score;
          index = i;
        }
        i++;
      }
      CommandRemoveCard command(playerID, index);
      command.Execute(gameState);
      std::cout << "score was : " << min << std::endl;
      cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
    }
    cout<<"Add card number "<<card<<" to player "<<playerID<<"'s deck: " << room->GetReward()[card] -> GetName()<<endl;
    cards.push_back(room->GetReward()[card]);
    gameState->GetPlayers()[playerID]->GetDeck()->SetCards(cards);
  }
}

void CommandAddCard::Undo (std::shared_ptr<state::GameState>& gameState){
  if (playerID >= 0 && playerID < 2 ){
    cout<<"Undo Adding card number "<<card<<" to player "<<playerID<<"'s deck"<<endl;
    std::vector<Card*> cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
    cards.pop_back();
    gameState->GetPlayers()[playerID]->GetDeck()->SetCards(cards);
  }
}

json_map CommandAddCard::Serialize () {
  json_map val;
  val["typeCmd"] ="AddCard";
  val["playerID"] = playerID;
  val["card"] = card;
  val["isDeckFull"] = isDeckFull;
  return val;
}
 CommandAddCard* CommandAddCard::Deserialize (json_map in){
   playerID = in["playerID"].as<json_int>();
   card = in["card"].as<json_int>();
   // isDeckFull = in["isDeckFull"].as<json_value::type::boolean>();
  return this;
}
