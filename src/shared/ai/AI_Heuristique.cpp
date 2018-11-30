#include "AI_Heuristique.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <math.h>

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
  int floorNb =  gameState->GetMap()->GetCurrentFloor();
  if(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn() == entityID){
    std::cout << "thinking ..." << std::endl;
    if (gameState->GetRules()->GetIsGameLost()){
      std::cout << "you're dead, deal with it" << std::endl;
    } else if (!gameState->GetIsInsideRoom()){
      moteur->AddCommand(std::make_shared<engine::CommandEnterRoom>());
    } else {
      int floorNb = gameState->GetMap()->GetCurrentFloor();
      std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
      Player* player = gameState->GetPlayers()[entityID];

      if (room->GetIsSleepRoom()){
        if (player->GetLife() < player->GetMaxLife()/2){
          moteur->AddCommand(std::make_shared<engine::CommandHeal>(room->GetHeal(), entityID));
        } else {
          moteur->AddCommand(std::make_shared<engine::CommandChangeStat>(entityID, gameState->GetPlayers()[entityID]->GetStatAttack() + 2,gameState->GetPlayers()[entityID]->GetStatBlock() + 2));
        }
        moteur->AddCommand(std::make_shared<engine::CommandExitRoom>());
      } else if (room->GetIsSpecialTrainingRoom()) {
        std::vector<int> count = player->GetDeck()->CountCards();
        std::vector<int> attack, block, buff, debuff;

        for (int i = 0; i < (int) room->GetReward().size(); i++ ){
          if (room->GetReward()[i]->GetAttack() > 0) attack.push_back(i);
          if (room->GetReward()[i]->GetBlock() > 0) block.push_back(i);
          if ((room->GetReward()[i]->GetDebuff()->GetAttackMinus() > 0) || (room->GetReward()[i]->GetDebuff()->GetBlockMinus() > 0)) attack.push_back(i);
          if ((room->GetReward()[i]->GetBuff()->GetAttackPlus() > 0) || (room->GetReward()[i]->GetBuff()->GetBlockPlus() > 0)
              || (room->GetReward()[i]->GetBuff()->GetEvade() > 0) || (room->GetReward()[i]->GetBuff()->GetHeal() > 0)
              || (room->GetReward()[i]->GetBuff()->GetRetaliate() > 0)) block.push_back(i);
        }

        if (count[0] < count[1] && attack.size() > 0){
          moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[rand() % (int) attack.size()], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        } else if ((count[0] > count[1] && block.size()) > 0){
          moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[rand() % (int) block.size()], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        } else {
          moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, rand() % (int) room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        }

        // if (entityID == 1 {
        //   moteur->AddCommand(std::make_shared<engine::CommandExitRoom>());
        // } else {
        //   moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());
        // }


      } else { //enemyroom
        if (!gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon()){ // keep fighting

          DeckParts* hand = room->GetHands()[entityID];
          std::vector<Card*> cards = hand->GetCards();

          // can we still play cards?
          int playable_card_exists = -1;
          for(int i = 0; i< (int) cards.size(); ++i){
            if (cards[i]->GetCost() <= gameState->GetPlayers()[entityID]->GetEnergy()){
              playable_card_exists = i;
              break;
            }
            i++;
          }
          if(playable_card_exists >= 0){

            // for max attack
            // target = 0

            int cards_played[5]; // for the function max_attack and max_block
            int cards_index[5];  //index of the cards->used if multiple cards are played with no update from the motor
            for(int i = 0; i< 5; i++){
              // std::cout << i << std::endl;
              cards_played[i] = 0;
              cards_index[i] = i;
            }

            int block_aim = 0;
            std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
            for(auto& enemy : enemies){
              int attack = enemy->GetSkills()[enemy->GetIntent()]->GetAttack();
              if(attack > 0){
                block_aim+= attack;
              }
            }
            int try_block = 0;
            int max = 0;
            if(block_aim > gameState->GetPlayers()[entityID]->GetBlock()){
              try_block = Try_block(cards, cards_played, gameState->GetPlayers()[entityID]->GetEnergy(), 0, -1,0, block_aim);
              std::cout << "try block: " << try_block << std::endl;

            }
            if(try_block == 0){
              max =  Max_attack_ite( cards,  cards_played, gameState->GetPlayers()[entityID]->GetEnergy(), room->GetEnemies()[2]->GetBlock(), room->GetEnemies()[2]->GetLife());
              std::cout << "max attack: " << max << std::endl;
            }

            if(max > 0){
              for(int i = 0; i < 5; i++){
                std::cout << cards_played[i] << std::endl;
                if(cards_played[i] > 0){
                  std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                  moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 2, cards_index[i]));
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
                  moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, entityID, cards_index[i]));
                  for(int j = i+1 ; j<  (int) cards.size(); j++){
                    cards_index[j] = cards_index[j] - 1;
                  }
                }
              }
            } else if(cards[playable_card_exists]->GetTarget() == 0 || cards[playable_card_exists]->GetTarget() == 3){
                  moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 0, playable_card_exists));
                } else moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 2, playable_card_exists));
              } else {
            std::cout << "next turn" << std::endl;
            moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());

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
            moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          } else if (count[0] > count[1] && block.size() > 0){
            moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          } else {
            moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, rand() % (int) room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          }

          // if (entityID == 1) {
          //   moteur->AddCommand(std::make_shared<engine::CommandExitRoom>());
          // } else {
          //   moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());
          // }

        }
      }


    }

    //
    // int index = rand() % (int) commands.size();
    // std::shared_ptr<Command> command_chosen = commands[index];
    // moteur->AddCommand(command_chosen);

    if ((entityID == (int) gameState->GetPlayers().size() -1) &&
        (gameState->GetIsInsideRoom() && (( gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom() ||
        gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom()) ||
        (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsEnemyRoom() &&
        gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon())))){
          moteur->AddCommand(std::make_shared<CommandExitRoom>());
    } else if (gameState->GetIsInsideRoom() && (( gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom() ||
               gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom()) ||
               (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsEnemyRoom() &&
               gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon()))){
                  moteur->AddCommand(std::make_shared<CommandNextEntity>());
    }
  }
}

