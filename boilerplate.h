#pragma once

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include <dialogs/dialogs.h>
#include <notification/notification_messages.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/button_menu.h>
#include <gui/modules/dialog_ex.h>
#include "scenes/boilerplate_scene.h"
#include "views/boilerplate_startscreen.h"
#include "views/contactlesshid_readerscreen.h"
#include <gui/modules/variable_item_list.h>
#include "helpers/boilerplate_storage.h"
#include "boilerplate_icons.h"

#define TAG "ContactlessHID"

#define SUBGHZ_APP_EXTENSION ".sub"
#define SUBGHZ_APP_FOLDER ANY_PATH("subghz")
#define CONTACTLESSHID_VERSION ".1"

typedef struct {
    Gui* gui;
    NotificationApp* notification;
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;
    VariableItemList* variable_item_list;
    BoilerplateStartscreen* boilerplate_startscreen;
    ContactlessHIDReaderscreen* contactlesshid_readerscreen;
    DialogsApp* dialogs; // File Browser
    FuriString* file_path; // File Browser
    uint32_t alert;
    uint32_t append_enter;
    int read_mode;
    char* const read_mode_text;
    ButtonMenu* button_menu; // Button Menu
} Boilerplate;

typedef enum {
    BoilerplateViewIdStartscreen,
    ContactlessHIDViewIdReaderscreen,
    BoilerplateViewIdSettings,
} BoilerplateViewId;

typedef enum {
    ContactlessHIDAlertOff,
    ContactlessHIDAlertLED,
    ContactlessHIDAlertSound,
    ContactlessHIDAlertBoth,
} BoilerplateAlertState;

typedef enum {
    ContactlessHIDAppendEnterOff,
    ContactlessHIDAppendEnterOn,
} BoilerplateAppendEnterState;

typedef enum {
    ContactlessHIDRFID = 1,
    ContactlessHIDNFC
} ContactlessHIDMode;

