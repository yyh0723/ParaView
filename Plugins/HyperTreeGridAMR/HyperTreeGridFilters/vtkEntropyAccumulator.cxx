/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkEntropyAccumulator.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkEntropyAccumulator.h"

#include "vtkObjectFactory.h"

#include <cassert>
#include <cmath>

vtkStandardNewMacro(vtkEntropyAccumulator);

//----------------------------------------------------------------------------
vtkEntropyAccumulator::vtkEntropyAccumulator()
{
  this->Value = 0.0;
}

//----------------------------------------------------------------------------
void vtkEntropyAccumulator::Add(vtkAbstractAccumulator* accumulator)
{
  assert(
    vtkEntropyAccumulator::SafeDownCast(accumulator) && "Cannot accumulate different accumulators");
  this->Value += accumulator->GetValue();
}

//----------------------------------------------------------------------------
void vtkEntropyAccumulator::Add(double value)
{
  this->Value += value * std::log(value);
}

//----------------------------------------------------------------------------
void vtkEntropyAccumulator::Initialize()
{
  this->Value = 0.0;
}

//----------------------------------------------------------------------------
void vtkEntropyAccumulator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Accumulated value : " << this->Value << std::endl;
}
