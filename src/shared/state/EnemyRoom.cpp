// #include "EnemyRoom.h"
//
// using namespace state;
//
//
// EnemyRoom::~EnemyRoom()
// {
//
// }
// // EnemyRoom::EnemyRoom (int roomNumber, std::string element, std::vector<std::shared_ptr<Enemy>> enemies, std::vector<std::shared_ptr<DrawPile>> drawPiles): Room(roomNumber, element, false, true, false), enemies(enemies), drawPiles(drawPiles), turn(0), entityTurn(0), isGameLost(false)
// // {
// //   hands.reserve(2);
// //   discardPiles.reserve(2);
// // }
//
// int EnemyRoom::GetTurn (){
//   return turn;
// }
//
// int EnemyRoom::GetEntityTurn (){
//   return entityTurn;
// }
//
// bool EnemyRoom::GetIsGameLost (){
//   return isGameLost;
// }
//
// void EnemyRoom::SetIsGameLost (bool lost){
//   this->isGameLost = lost;
// }
//
// // std::vector<std::shared_ptr<DrawPile>> EnemyRoom::GetDrawPiles (){
// //   return drawPiles;
// // }
// //
// // std::vector<std::shared_ptr<DiscardPile>> EnemyRoom::GetDiscardPiles (){
// //   return discardPiles;
// // }
// //
// // std::vector<std::shared_ptr<Hand>> EnemyRoom::GetHands (){
// //   return hands;
// // }
//
// void EnemyRoom::SetDrawPiles (std::vector<std::shared_ptr<DrawPile>> drawPileVector){
//   this->drawPiles = drawPileVector;
// }
//
// void EnemyRoom::SetDiscardPiles (std::vector<std::shared_ptr<DiscardPile>> discardPileVector){
//   this->discardPiles = discardPileVector;
// }
//
// void EnemyRoom::SetHands (std::vector<std::shared_ptr<Hand>> handVector){
//   this->hands = handVector;
// }
