#include "CommandDiscard.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandDiscard::CommandDiscard (int entityID, int cardID): entityID(entityID), cardID(cardID){}

CommandDiscard::CommandDiscard (){}

void CommandDiscard::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Discard card number "<<cardID<<" from player "<<entityID<<endl;
  if (entityID >= 0 && entityID < 2){
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();

    std::vector<DeckParts*> hands = room->GetHands();
    std::vector<DeckParts*> discardPiles = room->GetDiscardPiles();

    std::vector<Card*> handCards = hands[entityID]->GetCards();
    std::vector<Card*> discardPileCards = discardPiles[entityID]->GetCards();

    discardPileCards.push_back(handCards[cardID]);
    handCards.erase(handCards.begin() + cardID);

    hands[entityID]->SetCards(handCards);
    hands[entityID]->SetSize(handCards.size());
    discardPiles[entityID]->SetCards(discardPileCards);
    discardPiles[entityID]->SetSize(discardPileCards.size());

    room->SetHands(hands);
    room->SetDiscardPiles(discardPiles);
  }
}

void CommandDiscard::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Discard card number "<<cardID<<" from player "<<entityID<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();

  std::vector<DeckParts*> hands = room->GetHands();
  std::vector<DeckParts*> discardPiles = room->GetDiscardPiles();

  std::vector<Card*> handCards = hands[entityID]->GetCards();
  std::vector<Card*> discardPileCards = discardPiles[entityID]->GetCards();

  handCards.push_back(discardPileCards.back());
  discardPileCards.pop_back();

  hands[entityID]->SetCards(handCards);
  hands[entityID]->SetSize(handCards.size());
  discardPiles[entityID]->SetCards(discardPileCards);
  discardPiles[entityID]->SetSize(discardPileCards.size());

  room->SetHands(hands);
  room->SetDiscardPiles(discardPiles);
}
