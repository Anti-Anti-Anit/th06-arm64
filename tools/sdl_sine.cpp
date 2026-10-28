#include <SDL2/SDL.h>
#include <cstdio>
#include <cmath>

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
    SDL_PauseAudioDevice(dev, 0);
    const int TOTAL = 44100 * 5;
    static short buf[44100];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 44100; j++) {
            buf[j] = (short)(12000.0 * sin(2.0 * M_PI * 440.0 * (i * 44100 + j) / 44100.0));
        }
        SDL_QueueAudio(dev, buf, sizeof(buf));
    }
    std::printf("QUEUED 5s of 440Hz sine\n");
    while (SDL_GetQueuedAudioSize(dev) > 0) SDL_Delay(100);
    std::printf("DONE - did you hear it?\n");
    SDL_CloseAudioDevice(dev);
    return 0;
}
