#include "methods.h"
#include "notebook.h"

Methods::Methods() : Gtk::ListViewText(1) {

  // get_column(0)->set_title("Location");
  // get_column(1)->set_title("Symbol");

  get_column(0)->set_title("Symbol");
  
  
}

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


void Methods::add_row(const std::string& row) {
  list_view_text.append(row);
}

void Methods::update(Source::View *view) {
  
  clear_items();
  
  if(view->get_methods) {
    auto methods=Notebook::get().get_current_view()->get_methods();
    if(!methods.empty()) {
    
      for(auto &method: methods) {
        append(method.second);
      }
    
    }
  }
}

Methods::~Methods() {
  // dispatcher.disconnect();
}
