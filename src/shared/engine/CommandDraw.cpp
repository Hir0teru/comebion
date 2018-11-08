#include "CommandDraw.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandDraw::CommandDraw (int entityID): entityID(entityID){}

CommandDraw::CommandDraw (){}

void CommandDraw::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Draw card for player "<<entityID<<endl;
  if (entityID > 0 && entityID < 2){
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();

    std::vector<DeckParts*> hands = room->GetHands();
    std::vector<DeckParts*> drawPiles = room->GetDrawPiles();

    std::vector<Card*> handCards = hands[entityID]->GetCards();
    std::vector<Card*> drawPileCards = drawPiles[entityID]->GetCards();

    handCards.push_back(drawPileCards.back());
    drawPileCards.pop_back();

    hands[entityID]->SetCards(handCards);
    drawPiles[entityID]->SetCards(drawPileCards);

    room->SetHands(hands);
    room->SetDrawPiles(drawPiles);
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
  drawPiles[entityID]->SetCards(drawPileCards);

  room->SetHands(hands);
  room->SetDrawPiles(drawPiles);
}
