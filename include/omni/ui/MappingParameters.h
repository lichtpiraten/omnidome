/* Copyright (c) 2014-2015 "Omnidome" by cr8tr
 * Dome Mapping Projection Software (http://omnido.me).
 * Omnidome was created by Michael Winkelmann aka Wilston Oreo (@WilstonOreo)
 * 
 * This file is part of Omnidome.
 * 
 * Omnidome is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OMNI_UI_MAPPINGPARAMETERS_H_
#define OMNI_UI_MAPPINGPARAMETERS_H_

#include <omni/mapping/Interface.h>
#include <omni/ui/ParameterWidget.h>

namespace omni
{
  namespace ui
  {
    /**@brief Parameter widget for getting and setting mapping parameters 
     **/
    class MappingParameters : public ParameterWidget
    {
      Q_OBJECT
    public:
      MappingParameters(QWidget* _parent);
      ~MappingParameters();

      mapping::Interface* mapping();
      mapping::Interface const* mapping() const;
      void setMapping(mapping::Interface* _mapping);

      /// Set parameters from sliders to mapping
      void updateParameters();
    private:
      slim::Rotation* rotation_ = nullptr;

      /// Show widgets parameter according to given mapping type
      void widgetVisibility();
      
      /// Clear and setup all parameter widgets
      void setup();

      mapping::Interface* mapping_ = nullptr;
    };
  }
}


#endif /* OMNI_UI_MAPPINGPARAMETERS_H_ */
