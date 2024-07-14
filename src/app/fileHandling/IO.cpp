#include<iostream>
#include "IO.hpp"
#include<fstream>

using namespace std;

IO::IO(const std::string &filepath){
  file_stream.open(filepath,ios::in|ios::out|ios::binary);
  if(!file_stream.is_open()){
    cout<<"Unable to open the file: "<<filepath<<endl;
  }
}

fstream IO::getFileStream(){
  return move(file_stream);
}

IO::~IO(){
  if(file_stream.is_open()){
    file_stream.close();
  }
}

