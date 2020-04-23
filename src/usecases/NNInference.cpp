/*
 * NNInference.hpp
 *
 *  Created on: 4 19, 2020
 *      Author: Fu GUo
 */
#include "NNInference.hpp"
#include "../connector/ImageLoad.hpp"
#include "../dataflow/Vertex.hpp"
#include "../batching/Resize.hpp"
#include "../batching/Inference.hpp"
using namespace std;

NNInference::NNInference() :
		Dataflow() {

	imgload = new ImageLoad("../data/imgs/",10,0, rank, worldSize,false);
	resize = new Resize(1, rank, worldSize,false,128,128);
	inference = new Inference(2,rank,worldSize,false);
	// Simple chain
	addLink(imgload ,resize);
	addLink(resize,inference );
	imgload ->initialize();
	resize ->initialize();
	inference->initialize();
	}

NNInference::~NNInference() {
	delete imgload;
	delete resize;
	delete inference ;
}
