#include <omni/ui/ScreenSetup.h>

#include <omni/proj/ScreenSetup.h>

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>

namespace omni
{
  namespace ui
  { 
    ScreenSetup::ScreenSetup(QWidget* _parent) :
      QWidget(_parent)
    {
      setMouseTracking(true);
      setAcceptDrops(true);
      updateScreens();
    }

    ScreenSetup::~ScreenSetup()
    {
    }
      
    float ScreenSetup::zoom() const
    {
      return zoom_;
    }

    void ScreenSetup::setZoom(float _zoom) 
    {
      zoom_=_zoom;
      update();
    }
    
    void ScreenSetup::updateScreens()
    {
      screenItems_.clear();
      desktopRect_ = QRect(0,0,0,0);

      setup_ = proj::ScreenSetup::current();

      for (auto& _screen : setup_.screens())
      {
        screenItems_.push_back(Item(*this,_screen));

        desktopRect_ |= _screen.rect();
      }
    }
      
    float ScreenSetup::scalingFactor() const 
    {
      auto _windowRect = this->rect();
      float _rectAspect = desktopRect_.width() / desktopRect_.height();
      float _windowAspect = _windowRect.width() / _windowRect.height();

      float _factor = 1.0f;

      if (_rectAspect > _windowAspect) {                
        _factor = _windowRect.width() / desktopRect_.width();
      } else {
        _factor = _windowRect.height() / desktopRect_.height();
      }

      return _factor * zoom();
    }

    QRectF ScreenSetup::transformedRect() const
    {
      auto _windowRect = this->rect();
      auto _zoom = scalingFactor();
      return QRectF(
          0.5*(_windowRect.width() - _zoom * (desktopRect_.width())),
          0.5*(_windowRect.height() - _zoom * (desktopRect_.height())),
          _zoom * desktopRect_.width(),
          _zoom * desktopRect_.height());
    }

    QRectF ScreenSetup::transformedRect(QRectF const& _rect) const
    {
      auto _zoom = scalingFactor();

      /// Transformed desktop rect
      auto _desktopRect = transformedRect();

      return QRectF(
          _desktopRect.x() + _rect.x() * _zoom,
          _desktopRect.y() + _rect.y() * _zoom,
          _rect.width() * _zoom,
          _rect.height() * _zoom);
    }

      
    void ScreenSetup::mouseMoveEvent(QMouseEvent* _event)
    {
      bool _update = false;
      for (auto& _item : screenItems_)
      {
        bool _pointInRect = _item.rect().contains(_event->pos());
        _update |= _pointInRect != _item.mouseOver();
        _item.setMouseOver(_pointInRect);
      }

      if (_update)
        update();
    }
 
    void ScreenSetup::paintEvent(QPaintEvent*)
    {
      QPainter _p(this);
      
      _p.setPen(QPen(QColor("#ffffff").darker(150),3));

      _p.drawRect(transformedRect());

      for (auto& _item : screenItems_)
      {
        _item.paint(_p);
      }
    }


    /// ScreenSetup::Item 
    /////////////////////////////////////////
    
    ScreenSetup::Item::Item(
        ScreenSetup& _screenSetup,
        Screen const& _screen) :
      screenSetup_(_screenSetup),
      screen_(_screen)
    {
    
    }

    bool ScreenSetup::Item::mouseOver() const
    {
      return mouseOver_;
    }

    void ScreenSetup::Item::setMouseOver(bool _mouseOver) 
    {
      mouseOver_=_mouseOver;
    }

    bool ScreenSetup::Item::drop() const
    {
      return drop_;
    }

    void ScreenSetup::Item::setDrop(bool _drop) 
    {
      drop_=_drop;
    }

    QRectF ScreenSetup::Item::rect() const
    {
      return screenSetup_.transformedRect(screen_.rect());
    }

    void ScreenSetup::Item::paint(QPainter& _p)
    {
      // Draw rectangle with tuning color
      QColor _color = tuning_ ? tuning_->color() : "#cccccc";

      if (mouseOver_)
      {
        _color = _color.lighter(120);
      }
      
      _p.setBrush(_color);
      _p.setPen(QPen(_color.darker(200),1));

      auto _rect = rect();
      _p.drawRect(_rect); 

      // Draw resolution text
      _p.setBrush(Qt::NoBrush);
      _p.setPen(QPen(_color.darker(500),1));

      // Resolution string
      QString _resStr = QString("%1 x %2").arg(screen_.width()).arg(screen_.height());

      _p.drawText(_rect,Qt::AlignHCenter | Qt::AlignVCenter,_resStr);
    }

    void ScreenSetup::Item::attachTuning(omni::proj::Tuning* _tuning)
    {
      tuning_=_tuning;
      screenSetup_.update();
    }

    void ScreenSetup::Item::detachTuning()
    {
      tuning_ = nullptr;
      screenSetup_.update();
    }
  }
}
