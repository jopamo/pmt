/*

Imagine the following scenario: two people are in a square area. This might be a large shopping center, or a
street grid; but we’ll assume it is a large forest surrounded by a formidable wall. The rectangle is overlayed with
an invisible grid, with coordinate (0,0) in the lower left-hand corner, and the coordinate (Dimension,
Dimension) in the upper right corner. (More information about Dimension is below.)
We are going to simulate two people randomly wandering around this grid. PersonA will start at (0,0), and
PersonB will start at (Dimension, Dimension). PersonA will move first, then PersonB, and they will keep
alternating moves, one at a time, until they end up at the same coordinate, or the maxMoves number of moves is
exceeded.

Each time a person is to make a move, your program will randomly choose from four directions: north, east,
south, or west. If the person is on the edge of the grid, and moving in the selected direction would take the
person off the grid (that is, through the surrounding wall), then for this “move” the person will stay at the same
coordinate, and it is the next person’s turn to move.
When your program begins, it should print to the screen an explanation of what the program will do. This
explanation should fit on one screen (so it can’t be too long), but it should communicate the idea of the
program.

Next, your program prompts the interactive user for a positive integer that will determine the size of the square
grid. In this specification, that value is known as Dimension. The resulting grid will have vertical and horizontal
indices that range from 0 to Dimension, inclusive.

When you prompt for Dimension, ask the user to enter a positive integer < 100. If the user types in anything
besides digits, give an appropriate error message and reprompt. If the user types in digits, but not an integer in
the proper range, give an appropriate error message and reprompt. Don’t stop reprompting until an integer in the
proper range is entered. Remember that every prompt should be explicit and precise about what is being
requested, and what (if anything) went wrong.

When your program has successfully established Dimension, prompt for another positive integer. This number
will determine how many total moves will be allowed before the two people “give up.” This positive integer
should be <= 1000000. This specification will call that number maxMoves. As before, if the user types in
anything besides digits, give an appropriate error message and reprompt. If the user types in digits, but not an
integer in the proper range, give an appropriate error message and reprompt. Don’t stop reprompting until an
integer in the proper range is entered. Remember that every prompt should be explicit and precise about what is
being requested.

Your grade depends partly on how good your error messages are for inappropriate responses from the user. The
more specific your error messages, the better.
Smart programmers will have subprograms for fetching positive integers from the interactive user. Smart
programming is rewarded, and awkward or inefficient programming is penalized. Just in case I am being too
subtle here, write a subprogram (it may be called a function, it may be called a procedure in the language you
choose) that takes input parameters, and returns a positive integer inside the boundaries, a number that the user
has entered. Such a subprogram will turn out to be handy in future assignments.
Please forgive me if I seem to be exceedingly pedantic on this point; I usually assume that students are smart
enough to notice when I am requiring something in a specification. However, in prior years when I have
penalized students who don’t follow the instructions, a few students (just a few) make the following argument:
“You didn’t explicitly say we HAD to do....” So, for your HW1 I am trying to be quite detailed about what I
require. In subsequent assignments, I will assume that you know enough about well-structured programming
that you will be expected to do the right thing, and that you understand what I am after when I make a hint like
“smart programmers will...” If you think I am a bit touchy on this subject, you are correct.
Once you have the two numbers Dimension and maxMoves, your program should proceed as follows:
Starting with PersonA, the two people will alternate taking a random move. (Remember, some “moves” may be
staying in the same place, if the person starts on an edge and the randomly selected move would require
breaking through the wall.) Each time either person makes a move, the program checks to see if the two people
are at the same coordinate. If so, the program halts with a message that says at which coordinates the two people
met, and at what turn that meeting took place. If not, the moves continue.
Please note that your program should check to see if the people are at the same coordinate after EACH move. It
is a mistake to wait until after both people have made a move to check. You also need to make sure that the
program halts either after the people meet, or until maxMoves moves have occurred. Stopping after (maxMoves
-1) moves without a meet, or stopping after (maxMoves + 1) moves is not acceptable. Note that the user can
specify either an odd or even maxMoves.
Finally, it is possible (though pretty unlikely) that the two people meet for the first time at exactly the last
possible move. Notice that this possible outcome is different from doing maxMoves moves without the people
meeting. Make sure your program recognizes the difference between these two outcomes.
The moves continue until one of two things happens: the two people meet (please see the previous paragraph),
or after maxMoves moves, the two people never were at the same coordinate. No matter which occurs, the
program should print to the screen what happened, saying either how many moves were made before the people
met or that they gave up after a certain number of moves. The program then halts with a “good bye” message.
If you know nothing about pseudo-random number generators, Wikipedia has a pretty good introduction:
https://en.wikipedia.org/wiki/Random_number_generation. They also have a list of well cited papers about
pseudo random number generators: https://en.wikipedia.org/wiki/List_of_random_number_generators. If you
study that list, you’ll find a reference to the “Park Miller generator;” that Miller is me.

*/

#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int roll(int min, int max) {
	int roll = rand() % max + min;

	return roll;
}

int main() {
	srand (time(NULL));

	long randnum = roll(1, 4);

	std::cout << "Here's a random number ";
	std::cout << randnum << endl;

	return 0;
}

