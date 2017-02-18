#ifndef JUCI_METHODS_H_
#define JUCI_METHODS_H_

#include <gtkmm.h>
#include <vector>
#include <string>
#include "boost/filesystem.hpp"
#include "source.h"

class Methods : public Gtk::TreeView {
  class ColumnRecord : public Gtk::TreeModel::ColumnRecord {
  public:
    ColumnRecord() {
      add(text);
    }
    Gtk::TreeModelColumn<std::string> text;
  };
public:
  bool use_markup;
  Methods(bool use_markup);

  static Methods &get() {
    static Methods singleton(true);
    return singleton;
  }
  ~Methods();

  void append(const std::string& value);
  void clear();
  
  void update();
  
  
  std::function<void()> on_hide;
  std::function<void(const std::string& selected, bool hide_window)> on_select;
  std::function<void(const std::string &selected)> on_changed;
  
  void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
  {}
  
  /// This is a default handler for the signal signal_test_expand_row().
  bool on_test_expand_row(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path)
  { return true; }
  
  /// This is a default handler for the signal signal_test_collapse_row().
  bool on_test_collapse_row(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path)
  { return true; }
  
  /// This is a default handler for the signal signal_row_expanded().
  void on_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path)
  {}
  
  /// This is a default handler for the signal signal_row_collapsed().
  void on_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path)
  {}
  
  /// This is a default handler for the signal signal_cursor_changed().
  void on_cursor_changed()
  {}
  
  /// This is a default handler for the signal signal_columns_changed().
  void on_columns_changed()
  {}
  
private:
  Glib::RefPtr<Gtk::ListStore> list_store;
  ColumnRecord column_record;
  Gtk::CellRendererText cell_renderer;
  std::unordered_map<std::string, Source::Offset> rows;
};

#endif  // JUCI_METHODS_H_
