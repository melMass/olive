#ifndef TIMELINEVIEWBASE_H
#define TIMELINEVIEWBASE_H

#include <QGraphicsView>

#include "timelineplayhead.h"
#include "timelineviewenditem.h"
#include "widget/timelinewidget/timelinescaledobject.h"

class TimelineViewBase : public QGraphicsView, public TimelineScaledObject
{
  Q_OBJECT
public:
  TimelineViewBase(QWidget* parent = nullptr);

  void SetScale(const double& scale);

  void SetEndTime(const rational& length);

public slots:
  void SetTimebase(const rational& timebase);

  void SetTime(const int64_t time);

signals:
  void TimeChanged(const int64_t& time);

  void ScaleChanged(double scale);

protected:
  virtual void drawForeground(QPainter *painter, const QRectF &rect) override;

  virtual void resizeEvent(QResizeEvent *event) override;

  virtual void ScaleChangedEvent(double scale);

  bool HandleZoomFromScroll(QWheelEvent* event);

  bool WheelEventIsAZoomEvent(QWheelEvent* event);

  void SetLimitYAxis(bool e);

  rational GetPlayheadTime();

  bool PlayheadPress(QMouseEvent* event);
  bool PlayheadMove(QMouseEvent* event);
  bool PlayheadRelease(QMouseEvent* event);

private:
  qreal GetPlayheadX();

  int64_t playhead_;

  TimelinePlayhead playhead_style_;

  double playhead_scene_left_;
  double playhead_scene_right_;

  bool dragging_playhead_;

  TimelineViewEndItem* end_item_;

  QGraphicsScene scene_;

  bool limit_y_axis_;

private slots:
  /**
   * @brief Slot called whenever the view resizes or the scene contents change to enforce minimum scene sizes
   */
  void UpdateSceneRect();

  /**
   * @brief Slot to center the horizontal scroll bar on the playhead's current position
   */
  void CenterScrollOnPlayhead();

  /**
   * @brief Slot to handle page scrolling of the playhead
   *
   * If the playhead is outside the current scroll bounds, this function will scroll to where it is. Otherwise it will
   * do nothing.
   */
  void PageScrollToPlayhead();

};

#endif // TIMELINEVIEWBASE_H