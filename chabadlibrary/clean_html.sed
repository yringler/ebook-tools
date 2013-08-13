# two commands - one for single line <script>s, one for multi

# get rid of redirection script -- now the links are correct
# one line and multiline
\;<script.*</script>;d
/<script.*>/,\;</script>;d

# get rid of opening stuff
/<div class=breadcrumbs>/,\;</div>;d

# saves table of contents
/<table width=/n
# check (maybe) - some <table>s have a </div> on same line
/<table/,/<\/table>/d

# gets rid of a few spans at the end of the file
/<span id=app/,/<\/span>/d

## doesn't seem needed - onKeyDown stuff
#/<body dir=rtl/s/.*/<body dir=rtl>/

## I'm not sure what this next line does
#/style=/s/\(.*\)style=".*"\(.*\)/\1\2/

## doesn't seem needed
# saves footnotes
#/<span class=haor/n  
# I'm not sure what a cup is-seems to be a section of some sort
#\;<span class=cup;n
