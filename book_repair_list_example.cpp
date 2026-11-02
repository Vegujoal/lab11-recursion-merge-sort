/*
 * Course: COEN 2220 - Programming 2
 * Name: [Jose Alejandro Vera Guagua]
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Guided example - recursive total and linked-list merge sort
 * Due date: [12/2/2026]
 */

#include <iostream>
#include <string>
using namespace std;

class BookRepairList
{
private:
    struct Node
    {
        string bookCode; // Keep the book identity attached to its page count.
        int pages;       // Store the number of pages still needing repair.
        Node *next;      // Link to the next registered book.
    };

    Node *head; // Remember the first node of the collection.

    // --- STEP B2: Sum pages recursively ---
    
    int totalFrom(Node *current) const
    {
        if (current == nullptr)
        {
            return 0; // Base case: no remaining books contribute zero pages.
        }

        int laterPages = totalFrom(current->next); // Solve a shorter remaining chain.
        return current->pages + laterPages; // Finish this call after the next returns.
    }
    

    // --- STEP B3: Split, recursively sort, and merge existing nodes ---
    
    Node *splitList(Node *firstNode)
    {
        Node *slow = firstNode;
        Node *fast = firstNode;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            slow = slow->next;       // Find the final node of the left half.
            fast = fast->next->next;
        }

        Node *rightHead = slow->next; // Keep the right half before cutting its link.
        slow->next = nullptr;         // Both halves now end independently.
        return rightHead;
    }

    Node *mergeLists(Node *left, Node *right)
    {
        if (left == nullptr)
        {
            return right;
        }
        if (right == nullptr)
        {
            return left;
        }

        Node *result;
        if (left->pages <= right->pages)
        {
            result = left; // Prefer the left node on ties to preserve arrival order.
            left = left->next;
        }
        else
        {
            result = right;
            right = right->next;
        }

        Node *tail = result; // Track the last node already selected.
        while (left != nullptr && right != nullptr)
        {
            if (left->pages <= right->pages)
            {
                tail->next = left;
                left = left->next; // Preserve access to the unused left chain.
            }
            else
            {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }

        if (left != nullptr)
        {
            tail->next = left;
        }
        else
        {
            tail->next = right; // Attach the entire chain that has not been used.
        }
        return result;
    }

    Node *sortNodes(Node *firstNode)
    {
        if (firstNode == nullptr || firstNode->next == nullptr)
        {
            return firstNode; // Zero or one node is already sorted.
        }

        Node *rightHead = splitList(firstNode);
        Node *leftSorted = sortNodes(firstNode); // Finish the left half first.
        Node *rightSorted = sortNodes(rightHead);
        return mergeLists(leftSorted, rightSorted); // Both inputs are now sorted.
    }
    

public:
    BookRepairList()
    {
        head = nullptr;
    }

    ~BookRepairList()
    {
        while (head != nullptr)
        {
            Node *nodeToDelete = head;
            head = head->next; // Preserve the next address before releasing this node.
            delete nodeToDelete;
        }
    }

    void addBook(const string& newBookCode, int newPages)
    {
        Node *newNode = new Node;
        newNode->bookCode = newBookCode;
        newNode->pages = newPages;
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode; // Register books in their original arrival order.
    }

    void display() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << "Book: " << current->bookCode
                 << " | Pages: " << current->pages << endl;
            current = current->next;
        }
    }

    // --- STEP B2: Offer a public operation without exposing Node ---
    
    int totalPages() const
    {
        return totalFrom(head); // Start the recursive traversal at the first book.
    }
    

    // --- STEP B3: Preserve the new entry point after sorting ---
    
    void sortByPages()
    {
        head = sortNodes(head); // The smallest book may become the new first node.
    }
    
};

int main()
{
    BookRepairList repairs;
    repairs.addBook("BK-101", 12);
    repairs.addBook("BK-102", 4);
    repairs.addBook("BK-103", 9);
    repairs.addBook("BK-104", 2);
    repairs.addBook("BK-105", 7);
    repairs.addBook("BK-106", 4);
    repairs.addBook("BK-107", 10);
    repairs.addBook("BK-108", 3);

    cout << "Arrival order:" << endl;
    repairs.display();

    // --- STEP B2: Observe the recursive total ---
    
    cout << "Total pages before sorting: " << repairs.totalPages() << endl;

    // --- STEP B3: Observe the sorted list and verify the total ---
    
    repairs.sortByPages();
    cout << "Sorted by pages:" << endl;
    repairs.display();
    cout << "Total pages after sorting: " << repairs.totalPages() << endl;
    

    return 0;
}

/*
 * Analysis Answers
 *
 * B4 - Recursive total
 * For the eight-book list, how many totalFrom calls occur, including the base case?
 * What value does the call for BK-108 return, and where does execution resume next?
 * Answer: Ocurred 9 calls, including the base case. The call for BK-108 returns 3, and execution resumes at the call for BK-107.
 *
 * B5 - Splitting and returning
 * Show the two-node sublist BK-101:12 -> BK-102:4, its base cases, and its merged
 * result. Which node address is returned? Why must sortByPages update head?
 * Answer:
 *Splitlist fuction divide the list into two halves, the first half is BK-101:12 and the second half is BK-102:4. The base cases
 are when the list has zero or one node, which are already sorted. The merged result is BK-102:4 -> BK-101:12. The address of the 
 node BK-102 is returned because it is the new head of the sorted list and sortByPages must update head to point to the new first node 
 of the sorted list.
 * B6 - Time and auxiliary space
 * Compare totalPages and sortByPages. Give the time and auxiliary-space order of
 * each operation, including pending calls. Do not count list construction.
 * Answer:
 *totalPages: (Time complexity O(N)) The function visits each of the N nodes in the linked list exactly once to accumulate the page count.
 In auxiliary O(N) space, The recursive call stack stores N pending function frames simultaneously before starting to return and add up the values.
sortyByPages: (Time complexity O(N log N)) The function recursively splits the list into halves and merges them back together, resulting in a logarithmic number of levels of recursion with each level processing all N nodes. 
    In auxiliary O(log N) space, The recursive call stack stores log N pending function frames simultaneously before starting to return and merge the sorted sublists.
 */