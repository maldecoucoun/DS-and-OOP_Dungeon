#include "Dungeon.h"

bool Dungeon::unfin = true;

Dungeon::Dungeon() {}
    //Record record;

void Dungeon::startGame(){
    createPlayer();
    createMap();
    player.triggerEvent(&player);
}

void Dungeon::runDungeon(){
    startGame();
    while (unfin){
         chooseAction(player.getCurrentRoom()->getObjects());
    }
}

void Dungeon::createPlayer(){
    string name;
    char ans;
    cout << "\nHello. What's your name? : ";
    cin >> name;
    cout << "\nWelcome to Hogwarts, " << name << ".\n" << endl;
    cout << "Okay...Let's see..." << name << ". Which personality trait do you consider fits you the best? \n" << endl;    
    cout << "Enter the index of the charcter you want to interact:\n" << endl;
    cout << "<B>ravery " << endl;
    cout << "<I>ntelligence " << endl;
    cout << "<E>mpathy " << endl;
    cout << "<A>mbition " << endl;    
    cin >> ans;
    cout << endl;
    switch(ans){
        case 'b': case 'B':
            player = Player(name, 90, 120, 100, 70);
            cout << name << " Welcome to ...Gryffindor ! \n\n" << endl;
            break;
        case 'i': case 'I':
            player = Player(name, 90, 110, 105, 80);
            cout << name << " Welcome to ...Ravenclaw ! \n\n" << endl;
            break;
        case 'e': case 'E':
            player = Player(name, 100, 95, 90, 70);
            cout << name << " Welcome to ...Hufflepuff ! \n\n" << endl;
            break;
        case 'a': case 'A':
            player = Player(name, 90, 105, 110, 80);
            cout << name << " Welcome to ...Slytherin ! \n\n" << endl;
            break;
    }
    
        
}

void Dungeon::handleEvent(Object* object){
    if(object -> triggerEvent(&player)){
        return;
    } else {
        exit(0);
    }
}

void Dungeon::handleMovement(){
    map<char, Room*> moveRoom;
    if(    player.getCurrentRoom() -> getUpRoom() != nullptr
        || player.getCurrentRoom() -> getDownRoom() != nullptr
        || player.getCurrentRoom() -> getLeftRoom() != nullptr
        || player.getCurrentRoom() -> getRightRoom() != nullptr)
    {
        if(player.getCurrentRoom() -> getUpRoom() != nullptr){
            moveRoom['U'] = moveRoom['u'] = player.getCurrentRoom() -> getUpRoom();
            cout << "<U>p Room" << endl;
        }
        if(player.getCurrentRoom() -> getDownRoom() != nullptr){
            moveRoom['D'] = moveRoom['d'] = player.getCurrentRoom() -> getDownRoom();
            cout << "<D>own Room" << endl;
        }
        if(player.getCurrentRoom() -> getLeftRoom() != nullptr){
            moveRoom['L'] = moveRoom['l'] = player.getCurrentRoom() -> getLeftRoom();
            cout << "<L>eft Room" << endl;
        }
        if(player.getCurrentRoom() -> getRightRoom() != nullptr){
            moveRoom['R'] = moveRoom['r'] = player.getCurrentRoom() -> getRightRoom();
            cout << "<R>ight Room" << endl;
        }
        if(player.getCurrentRoom() -> getIsExit() == true){
            moveRoom['E'] = moveRoom['e'] = nullptr;
            cout << "<E>xit" << endl;
        }
        char c;
        do{
            cout << " Where do you want to go? ";
        } while(cin >> c && moveRoom.find(c) == moveRoom.end());
        if(c == 'E' || c == 'e'){
            cout << "Hey, Congrats!" << player.getName() << ", you have exited Hogwarts." << endl;
            exit(0);
        } else {
            player.changeRoom(moveRoom[c]);
        }
    } else {
        cout << "Back off! You can't go this way!" << endl;
    }
    return;
}

