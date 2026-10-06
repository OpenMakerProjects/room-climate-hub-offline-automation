#include <cassert>
#include "../firmware/room-climate-hub-offline-automation/policy.h"
int main(){
 OfflinePolicy p;p.update(true,1000,0);assert(p.dark&&p.red==120&&p.blue==120);
 p.update(true,1400,10);assert(p.dark);p.update(true,1600,20);assert(!p.dark&&p.green==20&&p.red==0);
 p.update(true,1400,30);assert(!p.dark);p.update(true,1200,40);assert(p.dark);
 p.update(false,1000,100);assert(p.doorOpen);p.update(false,1000,149);assert(p.doorOpen);
 p.update(false,1000,150);assert(!p.doorOpen&&p.red==0&&p.green==0);
 p.update(true,1000,200);p.update(false,1000,220);p.update(false,1000,300);assert(!p.doorOpen);
 p.update(true,-1,400);p.update(true,-1,450);assert(p.fault&&p.red==0);
 p.update(true,4096,460);assert(p.fault);p.update(true,2000,470);assert(!p.fault&&p.green==20);
 OfflinePolicy w;w.doorOpen=false;w.rawOpen=false;w.update(true,2000,0xfffffff0u);w.update(true,2000,0x22u);assert(w.doorOpen);
}
