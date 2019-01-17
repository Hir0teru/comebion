#ifndef CommandDB__H
#define CommandDB__H

#include "Cmd.h"

/// class CommandDB -
class CommandDB {
  // Associations
  // Attributes
protected:
  int idseq;
  map<int,unique_ptr<Cmd> > commands;
  // Operations
public:
  CommandDB ();
  const Cmd* getCommand (int id) const;
  int addCommand (unique_ptr<Cmd> command);
  void setCommand (int id, unique_ptr<Cmd> command);
  void removeCommand (int id);
  map<int,unique_ptr<Cmd> >& getCommands();
};

#endif
