#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh_list.clear();

	auto radius = 300;
	auto deg_start = 0;

	for (auto radius = 50; radius < 350; radius += 25) {

		ofMesh mesh;

		for (auto deg = deg_start; deg < deg_start + 360; deg += 60) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(100 * cos(deg * DEG_TO_RAD), 100 * sin(deg * DEG_TO_RAD));
			mesh.addVertex(glm::vec3(location, 0));
			mesh.addVertex(glm::vec3(location, 50 + 100 * ofNoise(noise_location.x * 0.003, noise_location.y * 0.003, radius * 0.005 + ofGetFrameNum() * 0.01)));
		}

		for (auto i = 0; i < mesh.getVertices().size(); i++) {

			mesh.addIndex(i);
			mesh.addIndex((i + 1) % mesh.getVertices().size());
			mesh.addIndex((i + 2) % mesh.getVertices().size());
		}

		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& mesh : this->mesh_list) {

		ofSetColor(239);
		mesh.draw();

		ofNoFill();
		ofSetColor(39);
		for (auto i = 0; i < mesh.getVertices().size(); i += 2) {

			ofBeginShape();
			ofVertex(mesh.getVertex(i));
			ofVertex(mesh.getVertex((i + 1) % mesh.getVertices().size()));
			ofVertex(mesh.getVertex((i + 3) % mesh.getVertices().size()));
			ofVertex(mesh.getVertex((i + 2) % mesh.getVertices().size()));
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}