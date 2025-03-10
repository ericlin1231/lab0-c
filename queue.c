#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head)
        return NULL;

    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    /* Queue exist check */
    if (!head)
        return;

    /* Empty queue check */
    if (list_empty(head)) {
        free(head);
        return;
    }

    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        list_del(node);
        element_t *container = container_of(node, element_t, list);
        free(container->value);
        free(container);
    }

    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *node = malloc(sizeof(element_t));

    if (!node)
        return false;

    node->value = malloc(strlen(s) * sizeof(char) + 1);

    if (!(node->value)) {
        free(node);
        return false;
    }

    snprintf(node->value, strlen(node->value), "%s", s);
    list_add(&(node->list), head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *node = malloc(sizeof(element_t));

    if (!node)
        return false;

    node->value = malloc(strlen(s) * sizeof(char) + 1);

    if (!(node->value)) {
        free(node);
        return false;
    }

    snprintf(node->value, strlen(node->value), "%s", s);
    list_add_tail(&(node->list), head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *node = container_of(head->next, element_t, list);
    snprintf(sp, bufsize, "%s", node->value);
    list_del(head->next);
    return node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *node = list_last_entry(head, element_t, list);
    snprintf(sp, bufsize, "%s", node->value);
    list_del(head->prev);
    return node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;

    struct list_head *next = head->next, *prev = head->prev;
    for (; (next != prev) && (next->next != prev);
         next = next->next, prev = prev->prev)
        ;

    element_t *node = container_of(prev, element_t, list);
    list_del(prev);
    free(node->value);
    free(node);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || list_empty(head))
        return;

    struct list_head *node = head;
    while ((node->next != head) && (node->next->next != head)) {
        list_move(node->next->next, node);
        node = node->next->next;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        *(uintptr_t *) &node->prev ^= (uintptr_t) node->next;
        *(uintptr_t *) &node->next ^= (uintptr_t) node->prev;
        *(uintptr_t *) &node->prev ^= (uintptr_t) node->next;
    }
    *(uintptr_t *) &head->prev ^= (uintptr_t) head->next;
    *(uintptr_t *) &head->next ^= (uintptr_t) head->prev;
    *(uintptr_t *) &head->prev ^= (uintptr_t) head->next;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
