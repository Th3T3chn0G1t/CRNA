# Tutorial

## Welcome
Thank you for considering CRNA for your next big project! Let's get started shall we?

Firstly, keep the following in mind in case you encounter an issue during development:
    - The documentation is your best friend, it explains how to use all functions and explains the purpose of all variables and types. Documentation can be found [here](https://th3t3chn0g1t.github.io/CRNA)
    - All types have memory management covered, don't worry yourself with it and just use the initialization function provided in headers
    - If you have crash or bug, don't be afraid to use a debugger to peek at the running of your code. Use ```make debug``` to enter debugging

With that out of the way, let's move onto your first program

## Hello CRNA
(This section presumes that you have followed the intallation instructions in the README)

To generate a new project, navigate to the CRNA directory in the command line and run```scripts/generateProjectTemplate.sh <destination dir>``` where destination dir is the relative path to the destination directory. E.g. ```scripts/generateProjectTemplate.sh ~/dev/crna_tutorial```. This script automatically excludes a lot of the stuff you don't need

Now if you naviagate to ```src/game/main.c``` in your newly created project, you can observe the following:
```c
    #include "../engine/include/crna.h"
    #include "../engine/include/io.h"

    void on_start(settings_T* settings, node_T** registry, game_T* game) {
        info("Game started");
    }

    void on_update(game_T* game, node_T* registry, camera_controller_T* camera) {
        static bool echoed_gamestate = false;
        if(!echoed_gamestate) {
            print_gamestate_info();
            echoed_gamestate = true;
        }
    }

    void on_destroy(node_T* registry) {
        info("Shutting down...");
    }

    int main(int argc, char** argv) {
        crna_init(on_start, on_update, on_destroy);
    }
```
If you now add the line ```info("Hello, world!")``` to the ```on_start()``` function and run ```make run```, then exit the program using ```ALT-F4``` on Linux or ```CMD+Q``` on MacOS. You should see the following log output:
```c
    INFO: Hello, world!
    INFO: Game started
    WARNING: Registry was empty during initialization. Creating dummy entry at index 0 for camera controller
    DEBUG: Gamestate Information

    Game Settings:
            Resolution: 1280 x 800
            Framerate: 60
            Position: 0, 0
            Title: Title
            Version: 0.0.0
            Fullscreen?: False
            Decorated?: False
            Font: res/font/BPdotsSquareBold.ttf
            Font Size: 16
    Registry Length: 1
    Game:
            Window: Valid
            Window Context: Valid
            Input Context: Valid
    Camera Controller:
            Drawing Context: Valid
            Latch: Valid

    INFO: Quit requested by user
    INFO: Shutting down...
```
(The warnings and debug information are just default behaviours of the application and the compilation output will probably have some warnings especially in non-production versions)

There you are! In the next tutorial we will move onto some coneptual bits & pieces for CRNA