#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* playerSurface;
SDL_Surface* txtSurface;
SDL_Texture* playerTexture;
SDL_Surface* battleselectsurface;
SDL_Texture* battleselectTexture;
SDL_Surface* enemySurface;
SDL_Texture* enemyTexture;
TTF_Font* font;
SDL_Texture* txtTexture;
Mix_Music* battlemusic;
Mix_Chunk* ping;
int tilex=1,tiley=1,moveanim=0,walkanim=32,dir=0,prevdir=0,playertexturex=1,playertexturey=1,currentdialogue=0,dialoguesize=0,dialogueprogress=0,enemycode=0;
bool running=false,battle=false,playerturn=true;
char right=0,up=0,left=0,down=0,z=0,x=0,battlemenu=0;
char dialogue[64][256]={};
SDL_Rect playerrect = { 0, 0, 24 ,32 },playertexturerect={0,0,24,32},tilerect={0,0,16,16},dialoguerect={0,0,160,48},txtRect,
selectbox={0,0,32,16},selecttexturebox={0,0,32,16},enemybox={0,0,0,0};
int lastTick = 0,currentmap=0;
unsigned char tilemap[5][9][10]={{
  {1,1,1,1,1,1,1,1,1,1},//0
  {1,0,0,0,0,0,0,0,0,1},//1
  {1,1,1,0,0,0,0,0,0,1},//2
  {1,0,0,0,0,0,0,0,0,1},//3
  {1,0,0,1,1,1,0,0,0,1},//4
  {1,0,0,0,0,0,0,0,0,1},//5
  {1,0,0,0,0,0,1,1,1,1},//6
  {1,0,0,0,0,0,0,0,0,0},//7
  {1,1,1,1,1,1,1,1,1,1}},//8
/* 0 1 2 3 4 5 6 7 8 9*/{
  {1,1,1,1,1,1,1,1,1,1},//0
  {1,0,0,0,0,0,0,0,0,1},//1
  {1,0,0,0,0,1,0,0,0,1},//2
  {1,0,0,0,0,0,0,0,0,1},//3
  {1,0,0,0,0,0,0,0,0,1},//4
  {1,0,0,0,0,0,0,0,0,1},//5
  {1,0,0,0,0,0,0,0,0,1},//6
  {0,0,0,0,0,0,0,0,0,0},//7
  {1,1,1,1,1,1,1,1,1,1}},//8
/* 0 1 2 3 4 5 6 7 8 9*/
};
const int interval = 1000; // 1초 간격

int BattleInit(){
  char temp[256]="res/Enemies/Enemy";
  char temp2[3]={};
  sprintf(temp2, "%d", enemycode);
  strcat(temp,temp2);
  strcat(temp,".png");

  enemySurface = IMG_Load(temp);
  if (enemySurface==NULL) {
  printf("이미지 불러오기 실패\n%s\n", SDL_GetError());
  return 1;
  }
  enemyTexture=SDL_CreateTextureFromSurface(renderer,enemySurface);
  enemybox = (SDL_Rect){ 80, 64, enemySurface->w, enemySurface->h };
  enemybox.x-=enemybox.w/2;
  SDL_FreeSurface(enemySurface);
  Mix_PlayMusic(battlemusic, -1);
  return 0;
}

int Init(){
  srand(time(NULL));
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Time stops for no one",
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_RenderSetLogicalSize(renderer,160,144);
  playerSurface = IMG_Load("res/char.png");
  battleselectsurface = IMG_Load("res/Battlemenu.png");
  if (playerSurface == NULL||battleselectsurface==NULL) {
  printf("이미지 불러오기 실패\n%s\n", SDL_GetError());
  return 1;
  }
  playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
  battleselectTexture = SDL_CreateTextureFromSurface(renderer, battleselectsurface);
  SDL_FreeSurface(playerSurface);
  SDL_FreeSurface(battleselectsurface);
  // 폰트 불러오기
  TTF_Init();
  font = TTF_OpenFont("res/Monocat_6x12.ttf", 12);
  if (font == NULL) {
  printf("폰트 불러오기 실패: %s\n", TTF_GetError());
  return 1;
  }
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  battlemusic = Mix_LoadMUS("res/Cigar Smoke.ogg");
    if (battlemusic == NULL) {
    printf("%s\n", Mix_GetError());
    return 1;
    }
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
  return 0;
}

