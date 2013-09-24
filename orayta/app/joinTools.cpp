#include <cassert>
#include "joinTools.h"
#include "location.h"

void connect(JoinerQueue & joinerQueue, SourceTextQueue & sourceTextQueue)
{
	Joiner tmp;
	tmp.use(1);

	for(SourceTextQueue::iterator iter = sourceTextQueue.begin();
			iter != sourceTextQueue.end(); iter++) {
		if(iter->active() == 1) {
			// set joiner to source text
			tmp.first().to(iter->first());
			joinerQueue.push_back(tmp);
		} else {
			joinerQueue.push_back(*iter);
		}
	}
}

void connect(JoinerQueue & joinerQueue, CommentaryQueue & commentaryQueue)
{
	JoinerQueue::iterator jit;
	JoinerQueue::iterator jend = joinerQueue.end();
	CommentaryQueue::iterator cit;
	CommentaryQueue::iterator cend = CommentaryQueue.end();

	while(moveToHighestLocationTogether(jit, jend, cit, cend)) {
		jit++;
		cit++;
		// attach comment to source text
		jit->first().attach(cit->first());
	}
}
