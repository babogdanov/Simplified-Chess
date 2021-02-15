This is the first version of Chess I've done. It was my course project for Introduction to Programming and it's a great example of a lack of coding practices.
The task was to create a simplified chess game with 4 pieces- 1 white king, 1 black king and 2 white rooks. 
The board is a square with variable size and the pieces are generated on random squares.
The user plays with the white pieces and there is a primitive bot playing with the black pieces. 
Its decision making is very simple- if it can capture one of the opponent's rooks it does that and if it can't it picks a legal move at random. 
I started working on it before learning the first thing about OOP or even the existence of classes, 
my knowledge of the STL in C++ was very limited at the time and we weren't allowed to use anything we didn't fully understand yet.
There is barely any structure to it- it's functions calling each other chaotically,
the code is closed for any extension or modification and there is a bunch of hard to trace dependencies everywhere.
Still, I was very proud of it when I completed it as it's robust and bug-free and I wrote it all on my own.
It also motivated me to eventually write a better version when I gained enough knowledge.