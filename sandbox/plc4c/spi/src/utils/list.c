/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <plc4c/utils/list.h>

void plc4c_utils_list_create(plc4c_list **list) {
    plc4c_list *new_list = malloc(sizeof(plc4c_list));
    new_list->head = NULL;
    new_list->tail = NULL;
    *list = new_list;
}

size_t plc4c_utils_list_size(plc4c_list* list) {
    if(list->head == NULL) {
        return 0;
    }
    plc4c_list_element *cur_element = list->head;
    int count = 1;
    while(cur_element->next != NULL) {
        count++;
        cur_element = cur_element->next;
    }
    return count;
}

bool plc4c_utils_list_empty(plc4c_list* list) {
    return list->head == NULL;
}

bool plc4c_utils_list_contains(plc4c_list* list, plc4c_list_element* element) {
    if((list == NULL) || (element == NULL)) {
        return false;
    }
    plc4c_list_element *cur_element = list->head;
    do {
        if(cur_element == element) {
            return true;
        }
        cur_element = cur_element->next;
    } while (cur_element != NULL);
    return false;
}

void plc4c_utils_list_insert_head(plc4c_list* list, plc4c_list_element* element) {
    list->head->next = element;
    element->previous = list->head;
    list->head = element;
}

void plc4c_utils_list_insert_head_value(plc4c_list* list, void* value) {
    plc4c_list_element *new_element = malloc(sizeof(plc4c_list_element));
    new_element->value = value;
    new_element->next = NULL;
    plc4c_utils_list_insert_head(list, new_element);
}

void plc4c_utils_list_insert_tail(plc4c_list* list, plc4c_list_element* element) {
    if (list->tail != NULL) {
        list->tail->previous = element;
        element->next = list->tail;
    } else {
        list->head = element;
    }
    list->tail = element;
}

void plc4c_utils_list_insert_tail_value(plc4c_list* list, void* value) {
    plc4c_list_element *new_element = malloc(sizeof(plc4c_list_element));
    new_element->value = value;
    new_element->next = NULL;
    plc4c_utils_list_insert_tail(list, new_element);
}

void plc4c_utils_list_remove(plc4c_list* list, plc4c_list_element* element) {
    // If the list doesn't contain this element, no need to do anything.
    if(!plc4c_utils_list_contains(list, element)) {
        return;
    }

    // Remember the next and previous elements.
    plc4c_list_element* previous_element = element->previous;
    plc4c_list_element* next_element = element->next;

    // Link the previous and next elements (taking the current element out of the list).
    if(previous_element != NULL) {
        previous_element->next = next_element;
    }
    if(next_element != NULL) {
        next_element->previous = previous_element;
    }

    // Update head and tail (if required)
    if(list->head == element) {
        list->head = next_element;
    }
    if(list->tail == element) {
        list->tail = previous_element;
    }

    // Reset the pointers to the neighboring elements.
    element->next = NULL;
    element->previous = NULL;
}

plc4c_list_element *plc4c_utils_list_remove_head(plc4c_list* list) {
    plc4c_list_element *removed_element = list->head;
    list->head = list->head->previous;
    list->head->next = NULL;
    removed_element->previous = NULL;
    return removed_element;
}

plc4c_list_element *plc4c_utils_list_remove_tail(plc4c_list* list) {
    plc4c_list_element *removed_element = list->tail;
    list->tail = list->tail->next;
    list->tail->previous = NULL;
    removed_element->next = NULL;
    return removed_element;
}

plc4c_list_element *plc4c_utils_list_head(plc4c_list *list) {
    return list->head;
}

plc4c_list_element *plc4c_utils_list_tail(plc4c_list *list) {
    return list->tail;
}
