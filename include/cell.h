#pragma once

#include <cfloat>
#include <iostream>
#include <string>

using namespace std;

class Cell
{
private:
  int parent_x_;
  int parent_y_;
  double g_;
  double h_;
  double f_;
  bool obstacle_;
  bool is_entry_;
  bool is_exit_;
  string emoji_;
  
public:
  Cell() {
    parent_x_ = -1;
    parent_y_ = -1;
    g_ = FLT_MAX;
    h_ = FLT_MAX;
    f_ = FLT_MAX;
    obstacle_ = false;
    is_entry_ = false;
    is_exit_  = false;
    emoji_ = "⬜";
  };

  int GetParentActualX();
  int GetParentActualY();

  double GetG();
  double GetF();
  double GetH();
  bool isEntry();
  bool isExit();
  bool isObstacle();
  string GetEmoji();

  void SetParentActualX(int new_parent_i);
  void SetParentActualY(int new_parent_j);
  void SetG(double new_g);
  void SetF(double new_f);
  void SetH(double new_h);
  void SetObstacle(bool new_obstacle);
  void SetEntry();
  void SetExit();
  void SetCellInPath();
};