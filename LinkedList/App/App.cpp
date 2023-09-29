#include <iostream>
#include <LinkedList.hpp>


bool quit;

void DisplayActions()
{
    std::cout << "===========" << std::endl;
    std::cout << "1. Display list" << std::endl;
    std::cout << "2. Previous / next" << std::endl;
    std::cout << "3. Invert list" << std::endl;
    std::cout << "4. Sort list" << std::endl;
    std::cout << "5. Find in list" << std::endl;
    std::cout << "6. Quit" << std::endl;
    std::cout << "===========" << std::endl;
    std::cout << std::endl;
}

void PlayAction(int index, LinkedList& linkedList)
{
    switch (index)
    {
        case 1:
            linkedList.Display(linkedList.rootNodePtr);
            break;

        case 2:
            {
                std::cout << "Target:" << std::endl;
                std::string response;
                std::cin >> response;
                linkedList.DisplayPreviousAndNext(linkedList.rootNodePtr, response);
            }
            break;

        case 3:
            linkedList.Invert(linkedList.rootNodePtr);
            break;

        case 4:
            linkedList.Sort(&linkedList.rootNodePtr);
            break;

        case 5:
            std::cout << "Target:" << std::endl;
            char response;
            std::cin >> response;
            linkedList.Find(linkedList.rootNodePtr, response);
            break;

        case 6:
            quit = true;
            break;

        default:
            std::cout << "This is not a valid input" << std::endl;
            break;
    }
}

int main()
{
    LinkedList linkedList("./words.txt");

    int actionChoice;
    while (quit == false)
    {
        DisplayActions();
        std::cout << "Actions:" << std::endl;
        
        std::cin >> actionChoice;
        std::cout << std::endl;

        PlayAction(actionChoice, linkedList);

        for (size_t i = 0; i < 4; i++)
        {
            std::cout << std::endl;
        }
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }
}