#include "../boilerplate.h"
#include <furi.h>
#include <furi_hal.h>
#include <input/input.h>
#include <gui/elements.h>

struct ContactlessHIDReaderscreen {
    View* view;
    ContactlessHIDReaderscreenCallback callback;
    void* context;
};

//const char* const read_mode_text[2] = {
//    "RFID",
//    "NFC",
//};

typedef struct {
    const char* read_mode_display;
} ContactlessHIDReaderscreenModel;

//static void contactlesshid_scene_readerscreen_mode_display(int mode) {
//    return read_mode_text[mode];
//}

void contactlesshid_readerscreen_set_callback(
    ContactlessHIDReaderscreen* instance,
    ContactlessHIDReaderscreenCallback callback,
    void* context) {
    furi_assert(instance);
    furi_assert(callback);
    instance->callback = callback;
    instance->context = context;
}

void contactlesshid_readerscreen_draw(Canvas* canvas, ContactlessHIDReaderscreenModel* model) {
    UNUSED(model);
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 64, 32, AlignCenter, AlignCenter, model->read_mode_display);
    canvas_set_font(canvas, FontSecondary);
}

static void contactlesshid_readerscreen_model_init(ContactlessHIDReaderscreenModel* const model, const char* read_mode_display) {
    model->read_mode_display = read_mode_display;
}

bool contactlesshid_readerscreen_input(InputEvent* event, void* context) {
    furi_assert(context);
    ContactlessHIDReaderscreen* instance = context;
    if(event->type == InputTypeRelease) {
        switch(event->key) {
        case InputKeyBack:
            with_view_model(
                instance->view,
                ContactlessHIDReaderscreenModel * model,
                {
                    UNUSED(model);
                    instance->callback(ContactlessHIDCustomEventReaderscreenBack, instance->context);
                },
                true);
            break;
        case InputKeyLeft:
        case InputKeyRight:
        case InputKeyOk:
        case InputKeyUp:
        case InputKeyDown:
        case InputKeyMAX:
            break;
        }
    }
    return true;
}

void contactlesshid_readerscreen_exit(void* context) {
    furi_assert(context);
}

ContactlessHIDReaderscreen* contactlesshid_readerscreen_alloc(Boilerplate* app) {
    ContactlessHIDReaderscreen* instance = malloc(sizeof(ContactlessHIDReaderscreen));
    instance->view = view_alloc();
    view_allocate_model(instance->view, ViewModelTypeLocking, sizeof(ContactlessHIDReaderscreenModel));
    view_set_context(instance->view, instance); // furi_assert crashes in events without this
    view_set_draw_callback(instance->view, (ViewDrawCallback)contactlesshid_readerscreen_draw);
    view_set_input_callback(instance->view, contactlesshid_readerscreen_input);
    //view_set_enter_callback(instance->view, boilerplate_startscreen_enter);
    //view_set_exit_callback(instance->view, boilerplate_startscreen_exit);

    with_view_model(
        instance->view,
        ContactlessHIDReaderscreenModel * model,
        { contactlesshid_readerscreen_model_init(model, app->read_mode_text[app->read_mode]);  },
        true);

    return instance;
}

void contactlesshid_readerscreen_free(ContactlessHIDReaderscreen* instance) {
    furi_assert(instance);

    with_view_model(
        instance->view, ContactlessHIDReaderscreenModel * model, { UNUSED(model); }, true);
    view_free(instance->view);
    free(instance);
}

View* contactlesshid_readerscreen_get_view(ContactlessHIDReaderscreen* instance) {
    furi_assert(instance);
    return instance->view;
}
