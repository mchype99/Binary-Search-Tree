
//***********************************************************************************
//								B S T . C P P

/*
This is a simple program to give the student experience writing code
for binary trees.  This is a CLASS implementation of the BST ADT.
The student should study, comment, correct errors, compile,
implement/un-implemented/undeveloped functions, and modify code to make
it more efficient when ever necessary. The student should be able to
discuss the advantages and disadvantages of using such an
implementation.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: Default Constructor
//Precondition: Constructor has not been invoked.
//Postcondition: root = 0;info from text file entered into bst.
//Description: Constructs an instance of a bst object with info from text file.
///////////////////////////////////////////////////////////////////////////////////////////////
bst::bst()
{
	ifstream in;
    ifstream in2;
    string county;
    string county2;
    double population;
    string s;
    int scount = 0;
    in.open("county_data.txt"); 
    in2.open("county_data.txt"); 
    root = 0; 

    if (in.is_open() && in2.is_open())
    { 
		while (!in.eof()) 
        {
			while (getline(in, s))
            {
                for (int i = 0; i < s.length(); i++)
                {
					if (s[i] == ' ') 
					{
						scount++;
                    }
                }
                if (scount == 1) 
                {
					in2 >> county >> population;
					insert(county, population);
                }
                if (scount == 2) 
                {
					in2 >> county >> county2 >> population;
                    county = county + " " + county2;
                    insert(county, population);
                }
                scount = 0;            
            }
        }
    }
    else 
    {
		cout << "No file found." << endl;
    }
    in.close();
    in2.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: empty
//Precondition: bst is initialized
//Postcondition: return true if bst is null; otherwise false is retured.
//Description: Checks if bst is empty
///////////////////////////////////////////////////////////////////////////////////////////////
bool bst::empty()
{
	return (root == 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: insert
//Precondition: bst is initialized.
//Postcondition: parameters are put through overloaded insert function
//Description: auxiliary function for insert.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::insert(string item, double pop)
{
	insert(root, item, pop);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: insert
//Precondition: bst is initialized
//Postcondition: item added to bst.
//Description: inserts an item into the bst.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::insert(treenode * & loc_ptr, string item, double pop)
{
	if (loc_ptr == 0)
	{
		loc_ptr = new treenode;
		loc_ptr->lchild = loc_ptr->rchild = 0;
		loc_ptr->county_name = item;
		loc_ptr->population_size = pop;
	}
	else if (loc_ptr->county_name>item)
		insert(loc_ptr->lchild, item, pop);
	else if (loc_ptr->county_name<item)
		insert(loc_ptr->rchild, item, pop);
	else
		cout << "the item is already in the tree\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: search_tree
//Precondition: bst is initialized
//Postcondition: parameters are run through overloaded search_tree function
//Description: auxiliary function for search_tree
///////////////////////////////////////////////////////////////////////////////////////////////
treenode * bst::search_tree(string item)
{
	return search_tree(root, item);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: search_tree
//Precondition: bst is initialized
//Postcondition: returns a pointer to the node in bst with a county name that matches item
//Description: returns a pointer to the node in bst with a county name that matches item
///////////////////////////////////////////////////////////////////////////////////////////////
treenode * bst::search_tree(treenode * loc_ptr, string item)
{
	if (loc_ptr != 0)
	{
		if (loc_ptr->county_name == item)
			return loc_ptr;
		else if (loc_ptr->county_name>item)
			return search_tree(loc_ptr->lchild, item);
		else
			return search_tree(loc_ptr->rchild, item);
	}
	else
		return loc_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: del_name
//Precondition: bst is initialized
//Postcondition: parameters are run through overloaded del_name function
//Description: auxiliary function for overloaded del_name function.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::del_name(string item)
{
	del_name(root, item);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: del_name
//Precondition: bst is initialized
//Postcondition: Item deleted from bst
//Description: deletes an item from the bst if found
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::del_name(treenode * & loc_ptr, string item)
{
	if (loc_ptr == 0)
		cout << "item not in tree\n";
	else if (loc_ptr->county_name > item)
		del_name(loc_ptr->lchild, item);
	else if (loc_ptr->county_name < item)
		del_name(loc_ptr->rchild, item);
	else
	{
		treenode * ptr;

		if (loc_ptr->lchild == 0)
		{
			ptr = loc_ptr->rchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else if (loc_ptr->rchild == 0)
		{
			ptr = loc_ptr->lchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else
		{
			ptr = inorder_succ(loc_ptr);
			loc_ptr->county_name = ptr->county_name;
			del_name(loc_ptr->rchild, ptr->county_name);
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: inorder_succ
//Precondition: bst is initialized
//Postcondition: returns a pointer to the inorder successor, based on county name. 
//Description: returns a pointer to the inorder successor, based on county name. 
///////////////////////////////////////////////////////////////////////////////////////////////
treenode * bst::inorder_succ(treenode * loc_ptr)
{
	treenode *ptr = loc_ptr->rchild;

	while (ptr->lchild != 0)
	{
		ptr = ptr->lchild;
	}
	return ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: print_tree
//Precondition: bst is initialized
//Postcondition: parameters are run through overloaded print_tree function
//Description: auxiliary function for overloaded print_tree function.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::print_tree()
{
	print_tree(root);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: print_tree
//Precondition: bst is initialized
//Postcondition: prints each county record to the screen sorted by county name.
//Description: prints each county record to the screen sorted by county name.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::print_tree(treenode * loc_ptr)
{
	if (loc_ptr != 0) 
	{
		print_tree(loc_ptr->lchild);
		cout << loc_ptr->county_name << ", " << loc_ptr->population_size << endl;
		print_tree(loc_ptr->rchild);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: Destructor
//Precondition: bst is initialized
//Postcondition: all allocated memory for bst is de-allocated.
//Description: de-allocates dynamic memory allocate for tree bool
///////////////////////////////////////////////////////////////////////////////////////////////
bst::~bst()
{
	while (root != 0)
	{
		del_name(root->county_name);
	}
	cout << "Destructor has been called\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: county_ranges
//Precondition: bst is initialized
//Postcondition: parameters are run through overloaded county_ranges function
//Description: auxiliary function for overloaded county_ranges function.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::county_ranges(const string& min_name, const string& max_name)
{
	county_ranges(root, min_name, max_name);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: county_ranges
//Precondition: bst is initialized
//Postcondition: all county names between min_name and max_name are displayed
//Description: prints all the county names to the screen that lie between min_name and max_name.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::county_ranges(treenode*& node, const string& min_name, const string& max_name)
{
	if (node != 0) 
	{
		if (node->county_name.compare(min_name) > 0)
		{
			county_ranges(node->lchild, min_name, max_name);
		}
		if (node->county_name.compare(min_name) >= 0)
		{
			if (node->county_name.compare(max_name) <= 0)
			{
				cout << node->county_name << ", " << node->population_size << endl;
			}
		}
		if (node->county_name.compare(max_name) < 0)
		{
			county_ranges(node->rchild, min_name, max_name);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: sorted_info
//Precondition: bst is initialized
//Postcondition: all county names between min_name and max_name are displayed
//Description: Creates new file, calls overloaded function sorted_info to print to file
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::sorted_info()
{
	ofstream out;
	out.open("county_info.txt");
	out.precision(10);

	sorted_info(out, root);

	out.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: sorted_info
//Precondition: bst is initialized
//Postcondition: prints each county record to a file called “county_info.txt” sorted by county name.
//Description: prints each county record to a file called “county_info.txt” sorted by county name.
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::sorted_info(ofstream& out, treenode*& loc_ptr)
{
	if (out.is_open())
	{
		if (loc_ptr != 0)
		{
			sorted_info(out, loc_ptr->lchild);
			out << loc_ptr->county_name << "  " << loc_ptr->population_size << "\n";
			sorted_info(out, loc_ptr->rchild);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: empty_tree
//Precondition: bst is initialized
//Postcondition: all nodes that were allocated to the bst are de-allocated
//Description: de-allocate all nodes that were allocated to the bst
///////////////////////////////////////////////////////////////////////////////////////////////
void bst::empty_tree()
{
	while (root != 0)
	{
		del_name(root->county_name);
	}
}