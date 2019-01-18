#include "AI_Deep.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <limits>
#include "networkManager.h"

using namespace ai;
using namespace state;
using namespace engine;
using namespace networkManager;




AI_Deep::AI_Deep (){}
AI_Deep::AI_Deep (std::shared_ptr<state::GameState> gameState, std::shared_ptr<engine::Moteur> moteur, int entityID){
  this -> gameState = gameState;
  this -> moteur = moteur;
  if(entityID >=0 && entityID < 2){
    this -> entityID = entityID;
  } else entityID = 0;
  network = false;

}
AI_Deep::~AI_Deep (){}

// std::vector<std::unique_ptr<Node>> AI_Deep::Create_Tree (int current_index, int target, std::vector<int> indexes_left){
//
// }




std::shared_ptr<Node> AI_Deep::Create_Next(int current_index, int target, std::vector<int> indexes_left){
  std::vector<std::shared_ptr<Node>> next_nodes;
  if(indexes_left.size()==0){ // time to end turn
    return( std::make_shared<Node>(-1,0,next_nodes));
  }
  else{
    std::vector<std::shared_ptr<Node>> empty_node;
    next_nodes.push_back(std::make_shared<Node>(-1,0,empty_node)); // command next_turn
    for (int i : indexes_left){
      std::vector<int> new_indexes_left;
      int floorNb = gameState->GetMap()->GetCurrentFloor();
      std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
      std::vector<Card*> hand = room -> GetHands()[entityID] -> GetCards();
      // copy indexes without i:
      for(int j : indexes_left){
        if (j != i) new_indexes_left.push_back(j);
      }
      if(new_indexes_left.size() !=0){
        if(hand[i] -> GetTarget() == 0 || hand[i] -> GetTarget() == 3 ){
          for(size_t tp = 0; tp < gameState -> GetPlayers().size(); tp++){
            if(gameState->GetPlayers()[tp]->GetIsEntityAlive()){
              next_nodes.push_back(Create_Next(i, tp, new_indexes_left)); //play card on different targets
            }
          }
        } else{
          for(size_t te = 0; te < room -> GetEnemies().size(); te++){
            if(room->GetEnemies()[te] ->GetIsEntityAlive()){
              next_nodes.push_back(Create_Next(i, te + 2, new_indexes_left)); //play card on different targets
            }
          }
        }
      } else {
        if(hand[i] -> GetTarget() == 0 || hand[i] -> GetTarget() == 3 ){
          for(size_t tp = 0; tp < gameState -> GetPlayers().size(); tp++){
            if(gameState->GetPlayers()[tp]->GetIsEntityAlive()){
              next_nodes.push_back(std::make_shared<Node>(i,tp,empty_node));
            }
          }
        } else{
          for(size_t te = 0; te < room -> GetEnemies().size(); te++){
            if(room->GetEnemies()[te]->GetIsEntityAlive()){
              next_nodes.push_back(std::make_shared<Node>(i,te + 2,empty_node));
            }
          }
        }
      }
    }
    return(std::make_shared<Node>(current_index, target, next_nodes));
  }
}

std::shared_ptr<engine::Moteur> AI_Deep::GetMoteur (){
  return moteur;
}

