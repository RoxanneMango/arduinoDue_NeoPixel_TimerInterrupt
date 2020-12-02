#ifndef NEO_PIXEL_H
#define NEO_PIXEL_H

#include <Adafruit_NeoPixel.h>

class NeoPixelController
{
private:
	unsigned int pixelNum;
	unsigned int pixelPin;

	Adafruit_NeoPixel neoPixel;
	
public:
	NeoPixelController(unsigned int pixelNum, unsigned int pixelPin) : neoPixel(pixelNum, pixelPin)
	{}
	~NeoPixelController()
	{}
	
	void init()
	{
		neoPixel.begin();
		neoPixel.clear();
		neoPixel.show();		
	}
	
	void setColor(unsigned int index, uint8_t r, uint8_t g, uint8_t b)
	{
		neoPixel.setPixelColor(index, neoPixel.Color(r, g, b));
	}
	
	void setColor(uint8_t r, uint8_t g, uint8_t b)
	{
		neoPixel.fill(neoPixel.Color(r, g, b));
	}
	
	void clear()
	{
		neoPixel.clear();
	}
	
	void update()
	{
		neoPixel.show();
	}
};

#endif // NEO_PIXEL_H