/*
 * NNInference.hpp
 *
 *  Created on: 4 19, 2020
 *      Author: Fu GUo
 */

#ifndef USECASES_NNINFERENCE_HPP_
#define USECASES_NNINFERENCE_HPP_

#include "../dataflow/Dataflow.hpp"

using namespace std;

class NNInference: public Dataflow {

public:

	Vertex *imgload,*resize,*inference;

	NNInference();

	~NNInference();

};

#endif /* USECASES_NNINFERENCE_HPP_ */
