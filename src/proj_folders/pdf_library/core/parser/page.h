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

#ifndef PDF_LIB_CORE_PARSER_PAGE_H
#define PDF_LIB_CORE_PARSER_PAGE_H

namespace pdf_lib
{
  namespace core
  {
    template<>
    class _parser<PAGE, PAGE> :
      public _parser<BASE, PAGE>
    {
    public:
      _parser(core::object<PAGE> & page) : 
	_parser<BASE, PAGE>(page) 
      {}
      
      virtual void process_page() = 0;
    };
  //*/
  }
  
}

#endif
