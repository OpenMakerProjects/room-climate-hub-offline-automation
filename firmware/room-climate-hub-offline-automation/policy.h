#pragma once
#include <stdint.h>
struct OfflinePolicy{
 bool doorOpen=true,rawOpen=true,dark=false,fault=false;uint32_t changedAt=0;
 uint8_t red=0,green=0,blue=0;
 void update(bool open,int adc,uint32_t now){
  if(open!=rawOpen){rawOpen=open;changedAt=now;}
  if(rawOpen!=doorOpen&&uint32_t(now-changedAt)>=50)doorOpen=rawOpen;
  fault=adc<0||adc>4095;
  if(!fault){if(adc<=1200)dark=true;else if(adc>=1600)dark=false;}
  red=green=blue=0;
  if(!fault&&doorOpen){if(dark){red=green=blue=120;}else green=20;}
 }
};
