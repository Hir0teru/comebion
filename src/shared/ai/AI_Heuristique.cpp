#include "AI_Heuristique.h"
#include "engine.h"
#include "state.h"
#include <iostream>

using namespace ai;
using namespace state;
using namespace engine;


AI_Heuristique::AI_Heuristique (){}
AI_Heuristique::AI_Heuristique (std::shared_ptr<state::GameState> gameState, std::shared_ptr<engine::Moteur> moteur, int entityID){
  this->gameState = gameState;
  this->moteur = moteur;
  if(entityID >=0 && entityID < 2){
    this->entityID = entityID;
  } else entityID = 0;
}


void AI_Heuristique::Play (){
  int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
  if(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom() -> GetEntityTurn() == entityID){
    std::cout << "thinking ..." << std::endl;
    if (gameState->GetRules()->GetIsGameLost()){
      std::cout << "you're dead, deal with it" << std::endl;
    } else if (!gameState->GetIsInsideRoom()){
      moteur -> AddCommand(std::make_shared<engine::CommandEnterRoom>());
    } else {
      int floorNb = gameState->GetMap()->GetCurrentFloor();
      std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
      Player* player = gameState->GetPlayers()[entityID];

      if (room->GetIsSleepRoom()){
        if (player->GetLife() < player->GetMaxLife()/2){
          moteur -> AddCommand(std::make_shared<engine::CommandHeal>(room->GetHeal(), entityID));
        } else {
          moteur -> AddCommand(std::make_shared<engine::CommandChangeStat>(entityID, gameState->GetPlayers()[entityID]->GetStatAttack() + 2,gameState->GetPlayers()[entityID]->GetStatBlock() + 2));
        }
        moteur -> AddCommand(std::make_shared<engine::CommandExitRoom>());
      } else if (room->GetIsSpecialTrainingRoom()) {
        std::vector<int> count = player->GetDeck()->CountCards();
        std::vector<int> attack, block, buff, debuff;

        for (int i = 0; i < (int) room->GetReward().size(); i++ ){
          if (room->GetReward()[i]->GetAttack() > 0) attack.push_back(i);
          if (room->GetReward()[i]->GetBlock() > 0) block.push_back(i);
          if (room->GetReward()[i]->GetDebuff() > 0) attack.push_back(i);
          if (room->GetReward()[i]->GetBuff() > 0) block.push_back(i);
        }

        if (count[0] < count[1] && attack.size() > 0){
          moteur -> AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[rand() % (int) attack.size()], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        } else if ((count[0] > count[1] && block.size()) > 0){
          moteur -> AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[rand() % (int) block.size()], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        } else {
          moteur -> AddCommand(std::make_shared<engine::CommandAddCard>(entityID, rand() % (int) room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        }

        // if (entityID == 1 {
        //   moteur -> AddCommand(std::make_shared<engine::CommandExitRoom>());
        // } else {
        //   moteur -> AddCommand(std::make_shared<engine::CommandNextEntity>());
        // }


      } else { //enemyroom
        if (!gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon()){ // keep fighting
          std::cout << "in process..." <<std::endl;

          DeckParts* hand = room->GetHands()[entityID];
          std::vector<Card*> cards = hand -> GetCards();

          // can we still play cards?
          int playable_card_exists = -1;
          for(int i = 0; i< (int) cards.size(); ++i){
            if (cards[i] -> GetCost() <= gameState -> GetPlayers()[entityID] -> GetEnergy()){
              playable_card_exists = i;
              break;
            }
            i++;
          }
          if(playable_card_exists >= 0){

            // for max attack
            // target = 0

            int cards_played[5]; // for the function max_attack and max_block
            int cards_index[5];  //index of the cards -> used if multiple cards are played with no update from the motor
            for(int i = 0; i< 5; i++){
              std::cout << i << std::endl;
              cards_played[i] = 0;
              cards_index[i] = i;
            }

            int block_aim = 0;
            std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom() -> GetEnemies();
            for(auto& enemy : enemies){
              int attack = enemy -> GetSkills()[enemy -> GetIntent()] ->  GetAttack();
              if(attack > 0){
                block_aim+= attack;
              }
            }
            int try_block = 0;
            int max = 0;
            if(block_aim > gameState -> GetPlayers()[entityID] -> GetBlock()){
              try_block = Try_block(cards, cards_played, gameState -> GetPlayers()[entityID] -> GetEnergy(), 0, -1,0, block_aim);
              std::cout << "try block: " << try_block << std::endl;

            }
            if(try_block == 0){
              max =  Max_attack( cards,  cards_played, gameState -> GetPlayers()[entityID] -> GetEnergy(), 0, -1,0);
              std::cout << "max attack: " << max << std::endl;
            }

            if(max > 0){
              for(int i = 0; i < 5; i++){
                std::cout << cards_played[i] << std::endl;
                if(cards_played[i] > 0){
                  std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                  moteur -> AddCommand(std::make_shared<CommandPlayCard>(entityID, 2, cards_index[i]));
                  for(int j = i+1 ; j<  (int) cards.size(); j++){
                    cards_index[j] = cards_index[j] - 1;
                  }
                }
              }
            } else if(try_block > 0){
              for(int i = 0; i < 5; i++){
                std::cout << cards_played[i] << std::endl;
                if(cards_played[i] > 0){
                  std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                  moteur -> AddCommand(std::make_shared<CommandPlayCard>(entityID, entityID, cards_index[i]));
                  for(int j = i+1 ; j<  (int) cards.size(); j++){
                    cards_index[j] = cards_index[j] - 1;
                  }
                }
              }
            } else if(cards[playable_card_exists] -> GetTarget() == 0 || cards[playable_card_exists] -> GetTarget() == 3){
                  moteur -> AddCommand(std::make_shared<CommandPlayCard>(entityID, 0, playable_card_exists));
                } else moteur -> AddCommand(std::make_shared<CommandPlayCard>(entityID, 2, playable_card_exists));
              } else{
            std::cout << "next turn" << std::endl;
            moteur -> AddCommand(std::make_shared<engine::CommandNextEntity>());

          }
        } else { //fight won

          std::vector<int> count = player->GetDeck()->CountCards();
          std::vector<int> attack, block, buff, debuff;

          for (int i = 0; i < (int) room->GetReward().size(); i++ ){
            if (room->GetReward()[i]->GetAttack() > 0) attack.push_back(i);
            if (room->GetReward()[i]->GetBlock() > 0) block.push_back(i);
            if (room->GetReward()[i]->GetDebuff() > 0) attack.push_back(i);
            if (room->GetReward()[i]->GetBuff() > 0) block.push_back(i);
          }

          if (count[0] < count[1] && attack.size() > 0){
            moteur -> AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          } else if (count[0] > count[1] && block.size() > 0){
            moteur -> AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          } else {
            moteur -> AddCommand(std::make_shared<engine::CommandAddCard>(entityID, rand() % (int) room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          }

          // if (entityID == 1) {
          //   moteur -> AddCommand(std::make_shared<engine::CommandExitRoom>());
          // } else {
          //   moteur -> AddCommand(std::make_shared<engine::CommandNextEntity>());
          // }

        }
      }


    }

    //
    // int index = rand() % (int) commands.size();
    // std::shared_ptr<Command> command_chosen = commands[index];
    // moteur->AddCommand(command_chosen);

    if ((entityID == (int) gameState -> GetPlayers().size() -1) &&
        (gameState->GetIsInsideRoom() && (( gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsSleepRoom() ||
        gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom()) ||
        (gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
        gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsFightWon())))){
          moteur -> AddCommand(std::make_shared<CommandExitRoom>());
    } else if (gameState->GetIsInsideRoom() && (( gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsSleepRoom() ||
               gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom()) ||
               (gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
               gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsFightWon()))){
                  moteur -> AddCommand(std::make_shared<CommandNextEntity>());
    }
  }
}

std::shared_ptr<engine::Moteur>& AI_Heuristique::GetMoteur(){
  return moteur;
}

int AI_Heuristique::Max_attack(std::vector<state::Card*> cards, int * cards_played, int energy_left, int max, int index, int nb_card_played){
  if(index >= (int) cards.size() - 1 ) return max;
  int newmax = max;
  for(int i = index + 1; i< (int) cards.size(); i++){
    if(cards_played[i] == 0 && cards[i] -> GetCost() <= energy_left && cards[i] -> GetAttack() > 0 ){


      int cards_played_cpy[5];
      for(int j = 0; j < 5; j++){
        cards_played_cpy[j] = cards_played[j];
      }

      cards_played_cpy[i] = nb_card_played + 1;
      // calcule le max en jouant la carte i
      newmax =  Max_attack(cards, cards_played_cpy, energy_left - cards[i] -> GetCost(), max  + cards[i] -> GetAttack(), i, nb_card_played + 1);
    //  cards_played[i] = 0;
    // calcule le max en ne jouant pas la carte i
      max = Max_attack(cards, cards_played, energy_left, max, i, nb_card_played);

      if(newmax > max){
        max = newmax;
        //cards_played[i] = nb_card_played + 1;
        // si le max en jouant la carte est plus grand que sans la jouer:
        for(int j = 0; j < 5; j++){
          cards_played[j] = cards_played_cpy[j];
        }
        return(max);
      } else {
        for(int j = 0; j < 5; j++){
          cards_played_cpy[j] = cards_played[j];
        }
      }
    }
  }
  return max;
}

int AI_Heuristique::Try_block(std::vector<state::Card*> cards, int * cards_played, int energy_left, int block, int index, int nb_card_played, int block_aim){
  if(index >= (int) cards.size() - 1  || block >= block_aim) return block;
  int newblock = block;
  for(int i = index + 1; i< (int) cards.size(); i++){
    if(cards_played[i] == 0 && cards[i] -> GetCost() <= energy_left && cards[i] -> GetBlock() > 0 && i != index){

      int cards_played_cpy[5];
      for(int j = 0; j < 5; j++){
        cards_played_cpy[j] = cards_played[j];
      }

      cards_played_cpy[i] = nb_card_played + 1;
      newblock = Try_block(cards, cards_played_cpy, energy_left - cards[i] -> GetCost(), block  + cards[i] -> GetBlock(), i, nb_card_played + 1, block_aim);
      block = Try_block(cards, cards_played, energy_left, block, i, nb_card_played, block_aim);

      if(newblock > block){
        block = newblock;
        //cards_played[i] = nb_card_played + 1;
        for(int j = 0; j < 5; j++){
          cards_played[j] = cards_played_cpy[j];
        }
        return(block);
      }
    }
  }
  return block;
}
