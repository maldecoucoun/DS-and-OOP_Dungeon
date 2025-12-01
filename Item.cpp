#include "Item.h"

Item::Item(): Object("", "Item"), health(0), attack(0), defense(0), money(0){}

Item::Item(string name, string ty, int hp, int atk, int def, int money):
    Object(name, "Item"), type(ty), health(hp), attack(atk), defense(def), money(money){}

bool Item::triggerEvent(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    cout << "\nYou've got " << getName() << endl;
    player -> addItem(*this);
    return true;
}

void Item::setHealth(int hp) {
    this->health = hp;
}

void Item::setAttack(int atk) {
    this->attack = atk;
}

void Item::setDefense(int def) {
    this->defense = def;
}

void Item::setMoney(int money) {
    this->money = money;
}

void Item::setType(string ty) {
    this->type = ty;
}


int Item::getHealth(){
    return this -> health;
}

int Item::getAttack(){
    return this -> attack;
}

int Item::getDefense(){
    return this -> defense;
}

int Item::getMoney(){
    return this -> money;
}

string Item::getType(){
    return type;
}

