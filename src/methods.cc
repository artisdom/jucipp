#include "methods.h"
#include "source.h"
#include "notebook.h"

Methods::Methods(bool use_markup) : Gtk::TreeView(), use_markup(use_markup) {
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
  
  on_select = [this](const std::string& selected, bool hide_window) {
    if(auto view=Notebook::get().get_current_view()) {
      auto offset=rows.at(selected);
      view->get_buffer()->place_cursor(view->get_buffer()->get_iter_at_line_index(offset.line, offset.index));
      view->scroll_to(view->get_buffer()->get_insert(), 0.0, 1.0, 0.5);
      view->hide_tooltips();
    }
  };
  
  auto activate=[this](){
    auto it=this->get_selection()->get_selected();
    if(on_select && it) {
      std::string row;
      it->get_value(0, row);
      on_select(row, true);
    }
  };
  
  this->signal_row_activated().connect([this, activate](const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*) {
    activate();
  });
}

void Methods::append(const std::string& value) {
  auto new_row=list_store->append();
  new_row->set_value(column_record.text, value);
}

void Methods::clear() {
  list_store->clear();
  rows.clear();
}

void Methods::update() {
  clear();

  Source::View *view = Notebook::get().get_current_view();
  if(view->get_methods) {
    auto methods=view->get_methods();
    if(!methods.empty()) {
    
      for(auto &method: methods) {
        rows[method.second]=method.first;
        append(method.second);
      }
    }
  }
}

Methods::~Methods()
{}
