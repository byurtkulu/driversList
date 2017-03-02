//
//  main.cpp
//  FormulaDriverListLinkedList
//
//  Created by Bahadır Yurtkulu on 27.02.2017.
//  Copyright © 2017 Bahadir. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include "strutils.h"



using namespace std;





// To store the drivers data.
// It has 3 types of data:
//    Driver Name (string)
//    Driver Point (int)
//    Next (pointer, which points to the next node)
//
struct node {
    string name;
    int point;
    node * next; // points to next node or to NULL.
    
    //default constructor
    node()
        :name("@Mr. Nobody"), point(0), next(NULL)
    {}
    
    //constructor
    node(string str, int i, node * n)
        :name(str), point(i), next(n)
    {}
};





// Searchs given string in a linked list.
// Takes two parameter:
//       head pointer of the linked list
//       string to be searched
//
//

//**** This function is directly copied from linkedList.cpp ****//

bool SearchList(node *head, string searchValue)
{
    while (head != NULL)
    {
        if(head->name == searchValue) {
            //If the node with the given ID is found
            return true;
        }
        head = head->next;
    }
    //If the code proceeds from here, it means that the whole list is traversed
    //and a node with ID == searchValue could not be found.
    return false;
}




// add a seperately created node to the linked list alphabetically.
//
void insertAlphabetically (node* headPtr, node* &tempHead) {
    
    // compare function compare two string alphabetically.
    // str1.compare(str2)
    // if str1 comes first alphabetically func returns negative integer
    // if they are same it returns zero
    // else (str2 comes first) it returns positive integer
    //
    
    // checks the next node's name
    // compare them if new drivers name is smaller then the
    // next nodes driver names, insert new driver before the next one.
    //
    //             head node     next        ...
    //              --------    -------    -------
    //  headPtr --> | head |--->| 1st |--->| 2nd |---> ... ---> NULL
    //              --------    -------    -------
    //
    //               ---------------
    //  tempHead --> |  new node   |
    //               | driver data | --> NULL
    //               ---------------
    //
    //
    while (headPtr != NULL) {
        
        if (headPtr != NULL && headPtr->next != NULL) {  // short circuit evaluation is used.
            

            
            
            if (tempHead->name.compare((headPtr->next)->name) < 0) {

                tempHead->next = headPtr->next;
                headPtr->next = tempHead;
                
                headPtr = NULL;
            }
            
            else {
                headPtr = headPtr->next;
            }
        }
        else if (headPtr->next == NULL) {
            
            headPtr->next = tempHead;
            headPtr = NULL;
        }
        

    }
    
    tempHead = NULL;
    
}



// if new drivers name exists in the list
// find drivers node and sum the points
// if negative or zero, delete the node.
// else update.
//
void sumPoints(node* headPtr, string driverName, int driverPoint) {
    node* prev = headPtr;
    
    headPtr = headPtr->next;
    
    while (headPtr != NULL) {
        
        if (headPtr->name == driverName) {
            
            headPtr->point += driverPoint;
           
            if (headPtr->point <= 0) {
                //delete this node
                cout << driverName << " has been removed from the list since his points became non-positive.\n";
                prev->next = headPtr->next;
                headPtr->next = NULL;
                headPtr = NULL;
            }
            else {
                cout << headPtr->name << " has been updated and new point is " << headPtr->point << '\n';
                headPtr = NULL;
            }
        }
        
        else {
            prev = headPtr;
            headPtr = headPtr->next;
        }
    }
}







///////////////////////////
//=======================//
//==== MAIN FUNCTION ====//
//=======================//
///////////////////////////

