#pragma once

#include <cfloat>

class Cell
{
private:
  int parent_x_;
  int parent_y_;
  double g_;
  double h_;
  double f_;
  bool obstacle_;

public:
  Cell()
  {
    parent_x_ = -1;
    parent_y_ = -1;
    g_ = FLT_MAX;
    h_ = FLT_MAX;
    f_ = FLT_MAX;
    obstacle_ = false;
  };

  int GetParentActualX();
  int GetParentActualY();

  double GetG();
  double GetF();
  double GetH();
  bool isObstacle();

  void SetParentActualX(int new_parent_i);
  void SetParentActualY(int new_parent_j);
  void SetG(double new_g);
  void SetF(double new_f);
  void SetH(double new_h);
  void SetObstacle(bool new_obstacle);
};