#include "game.h"

using namespace std;

int playGame(SDL_Window *window, SDL_Renderer *renderer, int arrScore[], int fps)
{
    int play;
    srand(time(NULL));
	
	Painter painter (window, renderer);
	
    // Load Ảnh
	SDL_Texture* gameover = loadTexture("image/game_over.jpg", renderer);
    SDL_Texture* heart = loadTexture("image/heart.jpg", renderer);
    SDL_Texture* background = loadTexture("image/bg.jpg", renderer);
    SDL_Texture* colBar = loadTexture("image/bar.jpg", renderer);
    SDL_Texture* _background = removeBackground(renderer, "image/_back.jpg");
    SDL_Texture* addHeart = removeBackground(renderer, "image/add_lives.jpg");
    SDL_Texture* shield = removeBackground(renderer, "image/shield.jpg");
    SDL_Texture* gai = removeBackground(renderer, "image/gai.jpg");
    SDL_Texture* shieldPro = removeBackground(renderer, "image/prot.jpg");

    // Load nhạc
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* Music = Mix_LoadMUS ("music/music.mp3");
    Mix_Chunk* healthsound = Mix_LoadWAV("music/heart.wav");
	Mix_Chunk* jumpsound = Mix_LoadWAV("music/jumpOnbar.wav");
	Mix_Chunk* diesound = Mix_LoadWAV("music/die.mp3");
	Mix_Chunk* Mgameover = Mix_LoadWAV("music/gameover.mp3");
    Mix_Chunk* protectedSound = Mix_LoadWAV("music/protected.wav");

    // Load Text
    TTF_Init();
    TTF_Font* font1 = NULL;
    font1 = TTF_OpenFont("font/COOPBL.TTF", 32);
    TTF_Font* font2 = NULL;
    font2 = TTF_OpenFont("font/COOPBL.TTF", 24);

    SDL_Surface* lives = TTF_RenderText_Solid(font2, "Lives", WHITE_COLOR);
    SDL_Texture* title_live = SDL_CreateTextureFromSurface(renderer, lives);
    SDL_Surface* scores = TTF_RenderText_Solid(font2, "Score", WHITE_COLOR);
    SDL_Texture* title_score = SDL_CreateTextureFromSurface(renderer, scores);
    
    SDL_Surface* scoresLast = TTF_RenderText_Solid(font2, "Your Score: ", RED_COLOR);
    SDL_Texture* title_score_last = SDL_CreateTextureFromSurface(renderer, scoresLast);


    int live = 3;
	int score = 0;
    
   
    // Toạ độ ban đầu của ball
    int x = 300;
    int y = 58;

    // Khởi tạo toạ độ của các vật trong game
    vector<bar> color_bar;
    vector<bar> gai_bar;
    vector<items> add_heart;
    vector<items> add_shield;

    for (int i = 0; i <=600; i++) {
        bar _bar;
        color_bar.push_back(_bar);
        
        items _heart;
		_heart.itemsRect.x = _bar.barRect.x + 10;
        _heart.itemsRect.y = _bar.barRect.y - 12;
		add_heart.push_back(_heart);

        items _shield;
        _shield.itemsRect.x = _bar.barRect.x + 10;
        _shield.itemsRect.y = _bar.barRect.y - 12;
        add_shield.push_back(_shield);

    }

    for (int i = 0; i <=600; i++) {
        bar _gaibar;
        gai_bar.push_back(_gaibar);
    }

    SDL_Rect shieldRect;
    shieldRect.w = 40;
    shieldRect.h = 40;


    SDL_Event e;
    const int step = 30;
    bool ballUp = true;
    bool soundJump = true;
    bool rightDirection = true;
    bool doNotMove = true;
    bool running = true;
    bool gameOver = false;
    bool isProtected = false;
    int color_cur = 0; 
    int gai_cur = 0;
    const int DELAY_TIME = 2000 / fps;

    Mix_PlayMusic(Music, -1);
    Uint32 frameStart, frameTime;

    while (running) {
		frameStart = SDL_GetTicks();
        
        SDL_Surface* score_cur = TTF_RenderText_Solid(font2, numberToString(score).c_str(), RED_COLOR);
        SDL_Texture* Score_render = SDL_CreateTextureFromSurface(renderer, score_cur);

        SDL_Surface* score_cur_last = TTF_RenderText_Solid(font2, numberToString(score).c_str(),RED_COLOR);
        SDL_Texture* Score_render_last = SDL_CreateTextureFromSurface(renderer, score_cur_last);

        // Vẽ lại background game
        refreshScreen(window, renderer, painter, background, _background, heart, live);
        renderTexture(title_live,renderer, 0, 40, 45, 20);
        renderTexture(title_score, renderer, 355, 40, 50, 20);
        renderTexture(Score_render, renderer, 360, 60);

        // Vẽ hình tròn của ball
        painter.setColor(WHITE_COLOR);
        painter.setPosition(x, y);
        painter.createCircle(10);
        SDL_Rect ballPlay = {x, y, 20,20}; 
        
        while (SDL_PollEvent(&e)) {
            // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
            if (e.type == SDL_QUIT) running = false;

            // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
            if (e.type == SDL_KEYDOWN) {
                // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
                if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
                
                else if (e.key.keysym.sym == SDLK_LEFT) {
                        rightDirection = false;
                        doNotMove = false;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                        rightDirection = true;
                        doNotMove = false;
                }
            }
        }

        if (doNotMove) x = x;
        else if (rightDirection) {
            if (x < SCREEN_WIDTH-step/2) x = x + step/2;
        }
        else {
            if (x >= step/2)  x = x - step/2;
        }

        // Nếu ball chạm vào gai nhọn bên trên hoặc đi quá dưới thì trừ một live
        if (y <= 40 || y >= 660) {
            live--;
            Mix_PlayChannel(-1, diesound, 0);
            x = 200;
            y = 58;
            isProtected = false;
        }

        
        for (int i = 0; i <= color_cur; i++) {
            // Trường hợp ăn một heart tăng thêm một live
            if (i % 8 == 0) {
                if (SDL_HasIntersection(&add_heart[i].itemsRect, &ballPlay)) {
                    if (live<3) live++;
                    remove(add_heart[i].itemsRect);
                    Mix_PlayChannel(-1, healthsound, 0);
                }
            }
            // Trường hợp ăn được shield thì được bảo vệ khỏi những gai nhọn
            if (i % 15 == 0 && i % 8 != 0) {
                if (SDL_HasIntersection(&add_shield[i].itemsRect, &ballPlay)) {
                    remove(add_shield[i].itemsRect);
                    Mix_PlayChannel(-1, protectedSound, 0);
                    isProtected = true;
                }
            }
        }

        // Nếu ball nằm trên bar
        for (int i = 0; i <= color_cur; i++) {
            if ((x >= color_bar[i].barRect.x-20) && (x <= color_bar[i].barRect.x+45) && (y >= color_bar[i].barRect.y-30) && (y <= color_bar[i].barRect.y-20)){
                ballUp = true;
                if (soundJump) {
                    score ++;
                    Mix_PlayChannel(-1, jumpsound, 0);
                    soundJump = false;

                }
            }
        }

        // Vẽ vòng tròn bảo vệ
        if (isProtected) {
            shieldRect.x = x-10;
            shieldRect.y = y-20;
            shieldRect.w = 40;
            shieldRect.h = 40;
            renderTexture(shieldPro, renderer, shieldRect.x, shieldRect.y, shieldRect.w, shieldRect.h);
        }

        // Nếu không được bảo vệ thì mất live
        for (int i = 0; i <= gai_bar.size(); i++) {
            if ((x >= gai_bar[i].barRect.x-20) && (x <= gai_bar[i].barRect.x+45) && (y >= gai_bar[i].barRect.y-30) && (y <= gai_bar[i].barRect.y-10)){
                if (!isProtected) {    
                    live--;
                    Mix_PlayChannel(-1, diesound, 0);
                    x = 200;
                    y = 58;
                } else {
                    ballUp = true;
                }
            }
        }

        if (ballUp) {
            y -= step/2;
        } else {
            y += step/2;
        }
        
        // Lưới bảo vệ bóng chỉ trong một thời gian
        if (color_cur % 25 == 0) {
            isProtected = false;
            remove(shieldRect);
        }
        
        if (!ballUp) soundJump = true;
        doNotMove = true;
        ballUp = false;
        
        // Vẽ thêm các bar
        if (color_bar[color_cur].barRect.y <= 450) color_cur++;
        if (gai_bar[gai_cur].barRect.y <= 250) gai_cur++;
        
        /* Vẽ các color_bar, gai_bar , heart, shield
        ** và cập nhật vị trí mới
        */
        for (int i = 0; i <= color_cur; i++) {
            color_bar[i].updatePos();
            renderTexture(colBar, renderer, color_bar[i].barRect.x, color_bar[i].barRect.y, color_bar[i].barRect.w, color_bar[i].barRect.h);
        }
        
        for (int i = 0; i <= gai_cur; i++) {
            gai_bar[i].updatePos();
            renderTexture(gai, renderer, gai_bar[i].barRect.x, gai_bar[i].barRect.y, gai_bar[i].barRect.w, gai_bar[i].barRect.h);
        }
        for (int i = 0; i <= color_cur; i++) {
            if (i % 8 == 0) {
                add_heart[i].updatePos();
                renderTexture(addHeart, renderer, add_heart[i].itemsRect.x,  add_heart[i].itemsRect.y, add_heart[i].itemsRect.w, add_heart[i].itemsRect.h);
            }
            if (i % 15 == 0 && i % 8 != 0) {
                add_shield[i].updatePos();
                renderTexture(shield, renderer, add_shield[i].itemsRect.x,  add_shield[i].itemsRect.y, add_shield[i].itemsRect.w, add_shield[i].itemsRect.h);
            }
        }
           
        if (live == 0) gameOver = true;
        
        /**
        * Nếu gameover, hiển thị background gameover 
        * Hiển thị điểm, các title và top 5 người cao điểm nhất
        */
        if (gameOver) {
            Mix_PauseMusic();
            renderTexture(gameover, renderer, 0, 0);
            renderTexture(title_score_last, renderer, 110, 220);
            renderTexture(Score_render_last, renderer, 270, 220);
            Mix_PlayChannel(-1, Mgameover, 0);
			SDL_Delay(10);
            for (int i = 0; i < 5; ++i) {
                if (score > arrScore[i]) {
                    for (int j = 3; j >= i; --j){
                        arrScore[j+1] = arrScore[j];
                    }
                    arrScore[i] = score;
                    break;
                }
            }
            for (int i = 0; i < 5; ++i) {
                printNumber(renderer, font2, arrScore[i], 220, 322+i*48);   
            }
            running = false;
            play = playAgain(renderer, font2); 
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}          
    }
    
    // Xoá bỏ SDL
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(gameover);
	SDL_DestroyTexture(heart);
    SDL_DestroyTexture(colBar);
    SDL_DestroyTexture(addHeart);
    SDL_DestroyTexture(_background);
	SDL_DestroyTexture(shield);
	SDL_DestroyTexture(gai);
    SDL_DestroyTexture(shieldPro);
    SDL_DestroyTexture(title_live);
    SDL_DestroyTexture(title_score);
    SDL_DestroyTexture(title_score_last);

    SDL_FreeSurface(lives);
    SDL_FreeSurface(scores);
    SDL_FreeSurface(scoresLast);

    TTF_Quit();
    Mix_CloseAudio();
    return play;

}


