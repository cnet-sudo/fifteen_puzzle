// ResourceManager.cpp
#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {}

template<typename T>
bool ResourceManager::loadResource(HRSRC resource, HGLOBAL handle, T& target) {
    if (!resource) {
        std::cerr << "Не удалось найти ресурс" << std::endl;
        return false;
    }
    handle = LoadResource(NULL, resource);
    if (!handle) {
        std::cerr << "Не удалось загрузить ресурс" << std::endl;
        return false;
    }
    const void* data = LockResource(handle);
    DWORD size = SizeofResource(NULL, resource);

    return target.loadFromMemory(data, size);
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadFont(const std::string& id, int resourceId) {
    HRSRC fontResource = FindResource(NULL, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    HGLOBAL fontHandle = NULL;
    sf::Font font;
    if (!loadResource(fontResource, fontHandle, font)) {
        std::cerr << "Не удалось загрузить шрифт " << id << std::endl;
        return false;
    }
    fonts[id] = std::move(font);
    return true;
}

bool ResourceManager::loadSound(const std::string& id, int resourceId) {
    HRSRC soundResource = FindResource(NULL, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    HGLOBAL soundHandle = NULL;
    sf::SoundBuffer buffer;
    if (!loadResource(soundResource, soundHandle, buffer)) {
        std::cerr << "Не удалось загрузить звук " << id << std::endl;
        return false;
    }
    buffers[id] = std::move(buffer);
    return true;
}

bool ResourceManager::loadTexture(const std::string& id, int resourceId) {
    HRSRC textureResource = FindResource(NULL, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    HGLOBAL textureHandle = NULL;
    sf::Texture texture;
    if (!loadResource(textureResource, textureHandle, texture)) {
        std::cerr << "Не удалось загрузить текстуру " << id << std::endl;
        return false;
    }
    textures[id] = std::move(texture);
    return true;
}

bool ResourceManager::loadMusic(const std::string& id, int resourceId) {
    HRSRC musicResource = FindResource(NULL, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    HGLOBAL musicHandle = NULL;
    if (!musicResource) {
        std::cerr << "Не удалось найти музыкальный ресурс " << id << std::endl;
        return false;
    }
    musicHandle = LoadResource(NULL, musicResource);
    if (!musicHandle) {
        std::cerr << "Не удалось загрузить музыкальный ресурс " << id << std::endl;
        return false;
    }
    const void* data = LockResource(musicHandle);
    DWORD size = SizeofResource(NULL, musicResource);

    auto music = std::make_unique<sf::Music>();
    if (!music->openFromMemory(data, size)) {
        std::cerr << "Не удалось открыть музыкальный поток " << id << " из памяти" << std::endl;
        return false;
    }
    musicStreams[id] = std::move(music);
    return true;
}

sf::Font& ResourceManager::getFont(const std::string& id) {
    auto it = fonts.find(id);
    if (it == fonts.end()) {
        std::cerr << "Шрифт " << id << " не найден" << std::endl;
        static sf::Font emptyFont;
        return emptyFont;
    }
    return it->second;
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& id) {
    auto it = buffers.find(id);
    if (it == buffers.end()) {
        std::cerr << "Звуковой буфер " << id << " не найден" << std::endl;
        static sf::SoundBuffer emptyBuffer;
        return emptyBuffer;
    }
    return it->second;
}

sf::Texture& ResourceManager::getTexture(const std::string& id) {
    auto it = textures.find(id);
    if (it == textures.end()) {
        std::cerr << "Текстура " << id << " не найдена" << std::endl;
        static sf::Texture emptyTexture;
        return emptyTexture;
    }
    return it->second;
}

sf::Image ResourceManager::getImage(const std::string& id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.copyToImage();
    }
    std::cerr << "Текстура для изображения " << id << " не найдена" << std::endl;
    return sf::Image();
}

sf::Music& ResourceManager::getMusic(const std::string& id) {
    auto it = musicStreams.find(id);
    if (it == musicStreams.end()) {
        std::cerr << "Музыкальный поток " << id << " не найден" << std::endl;
        static sf::Music emptyMusic;
        return emptyMusic;
    }
    return *(it->second);
}