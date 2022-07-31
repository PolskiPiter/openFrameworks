#pragma once

#include "ofMain.h"
#include <math.h>
#include <time.h>

//Sta³a: liczba PI
#define M_PI 3.14159265358979323846

class ofApp : public ofBaseApp{

	private:
		//Atrybuty
		int V;
		int deep;
		int counter_param_scale;

		vector<float> scale_parameters;
		vector<float> center_triangle_x;
		vector<float> center_triangle_y;
		
		clock_t time_animation;
		
		ofVec2f ver1;
		ofVec2f	ver2;
		ofVec2f ver3;
	
		vector<ofVec2f> array_vertex;
		
		ofColor Blue_hex_00002d;
		ofColor Blue_hex_4b2dff;
		ofColor Red_hex_ff0f55;

		//Metody
		void CalculateVertex(vector<ofVec2f> & array_vertex, ofVec2f ver1, ofVec2f ver2, ofVec2f ver3, int deep);

	public:
		//Metody
		void setup();
		void update();
		void draw();
		
};
