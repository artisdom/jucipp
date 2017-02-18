#include "methods2.h"
#include "notebook.h"

Methods::ListViewText::ListViewText(bool use_markup) : Gtk::TreeView(), use_markup(use_markup) {
  list_store = Gtk::ListStore::create(column_record);
  set_model(list_store);
  append_column("", cell_renderer);
  if(use_markup)
    get_column(0)->add_attribute(cell_renderer.property_markup(), column_record.text);
  else
    get_column(0)->add_attribute(cell_renderer.property_text(), column_record.text);
  
  get_selection()->set_mode(Gtk::SelectionMode::SELECTION_BROWSE);
  set_enable_search(true);
  set_headers_visible(false);
  set_hscroll_policy(Gtk::ScrollablePolicy::SCROLL_NATURAL);
  set_activate_on_single_click(true);
  set_hover_selection(false);
  set_rules_hint(true);
}

void Methods::ListViewText::append(const std::string& value) {
  auto new_row=list_store->append();
  new_row->set_value(column_record.text, value);
}

void Methods::ListViewText::clear() {
  unset_model();
  list_store.reset();
}