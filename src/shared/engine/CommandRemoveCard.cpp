#include "CommandRemoveCard.h"
#include "state/Card.h"
#include <iostream>

using namespace engine;
using namespace std;

CommandRemoveCard::CommandRemoveCard (){
  playerID = 0;
  index = 0;
}
CommandRemoveCard::CommandRemoveCard (int playerID, int index){
  if (playerID >= 0 && playerID < 2){
    this->playerID = playerID;
  } else this->playerID = 0;
  if (index >= 0 && index < 15){
    this->index = index;
  } else this->index = 0;
}
void CommandRemoveCard::Execute (std::shared_ptr<state::GameState>& gameState){
  std::vector<state::Card*> cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
  cout<<"Remove card "<<cards[index]->GetName()<<" from player "<<playerID<<endl;
  cards.erase(cards.begin() + index);
  gameState->GetPlayers()[playerID]->GetDeck()->SetCards(cards);
}

void CommandRemoveCard::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Remove card "<<index<<" from player "<<playerID<<endl;
}

Json::Value CommandRemoveCard::Serialize () {
  Json::Value val;
  return val;
}
 CommandRemoveCard* CommandRemoveCard::Deserialize (Json::Value in){
  return this;
}
