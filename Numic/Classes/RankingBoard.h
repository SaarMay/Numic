#ifndef _RANKING_BOARD_H_
#define _RANKING_BOARD_H_ 

#include "allScene.h"
#include <fstream>
USING_NS_CC;

class RankingBoard : public Layer
{
public:
	RankingBoard();
	~RankingBoard();

	virtual bool init();

	void getInfo();			// Get ranking information from rank.txt
	
	CREATE_FUNC(RankingBoard);
	/* data */
};

#endif