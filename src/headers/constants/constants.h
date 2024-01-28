#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define SCREEN_W 600
#define SCREEN_H SCREEN_W
#define WINPOS_X 500
#define WINPOS_Y 20
#define HEAD_H 10
#define HEAD_W 10
#define GRIDCELL_H SCREEN_H / HEAD_H
#define GRIDCELL_W SCREEN_W / HEAD_W
#define GAMENAME "Cnake"
#define SLEEP 0.5
#define SDLSLEEP 50
#define NUMOFCOMPUTERMOVES GRIDCELL_H*GRIDCELL_W
#define RANDOMRUNS 10000
#define RANDOMPATHLENGTH 15
#define LOGDIR "/Cnake/logs"
#define MAINMENUIMG "/Cnake/img/CnakeMenu.png"

#endif
