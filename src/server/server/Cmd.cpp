/**
 * @file Cmd.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "Cmd.hpp"

Cmd::Cmd (int author,
  std::string typeCmd,
  int entityID,
  int block,
int target,
int buff_AP,
int buff_BP,
int buff_E,
int buff_R,
int buff_H,
int playerID,
int card,
bool isDeckFull,
int debuff_AM,
int debuff_BM,
int energyAmount,
int damage,
int entityLife,
int targetLife,
int element,
int previousElement,
int intent,
int previousIntent,
int statAttack,
int statBlock,
int previousStatAttack,
int previousStatBlock,
int cardID,
bool isFightWon,
int heal,
int targetID,
int cardIndex,
int enemyID,
int skillIndex,
int index) :
author(author),
typeCmd(typeCmd),
entityID(entityID),
block(block),
target(target),
buff_AP(buff_AP),
buff_BP(buff_BP),
buff_E(buff_E),
buff_R(buff_R),
buff_H(buff_H),
playerID(playerID),
card(card),
isDeckFull(isDeckFull),
debuff_AM(debuff_AM),
debuff_BM(debuff_BM),
energyAmount(energyAmount),
damage(damage),
entityLife(entityLife),
targetLife(targetLife),
element(element),
previousElement(previousElement),
intent(intent),
previousIntent(previousIntent),
statAttack(statAttack),
statBlock(statBlock),
previousStatAttack(previousStatAttack),
previousStatBlock(previousStatBlock),
cardID(cardID),
isFightWon(isFightWon),
heal(heal),
targetID(targetID),
cardIndex(cardIndex),
enemyID(enemyID),
skillIndex(skillIndex),
index(index){}
