//
// Created by ysun3 on 11/8/17.
//

#include <sstream>
#include "HUD.h"
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"

//Definiton of HUD
HUD::HUD() : original_life_time(Gamedata::getInstance().getXmlInt("HUD/life")),
             remain_life_time(original_life_time),
             num_of_lines(Gamedata::getInstance().getXmlInt("HUD/lines"))
{
    for(int i = 1; i <= num_of_lines; i++)
    {
        std::string str = Gamedata::getInstance().getXmlStr("HUD/line" + std::to_string(i));
        contents.push_back(str);
    }
}

HUD::~HUD() { delete instance; }

HUD* HUD::getInstace()
{
    if(!instance) instance = new HUD;
    return instance;
}

void HUD::ShowHUD(int timePast)
{
    SDL_Color color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    if(remain_life_time - timePast > 0)
    {
        SDL_SetRenderDrawColor(RenderContext::getInstance()->getRenderer(),0,0,0,100);
        SDL_Rect rect;
        rect.x = 30;
        rect.y = 50;
        rect.w = 320;
        rect.h = (int)contents.size() * 30;
        SDL_SetRenderDrawBlendMode(RenderContext::getInstance()->getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(RenderContext::getInstance()->getRenderer(), &rect);
        for(size_t i = 0; i < contents.size(); i++)
        {
            IOmod::getInstance().writeText(contents[i], 30, 50 + (int)i * 30, -24, -6, color);
        }
    }
}

void HUD::ResetLife(int currentSecond)
{
    remain_life_time = currentSecond + original_life_time + 1;
}

HUD* HUD::instance = NULL;

//Definition of PoolHUD
PoolHUD::PoolHUD(const Player & p) :
    player(p),
    showPoolHUD(true)
{}

void PoolHUD::ShowHUD() const
{
    if(showPoolHUD)
    {
        SDL_Color color;
        color.r = 255;
        color.g = 0;
        color.b = 0;
        color.a = 255;

        SDL_SetRenderDrawColor(RenderContext::getInstance()->getRenderer(),0,0,0,100);
        SDL_Rect rect;
        rect.x = 630;
        rect.y = 50;
        rect.w = 160;
        rect.h = 100;
        SDL_SetRenderDrawBlendMode(RenderContext::getInstance()->getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(RenderContext::getInstance()->getRenderer(), &rect);

        std::stringstream strm;
        strm << "Bullet list: " << player.getBulletsCount();
        IOmod::getInstance().writeText(strm.str(), 650, 60, -24, -6, color);

        strm.clear();
        strm.str("");

        strm << "Free list: " << player.getFreeBulletsCount();
        IOmod::getInstance().writeText(strm.str(), 650, 90, -24, -6, color);

        strm.clear();
        strm.str("");

        strm << "God mode: " << player.getGodMode();
        IOmod::getInstance().writeText(strm.str(), 650, 120, -24, -6, color);
    }
}

//Definition of GameoverHUD
GameoverHUD::GameoverHUD() :
    content()
{}

void GameoverHUD::setContent(std::string& cont)
{
    content = cont;
}

void GameoverHUD::ShowWin() const
{
    SDL_SetRenderDrawColor(RenderContext::getInstance()->getRenderer(),0,0,0,100);
    SDL_Rect rect;
    rect.x = 270;
    rect.y = 210;
    rect.w = 230;
    rect.h = 90;
    SDL_SetRenderDrawBlendMode(RenderContext::getInstance()->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(RenderContext::getInstance()->getRenderer(), &rect);

    IOmod::getInstance().writeText(content, 290, 230);
    IOmod::getInstance().writeText("Press R to restart", 290, 260);
}

void GameoverHUD::ShowLose() const
{
    SDL_SetRenderDrawColor(RenderContext::getInstance()->getRenderer(),0,0,0,100);
    SDL_Rect rect;
    rect.x = 270;
    rect.y = 210;
    rect.w = 230;
    rect.h = 90;
    SDL_SetRenderDrawBlendMode(RenderContext::getInstance()->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(RenderContext::getInstance()->getRenderer(), &rect);

    IOmod::getInstance().writeText(content, 290, 230);
    IOmod::getInstance().writeText("Press R to restart", 290, 260);
}