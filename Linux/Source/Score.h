/*
 * Score.h
 *
 *  Created on: Jun 1, 2020
 *      Author: niloufar
 */
#include <vector>
#ifndef SCORE_H_
#define SCORE_H_

namespace std {

class Score {
public:
	Score();
	float score;
	vector<float> distances;
	float label_score;
	float rmsd;
	float TMScore;
};

} /* namespace std */

#endif /* SCORE_H_ */
