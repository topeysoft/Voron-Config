// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: Knomi2

#include "../ui.h"

void ui_ScreenDialog_screen_init(void)
{
    ui_ScreenDialog = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenDialog, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenDialog, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenDialog, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btn_dialog_cancel = lv_imgbtn_create(ui_ScreenDialog);
    lv_imgbtn_set_src(ui_btn_dialog_cancel, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_cancel_png, NULL);
    lv_obj_set_height(ui_btn_dialog_cancel, 64);
    lv_obj_set_width(ui_btn_dialog_cancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_btn_dialog_cancel, 138);
    lv_obj_set_y(ui_btn_dialog_cancel, 148);

    ui_btn_dialog_ok = lv_imgbtn_create(ui_ScreenDialog);
    lv_imgbtn_set_src(ui_btn_dialog_ok, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_dialog_png, NULL);
    lv_obj_set_width(ui_btn_dialog_ok, 56);
    lv_obj_set_height(ui_btn_dialog_ok, 56);
    lv_obj_set_x(ui_btn_dialog_ok, 46);
    lv_obj_set_y(ui_btn_dialog_ok, 148);

    ui_img_dialog_ok = lv_img_create(ui_btn_dialog_ok);
    lv_img_set_src(ui_img_dialog_ok, &ui_img_img_ok_png);
    lv_obj_set_width(ui_img_dialog_ok, 24);
    lv_obj_set_height(ui_img_dialog_ok, 17);
    lv_obj_set_align(ui_img_dialog_ok, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_dialog_ok, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_img_dialog_ok, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_label_dialog = lv_label_create(ui_ScreenDialog);
    lv_obj_set_width(ui_label_dialog, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label_dialog, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_label_dialog, 0);
    lv_obj_set_y(ui_label_dialog, 74);
    lv_obj_set_align(ui_label_dialog, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_label_dialog, "Start Printing?");
    lv_obj_set_style_text_font(ui_label_dialog, &ui_font_InterSemiBold24, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_btn_dialog_cancel, ui_event_btn_dialog_cancel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_dialog_ok, ui_event_btn_dialog_ok, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenDialog, ui_event_ScreenDialog, LV_EVENT_ALL, NULL);

}
