// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: Knomi2

#include "../ui.h"

// COMPONENT Label2

lv_obj_t * ui_Label2_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Label2;
    cui_Label2 = lv_label_create(comp_parent);
    lv_obj_set_width(cui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_Label2, 0);
    lv_obj_set_y(cui_Label2, -29);
    lv_obj_set_align(cui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(cui_Label2, "180C\n");

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_LABEL2_NUM);
    children[UI_COMP_LABEL2_LABEL2] = cui_Label2;
    lv_obj_add_event_cb(cui_Label2, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Label2, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Label2_create_hook(cui_Label2);
    return cui_Label2;
}
