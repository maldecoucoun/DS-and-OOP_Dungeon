#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item: public Object
{
private:
    int health, attack, defense, money;
    string type;
public:
    Item();
    Item(string, string, int, int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getMoney();
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setMoney(int);
    string getType();
    void setType(string);
};

#endif // ITEM_H_INCLUDED
