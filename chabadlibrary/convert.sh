#!/bin/bash
# Usage: in_file out_format book|set calibre_options

if ! [  "$1" -a "$2"  -a "$3" ]; then
 echo <<- EOF 
 Usage: in_file out_format book|set calibre_options
 the third argument is book if in_file is a book
 or set of in_file is a set
 everything after that is given to calibre ebook-convert
EOF
 exit
fi

readonly file=$1
readonly format=$2
readonly type=$3
shift 3
read calibre_options <<< $*
echo $calibre_options

get_title() {	# arg: file to extract title from
	sed -n -e "/div class=heading/{ 
		s/.*heading>\(.*\)<.*/\1/p
		q
}" $1
}
get_author() { # arg: file to extract from
	cur_file=$(readlink -f $1)
	in_dir=$(dirname $cur_file)	# directory $1 is in
	parent_dir=$(dirname $in_dir)

	# the heading of index.htm in author's folder is author
	author=$(get_title $parent_dir/index.htm)
	# For a Rebbe, has this word.
	author=${author/ספרי/}
	author=$(sed -e s/[[:space:]]*ספרי[[:space:]]*// <<< $author)

	echo $author
}
convert() {	# args: filename out_dir title author
	# doesn't generate title so if type==set can stick in prefix
	# doesn't generate author because diffrent if set
	ebook-convert "$1" "${2}/${3}.${format}" \
		--title "$3" --authors "$4" --language Hebrew \
		--toc-threshold 0 --max-toc-links 0 \
		--level1-toc '//h:div[@class="heading"]' \
		--chapter-mark rule $calibre_options
}

# gets author of set or of sefer
author="$(get_author $file)"
if ! [ -e "$author" ]; then mkdir "$author"; fi

if [ $type == set ]; then
	series="$(get_title $file)"
	o_dir="${author}/${series}"
	if ! [ -e "$o_dir" ]; then mkdir "$o_dir"; fi

	for i in */index.htm; do
		convert "$i" "$o_dir" "$series $(get_title $i)" "$author"
	done
elif [ $type == book ]; then
	convert "$file" "${author}" "$(get_title $file)" "$author"
else
	echo Error:arg3 type == $type
fi
