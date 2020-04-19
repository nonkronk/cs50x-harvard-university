#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Compare string
    for (int i = 0, j = candidate_count; i < j; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update ranks
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update each possible preferences
    for (int i = candidate_count, j = 0; i > 0; i--)
    {
        for (int k = 1; k < i; k++)
        {
            // Update preferences
            preferences[ranks[j]][ranks[j + k]]++;
        }
        // Store 0 while prefer themselves
        preferences[ranks[i]][ranks[i]] = 0;
        j++;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate over candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Decide winner
            if (preferences[i][j] > preferences[j][i])
            {
                // Store Winner & loser to array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // Update total pairs
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Create sorted array
    int arr[pair_count], temp, temp2;

    // Sort pairs array (bubble)
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                temp = pairs[i].winner;
                temp2 = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp;
                pairs[j].loser = temp2;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate over candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            // Iterate over pairs array
            for (int k = 0; k < pair_count; k++)
            {
                // Lock pairs
                if (pairs[k].winner == i && pairs[k].loser == j)
                {
                    locked[i][j] = true;
                }
                // Skip when it creates cycle
                if (j == pairs[0].winner)
                {
                    locked[i][j] = false;
                }
            }
            printf("%d", locked[i][j]);
        }
        printf("\n");
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate over candidate
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                count++;
            }
            // Print only eligible candid
            if (count == candidate_count)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}