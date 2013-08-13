#/bin/bash
# usage: director_of_authors, out_format calibre_options

# yeah, I know, this is a really clumsy way of implementing base_dir arg, 
# but I'm tired now, maybe I'll clean it up later
# it up later
old_dir=$PWD
cd $1
if [ "${PWD##*/}" != books ]; then echo error; exit; fi
shift

if [ ! "$1" ]; then echo What format? && exit; fi

script_parent=$(dirname $0)
out_format=$1
shift
calibre_options="$*"

# structure of books dir: author/book OR author/set
# go through all of those directories
# remember: depth 1 is all dirs in current dir, 2 is all in those dirs
for book_folder in $(find -not -path \*css\* -type d -maxdepth 2 -mindepth 2)
do
	# if its a set
	found=$(sed -e "/^#/d" "$script_parent/set.txt" | \
		grep ${book_folder##.*/})
	if [ $found ]; then
		type=set
	else
		type=book
	fi
	# saves all in a directory called $out_format
	${script_parent}/convert.sh "${old_dir}/$out_format" $book_folder/index.htm \
		$out_format $type $calibre_options
done

cd $old_dir
