/*
 * Course: COEN 2220 - Programming 2
 * Name: [Jose Alejandro Vera Guagua]
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Practice - sort a temporary view without changing original tasks
 * Due date: [11/02/2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct RepairTask
{
    string taskId;     // Preserve the identity of the original task.
    int daysUntilDue;  // Smaller values must appear first in the report.
    int minutesNeeded; // Break equal-deadline ties with smaller durations first.
};

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right);
void mergeTaskView(RepairTask *view[], RepairTask *temporary[], int first, int middle, int last);
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last);
void displayOriginal(const RepairTask tasks[], int count);
void displayView(RepairTask *view[], int count);

int main()
{
    const int TASK_COUNT = 8;
    RepairTask tasks[TASK_COUNT] =
    {
        {"RT-101", 3, 30}, {"RT-102", 1, 20},
        {"RT-103", 2, 15}, {"RT-104", 1, 10},
        {"RT-105", 2, 15}, {"RT-106", 3, 10},
        {"RT-107", 1, 20}, {"RT-108", 2, 5}
    };
    RepairTask *view[TASK_COUNT];      // Borrow addresses of existing tasks.
    RepairTask *temporary[TASK_COUNT]; // Hold addresses while merging the view.
    for (int index = 0; index < TASK_COUNT; index++)
    {
        view[index] = &tasks[index]; // Preserve arrival order in the initial view.
    }

    cout << boolalpha;
    cout << "Original arrival order:" << endl;
    displayOriginal(tasks, TASK_COUNT);

    // ===== Resolve these TODOs now (Part C) =====
    // TODO (Part C): Activate the C test block after completing the comparator.
    
    cout << "Earlier deadline first: "
         << comesBeforeOrEqual(&tasks[1], &tasks[0]) << endl;
    cout << "Shorter duration within same deadline: "
         << comesBeforeOrEqual(&tasks[3], &tasks[1]) << endl;
    cout << "Exact tie keeps left: "
         << comesBeforeOrEqual(&tasks[2], &tasks[4]) << endl;
    cout << "Later deadline first: "
         << comesBeforeOrEqual(&tasks[0], &tasks[1]) << endl;
    

    // ===== Resolve these TODOs later (Part D) =====
    // TODO (Part D): Call mergeSortView for the complete logical range.
    mergeSortView(view, temporary, 0, TASK_COUNT - 1);
    // TODO (Part D): Display the sorted view with a descriptive heading.
    cout << "Sorted view (earlier deadlines first):" << endl;
    displayView(view, TASK_COUNT);
    // TODO (Part D): Display tasks again to prove that arrival order did not change.
    cout << "Original arrival order (unchanged):" << endl;
    displayOriginal(tasks, TASK_COUNT);

    return 0;
}

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right)
{
    // ===== Resolve this TODO now (Part C) =====
    // TODO (Part C): Implement the specified two-field order, including exact ties.
    if (left->daysUntilDue < right->daysUntilDue)
    {
        return true; // Left has an earlier deadline.
    }
    else if (left->daysUntilDue > right->daysUntilDue)
    {
        return false; // Right has an earlier deadline.
    }
    else
    {
        // Deadlines are equal, compare minutesNeeded.
        if (left->minutesNeeded < right->minutesNeeded)
        {
            return true; // Left has a shorter duration.
        }
        else if (left->minutesNeeded > right->minutesNeeded)
        {
            return false; // Right has a shorter duration.
        }
        else
        {
            return true; // Exact tie, preserve left's position.
        }
    }
    return false; // Temporary placeholder; replace this line in Part C.
}

// ===== Resolve these TODOs later (Part D) =====
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last)
{
    // TODO (Part D): Implement recursive merge sort using inclusive indices.
    if(first < last)
    {
        int middle = first + (last - first) / 2; // Calculate the middle index.
        mergeSortView(view, temporary, first, middle); // Sort the left half.
        mergeSortView(view, temporary, middle + 1, last); // Sort the right half.
        mergeTaskView(view, temporary, first, middle, last); // Merge the sorted halves.
    }
}

void mergeTaskView(RepairTask *view[], RepairTask *temporary[], int first, int middle, int last)
{
    // TODO (Part D): Merge two sorted segments using comesBeforeOrEqual.
    int first1 = first;
    int last1 = middle;
    int first2 = middle + 1;
    int last2 = last;
    int index = first1; // Siguiente posición disponible en el arreglo temporal

    // Combinar mientras ambos segmentos tengan elementos
    while ((first1 <= last1) && (first2 <= last2))
    {
        if (comesBeforeOrEqual(view[first1], view[first2]))
        {
            temporary[index] = view[first1];
            first1++;
        }
        else
        {
            temporary[index] = view[first2];
            first2++;
        }
        index++;
    }

    // Aqui se copian los elementos restantes de la primera mitad, si quedan
    while (first1 <= last1)
    {
        temporary[index] = view[first1];
        first1++;
        index++;
    }

    // Aqui se copian los elementos restantes de la segunda mitad, si quedan
    while (first2 <= last2)
    {
        temporary[index] = view[first2];
        first2++;
        index++;
    }
    // TODO (Part D): Preserve pending pointers and copy the merged segment back.
    for (index = first; index <= last; index++)
    {
        view[index] = temporary[index];
    }
}

void displayOriginal(const RepairTask tasks[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << tasks[index].taskId
             << " | Days until due: " << tasks[index].daysUntilDue
             << " | Minutes: " << tasks[index].minutesNeeded << endl;
    }
}

void displayView(RepairTask *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << view[index]->taskId
             << " | Days until due: " << view[index]->daysUntilDue
             << " | Minutes: " << view[index]->minutesNeeded << endl;
    }
}

/*
 * Analysis Answers
 *
 * C5 - Two-field decision
 * Explain the result for RT-103 compared with RT-108. Which field decides it?
 * 
 * Answer:
 *Although both tasks have the same daysUntilDue value of 2, the minutesNeeded field decides the order. RT-108 has a shorter duration (5 minutes) compared to RT-103 (15 minutes).
 * D1 - Recursive ranges
 * Show first, last, middle, and the base-case evaluations along the first branch
 * starting at 0..7. Identify where execution resumes after the call for 0..0.
 * 
 * Answer: The execution resumes at the call for 1..1 after the base case for 0..0 is reached. The first, last, and middle
 * values for the first branch are as follows.
 *
 * D2 - Stable ties
 * Identify both pairs of tasks that tie in the two sort fields. Explain how the
 * comparator and the merge preserve their arrival order.
 * 
 * Answer: The comparator preserves the arrival order for tasks that tie in both sort fields by returning
 * truue when the left task is equal to the right task.
 *
 * D3 - Time, space, and original data
 * Give the sorting time and auxiliary-space order of this pointer-array version.
 * Compare with the linked-list sort in Part B and explain why the original task
 * storage order is preserved here but the node order changes in Part B.
 * 
 * Answer: The sorting time for this pointer-array version is O(n Log n) and the auxiliary space is O(n).
 * In contrast, the linked-list sort in Part B also has a time complexity of O(n Log n) but uses O(1) auxiliary space.
 * The original task storage order is preserved in this pointer version because we are sorting an array of pointers to
 * the original tasks, rather than the tasks themselves. This means that the original array of tasks remains unchanged.
 *
 */