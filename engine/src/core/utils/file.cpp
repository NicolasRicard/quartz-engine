#include <engine/core/utils/file.hpp>

using namespace phx;

void Content::load(){
    //Create content directories if they don't exist
    if(! fs::exists("games")) fs::create_directory("games");
    if(! fs::exists("mods")) fs::create_directory("mods");
    if(! fs::exists("texturepacks")) fs::create_directory("texturepacks");

    for (const auto & entry : fs::directory_iterator("games/"))
        if(fs::exists(entry.path().string() + "/info.txt" ))
            m_games.push_back("games/" + entry.path().string());
};

//Getters and setters
std::string Content::getGame(std::string gamename){
    
};
std::string Content::getMod(std::string modname){

};
std::string Content::getTexturePack(std::string texturepackname){

};
std::vector <std::string>Content::getGames(){
    return m_games;
};
std::vector <std::string>Content::getMods(){
    return m_mods;
};
std::vector <std::string>Content::getTexturePacks(){
    return m_texturePacks;
};