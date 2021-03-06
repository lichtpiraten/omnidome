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

#ifndef OMNI_CANVAS_PLANAR_H_
#define OMNI_CANVAS_PLANAR_H_

#include <omni/canvas/Interface.h>
#include <omni/EulerAngles.h>

namespace omni
{
  namespace canvas
  {
    /// A planar canvas 
    class Planar : 
      public Canvas,
      Registrar<Planar>
    {
    public:
      OMNI_TYPEID("Planar")

      Planar();
      ~Planar();
      
      void draw() const;
      void drawAux() const;

      float width() const;
      void setWidth(float _width);
      
      float height() const;
      void setHeight(float _height);

      QVector3D center() const;
      void setCenter(QVector3D const&);
      
      EulerAngles& angles();
      EulerAngles const& angles() const;
       
      omni::Box bounds() const;

      void fromStream(QDataStream&);
      void toStream(QDataStream&) const;

    private:
      float width_ = 1.0, height_ = 1.0;
      QVector3D center_;
      EulerAngles angles_;
    };
  }
}


#endif /* OMNI_CANVAS_PLANAR_H_ */
