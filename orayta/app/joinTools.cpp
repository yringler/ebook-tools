#include <cassert>
#include "joinTools.h"
#include "location.h"

void connect(JoinerQueue & joinerQueue, SourceTextQueue & sourceTextQueue)
{
	// where first is binder and second is location
	Joiner first_active;
	first_active.use(1);
	Joiner second_active;
	second_active.use(2);

	for(SourceTextQueue::iterator iter = sourceTextQueue.begin();
			iter != sourceTextQueue.end(); iter++) {
		if(iter->active() == 1) {
			// set joiner to source text
			first_active.first().to(iter->first());
			joinerQueue.push_back(first_active);
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
