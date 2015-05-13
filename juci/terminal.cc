#include "terminal.h"
#include <iostream>
#include <thread>
// #include <pstream.h>
// #include <string>


Terminal::View::View(){
  scrolledwindow_.add(textview_);
  scrolledwindow_.set_size_request(-1,150);
  view_.add(scrolledwindow_);
  textview_.set_editable(false);
}


Terminal::Controller::Controller() {
  folder_command_ = "";
}

void Terminal::Controller::SetFolderCommand( boost::filesystem::path
					     CMake_path) {
  path_ = CMake_path.string();
  folder_command_ = "cd "+ path_ + "; ";
}

void Terminal::Controller::Compile(){
  Terminal().get_buffer()->set_text("");
  ExecuteCommand("cmake .", "r");
  if (ExistInConsole(cmake_sucsess)){
    ExecuteCommand("make", "r");
  } 
}

void Terminal::Controller::Run(std::string executable) {
  PrintMessage("juCi++ execute: " + executable + "\n");
  ExecuteCommand("./"+executable, "w");
}

void Terminal::Controller::PrintMessage(std::string message){
  Terminal().get_buffer()->
    insert(Terminal().get_buffer()-> end(),"> "+message);
}


bool Terminal::Controller::ExistInConsole(std::string string) {
  double pos = Terminal().get_buffer()->
    get_text().find(string);
  if (pos == std::string::npos) return false;
  return true;
}

void Terminal::Controller::ExecuteCommand(std::string command, std::string mode) {

  std::cout << "EXECUTE COMMAND: "<< command << std::endl;
  if(mode == "w"){
    command =  path_ + " " +command + " > some_file.txt";
    system(command.c_str());
  }else{
    
    FILE* p = popen(command.c_str(), mode.c_str());
    command = folder_command_+command;
    if (p == NULL) {
      PrintMessage("juCi++ ERROR: Failed to run command" + command + "\n");
    }else {
      char buffer[1028];
      while (fgets(buffer, 1028, p) != NULL) {
	PrintMessage(buffer);
      }
      pclose(p); 
    }
  }



  // // run a process and create a streambuf that reads its stdout and stderr
  //  redi::ipstream proc(command, redi::pstreams::pstderr);
  //  std::string line;
  //  // read child's stdout
  //  while (std::getline(proc.out(), line))
  //    PrintMessage(line+ "\n");

  //  // read child's stderr
  //  while (std::getline(proc.err(), line))
  //    PrintMessage(line+ "\n");

}
