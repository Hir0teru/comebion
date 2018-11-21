// #include "AI_Heuristique.h"
// #include "engine.h"
// #include <iostream>
//
// using namespace ai;
// using namespace state;
// using namespace engine;
//
//
// AI_Heuristique::AI_Heuristique (){}
// AI_Heuristique::AI_Heuristique (std::shared_ptr<state::GameState> gameState, std::shared_ptr<engine::Moteur> moteur, int entityID){
//   this->gameState = gameState;
//   this->moteur = moteur;
//   if(entityID >=0 && entityID < 2){
//     this->entityID = entityID;
//   } else entityID = 0;
// }
//
//
// void AI_Heuristique::Play (){
//   std::cout << "thinking ..." << std::endl;
//   if (gameState->GetRules()->GetIsGameLost()){
//     std::cout << "you're dead, deal with it" << std::endl;
//   } else if (!gameState->GetIsInsideRoom()){
//     moteur.AddCommand(std::make_shared<engine::CommandEnterRoom>());
//   } else {
//     int floorNb = gameState->GetMap()->GetCurrentFloor();
//     std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
//     Player* player = gameState->GetPlayers()[entityID];
//
//     if (room->GetIsSleepRoom()){
//       if (player->GetLife() < player->GetMaxLife()/2){
//         moteur.AddCommand(std::make_shared<engine::CommandHeal>(room->GetHeal(), entityID));
//       } else {
//         moteur.AddCommand(std::make_shared<engine::CommandChangeStat>(gameState->GetPlayers()[entityID]->GetStatAttack() + 2,gameState->GetPlayers()[entityID]->GetStatBlock() + 2,  entityID));
//       }
//       moteur.AddCommand(std::make_shared<engine::CommandExitRoom>());
//     } else if (room->GetIsSpecialTrainingRoom()) {
//       std::vector<int> count = player->GetDeck()->CountCards();
//       std::vector<int> attack, block, buff, debuff;
//
//       for (int i = 0; i < room->GetReward().size(); i++ ){
//         if (room->GetReward()[i]->GetAttack() > 0) attack.push_back(i);
//         if (room->GetReward()[i]->GetBlock() > 0) block.push_back(i);
//         if (room->GetReward()[i]->GetDebuff() > 0) attack.push_back(i);
//         if (room->GetReward()[i]->GetBuff() > 0) block.push_back(i);
//       }
//
//       if (count[0] < count[1] && attack.size() > 0){
//         moteur.AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
//       } else if (count[0] > count[1] && block.size()) > 0{
//         moteur.AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
//       } else {
//         moteur.AddCommand((std::make_shared<engine::CommandAddCard>(entityID, rand() % room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
//       }
//
//       if (entityID == 1) {
//         moteur.AddCommand(std::make_shared<engine::CommandExitRoom>());
//       } else {
//         moteur.AddCommand(std::make_shared<engine::CommandNextEntity>());
//       }
//
//     } else { //enemyroom
//       if (!gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon()){ // keep fighting
//
//         DeckParts* hand = room->GetHands()[entityID];
//
//
//
//         for (int i = 0; i < room->GetHands()[entityID]->GetSize(); i++){ // try to play cards
//           if(room->GetHands()[entityID]->GetCards()[i]->GetTarget() == 0 || room->GetHands()[entityID]->GetCards()[i]->GetTarget() == 3){
//             possibleCommands.push_back(std::make_shared<engine::CommandPlayCard>(entityID, 0, i));
//             if ((int)gameState->GetPlayers().size() == 2 ){
//               possibleCommands.push_back(std::make_shared<engine::CommandPlayCard>(entityID, 1, i));
//             }
//           } else {
//             for (int j = 0; j < (int) room->GetEnemies().size(); j++){
//               possibleCommands.push_back(std::make_shared<engine::CommandPlayCard>(entityID, j+2, i));
//             }
//           }
//         }
//
//
//
//
//         moteur.AddCommand(std::make_shared<engine::CommandNextEntity>());
//
//
//
//
//
//
//
//
//
//
//
//       } else { //fight won
//
//         std::vector<int> count = player->GetDeck()->CountCards();
//         std::vector<int> attack, block, buff, debuff;
//
//         for (int i = 0; i < room->GetReward().size(); i++ ){
//           if (room->GetReward()[i]->GetAttack() > 0) attack.push_back(i);
//           if (room->GetReward()[i]->GetBlock() > 0) block.push_back(i);
//           if (room->GetReward()[i]->GetDebuff() > 0) attack.push_back(i);
//           if (room->GetReward()[i]->GetBuff() > 0) block.push_back(i);
//         }
//
//         if (count[0] < count[1] && attack.size() > 0){
//           moteur.AddCommand(std::make_shared<engine::CommandAddCard>(entityID, attack[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
//         } else if count[0] > count[1] && block.size() > 0{
//           moteur.AddCommand(std::make_shared<engine::CommandAddCard>(entityID, block[0], gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
//         } else {
//           moteur.AddCommand((std::make_shared<engine::CommandAddCard>(entityID, rand() % room->GetReward().size(), gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
//         }
//
//         if (entityID == 1) {
//           moteur.AddCommand(std::make_shared<engine::CommandExitRoom>());
//         } else {
//           moteur.AddCommand(std::make_shared<engine::CommandNextEntity>());
//         }
//
//       }
//     }
//   }
//
//
//   int index = rand() % (int) commands.size();
//   std::shared_ptr<Command> command_chosen = commands[index];
//   moteur->AddCommand(command_chosen);
//
//   int floorNb = gameState->GetMap()->GetCurrentFloor();
//
//   if (gameState->GetIsInsideRoom() &&(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom() || gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom())) {
//     moteur->AddCommand(std::make_shared<CommandNextEntity>());
//     std::cout << "done thinking!" << std::endl;
//   }
//
// }
//
// std::shared_ptr<engine::Moteur>& AI_Heuristique::GetMoteur(){
//   return moteur;
// }
