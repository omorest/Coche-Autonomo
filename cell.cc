#include "cell.h"

int Cell::GetParentActualX()
{
    return parent_x_;
}

int Cell::GetParentActualY()
{
    return parent_y_;
}

double Cell::GetG()
{
    return g_;
}

double Cell::GetF()
{
    return f_;
}

double Cell::GetH()
{
    return h_;
}

void Cell::SetParentActualX(int new_parent_i)
{
    parent_x_ = new_parent_i;
}

void Cell::SetParentActualY(int new_parent_j)
{
    parent_y_ = new_parent_j;
}

void Cell::SetG(double new_g)
{
    g_ = new_g;
}

void Cell::SetF(double new_f)
{
    f_ = new_f;
}

void Cell::SetH(double new_h)
{
    h_ = new_h;
}



bool Cell::isObstacle() {
    return obstacle_;
}


void Cell::SetObstacle(bool new_obstacle) {
    obstacle_ = new_obstacle;
    emoji_    = "🚧";
}


string Cell::GetEmoji() {
    return emoji_;
}
