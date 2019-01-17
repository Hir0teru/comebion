#ifndef Cmd__H
#define Cmd__H

#include <stdlib.h>
#include <stdio.h>
#include <string>
/// class Cmd -
class Cmd {
  // Attributes
public:
  int author;
  std::string typeCmd;
  int entityID;
  int block;
  int target;
  int buff_AP;
  int buff_BP;
  int buff_E;
  int buff_R;
  int buff_H;
  int playerID;
  int card;
  bool isDeckFull;
  int debuff_AM;
  int debuff_BM;
  int energyAmount;
  int damage;
  int entityLife;
  int targetLife;
  int element;
  int previousElement;
  int intent;
  int previousIntent;
  int statAttack;
  int statBlock;
  int previousStatAttack;
  int previousStatBlock;
  int cardID;
  bool isFightWon;
  int heal;
  int targetID;
  int cardIndex;
  int enemyID;
  int skillIndex;
  int index;
  // Operations
public:
  Cmd  (int author,
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
  int index) ;
};

#endif
