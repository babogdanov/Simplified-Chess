# Simplified Chess

**Motivation/ Task specification**

This was my Introduction to Programming course project assignment. The task was to design a simplified chess game with 4 pieces- 1 white king, 1 black king and 2 white rooks. The board is a square with variable size and the pieces are generated on random squares. The user plays with the white pieces and there is a primitive bot playing with the black pieces. The bot's behaviour was not specified but I created some simple logic- if it can capture one of the opponent's rooks, it does that and if it can't, it picks a legal move at random. The game is to be played by the player until it reaches 1 of its 3 possible conclusions- the player checkmates the enemy king, the player loses both of his rooks resulting in draw by insuficcient material, or the player leaves no squares for the enemy king to move, while the enemy king is not in check (results in draw by stalemate).

**Technologies used**

C++ was the obligatory language for the project (or rather C given my knowledge at the time).

**Features**

The visual representation of the board is in the console. Dashes(-) denote the empty squares, K is the player's king, P is the enemy king, 1 and 2 are the player's rooks. Moving a piece is done one step at a time- first the symbol of the piece is inputted, then the row and the column to which the player wants to move it. Validation of the input is implemented- the game will prompt for input, until it receives a valid input which is also a legal move. The game carries on until 1 of the 3 endings mentioned above is reached. 

**How to use**

You can find all the source code in Chess.cpp and compile it if you want to, or you can test the game through Simplified_Chess.exe.

**Problems with the design and implementation**

I lacked any knowledge about OOP, efficient design or good good coding practices when I started working on the project- the result is unreadable spaghetti code full of bad design choices. It wasn't really pleasant creating it this way, but I am still proud of it as I managed to make it robust and bug-free on my own. It also motivated me to start working on better versions when I gain enough knowledge.


