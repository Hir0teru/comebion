#include "CommandAddCard.h"
#include "CommandRemoveCard.h"
#include "state/PlayerManager.h"
#include "state/CardManager.h"
#include <tgmath.h>
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
      int index = rand() % 15;
      // int index = 0;
      // int min = 0;
      // for(auto card : cards){
      //   int score = card -> GetAttack() * 1.5 + card -> GetBlock() + pow( card -> GetHeal(), 2)+ pow(card -> GetBuff() -> GetEvade(), 4) +
      //   pow(card -> GetBuff() -> GetHeal(), 2) + pow(card -> GetBuff() ->GetRetaliate() , 3) + pow(card -> GetBuff() ->GetAttackPlus(), 3) +
      //   pow(card -> GetBuff() ->GetBlockPlus(), 3) ,
      // }
      CommandRemoveCard command(playerID, index);
      command.Execute(gameState);
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
