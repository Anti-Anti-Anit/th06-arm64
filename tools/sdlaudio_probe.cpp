#include <SDL2/SDL.h>
#include <cstdio>

int main()
{
    if (SDL_Init(SDL_INIT_AUDIO)) {
        std::printf("INIT FAILED: %s\n", SDL_GetError());
        return 1;
    }
    SDL_AudioSpec desired = {}, obtained = {};
    desired.freq = 44100;
    desired.format = AUDIO_S16;
    desired.channels = 2;
    desired.samples = 2048;
    desired.callback = NULL;
    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);
    if (dev == 0) {
        std::printf("OPEN FAILED: %s\n", SDL_GetError());
        return 1;
    }
    std::printf("OPEN OK dev=%u freq=%d ch=%d samples=%u fmt=0x%x\n",
                dev, obtained.freq, obtained.channels, obtained.samples, obtained.format);
    SDL_PauseAudioDevice(dev, 0);
    SDL_Delay(1000);
    SDL_CloseAudioDevice(dev);
    std::printf("DONE\n");
    return 0;
}
