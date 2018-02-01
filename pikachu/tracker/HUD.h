//
// Created by ysun3 on 11/8/17.
//

#ifndef INC_3_HUD_H
#define INC_3_HUD_H

#include <vector>
#include <string>
#include "gamedata.h"
#include "player.h"

class HUD
{
public:
    HUD();
    ~HUD();

    static HUD* getInstace();
    void ShowHUD(int timePast);
    void ResetLife(int currentSecond);

private:
    static HUD* instance;
    std::vector<std::string> contents;
    int original_life_time;
    int remain_life_time;
    int num_of_lines;
};

class PoolHUD
{
public:
    PoolHUD(const Player&);

    void ShowHUD() const;
    void update();
    void toggle() { showPoolHUD = !showPoolHUD; }

    PoolHUD(const PoolHUD&) = delete;
    PoolHUD& operator=(const PoolHUD&) = delete;

private:
    const Player& player;
    bool showPoolHUD;
};

class GameoverHUD
{
public:
    GameoverHUD();

    void ShowLose() const;
    void ShowWin() const;
    void update();
    void setContent(std::string& content);

private:
    string content;
};

#endif //INC_3_HUD_H
