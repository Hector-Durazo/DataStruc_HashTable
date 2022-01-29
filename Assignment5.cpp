// Assignment #5
// Name: Hector Durazo
// ASU Email Address: hmdurazo@asu.edu
// Description: This program displays the user how large would they like their
//              hash table to be. Then user can choose ‘A’, ‘B’, ‘C’, ‘D’, or ‘Q’
//              where each letter corresponds to a uniqu function.
//              
//               
//              
#include <iostream>     //to use cout
#include <iomanip>      //to format output
#include <string>       //to use strings
#include <cstring>      //to use strtok function to parse the users info
#include "HashTable.h"  //include the hashTable file

using namespace std;

int main(int argc, char const *argv[])
{
    // local variables, can be accessed anywhere from the main method
    char input = 'Z';
    int hashSize = 0;
    string courseInfo[7], courseId, days, time, userIn;
    int parseSize, credit, capacity;
    bool success = false;

    //ask the user to enter a desired table size
    cout << "Please enter a hash table size." << endl;
    cin >> hashSize;

    // instantiate a hashTable object
    HashTable *hash = new HashTable(hashSize);

    //loop that runs until the user is done useing the program
    do
    {
        //will as for the user input
        cout << "What action would you like to perform?" << endl;
        cin >> input;
        input = toupper(input);
        char str[50];
        //matches one of the case statements
        switch (input)
        {
        case 'A'://add a course to the hash table

            cout << "Enter a course information using the format courseid:credits:capacity:days,time" << endl;
            cin >> str;
            //convert all delimiters in the sting into :
            for (int i = 0; i < 50; i++)
            {
                if (str[i] == ',')
                {
                    str[i] = ':';
                }
            }
            
            char* point;
            point = strtok(str, ":");
            parseSize = 0;
            //sperating all the information in the sting and putting them in an array
            while(point != NULL)
            {
                courseInfo[parseSize] = point;
                parseSize += 1;
                point = strtok(NULL, ":");
            }
            //case for if the user adds minutes to the input
            if(parseSize == 6)
            {
                time = courseInfo[4] +":"+ courseInfo[5];
            }
            else
            {
                time = courseInfo[4];
            }
                //extracting information from array into variables
                courseId = courseInfo[0];
                credit = stoi(courseInfo[1]);
                capacity = stoi(courseInfo[2]);
                days = courseInfo[3];

            //calling the insertElement function which returns either true if a coures was successfully added
            success = hash->insertElement(courseId, credit, capacity, days, time);
            
            if(success == false)
                cout << "The table is full"<< endl;
            break;

        case 'B'://searches for a course in the hash table
            cout << "Enter a courseId" <<endl;
            cin >> userIn;
            //calls the searchElement method which reatures a true if a course is found
            success = hash->searchElement(userIn);
            //if the coures does not exist it returns not found
            if(success == false)
                cout << userIn << " not found" << endl;
            break;

        case 'C'://allows the user to change the capacity of a course
            cout << "Enter a courseId and a capacity value to change to using the format courseId:capacity" << endl;
            cin >> str;
            point = strtok(str, ":,");
            parseSize = 0;
            //parses the users input and puts them into an array
            while(point != NULL)
            {
                courseInfo[parseSize] = point;
                parseSize += 1;
                point = strtok(NULL, ",");
            }
            //setting variables to users input
            courseId = courseInfo[0];
            capacity = stoi(courseInfo[1]);

            //calls changeCourseCapacity and returnes true if the course exists and the capacity was changed
            success = hash->changeCourseCapacity(courseId, capacity);

            if(success == false)
                cout << courseId << " not found" << endl;
            break;
        
        case 'D'://prints out the entire hash table
            hash->printHash();
            break;
        default:
            break;

        }
    } while (input != 'Q');//the user quits the program
    
    //deletes the hash object that was created earlier
    delete hash;
    return 0;
}