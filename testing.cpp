#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cctype>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <array>
#include <map>


//using std::assign;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::tolower;
using std::transform;
using std::istringstream;
using std::ostringstream;
using std::ostream;
using std::invalid_argument;
using std::sort;
using std::stringstream;
using std::getline;
using std::end;
using std::begin;
using std::array;
//using std::size;

class GameState 
{
  public:
    GameState() = default;
    int NumPieces();
    int NumPieces(string);
    int NumPieces(string, string);
    std::map<string,vector<int>> how_many_;
    void AddPiece(const string &, const string &) ;
    void RemovePiece(const string &, const string &) ;
};

class GamePiece 
{
  private:
    string name_;
    string piece_;
    GameState *game_;
  public:
    GamePiece(string, string, GameState*);
    GamePiece(const GamePiece &);
    ~GamePiece();
    void ClassAdd(GameState *);
    void ClassSub(GameState *);
    string GetPlayer() const;
    string GetType() const;
    int GetPower() const;
    int GetSpeed() const;

    bool operator==(const GamePiece &one) const;
    bool operator<=(const GamePiece &one) const;
    bool operator>=(const GamePiece &one) const;
    bool operator!=(const GamePiece &one) const;
    bool operator<(const GamePiece &one) const;
    bool operator>(const GamePiece &one) const;
    GamePiece &operator=(const GamePiece &one); 
    friend ostream& operator<<(ostream& os, const GamePiece &imp);
};

int GameState::NumPieces()
{
  int total = 0;
  for(auto it = how_many_.begin(); it != how_many_.end(); it++)
  {
    for(int i = 0; i < it->second.size(); i++)
      total += how_many_[it->first][i];
  }
  return total;
}

int GameState::NumPieces(string name)
{
  int total = 0;
  for(int i = 0; i < how_many_[name].size(); i++)
    total += how_many_.at(name)[i];
  return total;
}

int GameState::NumPieces(string name, string type)
{
  if(how_many_.find(name) == how_many_.end())
  {
    return 0;
  }
  else 
  {
    if(type == "Warrior")
      return how_many_[name][0];
    else if(type == "Scout")
      return how_many_[name][1];
    else if(type == "Wizard")
      return how_many_[name][2];
    else
      return 0;
  }
}

void GameState::AddPiece(const string &name_, const string & piece_) {
    if(piece_ == "Warrior")
    {
     how_many_[name_][0] += 1;
    }
    else if(piece_ == "Scout")
    {
    how_many_[name_][1] += 1;
    }
    else
    {
    how_many_[name_][2] += 1;
    }
}

void GameState::RemovePiece(const string &name_, const string & piece_) {
    if(piece_ == "Warrior")
    {
      how_many_[name_][0] -= 1;
    }
    else if(piece_ == "Scout")
    {
      how_many_[name_][1] -= 1;
    }
    else
    {
      how_many_[name_][2] -= 1;
    }
}

void GamePiece::ClassSub(GameState *game)
{
  if(piece_ == "Warrior")
    {
      game->how_many_[name_][0] -= 1;
    }
    else if(piece_ == "Scout")
    {
      game->how_many_[name_][1] -= 1;
    }
    else
    {
      game->how_many_[name_][2] -= 1;
    }
}

void GamePiece::ClassAdd(GameState *game)
{
  //*game -> how_many_;
  if (game->how_many_.size() == 0)
  {
    game->how_many_[name_] = {0,0,0};
  }
  if(game->how_many_[name_].empty() == true)
  {
    game->how_many_[name_] = {0,0,0};
  }
  if(piece_ == "Warrior")
  {
    game->how_many_[name_][0] += 1;
  }
  else if(piece_ == "Scout")
  {
    game->how_many_[name_][1] += 1;
  }
  else
  {
    game->how_many_[name_][2] += 1;
  }
}



GamePiece::GamePiece(string name, string piece, GameState *game)
{
  name_ = name;
  piece_ = piece;
  game_ = game;
  ClassAdd(game);
}

