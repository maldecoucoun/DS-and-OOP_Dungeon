#include "NPC.h"

NPC::NPC():GameCharacter(){}

NPC::NPC(string name, string script, vector<Item> commodity):
    GameCharacter(name, " <NPC> ", 0, 0, 0, 0){
        this -> script = script;
        this -> commodity = commodity;
    }

void NPC::listCommodity(){
    int idx = 0;
    for(auto i: this->commodity){
        cout << idx++ << ": " << i.getType() << " " << i.getName() << endl;
        cout << " HP: " << i.getHealth() << endl;
        cout << " ATK: " << i.getAttack() << endl;
        cout << " DEF: " << i.getDefense() << endl;
        cout << "MONEY: " << i.getMoney() << endl;
    }
}

bool NPC::triggerEvent(Object* object) {

    Player* player = dynamic_cast<Player*>(object);
    cout << getScript() << endl;
    
    int idx = -1;
    do{
        if(0 <= idx && idx < (int)commodity.size()){
            commodity[idx].triggerEvent(player);
            commodity.erase(commodity.begin()+idx);
        }
        cout << "I have some uesful things. Do you want anything?" << endl;
        cout << "------ --------- ITEM --------- ------" << endl;
        listCommodity();
        cout << "--------------------------------------" << endl;

        cout << "Enter the index of wanted item (Enter -1 for quitting): ";
    } while(cin >> idx && idx != -1);

    return true;
}

void NPC::setScript(string script){
    this -> script = script;
}

void NPC::setCommodity(vector<Item> commodity){
    this -> commodity = commodity;
}

string NPC::getScript(){
    return this -> script;
}

vector<Item> NPC::getCommodity(){
    return this -> commodity;
}