#include "Transition.h"

Transition::Transition(sf::RenderWindow& window)
    : window(window), alpha(255.f), transitioning(false), fadingIn(false), transitionDuration(0.5f) {
    overlay.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    overlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
}

void Transition::startTransition(GameState newState) {
    transitioning = true;
    fadingIn = false;
    targetState = newState;
    alpha = 255.f;
    overlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
}

bool Transition::update(GameState& currentState, float deltaTime) {
    if (transitioning) {
        if (!fadingIn) {
            alpha -= (255.f / transitionDuration) * deltaTime;
            if (alpha <= 0.f) {
                alpha = 0.f;
                fadingIn = true;
                currentState = targetState;
            }
        }
        else {
            alpha += (255.f / transitionDuration) * deltaTime;
            if (alpha >= 255.f) {
                alpha = 255.f;
                transitioning = false;
            }
        }
        overlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(255.f - alpha)));
        return true;
    }
    return false;
}

void Transition::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (transitioning) {
        target.draw(overlay, states);
    }
}