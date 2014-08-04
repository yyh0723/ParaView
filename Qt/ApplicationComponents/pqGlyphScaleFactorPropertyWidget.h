/*=========================================================================

   Program: ParaView
   Module:  pqGlyphScaleFactorPropertyWidget.h

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#ifndef __pqGlyphScaleFactorPropertyWidget_h
#define __pqGlyphScaleFactorPropertyWidget_h

#include "pqApplicationComponentsModule.h"
#include "pqDoubleVectorPropertyWidget.h"

#include <QPalette>

/// pqGlyphScaleFactorPropertyWidget is used for the "Scale Factor" property on
/// the Glyph filter. It adds a button to the widget that allows the user to
/// "reset" property value using the domain.
class PQAPPLICATIONCOMPONENTS_EXPORT pqGlyphScaleFactorPropertyWidget : public pqDoubleVectorPropertyWidget
{
  Q_OBJECT
  typedef pqDoubleVectorPropertyWidget Superclass;
public:
  pqGlyphScaleFactorPropertyWidget(
    vtkSMProxy* proxy, vtkSMProperty* property, QWidget* parent=0);
  virtual ~pqGlyphScaleFactorPropertyWidget();

  /// overridden to clear the highlights on the "reset" button.
  virtual void apply();
  virtual void reset();

protected slots:
  /// highlights the button.
  void highlightResetButton(bool highlight=true);

  /// update the property's value using the domain.
  virtual void resetClicked();

private:
  Q_DISABLE_COPY(pqGlyphScaleFactorPropertyWidget);
  QWidget* ResetButton;
  QPalette ResetPalette;
};

#endif
