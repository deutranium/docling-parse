//-*-C++-*-

/***********************************************************
IBM Confidential
OCO Source Materials
IBM Research Zurich Smart Annotator Licensed Internal Code
(C) Copyright IBM Corp. 2017

Authors: Peter W. J. Staar, Michele Dolfi, Christoph Auer,
Matthieu Mottet 
Email: {taa, dol, cau, ttt}@zurich.ibm.com
Date: 18/08/2017
**********************************************************/

#ifndef PDF_LIB_CORE_OBJECT_FONT_FILE_1_H
#define PDF_LIB_CORE_OBJECT_FONT_FILE_1_H

#include "logging_library.h"

namespace pdf_lib
{
  namespace core
  {

    class fontfile1
    {      
    public:
      
      typedef std::string                         key_type;
      typedef std::pair<std::string, std::string> val_type;
      
      typedef std::pair<key_type, val_type> elm_type;
      
    public:
      
      fontfile1();
      ~fontfile1();
      
      template<typename ss_type>
      void print(ss_type& ss);
    };

    fontfile1::fontfile1()
    {}
    
    fontfile1::~fontfile1()
    {}
    
    template<typename ss_type>
    void fontfile1::print(ss_type& ss)
    {
      
    }
    
  }

}

#endif
