#include "renderer.hpp"

#include<iostream>

Renderer::Renderer(){
    this->pWindow = nullptr;
    this->_is_running = false;
    this->pCanvas = new Canvas(Renderer::WIDTH, Renderer::WIDTH);

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0) {
        Uint32 flags = SDL_WINDOW_SHOWN;
        this->pWindow = SDL_CreateWindow("The game has started", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, Renderer::WIDTH, Renderer::HEGHT, flags);
        if(this->pWindow){
            this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_ACCELERATED);
            if(!this->pRenderer){
                SDL_Log("Unable to create renderer: %s", SDL_GetError());
            }
        }
        else{
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        }
    }
    else{
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }
}

bool Renderer::setPixelAt(uint32_t inX, uint32_t inY, Color& inColor){
    return(this->pCanvas->setPixelAt(inX, inY, inColor));
}

Renderer::~Renderer(){
    SDL_DestroyWindow(this->pWindow);
    SDL_DestroyRenderer(this->pRenderer);
    SDL_Quit();
}

SDL_Renderer* Renderer::getRenderer(void){
    return this->pRenderer;
}
bool Renderer::isRunning(void){
    return this->_is_running;
}

void Renderer::stopRunning(void){
    SDL_Delay(2500);
    this->_is_running = false;
}

void Renderer::handleEvents(void){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                this->stopRunning();
            break;
            default:
            break;
        }
    }
}

bool Renderer::startRunning(void){
    //black, opaque
    SDL_SetRenderDrawColor(this->pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //clear window to black
    SDL_RenderClear(this->pRenderer);
    //show window
    SDL_RenderPresent(this->pRenderer);

    this->_is_running = true;

    return true;
}

bool Renderer::saveWindow(const std::string& fPath){
    bool result = false;
    SDL_Surface* pScreen = SDL_GetWindowSurface(this->pWindow);
    if(pScreen){
        SDL_LockSurface(pScreen);
        if(SDL_SaveBMP(pScreen, fPath.c_str())){
            result = true;
        }
        SDL_UnlockSurface(pScreen);
    }
    return result;
}

bool Renderer::render(void){

    //clear window to black
    SDL_RenderClear(this->pRenderer);
    //get first pixel from the Canvas(top-left screen corner)
    Color* pColor = this->pCanvas->getPixelAt(0,0);
    SDL_Surface* pScreen = SDL_GetWindowSurface(this->pWindow);
    Uint32* pixels = (Uint32*)pScreen->pixels;

    SDL_LockSurface(pScreen);
    for(uint32_t X  = 0; X < Renderer::WIDTH; X++){
        for(uint32_t Y = 0; Y < Renderer::HEGHT; Y++){
            uint32_t pixPos = X + Y * Renderer::WIDTH;
            pixels[pixPos] = SDL_MapRGB(pScreen->format, (Uint8)pColor[pixPos].red, (Uint8)pColor[pixPos].green, (Uint8)pColor[pixPos].blue);
        }
        //optimize to display lines at each time
    }
    SDL_UnlockSurface(pScreen);

    SDL_UpdateWindowSurface(this->pWindow);
    return true;
}