#include "GameCharacter.h"

GameCharacter::GameCharacter():
    Object("","GameCharacter"), currentHealth(0), maxHealth(0), attack(0), defense(0), money(0){}

GameCharacter::GameCharacter(string name, string tag, int hp, int atk, int def, int money):
    Object(name,tag), currentHealth(hp), maxHealth(hp), attack(atk), defense(def), money(money){}

bool GameCharacter::checkIsDead(){
    if(getCurrentHealth()<=0)
        return 1;
    else
        return 0;
}

int GameCharacter::takeDamage(int dmg){
    return this -> currentHealth -= dmg;
} 

void GameCharacter::setCurrentHealth(int hp){
    this -> currentHealth = hp;
}

void GameCharacter::setMaxHealth(int hp){
    this -> maxHealth = hp;
}

void GameCharacter::setAttack(int atk){
    this -> attack = atk;
}

void GameCharacter::setDefense(int def){
    this -> defense = def;
}

void GameCharacter::setMoney(int money) {
    this -> money = money;
}

int GameCharacter::getMaxHealth(){
    return this -> maxHealth;
}

int GameCharacter::getCurrentHealth(){
    return this -> currentHealth;
}

int GameCharacter::getAttack(){
    return this -> attack;
}

int GameCharacter::getDefense(){
    return this -> defense;
}

int GameCharacter::getMoney() {
    return this -> money;
}
