#include <SDL2/SDL.h>
#include <cstdio>
#include <thread>
#include <memory>
#include <functional>
#include <unistd.h>
#include <cstdlib>
#include <string>


class MyMain {
    public:
        bool done = false;
        int score = 0;
        std::thread t1;
        void process_start();
        void process_stop();
        void process_body();
        void video();

        int pp_pos_x = 120;
        int pp_pos_y = 60;
        int pp_w = 60;
        int pp_h = 30;
        int pp_vel_x = 1;
        int pp_vel_y = 2;
        int pp_acc_x = 0;
        int pp_acc_y = 0;

        int pp1_pos_x = 220;
        int pp1_pos_y = 60;
        int pp1_w = 30;
        int pp1_h = 60;
        int pp1_vel_x = 2;
        int pp1_vel_y = 1;
        int pp1_acc_x = 0;
        int pp1_acc_y = 0;

        int pp2_pos_x = 320;
        int pp2_pos_y = 60;
        int pp2_w = 40;
        int pp2_h = 40;
        int pp2_vel_x = 1;
        int pp2_vel_y = 2;
        int pp2_acc_x = 0;
        int pp2_acc_y = 0;

        int mm_pos_x = 20;
        int mm_pos_y = 20;
        int mm_w = 20;
        int mm_h = 20;

    protected:
        void speedup(int a_acc_x, int a_acc_y, int &a_vel_x, int &a_vel_y);
        void collision_border(int a_pos_x, int a_pos_y, int a_w, int a_h, int &a_vel_x, int &a_vel_y);
        void collision_speed(int a_pos_x, int a_pos_y, int a_w, int a_h, int b_pos_x, int b_pos_y, int b_w, int b_h, int &a_vel_x, int &a_vel_y, int &b_vel_x, int &b_vel_y);
        bool collision_mouse(int a_pos_x, int a_pos_y, int a_w, int a_h, int b_pos_x, int b_pos_y, int b_w, int b_h);
};

void MyMain::speedup(int a_acc_x, int a_acc_y, int &a_vel_x, int &a_vel_y) {
    if ( a_vel_x >= 0 ) {
        a_vel_x+= a_acc_x;
    }
    else {
        a_vel_x-= a_acc_x;
    }

    if ( a_vel_y >= 0 ) {
        a_vel_y+= a_acc_y;
    }
    else {
        a_vel_y-= a_acc_y;
    }
}

void MyMain::collision_border(int a_pos_x, int a_pos_y, int a_w, int a_h, int &a_vel_x, int &a_vel_y) {
    if( (a_pos_x + a_w) > 640 ) {
        a_vel_x = -abs(a_vel_x);
    }

    if( (a_pos_y + a_h) > 480 ) {
        a_vel_y = -abs(a_vel_y);
    }

    if( (a_pos_x - a_w) < 0 ) {
        a_vel_x = abs(a_vel_x);
    }

    if( (a_pos_y - a_h) < 0 ) {
        a_vel_y = abs(a_vel_y);
    }
}

void MyMain::collision_speed(int a_pos_x, int a_pos_y, int a_w, int a_h, int b_pos_x, int b_pos_y, int b_w, int b_h, int &a_vel_x, int &a_vel_y, int &b_vel_x, int &b_vel_y) {
    if(
        abs(a_pos_x - b_pos_x) < (a_w + b_w) &&
        (a_pos_x - b_pos_x) >= 0 &&
        (a_pos_y + a_h) > (b_pos_y - b_h) &&
        (a_pos_y - a_h) < (b_pos_y + b_h)
    ) {
        a_vel_x = abs(a_vel_x);
        b_vel_x = -abs(b_vel_x);
    }
    else if(
        abs(a_pos_x - b_pos_x) < (a_w + b_w) &&
        (a_pos_x - b_pos_x) < 0 &&
        (a_pos_y + a_h) > (b_pos_y - b_h) &&
        (a_pos_y - a_h) < (b_pos_y + b_h)
    ) {
        a_vel_x = -abs(a_vel_x);
        b_vel_x = abs(b_vel_x);
    }

    if(
        abs(a_pos_y - b_pos_y) < (a_h + b_h) &&
        (a_pos_y - b_pos_y) >= 0 &&
        (a_pos_x + a_w) > (b_pos_x - b_w) &&
        (a_pos_x - a_w) < (b_pos_x + b_w)
    ) {
        a_vel_y = abs(a_vel_y);
        b_vel_y = -abs(b_vel_y);
    }
    else if(
        abs(a_pos_y - b_pos_y) < (a_h + b_h) &&
        (a_pos_y - b_pos_y) < 0 &&
        (a_pos_x + a_w) > (b_pos_x - b_w) &&
        (a_pos_x - a_w) < (b_pos_x + b_w)
    ) {
        a_vel_y = -abs(a_vel_y);
        b_vel_y = abs(b_vel_y);
    }
}

