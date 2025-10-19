#include "list.h"
#include <stdlib.h>
// TODO: Include any necessary header files here

/**
 * returns head of the linked list.
 * 
 * @param head pointer to the first node of the linked list.
 * @return the head of the linked list. If the list is empty, returns NULL.
 */
struct ll_node *ll_head(struct ll_node *head) {
    return head;
}

/**
 * returns the tail of the linked list.
 * If the list is empty, returns NULL.
 */
struct ll_node *ll_tail(struct ll_node *head) {
    if (head == NULL) return NULL;

    struct ll_node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next; 
    }
    return cur;
}

/**
 * returns the number of elements in the linked list.
 * returns 0 if the list is empty.
 */
int ll_size(struct ll_node *head) {
    int count = 0;
    for (struct ll_node *cur = head; cur != NULL; cur = cur->next) {
        count++;
    }
    return count;
}

/**
 * searches through the linked list for the first node containing `value`.
 * returns a pointer to that node if found, or NULL if not found.
 */
struct ll_node *ll_find(struct ll_node *head, int value) {
    for (struct ll_node *cur = head; cur != NULL; cur = cur->next) {
        if (cur->data == value) {
            return cur;
        }
    }
    return NULL;
}


/**
 * converts the linked list into a dynamically allocated array.
 * returns NULL if the list is empty.
 */
int *ll_toarray(struct ll_node *head) {
    if (head == NULL) return NULL;

    int size = ll_size(head);
    int *arr = malloc(sizeof(int) * size);
    if (arr == NULL) return NULL; 

    struct ll_node *cur = head;
    for (int i = 0; i < size; i++) {
        arr[i] = cur->data;
        cur = cur->next;
    }

    return arr;
}


/**
 * creates a new linked list node with the given data.
 * returns a pointer to the new node, or NULL if malloc fails.
 */
struct ll_node *ll_create(int data) {
    struct ll_node *new_node = malloc(sizeof(struct ll_node));
    if (new_node == NULL) return NULL;

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/**
 * frees all nodes in the linked list.
 * safe to call on an empty list.
 */
void ll_destroy(struct ll_node *head) {
    struct ll_node *cur = head;
    while (cur != NULL) {
        struct ll_node *next = cur->next;
        free(cur);
        cur = next;
    }
}

/**
 * appends a new node with the given data to the tail of the list.
 * does nothing if the list is empty.
 */
void ll_append(struct ll_node *head, int data) {
    if (head == NULL) return;

    struct ll_node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next; 
    }

    struct ll_node *new_node = ll_create(data);
    if (new_node == NULL) return; 
    cur->next = new_node;
}

/**
 * creates a linked list from an array of integers.
 * returns the head of the list, or NULL if the array is empty / invalid.
 */
struct ll_node *ll_fromarray(int* data, int len) {
    if (data == NULL || len <= 0) return NULL;

    struct ll_node *head = ll_create(data[0]);
    if (head == NULL) return NULL;

    struct ll_node *tail = head;

    for (int i = 1; i < len; i++) {
        struct ll_node *new_node = ll_create(data[i]);
        if (new_node == NULL) {
            ll_destroy(head); // clean up if malloc fails
            return NULL;
        }
        tail->next = new_node;
        tail = new_node;
    }

    return head;
}


/**
 * removes the first node that contains `value` from the linked list.
 * frees that node and returns the head of the list.
 * if the value isn't found, returns the original head.
 */
struct ll_node *ll_remove(struct ll_node *head, int value) {
    if (head == NULL) return NULL;

    // case 1: the head itself needs to be removed
    if (head->data == value) {
        struct ll_node *new_head = head->next;
        free(head);
        return new_head;
    }

    // case 2: search for node in the rest of the list
    struct ll_node *cur = head;
    while (cur->next != NULL && cur->next->data != value) {
        cur = cur->next;
    }

    if (cur->next != NULL) {
        struct ll_node *to_delete = cur->next;
        cur->next = to_delete->next;
        free(to_delete);
    }

    return head;
}

