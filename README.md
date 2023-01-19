
COMPILE INSTRUCTION

>sudo apt install libsdl2-dev
>cd build
>cmake ..
>make
>./CppTesting


ANYTHIN ELSE

Some test code for accelerated drawings.

sudo apt install libx11-dev
sudo apt install libsdl2-dev

git submodule add git@github.com:ocornut/imgui.git lib/imgui
git submodule add git@github.com:libsdl-org/SDL.git lib/SDL

Maybe will need later:
https://github.com/libsdl-org/SDL_ttf
https://github.com/epezent/implot




Oh well, my SDL2 version is too old for imgui
I will try to use SDL2 at least.
https://wiki.libsdl.org/SDL2/SDL_CreateRenderer


Ok, some drawing and animations work.
Also can save state before animating.

Threads added.

