#include <SFML/Graphics.hpp>
#include <string>
#include <map>

export module TextureManager;

export class TextureManager{
    // The textures that are loaded
    static std::map<std::string, sf::Texture*> textures;

    // Manually keep track of the order in which textures were loaded, so you can get by index.
    static std::vector<std::string> order;

    // Constructor that is not used
    TextureManager() {
    }
public:
    // Destructor which deletes the textures previously loaded
    ~TextureManager(){
        // Delete all of the textures we used
        sf::Texture* texture;
        std::map<std::string, sf::Texture*>::iterator iter = textures.begin();
        while (iter != textures.end())
        {
            texture = iter->second;
            delete texture;
            iter++;
        }
    }

    static int getLength() {
        return textures.size();
    }

    // Get texutre by name specified in loadTexture, or return null
    static sf::Texture* getTexture(std::string name) {
        if (textures.find(name) != textures.end()) {
            return textures[name];
        }
        else {
            return NULL;
        }
    }

    // Get texutre by index in map, or return null
    static sf::Texture* getTexture(int index) {
        return getTexture(order.at(index));
    }

    // Loads the texture and returns a pointer to it
    // If it is already loaded, this function just returns it
    // If it cannot find the file, returns NULL
    static sf::Texture* loadTexture(std::string name, std::string path) {
        // Haven't loaded it yet, time to create it
        sf::Texture* texture = new sf::Texture();

        if (texture->loadFromFile(path))
        {
            textures[name] = texture;

            // Push to vector the order in which items were loaded into map, for accessing via index.
            order.push_back(name);
            return textures[name];
        }
        else
        {
            // Could not load the file
            delete texture;
            return NULL;
        }
    }
};