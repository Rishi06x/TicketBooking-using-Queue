#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Maximum number of tickets available and maximum queue size

typedef struct {
    int front, rear;
    int customers[MAX]; // Queue to store customer IDs
} Queue;

// Function prototypes
void initializeQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int customer);
int dequeue(Queue *q);
void bookTicket(Queue *q, int *availableTickets);

// Initialize the queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
int isFull(Queue *q) {
    return (q->rear == MAX - 1);
}

// Check if the queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1 || q->front > q->rear);
}

// Add a customer to the queue
void enqueue(Queue *q, int customer) {
    if (isFull(q)) {
        printf("Queue is full! No more customers can be added.\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->customers[q->rear] = customer;
    printf("Customer %d added to the queue.\n", customer);
}

// Remove a customer from the queue and return the customer ID
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty! No customers to process.\n");
        return -1;
    }
    int customer = q->customers[q->front];
    q->front++;
    return customer;
}

// Function to book a ticket
void bookTicket(Queue *q, int *availableTickets) {
    if (*availableTickets <= 0) {
        printf("No tickets available!\n");
        return;
    }

    if (!isEmpty(q)) {
        int customer = dequeue(q);
        printf("Processing booking for Customer %d...\n", customer);
        (*availableTickets)--;
        printf("Ticket booked for Customer %d. Tickets remaining: %d\n", customer, *availableTickets);
    } else {
        printf("No customers in queue to process.\n");
    }
}

int main() {
    Queue q;
    int availableTickets = MAX;
    int choice, customerID = 1;

    initializeQueue(&q);

    while (1) {
        printf("\n--- Ticket Booking System ---\n");
        printf("1. Add customer to the queue\n");
        printf("2. Process booking\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!isFull(&q)) {
                    enqueue(&q, customerID++);
                }
                else{
                    printf("Queue is full! No more available tickets.\n");
                }
                break;
            case 2:
                bookTicket(&q, &availableTickets);
                break;
            case 3:
                printf("Exiting the system.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}