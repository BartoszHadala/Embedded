#include <stdio.h>
#include "event_manager.h"

#define MAX_NUMBER_OF_EVENTS 10

static Event * events[MAX_NUMBER_OF_EVENTS];

void EVENT_MANAGER_INIT(void) {
    for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
        events[i] = NULL;
    }
}

bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
    if (event == NULL || onEvent == NULL) {
        return 0;
    } else {
        for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
            if (events[i] == NULL) {
                events[i] = event;
                events[i]->isScheduled = false;
                events[i]->scheduledTime = 0;
                events[i]->interval = 0;
                events[i]->onEvent = onEvent;
                events[i]->context = context;
                return true;
            } 
            
        }
    }
    return false;
}

void EVENT_MANAGER_UnregisterEvent(Event* event) {
    if (event == NULL) {
        return;
    } else {
        for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
            if (events[i] == event) {
                events[i] = NULL;
            }
        }
    }
}

bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time, uint64_t interval) {
    if (event == NULL || time <= 0) {
        return false;
    } else {
        for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
            if (events[i] == event) {
                events[i]->scheduledTime = time;
                events[i]->interval = interval;
                events[i]->isScheduled = true;
                return true;
            }
        }
    }
    return false;
}

void EVENT_MANAGER_Process(uint64_t currentTime) {
    if (currentTime <= 0) {
        return;
    }
    for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
        if (events[i] != NULL && events[i]->isScheduled) {
            if(events[i]->scheduledTime <= currentTime) {
                events[i]->onEvent(events[i], events[i]->scheduledTime, events[i]->context);
                if (events[i]->interval > 0) {
                    events[i]->scheduledTime += events[i]->interval;
                } else {
                    events[i]->isScheduled = false;
                }
            }
        }
    }
}
