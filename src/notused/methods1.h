#ifndef JUCI_METHODS_H_
#define JUCI_METHODS_H_

#include <gtkmm.h>
#include <vector>
#include <string>
#include "boost/filesystem.hpp"
#include "source.h"

class Methods : public Gtk::ListViewText {
  
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

  class MethodData {
  public:
    Gtk::TreeModel::Row row;
    Glib::RefPtr<Gio::FileMonitor> monitor;
    std::shared_ptr<sigc::connection> connection;
  };

  class TreeStore : public Gtk::TreeStore {
  protected:
    TreeStore() {}

    bool row_drop_possible_vfunc(const Gtk::TreeModel::Path &path, const Gtk::SelectionData &selection_data) const override;
    bool drag_data_received_vfunc(const TreeModel::Path &path, const Gtk::SelectionData &selection_data) override;
    bool drag_data_delete_vfunc (const Gtk::TreeModel::Path &path) override;

  public:
    class ColumnRecord : public Gtk::TreeModel::ColumnRecord {
    public:
      ColumnRecord() {
        add(id);
        add(name);
        add(markup);
        add(path);
        add(type);
      }
      Gtk::TreeModelColumn<std::string> id;
      Gtk::TreeModelColumn<std::string> name;
      Gtk::TreeModelColumn<Glib::ustring> markup;
      Gtk::TreeModelColumn<boost::filesystem::path> path;
      Gtk::TreeModelColumn<PathType> type;
    };

    static Glib::RefPtr<TreeStore> create() {return Glib::RefPtr<TreeStore>(new TreeStore());}
  };

  Methods();

  public:
    static Methods &get() {
      static Methods singleton;
      return singleton;
    }
    ~Methods();
    
    void update(Source::View *view);
    
private:
  Gtk::CellRendererText cell_renderer;
  Glib::RefPtr<Gtk::ListStore> list_store;
  
  ListViewText list_view_text;
};
#endif  // JUCI_METHODS_H_
