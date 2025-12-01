#include "Monster.h"


int calculateDamage(int atk, int def) {
    return atk * atk / (atk + def);
}

bool Monster::getIsBoss() {
    return isBoss;
}

void Monster::setIsBoss(int _isBoss) {
    isBoss = _isBoss;
}

Monster::Monster():GameCharacter("", "Monster", 0, 0, 0, 0), isBoss(false){}

Monster::Monster(string name, int maxHealth, int attack, int defense, int money):
    GameCharacter(name, " <Enemy> ", maxHealth, attack, defense, 0), isBoss(false){}

bool Monster::triggerEvent(Object* object){
    char ans;
    Player* player = dynamic_cast<Player*> (object);
    player -> triggerEvent(player);
    cout << "<" << getName() << ">" << endl;
    cout << " Health = " << getCurrentHealth() << endl;
    cout << " Attack = " << getAttack() <<endl;
    cout << " Defense = " << getDefense() << endl;
    int player_dmg = calculateDamage(player -> getAttack(), getDefense());
    int monster_dmg = calculateDamage(getAttack(), player -> getDefense());
    while(1){
        cout << " What do you prefer to do right now? " << endl;
        cout << " <C>heck my status" << endl;
        cout << " <A>ttack the enemy " << endl;
        cout << " <R>etreat to previous room" << endl;
        cout << " <P>otion " << endl;
        cin >> ans;
        cout << endl;
        if(ans == 'c' ||ans == 'C'){
            player -> triggerEvent(player);
            cout <<  endl ;
            continue;
        }
        else if(ans == 'a' || ans == 'A'){
            cout << " Student " << player -> getName() << " deals " << player_dmg << " damages to Enemy " << getName() << endl;
            setCurrentHealth(getCurrentHealth() - player_dmg);
            if (getCurrentHealth() <= 0) {
                cout << " Enemy " << getName() << " has been killed." << endl;
                player -> getCurrentRoom() -> popObject(this);
                return true;
            }
            cout << " Enemy " << getName() << " deals " << monster_dmg << " damages to Student " << player -> getName() << endl;
            player -> setCurrentHealth(player -> getCurrentHealth() - monster_dmg);
            if (player -> getCurrentHealth() <= 0) {
                cout << " Student " << player -> getName() << " is dead." << endl;
                return false;
            }
        }
        else if(ans == 'r' || ans == 'R'){
            player -> changeRoom(player -> getPreviousRoom());
            cout << endl;
            return true;
        }
        else if(ans == 'p' || ans == 'P'){
            int idx = -2;
            do {
                if(0 <= idx && idx < player -> getPotions().size()){
                    auto potion = player -> getPotions()[idx];
                    auto atk = potion.getAttack();
                    auto hp = potion.getHealth();
                    auto money = potion.getMoney();
                    if(atk != 0){
                        cout << "Player " << player -> getName() << " using " << potion.getName()
                        << " to deal " << atk
                        << " damages to Enemy " << getName() << endl;
                        setCurrentHealth(getCurrentHealth() - atk);
                        if(getCurrentHealth() <= 0){
                            cout << " Enemy " << getName() << " has been killed." << endl; 
                            player -> getCurrentRoom() -> popObject(this);
                            return true;
                        }
                    }
                    else if(hp != 0){
                        player -> setCurrentHealth(player -> getCurrentHealth() + hp);
                        if(player -> getCurrentHealth() > player -> getMaxHealth()){
                            player -> setCurrentHealth(player -> getMaxHealth());
                        }
                    }
                    else if (money != 0) {
                        player->setMoney(player->getMoney() + money);
                    }
                    player -> popPotions(potion);
                }
                int sz = player -> getPotions().size();
                for(int i = 0; i < sz; i++){
                    auto potion = player -> getPotions()[i];
                    auto atk = potion.getAttack();
                    auto hp = potion.getHealth();
                    auto money = potion.getMoney();
                    cout << i << ": " << (potion.getName()) << " ";
                    if(atk != 0){
                        cout << "ATK: " << atk << " ";
                    }
                    if(hp != 0){
                        cout << "HP: " << hp << " ";
                    }
                    if (money != 0) {
                        cout << "Money: " << money << " ";
                    }
                    cout << endl;
                }
                cout << "Which potions do you prefer to use ? ...(-1 to quit) > ";
            } while(cin >> idx && idx != -1);
        }
        else {
            cout << " Wrong input!" << endl;
        }
        cout << "(R)ETREAT" << endl;
        cout << "(A)TTACK" << endl;
        cout << "(S)TATUS" << endl;
        cout << "(P)otion" << endl;
        cout << "What do you want to do? > "; 
    } while(cin >> ans);
}