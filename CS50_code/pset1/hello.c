#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n");
    printf("hello, %s\n", name);
}

//this is a comment. \n stands for new line.
/* this is a multi line comment.
all programs needs to be compiled using the command clang (c language).
'printf' means formatted text just print produces an error*/
//'clang' -o filename names the output.
//the program 'make' cheats compiling and naming together
/* %s is a placeholder for a string.
because there a weird 'functions' here we have to also load cs50.h
while compiling, there has to be a '-lcs50' at the end of the command to link the given functions/variables to the compiler.
'make' cheats this again.*/