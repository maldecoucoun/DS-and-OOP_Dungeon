#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

Player::Player():GameCharacter(){}

Player::Player(string name, int health, int attack, int defense, int money):GameCharacter(name, "Player", health, attack, defense, money){
    currentRoom = nullptr;
    previousRoom = nullptr;
}

void Player::addItem(Item newItem){
    string type = newItem.getType();
    if(type == "keys"){
        addKey(newItem);
    } 
    else if(type == "potions") {
        addPotions(newItem);
    } 
    else {
        inventory.push_back(newItem);
    }
}

void Player::increaseStates(int increase_hp, int increase_atk, int increase_def, int increase_money){
    setCurrentHealth(min(getCurrentHealth() + increase_hp, getMaxHealth()));
    setAttack(getAttack() + increase_atk);
    setDefense(getDefense() + increase_def);
}

void Player::changeRoom(Room* current){
    if(current -> getRoomKey() != nullptr){
        bool lock = true;
        for(auto it = keys.begin(); it != keys.end(); it++){
            if(it -> getName() == current -> getRoomKey() -> getName()){
                cout << "You've got the key to enter this room." << endl;
                lock = false;
                break;
            }
        }
        if(lock){
            cout << " You need key " + current -> getRoomKey() -> getName() + " to enter this room." << endl;
            return;
        }
    }
    setPreviousRoom(getCurrentRoom());
    setCurrentRoom(current);
}

bool Player::triggerEvent(Object* object){
    Player* player = dynamic_cast<Player*>(object);
    cout << "\n-------------------Current Status-------------------" << endl;
    cout << "   [Name]  " << getName() << endl;
    cout << "   [Health]  " << getCurrentHealth() << endl;
    cout << "   [Attack]  " << getAttack() << endl;
    cout << "   [Defense]  " << getDefense() << endl;
    cout << "   [Money]  " << getMoney() << endl;

    auto inve = getInventory();
    if(inve.size() != 0){
        cout << "   [Item]  ";
        for(auto i: inve){
            cout << i.getType() << " " << i.getName() << ", ";
        }
        cout << endl;
    }
    cout << "   [Equipment]   " << endl;
    cout << "    >> Head : " << (head == nullptr ? " (empty) " : head -> getName()) << endl;
    cout << "    >> Body : " << (body == nullptr ? " (empty) " : body -> getName()) << endl;
    cout << "    >> Left Arm : " << (left == nullptr ? " (empty) " : left -> getName()) << endl;
    cout << "    >> Right Arm : " << (right == nullptr ? " (empty) " : right -> getName()) << endl;
    cout << "    ------------------------------" << endl;
    cout << "   [Keys]   " << endl;
    int idx = 0;
    for(Item i: keys){
        cout << idx++ << ": " << i.getName() << endl;
    }
    cout << "    ------------------------------" << endl;
    cout << "   [Potions]   " << endl;
    idx = 0;
    for(Item i: potions){
        cout << idx++ << ": " << i.getName() << " ATK: " << i.getAttack() << " HP: " << i.getHealth() << endl;
    }
    cout << "   \nYou're now in  " << currentRoom -> getIndex() << "!" << endl << endl;
    return 1;
}

void Player::setCurrentRoom(Room* currentRoom){
    this -> currentRoom = currentRoom;
}

void Player::setPreviousRoom(Room* previousRoom){
    this -> previousRoom = previousRoom;
}

void Player::setInventory(vector<Item> inventory){
    this -> inventory = inventory;
}

Room* Player::getCurrentRoom(){
    return currentRoom;
}

Room* Player::getPreviousRoom(){
    return previousRoom;
}

vector<Item> Player::getInventory(){
    return inventory;
}

Item* Player::getHead(){
    return head;
}
Item* Player::getLeft(){
    return left;
}
Item* Player::getRight(){
    return right;
}
Item* Player::getBody(){
    return body;
}

vector<Item> Player::getPotions(){
    return potions;
}

vector<Item> Player::getKeys(){
    return keys;
}

