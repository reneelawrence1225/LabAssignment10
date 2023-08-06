#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie *letters[26];
    int counter;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    
    for(int r = 0; r < 26; r++)
    {
        newTrie->letters[r] = NULL;
    }

    newTrie->counter = 0;
    return newTrie;

}


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *present = pTrie;

    for(int r = 0; word[r] != '\0'; r++)
    {
        int index = word[r] - 'a';

        if(present->letters[index] == NULL)
        {
            present->letters[index] = createTrie();
        }

        present = present->letters[index];

    }
    
    
    present->counter++;

}



// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *present = pTrie;

    for(int r = 0; word[r] != '\0'; r++)
    {
        int index = word[r] - 'a';
        if(present->letters[index] == NULL)
        {
            return 0;
        }
        present = present->letters[index];
    }

    return present->counter;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL)
    {
        return NULL;
    }

    for(int r = 0; r < 26; r++)
    {
        if(pTrie->letters[r] != NULL)
        {
            pTrie->letters[r] = deallocateTrie(pTrie->letters[r]);
        }
    }

    free(pTrie);
    return NULL;

}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Cannot open file: %s\n", filename);
        return 0;
    }

    int wordNum;
    fscanf(file, "%d", &wordNum);

    for(int i = 0; i < wordNum; i++)
    {
        pInWords[i] = (char *)malloc(256 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return wordNum;

}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
        deallocateTrie(pTrie);
	return 0;
}























