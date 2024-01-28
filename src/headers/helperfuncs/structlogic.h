#ifndef _STRUCTLOGIC_H_
#define _STRUCTLOGIC_H_
#include "menu.h"
#include "gamestate.h"
#include "Cnake.h"
#include "Cnakebody.h"
#include "fruit.h"

struct Menu* InitializeMenu(void);
struct Gamestate* InitializeGamestate(void);
struct Cnake* InitializeCnake(void);
struct Cnakebody* InitializeCnakebody(int xpos, int ypos);
struct Fruit* InitializeFruit(void);
void LinkMenuAndGamestate(struct Menu* menu, struct Gamestate* gamestate);
void FreeMenu(struct Menu* menu);
void FreeGamestate(struct Gamestate* gamestate);
void FreeCnake(struct Cnake* cnake);
void FreeCnakebody(struct Cnakebody* cnakebody);
void FreeFruit(struct Fruit* fruit);
struct Cnakebody* GetLastCnakebody(struct Cnakebody* cnakebody);
void CopyCnake(struct Cnake* original, struct Cnake* copy);
void InitializeAndUpdateCnakebody(struct Cnakebody* parent, struct Cnakebody* originalCnakebody);

#endif
