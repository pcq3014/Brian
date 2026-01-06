/* 
Question 1:
We want to compute a division between two integers (divisor is different from 0) 
using only subtraction and recursion as follows:
    div(a, b) = remainder = a if a < b and quotient = quotient + 1, div(a - b, b).
    For example: quotient and remainder = 0 at the beginning
        . div(10, 3) = (quotient = 1, div(10-3, 3)) = (quotient = 2, div(7-3, 3)) = (quotient = 3, div(4-3, 3))
        . div(1, 3) = ( remainder = 1)
        . Result: quotient = 3, remainder = 1
Note: Use pointers to update the quotient and remainder in the recursive function. You can use the following declaration
int div(int *q, int *r, int a, int b);

    . Implement this recursive division algorithm in C.
    . Calculate the complexity of your algorithm. Justify your answer.

Question 2: Let a priority queue of elements be defined as follows:
    typedef struct {
        int data;
        int priority; //possible values: [0 .. 5]
}Element;
    typedef struct {
        int size;
        Element data[100];
}Queue;
    In this queue: Element with higher priority values (Smaller number) are placed at the front whenever a new element
is added.
    
    . Initial Queue:
    Data: 30 | Priority: 1
    Data: 25 | Priority: 3

    .After enqueue (10, 0):
    Data: 10 | Priority: 0
    Data: 30 | Priority: 1
    Data: 25 | Priority: 3

. The dequeue operation removes the front element (i.e., the element with the 
highest priority).
You have to implement the following functions in C
. Implement a function init() to initialize the queue and create an initial queue with at least 
six elements of your choice (data and priority).
. Implement the enqueue() and dequeue() functions and other basic functions (init(), display(), etc)
Write a main() function to test all the above functions.
    
*/

Question 1: 
#include <stdio.h>

/**
 * Recursive function to compute division using subtraction.
 * * @param q Pointer to the quotient variable (should be initialized to 0)
 * @param r Pointer to the remainder variable
 * @param a The dividend
 * @param b The divisor (assumed > 0)
 * @return 0 on completion
 */
int recursive_div(int *q, int *r, int a, int b) {
    // Base case: if dividend a is less than divisor b
    if (a < b) {
        *r = a; // The remaining value of a is the remainder
        return 0;
    } 
    // Recursive step
    else {
        (*q)++; // Increment quotient
        // Recursively call with reduced dividend (a - b)
        return recursive_div(q, r, a - b, b);
    }
}

int main() {
    int a = 10;
    int b = 3;
    int quotient = 0;   // Initialize quotient to 0 as per requirements
    int remainder = 0;  // Initialize remainder

    // Check for division by zero constraint
    if (b == 0) {
        printf("Error: Divisor cannot be 0.\n");
        return 1;
    }

    recursive_div(&quotient, &remainder, a, b);

    printf("Division: %d / %d\n", a, b);
    printf("Result: Quotient = %d, Remainder = %d\n", quotient, remainder);

    return 0;
}


/* 2. Complexity AnalysisTo determine the complexity, we look at how many times the recursive
 function is called based on the input values a (dividend) and b (divisor)
 .  Logic: The algorithm works by repeatedly subtracting b from a until a is less than b.
 .  Recurrence Relation: T(a) = T(a - b) + 1
 .  Number of Steps: The recursion depth corresponds exactly to the number of times we can subtract b from a. 
 Mathematically, this is the quotient, which is a/b.

 Time Complexity: O(a/b). In the worst-case scenario (where b = 1), the algorithm performs $a$ subtractions. 
 Therefore, the worst-case time complexity is O(a) (linear with respect to the dividend).
 Space Complexity: O(a/b)Since this is a recursive algorithm, each function call adds a frame to the call stack. 
 The depth of the stack is equal to the number of recursive calls, which is  [a / b] 
 In the worst case (b=1), the space complexity is O(a).
*/
 Question 2:

 #include <stdio.h>
#include <stdlib.h>

#define MAX 100

// --- Structure Definitions ---
typedef struct {
    int data;
    int priority; // possible values: [0 .. 5], 0 is highest priority
} Element;

typedef struct {
    int size;
    Element data[MAX];
} Queue;

// --- Function Prototypes ---
void init(Queue *q);
void enqueue(Queue *q, int val, int prio);
Element dequeue(Queue *q);
void display(Queue *q);

// --- Main Testing Function ---
int main() {
    Queue q;

    // 1. Initialize and pre-fill with 6 elements
    printf("--- Initializing Queue ---\n");
    init(&q);
    display(&q);

    // 2. Test Enqueue (High Priority)
    printf("\n--- Enqueue (Data: 10, Priority: 0) ---\n");
    enqueue(&q, 10, 0); // Should go to the very front
    display(&q);

    // 3. Test Enqueue (Low Priority)
    printf("\n--- Enqueue (Data: 99, Priority: 5) ---\n");
    enqueue(&q, 99, 5); // Should go to the back
    display(&q);

    // 4. Test Dequeue (Should remove Priority 0)
    printf("\n--- Dequeue Operation ---\n");
    Element e = dequeue(&q);
    if (e.priority != -1) {
        printf("Dequeued Element -> Data: %d | Priority: %d\n", e.data, e.priority);
    }
    display(&q);

    return 0;
}

// --- Function Implementations ---

/**
 * Adds an element to the queue while maintaining priority order.
 * Lower priority number = Higher importance.
 */
void enqueue(Queue *q, int val, int prio) {
    if (q->size >= MAX) {
        printf("Queue Overflow! Cannot add element.\n");
        return;
    }

    // Validate priority range [0..5]
    if (prio < 0 || prio > 5) {
        printf("Invalid priority! Must be between 0 and 5.\n");
        return;
    }

    // Find correct position and shift elements to the right
    // We start from the end of the array
    int i = q->size - 1;

    // While we haven't reached the start AND the current element has 
    // lower priority (higher number) than the new one:
    while (i >= 0 && q->data[i].priority > prio) {
        q->data[i + 1] = q->data[i]; // Shift right
        i--;
    }

    // Insert the new element
    q->data[i + 1].data = val;
    q->data[i + 1].priority = prio;
    q->size++;
}

/**
 * Initializes the queue and populates it with 6 initial elements.
 */
void init(Queue *q) {
    q->size = 0; // Reset size
    
    // Add 6 elements with mixed priorities to demonstrate sorting
    // Note: The order we add them doesn't matter; enqueue will sort them.
    enqueue(q, 30, 1);
    enqueue(q, 25, 3);
    enqueue(q, 100, 5); // Lowest priority
    enqueue(q, 5, 0);   // Highest priority
    enqueue(q, 42, 2);
    enqueue(q, 77, 4);
}

/**
 * Removes and returns the element at the front (highest priority).
 */
Element dequeue(Queue *q) {
    Element removedElement;
    
    if (q->size <= 0) {
        printf("Queue Underflow! Queue is empty.\n");
        // Return a dummy element to indicate failure
        removedElement.data = -1;
        removedElement.priority = -1;
        return removedElement;
    }

    // Get the front element
    removedElement = q->data[0];

    // Shift all remaining elements to the left
    for (int i = 0; i < q->size - 1; i++) {
        q->data[i] = q->data[i + 1];
    }

    q->size--;
    return removedElement;
}

/**
 * Helper function to print the current state of the queue.
 */
void display(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty.\n");
        return;
    }
    
    printf("Queue Status (Size: %d):\n", q->size);
    for (int i = 0; i < q->size; i++) {
        printf("  [%d] Data: %d | Priority: %d\n", i, q->data[i].data, q->data[i].priority);
    }
}
Cauhoi