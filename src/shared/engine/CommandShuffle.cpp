#include <algorithm>

#include "CommandShuffle.h"
#include "state/Card.h"
#include "state/DeckParts.h"
#include <iostream>

using namespace engine;
using namespace std;

CommandShuffle::CommandShuffle (){
  playerID = 0;
}
CommandShuffle::CommandShuffle (int playerID){
  if(playerID >=0 && playerID < 2){
    this->playerID = playerID;
  }
}
void CommandShuffle::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Shuffle DrawPile of player "<<playerID<<endl;
  if(playerID >=0 && playerID < 2){
    int floorNb =  gameState->GetMap()->GetCurrentFloor();
    std::vector<state::Card*> drawPile =  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetDrawPiles()[playerID]->GetCards();
    std::vector<state::Card*> discardPile =  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetDiscardPiles()[playerID]->GetCards();
    drawPile.insert(drawPile.end(), discardPile.begin(), discardPile.end());
    std::random_shuffle(drawPile.begin(), drawPile.end());
    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetDrawPiles()[playerID]->SetCards(drawPile);
    discardPile.clear();
    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetDiscardPiles()[playerID]->SetCards(discardPile);
  }
}

void CommandShuffle::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Shuffle DrawPile of player "<<playerID<<endl;
}

json_map CommandShuffle::Serialize () {
  json_map val;
  return val;
}
 CommandShuffle* CommandShuffle::Deserialize (json_map in){
  return this;
}
