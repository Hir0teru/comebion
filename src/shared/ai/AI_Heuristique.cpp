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
        // moteur->AddCommand(std::make_shared<engine::CommandExitRoom>());
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
          std::vector<int> playable_cards;
          // int playable_card_exists = -1;
          // int i = 0;
          int evade = -1;
          for(int i = 0; i < (int) cards.size(); i++){
            if (cards[i]->GetCost() <= gameState->GetPlayers()[entityID]->GetEnergy()){
              // playable_card_exists = i;
              playable_cards.push_back(i);
              if(cards[i] -> GetBuff() -> GetEvade() >0){
                evade = i;  //used to block
              }
            }
          }
          if(playable_cards.size() > 0){

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
                attack += enemy -> GetStatAttack();
                if(enemy -> GetBuff().GetAttackPlus() > 0){
                  attack *= 1.5;
                }
                block_aim+= attack;
              }
            }
            int try_block = 0; // valeur de block max ou atteinte en jouant au mieux le bloc
            int max = 0; // valeur d'attaque max atteinte en jouant des cartes d'attaque
            Player * player = gameState->GetPlayers()[entityID];
            if(block_aim > player->GetBlock() && player -> GetBuff().GetEvade() <= 0){
              if(evade > -1){
                moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, entityID, evade));
                evade = -2; // played evade
                // std::cout << "played evade" << std::endl;
              }
              else{ // no evade cards to play
                try_block = Try_block(cards, cards_played, player, block_aim);
                std::cout << "try block: " << try_block << std::endl;
                if(try_block == 0){
                  max = Max_attack(cards, cards_played, gameState->GetPlayers()[entityID], room->GetEnemies()[room->MostVulnerableEnemy() - 2].get());
                  std::cout << "max attack: " << max << std::endl;
                }
              }
            } else{
              max = Max_attack(cards, cards_played, gameState->GetPlayers()[entityID], room->GetEnemies()[room->MostVulnerableEnemy() - 2].get());
              std::cout << "max attack: " << max << std::endl;
            }

            if(max > 0){
              // play cards fo attackplus

              if(block_aim > 0){ // the last element matters
                for(int i = 0; i < 5; i++){
                  // chaeck if the card makes you vulnerable, if so, play first.
                  if(cards_played[i] > 0 && (cards[i]->GetTarget() == 1 || cards[i]->GetTarget() == 2 )
                      && (cards[i] -> GetElement() - gameState->GetMap()->GetFloors()[floorNb] -> GetElement() == -1 || cards[i] -> GetElement() - gameState->GetMap()->GetFloors()[floorNb] -> GetElement() == 3 )){
                   // std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                    moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, room->MostVulnerableEnemy(), cards_index[i]));
                    cards_played[i] = 0;
                    for(int j = i+1 ; j<  (int) cards.size(); j++){
                      cards_index[j] = cards_index[j] - 1;
                    }
                  }
                }
              }
              for(int i = 0; i < 5; i++){
                // std::cout << cards_played[i] << std::endl;
                if(cards_played[i] > 0 && (cards[i]->GetTarget() == 1 || cards[i]->GetTarget() == 2)){
                 std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                  moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, room->MostVulnerableEnemy(), cards_index[i]));
                  for(int j = i+1 ; j<  (int) cards.size(); j++){
                    cards_index[j] = cards_index[j] - 1;
                  }
                }
              }

            } else if(try_block > 0){
              // play cards for block - element will matter

              for(int i = 0; i < 5; i++){
                // std::cout << cards_played[i] << std::endl;
                if(cards_played[i] > 0 && (cards[i]->GetTarget() == 0 || cards[i]->GetTarget() == 3)){
                 std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                  moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, entityID, cards_index[i]));
                  for(int j = i+1 ; j<  (int) cards.size(); j++){
                    cards_index[j] = cards_index[j] - 1;
                  }
                }
              }

              for(int i = 0; i < 5; i++){
                // std::cout << cards_played[i] << std::endl;
                if(cards_played[i] > 0 && (cards[i]->GetTarget() == 0 || cards[i]->GetTarget() == 3)
                  && (cards[i] -> GetElement() - gameState->GetMap()->GetFloors()[floorNb] -> GetElement() == -1 || cards[i] -> GetElement() - gameState->GetMap()->GetFloors()[floorNb] -> GetElement() == 3 )){
                 std::cout << " card " << i << " played in " << cards_played[i] << std::endl;
                  moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, entityID, cards_index[i]));
                  cards_played[i] = 0;
                  for(int j = i+1 ; j<  (int) cards.size(); j++){
                    cards_index[j] = cards_index[j] - 1;
                  }
                }
              } // else: try play random card
            } else if (evade != -2){
              int choice;

              choice = rand() % playable_cards.size();
              // if(cards[playable_card_exists]->GetTarget() == 0 || cards[playable_card_exists]->GetTarget() == 3){
              //     moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 0, playable_card_exists));
              //   } else moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 2, playable_card_exists));

              //check if element matters:
              if(block_aim > 0){
                int enemyElement = gameState->GetMap()->GetFloors()[floorNb] -> GetElement(); // is the element of the card a bad element?
                if (cards[playable_cards[choice]] -> GetElement() - enemyElement == -1 || cards[playable_cards[choice]] -> GetElement() - enemyElement == 3 ){
                  bool found = false;
                  for(int i : playable_cards){
                    if(! (cards[playable_cards[i]] -> GetElement() - enemyElement == -1 || cards[playable_cards[i]] -> GetElement() - enemyElement == 3 )){
                      found = true;
                      choice = i;
                      break;
                    }
                  }
                  if (!found){
                    choice = -1;
                  }
                }
              }
              if(choice > -1){
                if(cards[playable_cards[choice]]->GetTarget() == 0 || cards[playable_cards[choice]]->GetTarget() == 3){
                    moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 0, playable_cards[choice]));
                  } else moteur->AddCommand(std::make_shared<CommandPlayCard>(entityID, 2, playable_cards[choice]));
                } else{ // no more cards to play
                std::cout << "next turn" << std::endl;
                moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());
              }
            }

        } else{
          std::cout << "next turn" << std::endl;
          moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());
        }
      }
         else { //fight won

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

int AI_Heuristique::Max_attack(std::vector<state::Card*> cards, int * cards_played, Player* player, Enemy* enemy){
  int best_choice = 0;
  int max_damage = 0;
  int energy_used = 0;
  int card_played_order = 1;
  int block = enemy->GetBlock();
  int life = enemy->GetLife();
  int energy_available = player->GetEnergy();

  for (int i = 0; i < pow(2, cards.size()); i++){
    int damage = 0;
    int energy = 0;

    for (int card_nb = 0; card_nb < (int) cards.size(); card_nb ++){
      if ((int) (i / pow(2, card_nb)) % 2){
        damage += GetRealDamage(enemy, player, cards[card_nb]);
        energy += cards[card_nb]->GetCost();
      }
    }

    if (energy <= energy_available &&
        ((damage > (block + life) && energy < energy_used)
         || (damage > max_damage && max_damage < (block + life))
         || (damage == max_damage && energy <= energy_used))){
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


int AI_Heuristique::Try_block(std::vector<state::Card*> cards, int * cards_played, Player* player, int block_aim){
  int best_choice = 0;
  int max_block = 0;
  int energy_used = 0;
  int card_played_order = 1;
  int energy_available = player->GetEnergy();

  block_aim = block_aim - player->GetBlock();

  if (block_aim > 0) {
    for (int i = 0; i < pow(2, cards.size()); i++){
      int block = 0;
      int energy = 0;

      for (int card_nb = 0; card_nb < (int) cards.size(); card_nb ++){
        if ((int) (i / pow(2, card_nb)) % 2){
          block += GetRealBlock(player, cards[card_nb]) + cards[card_nb]->GetHeal();
          energy += cards[card_nb]->GetCost();
        }
      }

      if (energy <= energy_available &&
          ((block > block_aim && energy < energy_used)
           || (block > max_block && max_block < block_aim)
           || (block == max_block && energy <= energy_used))){
        max_block = block;
        energy_used = energy;
        best_choice = i;
      }
    }

    if (max_block > 0){
      for (int card_nb = 0; card_nb < (int) cards.size(); card_nb ++){
        if ((int) (best_choice / pow(2, card_nb)) % 2){
          cards_played[card_nb] = card_played_order;
          card_played_order++;
        }
      }
    }
  }

  return max_block;
}


int AI_Heuristique::GetRealDamage(Enemy* enemy, Player* player, Card* card){
  int entityElement = card->GetElement();
  int targetElement = enemy->GetElement();
  int damage = card->GetAttack();

  if(damage > 0){
    float tmpdamage;
    tmpdamage = damage + player->GetStatAttack();
    if(player->GetDebuff().GetAttackMinus() > 0 ){
      tmpdamage = tmpdamage/2.;
    }
    if(player->GetBuff().GetAttackPlus() > 0 ){
      tmpdamage = tmpdamage * 1.5;
    }
    // check elements:
    switch(entityElement){
    case 1:
      if (targetElement == 4){
        tmpdamage = tmpdamage * 1.5;
      } else if (targetElement == 2){
        tmpdamage = tmpdamage/2.;
      }
      break;
    case 2:
      if (targetElement == 1){
        tmpdamage = tmpdamage * 1.5;
      } else if (targetElement == 3){
        tmpdamage = tmpdamage/2.;
      }
        break;
    case 3:
      if (targetElement == 2){
        tmpdamage = tmpdamage * 1.5;
      } else if (targetElement == 4){
        tmpdamage = tmpdamage/2.;
      }
      break;
    case 4:
      if (targetElement == 3){
        tmpdamage = tmpdamage * 1.5;
      } else if (targetElement == 1){
        tmpdamage = tmpdamage/2.;
      }
      break;
    }
    return (int) tmpdamage;
  } else {
    return 0;
  }
}


int AI_Heuristique::GetRealBlock(Player* player, Card* card){
  int block = card->GetBlock();

  if (block != 0){
    block += player->GetStatBlock();
  }

  if (player->GetBuff().GetBlockPlus() > 0){
    block *= 1.5;
  }

  if (player->GetDebuff().GetBlockMinus() > 0){
    block *= 0.5;
  }

  return block;
}
