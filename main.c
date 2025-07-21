#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdbool.h>


SDL_Window* window;
SDL_Renderer* renderer;
int x=0,y=0;
float xvelocity=0,yvelocity=0;
bool right=false,up=false,left=false,down=false,z=false;
SDL_Rect playerrect = { 0, 0, 16 ,16 },tilerect={0,0,16,16};
int lastTick = 0,currentmap=0;
unsigned char tilemap[5][15][16]={{
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
  {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
};
const int interval = 1000; // 1초 간격

int Init(){
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Time stops for no one",
  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 240, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
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
  if(left)xvelocity=-3;
  else if(right)xvelocity=3;
  else xvelocity=0;
  if((xvelocity>0&&tilemap[currentmap][y/16][x/16+1]==1)||(xvelocity<0&&tilemap[currentmap][y/16][x/16]==1))xvelocity=0;
  if(tilemap[currentmap][1+y/16][x/16]==0&&tilemap[currentmap][1+y/16][1+x/16]==0)yvelocity+=0.5f;
  else if(z){yvelocity=-10;z=false;}
  else {yvelocity=0;y/=16;y*=16;}
  x+=xvelocity;
  y+=yvelocity;
  playerrect.x=x;
  playerrect.y=y;
}
void render(){
  // 배경 새로 그리기

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // 사각형 그리기
  SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
  SDL_RenderFillRect(renderer, &playerrect);

  for(int i=0;i<15;i++)
  for(int j=0;j<16;j++){
    tilerect.x=j*16;tilerect.y=i*16;
    if(tilemap[currentmap][i][j]==1){SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);SDL_RenderFillRect(renderer, &tilerect);}}
  // 이미지 그리기
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