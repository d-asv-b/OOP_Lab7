#pragma once

#include <memory>

class IApp {
public:
    virtual ~IApp() = default;
    virtual void run() const = 0;
};

class App : public IApp {
private:
    size_t charactersCount_;
    long mapWidth_ = 100;
    long mapHeight_ = 100;
    
public:
    App(size_t characters, long map_width, long map_height);

    void run() const override;
};