int main() {
    int option;
    string optionStr;
    node* headPtr = nullptr;
    node* prevPtr = nullptr;
    node* tempHead = nullptr;
    
    
    
    ifstream driverFile;
    string fileName;
    string line;
    string driverName;
    int driverPoint;
    bool isExist;
    
    
    
    
    while (true) {
        
        
        cout << "\nFormula 1 Points Table System" << endl;
        cout << "---------------------------------" << endl;
        cout << "Please select one option [1..4]: " << endl;
        cout << "1. Load driver names and points from a file\n";
        cout << "2. Insert a new driver / Modify points of an existing driver\n";
        cout << "3. Display points table in alphabetical order\n";
        cout << "4. Exit" << endl;
        
        cin >> optionStr;
        option = atoi(optionStr);
        
        while (option > 4 || option < 1) {
            cout << "Oops! This is not a valid option. Enter again: \n";
            cin >> optionStr;
            option = atoi(optionStr);
        }
        
         if (option == 1) {
            //Load driver names and points from a file
            
            headPtr = new node; //create initial node.
            
            
            
            /********* open the file *********/
            
            cout << "Enter the file name: \n";
            cin >> fileName;
            driverFile.open(fileName);
            
            while (driverFile.fail()) {
                
                cout << "Oops! Could not open. Enter the name again: \n";
                driverFile.clear();
                cin >> fileName;
                driverFile.open(fileName);
            }
            
            
            
            /****** Read line by line and add to the linked list or update *******/
            
            while (getline(driverFile, line)) {
                istringstream iss(line);
                iss >> driverName >> driverPoint;
                
                //we have first line driver names and point.
                //check if it exist...
                isExist = SearchList(headPtr, driverName);
                
                
                if(!isExist) {

                    if (driverPoint > 0) {
                        //if it is not exist create a node
                        tempHead = new node(driverName, driverPoint, NULL);
                        
                        //insert it to the linked list alphabetically.
                        insertAlphabetically(headPtr, tempHead);
                        cout << driverName << " has been added to the list with initial points " << driverPoint << '\n';
                    }
                    else {
                        cout << driverName << " has not been added since the initial points cannot be non-positive.\n";
                    }
                }
                else {
                    
                    //If exists in the linked list
                    //sum points.
                    sumPoints(headPtr, driverName, driverPoint);
                }
            }
            
        }
        
        else if (option == 2) {
            //Insert a new driver / Modify points of an existing driver
            cout << "Please enter name of the driver you wish to add/modify: ";
            cin >> driverName;
            cout << "Please enter how many points you wish to initialize/add/remove: ";
            cin >> driverPoint;
            
            isExist = SearchList(headPtr, driverName);
            
            if(!isExist) {
                
                if (driverPoint > 0) {
                    //if it is not exist create a node
                    tempHead = new node(driverName, driverPoint, NULL);
                    
                    //insert it to the linked list alphabetically.
                    insertAlphabetically(headPtr, tempHead);
                    cout << driverName << " has been added to the list with initial points " << driverPoint << '\n';
                }
                
                else {
                    cout << driverName << " has not been added since the initial points cannot be non-positive.\n";
                }
            }
            
            else {
                
                //If exists in the linked list
                //sum points.
                sumPoints(headPtr, driverName, driverPoint);
            }
        }
        
        else if (option == 3) {
            //Display points table in alphabetical order
            
            if (headPtr != nullptr) {
            
                tempHead = headPtr;
                cout << "\nPoints Table\n";
                cout << "----------------------------\n";
                
                tempHead = tempHead->next; // do not print head node, @Mr. Nobody.
                while (tempHead != NULL) {
                    cout << tempHead->name << "  " << tempHead->point << '\n';
                    tempHead = tempHead->next;
                }
            }
            
            else {
                cout << "\nThe points table is empty.\n\n";
            }
            
            tempHead = nullptr;
        }
        
        else if (option == 4) {
            
            //return all the dynamically allocated memory to the heap before the termination
            
            driverFile.close();
            
            
            delete headPtr;
            delete tempHead;
            delete prevPtr;
            cin.get();
            cin.ignore();
            
            return 0;
        }
    }
}
