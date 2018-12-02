#include "CommandAddCard.h"
#include "CommandRemoveCard.h"
#include "state/PlayerManager.h"
#include "state/CardManager.h"
#include <iostream>

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
      int min = 0;
      for(auto card : cards){
        int score = card -> GetAttack() + card -> GetBlock() + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 4 +
                    card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                    card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2 +
                    (card -> GetTarget() >= 2) * 5 - 3 * card -> GetCost();
        if (min > score){
          min = score;
          index = i;
        }
        i++;
      }
      CommandRemoveCard command(playerID, index);
      command.Execute(gameState);
      cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
    }
    cout<<"Add card number "<<card<<" to player "<<playerID<<"'s deck"<<endl;
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
