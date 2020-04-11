/**
 * Copyright (c) 2020 University of Luxembourg. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be
 * used to endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY OF LUXEMBOURG AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE UNIVERSITY OF LUXEMBOURG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

/*
 * PairPartition.hpp
 *
 *  Created on: May 16, 2018
 *  Author: amal.tawakuli, martin.theobald
 */

#ifndef PARTITIONING_PAIRPARTITION_HPP_
#define PARTITIONING_PAIRPARTITION_HPP_

#include <iostream>
#include <unordered_map>

using namespace std;

template<typename K, typename V, typename K_hash>
class PairPartition {

public:

	PairPartition() {
	}

	~PairPartition() {
	}

	typename unordered_map<K, V>::iterator get(K key) {
		//cout << "\nGET KEY: " + key << endl;
		return values.find(key);
	}

	void setValue(K key, V val) {
		typename unordered_map<K, V>::iterator it = get(key);
		if (it != NULL) {
			values[it].second = val;
		}
	}

	void add(K key) {
		typename unordered_map<K, V>::iterator it = get(key);
		if (it != values.end()) {
			it->second = it->second + 1;
		} else {
			values.insert(it, make_pair(key, 1));
		}
	}

	void add(K key, V value) {
		typename unordered_map<K, V>::iterator it = get(key);
		if (it != values.end()) {
			it->second = it->second + value;
		} else {
			values.insert(it, make_pair(key, value));
		}
	}

	void clear() {
		values.clear();
	}

	void print() {
		typename unordered_map<K, V>::iterator it = values.begin();
		int i = 0;
		while (it != values.end()) {
			cout << i << "\t KEY [" << it->first << "] | VALUE [" << it->second
					<< "]" << endl;
			it++;
			i++;
		}
	}

private:

	//unordered_map<K, V> values; // default hash library
	unordered_map<K, V, K_hash> values; // custom hash library (CityHash)

};

#endif /* PARTITIONING_PAIRPARTITION_HPP_ */
