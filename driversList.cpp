//
//  main.cpp
//  FormulaDriverListLinkedList
//
//  Created by Bahadır Yurtkulu on 27.02.2017.
//  Copyright © 2017 Bahadir. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "strutils.h"

using namespace std;


/*************************************************************************/


struct node {
    string name;
    int point;
    node * next;
    
    //default constructor
    node()
        :name("@Mr. Nobody"), point(0), next(NULL)
    {}
    
    //constructor
    node(string str, int i, node * n)
        :name(str), point(i), next(n)
    {}
};



/*************************************************************************/


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



/*************************************************************************/


void insertAlphabetically (node* headPtr, node* &tempHead) {
    
    while (headPtr != NULL) {
        
        if (headPtr != NULL && headPtr->next != NULL) {
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


/*************************************************************************/


void sumPoints(node* headPtr, string driverName, int driverPoint) {
    node* prev = headPtr;
    
    headPtr = headPtr->next;
    
    while (headPtr != NULL) {
        
        if (headPtr->name == driverName) {
            
            headPtr->point += driverPoint;
           
            if (headPtr->point <= 0) {
                //delete this node
                prev->next = headPtr->next;
                headPtr->next = NULL;
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



/*************************************************************************/


int main() {
    int option;
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
        
        
        cout << "Formula 1 Points Table System" << endl;
        cout << "-----------------------------" << endl;
        cout << "Please select one option [1..4]: " << endl;
        cout << "1. Load driver names and points from a file\n";
        cout << "2. Insert a new driver / Modify points of an existing driver\n";
        cout << "3. Display points table in alphabetical order\n";
        cout << "4. Exit" << endl;
        
        cin >> option;
        while (option > 4 || option < 1) {
            cout << "Oops! This is not a valid option. Enter again: \n";
            cin.clear();
            cin >> option;
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
            /********************************/
            
            
            
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
        
        if (option == 2) {
            //Insert a new driver / Modify points of an existing driver
            
        }
        
        if (option == 3) {
            //Display points table in alphabetical order
            
            if (headPtr != nullptr) {
            
                tempHead = headPtr;
                cout << "Points Table\n";
                cout << "----------------------------\n";
                while (tempHead != NULL) {
                    cout << tempHead->name << "  " << tempHead->point << '\n';
                    tempHead = tempHead->next;
                }
            }
            
            else {
                cout << "The points table is empty.\n\n";
            }
        }
        
        if (option == 4) {
            
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
