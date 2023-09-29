#include <iostream>
#include <LinkedList.hpp>
#include <fstream>
#include <string>


LinkedList::LinkedList() :
	rootNodePtr(nullptr)
{

}

LinkedList::LinkedList(const char* fileNamePtr)
{
	rootNodePtr = Load(fileNamePtr);
}

LinkedList::~LinkedList()
{
	Node* nextNodePtr = rootNodePtr;

	while (nextNodePtr != nullptr)
	{
		Node* currentNodePtr = nextNodePtr;
		nextNodePtr = nextNodePtr->nextPtr;
		delete currentNodePtr;
	}
}

LinkedList::Node::Node(std::string wordPtr, Node* nextPtr) :
	word(wordPtr),
	nextPtr(nextPtr)
{

}

LinkedList::Node* LinkedList::Load(const char* fileName)
{
	Node* rootNodePtr = nullptr;
	Node* previousNodePtr = nullptr;

	std::ifstream fileStream;

	fileStream.open(fileName, std::ios::in);
	if (fileStream.is_open() == false)
	{
		std::cout << "Unable to open the file" << std::endl;
		return nullptr;
	}

	std::string output;
	while (getline(fileStream, output))
	{
		if (rootNodePtr == nullptr)
		{
			rootNodePtr = new Node(output, nullptr);
			previousNodePtr = rootNodePtr;
		}
		else
		{
			Node* currentNode = new Node(output, nullptr);

			previousNodePtr->nextPtr = currentNode;
			previousNodePtr = currentNode;
		}

	}

	fileStream.close();
	return rootNodePtr;
}

void LinkedList::Display(Node* headPtr)
{
	while (headPtr != nullptr)
	{
		std::cout << headPtr->word << std::endl;
		headPtr = headPtr->nextPtr;
	}
}

void LinkedList::DisplayPreviousAndNext(Node* headPtr, std::string_view word)
{
	if (headPtr == nullptr)
	{
		std::cout << "headPtr nullptr" << std::endl;
		return;
	}

	Node* previousNode = nullptr;
	bool found = false;
	while (headPtr != nullptr && found == false)
	{
		if (headPtr->word == word)
		{
			found = true;

			if (previousNode != nullptr)
			{
				std::cout << "Previous : " + previousNode->word << std::endl;
			}

			if (headPtr->nextPtr != nullptr)
			{
				std::cout << "Next : " + headPtr->nextPtr->word << std::endl;
			}
		}

		previousNode = headPtr;
		headPtr = headPtr->nextPtr;
	}
}

void LinkedList::Invert(Node*& headPtr)
{
	Node* currentNodePtr = nullptr;
	Node* previousNodePtr = nullptr;

	while (headPtr != nullptr)
	{
		previousNodePtr = headPtr->nextPtr;
		headPtr->nextPtr = currentNodePtr;
		currentNodePtr = headPtr;
		headPtr = previousNodePtr;
	}
	headPtr = currentNodePtr;
}

//
// Hadn't been able to sort the LinkedList on my own because I was always losing the headNode
//
void LinkedList::Sort(Node** headNodePtr)
{
	// pHead always points to the head of the list
	Node* currentNodePtr{ *headNodePtr };
	*headNodePtr = nullptr;

	// Bubble sort on a linked list
	bool exchangeOccurs{ true };
	while (exchangeOccurs)
	{
		Node* leftNodePtr = currentNodePtr;
		Node* rightNodePtr = currentNodePtr->nextPtr;
		exchangeOccurs = false;

		while (rightNodePtr != nullptr)
		{
			// Right < Left (lexicographically)
			if (tolower((rightNodePtr)->word[0]) < tolower((leftNodePtr)->word[0]))
			{
				std::swap(*leftNodePtr, *rightNodePtr);
				std::swap((leftNodePtr)->nextPtr, (rightNodePtr)->nextPtr);

				leftNodePtr = (leftNodePtr)->nextPtr;

				exchangeOccurs = true;
			}
			else
			{
				leftNodePtr = rightNodePtr;
				rightNodePtr = rightNodePtr->nextPtr;
			}
		}

		// Link last node to the sorted segment
		rightNodePtr = *headNodePtr;

		// If an exchange occurs, detach the final node, terminate the list, and
		// continue.
		if (exchangeOccurs)
		{
			// Take the last node off the list and push it into the result.
			*headNodePtr = leftNodePtr;
			leftNodePtr = nullptr;
		}
		// List sorted.
		// Update pHead pointer and stop the  loop
		else
		{
			*headNodePtr = currentNodePtr;
			break;
		}
	}
}

LinkedList* LinkedList::Find(Node* headPtr, char firstLetter)
{
	if (headPtr == nullptr)
	{
		std::cout << "pHead is nullptr" << std::endl;
		return nullptr;
	}

	if (std::isalpha(firstLetter) == false) return nullptr;
	
	firstLetter = (char)std::tolower(firstLetter);

	LinkedList* newLinkedListPtr = new LinkedList();

	Node* currentHeadPtr = nullptr;
	Node* currentNodePtr = headPtr;
	while (currentNodePtr != nullptr)
	{
		std::string currentNodeWord = currentNodePtr->word;

		if (std::tolower(currentNodeWord[0]) == firstLetter)
		{
			if (newLinkedListPtr->rootNodePtr == nullptr)
			{
				newLinkedListPtr->rootNodePtr = new Node(currentNodeWord, nullptr);
				currentHeadPtr = newLinkedListPtr->rootNodePtr;
				std::cout << currentNodeWord << std::endl;
			}
			else
			{
				currentHeadPtr->nextPtr = new Node(currentNodeWord, nullptr);
				currentHeadPtr = currentHeadPtr->nextPtr;
				std::cout << currentNodeWord << std::endl;
			}

		}

		currentNodePtr = currentNodePtr->nextPtr;
	}

	if (newLinkedListPtr->rootNodePtr == nullptr)
	{
		delete newLinkedListPtr;
		return nullptr;
	}
	
	return newLinkedListPtr;
}