int inputstuff(){
  if(z>0)z=1;
  if(x>0)x=1;
  if(left>0)left=1;
  if(right>0)right=1;
  if(down>0)down=1;
  if(up>0)up=1;
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
  switch (event.type) {
  // 창 닫기 버튼을 누르면 종료
  case SDL_QUIT: return 1;
  case SDL_KEYDOWN:
    switch(event.key.keysym.sym){
        case SDLK_a: case SDLK_LEFT:{if(left>0)left=1;else left=2;break;}
        case SDLK_d: case SDLK_RIGHT:{if(right>0)right=1;else right=2;break;}
        case SDLK_s: case SDLK_DOWN:{if(down>0)down=1;else down=2;break;}
        case SDLK_w: case SDLK_UP:{if(up>0)up=1;else up=2;break;}
        case SDLK_z:{if(z>0)z=1;else z=2;break;}
        case SDLK_x:{if(x>0)x=1;else x=2;break;}
    }
    break;
  case SDL_KEYUP:
    switch(event.key.keysym.sym){
        case SDLK_a: case SDLK_LEFT:{left=0;break;}
        case SDLK_d: case SDLK_RIGHT:{right=0;break;}
        case SDLK_s: case SDLK_DOWN:{down=0;break;}
        case SDLK_w: case SDLK_UP:{up=0;break;}
        case SDLK_z:{z=0;break;}
        case SDLK_x:{x=0;break;}
    }
  }
  break;
}
return 0;
}

