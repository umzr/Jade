#include <string.h>

#include "../button_events.h"
#include "../jade_assert.h"
#include "../ui.h"

// QR frame guides around the central part of the frame (100x100px)
#define GUIDE_CORNERS_ICON_WIDTH 104
#define GUIDE_CORNERS_ICON_HEIGHT 104
static char qr_frame_guide_icon_data[]
    = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFC\xFF"
      "\x03\x00\x00\x00\x00\x00\x00\x00\xC0\xFF\x3F\xFC\xFF\x01\x00\x00\x00\x00\x00\x00\x00\x80\xFF\x3F\x0C\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x04\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x0C"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\xFC\xFF\x01\x00\x00\x00\x00\x00\x00\x00\x80\xFF\x3F\xFC\xFF\x03"
      "\x00\x00\x00\x00\x00\x00\x00\xC0\xFF\x3F\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00";

static Icon icon_qr_frame_guide = {
    .width = GUIDE_CORNERS_ICON_WIDTH, .height = GUIDE_CORNERS_ICON_HEIGHT, .data = (uint32_t*)qr_frame_guide_icon_data
};

gui_activity_t* make_camera_activity(gui_view_node_t** image_node, gui_view_node_t** label_node,
    const bool show_click_btn, const bool show_qr_frame_guide, progress_bar_t* progress_bar, const bool show_help_btn)
{
    // progress bar is optional
    JADE_INIT_OUT_PPTR(image_node);
    JADE_INIT_OUT_PPTR(label_node);

    gui_activity_t* const act = gui_make_activity();

    gui_view_node_t* hsplit;
    gui_make_hsplit(&hsplit, GUI_SPLIT_RELATIVE, 2, 50, 50);
    gui_set_parent(hsplit, act->root_node);

    // LHS
    gui_view_node_t* vsplit;
    if (show_click_btn && progress_bar) {
        gui_make_vsplit(&vsplit, GUI_SPLIT_RELATIVE, 4, 20, 30, 25, 25);
    } else if (progress_bar || show_click_btn) {
        gui_make_vsplit(&vsplit, GUI_SPLIT_RELATIVE, 3, 20, 55, 25);
    } else {
        gui_make_vsplit(&vsplit, GUI_SPLIT_RELATIVE, 2, 20, 80);
    }
    gui_set_parent(vsplit, hsplit);

    // first row, header, back button
    btn_data_t hdrbtns[]
        = { { .txt = "=", .font = JADE_SYMBOLS_16x16_FONT, .ev_id = BTN_CAMERA_EXIT, .borders = GUI_BORDER_ALL },
              { .txt = NULL, .font = GUI_DEFAULT_FONT, .ev_id = GUI_BUTTON_EVENT_NONE },
              { .txt = "?", .font = GUI_TITLE_FONT, .ev_id = BTN_CAMERA_HELP, .borders = GUI_BORDER_ALL } };

    // Remove help button if not required
    if (!show_help_btn) {
        hdrbtns[2].txt = NULL;
        hdrbtns[2].ev_id = GUI_BUTTON_EVENT_NONE;
    }
    add_buttons(vsplit, UI_ROW, hdrbtns, 3);

    // second row, message
    gui_view_node_t* fill;
    gui_make_fill(&fill, TFT_BLACK);
    gui_set_parent(fill, vsplit);

    gui_make_text(label_node, "Initializing\nthe camera", TFT_WHITE);
    gui_set_parent(*label_node, fill);
    gui_set_padding(*label_node, GUI_MARGIN_ALL_DIFFERENT, 12, 2, 0, 4);
    gui_set_align(*label_node, GUI_ALIGN_LEFT, GUI_ALIGN_TOP);

    // Any progress bar, if applicable
    if (progress_bar) {
        make_progress_bar(vsplit, progress_bar);
    }

    // buttons
    if (show_click_btn) {
        // A 'click' button
        btn_data_t ftrbtn = { .txt = "S", .font = VARIOUS_SYMBOLS_FONT, .ev_id = BTN_CAMERA_CLICK };
        add_buttons(vsplit, UI_ROW, &ftrbtn, 1);
    }

    // RHS
    gui_make_picture(image_node, NULL);
    gui_set_parent(*image_node, hsplit);
    gui_set_align(*image_node, GUI_ALIGN_CENTER, GUI_ALIGN_MIDDLE);

    // Show QR frame guides if required
    if (show_qr_frame_guide) {
        JADE_ASSERT(sizeof(qr_frame_guide_icon_data) == (GUIDE_CORNERS_ICON_WIDTH * GUIDE_CORNERS_ICON_HEIGHT / 8) + 1);
        gui_view_node_t* qr_frame_guide;
        gui_make_icon(&qr_frame_guide, &icon_qr_frame_guide, TFT_WHITE, NULL);
        gui_set_align(qr_frame_guide, GUI_ALIGN_CENTER, GUI_ALIGN_MIDDLE);
        gui_set_parent(qr_frame_guide, *image_node);
    }

    return act;
}