GamePiece::GamePiece(const GamePiece &p)
{
  name_ = p.name_;
  piece_ = p.piece_;
  game_ = p.game_;
  ClassAdd(game_);
}

GamePiece::~GamePiece()
{
  ClassSub(game_);
}

string GamePiece::GetPlayer() const
{
  return name_;
}

string GamePiece::GetType() const
{
  return piece_;
}

int GamePiece::GetPower() const
{
  if(piece_ == "Warrior")
  {
    return 5;
  }
  else if (piece_ == "Scout")
  {
    return 1;
  }
  else if(piece_ == "Wizard")
  {
    return game_->how_many_[name_][2];
  }
  else
    return 0;
}

int GamePiece::GetSpeed() const
{
  if(piece_ == "Warrior")
  {
    return 2;
  }
  else if (piece_ == "Scout")
  {
    return 8;
  }
  else if(piece_ == "Wizard")
  {
    int totalwiz = 0;
    for(auto it = game_->how_many_.begin(); it != game_->how_many_.end(); ++it)
    {
      if(it-> first != name_)
      {
        totalwiz += it -> second[2];
      }
    }
    if(12 - totalwiz <= 0)
      return 1;
    else
      return(12 - totalwiz);
    }
}

bool GamePiece::operator==(const GamePiece &one) const
{
  if(one.GetPower() == GetPower() && one.GetSpeed() == GetSpeed())
  {
    return true;
  }
  return false;
}

bool GamePiece::operator>=(const GamePiece &one) const
{
  if(one.GetPower() < GetPower())
    return true;
  else if (one.GetPower() == GetPower() && one.GetSpeed()  < GetSpeed())
    return true;
  else if (one.GetPower() == GetPower() && one.GetSpeed()  == GetSpeed())
    return true;
  return false;
}
bool GamePiece::operator<=(const GamePiece &one) const
{
  if(one.GetPower() > GetPower())
    return true;
  else if (one.GetPower() == GetPower() && one.GetSpeed() > GetSpeed())
    return true;
  else if (one.GetPower() == GetPower() && one.GetSpeed() == GetSpeed())
    return true;
  return false;
}

bool GamePiece::operator!=(const GamePiece &one) const
{
  if(one.GetPower() == GetPower() && one.GetSpeed() == GetSpeed())
    return false;
  return true;
}

bool GamePiece::operator>(const GamePiece &one) const
{
  if(one.GetPower() < GetPower())
    return true;
  else if (one.GetPower() == GetPower() && one.GetSpeed() < GetSpeed())
    return true;
  return false;
}

bool GamePiece::operator<(const GamePiece &one) const
{
  if(one.GetPower() > GetPower())
    return true;
  else if (one.GetPower() == GetPower() && one.GetSpeed() > GetSpeed())
    return true;
  return false;
}

GamePiece& GamePiece::operator=(const GamePiece &one)
{
  game_ -> RemovePiece(name_, piece_);
  name_ = one.name_;
  piece_ = one.piece_;
  game_ = one.game_;
  game_ -> AddPiece(name_, piece_);
  return *this;
}

ostream& operator<<(ostream& os, const GamePiece &imp)
{
  os << "(" << imp.name_ <<"," << imp.piece_ << "," << imp.GetPower() << "," << imp.GetSpeed() << ")";
  return os;
}

int main()
{
    GameState state;

    GamePiece base_warrior("Base", "Warrior", &state);
    GamePiece base_scout("Base", "Scout", &state);
    GamePiece base_wizard("Base", "Wizard", &state);

    GamePiece extra1(base_warrior);
    GamePiece extra2(base_warrior);
    GamePiece extra3(base_warrior);

    cout <<state.NumPieces() << " 1" << endl;
    extra1 = base_wizard;
    cout <<base_wizard.GetPower() << " 2" << endl;
    extra2 = base_wizard;
    extra3 = extra1;
    cout <<base_wizard.GetPower() << " 4" << endl;
    extra2 = base_scout;
    cout <<base_wizard.GetPower() << " 3" << endl;
    extra3 = extra2;
    extra1 = base_warrior;
    cout <<base_wizard.GetPower() << " 3" << endl;
}