void Player::setHead(Item* new_head){
    increaseStates(new_head -> getHealth(), new_head -> getAttack(), new_head -> getDefense(), new_head -> getMoney());
    for(auto it = inventory.begin(); it != inventory.end(); it++){
        if(it->getName() == new_head -> getName()){
            inventory.erase(it);
            break;
        }
    }
    if(head != nullptr){
        increaseStates(-head -> getHealth(), -head -> getAttack(), -head -> getDefense(), -head -> getMoney());
        inventory.push_back(*head);
    }
    head = new_head;
}

void Player::setLeft(Item* new_left){
    increaseStates(new_left -> getHealth(), new_left -> getAttack(), new_left -> getDefense(), new_left -> getMoney());
    for(auto it = inventory.begin(); it != inventory.end(); it++){
        if(it -> getName() == new_left -> getName()){
            inventory.erase(it);
            break;
        }
    }
    if(left != nullptr){
        increaseStates(-left -> getHealth(), -left -> getAttack(), -left -> getDefense(), -left -> getMoney());
        inventory.push_back(*left);
    }
    left = new_left;
}

void Player::setRight(Item* new_right){
    increaseStates(new_right -> getHealth(), new_right -> getAttack(), new_right -> getDefense(), new_right -> getMoney());
    for(auto it = inventory.begin(); it != inventory.end(); it++){
        if(it -> getName() == new_right -> getName()){
            inventory.erase(it);
            break;
        }
    }
    if(right != nullptr){
        increaseStates(-right -> getHealth(), -right -> getAttack(), -right -> getDefense(), -right -> getMoney());
        inventory.push_back(*right);
    }
    right = new_right;
}

void Player::setBody(Item* new_body){
    increaseStates(new_body -> getHealth(), new_body -> getAttack(), new_body -> getDefense(), new_body -> getMoney());
    for(auto it = inventory.begin(); it != inventory.end(); it++){
        if(it -> getName() == new_body -> getName()){
            inventory.erase(it);
            break;
        }
    }
    if(body != nullptr){
        increaseStates(-body -> getHealth(), -body -> getAttack(), -body -> getDefense(), -body -> getMoney());
        inventory.push_back(*body);
    }
    body = new_body;
}

void Player::addKey(Item key){
    keys.push_back(key);
}

void Player::addPotions(Item potion){
    potions.push_back(potion);
}

