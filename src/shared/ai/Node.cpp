#include "Node.h"
#include "state.h"
#include <iostream>

using namespace ai;



Node::Node (){
  card_index = -1;
  target = 0;
  to_play = 0;
}

Node::Node (int card_index, int target, std::vector<std::shared_ptr<Node>> next_cards){
  this -> card_index = card_index;

  this -> target = target;

  this -> next_cards = next_cards;

  to_play = false;
}
Node::~Node (){

}
void Node::Display (int depth){
  if(next_cards.size() == 0){
    std::cout << "prof: " << depth<< " index " << card_index << " , target " << target <<std::endl;
  }
  else{
    std::cout << "sons:" <<std::endl;
    for (auto node : next_cards){
      node -> Display(depth + 1);
    }
    std::cout << "father prof: " <<depth << " index " << card_index << " , target " << target <<std::endl;
  }
}
int Node::GetCardIndex (){
  return card_index;
}
int Node::GetTarget (){
  return target;
}
std::vector<std::shared_ptr<Node>> Node::GetNextCards (){
  return next_cards;
}

bool Node::GetToPlay(){
  return to_play;
}

void Node::SetToPlay(bool to_play){
  this -> to_play = to_play;
}