bool MyMain::collision_mouse(int a_pos_x, int a_pos_y, int a_w, int a_h, int b_pos_x, int b_pos_y, int b_w, int b_h) {
    if(
        abs(a_pos_x - b_pos_x) < (a_w + b_w) &&
        abs(a_pos_y - b_pos_y) < (a_h + b_h)
    ) {
        return true;
    }

    return false;
}

void MyMain::process_start() {
    t1 = std::thread( std::bind(&MyMain::process_body, this), this );
}

void MyMain::process_stop() {
    t1.join();
}

void MyMain::process_body() {
    printf("Starting background process...\n");

    for (int i = 0; i < 10000 && !done; i++) {
        usleep(16670);
        score++;

        // Acceleration sometimes
        if( i%1000 == 0 ) {
            pp_acc_x = pp_acc_y = pp1_acc_x = pp1_acc_y = pp2_acc_x = pp2_acc_y = 1;
        }
        else {
            pp_acc_x = pp_acc_y = pp1_acc_x = pp1_acc_y = pp2_acc_x = pp2_acc_y = 0;
        }

        // Speed increase
        speedup(pp_acc_x, pp_acc_y, pp_vel_x, pp_vel_y);
        speedup(pp1_acc_x, pp1_acc_y, pp1_vel_x, pp1_vel_y);
        speedup(pp2_acc_x, pp2_acc_y, pp2_vel_x, pp2_vel_y);

        // Move
        pp_pos_x+= pp_vel_x;
        pp_pos_y+= pp_vel_y;

        pp1_pos_x+= pp1_vel_x;
        pp1_pos_y+= pp1_vel_y;

        pp2_pos_x+= pp2_vel_x;
        pp2_pos_y+= pp2_vel_y;

        // Border collision
        collision_border(pp_pos_x, pp_pos_y, pp_w, pp_h, pp_vel_x, pp_vel_y);
        collision_border(pp1_pos_x, pp1_pos_y, pp1_w, pp1_h, pp1_vel_x, pp1_vel_y);
        collision_border(pp2_pos_x, pp2_pos_y, pp2_w, pp2_h, pp2_vel_x, pp2_vel_y);

        // Objects collision
        collision_speed(pp_pos_x, pp_pos_y, pp_w, pp_h, pp1_pos_x, pp1_pos_y, pp1_w, pp1_h, pp_vel_x, pp_vel_y, pp1_vel_x, pp1_vel_y);
        collision_speed(pp_pos_x, pp_pos_y, pp_w, pp_h, pp2_pos_x, pp2_pos_y, pp2_w, pp2_h, pp_vel_x, pp_vel_y, pp2_vel_x, pp2_vel_y);
        collision_speed(pp1_pos_x, pp1_pos_y, pp1_w, pp1_h, pp2_pos_x, pp2_pos_y, pp2_w, pp2_h, pp1_vel_x, pp1_vel_y, pp2_vel_x, pp2_vel_y);

        // Gameover
        if( i < 300 ) {

        }
        else if (
            collision_mouse(pp_pos_x, pp_pos_y, pp_w, pp_h, mm_pos_x, mm_pos_y, mm_w, mm_h) ||
            collision_mouse(pp1_pos_x, pp1_pos_y, pp1_w, pp1_h, mm_pos_x, mm_pos_y, mm_w, mm_h) ||
            collision_mouse(pp2_pos_x, pp2_pos_y, pp2_w, pp2_h, mm_pos_x, mm_pos_y, mm_w, mm_h)
        ) {
            done = true;
        }

    }

    done = true;

    printf("SCORE: %d\n", score);

    printf("Done background process.\n");
}