void Player::equip(){
    while(true){
        cout << "   [Equipment]   " << endl;
        cout << " >> Head : " << (head == nullptr ? " (empty) " : (head -> getName() + " ATK: " + to_string(head -> getAttack()) + " DEF: " + to_string(head -> getDefense()))) << endl;
        cout << " >> Body : " << (body == nullptr ? " (empty) " : (body -> getName() + " ATK: " + to_string(body -> getAttack()) + " DEF: " + to_string(body -> getDefense()))) << endl;
        cout << " >> Left Arm : " << (left == nullptr ? " (empty) " : (left -> getName() + " ATK: " + to_string(left -> getAttack()) + " DEF: " + to_string(left -> getDefense()))) << endl;
        cout << " >> Right Arm : " << (right == nullptr ? " (empty) " : (right -> getName() + " ATK: " + to_string(right -> getAttack()) + " DEF: " + to_string(right -> getDefense()))) << endl;
        char c;
        do{
            cout << " <H>ead" << endl;
            cout << " <B>ody" << endl;
            cout << " <L>eft Arm" << endl;
            cout << " <R>ight Arm" << endl;
            cout << " <E>xit" << endl;
            cout << " Which part do you want to put the equipments on ? >> ";
        } 
        while(cin >> c && (c != 'h' && c != 'H' && c != 'b' && c != 'B' && c != 'l' && c != 'L' && c != 'r' && c != 'R' && c != 'e' && c != 'E'));

        if(c == 'e' || c == 'E') return;

        if(c == 'h' || c == 'H'){
            cout << " >> Head : " << (head == nullptr ? " (empty) " : (head -> getName() + " ATK: " + to_string(head -> getAttack()) + " DEF: " + to_string(head -> getDefense()))) << endl;
            cout << " Inventory : " << endl;
            int idx = 0;
            vector<Item> rep;
            for(Item i: inventory){
                if(i.getType() == "head" ){
                    cout << " >> " << idx ++ << ": "<< i.getName() + " ATK: " + to_string(i.getAttack()) + " DEF: " + to_string(i.getDefense()) << endl;
                    rep.push_back(i);
                }
            }
            idx = -1;
            do{
                if(idx >= 0 && idx < (int)rep.size()){
                    Item* newed = new Item(rep[idx]);
                    setHead(newed);
                    break;
                }
                cout << "Which equipment do you want to put on ? ...(Enter -1 to leave) >> ";
            } 
            while(cin >> idx && idx != -1);            
        } 
        else if(c == 'b' || c == 'B'){
            cout << " >> Body : " << (body == nullptr ? " (empty) " : (body -> getName() + " ATK: " + to_string(body -> getAttack()) + " DEF: " + to_string(body -> getDefense()))) << endl;
            cout << "Inventory : " << endl;
            int idx = 0;
            vector<Item> rep;
            for(Item i: inventory){
                if(i.getType() == "body"){
                    cout << " >> " << idx ++ << ": "<< i.getName() + " ATK: " + to_string(i.getAttack()) + " DEF: " + to_string(i.getDefense()) << endl;
                    rep.push_back(i);
                }
            }
            idx = -1;
            do{
                if(idx >= 0 && idx < (int)rep.size()){
                    Item* newed = new Item(rep[idx]);
                    setBody(newed);
                    break;
                }
                cout << "Which equipment do you want to put on ? ...(Enter -1 to leave) >> ";
            } 
            while(cin >> idx && idx != -1);

        } 
        else if(c == 'l' || c == 'L'){
            cout << " >> Left Arm: " << (left == nullptr ? " (empty) " : (left -> getName() + " ATK: " + to_string(left -> getAttack()) + " DEF: " + to_string(left -> getDefense()))) << endl;
            cout << "Inventory : " << endl;
            int idx = 0;
            vector<Item> rep;
            for(Item i: inventory){
                if(i.getType() == "left"){
                    cout << " >> " << idx ++ << ": "<< i.getName() + " ATK: " + to_string(i.getAttack()) + " DEF: " + to_string(i.getDefense()) << endl;
                    rep.push_back(i);
                }
            }
            idx = -1;
            do{
                if(idx >= 0 && idx < (int)rep.size()){
                    Item* newed = new Item(rep[idx]);
                    setLeft(newed);
                    break;
                }
                cout << "Which equipment do you want to put on ? ...(Enter -1 to leave) >> ";
            }
            while(cin >> idx && idx != -1);
        } 
        else if(c == 'r' || c == 'R'){
            cout << " >> Right Arm: " << (right == nullptr ? " (empty) " : (right -> getName() + " ATK: " + to_string(right -> getAttack()) + " DEF: " + to_string(right -> getDefense()))) << endl;
            cout << "Inventory : " << endl;
            int idx = 0;
            vector<Item> rep;
            for(Item i: inventory){
                if(i.getType() == "right"){
                    cout << " >> " << idx ++ << ": "<< i.getName() + " ATK: " + to_string(i.getAttack()) + " DEF: " + to_string(i.getDefense()) << endl;
                    rep.push_back(i);
                }
            }
            idx = -1;
            do{
                if(idx >= 0 && idx < (int)rep.size()){
                    Item* newed = new Item(rep[idx]);
                    setRight(newed);
                    break;
                }
                cout << "Which equipment do you want to put on ? ...(Enter -1 to leave) >> ";
            }
            while(cin >> idx && idx != -1);
        }    
    }
}

void Player::popKey(Item key){
    for(auto it = keys.begin(); it != keys.end(); ++it){
        if(key.getName() == it -> getName()){
            keys.erase(it);
            break;
        }
    }
}

void Player::popPotions(Item potion){
    for(auto it = potions.begin(); it != potions.end(); ++it){
        if(potion.getName() == it -> getName()){
            potions.erase(it);
            break;
        }
    }
}

void Player::useHealPotion(Item potion){
    increaseStates(potion.getHealth(), 0, 0, 0);
}