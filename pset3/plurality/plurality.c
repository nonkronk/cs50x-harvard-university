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

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Compare string
    for (int i = 0, j = candidate_count; i < j; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max = INT_MIN;
    int count = 0;
    int indeks[MAX] = {};

    // Immediately return single candidate
    if (candidate_count == 1)
    {
        printf("%s\n", candidates[0].name);
        return;
    }

    // Calculate highest voted number
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
        }
    }
    // Count equal voted
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes == max)
        {
            indeks[count] = i;
            count++;
        }
    }
    // Print most voted candidate
    if (count == 1)
    {
        printf("%s\n", candidates[indeks[count - 1]].name);
    }
    // Print equal voted candidate
    else
    {
        for (int i = 0; i < (count - 1); i++)
        {
            printf("%s\n", candidates[indeks[i]].name);
        }
        printf("%s\n", candidates[indeks[count - 1]].name);
    }
    return;
}