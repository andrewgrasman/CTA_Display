#include "drivers/ledLines.h"

const uint8_t redlp[]={0, 1, 2, 3, 4, 5, 6, 7, 8};//stations then last pixel
const uint8_t bluelp[]={9, 10, 11, 12, 13, 14, 15, 16, 17};
const uint8_t greenlp[]={18, 19, 20, 21, 22, 23, 24, 25, 26};
const uint8_t orangelp[]={27, 28, 29, 30, 31, 32, 33, 34, 35};
const uint8_t purplelp[]={36, 37, 38, 39, 40, 41, 42, 43, 44};
const uint8_t whitepurplelp[]={45, 46, 47};
const uint8_t yellowlp[]={48};
const uint8_t pinklp[]={49};
const uint8_t brownlp[]={50};
const uint32_t colors[NUM_LINES] = {
	0xFF0000, // RED
	0x0000FF, // BLUE
	0x00FF00, // GREEN
	0xFFA500, // ORANGE
	0x800080, // PURPLE
	0xFF99FF, // WHITE_PURPLE
	0xFFFF00, // YELLOW
	0xFFC0CB, // PINK
	0xA52A2A  // BROWN
};

Adafruit_NeoPixel strip1(1,7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(1,15, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(1,16, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(1,17, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5(1,18, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6(1,8, NEO_GRB + NEO_KHZ800);

void changeLines(uint8_t line,uint8_t* positions){
	int i=0,index=0,offset;
	switch(line){
		case RED:
		offset=0;// offsets are sum of last pixel from previous train lines on their neopixel strip
		for(i;i<redlp[5];i++){//5 is the last station in the phyisical strip before continue in loop
			if(redlp[index]==i){//TODO: change to redlp[positions[index]] with gaurd once each stations position is known
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<redlp[sizeof(redlp)];i++){// sizeof uint8_t is one so no need to divide
			if(redlp[index]==i){
			strip1.setPixelColor(offset+i,0);//TODO: update strips for implementation
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;

		case BLUE:
		offset=0;
		for(i;i<bluelp[5];i++){
			if(bluelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<bluelp[sizeof(bluelp)];i++){
			if(bluelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case GREEN:
		offset=0;
		for(i;i<greenlp[5];i++){
			if(greenlp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<greenlp[sizeof(greenlp)];i++){
			if(greenlp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;

		case ORANGE:
		offset=0;
		for(i;i<orangelp[5];i++){
			if(orangelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<orangelp[sizeof(orangelp)];i++){
			if(orangelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;

		case PURPLE:
		for(i;i<purplelp[sizeof(purplelp)];i++){
			if(purplelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case WHITE_PURPLE:
		for(i;i<whitepurplelp[5];i++){
			if(whitepurplelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<whitepurplelp[sizeof(whitepurplelp)];i++){
			if(whitepurplelp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case YELLOW:
		for(i;i<yellowlp[sizeof(yellowlp)];i++){
			if(yellowlp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case PINK:
		for(i;i<pinklp[5];i++){
			if(pinklp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<pinklp[sizeof(pinklp)];i++){
			if(pinklp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case BROWN:
		for(i;i<brownlp[5];i++){
			if(brownlp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<brownlp[sizeof(brownlp)];i++){
			if(brownlp[index]==i){
			strip1.setPixelColor(offset+i,0);
			index++;
			}	else
			strip1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
	}
}
void changeLines(uint8_t line, int* positions,float* progress){
	//TODO: when done with above implement [0,1) progress to chose led for train position
	//possibly have other call this but with progress=0 for each position
}
void updateLines(){
	strip1.show();
	strip2.show();
	strip3.show();
	strip4.show();
	strip5.show();
	strip6.show();
}
void initLines(){
	strip1.begin();
	strip2.begin();
	strip3.begin();
	strip4.begin();
	strip5.begin();
	strip6.begin();
	strip1.clear();
	strip2.clear();
	strip3.clear();
	strip4.clear();
	strip5.clear();
	strip6.clear();
	updateLines();
}