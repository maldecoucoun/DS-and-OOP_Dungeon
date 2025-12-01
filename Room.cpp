#include "Room.h"

Room::Room() {}
Room::Room(bool isExit,int index,vector<Object*> objects){
    this -> isExit = isExit;
    this -> index = index;
    this -> objects = objects;
    this -> upRoom = nullptr;
    this -> downRoom = nullptr;
    this -> leftRoom = nullptr;
    this -> rightRoom = nullptr;
}

bool Room::popObject(Object* obj){
    for(int i = 0; i < objects.size(); i++){
        if(obj -> getName() == objects[i] -> getName()){
            objects.erase(objects.begin() + i);
        }
    }
    return 1;
}

void Room::setUpRoom(Room* upRoom){
    this -> upRoom = upRoom;
}

void Room::setDownRoom(Room* downRoom){
    this -> downRoom = downRoom;
}

void Room::setLeftRoom(Room* leftRoom){
    this -> leftRoom = leftRoom;
}

void Room::setRightRoom(Room* rightRoom){
    this -> rightRoom = rightRoom;
}

void Room::setIsExit(bool isExit){
    this -> isExit = isExit;
}

void Room::setIndex(int index){
    this -> index = index;
}

void Room::setRoomKey(Item* key){
    this -> roomKey = key;
}

vector<Object*> Room::getObjects(){
    return objects;
}

void Room::addObject(Object* obj){
    objects.push_back(obj);
}

Room* Room::getUpRoom(){
    return upRoom;
}

Room* Room::getDownRoom(){
    return downRoom;
}

Room* Room::getLeftRoom(){
    return leftRoom;
}

Room* Room::getRightRoom(){
    return rightRoom;
}

bool Room::getIsExit(){
    return isExit;
}

int Room::getIndex(){
    return this -> index;
}

Item* Room::getRoomKey(){
    return this -> roomKey;
}