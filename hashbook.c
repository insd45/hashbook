//Ian Smith insd45 12442396
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*struct hash *hashTable = NULL;
int elecount = 26;  //size of hash table. Making it 26 because there are 26 letters in the alphabet. Easy, constant, and we can assume that nobody has the same first name */
//  ^^^^^^^ I'm actually not convinced that we even need this chunk of code

struct person {
    char name[100];  //literally the only data that makes people different
    struct person *next;    //Linked List: (persons whose names start with the same letter?)
    struct friend *friends;     //Head of the list of all this person's friends
};

struct friend {
    char name[100];
    struct friend* nextFriend;
};

struct hash {
    struct person *head;     //Hash objects hold pointers to people lists
    int count;     //not sure. Holds the size of the linked list within each hash?
};

void createPerson(struct hash *hashTable, char *name1); //Mostly just creates the index for the name to go. Calls insertToHash 
void insertToHash(struct hash *hashTable, char* name1, int index);  //Where the insertion actually happens
void friendify(struct hash *hashTable, char *name1, char *name2);  //Makes these 2 names friends
int checkIfExists(struct hash *hashTable, char *name);  //Check if this name is in the hash
void displayFriends(struct hash *hashTable, char *name);  //Show all this loser's friends
void unfriendify(struct hash *hashTable, char *name1, char *name2);   //Remove these 2 from each other's friend list
int areTheyFriends(struct hash *hashTable, char *name1, char *name2);    //Returns 1 if they're friends, returns 0 otherwise
void freeMemory(struct hash *hashTable);    //Free up the hashTable
void freePersons(struct person *person1);   //Free up all persons (called in freeMemory)
void freeFriends(struct friend *friend1);   //Free up all friends (called in freePersons)

