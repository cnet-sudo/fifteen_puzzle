#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <map>
#include <string>
#include <memory>

class ResourceManager {
private:
    std::map<std::string, sf::Font> fonts;          // Хранилище для шрифтов
    std::map<std::string, sf::SoundBuffer> buffers; // Хранилище для звуковых буферов
    std::map<std::string, sf::Texture> textures;    // Хранилище для текстур
    std::map<std::string, std::unique_ptr<sf::Music>> musicStreams; // Хранилище для музыкальных потоков

    // Приватный конструктор для реализации синглтона
    ResourceManager();

    // Приватный деструктор
    ~ResourceManager() {}

    // Вспомогательный метод для загрузки ресурса
    template<typename T>
    bool loadResource(HRSRC resource, HGLOBAL handle, T& target);

public:
    // Метод получения единственного экземпляра класса
    static ResourceManager& getInstance();

    // Запрет копирования
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Методы загрузки конкретных ресурсов
    bool loadFont(const std::string& id, int resourceId);
    bool loadSound(const std::string& id, int resourceId);
    bool loadTexture(const std::string& id, int resourceId);
    bool loadMusic(const std::string& id, int resourceId); // Новый метод для музыки

    // Геттеры для получения ресурсов по идентификатору
    sf::Font& getFont(const std::string& id);
    sf::SoundBuffer& getSoundBuffer(const std::string& id);
    sf::Texture& getTexture(const std::string& id);
    sf::Image getImage(const std::string& id);
    sf::Music& getMusic(const std::string& id); // Новый геттер для музыки
};

