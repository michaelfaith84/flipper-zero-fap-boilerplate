#pragma once

#include <gui/view.h>
#include "../helpers/boilerplate_custom_event.h"

typedef struct ContactlessHIDReaderscreen ContactlessHIDReaderscreen;

typedef void (*ContactlessHIDReaderscreenCallback)(BoilerplateCustomEvent event, void* context);

void contactlesshid_readerscreen_set_callback(
    ContactlessHIDReaderscreen* contactlesshid_readerscreen,
    ContactlessHIDReaderscreenCallback callback,
    void* context);

View* contactlesshid_readerscreen_get_view(ContactlessHIDReaderscreen* contactlesshid_static);

ContactlessHIDReaderscreen* contactlesshid_readerscreen_alloc();

void contactlesshid_readerscreen_free(ContactlessHIDReaderscreen* contactlesshid_static);