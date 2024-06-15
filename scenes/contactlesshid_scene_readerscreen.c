#include "../boilerplate.h"
#include "../helpers/boilerplate_custom_event.h"
#include "../views/contactlesshid_readerscreen.h"

void contactlesshid_scene_readerscreen_callback(BoilerplateCustomEvent event, void* context) {
    furi_assert(context);
    Boilerplate* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, event);
}

void contactlesshid_scene_readerscreen_on_enter(void* context) {
    furi_assert(context);
    Boilerplate* app = context;
    contactlesshid_readerscreen_set_callback(
        app->contactlesshid_readerscreen, contactlesshid_scene_readerscreen_callback, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, ContactlessHIDViewIdReaderscreen);
}

bool contactlesshid_scene_readerscreen_on_event(void* context, SceneManagerEvent event) {
    Boilerplate* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
        case ContactlessHIDCustomEventReaderscreenBack:
            if(!scene_manager_search_and_switch_to_previous_scene(
                   app->scene_manager, BoilerplateSceneStartscreen)) {
                scene_manager_stop(app->scene_manager);
                view_dispatcher_stop(app->view_dispatcher);
            }
            consumed = true;
            break;
        }
    }

    return consumed;
}

void contactlesshid_scene_readerscreen_on_exit(void* context) {
    Boilerplate* app = context;
    UNUSED(app);
}