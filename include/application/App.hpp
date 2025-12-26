#pragma once

#include <memory>
#include <mutex>
#include <vector>

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

    mutable std::mutex map_mtx_;
    std::vector<std::vector<char>> map_;

    static std::unique_ptr<App> instance_;
    static std::mutex instance_mtx_;

    App(size_t characters, long map_width, long map_height);
    App(const App&) = delete;
    App& operator=(const App&) = delete;

public:
    static App& getInstance(size_t characters = 50, long map_width = 100, long map_height = 100);

    void run() const override;
    void print_map() const;
    void edit_map(long posX, long posY, char newVal);

    long get_map_width() const;
    long get_map_height() const;

    char get_map_state(long posX, long posY) const;
};