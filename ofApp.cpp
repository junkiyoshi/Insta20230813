#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	float span = 1;
	ofColor color;

	for (float x = ofGetWindowWidth() * -0.5 + 30; x < ofGetWindowWidth() * 0.5 - 30 - span; x += span) {

		for (float y = ofGetWindowHeight() * -0.5 + 30; y < ofGetWindowHeight() * 0.5 - 30 - span; y += span) {

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			for (int i = this->mesh.getNumVertices() - 4; i < this->mesh.getNumVertices(); i++) {

				auto noise_value = ofMap(ofNoise(this->mesh.getVertex(i).x * 0.002, this->mesh.getVertex(i).y * 0.002, glm::length(this->mesh.getVertex(i)) * 0.03 - ofGetFrameNum() * 0.03), 0, 1, 0, 3);
				int int_noise_value = noise_value;
				float param = noise_value - int_noise_value;
				param = abs(param - 0.5);

				auto hue = int_noise_value == 0 ? 0 : int_noise_value == 1 ? 140 : 192;
				auto alpha = param < 0.35 ? ofMap(param, 0, 0.35, 255, 0) : 0;

				color.setHsb(hue, 255, 255, alpha);
				this->mesh.addColor(color);
			}

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	this->mesh.draw();

	//ostringstream os;
	//os << setw(4) << setfill('0') << ofGetFrameNum();
	//ofImage image;
	//image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	//image.saveImage("image/cap/img_" + os.str() + ".jpg");
	//if (ofGetFrameNum() >= 20 * 25) {

	//	std::exit(1);
	//}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}