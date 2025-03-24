#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <map>
#include <string>
#include <memory>

class ResourceManager {
private:
    std::map<std::string, sf::Font> fonts;          // ��������� ��� �������
    std::map<std::string, sf::SoundBuffer> buffers; // ��������� ��� �������� �������
    std::map<std::string, sf::Texture> textures;    // ��������� ��� �������
    std::map<std::string, std::unique_ptr<sf::Music>> musicStreams; // ��������� ��� ����������� �������

    // ��������� ����������� ��� ���������� ���������
    ResourceManager();

    // ��������� ����������
    ~ResourceManager() {}

    // ��������������� ����� ��� �������� �������
    template<typename T>
    bool loadResource(HRSRC resource, HGLOBAL handle, T& target);

public:
    // ����� ��������� ������������� ���������� ������
    static ResourceManager& getInstance();

    // ������ �����������
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // ������ �������� ���������� ��������
    bool loadFont(const std::string& id, int resourceId);
    bool loadSound(const std::string& id, int resourceId);
    bool loadTexture(const std::string& id, int resourceId);
    bool loadMusic(const std::string& id, int resourceId); // ����� ����� ��� ������

    // ������� ��� ��������� �������� �� ��������������
    sf::Font& getFont(const std::string& id);
    sf::SoundBuffer& getSoundBuffer(const std::string& id);
    sf::Texture& getTexture(const std::string& id);
    sf::Image getImage(const std::string& id);
    sf::Music& getMusic(const std::string& id); // ����� ������ ��� ������
};

