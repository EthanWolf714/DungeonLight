#include "game.h"

Game::Game(){
    
}

Game::~Game(){

}

void Game::Update(){
    player.Update();
}

void Game::Draw(){
    player.Draw();
}