#ifndef JUCI_METHODS2_H_
#define JUCI_METHODS2_H_

#include <gtkmm.h>
#include <vector>
#include <string>
#include "boost/filesystem.hpp"
#include "source.h"

class Methods {
  class ListViewText : public Gtk::TreeView {
    class ColumnRecord : public Gtk::TreeModel::ColumnRecord {
    public:
      ColumnRecord() {
        add(text);
      }
      Gtk::TreeModelColumn<std::string> text;
    };
  public:
    bool use_markup;
    ListViewText(bool use_markup);
    void append(const std::string& value);
    void clear();
  private:
    Glib::RefPtr<Gtk::ListStore> list_store;
    ColumnRecord column_record;
    Gtk::CellRendererText cell_renderer;
  };
  
  class SearchEntry : public Gtk::Entry {
  public:
    SearchEntry() : Gtk::Entry() {}
    bool on_key_press_event(GdkEventKey *event) override { return Gtk::Entry::on_key_press_event(event); };
  };
  
public:
  Methods(Gtk::TextView *text_view, Glib::RefPtr<Gtk::TextBuffer::Mark> start_mark, bool show_search_entry, bool use_markup);
  virtual ~Methods();
  void add_row(const std::string& row);
  void set_cursor_at_last_row();
  void show();
  void hide();
  
  bool is_visible() {return window.is_visible();}
  void get_position(int &root_x, int &root_y) {window.get_position(root_x, root_y);}
  
  std::function<void()> on_hide;
  std::function<void(const std::string& selected, bool hide_window)> on_select;
  std::function<void(const std::string &selected)> on_changed;
  Glib::RefPtr<Gtk::TextBuffer::Mark> start_mark;
  
protected:
  void cursor_changed();
  
  Gtk::TextView *text_view;
  Gtk::Window window;
  Gtk::Box vbox;
  Gtk::ScrolledWindow scrolled_window;
  ListViewText list_view_text;
  SearchEntry search_entry;
  bool show_search_entry;
  
  std::string last_row;
};

#endif  // JUCI_METHODS2_H_