int update(){
  if(currentdialogue<dialoguesize){
    if(dialogueprogress<strlen(dialogue[currentdialogue])){
      dialogueprogress++;
      if(z==2||x>0)dialogueprogress=strlen(dialogue[currentdialogue]);
      }
    else if(z==2){dialogueprogress=0;currentdialogue++;}
  }
  else if(battle){
    if(playerturn){
      if(right==2)battlemenu++;
      else if(left==2)battlemenu--;
      if(battlemenu<0)battlemenu=3;
      else if(battlemenu>3)battlemenu=0;
      if(z==2){
        switch(battlemenu){
          case 3:{battle=false;Mix_FadeOutMusic(500);break;}
        }
      }
    }
  }
  else{
    if(moveanim>0){
      if(walkanim>0){
        if(running)walkanim-=2;
        else walkanim--;
        }
      else walkanim=32;
      moveanim--;
      if(moveanim==0){
        if(rand() % 100>97){battle=true;playerturn=true;battlemenu=0;enemycode=0;if(BattleInit())return 1;}
        switch(dir){
          case 0:{tiley--;break;}
          case 1:{tilex++;break;}
          case 2:{tiley++;break;}
          case 3:{tilex--;break;}
        }
      }
    }
    if(moveanim==0&&!battle){
      if(z==2){
        int tempx=tilex,tempy=tiley;
        switch(dir){
          case 0:{tempy--;break;}
          case 1:{tempx++;break;}
          case 2:{tempy++;break;}
          case 3:{tempx--;break;}
        }
        switch(currentmap){
          case 1:{
            if(tempx==5&&tempy==2){
              currentdialogue=0;dialoguesize=2;dialogueprogress=0;
              char temp[55]="Test dialogue.";
              strcpy(dialogue[0],temp);
              char temp2[55]="Even more test stuff";
              strcpy(dialogue[1],temp2);
            }
            break;
          }
        }
      }
      else if(up>0){
        if(tilemap[currentmap][tiley-1][tilex]==0){if(x>0){moveanim=4;running=true;}else {moveanim=8;running=false;}}
        dir=0;
        }
      else if(right>0){
        if(tilemap[currentmap][tiley][tilex+1]==0){if(x>0){moveanim=4;running=true;}else {moveanim=8;running=false;}}
        dir=1;
        }
      else if(left>0){
        if(tilemap[currentmap][tiley][tilex-1]==0){if(x>0){moveanim=4;running=true;}else {moveanim=8;running=false;}}
        dir=3;
        }
      else if(down>0){
        if(tilemap[currentmap][tiley+1][tilex]==0){if(x>0){moveanim=4;running=true;}else {moveanim=8;running=false;}}
        dir=2;
        }
      
    }
    if(moveanim==0)walkanim=0;
    if(walkanim>24)playertexturerect.x=playertexturex*72;
    else if(walkanim>16)playertexturerect.x=playertexturex*72+24;
    else if(walkanim>8)playertexturerect.x=playertexturex*72+48;
    else playertexturerect.x=playertexturex*72+24;
    

    switch(currentmap){
      case 0:{
        if(tilex==9&&tiley==7){tilex=1;tiley=7;dir=1;currentmap=1;}
        break;
      }
      case 1:{
        if(tilex==0&&tiley==7){tilex=8;tiley=7;dir=3;currentmap=0;}
        break;
      }
    }
  }

  int temp=dir*32;
  temp+=playertexturey*128;
  playertexturerect.y=temp;
  playerrect.x=tilex*16+2*((dir==3&&moveanim>0)?-8+moveanim*(running?2:1):((dir==1&&moveanim>0)?8-moveanim*(running?2:1):0))-4;
  playerrect.y=tiley*16+2*((dir==0&&moveanim>0)?-8+moveanim*(running?2:1):((dir==2&&moveanim>0)?8-moveanim*(running?2:1):0))-16;
  return 0;
}
void render(){
  // 배경 새로 그리기

  if(battle){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(int i=0;i<4;i++){
      selectbox.x=4+40*i;
      selecttexturebox.y=i*16;
      if(i==battlemenu)selecttexturebox.x=32;
      else selecttexturebox.x=0;
      SDL_RenderCopy(renderer, battleselectTexture,&selecttexturebox, &selectbox);
    }
    
    SDL_RenderCopy(renderer, enemyTexture,NULL, &enemybox);
  }
  else{
    SDL_SetRenderDrawColor(renderer, 85, 85, 85, 255);
    SDL_RenderClear(renderer);

    for(int i=0;i<9;i++)
    for(int j=0;j<10;j++){
      tilerect.x=j*16;tilerect.y=i*16;
      if(tilemap[currentmap][i][j]==1){SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);SDL_RenderFillRect(renderer, &tilerect);}}
    // 이미지 그리기
    SDL_RenderCopy(renderer, playerTexture,&playertexturerect, &playerrect);
  }
  if(currentdialogue<dialoguesize){
      if(tiley>4&&battle)dialoguerect.y=0;
      else dialoguerect.y=96;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderFillRect(renderer,&dialoguerect);

      char temp[256]={};
      strcpy(temp,dialogue[currentdialogue]);
      temp[dialogueprogress+1]='\0';
      txtSurface = TTF_RenderText_Solid(font, temp, (SDL_Color){ 255, 255, 255, 255 });
      txtTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);
      txtRect = (SDL_Rect){ 0, dialoguerect.y, txtSurface->w, txtSurface->h };
      SDL_RenderCopy(renderer, txtTexture, NULL, &txtRect);
      SDL_FreeSurface(txtSurface);
    }
  // 화면 업데이트
  SDL_RenderPresent(renderer);
}

void Free(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_CloseAudio();
  SDL_DestroyTexture(txtTexture);
  SDL_DestroyTexture(playerTexture);
  SDL_DestroyTexture(battleselectTexture);
  SDL_DestroyTexture(enemyTexture);
  TTF_CloseFont(font);
  Mix_FreeMusic(battlemusic);
  Mix_CloseAudio();
  SDL_Quit();
}

int main() {
// SDL 초기화
if(Init())return 0;
  // 메인 루프
  while (true) {
  // 입력 처리
  if(inputstuff())return 0;

  if(update())return 0;
  render();
  // 60프레임 설정
  SDL_Delay(1000 / 60);
  }
// SDL 리소스 해제
Free();
}