int main() {
    printf("Type Commands:\nP <name> to create a person\nF <name1> <name2> to record these 2 as friends\nU <name1> <name2> to record these 2 are no longer friends\n");
    printf("L <name> to print all friends of this specified person\nQ <name1> <name2> returns a yes or no depending on whether they are friends\nX to quit\n");
    printf("Lowercase P, F, U, L, Q, X commands are NOT recognized\n");
    
    struct hash *hashTable = malloc(sizeof(struct hash) * 26);      //26 slots because 26 letters in the alphabet
    
    //Scan in the first character, see how many more strings need to be read in
    char first[100];
    char name1[100];
    char name2[100];
    int errorCheck = 0;
    int areThey = 0;
    
    while(errorCheck == 0)
    {
        scanf("%s", first);
        if(strcmp(first, "P") == 0)
        {
            //Scan in one more name, create a person with that name
            scanf("%s", name1);
            createPerson(hashTable, name1);
        }
        else if(strcmp(first, "F") == 0)
        {
            //Scan in two more names and friendify them
            scanf("%s %s", name1, name2);
            friendify(hashTable, name1, name2);
            
        }
        else if(strcmp(first, "U") == 0)
        {
            //scan in two more names and unfriendify them
            scanf("%s %s", name1, name2);
            unfriendify(hashTable, name1, name2);
        }
        else if(strcmp(first, "L") == 0)
        {
            //scan in one more name, and print all their friends
            scanf("%s", name1);
            displayFriends(hashTable, name1);
        }
        else if(strcmp(first, "Q") == 0)
        {
            //scan in 2 more names and check if theyre friends
            scanf("%s %s", name1, name2);
            areThey = areTheyFriends(hashTable, name1, name2);
            if(areThey == 1)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
        else if(strcmp(first, "X") == 0)
        {
            //Quit
            errorCheck = 1;
            freeMemory(hashTable);
        }
        else
        {
            //User didnt enter a P, F, U, L, Q, or X, so we gotta hit em with the "You're stupid"
            printf("Unrecognized command\n");
        }
    }
    
    return 0;
}

void createPerson(struct hash *hashTable, char* name1)
{
    //char *firstLetter = name1[0];    // Find the first letter of the name. if A set this person to hash, set it to uppercase
    char firstLetter = name1[0];
    //strcpy(firstLetter, name1[0]);
    //firstLetter = strupr(firstLetter);
    //strcpy(firstLetter, strupr(firstLetter));
    
    int index = 0;
    
    //Heck of an if statement---> find the correct index value, and then insertToHash at the specified index
    if(firstLetter == 'A' || firstLetter == 'a')
    {
        index = 0;
    }
    else if(firstLetter == 'B' || firstLetter == 'b')
    {
        index = 1;
    }
    else if(firstLetter == 'C' || firstLetter == 'c')
    {
        index = 2;
    }
    else if(firstLetter == 'D' || firstLetter == 'd')
    {
        index = 3;
    }
    else if(firstLetter == 'E' || firstLetter == 'e')
    {
        index = 4;
    }
    else if(firstLetter == 'F' || firstLetter == 'f')
    {
        index = 5;
    }
    else if(firstLetter == 'G' || firstLetter == 'g')
    {
        index = 6;
    }
    else if(firstLetter == 'H' || firstLetter == 'h')
    {
        index = 7;
    }
    else if(firstLetter == 'I' || firstLetter == 'i')
    {
        index = 8;
    }
    else if(firstLetter == 'J' || firstLetter == 'j')
    {
        index = 9;
    }
    else if(firstLetter == 'K' || firstLetter == 'k')
    {
        index = 10;
    }
    else if(firstLetter == 'L' || firstLetter == 'l')
    {
        index = 11;
    }
    else if(firstLetter == 'M' || firstLetter == 'm')
    {
        index = 12;
    }
    else if(firstLetter == 'N' || firstLetter == 'n')
    {
        index = 13;
    }
    else if(firstLetter == 'O' || firstLetter == 'o')
    {
        index = 14;
    }
    else if(firstLetter == 'P' || firstLetter == 'p')
    {
        index = 15;
    }
    else if(firstLetter == 'Q' || firstLetter == 'q')
    {
        index = 16;
    }
    else if(firstLetter == 'R' || firstLetter == 'r')
    {
        index = 17;
    }
    else if(firstLetter == 'S' || firstLetter == 's')
    {
        index = 18;
    }
    else if(firstLetter == 'T' || firstLetter == 't')
    {
        index = 19;
    }
    else if(firstLetter == 'U' || firstLetter == 'u')
    {
        index = 20;
    }
    else if(firstLetter == 'V' || firstLetter == 'v')
    {
        index = 21;
    }
    else if(firstLetter == 'W' || firstLetter == 'w')
    {
        index = 22;
    }
    else if(firstLetter == 'X' || firstLetter == 'x')
    {
        index = 23;
    }
    else if(firstLetter == 'Y' || firstLetter == 'y')
    {
        index = 24;
    }
    else
    {
        index = 25;
    }
    
    insertToHash(hashTable, name1, index);
}

void insertToHash(struct hash *hashTable, char* name1, int index)
{
    //We have the correct index to be sent to the hash, the name of the person, and the array of Hashes
    //Create the person object
    struct person *newPerson = malloc(sizeof(struct person));
    strcpy(newPerson->name, name1);
    newPerson->friends = NULL;
    //newPerson->next may not be NULL because it may have to be added to an index where people's names start with the same letter
    
    //First, check if person will be the first in the hash that index 'index' is pointing to
    if(!hashTable[index].head)        //  maybe . instead of ->
    {
        hashTable[index].head = newPerson;
        hashTable[index].count = 1;
        return;
    }
    
    //Adds person to head of list
    newPerson->next = (hashTable[index].head);
    
    //Current person becomes head of linked list at given hash index
    hashTable[index].head = newPerson;
    hashTable[index].count++;
    
    return;
}

void friendify(struct hash *hashTable, char *name1, char *name2)
{
    //Find them in the array. checkIfExists returns their index in the array, 500 if they don't exist
    int name1exists = checkIfExists(hashTable, name1);
    int name2exists = checkIfExists(hashTable, name2);
    
    //Set them to new pointers to traverse in the else statement
    
    if(name1exists == 500 || name2exists == 500)
    {
        printf("One or more of these people currently do not exist\n");
        return;
    }
    else
    {
        //So they both exist, and their index values are stored in name1exists, name2exists
        
        struct person *pf1Traverse = hashTable[name1exists].head;    //Used to traverse through all names at its index
        struct person *pf2Traverse = hashTable[name2exists].head;
        
        int i = 0;
        while(/*pf1Traverse->next != NULL && */i == 0)
        {
            //Find the person object within the linked list that we're adding name2 to their friend list
            if(strcmp(name1, pf1Traverse->name) == 0)
            {
                //We've found the person object with the name of name1. It is currently pf1Traverse
                i = 1;
                //By setting i = 1, we can quit the loop and pf1Traverse is still the person object with name1 as its name
            }
            else if(pf1Traverse->next != NULL)
            {
                //If the next person in the linked list is not NULL, continue
                pf1Traverse = pf1Traverse->next;
            }
            else
            {
                //If we've made it here, which should never happen, then pf1Traverse->next == NULL and pf1Traverse->name != name1
                //Which means that a person with name1 is not in this linked list (Shouldn't happen)
                i = 1;
            }
        }
        //Now, our person object with the name of name1 is stored currently at pf1Traverse
        
        //Repeat for name2
        i = 0;
        while(i == 0)
        {
            //Find the person object within the linked list that we're adding name1 to their friend list
            if(strcmp(name2, pf2Traverse->name) == 0)
            {
                //We've found the person object with the name of name2. It is currently pf2Traverse
                i = 1;
                //By setting i = 1, we can quit the loop and pf2Traverse is still the person object with name2 as its name
            }
            else if(pf2Traverse->next != NULL)
            {
                //If the next person in the linked list is not NULL, continue
                pf2Traverse = pf2Traverse->next;
            }
            else
            {
                //If we've made it here, which should never happen, then pf2Traverse->next == NULL and pf1Traverse->name != name2
                //Which means that a person with name2 is not in this linked list (Shouldn't happen)
                i = 1;
            }
        }
        //Now, our person object with the name of name2 is stored currently at pf2Traverse
        
        //Add them to each others' friends list
        //If their friends list is empty, just make the addition the head of the list
        //If their friends list has 1 or more elements, insert it at the beginning, and make it's next value
        
        //First, add the person object whose name is name2 to name1's friend list
        
        //Make a friend object out of name2
        struct friend *friend2 = malloc(sizeof(struct friend));
        
        if(pf1Traverse->friends != NULL)
        {
            //Friends list is NOT empty
            strcpy(friend2->name, pf2Traverse->name);
            //friend2 is now named name2
            //Make friend2 the head of person1's friend list, and make sure friend2->nextFriend holds the pre-existing friends list
            friend2->nextFriend = pf1Traverse->friends;
            pf1Traverse->friends = friend2;
        }
        else
        {
            //Friends list IS empty
            strcpy(friend2->name, pf2Traverse->name);
            //friend2 is now named name2
            //Make friend2 the head of person1's friend list, and make friend2->nextFriend = NULL
            friend2->nextFriend = NULL;
            pf1Traverse->friends = friend2;
        }
        
        struct friend *friend1 = malloc(sizeof(struct friend));
        
        if(pf2Traverse->friends != NULL)
        {
            //friends list is NOT empty
            strcpy(friend1->name, pf1Traverse->name);
            //friend 1 is now named name1
            //Make friend1 the head of person2's friend list, and make sure friend1->nextFriend holds the pre-existing friends list
            friend1->nextFriend = pf2Traverse->friends;
            pf2Traverse->friends = friend1;
        }
        else
        {
            //Friends list IS empty
            strcpy(friend1->name, pf1Traverse->name);
            //friend 1 is now named name1
            //Make friend1 the head of person2's friend list, and make friend1->nextFriend = NULL;
            friend1->nextFriend = NULL;
            pf2Traverse->friends = friend1;
        }
    }
}

void unfriendify(struct hash *hashTable, char *name1, char *name2)
{
    //First make sure they exist, store their indeces if they do
    int name1exists = checkIfExists(hashTable, name1);
    int name2exists = checkIfExists(hashTable, name2);
    
    if(name1exists == 500 || name2exists == 500)
    {
        printf("One or more of these people currently do not exist\n");
        return;
    }
    else
    {
        //So they both exist and their indeces are stored in name1exists and name2exists
        
        struct person *pf1Traverse = hashTable[name1exists].head;   //Will traverse all names in this index
        struct person *pf2Traverse = hashTable[name2exists].head;
        
        int i = 0;
        while(i == 0)
        {
            //Find name1 within this linked list for the purpose of removing name2 from their friends list
            if(strcmp(name1, pf1Traverse->name) == 0)
            {
                //We've found the person object with the name name1 currently stored at pf1Traverse
                i = 1;
                //Quit the while loop
            }
            else if(pf1Traverse->next != NULL)
            {
                //This isn't the correct name, but it's not the last in the list, so continue to the next chained name
                pf1Traverse = pf1Traverse->next;
            }
            else
            {
                //This shouldn't happen. It means the name isn't at the index, but as a safeguard, exit the loop
                i = 1;
            }
        }
        //Now our person object with the name name1 is stored in pf1Traverse
        
        //Repeat to find the location of name2
        i = 0;
        while(i == 0)
        {
            //Find name2 within this linked list for the purpose of removing name1 from their friends list
            if(strcmp(name2, pf2Traverse->name) == 0)
            {
                //We've found the person object with the name name2 currently stored at pf2Traverse
                i = 1;
                //Quit the while loop
            }
            else if(pf2Traverse->next != NULL)
            {
                //This isn't the correct name, but it's not the last in the list, so continue to the next chained name
                pf2Traverse = pf2Traverse->next;
            }
            else
            {
                //This should not happen. Exit loop as a safeguard
                i = 1;
            }
        }
        //Now our person object with the name name2 is stored in pf2Traverse
        
        //Remove them from each others' friend list
        //If one of their friends lists is empty, your job's already done
        //If their friends list is not empty, search through their friends list, find the other name, delete the node without breaking the list.
        
        //First, remove name2 from name1's friend list. Make a friend object out of name2 to be the head of the list(for traversal purposes)
        struct friend *friend2 = pf1Traverse->friends;
        struct friend *friend2head = pf1Traverse->friends;
        struct friend *prevFriend2 = pf1Traverse->friends;
        int dummy = 0;
        if(friend2 == NULL)
        {
            //pf1Traverse's friends list is empty
            //Basically do nothing, the user was stupid to send an unfriend command for people who weren't friends in the first place
            dummy++;
        }
        else if(friend2->nextFriend == NULL)
        {
            //pf1Traverse has got 1 friend, and we are going to delete this friend   ¯\_(ツ)_/¯
            pf1Traverse->friends = NULL;
            friend2 = NULL;
        }
        else
        {
            //pf1Traverse has multiple friends. Search the list. Find the friend
            //Traverse with friend2, remove the friend with name name2
            //The head of the linked list only changes if the first node in the list is the friend we need to remove
            
            //See if the first node is the one we need to remove from the friends list
            if(strcmp(friend2->name, name2) == 0)
            {
                pf1Traverse->friends = friend2->nextFriend;
                friend2 = NULL;
            }
            else
            {
                //So the first node in the list wasn't the friend that needs to be deleted
                while(strcmp(friend2->name, name2) != 0)
                {
                    prevFriend2 = friend2;
                    friend2 = friend2->nextFriend;
                }
                
                //Now, friend2->name == name2
                if(friend2->nextFriend != NULL)
                {
                    prevFriend2->nextFriend = friend2->nextFriend;
                    friend2 = NULL;
                }
                else
                {
                    prevFriend2->nextFriend = NULL;
                    friend2 = NULL;
                }
                pf1Traverse->friends = friend2head;
            }
        }
        
        //Repeat by removing name1 from name2's friend list
        struct friend *friend1 = pf2Traverse->friends;
        struct friend *friend1head = pf2Traverse->friends;
        struct friend *prevFriend1 = pf2Traverse->friends;
        dummy = 0;
        if(friend1 == NULL)
        {
            //pf1Traverse's friends list is empty
            //Basically do nothing, the user was stupid to send an unfriend command for people who weren't friends in the first place
            dummy++;
        }
        else if(friend1->nextFriend == NULL)
        {
            //pf1Traverse has got 1 friend, and we are going to delete this friend   ¯\_(ツ)_/¯
            pf2Traverse->friends = NULL;
            friend1 = NULL;
        }
        else
        {
            //pf1Traverse has multiple friends. Search the list. Find the friend
            //Traverse with friend2, remove the friend with name name2
            //The head of the linked list only changes if the first node in the list is the friend we need to remove
            
            //See if the first node is the one we need to remove from the friends list
            if(strcmp(friend1->name, name1) == 0)
            {
                pf2Traverse->friends = friend1->nextFriend;
                friend1 = NULL;
            }
            else
            {   
                while(strcmp(friend1->name, name1) != 0)
                {
                    prevFriend1 = friend1;
                    friend1 = friend1->nextFriend;
                }
                
                //Now, friend2->name == name2
                if(friend1->nextFriend != NULL)
                {
                    prevFriend1->nextFriend = friend1->nextFriend;
                    friend1 = NULL;
                }
                else
                {
                    prevFriend1->nextFriend = NULL;
                    friend1 = NULL;
                }
                pf2Traverse->friends = friend1head;
            }
        }
    }
}

int checkIfExists(struct hash *hashTable, char *name)
{
    //return 500 if no exist, return index if exist
    
    //First again, find the correct index
    char firstLetter = name[0];
    int index = 0;
    
    //Heck of an if statement---> find the correct index value, and then insertToHash at the specified index
    if(firstLetter == 'A' || firstLetter == 'a')
    {
        index = 0;
    }
    else if(firstLetter == 'B' || firstLetter == 'b')
    {
        index = 1;
    }
    else if(firstLetter == 'C' || firstLetter == 'c')
    {
        index = 2;
    }
    else if(firstLetter == 'D' || firstLetter == 'd')
    {
        index = 3;
    }
    else if(firstLetter == 'E' || firstLetter == 'e')
    {
        index = 4;
    }
    else if(firstLetter == 'F' || firstLetter == 'f')
    {
        index = 5;
    }
    else if(firstLetter == 'G' || firstLetter == 'g')
    {
        index = 6;
    }
    else if(firstLetter == 'H' || firstLetter == 'h')
    {
        index = 7;
    }
    else if(firstLetter == 'I' || firstLetter == 'i')
    {
        index = 8;
    }
    else if(firstLetter == 'J' || firstLetter == 'j')
    {
        index = 9;
    }
    else if(firstLetter == 'K' || firstLetter == 'k')
    {
        index = 10;
    }
    else if(firstLetter == 'L' || firstLetter == 'l')
    {
        index = 11;
    }
    else if(firstLetter == 'M' || firstLetter == 'm')
    {
        index = 12;
    }
    else if(firstLetter == 'N' || firstLetter == 'n')
    {
        index = 13;
    }
    else if(firstLetter == 'O' || firstLetter == 'o')
    {
        index = 14;
    }
    else if(firstLetter == 'P' || firstLetter == 'p')
    {
        index = 15;
    }
    else if(firstLetter == 'Q' || firstLetter == 'q')
    {
        index = 16;
    }
    else if(firstLetter == 'R' || firstLetter == 'r')
    {
        index = 17;
    }
    else if(firstLetter == 'S' || firstLetter == 's')
    {
        index = 18;
    }
    else if(firstLetter == 'T' || firstLetter == 't')
    {
        index = 19;
    }
    else if(firstLetter == 'U' || firstLetter == 'u')
    {
        index = 20;
    }
    else if(firstLetter == 'V' || firstLetter == 'v')
    {
        index = 21;
    }
    else if(firstLetter == 'W' || firstLetter == 'w')
    {
        index = 22;
    }
    else if(firstLetter == 'X' || firstLetter == 'x')
    {
        index = 23;
    }
    else if(firstLetter == 'Y' || firstLetter == 'y')
    {
        index = 24;
    }
    else
    {
        index = 25;
    }
    
    if(hashTable[index].head != NULL)
    {
        struct person *personList = hashTable[index].head;
        int i = 0;
        for(i = 0; i < hashTable[index].count; i++)
        {
            if(strcmp(name, personList->name) == 0)
            {
                return index;
            }
            else
            {
                personList = personList->next;
            }
        }
        return 500;
    }
    else
    {
        return 500;
    }
}

void displayFriends(struct hash *hashTable, char *name)
{
    //First, find the index
    int index = checkIfExists(hashTable, name);
    
    if(index == 500)
    {
        printf("Person does not exist\n");
        return;
    }
    else
    {
        //We've got the index in index now
        struct person *traverse = hashTable[index].head;
        
        int i = 0;
        while(i == 0)
        {
            //Traverse through every name at the desired index
            if(strcmp(traverse->name, name) == 0)
            {
                //We've found the person, currently at traverse
                i = 1;
                //Quit the loop because we want to display all of traverse's friends
            }
            else if(traverse->next != NULL)
            {
                //It's not this one, could be the next
                traverse = traverse->next;
            }
            else
            {
                //Shouldn't happen
                i = 1;
            }
        }
        
        //Display all of traverse's friends
        struct friend *tsFriends = traverse->friends;  //<----- This is now the head of the linked list containing all of traverse's friends
        
        if(tsFriends == NULL)
        {
            printf("No friends\n");
            return;
        }
        else
        {
            //Print the first friend
            printf("%s ", tsFriends->name); 
            //While tsFriends->nextFriend != NULL, print tsFriends->nextFriend's name (SegFault prevention)
            while(tsFriends->nextFriend != NULL)
            {
                printf("%s ", (tsFriends->nextFriend)->name);
                //Increment
                tsFriends = tsFriends->nextFriend;
            }
            printf("\n");
            return;
        }
    }
}

int areTheyFriends(struct hash *hashTable, char *name1, char *name2)
{
    //Returns 1 if they're friends, 0 otherwise
    //Only need to find name1 in the array. Name1 will be in name2's friend list
    int name1exists = checkIfExists(hashTable, name1);
    int name2exists = checkIfExists(hashTable, name2);
    
    if(name1exists == 500 || name2exists == 500)
    {
        return 0;
    }
    else
    {
        //They both exist, we only have to find one of them in the hash though
        struct person *pf1Traverse = hashTable[name1exists].head;
        
        int i = 0;
        while(i == 0)
        {
            if(strcmp(name1, pf1Traverse->name) == 0)
            {
                //We've found the person object with name of name1, currently stored in pf1Traverse
                i = 1;
                //Quit the loop
            }
            else if(pf1Traverse->next != NULL)
            {
                //If next is not NULL, continue
                pf1Traverse = pf1Traverse->next;
            }
            else
            {
                //Shouldn't happen. Quit loop
                i = 1;
            }
        }
        //We've got the correct person object. Now we have to check their friends list.
        
        struct friend *friend2 = malloc(sizeof(struct friend));
        
        if(pf1Traverse->friends == NULL)
        {
            //name1's friend list is empty. They can't be friends
            return 0;
        }
        else
        {
            //name1's friend list is not empty
            friend2 = pf1Traverse->friends;
            while(friend2->nextFriend != NULL)
            {
                if(strcmp(friend2->name, name2) == 0)
                {
                    return 1;
                }
                else
                {
                    friend2 = friend2->nextFriend;
                }
            }
            //One last check
            if(strcmp(friend2->name, name2) == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

void freeMemory(struct hash *hashTable)
{
    int i = 0;
    for(i = 0; i < 26; i++)
    {
        freePersons(hashTable[i].head);
    }
    free(hashTable);
}

void freePersons(struct person *person1)
{
    struct person *tmp;
    
    while(person1 != NULL)
    {
        tmp = person1;
        person1 = person1->next;
        freeFriends(tmp->friends);
        free(tmp);
    }
}

void freeFriends(struct friend *friend1)
{
    struct friend *tmp;
    
    while(friend1 != NULL)
    {
        tmp = friend1;
        friend1 = friend1->nextFriend;
        free(tmp);
    }
}