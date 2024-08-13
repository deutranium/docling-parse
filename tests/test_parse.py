#!/usr/bin/env python

GENERATE = False

import io
import os

import glob
import json

from docling_parse import docling_parse

def test_reference_documents_from_filenames():

    parser = docling_parse.pdf_parser()

    pdf_docs = glob.glob("./tests/pdf_docs/tests/*.pdf")

    assert len(pdf_docs)>0, "len(pdf_docs)==0 -> nothing to test"
    
    for pdf_doc in pdf_docs:
        print(pdf_doc)
        pred_doc = parser.find_cells(pdf_doc)

        if GENERATE:
            with open(pdf_doc+".json", "w") as fw:
                fw.write(json.dumps(pred_doc, indent=2))

            assert True
        else:
            with open(pdf_doc+".json", "r") as fr:
                true_doc = json.load(fr)

            num_true_pages=len(true_doc["pages"])
            num_pred_pages=len(pred_doc["pages"])
            
            assert num_true_pages==num_pred_pages, f"len(pred_doc[\"pages\"])!=len(true_doc[\"pages\"]) => {num_true_pages}!={num_pred_pages}"
                
            for pred_page,true_page in zip(pred_doc["pages"], true_doc["pages"]):

                assert pred_page["cells"]==true_page["cells"], "pred_page[\"cells\"]!=true_page[\"cells\"]"
                
                for pred_cell,true_cell in zip(pred_page["cells"], true_page["cells"]):
                    pred_text = pred_cell['content']['rnormalized']
                    true_text = true_cell['content']['rnormalized']
                    
                    assert pred_text==true_text, f"pred_text!=true_text => {pred_text}!={true_text}"
                    
                    pred_bbox = pred_cell['box']['device']
                    true_bbox = true_cell['box']['device']

                    for i in range(0,4):
                        assert round(pred_bbox[i])==round(true_bbox[i]), "round(pred_bbox[i])!=round(true_bbox[i])"

def test_reference_documents_from_bytesio():

    parser = docling_parse.pdf_parser()

    pdf_docs = glob.glob("./tests/pdf_docs/tests/*.pdf")

    assert len(pdf_docs)>0, "len(pdf_docs)==0 -> nothing to test"
    
    for pdf_doc in pdf_docs:
        print(pdf_doc)

        # Open the file in binary mode and read its contents
        with open(pdf_doc, "rb") as file:
            file_content = file.read()

        # Create a BytesIO object and write the file contents to it
        bytes_io = io.BytesIO(file_content)
    
        pred_doc = parser.find_cells_from_bytesio(bytes_io)

        if GENERATE:
            with open(pdf_doc+".json", "w") as fw:
                fw.write(json.dumps(pred_doc, indent=2))

            assert True
        else:
            with open(pdf_doc+".json", "r") as fr:
                true_doc = json.load(fr)

            num_true_pages=len(true_doc["pages"])
            num_pred_pages=len(pred_doc["pages"])
            
            assert num_true_pages==num_pred_pages, f"len(pred_doc[\"pages\"])!=len(true_doc[\"pages\"]) => {num_true_pages}!={num_pred_pages}"
                
            for pred_page,true_page in zip(pred_doc["pages"], true_doc["pages"]):

                assert pred_page["cells"]==true_page["cells"], "pred_page[\"cells\"]!=true_page[\"cells\"]"
                
                for pred_cell,true_cell in zip(pred_page["cells"], true_page["cells"]):
                    pred_text = pred_cell['content']['rnormalized']
                    true_text = true_cell['content']['rnormalized']
                    
                    assert pred_text==true_text, f"pred_text!=true_text => {pred_text}!={true_text}"
                    
                    pred_bbox = pred_cell['box']['device']
                    true_bbox = true_cell['box']['device']

                    for i in range(0,4):
                        assert round(pred_bbox[i])==round(true_bbox[i]), "round(pred_bbox[i])!=round(true_bbox[i])"
                        
