// #include "Card.h"
//
// using namespace state;
//
// Card::Card (std::string type, std::string element){
//   name = type;
//   /// Coût de la carte en energie
//   cost = 1;
//   /// Type de cible visée (0: joueur, 1: monstre, 2: tous les monstres, 3: tous les joueurs)
//   target = 1;
//   /// Image représentant la carte
//
//   /// Element de la carte (air, eau, terre, feu, pas d'element)
//   element = element;
//   /// Dégats de la carte
//   if (type == "basic attack"){
//     attack = 5;
//     block = 0;
//     image = "/home/ombre/Documents/Projet/comebion/res/textures/cards/bending/air_bending/1.png";
//   }
//   /// Nombre de block créé par la carte (à destination du joueur)
//   else {
//     block = 5;
//     attack = 0;
//     image = "/home/ombre/Documents/Projet/comebion/res/textures/cards/bending/air_bending/2.png";
//   }
//
//   /// Nombre de cartes pichées
//   draw = 0;
//   /// Nombre de cartes défaussées
//   discard = 0;
//   /// nombre de point de vie du joueur soignés
//   heal = 0;
//   /// liste de débuffs appliqués
//   // debuffs = std::vector<std::shared_ptr<Debuff>> ();
//   // /// liste de buffs appliqués
//   // buffs = std::vector<std::shared_ptr<Buff>> ();
// };
//
// int Card::GetCost (){
//   return cost;
// };
//
// void Card::SetCost (int cost){
//   cost = cost;
// };
//
// int Card::GetTarget (){
//   return target;
// };
//
// std::string Card::GetImage (){
//   return image;
// };
//
// std::string Card::GetElement (){
//   return element;
// };
//
// int Card::GetAttack (){
//   return attack;
// };
//
// int Card::GetBlock (){
//   return block;
// };
//
// int Card::GetDraw (){
//   return draw;
// };
//
// int Card::GetDiscard (){
//   return discard;
// };
//
// int Card::GetHeal (){
//   return heal;
// };
//
// Debuff Card::GetDebuff (){
//   return debuff;
// };
//
// Buff Card::GetBuff (){
//   return buff;
// };
//
// // Setters and Getters
