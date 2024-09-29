#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>

export module PopUp;

export class popUp {
    std::string text;
    std::string windowName;
public:
    popUp(std::string text, std::string windowName) {
        this->text = text;
        this->windowName = windowName;

        this->display();
    }

    std::string getText() {
        return this->text;
    }

    void setText(std::string text) {
        this->text = text;
    }

    void display() {
        MessageBoxA(NULL, this->text.c_str(), this->windowName.c_str(), MB_OK | MB_ICONINFORMATION);
    }

};