int AI_Deep::Seek_Best(std::shared_ptr<Node> tree, int P_PV_init, std::vector<int> E_PV_init, int P_PV_current,int P_Block_current, int P_Energy_current,
   int Current_element, std::vector<int> E_block_current, Buff Current_Buff, std::vector<Debuff> E_Current_Debuff){
  // tree: the tree with all the possible cards played, in any order
  // P_PV_init : initial amount of Pv of the IA (to calculate the score)
  // E_PV_init : initial amout of PV of the ennemies (if ennemy was dead from the start E_PV_init[i] = 0)
  // P_Block_current : current amout of block of the IA
  // E_PV_current : current amout of PV of the ennemies
  // P_Energy_current: current amout of energy of the IA
  // Current_element : current element of the player
  // E_block_current : current block on each of the enemies. if block is negative, it means the enemy has lost that much life
  //Current_Buff : current buff on player
  //E_Current_Debuff : current debuff on enemy

  int floorNb = gameState->GetMap()->GetCurrentFloor();
  std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
  std::vector<Card*> hand = room -> GetHands()[entityID] -> GetCards();
  bool end = false;
  if (tree -> GetCardIndex() == -1){ // finished playing cards
    end = true;
  } else if(tree -> GetCardIndex() != -2){ //not the root
      if(hand[tree -> GetCardIndex()] -> GetCost() > P_Energy_current){ //card cannot be played, this is the end : calculating score
        end = true;
      } else{ // play card
        int score = - std::numeric_limits<int>::max();
        // tree -> SetToPlay(true);
        // init all new data
        float tmp_block = 0;
        float tmp_attack = 0;
        int tmp_heal = 0;
        int retaliate = 0;
        Buff tmpBuff = Current_Buff;
        std::vector<Debuff> tmpE_Debuff;
        for(size_t i = 0; i<E_Current_Debuff.size(); i++){
          tmpE_Debuff.push_back(E_Current_Debuff[i]);
        }
        int tmp_element = hand[tree -> GetCardIndex()] -> GetElement();
        std::vector<int> tmp_E_block;
        for(size_t i = 0; i < E_block_current.size() ; i++){
          tmp_E_block.push_back(E_block_current[i]);
        }
        // calculate true attack/block/etc...
        if(tree -> GetTarget() == this->entityID){ // target is the IA
          // calculate block:
          tmp_block = hand[tree -> GetCardIndex()] -> GetBlock() + gameState -> GetPlayers()[entityID] -> GetStatBlock();
          if(Current_Buff.GetBlockPlus() > 0){
            tmp_block *= 1.5;
          }
          if(gameState -> GetPlayers()[entityID] -> GetDebuff().GetBlockMinus() > 0){
            tmp_block *= 0.5;
          }
          tmp_heal = hand[tree -> GetCardIndex()] -> GetHeal();
          if(P_PV_init< (P_PV_current +tmp_heal)){
            tmp_heal = P_PV_init - P_PV_current;
          }
          // change buff
          tmpBuff = *hand[tree -> GetCardIndex()] -> GetBuff();
          tmpBuff.SetBlockPlus(tmpBuff.GetBlockPlus() + Current_Buff.GetBlockPlus());
          tmpBuff.SetAttackPlus(tmpBuff.GetAttackPlus() + Current_Buff.GetAttackPlus());
          tmpBuff.SetEvade(tmpBuff.GetEvade() + Current_Buff.GetEvade());
          tmpBuff.SetHeal(tmpBuff.GetHeal() + Current_Buff.GetHeal());
          tmpBuff.SetRetaliate(tmpBuff.GetRetaliate() + Current_Buff.GetRetaliate());

        } else if(tree->GetTarget() >= 2){ //target is enemy
          //calculating attack:
          tmp_attack = hand[tree -> GetCardIndex()] -> GetAttack() + gameState -> GetPlayers()[entityID] -> GetStatAttack();
          if(Current_Buff.GetAttackPlus() > 0){
            tmp_attack *= 1.5;
          }
          if(gameState -> GetPlayers()[entityID] -> GetDebuff().GetAttackMinus() > 0){
            tmp_attack *= 0.5;
          }
          // considering elements...
          if((hand[tree -> GetCardIndex()] -> GetElement() - room -> GetEnemies()[tree -> GetTarget() - 2] -> GetElement() == -1)
              || (hand[tree -> GetCardIndex()] -> GetElement() - room -> GetEnemies()[tree -> GetTarget() - 2] -> GetElement() == 3)){ //element from enemy is stronger
                tmp_attack *= 0.5;
          } else if((hand[tree -> GetCardIndex()] -> GetElement() - room -> GetEnemies()[tree -> GetTarget() - 2] -> GetElement() == 1)
              || (hand[tree -> GetCardIndex()] -> GetElement() - room -> GetEnemies()[tree -> GetTarget() - 2] -> GetElement() == -3)){ //element from enemy is weaker
                tmp_attack *= 1.5;
          }
          //hitting all enemies:
          if(hand[tree -> GetCardIndex()] -> GetTarget() == 2){
            for(size_t i = 0; i < tmp_E_block.size(); i++){
              if( room -> GetEnemies()[i] -> GetBuff().GetEvade() <= 0){ // not evading attack
                tmp_E_block[i] -= (int) tmp_attack;
              }
            }
          } else if( room -> GetEnemies()[tree -> GetTarget() - 2] -> GetBuff().GetEvade() <= 0){ // not evading attack
            tmp_E_block[tree -> GetTarget() -2] -= (int) tmp_attack;
          }

          // change Debuff:
          tmpE_Debuff[tree->GetTarget()] = *hand[tree -> GetCardIndex()] -> GetDebuff();
          tmpE_Debuff[tree->GetTarget()].SetAttackMinus(tmpE_Debuff[tree->GetTarget()].GetAttackMinus() + E_Current_Debuff[tree->GetTarget()].GetAttackMinus()); //blockminus not relevant here

          // retaliate on player
          if(room -> GetEnemies()[tree -> GetTarget() - 2] -> GetBuff().GetRetaliate() > 0){
            retaliate +=5;
          }
          if(P_Block_current> retaliate){
            tmp_block = - retaliate;
            retaliate = 0;
          } else{
            retaliate -= P_Block_current;
            tmp_block = -P_Block_current;
          }
        }

        std::vector<std::shared_ptr<Node>> next_cards = tree -> GetNextCards();
        int index = -1;
        for(size_t i = 0; i<next_cards.size(); i++){ //calculate score on next nodes/cards with the new data
           int tmp_score = Seek_Best(next_cards[i], P_PV_init, E_PV_init, P_PV_current - retaliate + tmp_heal,P_Block_current + tmp_block,
             P_Energy_current - hand[tree -> GetCardIndex()] -> GetCost(), tmp_element,tmp_E_block, tmpBuff, tmpE_Debuff);
           if( tmp_score > score){
             score = tmp_score;
             index = i;
           }
            // else node -> SetToPlay(false);//not the best node, should not be played
        }
        if(index > -1){
          next_cards[index] -> SetToPlay(true);
        }
        return(score);
    }

  } else{// the root -> no card played -> only calculating the score of the sons
    int score = - std::numeric_limits<int>::max();
    std::vector<std::shared_ptr<Node>> next_cards = tree -> GetNextCards();
    int index = -1;
    for(size_t i = 0; i<next_cards.size(); i++){
       int tmp_score = Seek_Best(next_cards[i], P_PV_init, E_PV_init, P_PV_current, P_Block_current, P_Energy_current, Current_element, E_block_current, Current_Buff,  E_Current_Debuff);
       if( tmp_score > score){
         score = tmp_score;
         index = i;
       }
  // else node -> SetToPlay(false);//not the best node, should not be played
    }
    if(index > -1){
      next_cards[index] ->SetToPlay(true);
    } else std::cout <<"nothing to play" << std::endl;
    return(score);
  }

// calculating score
if(end){
  int score = 0;
  // need to add the enemies' attack to the score
  int E_element = gameState -> GetMap() -> GetFloors()[floorNb] -> GetElement();
  int E_attack = 0;
  std::vector<int> tmp_E_block; //need to recalculate life/block because of the player's retaliate
  for(size_t i = 0; i < E_block_current.size() ; i++){
    tmp_E_block.push_back(E_block_current[i]);
  }
  if(Current_Buff.GetEvade() <= 0){ //if player doesn't avoid the attack
    for(size_t i = 0; i < room -> GetEnemies().size(); i++){
      if(E_PV_init[i] > 0 && E_PV_init[i] + tmp_E_block[i]  > 0){ //the enemy is not dead (retaliate doesn't count)
        float tmp_attack = room -> GetEnemies()[i] -> GetSkills()[room -> GetEnemies()[i] -> GetIntent()] -> GetAttack();
        if(tmp_attack > 0 ){
          tmp_attack += room -> GetEnemies()[i] -> GetStatAttack();
          if(E_Current_Debuff[tree->GetTarget()].GetAttackMinus()> 0){
            tmp_attack *= 0.5;
          }
          if(room -> GetEnemies()[i] -> GetBuff().GetAttackPlus() > 0){
            tmp_attack *= 1.5;
          }
          E_attack += (int) tmp_attack;
          // retaliation of the player:
          if(Current_Buff.GetRetaliate() >  0){
            tmp_E_block[i] -= 5;
          }
        }
      }
    }
    if(Current_element - E_element == -1 || Current_element - E_element == 3){ // the enemy has a better element than the player
      E_attack *= 1.5;
    } else if(Current_element - E_element == 1 || Current_element - E_element == -3){ //the enemy has a weaker element than the player
      E_attack *= 0.5;
    }
  }
  if(P_Block_current > E_attack){
    E_attack = 0;
  } else{ E_attack -= P_Block_current;}
  //calculating score: score += 100 for each enemy killed, else score += enemy_PV_lost
  for(size_t i = 0; i < E_PV_init.size(); i++){
    if(E_PV_init[i] > 0){
      if(E_PV_init[i] + tmp_E_block[i]  <=0){
        score += 100;
      } else score -= tmp_E_block[i]; //if block < 0 it means the enemy lost PV
    }
  } // if player is dead after the enemies' attack, score = - infinity (or - max_value for the int), else score -= Player_PV_lost
  if(P_PV_current - E_attack<= 0){
    score =  - std::numeric_limits<int>::max();
  } else score = score -(P_PV_init - P_PV_current + E_attack);
  return score;
  }

  std::cout << "this should not be printed" << std::endl;
  return - std::numeric_limits<int>::max();
}

