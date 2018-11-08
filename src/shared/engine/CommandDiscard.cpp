#include "CommandDiscard.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandDiscard::CommandDiscard (int entityID, int cardID): entityID(entityID), cardID(cardID){}

CommandDiscard::CommandDiscard (){}

void CommandDiscard::Execute (std::shared_ptr<state::GameState>& gameState){
  // int floorNb = gameState->GetMap()->GetCurrentFloor();
  // EnemyRoom* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
  //
  // DeckParts* hand = room->GetHands()[entityId];
  // DeckParts* discardPile = room->GetDiscardPiles()[entityId];
  //
  // discardPile.push_back(hand[cardID]);
  // hand.erase(hand.begin() + cardID);
  //
  // room->setHands
}

void CommandDiscard::Undo (std::shared_ptr<state::GameState>& gameState){
  // int floorNb = gameState->GetMap()->GetCurrentFloor();
  // EnemyRoom* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
  //
  // DeckParts* hand = room->GetHands()[entityId];
  // DeckParts* discardPile = room->GetDiscardPiles()[entityId];
  //
  // hand.push_back
}
