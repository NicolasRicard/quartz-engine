#include <experimental/filesystem>
#include <engine/core/Core.hpp>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace phx{
    class Content{
        Content();
        ~Content();

        void load(); //Scan through content folders for any content

        //Getters

        std::string getGame(std::string gamename);
        std::string getMod(std::string modname);
        std::string getTexturePack(std::string texturepackname);
        std::vector <std::string>getGames();
        std::vector <std::string>getMods();
        std::vector <std::string>getTexturePacks();

        private:
            //Vectors to hold loaded content packs
            std::vector <std::string>m_games;
            std::vector <std::string>m_mods;
            std::vector <std::string>m_texturePacks;
    }
}