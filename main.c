#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* playerSurface;
SDL_Texture* playerTexture;
int tilex=1,tiley=1,moveanim=0,walkanim=32,dir=0,prevdir=0,playertexturex=1,playertexturey=1,currentdialogue=0,dialoguesize=0,dialogueprogress=0;
bool right=false,up=false,left=false,down=false,z=false;
char dialogue[64][128]={};
SDL_Rect playerrect = { 0, 0, 24 ,32 },playertexturerect={0,0,24,32},tilerect={0,0,16,16},dialoguerect={0,0,160,64};
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

int Init(){
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Time stops for no one",
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 144, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_RenderSetLogicalSize(renderer,160,144);
  playerSurface = IMG_Load("res/char.png");
  if (playerSurface == NULL) {
  printf("이미지 불러오기 실패\n%s\n", SDL_GetError());
  return 1;
  }
  playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
  return 0;
}

int inputstuff(){
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
  switch (event.type) {
  // 창 닫기 버튼을 누르면 종료
  case SDL_QUIT: return 1;

  case SDL_KEYDOWN:
    switch(event.key.keysym.sym){
        case SDLK_a: case SDLK_LEFT:{left=true;break;}
        case SDLK_d: case SDLK_RIGHT:{right=true;break;}
        case SDLK_s: case SDLK_DOWN:{down=true;break;}
        case SDLK_w: case SDLK_UP:{up=true;break;}
        case SDLK_z:{z=true;break;}
    }
    break;
  case SDL_KEYUP:
    switch(event.key.keysym.sym){
        case SDLK_a: case SDLK_LEFT:{left=false;break;}
        case SDLK_d: case SDLK_RIGHT:{right=false;break;}
        case SDLK_s: case SDLK_DOWN:{down=false;break;}
        case SDLK_w: case SDLK_UP:{up=false;break;}
        case SDLK_z:{z=false;break;}
    }
  }
  break;
}
return 0;
}

void update(){
  if(currentdialogue<dialoguesize){
  }
  else{
    if(moveanim>0){
      if(walkanim>0)walkanim--;
      else walkanim=32;
      moveanim--;
      if(moveanim==0){
        switch(dir){
          case 0:{tiley--;break;}
          case 1:{tilex++;break;}
          case 2:{tiley++;break;}
          case 3:{tilex--;break;}
        }
      }
    }
    if(moveanim==0){
      if(up){
        if(tilemap[currentmap][tiley-1][tilex]==0)moveanim=8;
        dir=0;
        }
      else if(right){
        if(tilemap[currentmap][tiley][tilex+1]==0)moveanim=8;
        dir=1;
        }
      else if(left){
        if(tilemap[currentmap][tiley][tilex-1]==0)moveanim=8;
        dir=3;
        }
      else if(down){
        if(tilemap[currentmap][tiley+1][tilex]==0)moveanim=8;
        dir=2;
        }
      else if(z){
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
              currentdialogue=0;dialoguesize=1;dialogueprogress=0;
              char temp[55]="Test dialogue.";
              strcpy(dialogue[0],temp);
            }
            break;
          }
        }
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
  playerrect.x=tilex*16+2*((dir==3&&moveanim>0)?-8+moveanim:((dir==1&&moveanim>0)?8-moveanim:0))-4;
  playerrect.y=tiley*16+2*((dir==0&&moveanim>0)?-8+moveanim:((dir==2&&moveanim>0)?8-moveanim:0))-16;
}
void render(){
  // 배경 새로 그리기

  SDL_SetRenderDrawColor(renderer, 0, 0, 170, 255);
  SDL_RenderClear(renderer);

  // 사각형 그리기
  SDL_RenderFillRect(renderer, &playerrect);

  for(int i=0;i<9;i++)
  for(int j=0;j<10;j++){
    tilerect.x=j*16;tilerect.y=i*16;
    if(tilemap[currentmap][i][j]==1){SDL_SetRenderDrawColor(renderer, 85, 85, 255, 255);SDL_RenderFillRect(renderer, &tilerect);}}
  // 이미지 그리기
  SDL_RenderCopy(renderer, playerTexture,&playertexturerect, &playerrect);

  if(currentdialogue<dialoguesize){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer,&dialoguerect);
  }

  // 화면 업데이트
  SDL_RenderPresent(renderer);
}

void Free(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
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

  update();
  render();
  // 60프레임 설정
  SDL_Delay(1000 / 60);
  }
// SDL 리소스 해제
Free();
}