#include "CommandAddCard.h"
#include "state/PlayerManager.h"
#include "state/CardManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandAddCard::CommandAddCard (int playerID, int card, bool isDeckFull): playerID(playerID), card(card), isDeckFull(isDeckFull){}

CommandAddCard::CommandAddCard (){}

void CommandAddCard::Execute (std::shared_ptr<state::GameState>& gameState){
  CardManager* CM = CardManager::instance();
  std::vector<Card*> cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
  cards.push_back((*CM)[card]);
  gameState->GetPlayers()[playerID]->GetDeck()->SetCards(cards);
}

void CommandAddCard::Undo (std::shared_ptr<state::GameState>& gameState){
  std::vector<Card*> cards = gameState->GetPlayers()[playerID]->GetDeck()->GetCards();
  cards.pop_back();
  gameState->GetPlayers()[playerID]->GetDeck()->SetCards(cards);
}
