#include <iostream>
#include<string>
#include<sstream>
#include<vector>
#include "AVL.h"
using namespace std;

int main()
{
    // Create instance of AVL Tree class in order to use when parsing inputs
    AVLTree tree;
    string num_commands;

    // Read entire input line to get correct number of commands to execute
    getline(cin, num_commands);

    // Looping through commands in order to process and execute them correctly
    for (int i = 0; i < stoi(num_commands); i++)
    {
        // Reads and interprets entire command line
        string command_line;
        getline(cin, command_line);

        // Reads and interprets current command
        istringstream in(command_line);
        string command;
        getline(in, command, ' ');

        // Use if statements to decide what action to complete
        if (command == "insert")
        {
            // Check that what being given is a name and UFID
            string name, UFID;

            // Read until first quote
            getline(in, name, '"');

            // Read until next quote to get full string/s
            getline(in, name, '"');
            in >> UFID;

            tree.testInsertNameID(name, UFID);

        }

        // Command that will invoke removeID function
        else if (command == "remove")
        {
            // check for being given name AND ID
            string UFID;

            // Read until first quote to then last quote
            getline(in, UFID, '"');
            getline(in, UFID, '"');


            tree.testRemoveID(UFID);
        }

        // Command that will invoke removeInorderN function
        if (command == "removeInorder")
        {
            int N;
            if (in >> N)
            {
                if (N < 0)
                {
                    cout << "unsuccessful" << endl;
                }
                else
                {
                    tree.testRemoveInorderN(N);
                }
            }
        }

        // Command that will invoke printInorder, printPreorder, or printPostorder functions
        else if (command == "printInorder")
        {
            tree.printInorder();
        }

        else if (command == "printPreorder")
        {
            tree.printPreorder();
        }

        else if (command == "printPostorder")
        {
            tree.printPostorder();
        }
        else if (command == "printLevelCount")
        {
            tree.testLevelCount();
        }

        // Command that will invoke either searchID or searchName function
        else if (command == "search")
        {
            string input;

            getline(in, input, '"');
            getline(in, input, '"');

            if (input.length() == 0)
            {
                cout << "unsuccessful" << endl;
            }

            // Check if input does not have digits, if so, use searchName
            if (!isdigit(input[0]))
            {
                tree.testSearchName(input);
            }

            else
            {
                // Otherwise use searchID
                tree.testSearchID(input);
            }

        }
    }

    // References:
    // Lecture Slides/Project Breakdown slides and video
}
