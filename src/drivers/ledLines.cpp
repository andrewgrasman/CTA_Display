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
	0xFFFFFF, // WHITE_PURPLE
	0xFFFF00, // YELLOW
	0xFFC0CB, // PINK
	0xA52A2A  // BROWN
};

Adafruit_NeoPixel line1(1,48, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel line2(1,48, NEO_GRB + NEO_KHZ800);

void changeLines(uint8_t line,uint8_t* positions){
	int i=0,index=0,offset;
	switch(line){
		case RED:
		offset=0;
		for(i;i<redlp[5];i++){
			if(redlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<redlp[sizeof(redlp)];i++){
			if(redlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;

		case BLUE:
		offset=0;
		for(i;i<bluelp[5];i++){
			if(bluelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<bluelp[sizeof(bluelp)];i++){
			if(bluelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case GREEN:
		offset=0;
		for(i;i<greenlp[5];i++){
			if(greenlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<greenlp[sizeof(greenlp)];i++){
			if(greenlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;

		case ORANGE:
		offset=0;
		for(i;i<orangelp[5];i++){
			if(orangelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<orangelp[sizeof(orangelp)];i++){
			if(orangelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;

		case PURPLE:
		for(i;i<purplelp[sizeof(purplelp)];i++){
			if(purplelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case WHITE_PURPLE:
		for(i;i<whitepurplelp[5];i++){
			if(whitepurplelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<whitepurplelp[sizeof(whitepurplelp)];i++){
			if(whitepurplelp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case YELLOW:
		for(i;i<yellowlp[sizeof(yellowlp)];i++){
			if(yellowlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case PINK:
		for(i;i<pinklp[5];i++){
			if(pinklp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<pinklp[sizeof(pinklp)];i++){
			if(pinklp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
		case BROWN:
		for(i;i<brownlp[5];i++){
			if(brownlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		offset=0;
		for(i;i<brownlp[sizeof(brownlp)];i++){
			if(brownlp[index]==i){
			line1.setPixelColor(offset+i,0);
			index++;
			}	else
			line1.setPixelColor(offset+i,colors[line]);
		}
		break;
		
	}
}
void changeLines(uint8_t line, int* positions,float* progress){
}
void updateLines(){
	line1.show();
	line2.show();
}
void initLines(){
	line1.begin();
	line2.begin();
	line1.clear();
	line2.clear();
	updateLines();
}