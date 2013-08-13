#/bin/bash
# usage: out_format calibre_options
#	run from books dir

script_parent=$(dirname $0)
out_format=$1
shift
calibre_options="$*"

# structure of books dir: author/book OR author/set
# go through all of those directories
# remember: depth 1 is all dirs in current dir, 2 is all in those dirs
for i in $(find -not -path \*css\* -type d -maxdepth 2 -mindepth 2); do
	# if its a set
	if grep -q ${i##/} $script_parent/set.txt; then
		type=set
	else
		type=book
	fi
	${script_parent}/convert.sh $i $out_format $calibre_options
done
