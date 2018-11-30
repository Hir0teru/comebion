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
      int min = 0;
      for(auto card : cards){
        int score = card -> GetAttack() + card -> GetBlock() + 8 * card -> GetBuff() -> GetEvade() + 4 * card -> GetBuff() -> GetEvade()
      }
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
