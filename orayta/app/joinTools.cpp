#include <cassert>
#include "joinTools.h"
#include "location.h"

void join(JoinerQueue & joinerQueue, SourceTextQueue & sourceTextQueue)
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
			second_active.second() = iter->second();
			joinerQueue.push_back(second_active);
		}
	}
}

void join(JoinerQueue & joinerQueue, CommentaryQueue & commentaryQueue)
{
	JoinerQueue::iterator jit = joinerQueue.begin();
	JoinerQueue::iterator jend = joinerQueue.end();
	CommentaryQueue::iterator cit = commentaryQueue.begin();
	CommentaryQueue::iterator cend = commentaryQueue.end();

	while(moveToHighestLocationTogether(jit, jend, cit, cend)) {
		jit++;
		cit++;
		
	/* 
	 * commentary is queue of comments on one eg mishna
	 * cycle through all of them, call attach(comment)
	 * for now, this code is a mess. B'e"H I'll clean up the typedefs later
	 */
		// cit is iterator-to-union, first of which is queu. Sorry.
		for(std::deque<WComment>::iterator i = cit->first().begin();
				i != cit->first().end(); i++)
			jit->first().attach(*i);
		/*
		 * this has to be the murkiest code I've written in my life
		 * I really don't know what came over me!
		 */
	}
}