// Hiện Menu cho trò chơi
int showMenu(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font) 
{
    // quy định toạ độ của các chữ hiện
    SDL_Rect pos_arr[CHOICE_MENU];
    pos_arr[0].x = 150;
    pos_arr[0].y = 320;
    pos_arr[0].w = 150;
    pos_arr[0].h = 32;

    pos_arr[1].x = 185;
    pos_arr[1].y = 410;
    pos_arr[1].w = 60;
    pos_arr[1].h = 32;
    // Hai lựa chọn trong menu
    std::string arrMenu[CHOICE_MENU] = {"Play Game", "Exit"};
    SDL_Color color[CHOICE_MENU] = {BLACK_COLOR};

    // Toạ độ của trỏ chuột
    int xm = 0;
    int ym = 0;

    bool selected[CHOICE_MENU] = {0, 0};

    // Sự kiện trỏ chuột thực hiện
    SDL_Event m_event;
    while (true) {
        renderTexture(texture, renderer, 0, 0);
        for (int i = 0; i < CHOICE_MENU; ++i) {
            printText(renderer, font, color[i], arrMenu[i], pos_arr[i].x, pos_arr[i].y, pos_arr[i].w, pos_arr[i].h);
        }
        
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type) 
            {
            case SDL_QUIT:
                return 1;
                break;
            
            // Trường hợp chuột trỏ vào chữ thì chữ đó chuyển sang màu đỏ
            case SDL_MOUSEMOTION:
                mouse_motion(m_event, xm, ym, CHOICE_MENU, pos_arr, selected, color);
                break;

            // Trường hợp chuột ấn chọn thì sẽ return lại 0 (chơi tiếp) hoặc 1 (thoát ra)
            case SDL_MOUSEBUTTONDOWN:
                return mouse_button_down(m_event, xm, ym, CHOICE_MENU, pos_arr);
                break;

            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)    return 1;
                break;
            
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return 1;
}

