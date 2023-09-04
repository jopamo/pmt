/*
 * You will be working with a partner. Other than the partner and the instructor, don’t ask or receive help from
anyone. If you look for information on the Internet, then you must document the website, and the information
you got from that site. You may not pay someone else to do this homework, or any part of it. And you are not
allowed to have an AI application write any or all of this assignment. (Whew... that’s a lot of do nots!)
At the end of this specification is a “rubric.” The rubric should help you to understand what we think is
important in HW1. It should also help you devise your own tests as you and your partner develop HW1.
If you have any questions, please email Keith at millerkei@umsl.edu.
The HW1 Programming Problem to Solve:
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
You Get to Choose a Programming Language, but NOT the IDE for HW1.
Onlinegdb.com is an integrated development environment (IDE) that is friendly to many of the languages that
seem popular with UMSL CS 4500 students. It is also free to use. When you are working on your assignment,
you will be required to use onlinegdb.com to prepare and test your programs. You can pick any language
supported by onlinegdb.com, and you must tell us in the FIRST LINE of your opening comment which
onlinegdb programming language we should use to run our tests on your program.
I suggest that you sign up for a free account on onlinegdb.com so that you can save your work on their system,
but I don’t require that.
The file that you submit should be a single text file submitted to the appropriate Canvas assignment. My grader
and I will open your text file, copy its contents, and then paste it into an onlinegdb.com window for the
programming language you name in your program code. I suggest that YOU test your text file by doing exactly
this, and making sure it works. If it does NOT work when we go to grade your program, you will immediately
lose 10% of your grade, and you will have to resubmit.
There are other ways in which you might be able to submit your programs, but for many reasons, I REQUIRE
you to hand in your program as a single text file. If you can't manage to do that with one particular language,
pick a different language that you CAN do with a single text file using onlinegdb.com.
Some students like to argue with me about this rule. I am aware that some programming languages, and some
computer science textbooks, favor the use of multiple files when programming in a particular programming
language. I do not dispute the advantages of this technique, but I don't want you using this technique in HW1.
Software engineering is centered around the needs of the customer. In the case of CS 4500 HW1, I am both the
customer and the boss. I want a single text file submitted from you for these projects. I hope that is crystal clear.
Strangely, some people don't test that their submission works as a single file using onlinegdb.com. They
develop their program using a different compiler, copy the resulting text into a text file, and assume that is
"should work" in onlinegdb. That is a bad idea, as it is likely to make trouble for me and for our grader, and that
will lose you points. Good software engineering is, in part, avoiding bad ideas.
Java is pretty popular among UMSL students. If you use Java, make sure your text file works using
onlinegbd.com's Java interface. Some students have had trouble with this in the past. You are forewarned.
To be clear: you are going to submit a single text file (.txt). If you submit anything else, you will lose points and
will have to resubmit. My grader will open that single file, copy the text, and paste it into onlinegdb.com, using
the language you specify in the first line of the opening comment of your program. If it compiles and runs, the
grader will grade it. If it is not a text file, or it does not compile, or it does not run, then the grader stops, and
you will have to resubmit your program directly to me via email, and there will be a penalty.
We have over 50 students in this class, and grading even simple programs quickly is going to be a challenge.
Using onlinegdb.com and the text file rule above is designed to streamline our grading process. Thanks for your
help with that.
No matter what programming language you eventually use, start the source code for your program with an
extensive opening comment. The first line of that opening comment must describe which programming
language you are using. The rest of the opening comment must include the names of all the programmers
working on the program, the date, the name of our class, an explanation of what the program is designed to do,
a description of the central data structure or structures in your program, and an explanation of any external files
used. If you use any outside resources to develop your program, for example looking up programming language
details on the Web, then your opening comment should explicitly list those sources, and give at least a little
information what you found at each resource. If your program doesn't include any of these, then indicate that by
listing the category, and indicating "None," or something like that. That is, don’t skip any of those things, and
label each. (Your description about what your program is designed to do could be used as the opening
explanation shown to your interactive user at the start of the program’s execution.)
I hope you are getting the impression that documentation is important to me. I am convinced that the best
software engineering professionals document their work in excruciating detail. That’s exactly what I want you
to do for any assignments in CS 4500.
In addition to the extensive opening comment, internal comments should explain important data structures
where they are declared and/or used, delineate large sections of code (“paragraphing comments”), and clarify
anything clever or hard to understand in your code. We grade documentation critically, so I recommend that
you spend some time on your opening and internal comments.
We will test your program by recompiling it, by running it with different inputs and by examining what your
program does.
Please remember, you may NOT get someone else to write this for you, or to help you write it. Any help you
get from a human should come from your instructor, Keith Miller, or from your HW1 small group partner. It is
not OK to seek code for this problem on the web. If you cheat in CS 4500 and you are caught, the penalties are
severe. CS 4500 is, in part, a course about professional ethics; playing fair matters,
If you have any questions, please email your instructor at millerkei@umsl.edu. Best of luck on your first
programming project in CS 4500.
Keith Miller
HW1 Rubric
 Was it handed in on time?
 Was it a single text file?
 Did the first line of the opening comment tell which programming language was to be used?
 Did it compile and run immediately using onlinegdb.com ? If not, STOP GRADING!
 Does the opening comment identify all the programmers, the date, and the class, an explanation of
what the program does, a description of the central data structure(s), any external files used, and any
external sources used in preparing the program?
 Does the code include appropriate internal comments ?
 When the program begins, does it print to the screen an explanation that is no more than 1 screen, but
tells concisely what the program is to do?
 Does the program next request the maximum coordinate of the square grid? Are there appropriate
error messages and reprompting if the user enters something other than the required value?
 Does the program next request the maximum number of turns possible before the people give up?
Are there appropriate error messages and reprompting if the user enters something other than the
required value?
 When the program runs, since randomness is involved, we can’t be sure of all the values returned.
However, like all probabilistic processes, these programs should have discernable trends. Does the
program work for the extremes of possible input parameters? Does the program trend towards
reasonable values when it is run multiple times on the same parameters?
 Does the program check for meeting after EACH move?
 Does the program halt after the proper number of moves if the people never meet?.
 Is the format of the output done consistent with the specification?
 Is the wording used to communicate with the interactive user precise, concise, and polite?
*/

#include <iostream>

int main() {
    std::cout << "Hello World!";
    return 0;
}

