alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 \
	-fsanitize=undefined,address'
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
alias b='g++ -Wshadow -Wall -o "%e" -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG'