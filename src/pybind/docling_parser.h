//-*-C++-*-

#ifndef PYBIND_PDF_PARSER_H
#define PYBIND_PDF_PARSER_H

#include <utf8/utf8.h>

#include "include_libs.h"

#include <utils.h>
#include <utils/meta_library.h>
#include <utils/logging_library.h>
#include <utils/string_library.h>
#include <utils/system_library.h>
#include <utils/container_library.h>
#include <utils/IO_library.h>
#include <utils/geometric_objects.h>

#include "pdf_library.h"
#include "pdf_parser.h"

#include "pdf_interface.h"
#include "pdf_interface/parser.h"

#include "pybind/docling_resources.h"

namespace docling
{
  class docling_parser: public docling_resources
  {
  public:

    docling_parser();

    void set_loglevel(int level=0);

    void unload_documents();
    
    nlohmann::json get_raw(std::string path);
    
    nlohmann::json find_cells(std::string path);

    nlohmann::json find_cells_on_page(std::string path, int page);

    nlohmann::json find_cells_from_bytesio(pybind11::object bytes_io);

    nlohmann::json find_cells_from_bytesio_on_page(pybind11::object bytes_io,
						   int page);

  private:

    pdf_lib::interface<pdf_lib::PARSER> interface;
  };

  docling_parser::docling_parser():
    docling_resources(),
    interface()
  {
    //std::string font_data_dir = PDF_DATA_DIR;

    std::string font_data_dir = resource_utils::get_resources_dir(true);

    //logging_lib::info("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
    //<< "using default font-data path : " << font_data_dir;

    //std::cout << __FILE__ << ":" << __LINE__ << "\t"
    //<< "using default font-data path : " << font_data_dir << "\n";

    pdf_lib::core::object<pdf_lib::core::FONT>::initialize(font_data_dir);
  }

  void docling_parser::set_loglevel(int level)
  {
    if(level>3)
      {    
	logging_lib::set_level("pdf-parser", 
			       logging_lib::ERROR   | 
			       logging_lib::WARNING | 
			       logging_lib::INFO    | 
			       logging_lib::SUCCESS);
      }
    else if(level==2)
      {    
	logging_lib::set_level("pdf-parser", 
			       logging_lib::ERROR   | 
			       logging_lib::WARNING | 
			       logging_lib::SUCCESS);
      }
    else if(level==1)
      {    
	logging_lib::set_level("pdf-parser", 
			       logging_lib::ERROR   | 
			       logging_lib::WARNING );
      }
    else if(level==0)
      {
	logging_lib::set_level("pdf-parser", 
			       logging_lib::ERROR);
      }
  }

  void docling_parser::unload_documents()
  {
    interface.unload_documents();
  }
  
  nlohmann::json docling_parser::get_raw(std::string path)
  {
    nlohmann::json data;// = nlohmann::json::parse(result);
    return data;
  }

  nlohmann::json docling_parser::find_cells(std::string path)
  {
    container_lib::container doc_raw;

    // parse the pdf file on path
    if (not interface.parse_pdf_page(path, doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not parse the PDF file";

        nlohmann::json data;
        data["message"] = "could not parse the PDF file";
        return data;
      }
    
    if (not interface.clean_raw_page(doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not clean the raw file";

        nlohmann::json data;
        data["message"] = "could not clean the raw file";
        return data;
      }

    interface.clean_pages(doc_raw);

    // remove font information ...
    for(int pid=0; pid<doc_raw["pages"].get_size(); pid++)
      {
        doc_raw["pages"][pid].erase("fonts");
      }    
    
    IO::writer<IO::JSON_CONTAINER> writer;
    std::string result = writer.to_string(doc_raw);
    
    nlohmann::json data = nlohmann::json::parse(result);
    return data;
  }

  nlohmann::json docling_parser::find_cells_on_page(std::string path, int page)
  {
    container_lib::container doc_raw;

    // parse the pdf file on path
    if (not interface.parse_pdf_page(path, page, doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not parse the PDF file";

        nlohmann::json data;
        data["message"] = "could not parse the PDF file";
        return data;
      }

    // only keep page -> bring it to the first and then resize array
    {
      if(page>0)
	{
	  doc_raw["pages"][0] = doc_raw["pages"][page];
	}
      doc_raw["pages"].resize(1);
    }
    
    if (not interface.clean_raw_page(doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not clean the raw file";

        nlohmann::json data;
        data["message"] = "could not clean the raw file";
        return data;
      }

    interface.clean_pages(doc_raw);

    // remove font information ...
    for(int pid=0; pid<doc_raw["pages"].get_size(); pid++)
      {
	if(doc_raw["pages"][pid].has("fonts"))
	  {
	    doc_raw["pages"][pid].erase("fonts");
	  }
      }
    
    IO::writer<IO::JSON_CONTAINER> writer;
    std::string result = writer.to_string(doc_raw);
    
    nlohmann::json data = nlohmann::json::parse(result);
    return data;
  }
  
  nlohmann::json docling_parser::find_cells_from_bytesio(pybind11::object bytes_io)
  {
    // Check if the object is a BytesIO object
    if (!pybind11::hasattr(bytes_io, "read")) {
      
        throw std::runtime_error("Expected a BytesIO object");
    }

    // Seek to the beginning of the BytesIO stream
    bytes_io.attr("seek")(0);

    // Read the entire content of the BytesIO stream
    pybind11::bytes data = bytes_io.attr("read")();

    // Get a pointer to the data
    std::string data_str = data.cast<std::string>();

    // Do something with the data (in this case, simply print the size)
    //std::cout << "Read " << data_str.size() << " bytes from the BytesIO stream" << std::endl;

    //std::string path;
    
    container_lib::container doc_raw;
    
    // parse the pdf file on path
    if (not interface.parse_pdf_page(data_str.c_str(), data_str.size(), doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not parse the PDF file";

        nlohmann::json data;
        data["message"] = "could not parse the PDF file";
        return data;
      }
    
    if (not interface.clean_raw_page(doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not clean the raw file";

        nlohmann::json data;
        data["message"] = "could not clean the raw file";
        return data;
      }

    interface.clean_pages(doc_raw);

    // remove font information ...
    for(int pid=0; pid<doc_raw["pages"].get_size(); pid++)
      {
        doc_raw["pages"][pid].erase("fonts");
      }    
    
    IO::writer<IO::JSON_CONTAINER> writer;
    std::string result = writer.to_string(doc_raw);    

    nlohmann::json output = nlohmann::json::parse(result);
    return output;
  }

  nlohmann::json docling_parser::find_cells_from_bytesio_on_page(pybind11::object bytes_io, int page)
  {
    // Check if the object is a BytesIO object
    if (!pybind11::hasattr(bytes_io, "read")) {
      
        throw std::runtime_error("Expected a BytesIO object");
    }

    // Seek to the beginning of the BytesIO stream
    bytes_io.attr("seek")(0);

    // Read the entire content of the BytesIO stream
    pybind11::bytes data = bytes_io.attr("read")();

    // Get a pointer to the data
    std::string data_str = data.cast<std::string>();

    // Do something with the data (in this case, simply print the size)
    //std::cout << "Read " << data_str.size() << " bytes from the BytesIO stream" << std::endl;

    //std::string path;
    
    container_lib::container doc_raw;
    
    // parse the pdf file on path
    if (not interface.parse_pdf_page(data_str.c_str(), data_str.size(), page, doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not parse the PDF file";

        nlohmann::json data;
        data["message"] = "could not parse the PDF file";
        return data;
      }

    // only keep page -> bring it to the first and then resize array
    {
      if(page>0)
	{
	  doc_raw["pages"][0] = doc_raw["pages"][page];
	}
      doc_raw["pages"].resize(1);
    }
    
    if (not interface.clean_raw_page(doc_raw))
      {
        logging_lib::error("pdf-parser") << __FILE__ << ":" << __LINE__ << "\t"
                                         << "could not clean the raw file";

        nlohmann::json data;
        data["message"] = "could not clean the raw file";
        return data;
      }

    interface.clean_pages(doc_raw);

    // remove font information ...
    for(int pid=0; pid<doc_raw["pages"].get_size(); pid++)
      {
	if(doc_raw["pages"][pid].has("fonts"))
	  {	    
	    doc_raw["pages"][pid].erase("fonts");
	  }
      }
    
    IO::writer<IO::JSON_CONTAINER> writer;
    std::string result = writer.to_string(doc_raw);    

    nlohmann::json output = nlohmann::json::parse(result);
    return output;
  }
  
}

#endif
