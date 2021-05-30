#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k].name, name) == 0)
        {
            preferences[voter][rank] = k;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //somethign with preference and !candidates[x].eliminated
    //loop thorugh voters and their preferences
    for (int i = 0; i < voter_count; i++)
    {
        //for voter i, check preferences. First not eliminated preference should be counted
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                //after a valid vote is found, this loop needs to stop because the next voter has to be checked
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //if a candidate has more than half of the votes they have won!
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {

            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //i make a new array, which i then sort to find the minimum
    candidate min[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        min[i] = candidates[i];
    }
    //bubblesort the new array
    candidate temp;
    for (int i = candidate_count - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            //i have to check for the number at votes, but resort the whole candidates structure!
            if (min[j].votes > min[j + 1].votes)
            {
                temp = min[j];
                min[j] = min[j + 1];
                min[j + 1] = temp;
            }
        }
    }
    //i take the first amount of votes for any not eliminated candidate
    int m = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!min[i].eliminated)
        {
            //obviously the loop needs to stop, once m is found!
            m = min[i].votes;
            break;
        }
    }
    //it is then returned to main
    return m;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //this looks for the amount of times min is in the list of uneliminated candidates. If it is found more than once, there has to be a tie!
    int tie = 0;
    int e = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        //each not eliminated candidate is checked for the minimum
        if (!candidates[i].eliminated)
        {
            //if they have votes = min, tie counts up
            if (candidates[i].votes == min)
            {
                tie++;
            }
        }
        //if a candidate is eliminated e goes up
        else
        {
            e++;
        }
    }
    //c = remaining candidates
    int c = candidate_count - e;
    //if all leftover candidates have the same (minimum) votes, it is a tie.
    if (tie == c)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}