#include"SDL2/SDL.h"
#include<string>
#include "canvas.hpp"

class Renderer{
    public:
    
    Renderer();
    ~Renderer();
    bool startRunning(void);
    bool render(void);

    static const uint16_t WIDTH = 640;
    static const uint16_t HEGHT = 480;
    bool isRunning(void);
    void stopRunning(void);
    void handleEvents(void);
    SDL_Renderer* getRenderer(void);
    bool saveWindow(const std::string& fPath);
    bool setPixelAt(uint32_t inX, uint32_t inY, Color& inColor);

    private:
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    Canvas* pCanvas;
    bool _is_running;

};