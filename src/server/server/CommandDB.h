#ifndef CommandDB__H
#define CommandDB__H

#include "Cmd.h"
#include <vector>

/// class CommandDB -
class CommandDB {
  // Associations
  // Attributes
protected:
  int idseq;
  std::vector<unique_ptr<Cmd> > commandsJ1;
  std::vector<unique_ptr<Cmd> > commandsJ2;

  // Operations
public:
  CommandDB ();
  // std::vector <Cmd*> getCommand (int id) const;
  int addCommand (unique_ptr<Cmd> command);
  void setCommand (int id, unique_ptr<Cmd> command);
  void removeCommand (int id);
  void removeCommands(int id);
  std::vector<unique_ptr<Cmd> >& getCommands(int id);
};

#endif
