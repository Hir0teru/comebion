#include "CommandDraw.h"
#include "state/PlayerManager.h"
#include "CommandShuffle.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandDraw::CommandDraw (int entityID): entityID(entityID){}

CommandDraw::CommandDraw (){}

void CommandDraw::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Draw card for player "<<entityID<<endl;
  if (entityID >= 0 && entityID < 2){
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::shared_ptr<Room>& room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
    std::vector<DeckParts*> hands = room->GetHands();
    std::vector<DeckParts*> drawPiles = room->GetDrawPiles();

    std::vector<Card*> handCards = hands[entityID]->GetCards();
    std::vector<Card*> drawPileCards = drawPiles[entityID]->GetCards();
    if((int) drawPileCards.size() <=0){
      CommandShuffle command(entityID);
      command.Execute(gameState);
    }
    hands = room->GetHands();
    drawPiles = room->GetDrawPiles();

    handCards = hands[entityID]->GetCards();
    drawPileCards = drawPiles[entityID]->GetCards();
    if (hands[entityID] -> GetSize() < 7){
    handCards.push_back(drawPileCards[drawPiles[entityID] -> GetSize() - 1]);
    drawPileCards.erase(drawPileCards.begin() + drawPiles[entityID] -> GetSize() - 1);

    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom() -> GetHands()[entityID]->SetCards(handCards);
    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom() -> GetDrawPiles()[entityID]->SetCards(drawPileCards);
  }
    // room->SetHands(hands);
    // room->SetDrawPiles(drawPiles);
    // gameState->GetMap()->GetFloors()[floorNb] -> SetCurrentRoom(room);
  }
}

void CommandDraw::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Draw card for player "<<entityID<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();

  std::vector<DeckParts*> hands = room->GetHands();
  std::vector<DeckParts*> drawPiles = room->GetDrawPiles();

  std::vector<Card*> handCards = hands[entityID]->GetCards();
  std::vector<Card*> drawPileCards = drawPiles[entityID]->GetCards();

  drawPileCards.push_back(handCards.back());
  handCards.pop_back();

  hands[entityID]->SetCards(handCards);
  hands[entityID]->SetSize(handCards.size());
  drawPiles[entityID]->SetCards(drawPileCards);
  drawPiles[entityID]->SetSize(drawPileCards.size());


  room->SetHands(hands);
  room->SetDrawPiles(drawPiles);
}

json_map CommandDraw::Serialize () {
  json_map val;
  return val;
}
 CommandDraw* CommandDraw::Deserialize (json_map in){
  return this;
}
