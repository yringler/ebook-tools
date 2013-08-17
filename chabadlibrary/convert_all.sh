#/bin/bash
# usage: director_of_authors, out_format [calibre_options]

# folder that the script and stuff are in
script_parent="$(dirname "$(readlink -f "$0")" )"

# loc of chabadlibrary.org/books on hard drive
readonly books_dir="$(readlink -f "$1")"
if [ "${books_dir##*/}" != books ]; then echo not given books dir; exit; fi

if [ ! "$2" ]; then 
	echo What format? && exit
else 
	out_format=$2
fi

shift 2		# allows to easily give all others args to calibre_options
calibre_options="$*"

# structure of books dir: author/book OR author/set
# go through all of those directories
# remember: depth 1 is all dirs in current dir, 2 is all in those dirs
for f in $(find "$books_dir" -maxdepth 2 -mindepth 2 \
	-not -path \*css\* -type d)
do
		### if its a set of seforim ###
	# pipe all lines of set.txt (except comments) to grep
	found="$(sed -e "/^#/d" "${script_parent}"/set.txt | grep "${f##*/}")"
	if [ $found ]; then
		type=set
	else
		type=book
	fi
	# saves to folder "$out_format" in dir that this script was called from
	"${script_parent}"/convert.sh $out_format \
		"$f"/index.htm $out_format $type $calibre_options
done
