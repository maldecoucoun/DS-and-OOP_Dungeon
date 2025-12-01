#include "Record.h"

/*Record::Record(){}

void Record::savePlayer(Player* player, ofstream& out_player){
    out_player << player -> getName() << endl;
    out_player << player -> getCurrentHealth() << endl;
    out_player << player -> getAttack() << endl;
    out_player << player -> getDefense() << endl;
    out_player << player -> getMoney() << endl;
    out_player << player -> getCurrentRoom() -> getIndex() << endl;
    out_player << player -> getPreviousRoom() -> getIndex() << endl;
    
    out_player << player -> getInventory().size() << endl;
    if(!player -> getInventory().empty()){
        for(auto i: player -> getInventory()){
            saveItem(&i, out_player, true);
        }
    }

    out_player << player -> getPotions().size() << endl;
    if(!player -> getPotions().empty()){
        for(auto i: player -> getPotions()){
        saveItem(&i, out_player, true);
        }
    }
    

    out_player << player->getKeys().size() << endl;
    if(!player -> getKeys().empty()){
        for(auto i: player -> getKeys()){
        saveItem(&i, out_player, true);
        }
    }
    

    if(player -> getHead() != nullptr){
        out_player << "head" << endl;
        saveItem(player -> getHead(), out_player, true);
    } 
    else {
        out_player << "null" << endl;
    }
    if(player -> getBody() != nullptr){
        out_player << "body" << endl;
        saveItem(player -> getBody(), out_player, true);
    } 
    else {
        out_player << "null" << endl;
    }
    if(player -> getLeft() != nullptr){
        out_player << "left" << endl;
        saveItem(player -> getLeft(), out_player, true);
    } 
    else {
        out_player << "null" << endl;
    }
    if(player -> getRight() != nullptr){
        out_player << "right" << endl;
        saveItem(player -> getRight(), out_player, true);
    } 
    else {
        out_player << "null" << endl;
    }    
}

void Record::loadPlayer(Player* player, vector<Room*> &rooms, ifstream& in){
    *player = Player();
    player -> setTag("player");
    string name;
    in.ignore();
    getline(in, name);
        player -> setName(name);
    int maxHealth;
        in >> maxHealth;
        player -> setMaxHealth(maxHealth);
    int currentHealth;
        in >> currentHealth;
        player -> setCurrentHealth(currentHealth);
    int attack;
        in >> attack;
        player -> setAttack(attack);
    int defense;
        in >> defense;
        player -> setDefense(defense);
    int currentRoom;
        in >> currentRoom;
        player -> setCurrentRoom(rooms[currentRoom]);
    int previousRoom;
        in >> previousRoom;
        if(previousRoom != -1){
        player -> setPreviousRoom(rooms[previousRoom]);
        } 
        else {
        player -> setPreviousRoom(nullptr);
        }
    int inventorySize;
        in >> inventorySize;
        for(int i = 0; i < inventorySize; i++){
            Item* item = new Item;
            loadItem(item, in);
            player -> addItem(*item);
        }
    string head;
        in >> head;
        if(head != "null"){
            Item* item = new Item;
            loadItem(item, in);
            player -> increaseStates(-item->getHealth(), -item -> getAttack(), -item -> getDefense(), -item -> getMoney());
            player -> setHead(item);
        }
    string body;
        in >> body;
        if(body != "null"){
            Item* item = new Item;
            loadItem(item, in);
            player -> increaseStates(-item -> getHealth(), -item -> getAttack(), -item -> getDefense(), -item -> getMoney());
            player -> setBody(item);
        }
    string left;
        in >> left;
        if(left != "null"){
            Item* item = new Item;
            loadItem(item, in);
            player -> increaseStates(-item -> getHealth(), -item -> getAttack(), -item -> getDefense(), -item -> getMoney());
            player -> setLeft(item);
        }
    string right;
        in >> right;
        if(right != "null"){
            Item* item = new Item;
            loadItem(item, in);
            player -> increaseStates(-item -> getHealth(), -item -> getAttack(), -item -> getDefense(), -item -> getMoney());
            player -> setRight(item);
        }
    int potionSize;
        in >> potionSize;
        for(int i = 0; i < potionSize; i++){
            Item* item = new Item;
            loadItem(item, in);
            player -> addItem(*item);
        }
    int keySize;
        in >> keySize;
        for(int i = 0; i < keySize; i++){
            Item* item = new Item;
            loadItem(item, in);
            player -> addItem(*item);
        }
}

void Record::saveRooms(vector<Room*>& rooms, ofstream& orooms){
    orooms << rooms.size() << endl;
    for(auto i: rooms){
        orooms << i -> getIndex() << endl;
        orooms << i -> getIsExit() << endl;

        orooms << (i -> getRoomKey() == nullptr ? "null" : i ->getRoomKey() -> getName()) << endl;
        if(i -> getUpRoom() != nullptr){
            orooms << i -> getUpRoom() -> getIndex() << endl;
        }
        else{
            orooms << "null" << endl;
        }
        if(i -> getDownRoom() != nullptr){
            orooms << i -> getDownRoom() -> getIndex() << endl;
        } 
        else{
            orooms << "null" << endl;
        }
        if(i -> getLeftRoom() != nullptr){
            orooms << i -> getLeftRoom() -> getIndex() << endl;
        } 
        else{
            orooms << "null" << endl;
        }
        if(i -> getRightRoom() != nullptr){
            orooms << i -> getRightRoom() -> getIndex() << endl;
        } 
        else{
            orooms << "null" << endl;

        }

        orooms << i -> getObjects().size() << endl;
        for(auto j: i -> getObjects()){
            if(j -> getTag() == "Item"){
                saveItem(dynamic_cast<Item*>(j), orooms, false);
            } 
            else if(j -> getTag() == "Monster"){
                saveMonster(dynamic_cast<Monster*>(j), orooms);
            } 
            else if(j -> getTag() == "NPC"){
                saveNPC(dynamic_cast<NPC*>(j), orooms);
            }
        }
    }
}

void Record::loadRooms(vector<Room*>& rooms, ifstream& in){
    rooms.clear();
    int sz;
    in >> sz;
    vector<int> up_idx(sz, -1);
    vector<int> down_idx(sz, -1);
    vector<int> left_idx(sz, -1);
    vector<int> right_idx(sz, -1);

    for(int i=0; i<sz; i++){
        Room* room = new Room;
        int idx;
            in >> idx;
            room -> setIndex(idx);
        bool isExit;
            in >> isExit;
            room -> setIsExit(isExit);
        string temp;
            in.ignore();
            getline(in, temp);
            if(temp != "null"){
                room->setRoomKey(new Item(temp, "key", 0, 0, 0, 0));
            }
            in >> temp;
            if(temp != "null"){
                up_idx[i] = stoi(temp);
            }
            in >> temp;
            if(temp != "null"){
                down_idx[i] = stoi(temp);
            }
            in >> temp;
            if(temp != "null"){
                left_idx[i] = stoi(temp);
            }
            in >> temp;
            if(temp != "null"){
                right_idx[i] = stoi(temp);
            }
        int objSz;
            in >> objSz;
            for(int j=0;j<objSz;j++){
                string tag;
                in >> tag;
                if(tag == "item"){
                    Item* item = new Item;
                    loadItem(item, in);
                    room -> addObject(item);
                }
                else if(tag == "monster"){
                    Monster* monster = new Monster;
                    loadMonster(monster, in);
                    room -> addObject(monster);
                }
                else if(tag == "npc"){
                    NPC* npc = new NPC;
                    npc->setTag("NPC");
                    loadNPC(npc, in);
                    room -> addObject(npc);
                }
            }
        rooms.push_back(room);
    }
    for(int i=0; i<sz; i++){
        if(up_idx[i] != -1){
            rooms[i] -> setUpRoom(rooms[up_idx[i]]);
        }
        if(down_idx[i] != -1){
            rooms[i] -> setDownRoom(rooms[down_idx[i]]);
        }
        if(left_idx[i] != -1){
            rooms[i] -> setLeftRoom(rooms[left_idx[i]]);
        }
        if(right_idx[i] != -1){
            rooms[i] -> setRightRoom(rooms[right_idx[i]]);
        }
    }
}

void Record::saveItem(Item* item, ofstream& oitem, bool isNPC){
    if(isNPC == false) oitem << "item" << endl;
    oitem << item -> getName() << endl;
    oitem << item -> getType() << endl;
    oitem << item -> getHealth() << endl;
    oitem << item -> getAttack() << endl;
    oitem << item -> getDefense() << endl;
}

void Record::loadItem(Item* item, ifstream& in){
    string name;
        in.ignore();
        getline(in, name);
        item -> setName(name);
    string type;
        in >> type;
        item -> setType(type);
    int health;
        in >> health;
        item -> setHealth(health);
    int attack;
        in >> attack;
        item -> setAttack(attack);
    int defense;
        in >> defense;
        item -> setDefense(defense);
    int money;
        in >> money;
        item -> setMoney(money);
}

void Record::saveMonster(Monster* monster, ofstream& omonster){
    omonster << "monster" << endl;
    omonster << monster -> getName() << endl;
    omonster << monster -> getMaxHealth() << endl;
    omonster << monster -> getCurrentHealth() << endl;
    omonster << monster -> getAttack() << endl;
    omonster << monster -> getDefense() << endl;
}

void Record::loadMonster(Monster* monster, ifstream& in){
    string name;
        in.ignore();
        getline(in, name);
        monster -> setName(name);
    int maxHealth;
        in >> maxHealth;
        monster -> setMaxHealth(maxHealth);
    int currentHealth;
        in >> currentHealth;
        monster -> setCurrentHealth(currentHealth);
    int attack;
        in >> attack;
        monster -> setAttack(attack);
    int defense;
        in >> defense;
        monster -> setDefense(defense);
}

void Record::saveNPC(NPC* npc, ofstream& oNPC){
    oNPC << "npc" << endl;
    oNPC << npc -> getName() << endl;
    oNPC << npc -> getScript() << endl;
    oNPC << "-" << endl;
    oNPC << npc -> getCommodity().size() << endl;
    for(auto i: npc -> getCommodity()){
        saveItem(&i, oNPC, true);
    }
}

void Record::loadNPC(NPC* npc, ifstream& in){
    string name;
        in.ignore();
        getline(in, name);
        npc -> setName(name);
    string script = "";
        while(true){
            string line;
            getline(in, line);
            if(line == "-"){
                break;
            }
            script += line + "\n";
        }
        npc -> setScript(script);
    vector<Item> commodity;
    int size;
        in >> size;
        for(int i = 0; i < size; i++){
            Item item;
            loadItem(&item, in);
            commodity.push_back(item);
        }
        npc -> setCommodity(commodity);
}

void Record::saveToFile(Player* player, vector<Room*>& rooms){
    ofstream out_player("player_record.txt");
    ofstream orooms("rooms_record.txt");
    savePlayer(player,out_player);
    saveRooms(rooms,orooms);
}

void Record::loadFromFile(Player* player, vector<Room*>& rooms){
    ifstream iplayer("player_record.txt");
    ifstream irooms("rooms_record.txt");
    loadPlayer(player, rooms, iplayer);
    loadRooms(rooms,irooms);
    player -> setCurrentRoom(rooms[currentroom]);
    player -> setPreviousRoom(rooms[previousroom]);
}

void Record::saveToFile(Player* player, vector<Room*>& rooms){
    string filename = "record.txt";
    ofstream out;
    out.open(filename);
    saveRooms(rooms, out);
    savePlayer(player, out);
    out.close();
}

void Record::loadFromFile(Player* player, vector<Room*>& rooms){
    string filename = "record.txt";
    ifstream in;
    in.open(filename);
    if(in.fail()){
        cout << "Record file not found." << endl;
        return;
    }
    loadRooms(rooms, in);
    loadPlayer(player, rooms, in);
}*/