void AI_Deep::Play_Cards(std::shared_ptr<Node> tree, std::vector<int> cards_index){
  if(tree->GetCardIndex() == -1){
    std::cout << "next turn" << std::endl;
    moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());
    moteur->AddCommand(std::make_shared<engine::CommandEndFight>());
  } else{
      if(tree->GetCardIndex() != -2){
        moteur->AddCommand(std::make_shared<engine::CommandPlayCard>(entityID, tree->GetTarget(), cards_index[tree->GetCardIndex()]));
        for(int j = tree->GetCardIndex() ; j<  5; j++){
          cards_index[j] = cards_index[j] - 1;
        }
      }
    bool found = false;
    size_t i = 0;
    while(!found && i<tree->GetNextCards().size()){
      if(tree->GetNextCards()[i] ->GetToPlay()){
        found = true;
        Play_Cards(tree->GetNextCards()[i], cards_index);
      }
      i++;
    }
    if(!found){
      moteur->AddCommand(std::make_shared<engine::CommandNextEntity>());
      moteur->AddCommand(std::make_shared<engine::CommandEndFight>());
    }
  }
}


void AI_Deep::Play(){
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
          if (room->GetReward()[i]->GetAttack() > 0) {attack.push_back(i);
          } else if (room->GetReward()[i]->GetBlock() > 0 || room->GetReward()[i] -> GetHeal() > 0) {block.push_back(i);
          }else if ((room->GetReward()[i]->GetDebuff()->GetAttackMinus() > 0) || (room->GetReward()[i]->GetDebuff()->GetBlockMinus() > 0)) {attack.push_back(i);
          } else block.push_back(i);
        }

        if (count[0] < count[1] && attack.size() > 0){ //less attack than block
          int max = -99;
          int index = -1;
          for(size_t i = 0; i < attack.size(); i++){
            state::Card* card = room->GetReward()[attack[i]];
            int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                        card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                        card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                        - 2 * card -> GetCost();
            if(card -> GetTarget() >=2) score +=5;
            if (max < score){
              max = score;
              index = attack[i];
            }
          }

        //  moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[rand() % (int) attack.size()], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, index, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        } else if ((count[0] > count[1] && block.size()) > 0){
          int max = -99;
          int index = -1;
          for(size_t i = 0; i < block.size(); i++){
            state::Card* card = room->GetReward()[block[i]];
            int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                        card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                        card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                        - 2 * card -> GetCost();
            if(card -> GetTarget() >=2) score +=5;
            if (max < score){
              max = score;
              index = block[i];
            }
          }
          //moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[rand() % (int) block.size()], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, index, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));

        } else {

          int max = -99;
          int index = -1;
          for(size_t i = 0; i < room->GetReward().size(); i++){
            state::Card* card = room->GetReward()[i];
            int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                        card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                        card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                        - 2 * card -> GetCost();
            if(card -> GetTarget() >=2) score +=5;
            if (max < score){
              max = score;
              index = i;
            }
          }
          //moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, rand() % (int) room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, index, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));

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
          if(cards.size() == 5){
            std::vector<int> indexes_left;
            indexes_left.push_back(0);
            indexes_left.push_back(1);
            indexes_left.push_back(2);
            indexes_left.push_back(3);
            indexes_left.push_back(4);

            std::shared_ptr<Node> node = Create_Next(-2, 0, indexes_left);
            std::cout << "created tree" << std::endl;
            //init the elements we need
            std::vector<int> E_PV_init;
            std::vector<int> E_block_current;
            std::vector<Debuff> E_Current_Debuff;
            for(auto& enemy : room->GetEnemies()){
              E_PV_init.push_back(enemy->GetLife());
              E_block_current.push_back(enemy->GetBlock());
              E_Current_Debuff.push_back(enemy->GetDebuff());
            }

            std::cout <<"seeking best score" << std::endl;
            int best_score = Seek_Best (node, gameState->GetPlayers()[entityID]->GetLife(), E_PV_init,gameState->GetPlayers()[entityID]->GetLife() ,
            0, 3, gameState->GetPlayers()[entityID]->GetElement(), E_block_current, gameState->GetPlayers()[entityID]->GetBuff(),  E_Current_Debuff);
            std::cout<< "best score is " << best_score << std::endl;

            std::vector<int> cards_index;
            for(int i = 0; i<5; i++){
              cards_index.push_back(i);
            }
            std::cout<<"play cards" << std::endl;
            Play_Cards(node, cards_index);

          } else moteur->AddCommand(std::make_shared<CommandNextEntity>());

      }else { //fight won

          std::vector<int> count = player->GetDeck()->CountCards();
          std::vector<int> attack, block, buff, debuff;

          for (int i = 0; i < (int) room->GetReward().size(); i++ ){
            if (room->GetReward()[i]->GetAttack() > 0) attack.push_back(i);
            if (room->GetReward()[i]->GetBlock() > 0) block.push_back(i);
            if (room->GetReward()[i]->GetDebuff() > 0) attack.push_back(i);
            if (room->GetReward()[i]->GetBuff() > 0) block.push_back(i);
          }

          if (count[0] < count[1] && attack.size() > 0){
            int max = -99;
            int index = -1;
            for(size_t i = 0; i < attack.size(); i++){
              state::Card* card = room->GetReward()[attack[i]];
              int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                          card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                          card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                          - 2 * card -> GetCost();
              if(card -> GetTarget() >=2) score +=5;
              if (max < score){
                max = score;
                index = attack[i];
              }
            }
            moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, index, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          } else if (count[0] > count[1] && block.size() > 0){
            int max = -99;
            int index = -1;
            for(size_t i = 0; i < block.size(); i++){
              state::Card* card = room->GetReward()[block[i]];
              int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                          card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                          card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                          - 2 * card -> GetCost();
              if(card -> GetTarget() >=2) score +=5;
              if (max < score){
                max = score;
                index = block[i];
              }
            }
            moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, index, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
          } else {
            int max = -99;
            int index = -1;
            for(size_t i = 0; i < room->GetReward().size(); i++){
              state::Card* card = room->GetReward()[i];
              int score = card -> GetAttack() + card -> GetBlock()  + card -> GetHeal() * 4 + card -> GetBuff() -> GetEvade() * 6 +
                          card -> GetBuff() -> GetRetaliate() * 4 + card -> GetBuff() -> GetHeal() * 2 + card -> GetDebuff() -> GetAttackMinus() * 2 +
                          card -> GetDebuff() -> GetBlockMinus() * 2 + card -> GetBuff() -> GetAttackPlus() * 2 + card -> GetBuff() -> GetBlockPlus() * 2
                          - 2 * card -> GetCost();
              if(card -> GetTarget() >=2) score +=5;
              if (max < score){
                max = score;
                index = i;
              }
            }
            //moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, rand() % (int) room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
            moteur->AddCommand(std::make_shared<engine::CommandAddCard>(entityID, index, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));

          }

        }
      }


    }

    if ((entityID == (int) gameState->GetPlayers().size() -1) &&
        (gameState->GetIsInsideRoom() && (( gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom() ||
        gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom()) ||
        (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsEnemyRoom() &&
        gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon())))){
          //moteur->AddCommand(std::make_shared<CommandExitRoom>());
          moteur->AddCommand(std::make_shared<CommandNextEntity>());
    } else if (gameState->GetIsInsideRoom() && (( gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom() ||
               gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom()) ||
               (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsEnemyRoom() &&
               gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon()))){
                  moteur->AddCommand(std::make_shared<CommandNextEntity>());
    }
  } else if(network){
    int entityTurn = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn();
    if(entityTurn < 2 && entityTurn != entityID-1 && moteur->GetCommands().empty() && moteur->GetNetwork()){
     NetworkManager* NM = NetworkManager::instance();
     Json::Value test = NM->Get("/command/" + std::to_string(entityID -1));
     if(!test.empty()){
       NM->Delete("/command/" + std::to_string(entityID -1));
       std::cout << "received :" <<std::endl;
       std::cout << test<< std::endl;
       moteur->ReadCommand(test);
  }
}

void AI_Deep::SetNetwork(bool network){
  this ->network = network;
}

bool AI_Deep::GetNetwork(){
  return network;
}
