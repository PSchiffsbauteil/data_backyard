#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election (right now [sorted] list of candidates)
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //this should: compare voter input and names of all candidates. If true/name exists give a vote to found candidate, else return false.
    //this kinda works.. if i do only the if condition, it accepts all candidates, but bugs out, when a wron name is put in
    //if i do any else condition, if accepts only the first candidates name, and returns everything else as invalid vote.
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j].name, name) == 0)
        {
            candidates[j].votes++;
            return true;
        }
    }
    return false;
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate temp[candidate_count];
    //bubblesort algorythm
    for (int i = candidate_count - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            //i have to check for the number at votes, but resort the whole candidates structure!
            if (candidates[j].votes > candidates[j + 1].votes)
            {
                temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }
    //i loop over the votes, check for ties and count those to get the number of winners. Then i print the last people in the sorted list.
    candidate winners[candidate_count];
    int w = 0;
    winners[0] = candidates[candidate_count - 1];

    for (int i = candidate_count - 1; i >= 0; i--)
    {
        if (candidates[i].votes == candidates[i - 1].votes)
        {
            winners[w + 1] = candidates[i - 1];
            w++;
        }
    }


    for (int i = 0; i <= w; i++)
    {
        printf("%s\n", winners[i].name);
    }
    return;
}