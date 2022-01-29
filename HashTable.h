// Assignment #5
// Name: Hector Durazo
// ASU Email Address: hmdurazo@asu.edu
// Description: program that creates a hash table (open addressing with double hashing) using 
//              a size that a user enters to store course information. Each course should have 
//              its courseId (such as CSE310), credits (int), capacity (int), days (such as MWF), 
//              and time (such as 10am-11am).
//
// Hash Analysis:   First i begin by generating a key using the courseId which is provided by the user.
//                  I do this by adding up all the ascii values. Then to generate a hash I used that key
//                  key and the index where its trying to insert the course.
//                      - I came up with the hash that i did because the range the keys i was generating was between
//                        350 and 390 so i thought that if i mod by 25 i can roughly get the remainder up to 19
//                      - The number of collisions was a little hight than expected but this was the lowest i could getit
//                      - My hash function works well when the size of the table is larger than the amount of inputs, but
//                        the number of collisions increases dramaticaly when i reach close to n.
//                      - The only thing i had to change was the way i was generating my keys because at first i was multiplying
//                        each character ascii value with eachother but a lot of the keys were coming out to even numbers so i
//                        changed it to add them instead.

#include <iostream> //to use cout
#include <iomanip>  //to format output
#include <string>   //to use strings
#include <math.h>

using namespace std;

//A course struct which contains all the information of a club
struct course
{
    int key, collision, capacity, credits;
    string days, time, courseid;
};

//class Hashtable will contain a hash table of course objects
class HashTable
{
    private://local variables
        int hashSize;
        course *table;

    public://methods 
        HashTable(int size);
        ~HashTable();

        void printHash();
        int hash(int k, int i);
        int generateK(string courseId);
        bool searchElement(string courseId);
        bool changeCourseCapacity(string courseId, int capacity);
        bool insertElement(string courseId, int credits, int capacity, string days, string time);
};

//HashTable constructor
HashTable::HashTable(int size)
{
    hashSize = size;
    //creates an array of course type objects
    table = new course[hashSize];
    //loop that sets every coures to empty
    for (int i = 0; i < size; i++)
    {
        table[i].key = 0;
        table[i].credits = 0;
        table[i].capacity = 0;
        table[i].collision = 0;
        table[i].days = "none";
        table[i].time = "none";
        table[i].courseid = "none";
    }
}
//Destructor
HashTable::~HashTable()
{
    //deletes the table array created earlier
    delete[] table;
}

//helper method that generates a key when given a string
int HashTable::generateK(string id)
{
    int key = 0;
    //for loop that iterates throught users coures id and adds up their ascii values
    for (int i = 0; i < id.length(); i++)
    {
        key += id[i];
    }
    return key;
}

//method that changes the capacity of a course given the course id and the new capacity
bool HashTable::changeCourseCapacity(string courseId, int newCapacity)
{
    //calls the helper method generateK to get a key and set it equal to the var k
    int k = generateK(courseId);
    //for loop that iterates up to the size of the table
    for (int i = 0; i < hashSize; i++)
    {
        //calls the hash method and rerurns hash for every i
        int j = hash(k, i);

        //where the comparison is being made to find a course in the table
        //if the hash keys match that means the course is in the table
        if (table[j].key == k)
        {
            //changeing the capacity of the course
            table[j].capacity = newCapacity;
            cout << table[j].courseid << " updated" << endl;
            return true;
        }
    }
    //returns false if the course is not found in the table
    return false;
}

//hash function that generates a hash given a key and an index
int HashTable::hash(int k, int i)
{
    //first hash mods the key with the size of the table
    int h1 = ((k % hashSize));
    //the second hash mods the key with 25 and adds 1
    int h2 = (1 + (k % 25));  
    //final hash combines the last two hashes to generate this one
    //h2 is multiplied by the index, then added by h1 and moded by the table size
    int h = ((h1 + (i * h2)) % hashSize);
    return h;
}

//seachElement function looks through the table using the hash key to find the matching key
bool HashTable::searchElement(string courseId)
{
    //calls the helper method generateK to get a key and set it equal to the var k
    int k = generateK(courseId);
    //for loop that iterates up to the size of the table
    for (int i = 0; i < hashSize; i++)
    {
        //calls the hash method and rerurns hash for every i
        int j = hash(k, i);

        //where the comparison is being made to find a course in the table
        //if the hash keys match that means the course is in the table
        if (table[j].key == k)
        {
            //prints out all the information of the course if found
            cout << table[j].courseid << " found with credit(s) " << table[j].credits
                 << ", capacity " << table[j].capacity
                 << " in the days: " << table[j].days
                 << " and the time: " << table[j].time << endl;
            return true;
        }
    }
    //if the course is not found it returns false
    return false;
}

//insertElements is function where the users information it taken and generates a j which is where 
//the course will be inserted in the table. returns ture if the course was added to the list
bool HashTable::insertElement(string courseId, int credits, int capacity, string days, string time)
{
    //calls the helper method generateK to get a key and set it equal to the var k
    int k = generateK(courseId);
    //for loop that iterates up to the size of the table
    for (int i = 0; i < hashSize; i++)
    {
        //calls the hash method and rerurns hash for every i
        int j = hash(k, i);

        //if a spot j on the table is empty then it will fill that spot up with that course
        if (table[j].key == 0)
        {
            table[j].key = k;
            table[j].capacity = capacity;
            table[j].courseid = courseId;
            table[j].credits = credits;
            table[j].days = days;
            table[j].time = time;
            return true;
        }
        //if that spot is already taken up then it will add to the collision counter with 
        //the course that is already there.
        else
        {
            table[j].collision += 1;
        }
    }
    //once i has iterated up to the hash size and still hasnt inserted the course then
    //it returns false and gives a message to the user
    cout << "Error: hash table overflow" << endl;
    return false;
}

//function that prings out the tabel
void HashTable::printHash()
{
    //int totalCol = 0;
    cout << "Index" << setw(15) << right
         << "Collision" << setw(15)
         << "CourseId" << setw(15)
         << "Credits" << setw(15)
         << "Capacity" << setw(15)
         << "Days" << setw(15)
         << "Time" << endl;
    for (int i = 0; i < hashSize; i++)
    {
        //totalCol += table[i].collision; // this was to add up the total amout of collisions
        cout << i << setw(15) << table[i].collision
             << setw(18) << table[i].courseid
             << setw(13) << table[i].credits
             << setw(15) << table[i].capacity
             << setw(18) << table[i].days
             << setw(17) << table[i].time << endl;
    }
    //cout << "total collisions = " << totalCol<< endl; // print out the total amout of collisions
}