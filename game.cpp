#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "./include/controllers/inputController.hpp"
#include "./include/controllers/timeController.hpp"
#include "./include/entity/entity.hpp"
#include "./include/sfml/texture.hpp"
#include "./include/body.hpp"
#include "./include/key.hpp"
#include "./include/sprite.hpp"
#include "./include/vector2.hpp"

std::vector<Texture> textures_loaded;
sf::Sprite filterGetSprite(Sprite _sprite, Vector2 _position, Vector2 _size);
bool haveTexture(const std::string _source);
int getTextureLoaded(const std::string _source);
void playerLogic(Entity &_player_entity, InputController _input);
void pipeLogic(Entity &_pipe, Entity &_reverse_pipe);
void updatePipePosition(Entity &_pipe, Entity &_reverse_pipe);

int main() {
    std::vector<Key> keys_allowed;
    keys_allowed.push_back(Key(' '));
    InputController input(keys_allowed);
    sf::RenderWindow window(sf::VideoMode(288, 512), "Flappy Bird");
    TimeController time_draw(30), time_animation(20), time_physics(10);
    Body default_body;

    Entity background_entity(default_body, "background", false);
    background_entity.setPosition(Vector2(0, 0));
    background_entity.setSize(Vector2(1, 1));

    Entity ground_entity(default_body, "ground", false);
    ground_entity.setSize(Vector2(1, 1));
    ground_entity.setPosition(Vector2(0, 512 - 112));

    Entity pipe_top(default_body, "reverse_pipe", false);
    pipe_top.setSize(Vector2(1, 1));
    pipe_top.setPosition(Vector2(0, -175));

    Entity pipe_bottom(default_body, "pipe", false);
    pipe_bottom.setSize(Vector2(1, 1));
    pipe_bottom.setPosition(Vector2(0, pipe_top.getPosition().y + 320 + 100));

    Entity player_entity(default_body, "bird", true);
    player_entity.setPosition(Vector2(50, 200));
    player_entity.setSize(Vector2(1, 1));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Keyboard::Key _key = event.key.code;
            
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    switch(_key) {
                        case sf::Keyboard::Space:
                            input.setKey(' ');
                            break;
                    }
                    break;

                case sf::Event::KeyReleased:
                    switch(_key) {
                        case sf::Keyboard::Space:
                            input.removeKey(' ');
                            break;
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    input.setKey(' ');
                    break;

                case sf::Event::MouseButtonReleased:
                    input.removeKey(' ');
                    break;
            }
        }

        if (time_animation.canUpdate()) {
            playerLogic(player_entity, input);
        } else if (time_draw.canUpdate()) {
            window.clear();
            //Draw logic: Background, Bird, Pipe, Ground;
            window.draw(filterGetSprite(background_entity.getSprite(), background_entity.getPosition(), background_entity.getSize()));
            sf::Sprite _player_sprite = filterGetSprite(player_entity.getSprite(), player_entity.getPosition(), player_entity.getSize());
            _player_sprite.setRotation(float(player_entity.getAceleration().y * 5));
            window.draw(_player_sprite);
            window.draw(filterGetSprite(pipe_top.getSprite(), pipe_top.getPosition(), pipe_top.getSize()));
            window.draw(filterGetSprite(pipe_bottom.getSprite(), pipe_bottom.getPosition(), pipe_bottom.getSize()));
            window.draw(filterGetSprite(ground_entity.getSprite(), ground_entity.getPosition(), ground_entity.getSize()));

            if (!player_entity.getColliding()) {
                pipeLogic(pipe_top, pipe_bottom);
            }

            window.display();
        } else if (time_physics.canUpdate()) {
            player_entity.setColliding(((
                player_entity.getPosition().x <= (pipe_top.getPosition().x + 52) && (player_entity.getPosition().x + 34) >= pipe_top.getPosition().x &&
                player_entity.getPosition().y <= (pipe_top.getPosition().y + 320) && (player_entity.getPosition().y + 24) >= pipe_top.getPosition().y
            ) || (
                player_entity.getPosition().x <= (pipe_bottom.getPosition().x + 52) && (player_entity.getPosition().x + 34) >= pipe_bottom.getPosition().x &&
                player_entity.getPosition().y <= (pipe_bottom.getPosition().y + 320) && (player_entity.getPosition().y + 24) >= pipe_bottom.getPosition().y
            )));
        }
    }
}

sf::Sprite filterGetSprite(Sprite _sprite, Vector2 _position, Vector2 _size) {
    sf::Sprite _new_sprite;
    
    if (!haveTexture(_sprite.source)) {
        sf::Texture new_texture_source;
        if (new_texture_source.loadFromFile(_sprite.source)) {
            textures_loaded.push_back(Texture(_sprite.source, new_texture_source));
            std::cout << "-->Texture<-- New Texture created\n";
        }
    }

    _new_sprite.setTexture(textures_loaded[getTextureLoaded(_sprite.source)].texture_source);
    _new_sprite.setPosition(sf::Vector2f(_position.x, _position.y));
    _new_sprite.setScale(sf::Vector2f(_size.x, _size.y));
    _new_sprite.setTextureRect(sf::IntRect(_sprite.frame_size.x * _sprite.current_frame, 0, _sprite.frame_size.x, _sprite.frame_size.y));

    return _new_sprite;
}

bool haveTexture(const std::string _source) {
    for (int i = 0; i < textures_loaded.size(); i++) {
        if (textures_loaded[i].source == _source) {
            return true;
        }
    }
    return false;
};

int getTextureLoaded(const std::string _source) {
    for (int i = 0; i < textures_loaded.size(); i++) {
        if (textures_loaded[i].source == _source) {
            return i;
        }
    }

    return -1;
}

void playerLogic(Entity &_player_entity, InputController _input) {
    if (!_player_entity.getColliding()) {
        if (_input.isKeyPressed(' ') && _player_entity.getAceleration().y > -12) {
            _player_entity.setAceleration(Vector2(0, _player_entity.getAceleration().y - 2));
        }

        if (_player_entity.getAceleration().y <= 5) {
            _player_entity.setAceleration(Vector2(0, _player_entity.getAceleration().y + 1));
        }

        _player_entity.setPosition(Vector2(50, _player_entity.getPosition().y + _player_entity.getAceleration().y));
        _player_entity.update();
    }
}

int pipe_current_x = 288;
void pipeLogic(Entity &_pipe, Entity &_reverse_pipe) {
    if (pipe_current_x <= -52) {
        pipe_current_x = 288;
        updatePipePosition(_pipe, _reverse_pipe);
    } else {
        pipe_current_x -= 3;
    }

    _pipe.setPosition(Vector2(pipe_current_x, _pipe.getPosition().y));
    _reverse_pipe.setPosition(Vector2(pipe_current_x, _reverse_pipe.getPosition().y));
}

int pipes_heights_pseudorandomic[] = {-82, -200, -100, -150, -220, -90, -72, -132, -60, -175, -145};
int pipes_heights_pseudorandomic_size = 10;
int pipes_heights_current_index = 0;

void updatePipePosition(Entity &_pipe, Entity &_reverse_pipe) {
    pipes_heights_current_index = (pipes_heights_current_index + 1) % pipes_heights_pseudorandomic_size;
    _pipe.setPosition(Vector2(_pipe.getPosition().x, pipes_heights_pseudorandomic[pipes_heights_current_index]));
    _reverse_pipe.setPosition(Vector2(_reverse_pipe.getPosition().x, _pipe.getPosition().y + 320 + 100));
}