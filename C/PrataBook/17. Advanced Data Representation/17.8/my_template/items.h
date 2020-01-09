#include "items.c"
void ShowArray(int *arr, int n);
void ShowIntItem(intitem *my_item);
void ShowWordItem(worditem *my_item);
char CompareIntItems(intitem *item1, intitem *item2);
char CompareCharArrays(char *arr1, char *arr2);
char CompareWordItems(worditem *item1, worditem *item2);
intitem *CreateIntItem(int n);
worditem *CreateWordItem(char *word);
void ChangeWordRepeatsCount(worditem *item);
char ComparePetItems(petitem *new_item, petitem *prev_item);
void ShowPetItem(petitem *my_item);
