/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBase64OutputStream.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkBase64OutputStream.h"
#include "vtkObjectFactory.h"

//----------------------------------------------------------------------------
vtkCxxRevisionMacro(vtkBase64OutputStream, "1.2");
vtkStandardNewMacro(vtkBase64OutputStream);

//----------------------------------------------------------------------------
static unsigned char vtkBase64OutputStreamEncode(unsigned char c);

//----------------------------------------------------------------------------
vtkBase64OutputStream::vtkBase64OutputStream()
{
  this->BufferLength = 0;
}

//----------------------------------------------------------------------------
vtkBase64OutputStream::~vtkBase64OutputStream()
{
}

//----------------------------------------------------------------------------
void vtkBase64OutputStream::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int vtkBase64OutputStream::StartWriting()
{
  if(!this->Superclass::StartWriting())
    {
    return 0;
    }
  this->BufferLength = 0;
  return 1;
}

//----------------------------------------------------------------------------
int vtkBase64OutputStream::EndWriting()
{
  if(this->BufferLength == 1)
    {
    if(!this->EncodeEnding(this->Buffer[0])) { return 0; }
    this->BufferLength = 0;
    }
  else if(this->BufferLength == 2)
    {
    if(!this->EncodeEnding(this->Buffer[0], this->Buffer[1])) { return 0; }
    this->BufferLength = 0;
    }
  return 1;
}

//----------------------------------------------------------------------------
int vtkBase64OutputStream::Write(const unsigned char* data,
                                 unsigned long length)
{ 
  unsigned long totalLength = this->BufferLength + length;
  const unsigned char* in = data;
  const unsigned char* end = data+length;
  
  if(totalLength >= 3)
    {
    if(this->BufferLength == 1)
      {
      if(!this->EncodeTriplet(this->Buffer[0], in[0], in[1])) { return 0; }
      in += 2;
      this->BufferLength = 0;
      }
    else if(this->BufferLength == 2)
      {
      if(!this->EncodeTriplet(this->Buffer[0], this->Buffer[1], in[0]))
        { return 0; }
      in += 1;
      this->BufferLength = 0;
      }
    }
  
  while((end - in) >= 3)
    {
    if(!this->EncodeTriplet(in[0], in[1], in[2])) { return 0; }
    in += 3;
    }
  
  while(in != end)
    {
    this->Buffer[this->BufferLength++] = *in++;
    }
  return 1;
}

//----------------------------------------------------------------------------
inline int vtkBase64OutputStream::EncodeTriplet(unsigned char c0,
                                                unsigned char c1,
                                                unsigned char c2)
{
  // Encodes 3 bytes into 4 bytes and writes them to the output stream.
  unsigned char out[4];
  out[0] = vtkBase64OutputStreamEncode((c0 >> 2) & 0x3F);
  out[1] = vtkBase64OutputStreamEncode(((c0 << 4) & 0x30)|((c1 >> 4) & 0x0F));
  out[2] = vtkBase64OutputStreamEncode(((c1 << 2) & 0x3C)|((c2 >> 6) & 0x03));
  out[3] = vtkBase64OutputStreamEncode(c2 & 0x3F);
  return (this->Stream->write(out, 4)? 1:0);
}
  
//----------------------------------------------------------------------------
inline int vtkBase64OutputStream:: EncodeEnding(unsigned char c0,
                                                unsigned char c1)
{
  // Encodes a 2-byte ending into 3 bytes and 1 pad byte and writes.
  unsigned char out[4];
  out[0] = vtkBase64OutputStreamEncode((c0 >> 2) & 0x3F);
  out[1] = vtkBase64OutputStreamEncode(((c0 << 4) & 0x30)|((c1 >> 4) & 0x0F));
  out[2] = vtkBase64OutputStreamEncode(((c1 << 2) & 0x3C));
  out[3] = '=';
  return (this->Stream->write(out, 4)? 1:0);
}

//----------------------------------------------------------------------------
inline int vtkBase64OutputStream::EncodeEnding(unsigned char c0)
{
  // Encodes a 1-byte ending into 2 bytes and 2 pad bytes and writes.
  unsigned char out[4];
  out[0] = vtkBase64OutputStreamEncode((c0 >> 2) & 0x3F);
  out[1] = vtkBase64OutputStreamEncode(((c0 << 4) & 0x30));
  out[2] = '=';
  out[3] = '=';
  return (this->Stream->write(out, 4)? 1:0);
}

//----------------------------------------------------------------------------
static const unsigned char vtkBase64OutputStreamEncodeTable[65] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789+/";

//----------------------------------------------------------------------------
unsigned char vtkBase64OutputStreamEncode(unsigned char c)
{ 
  return vtkBase64OutputStreamEncodeTable[c]; 
}

