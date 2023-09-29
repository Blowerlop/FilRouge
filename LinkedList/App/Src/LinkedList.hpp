#pragma once

#include <iostream>;

class LinkedList
{
	struct Node
	{
		std::string word{  };
		Node* nextPtr{ };

		Node(std::string word, Node* nextPtr);
	};

public:
	// Variables
	Node* rootNodePtr;


	// Constructors & Destructors
	LinkedList();
	LinkedList(const char* fileNamePtr);
	~LinkedList();


	// Methods
	Node* Load(const char* fileNamePtr);
	void Display(Node* headPtr);
	void DisplayPreviousAndNext(Node* headPtr, std::string_view word);
	void Invert(Node*& headPtr);
	void Sort(Node** headPtr);
	LinkedList* Find(Node* headPtr, char firstLetter);
};