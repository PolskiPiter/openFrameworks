#pragma once

#include "ofMain.h"
#include <time.h>

class ofApp : public ofBaseApp{
	private:
		
		// Wektory ruchu - przyspieszenia, prêdkoœci, po³o¿enia
		ofVec2f a;
		ofVec2f v;
		ofVec2f vn_1;
		ofVec2f r;

		// Krok czasowy (krok ca³kowania w metodzie Eulera)
		float dt;

		//Sprawdzenie czy dosz³o do kolizji
		bool collision;

		//Zmienne z tekstami do wyœwietlenia na ekranie
		string aVec_string;
		string vVec_string;
		string rVec_string;

		string dt_string;

		string Description;

		//Czcionka do tekstu
		ofTrueTypeFont FontArial;

		// Pi³ka do koszykówki - Rysunek
		ofImage BasketballBall;

		//DŸwiêk odbicia pi³ki
		ofSoundPlayer BasketballSingleBounceBall;

	public:
		void setup();
		void update();
		void draw();

	
};
