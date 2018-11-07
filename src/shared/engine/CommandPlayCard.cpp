#include "CommandPlayCard.h"
#include "state/DeckParts.h"

using namespace engine;


CommandPlayCard::CommandPlayCard (){
  entityID = 0;
  cardIndex = 0;
}
CommandPlayCard::CommandPlayCard (int entityID, int cardIndex){
  if(entityID >=0 && entityID < 2){
    this -> entityID = entityID;
  } else this -> entityID = 0;
  if(cardIndex >= 0 && cardIndex < 7){
    this -> cardIndex = cardIndex;
  } else this -> cardIndex = 0;
}

void CommandPlayCard::Execute (std::shared_ptr<state::GameState>& gameState){
  int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
  std::vector<state::Card*> hand =  gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetHands()[entityID] -> GetCards() ;
  int sizeHand = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetHands()[entityID] -> GetSize();
  if(sizeHand> cardIndex){
    std::vector<state::Card*> discardPile =  gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetDiscardPiles()[entityID]  -> GetCards();
    int sizeDiscard = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetDiscardPiles()[entityID]  -> GetSize();
    discardPile[sizeDiscard] = hand[cardIndex];
    for(int i = cardIndex; i < sizeHand - 1; i++){
      hand[i] = hand[i + 1];
    }
    hand[sizeHand -1] = nullptr;
    gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetDiscardPiles()[entityID] -> SetCards(discardPile);
    gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetHands()[entityID] -> SetCards(hand);
    gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetDiscardPiles()[entityID]  -> SetSize(sizeDiscard + 1);
    gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetHands()[entityID] -> SetSize(sizeHand - 1);
  }
}
void CommandPlayCard::Undo (std::shared_ptr<state::GameState>& gameState){}
