#include "../boilerplate.h"
#include <lib/toolbox/value_index.h>

enum SettingsIndex {
    SettingsIndexValue1,
    SettingsIndexValue2,
    SettingsIndexValue3,
    SettingsIndexValue4,
};

const char* const alert_text[4] = {
    "OFF",
    "LED",
    "SOUND",
    "BOTH",
};
const uint32_t alert_value[4] = {
    ContactlessHIDAlertOff,
    ContactlessHIDAlertLED,
    ContactlessHIDAlertSound,
    ContactlessHIDAlertBoth,
};

const char* const append_enter_text[2] = {
    "OFF",
    "ON",
};

const uint32_t append_enter_value[2] = {
    ContactlessHIDAppendEnterOff,
    ContactlessHIDAppendEnterOn,
};

static void boilerplate_scene_settings_set_alert(VariableItem* item) {
    Boilerplate* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, alert_text[index]);
    app->alert = alert_value[index];
}

static void boilerplate_scene_settings_set_append_enter(VariableItem* item) {
    Boilerplate* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, append_enter_text[index]);
    app->append_enter = append_enter_value[index];
}

void boilerplate_scene_settings_on_enter(void* context) {
    Boilerplate* app = context;
    VariableItem* item;
    uint8_t value_index;

    // Alert Settings
    item = variable_item_list_add(
        app->variable_item_list, "Alert:", 4, boilerplate_scene_settings_set_alert, app);
    value_index = value_index_uint32(app->alert, alert_value, 4);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, alert_text[value_index]);

    // Append Enter
    item = variable_item_list_add(
        app->variable_item_list,
        "Append Enter",
        2,
        boilerplate_scene_settings_set_append_enter,
        app);
    value_index = value_index_uint32(app->append_enter, append_enter_value, 2);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, append_enter_text[value_index]);

    view_dispatcher_switch_to_view(app->view_dispatcher, BoilerplateViewIdSettings);
}

bool boilerplate_scene_settings_on_event(void* context, SceneManagerEvent event) {
    Boilerplate* app = context;
    UNUSED(app);
    bool consumed = false;
    if(event.type == SceneManagerEventTypeCustom) {
    }
    return consumed;
}

void boilerplate_scene_settings_on_exit(void* context) {
    Boilerplate* app = context;
    variable_item_list_set_selected_item(app->variable_item_list, 0);
    variable_item_list_reset(app->variable_item_list);
}