void MyMain::video() {

    printf("Starting to test SDL renderer...\n");

    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf( "Nope!\t" );
        printf( "%s", SDL_GetError() );
        printf( "\n" );
    }

    SDL_Window* win = SDL_CreateWindow("Pilot game. ", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if( win == nullptr ) {
        SDL_Quit();
        printf( "Nope!\t" );
        printf( "%s", SDL_GetError() );
        printf( "\n" );
    }

    SDL_Renderer* ren = SDL_CreateRenderer( win, -1,
                                            SDL_RENDERER_ACCELERATED |
                                            SDL_RENDERER_PRESENTVSYNC
    );

    if( ren == nullptr ) {
        SDL_Quit();
        printf( "Nope!\t" );
        printf( "%s", SDL_GetError() );
        printf( "\n" );
    }

    SDL_Surface* bmp = SDL_LoadBMP( "hello.bmp" );

    SDL_RenderClear(ren);

    SDL_Texture *tex;

    if( bmp == nullptr ) {
        SDL_Quit();
        printf( "Nope!\t" );
        printf( "%s", SDL_GetError() );
        printf( "\n" );

        //tex = SDL_CreateTexture(ren, SDL_PIXELTYPE(SDL_PIXELFORMAT_RGB24), SDL_TEXTUREACCESS_STATIC, 640, 480);
    }
    else {
        tex = SDL_CreateTextureFromSurface(ren, bmp);
        SDL_FreeSurface(bmp);
    }

    if( tex == nullptr ) {
        SDL_Quit();
        printf( "Nope!\t" );
        printf( "%s", SDL_GetError() );
        printf( "\n" );
    }

    SDL_RenderCopy(ren, tex, NULL, NULL);

    SDL_Rect rect = {1, 1, 50, 100};

    SDL_Delay(1000);

    Uint32* pix = new Uint32[640*480];

    SDL_RenderReadPixels(ren, NULL, 0, pix, 640*sizeof(Uint32) );
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pix, 640, 480, 32, 640*sizeof(Uint32), 0, 0, 0, 0);
    SDL_Texture *bck = SDL_CreateTextureFromSurface(ren, surface);

    SDL_Event event;

    int j = 1;
    while ( not done ) {
        std::string new_header_s = "Pilot game. Score " + std::to_string(score);
        const char* new_header = new_header_s.c_str();

        SDL_SetWindowTitle(win, new_header);

        SDL_RenderCopy(ren, bck, NULL, NULL);

        rect = {pp_pos_x - pp_w, pp_pos_y - pp_h, pp_w*2, pp_h*2};
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
        SDL_RenderDrawRect(ren, &rect);

        rect = {pp1_pos_x - pp1_w, pp1_pos_y - pp1_h, pp1_w*2, pp1_h*2};
        SDL_SetRenderDrawColor(ren, 50, 155, 50, 0);
        SDL_RenderDrawRect(ren, &rect);

        rect = {pp2_pos_x - pp2_w, pp2_pos_y - pp2_h, pp2_w*2, pp2_h*2};
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
        SDL_RenderDrawRect(ren, &rect);


        SDL_PollEvent(&event);
        if( event.type == SDL_MOUSEMOTION ) {
            int btn = SDL_GetMouseState(&mm_pos_x, &mm_pos_y);
        }

        rect = {mm_pos_x - mm_w, mm_pos_y - mm_h, mm_w*2, mm_h*2};
        SDL_RenderDrawRect(ren, &rect);

        SDL_RenderPresent(ren);

        SDL_Delay(16);

        if( j < 255 ) {
            j++;
        }
        else {
            j = 0;
        }
    }

    printf("Done test SDL renderer.\n");

    sleep(2);
}