void Dungeon::createMap(){
    /*int room_num = 8;
    vector<Room> rooms;
    vector<Object*> obj0, obj1, obj2, obj3, obj4, obj5, obj6, obj7;
    vector<Item> item1;
    for(int index = 0 ; index <= room_num ; index++){
        Room temp;
        temp.setIndex(index);
        rooms.push_back(temp);
    }*/

    Monster* Tom = new Monster("Tom Riddle", 80, 130, 100, 0);
    Tom -> setIsBoss(true);
    Monster* Nagini = new Monster("Nagini", 50, 110, 90, 0);

    NPC* Dumb = new NPC("Dumbledore", "  Welcome to a new year at Hogwarts. \n  This present may help you get over the adventures in your school years.", vector<Item>{Item("The Sorting Hat", "head", 0, 0, 5, 0)});
    NPC* Lupin = new NPC("L.Lupin", "  Welcome to Defence Against the Dark Arts.\n  These things might help you. Take them with you. ", vector<Item>{Item("Patronum", "body", 0, 0, 5, 0)});
    NPC* Snape = new NPC("S.Snape", "  This lecture is dangerous. \n  Don't fool around. Don't leave your manners at home. \n  Come take away these things and try your best to stay alive.", vector<Item>{Item("Sectumsempra", "right", 0, 15, 0, 0)});
    //NPC* Harry = new NPC("Harry Potter", " Just call me Harry. It seems that you need some help! Catch this! ", vector<Item>{Item(" Magic ", "right", 0, 5, 0, 0)});
    NPC* Newt = new NPC("Newt", "   ...I'm Newt...\n  Ummm...Sorry...Can you help me hold these? \n  Nevermind...you can have them... ", vector<Item>{Item("Silver Eggs", "potions", 0, 20, 0, 0)});
    NPC* Draco = new NPC("Draco Malfoy", "  Draco Malfoy. Nice to meet you.\n  Why are you wondering around like a fool?\n  Hey, you dropped this. ", vector<Item>{Item("Wand", "left", 0, 0, 5, 0)});
    NPC* Borgin = new NPC("Mr. Borgin", "   I have everything you want...\n   If only you have enough money... ", vector<Item>{Item("Slytherin", "keys", 0, 0, 0, -50)});

    Room* hall = new Room(false, 0, vector<Object*>{Dumb, new Item("Magic", "left", 0, 1, 0, 0)});
    Room* classRoomA = new Room(false, 1, vector<Object*>{Lupin});
    Room* forbiddenForest = new Room(false, 2, vector<Object*>{Nagini});
    Room* KnucleturnAlley = new Room(false, 3, vector<Object*>{Borgin, new Item("DarkFire", "potions", 0, 15, 0, 0)});
    Room* DiagonAlley = new Room(false, 4, vector<Object*>{Newt, new Item("Suitcase", "body", 0, 5, 0, 0)});
    Room* classRoomB = new Room(false, 5, vector<Object*>{Snape, new Item("Heal potion", "potions", 5, 0, 0, 0)});
    Room* MalfoyCastle = new Room(false, 6, vector<Object*>{Draco});
    //Room* PrivetDrive = new Room(false, 7, vector<Object*>{Dumb, new Item("Magic", "potion", 0, 1, 0, 0)});
    Room* guntTomb = new Room(false, 7, vector<Object*>{Tom});

    //MalfoyCastle -> setRoomKey(new Item("Slytherin", "keys", 0, 0, 0, -60));

    hall->setUpRoom(DiagonAlley);
    hall->setDownRoom(KnucleturnAlley);
    hall->setLeftRoom(classRoomB);
    hall->setRightRoom(classRoomA);

    classRoomA->setLeftRoom(hall);
    classRoomA->setRightRoom(forbiddenForest);

    forbiddenForest->setLeftRoom(classRoomA);

    KnucleturnAlley->setUpRoom(hall);

    DiagonAlley->setDownRoom(hall);

    classRoomB->setRightRoom(hall);
    classRoomB->setUpRoom(MalfoyCastle);

    MalfoyCastle->setDownRoom(classRoomB);
    MalfoyCastle->setLeftRoom(guntTomb);

    guntTomb->setRightRoom(MalfoyCastle);

    rooms.push_back(hall);
    rooms.push_back(classRoomA);
    rooms.push_back(forbiddenForest);
    rooms.push_back(KnucleturnAlley);
    rooms.push_back(DiagonAlley);
    rooms.push_back(classRoomB);
    rooms.push_back(MalfoyCastle);
    rooms.push_back(guntTomb);

    player.setCurrentRoom(hall);
}

void Dungeon::chooseAction(vector<Object*> objects){
    int idx = 0;
    for(int i = 0; i < (int)objects.size(); i++){
        if(objects[i] -> getTag() == "Monster"){
            handleEvent(objects[i]);
            return;
        }
    }
    cout << "------------------- ROOM -------------------\n\n" << endl;
    
    for(int i = 0; i < (int)objects.size(); i++){
        cout << idx ++ << ": " << (objects[i] -> getTag() == "Item" ? dynamic_cast<Item*>(objects[i]) -> getType() : objects[i] -> getTag()) << " " << objects[i] -> getName() << endl;
    }
    cout << "--------------------------------------------" << endl;
    cout << "<M>ove" << endl;
    cout << "<S>tatus" << endl;
    cout << "<E>quipment" << endl;
    cout << "<P>otions" << endl;
    //cout << "<C>reate Record" << endl;
    //cout << "<L>oad Record" << endl;
    cout << "<Q>uit" << endl;
    char c;
    do{
        cout << "What do you want to do now ? ";
    } while(cin >> c && !(('0' <= c && c < '0'+(int)objects.size())
        || c == 'M' || c == 'm' || c == 'S' || c == 's' || c == 'E' || c == 'e' || c == 'P' || c == 'p' || c == 'C' || c == 'c' || c == 'L' || c == 'l' || c == 'Q' || c == 'q'));   
    if(c == 'M' || c == 'm'){
        handleMovement();
    } else if(c == 'S' || c == 's'){
        player.triggerEvent(&player);
    } else if(c == 'E' || c == 'e'){
        player.equip();
    } else if(c == 'P' || c == 'p') {
        int inp = -2;
        do {
            int sz = player.getPotions().size();
            if(0 <= inp && inp < sz){
                player.useHealPotion(player.getPotions()[inp]);
                player.popPotions(player.getPotions()[inp]);
            }
            int idx = 0;
            for(auto i: player.getPotions()){
                if(i.getHealth() != 0){
                    cout << idx << ": " << i.getName() << " HP: " << i.getHealth() << endl;
                }
                idx ++;
            }
            cout << "Which potions you want to use (-1 for quit) > ";
        } while(cin >> inp && inp != -1);
    /*} else if(c == 'C' || c == 'c'){
        record.saveToFile(&player, rooms);
    } else if(c == 'L' || c == 'l') {
        record.loadFromFile(&player, rooms);*/
    } else if(c == 'Q' || c == 'q'){
        exit(0);
    } else {
        handleEvent(objects[c-'0']);
        if(objects[c-'0'] -> getTag() == "Item"){
            player.getCurrentRoom() -> popObject(objects[c-'0']);
        }
    }
}

bool Dungeon::checkGameLogic(){
    if(player.getCurrentHealth()<=0)
        return false;
    else
        return true;
}