// Kiểm tra chuột có trỏ đến vùng lựa chọn không
bool checkFocus(const int& x, const int& y, SDL_Rect rect) 
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        return true;

    return false; 
}

// Lựa chọn độ khó của game
int showLevel(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font) 
{
    // quy định toạ độ của các chữ hiện
    SDL_Rect pos_arr[LEVEL];
    pos_arr[0].x = 160;
    pos_arr[0].y = 270;
    pos_arr[0].w = 90;
    pos_arr[0].h = 25;

    pos_arr[1].x = 160;
    pos_arr[1].y = 387;
    pos_arr[1].w = 120;
    pos_arr[1].h = 25;

    pos_arr[2].x = 160;
    pos_arr[2].y = 503;
    pos_arr[2].w = 90;
    pos_arr[2].h = 25;
    // Hai lựa chọn trong menu
    std::string arrMenu[LEVEL] = {"EASY", "NORMAL", "HARD"};

    // Toạ độ của trỏ chuột
    int xm = 0;
    int ym = 0;

    bool selected[LEVEL] = {0, 0, 0};

    SDL_Color color[LEVEL] = {BLACK_COLOR};
    
    // Sự kiện trỏ chuột thực hiện
    SDL_Event m_event;
    while (true) {
        renderTexture(texture, renderer, 0, 0);
        for (int i = 0; i < LEVEL; ++i) {
            printText(renderer, font, color[i], arrMenu[i], pos_arr[i].x, pos_arr[i].y, pos_arr[i].w, pos_arr[i].h);
        }

        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type) 
            {
            // Trường hợp chuột trỏ vào chữ thì chữ đó chuyển sang màu đỏ
            case SDL_MOUSEMOTION:
                mouse_motion(m_event, xm, ym, LEVEL, pos_arr, selected, color);
                break;

            // Trường hợp chuột ấn chọn
            case SDL_MOUSEBUTTONDOWN:
                return mouse_button_down(m_event, xm, ym, LEVEL, pos_arr);
                break;
            
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
}

// Trường hợp chuột trỏ vào chữ sẽ chuyển sang màu đỏ
void mouse_motion(SDL_Event m_event, int xm, int ym, int numsOfChoice,SDL_Rect pos_arr[], bool selected[], SDL_Color color[]) 
{
    xm = m_event.motion.x;
    ym = m_event.motion.y;

    for (int i = 0; i < numsOfChoice; ++i) {
        if (checkFocus(xm, ym, pos_arr[i])) {
            if (selected[i] == false) {
                selected[i] = 1;
                color[i] = RED_COLOR;
            }
        } else {
            if (selected[i] == true) {
                selected[i] = 0;
                color[i] = BLACK_COLOR;
            }
        }             
    }
}

// Trường hợp khi ấn chọn thì trả về lựa chọn tương ứng
int mouse_button_down(SDL_Event m_event, int xm, int ym, int numsOfChoice, SDL_Rect pos_arr[])
{
    int ans;
    xm = m_event.motion.x;
    ym = m_event.motion.y;
    
    for (int i = 0; i < numsOfChoice; ++i) {
        if (checkFocus(xm, ym, pos_arr[i]))
            ans = i;
    }
    return ans;
}

int playAgain(SDL_Renderer* renderer, TTF_Font* font) 
{
    // quy định toạ độ của các chữ hiện
    SDL_Rect pos_arr[CHOICE_MENU];
    pos_arr[0].x = 55;
    pos_arr[0].y = 625;
    pos_arr[0].w = 130;
    pos_arr[0].h = 25;

    pos_arr[1].x = 270;
    pos_arr[1].y = 625;
    pos_arr[1].w = 60;
    pos_arr[1].h = 25;
    // Hai lựa chọn trong menu
    std::string arrMenu[CHOICE_MENU] = {"Play Again", "Exit"};
    SDL_Color color[CHOICE_MENU] = {BLACK_COLOR};

    // Toạ độ của trỏ chuột
    int xm = 0;
    int ym = 0;

    bool selected[CHOICE_MENU] = {0, 0};

    // Sự kiện trỏ chuột thực hiện
    SDL_Event m_event;
    while (true) {
        for (int i = 0; i < CHOICE_MENU; ++i) {
            printText(renderer, font, color[i], arrMenu[i], pos_arr[i].x, pos_arr[i].y, pos_arr[i].w, pos_arr[i].h);
        }
        
        while (SDL_PollEvent(&m_event)) {
            switch (m_event.type) 
            {
            case SDL_QUIT:
                return 1;
                break;
            
            // Trường hợp chuột trỏ vào chữ thì chữ đó chuyển sang màu đỏ
            case SDL_MOUSEMOTION:
                mouse_motion(m_event, xm, ym, CHOICE_MENU, pos_arr, selected, color);
                break;

            // Trường hợp chuột ấn chọn thì sẽ return lại 0 (chơi lại) hoặc 1 (thoát ra)
            case SDL_MOUSEBUTTONDOWN:
                return mouse_button_down(m_event, xm, ym, CHOICE_MENU, pos_arr);
                break;

            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)    return 1;
                break;
            
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return 1;
}

void remove(SDL_Rect &rect)
{
    rect.h = 0;
    rect.w = 0;
}