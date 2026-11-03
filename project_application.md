# Lab 11 - Project Application

## E1 - Original collection and borrowed pointers
Describe orders, view, and which array stores the actual records.
## Orders is the primary array that stores the actual OrderPreview records in a contiguous block of memory. It serves as the master collection and source of truth.
## View is a secondary array of pointers (OrderPreview *view[]) that does not store objects of its own, but instead borrows the memory addresses (&orders[i]) of the orders that match the selection criteria.

## E2 - Implemented view and test
Describe the four dummy cases, the expected selected IDs, and the observed IDs.
Explain how you checked that original data and storage order were preserved.
## ID 101: DELIVERY, PENDING (Actived, selected).
## ID 102: DINE_IN, IN_PROGRESS (Is not a delivery, excluded).
## ID 103: DELIVERY, IN_PROGRESS (Actived, selected).
## ID 104: DELIVERY, COMPLETED (Is not actived, excluded).
## ID 101 and 103 are the observed IDs.
## The state of orders was displayed before and after building the view, confirming that positions, values, and the original insertion order remained completely unaltered.

## E3 - Sorting criterion and next integration step
State the three comparison rules and give a small example of their expected order.
Identify the remaining integration work, if any.
## Primary field: Elements with higher priority or earlier delivery times come first (depending on business logic).
## Tie-breaking: If there is a match in the primary field, a secondary attribute (such as duration or ID) is used to sort deterministically.
## Stability: In the case of an exact tie, the original arrival order is preserved.
## Next integration step: Incorporate the filtered and sorted view into the system's main reporting modules, ensuring that views can be dynamically updated without corrupting the base transaction queue.

## E4 - Lab evidence
Source file: delivery_view_practice.cpp 
Test output: delivery_view_output.txt
Explain how this practice prepares the project's temporary report.
## This practice establishes a reliable, non-destructive foundation for generating temporary reports by separating the master data from the reporting layer. By using an array of borrowed pointers (view) rather than cloning or modifying the original collection (orders), the system can efficiently filter, sort, and display specific subsets of data (such as active deliveries) on the fly. 