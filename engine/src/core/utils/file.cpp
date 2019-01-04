#include <engine/core/utils/file.hpp>

using namespace phx;

void load(){
    //Create content directories if they don't exist
    if(! fs::exists("games")) fs::create_directory("games");
    if(! fs::exists("mods")) fs::create_directory("mods");
    if(! fs::exists("texturepacks")) fs::create_directory("texturepacks");

    for (const auto & entry : fs::directory_iterator("games/"))
        if(fs::exists(entry.path().string() + "/info.txt" ))
            m_games.push_back("games/"+entry.path());
};

//Getters and setters

std::string getGame(std::string gamename){

};
std::string getMod(std::string modname){

};