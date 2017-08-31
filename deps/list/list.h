
//
// list.h
//
// Copyright (c) 2017 JesseChen <lkchan0719@gmail.com>
//

#ifndef _LIST_H__
#define _LIST_H__

#include <stddef.h>

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define LIST_POISON1  ((void *) 0x00010100) 
#define LIST_POISON2  ((void *) 0x00020200)

struct list_head {
    struct list_head *next, *prev;
};

void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static void __list_add(struct list_head *new,
        struct list_head *prev,
        struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void list_add(struct list_head *new, struct list_head *head)
{
  __list_add(new, head, head->next);
}

static void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

#if 0
#define container_of(ptr, type, member) ({                      \
            const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
            (type *)( (char *)__mptr - offsetof(type,member) );})
#endif 

#define container_of(ptr, type, member) \
      ((type *) ((char *) (ptr) - offsetof(type, member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member)              \
    for (pos = list_entry((head)->next, typeof(*pos), member);  \
         &pos->member != (head);    \
         pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_reverse(pos, head, member)          \
    for (pos = list_entry((head)->prev, typeof(*pos), member);  \
        &pos->member != (head);    \
        pos = list_entry(pos->member.prev, typeof(*pos), member))

/**
 *  * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 *   * @pos:    the type * to use as a loop cursor.
 *    * @n:     another type * to use as temporary storage
 *     * @head: the head for your list.
 *      * @member:  the name of the list_struct within the struct.
 *       */
#define list_for_each_entry_safe(pos, n, head, member)          \
    for (pos = list_entry((head)->next, typeof(*pos), member),  \
        n = list_entry(pos->member.next, typeof(*pos), member); \
        &pos->member != (head);                    \
        pos = n, n = list_entry(n->member.next, typeof(*n), member))


#endif 