std::shared_ptr<engine::Moteur>& AI_Heuristique::GetMoteur(){
  return moteur;
}

// cards : contient les cartes actuellement présentent dans la main
// cards_played : pointeur vers un int[5]->si cards_played[i] = 0, la carte i n'a pas été jouée, si cards_played[i] = 1 ou 2, la carte i a été jouée en 1er/2eme
// energy_left : l'énergie restante du joueur. Note: certaines cartes coûtent 0.
// max : le maximum d'attaque atteint actuellement (initialement 0)
// index : l'index de la carte qui a été jouée/non jouée en dernier (initialement -1)
// nb_card_played : le nombre de cartes déjà jouées - utilisé par cards_played uniquement (pour le débug)
int AI_Heuristique::Max_attack(std::vector<state::Card*> cards, int * cards_played, int energy_left, int max, int index, int nb_card_played){
  if(index >= (int) cards.size() - 1 ) return max;
  int newmax = max;
  for(int i = index+1; i< (int) cards.size(); i++){
    if(cards_played[i] == 0 && cards[i]->GetCost() <= energy_left && cards[i]->GetAttack() > 0 ){


      int cards_played_cpy[5];
      for(int j = 0; j < 5; j++){
        cards_played_cpy[j] = cards_played[j];
      }

      cards_played_cpy[i] = nb_card_played + 1;
      // calcule le max en jouant la carte i
      newmax =  Max_attack(cards, cards_played_cpy, energy_left - cards[i]->GetCost(), max  + cards[i]->GetAttack(), i, nb_card_played + 1);
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

int AI_Heuristique::Max_attack_ite(std::vector<state::Card*> cards, int * cards_played, int energy_available, int block, int life){
  int best_choice = 0;
  int max_damage = 0;
  int energy_used = 0;
  int card_played_order = 1;

  for (int i = 0; i < pow(2,cards.size()); i++){
    int damage = 0;
    int energy = 0;

    for (int card_nb = 0; card_nb < (int) cards.size(); card_nb ++){
      if ((int) (i / pow(2, card_nb)) % 2){
        damage += cards[card_nb]->GetAttack();
        energy += cards[card_nb]->GetCost();
      }
    }


    if (energy <= energy_available &&
        (damage > (block + life) && energy < energy_used)
         || (damage > max_damage && max_damage < (block + life))
         || (damage == max_damage && energy <= energy_used)){
      max_damage = damage;
      energy_used = energy;
      best_choice = i;
    }
  }

  if (max_damage > block){
    for (int card_nb = 0; card_nb < (int) cards.size(); card_nb ++){
      if ((int) (best_choice / pow(2, card_nb)) % 2){
        cards_played[card_nb] = card_played_order;
        card_played_order++;
      }
    }

    return max_damage;
  } else return 0;
}

int AI_Heuristique::Try_block(std::vector<state::Card*> cards, int * cards_played, int energy_left, int block, int index, int nb_card_played, int block_aim){
  if(index >= (int) cards.size() - 1  || block >= block_aim) return block;
  int newblock = block;
  for(int i = index + 1; i< (int) cards.size(); i++){
    if(cards_played[i] == 0 && cards[i]->GetCost() <= energy_left && cards[i]->GetBlock() > 0 && i != index){

      int cards_played_cpy[5];
      for(int j = 0; j < 5; j++){
        cards_played_cpy[j] = cards_played[j];
      }

      cards_played_cpy[i] = nb_card_played + 1;
      newblock = Try_block(cards, cards_played_cpy, energy_left - cards[i]->GetCost(), block  + cards[i]->GetBlock(), i, nb_card_played + 1, block_aim);
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
