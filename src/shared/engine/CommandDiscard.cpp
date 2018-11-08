#include "CommandDiscard.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandDiscard::CommandDiscard (int entityID, int cardID): entityID(entityID), cardID(cardID){}

CommandDiscard::CommandDiscard (){}

void CommandDiscard::Execute (std::shared_ptr<state::GameState>& gameState){
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  state::EnemyRoom* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();

  std::vector<DeckParts*> hands = room->GetHands()
  std::vector<DeckParts*> discardPiles = room->GetDiscardPiles()

  DeckParts* hand = hands[entityId];
  DeckParts* discardPile = discardPiles[entityId];

  discardPile.push_back(hand[cardID]);
  hand.erase(hand.begin() + cardID);

  hands[entityId] = hand;
  discardPiles[entityId] = discardPile;

  room->SetHands(hands);
  room->SetDiscardPiles(DiscardPiles);
}

void CommandDiscard::Undo (std::shared_ptr<state::GameState>& gameState){
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  EnemyRoom* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();

  std::vector<DeckParts*> hands = room->GetHands()
  std::vector<DeckParts*> discardPiles = room->GetDiscardPiles()

  DeckParts* hand = hands[entityId];
  DeckParts* discardPile = discardPiles[entityId];

  hand.push_back(discardPile.back());
  discardPile.pop_back();

  hands[entityId] = hand;
  discardPiles[entityId] = discardPile;

  room->SetHands(hands);
  room->SetDiscardPiles(DiscardPiles);
}
